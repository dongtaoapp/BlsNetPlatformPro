#include ".\FilterUp.h"
#include ".\NetSimulateCommunicate.h"
#include <boost/assert.hpp>

#include "..\common\VirtualIrp.h"

#include "..\simulatorBase\RealTimeDataIrp.h"
#include "..\simulatorBase\EventIrp_SimulateTrigger.h"


//=======================�̺߳���======================================
//ʱ���߳�
unsigned long WINAPI ThrdMicroSecondTimeFunc(LPVOID lpVoid)
{
	jysoft::transLayer::CNetSimulateCommunicate *pPtrComm = (jysoft::transLayer::CNetSimulateCommunicate *)lpVoid;
	HANDLE  pHandles[2];
	pHandles[0] = pPtrComm->m_hPause;
	pHandles[1] = pPtrComm->m_hThrdOut;
	while(1)
	{
        unsigned long dwRtn = ::WaitForMultipleObjects(2,pHandles,false,INFINITE);
		if(dwRtn == WAIT_OBJECT_0+1)
		{
			break;
		}
		dwRtn  = ::WaitForSingleObject(pPtrComm->m_hThrdOut,70);
		switch(dwRtn)
		{
		case WAIT_TIMEOUT:
			{
				pPtrComm->OnTime(70);
				break;
			}
		default:
			{//�˳�
				::SetEvent(pPtrComm->m_hThrdFinish);
				return 0;
			}
		}
	}
	::SetEvent(pPtrComm->m_hThrdFinish);
	return 0;
}

namespace jysoft { namespace transLayer 
{
	CNetSimulateCommunicate::CNetSimulateCommunicate(network::CNetTransferVir *pVirNetTransfer) : CVirtualCommunicate()
		, m_cBufferAndJudgeCPR( this )
	{
		m_hThrdOut = NULL;
		m_hThrdFinish = NULL;
		m_hPause   = NULL;
		m_pTriggerJudgeInterface = NULL;
		m_pVirNetTransferPtr  = pVirNetTransfer;
		m_bTcpEstablishSec    = false;
	}
	
	CNetSimulateCommunicate::~CNetSimulateCommunicate(void)
	{
		::SetEvent(m_hThrdOut);
		if( m_hThrdFinish != NULL)
			::WaitForSingleObject(m_hThrdFinish, INFINITE);
		CloseHandle(m_hThrdOut);
		m_hThrdOut    = NULL;
		CloseHandle(m_hThrdFinish);
		m_hThrdFinish = NULL;
		CloseHandle(m_hPause);
		m_hPause    = NULL;
		m_pTriggerJudgeInterface = NULL;
	}

	//����ͨ��Э��汾�ӿ�
	void CNetSimulateCommunicate::SetSimulateTriggerJudgePtr(ISimulateTriggerJudge *pJudgeInterface)
	{
		m_pTriggerJudgeInterface  = pJudgeInterface;
	}

	void CNetSimulateCommunicate::OnTime(int nMicroSecond)
	{
		m_cBufferAndJudgeCPR.lapseTimerHandle(nMicroSecond);
	}

	// ��ʼ��ͨ�Žӿڣ�ʹ�����������շ�����
	bool CNetSimulateCommunicate::InitializeCommunicate(void)
	{
		if(m_hThrdOut != NULL)
			CloseHandle(m_hThrdOut);
		m_hThrdOut = ::CreateEvent(NULL,true,false,NULL);
		if(m_hThrdFinish != NULL)
			CloseHandle(m_hThrdFinish);
		m_hThrdFinish = ::CreateEvent(NULL,true,false,NULL);
		if(m_hPause != NULL)
			CloseHandle(m_hPause);
		m_hPause = ::CreateEvent(NULL,true,true,NULL);
		//=======�����߳�==============
		::AfxBeginThread((AFX_THREADPROC)ThrdMicroSecondTimeFunc,(LPVOID)this,THREAD_PRIORITY_ABOVE_NORMAL);
		return true;
	}

	//������յ�������
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

	//���ݴ���������
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

	//�жϲ��ϴ��¼�
	void CNetSimulateCommunicate::JudgeDataTypeAndTransUp(_VirDataStruct *pDataStruct)
	{
		if( m_pTriggerJudgeInterface->judgeRealTimeDataType(pDataStruct, NULL) )
		{
			_CPRData  cprData;
			m_pTriggerJudgeInterface->judgeRealTimeDataType(pDataStruct, &cprData );
			//�ϴ�CPRʵʱ��������
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

	//�����ݴ�����λ��
	void CNetSimulateCommunicate::TransDownData(irp::CVirtualIrp * pDownIrp)
	{
		if( pDownIrp->isKindOf( "CSimulatorOrderIrp" ) )
		{
			irp::CSimulatorOrderIrp *pOrderIrp = (irp::CSimulatorOrderIrp *)pDownIrp;
			
			//�����ݴ�����λ��
			static byte byteOrderData[100];
			std::list<std::string>::iterator iter;
			iter = pOrderIrp->StartUnDecode();
			//�����¸�ָ��
			long uSize = pOrderIrp->NextUnDecode(iter, byteOrderData);
			while( uSize > 0  )
			{
				//��������
				SendData(byteOrderData, uSize);
				uSize = pOrderIrp->NextUnDecode(iter, byteOrderData);
			}
		}
	}

	//����CPR����
	void CNetSimulateCommunicate::TransUpCPRDataFromBuffer(const _CPRData *ptrdwCPRData, int nLength)
	{
		if( m_pFilterUpPtr != NULL && nLength > 0 )
		{
			irp::CRealTimeDataIrp  *pRealTimeDataIrp = irp::CRealTimeDataIrp::CreateRealTimeData_CPRIrp(ptrdwCPRData, nLength);
			m_pFilterUpPtr->TransportIrp(pRealTimeDataIrp);
		}
	}

	//�ϴ�CPR��ʼ����
	void CNetSimulateCommunicate::TransUpCPRStartOrder()
	{
		/*if( m_pFilterUpPtr != NULL )
		{
			irp::CCPRStatIrp  *pCPRStatIrp = irp::CCPRStatIrp::CreateEvent_CPRIrp(eNoneDefine, 1);
			m_pFilterUpPtr->TransportIrp( pCPRStatIrp );
		}*/
	}

	//�ϴ�CPR��������
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

	//��ʼCPR����ģ��
	void CNetSimulateCommunicate::StartCPRSimulate()
	{
		::SetEvent(m_hPause);
	}

	//����CPR���弰�ж�
	void CNetSimulateCommunicate::ResetBufferAndJudgeCPR()
	{
		m_cBufferAndJudgeCPR.reset();
	}

}}
