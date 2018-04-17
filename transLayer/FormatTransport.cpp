#include <algorithm>
#include <boost/foreach.hpp>
#include ".\formattransport.h"
#include ".\NetSimulateCommunicate.h"

#include "..\SimulatorBase\EventIrp_SimulateTrigger.h"


using namespace jysoft::irp;
namespace jysoft { namespace transLayer 
{
	void CFormatTransport::ThrdTransDownIrpFunc()
	{
		try
		{
			while(1)
			{
				CVirtualIrp *pIrp = NULL;
				{
					boost::mutex::scoped_lock lock(muDownIrp);
					cond_getDownIrp.wait(lock, boost::bind(&CFormatTransport::isTransInDownIrps, this));
					//先进先出处理接收包, 获取第一个包
					pIrp = *m_lstDownIrps.begin();
					m_lstDownIrps.pop_front();
				}
				boost::this_thread::interruption_point();
				m_pFilterDown->TransportIrp(NULL,pIrp);
				delete pIrp;
			}
		}
		catch (boost::thread_interrupted &)
		{
			;
		}
	}
	//============================================================================
	CFormatTransport::CFormatTransport( int nCommunicateVersion )
	{
		cond_IrpUp = NULL;
		m_pFilterDown   = new CFilterDown();
		m_pFilterUp     = new CFilterUp( this );
		//------------------------------------------------
		m_bInitialize = false;
		//默认为V1.0版本通信协议
		m_pTriggerJudgeInterface  = new CBlsTriggerJudgeVersion();

		m_nPaceDelayTime          = -1;
	}

	CFormatTransport::~CFormatTransport(void)
	{
		StopTransportData();
		if( m_pTriggerJudgeInterface != NULL )
		{
			delete m_pTriggerJudgeInterface;
			m_pTriggerJudgeInterface = NULL;
		}
		delete m_pFilterUp;
	}

	bool CFormatTransport::isTransUpIrps()
	{
		boost::mutex::scoped_lock  lock(muUpIrp);
		if( m_bInitialize && m_lstUpIrps.size() > 0 )
		{
			return true;
		}
		return false;
	}

	// 构建数据接收和发送线程
	void CFormatTransport::StartTransportData(void)
	{
		if(m_bInitialize == false)
		{
			if( m_pFilterDown == NULL )
			{
				m_pFilterDown  = new CFilterDown();
			}
			//=======创建线程==============
			tgDownIrpThread.create_thread( boost::bind(&CFormatTransport::ThrdTransDownIrpFunc, this));
			m_bInitialize = true;

			m_nPaceDelayTime          = -1;
		}
	}

	// 停止数据接收和发送线程
	void CFormatTransport::StopTransportData(void)
	{
		if( m_bInitialize )
		{
			m_bInitialize = false;
			tgDownIrpThread.interrupt_all();
			tgDownIrpThread.join_all();
			BOOST_FOREACH(auto x, m_lstUpIrps)
			{
				delete x;
			}
			m_lstUpIrps.clear();
			BOOST_FOREACH(auto x, m_lstDownIrps)
			{
				delete x;
			}
			m_lstDownIrps.clear();
			delete m_pFilterDown;
			m_pFilterDown  = NULL;
		}
	}

	// Function name   : SetUpCommunicates
	// Description     : 设置向上位机发送数据的所有方式(方式包括：串口，网络)
	// Return type     : 无
	// Argument        : CVirtualCommunicate *pUpCommunicates[]
	// Argument        : short uNumber
	void CFormatTransport::SetUpCommunicates(CVirtualCommunicate *pUpCommunicates[], short uNumber)
	{
		for(short i = 0; i<uNumber; ++i)
		{
			pUpCommunicates[i]->SetFilterUpPtr(m_pFilterUp);
			//----------------------------------------------------------
			CNetSimulateCommunicate *pCommCommnunicate = dynamic_cast<CNetSimulateCommunicate *>(pUpCommunicates[i]);
			if( pCommCommnunicate != NULL )
			{
				pCommCommnunicate->SetSimulateTriggerJudgePtr( m_pTriggerJudgeInterface );
			}
		}
	}

	void CFormatTransport::RmvUpCommunicate(CVirtualCommunicate *pUpCommunicate)
	{
		pUpCommunicate->SetFilterUpPtr(NULL);
	}

	//设置与CFilterUp连通的通信链路
	void CFormatTransport::SetFilterUpLinkCommunicates(CVirtualCommunicate *pUpCommunicates[], short uNumber, bool bRmvCurrCommunicate /*=true*/)
	{
		m_pFilterUp->SetFilterUpLinkCommunicates(pUpCommunicates,uNumber,bRmvCurrCommunicate);
	}

	void CFormatTransport::RmvFilterUpLinkCommunicate(CVirtualCommunicate *pUpCommunicate)
	{
		m_pFilterUp->RmvFilterUpLinkCommunicate(pUpCommunicate);
	}
	//设置与CFilterDown连通的通信链路
	void CFormatTransport::SetFilterDownLinkCommunicates(CVirtualCommunicate *pDownCommunicates[], short uNumber, bool bRmvCurrCommunicate/*=true*/)
	{
		if( m_pFilterDown != NULL )
		{
			m_pFilterDown->SetFilterDownLinkCommunicates(pDownCommunicates,uNumber,bRmvCurrCommunicate);
		}
	}

	void CFormatTransport::RmvFilterDownLinkCommunicates(CVirtualCommunicate *pDownCommunicate)
	{
		CVirtualCommunicate *pDownCommunicates[1];
		pDownCommunicates[0] = pDownCommunicate;
		if( m_pFilterDown != NULL )
		{
			m_pFilterDown->RmvFilterDownLinkCommunicates(pDownCommunicates, 1);
		}
	}

	void CFormatTransport::AddUpIrpToList(CVirtualIrp * pUpIrp)
	{
		if(m_bInitialize && !OnFilterTransUpIrp(pUpIrp))
		{
			boost::mutex::scoped_lock  lock(muUpIrp);
			m_lstUpIrps.push_back(pUpIrp);
			if( cond_IrpUp != NULL )
			{
				cond_IrpUp->notify_one();
			}
		}
		else
			delete pUpIrp;
	}

	void CFormatTransport::AddDownIrpToList(CVirtualIrp * pDownIrp)
	{
		if(m_bInitialize)
		{
			boost::mutex::scoped_lock  lock(muUpIrp);
			m_lstDownIrps.push_back(pDownIrp);
			cond_getDownIrp.notify_one();
		}
		else
			delete pDownIrp;
	}

	//将链表中的Irp传输到上层端
	CVirtualIrp * CFormatTransport::TransportIrpInUplst()
	{
		boost::mutex::scoped_lock  lock(muUpIrp);
		CVirtualIrp *pRtnIrp = *m_lstUpIrps.begin();
		m_lstUpIrps.pop_front();
		return pRtnIrp;
	}

	// 创建标准的通信层
	void CFormatTransport::CreateStandantCommunicate(CVirtualCommunicate * pCommCommunicatePtr)
	{
		CVirtualCommunicate *plstPtr[1];
		plstPtr[0] = pCommCommunicatePtr;
		//设置与CFilterDown连通的通信链路
		SetFilterDownLinkCommunicates(plstPtr,1, false);
		//设置向上传递的通信链路
		SetUpCommunicates(plstPtr,1);
	}

	//移除标准的通信层
	void CFormatTransport::RmvStandantCommunicate(CVirtualCommunicate * pCommCommunicatePtr)
	{
		CVirtualCommunicate *plstPtr[1];
		plstPtr[0] = pCommCommunicatePtr;
		if( m_pFilterDown != NULL )
		{
			m_pFilterDown->RmvFilterDownLinkCommunicates(plstPtr, 1);
		}
		//取消向上传递的通信链路
		pCommCommunicatePtr->SetFilterUpPtr(NULL);
	}

	//向上传输Irp
	void CFormatTransport::OnTranslateUpIrp(CVirtualIrp * pUpIrp)
	{
		m_pFilterUp->TransportIrp(pUpIrp);
	}

	//向下传输Irp
	void CFormatTransport::TranslateDownIrp(CVirtualCommunicate *pSrcCommunicate, CVirtualIrp * pDownIrp)
	{
		if( m_bInitialize && pDownIrp )
		{
			m_pFilterDown->TransportIrp(pSrcCommunicate, pDownIrp);
		}
		else
		{
			delete pDownIrp;
		}
	}

	/*******************************************************************************/
	// 函数名称： OnTransportDownOrderToSimulater
	// 功能：  向模拟人发送指令
	// 参数： 
	// 返回值:  
	void CFormatTransport::OnTransportDownOrderToSimulater(irp::CSimulatorOrderIrp *pOrderIrp)
	{
		if( pOrderIrp != NULL )
		{
			TranslateDownIrp( NULL, pOrderIrp );
		}
	}

	/*******************************************************************************/
	// 函数名称： NetworkTranslateUpIrp
	// 功能：  通过网络向上传输Irp
	// 参数： 
	// 返回值:  
	void CFormatTransport::OnTranslateUpIrpNoNetwork( CVirtualIrp * pUpIrp )
	{
		if( pUpIrp != NULL )
		{
			m_pFilterUp->TranslateUpIrpNoNetwork( pUpIrp );
		}
	}

	//过滤向上发送的Irp
	bool CFormatTransport::OnFilterTransUpIrp(CVirtualIrp *pTransUpIrp)
	{
	//	if( pTransUpIrp && pTransUpIrp->Get_eIrpType() == eSimulateTrigger_Event )
	//	{
	//		// 返回Event的指针
	//		CEventIrp_SimulateTrigger * pSimulateTriggerEventIrp = (CEventIrp_SimulateTrigger *)pTransUpIrp;
	//		if( pSimulateTriggerEventIrp->m_strTriggerEventName ==  CSEvent_Pace::getEvent_Pace_Caption() )
	//		{
	//			short sPaceSign, sHeartRate;
	//			if( pSimulateTriggerEventIrp->explainSimulateTrigger_PaceEventIrp(/*out*/sPaceSign, /*out*/sHeartRate) && sPaceSign == 0x12 )
	//			{
	//				if( m_nPaceDelayTime > 0 )
	//				{
	//					m_nPaceDelayTime  = 5;
	//					return TRUE;
	//				}
	//				else
	//				{
	//					m_nPaceDelayTime  = 5;
	//				}
	//			}
	//		}
	//	}
		return false;
	}

	//减少过滤计数时间
	void CFormatTransport::DecreaseFilterTransUpIrpTime(short  sSecond)
	{
		m_nPaceDelayTime          -= sSecond;
	}

	//重置事件处理
	void CFormatTransport::ResetTransportHandle()
	{
		m_nPaceDelayTime          = -1;
	}
}}
