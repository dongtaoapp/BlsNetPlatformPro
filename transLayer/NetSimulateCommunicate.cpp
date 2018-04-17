#include ".\FilterUp.h"
#include ".\NetSimulateCommunicate.h"
#include <boost/assert.hpp>

#include "..\common\VirtualIrp.h"

#include "..\simulatorBase\RealTimeDataIrp.h"
#include "..\simulatorBase\EventIrp_SimulateTrigger.h"


namespace jysoft { namespace transLayer 
{
	CNetSimulateCommunicate::CNetSimulateCommunicate(network::CNetTransferVir *pVirNetTransfer) : CVirtualCommunicate()
		, m_cBufferAndJudgeCPR( this )
	{
		m_pMicrosecTimer = NULL;
		m_pTriggerJudgeInterface = NULL;
		m_pVirNetTransferPtr  = pVirNetTransfer;
		m_bTcpEstablishSec    = false;
	}
	
	CNetSimulateCommunicate::~CNetSimulateCommunicate(void)
	{
		if( m_pMicrosecTimer != NULL )
		{
			m_pMicrosecTimer->killTimer();
			delete m_pMicrosecTimer;
		}
		m_pMicrosecTimer = NULL;
		if(m_pVirNetTransferPtr != NULL)
		{
			m_pVirNetTransferPtr->RemoveRecevNetDataOp(this);
		}
		m_pTriggerJudgeInterface = NULL;
	}

	//设置通信协议版本接口
	void CNetSimulateCommunicate::SetSimulateTriggerJudgePtr(ISimulateTriggerJudge *pJudgeInterface)
	{
		m_pTriggerJudgeInterface  = pJudgeInterface;
	}

	void CNetSimulateCommunicate::OnTime()
	{
		m_cBufferAndJudgeCPR.lapseTimerHandle(100);
	}

	// 初始化通信接口，使其能正常的收发数据
	bool CNetSimulateCommunicate::InitializeCommunicate(void)
	{
		if(m_pVirNetTransferPtr != NULL)
		{
			m_pVirNetTransferPtr->AddRecvNetDataOp(this);
		}
		if( m_pMicrosecTimer == NULL )
		{
			m_pMicrosecTimer = new utility::CEmulateTimer(100, boost::bind(&CNetSimulateCommunicate::OnTime, this));
		}
		return true;
	}

	//处理接收到的数据
	void CNetSimulateCommunicate::OnReceiveNetDataOp(network::NET_SOCKET_OBJ *sock, network::NET_BUFFER_OBJ *buf)
	{
		unsigned int nSumSize = 0;
		network::NET_BUFFER_OBJ *pRecvBuf = buf;
		while( pRecvBuf )
		{
			nSumSize += pRecvBuf->m_nCurrDataLen;
			pRecvBuf = pRecvBuf->next;
		}
		if( nSumSize == buf->m_nCurrDataLen && m_pTriggerJudgeInterface != NULL )
		{
			m_pTriggerJudgeInterface->writeCommunicateData( buf->m_cBuf+buf->m_uOffset, buf->m_nCurrDataLen );

			_VirDataStruct *pDataStruct = NULL;
			while ( (pDataStruct = m_pTriggerJudgeInterface->getDataStructFromCommData()) != NULL )
			{
				JudgeDataTypeAndTransUp( pDataStruct );
				delete pDataStruct;
			}
		}
		else
            BOOST_ASSERT( 0 );
	}

	//数据传到程序中
	void CNetSimulateCommunicate::TransUpData(void *lpData, short uNumber)
	{
		if( m_pTriggerJudgeInterface != NULL )
		{
			m_pTriggerJudgeInterface->writeCommunicateData( lpData, uNumber );

			_VirDataStruct *pDataStruct = NULL;
			while ( (pDataStruct = m_pTriggerJudgeInterface->getDataStructFromCommData()) != NULL )
			{
				JudgeDataTypeAndTransUp( pDataStruct );
				delete pDataStruct;
			}
		}
	}

	//判断并上传事件
	void CNetSimulateCommunicate::JudgeDataTypeAndTransUp(_VirDataStruct *pDataStruct)
	{
		if( m_pTriggerJudgeInterface->judgeRealTimeDataType(pDataStruct, NULL) )
		{
			_CPRData  cprData;
			m_pTriggerJudgeInterface->judgeRealTimeDataType(pDataStruct, &cprData );
			//上传CPR实时采样数据
			m_cBufferAndJudgeCPR.loadCPRNewData( cprData );
		}
		else
		{
			irp::CEventIrp_SimulateTrigger  *pSimulateTriggerIrp = m_pTriggerJudgeInterface->createEvent_SimulateTriggerIrp(pDataStruct);
			if(m_pFilterUpPtr != NULL && pSimulateTriggerIrp != NULL)
			{
				m_pFilterUpPtr->TransportIrp(pSimulateTriggerIrp);
			}
			else
			{
				delete pSimulateTriggerIrp;
			}
		}
	}

	//将内容传给下位机
	void CNetSimulateCommunicate::TransDownData(irp::CVirtualIrp * pDownIrp)
	{
		if( pDownIrp->isKindOf( "CSimulatorOrderIrp" ) )
		{
			irp::CSimulatorOrderIrp *pOrderIrp = (irp::CSimulatorOrderIrp *)pDownIrp;
			
			//将内容传给下位机
			static byte byteOrderData[100];
			std::list<std::string>::iterator iter;
			iter = pOrderIrp->StartUnDecode();
			//解码下个指令
			long uSize = pOrderIrp->NextUnDecode(iter, byteOrderData);
			while( uSize > 0  )
			{
				//发送数据
				SendData(byteOrderData, uSize);
				uSize = pOrderIrp->NextUnDecode(iter, byteOrderData);
			}
		}
	}

	//传输CPR数据
	void CNetSimulateCommunicate::TransUpCPRDataFromBuffer(const _CPRData *ptrdwCPRData, int nLength)
	{
		if( m_pFilterUpPtr != NULL && nLength > 0 )
		{
			irp::CRealTimeDataIrp  *pRealTimeDataIrp = irp::CRealTimeDataIrp::CreateRealTimeData_CPRIrp(ptrdwCPRData, nLength);
			m_pFilterUpPtr->TransportIrp(pRealTimeDataIrp);
		}
	}

	//上传CPR开始命令
	void CNetSimulateCommunicate::TransUpCPRStartOrder()
	{
		/*if( m_pFilterUpPtr != NULL )
		{
			irp::CCPRStatIrp  *pCPRStatIrp = irp::CCPRStatIrp::CreateEvent_CPRIrp(eNoneDefine, 1);
			m_pFilterUpPtr->TransportIrp( pCPRStatIrp );
		}*/
	}

	//上传CPR结束命令
	void CNetSimulateCommunicate::TransUpCPRStopOrder()
	{
		/*if( m_pFilterUpPtr != NULL )
		{
			irp::CCPRStatIrp  *pCPRStatIrp = irp::CCPRStatIrp::CreateEvent_CPRIrp(eNoneDefine, 0);
			m_pFilterUpPtr->TransportIrp( pCPRStatIrp );
		}*/
	}

	void CNetSimulateCommunicate::SendData(void *lpByte, short uSize)
	{
		if( m_pVirNetTransferPtr != NULL && m_bTcpEstablishSec )
		{
			m_pVirNetTransferPtr->DoSendData(lpByte, uSize, network::NT_SimulateCommData, eSimulateOrder);
		}
	}

	//开始CPR数据模拟
	void CNetSimulateCommunicate::StartCPRSimulate()
	{
		if( m_pMicrosecTimer != NULL )
		{
			m_pMicrosecTimer->startTimer();
		}
	}

	//重置CPR缓冲及判断
	void CNetSimulateCommunicate::ResetBufferAndJudgeCPR()
	{
		m_cBufferAndJudgeCPR.reset();
	}

}}
