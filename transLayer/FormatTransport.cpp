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
					//�Ƚ��ȳ�������հ�, ��ȡ��һ����
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
		//Ĭ��ΪV1.0�汾ͨ��Э��
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

	// �������ݽ��պͷ����߳�
	void CFormatTransport::StartTransportData(void)
	{
		if(m_bInitialize == false)
		{
			if( m_pFilterDown == NULL )
			{
				m_pFilterDown  = new CFilterDown();
			}
			//=======�����߳�==============
			tgDownIrpThread.create_thread( boost::bind(&CFormatTransport::ThrdTransDownIrpFunc, this));
			m_bInitialize = true;

			m_nPaceDelayTime          = -1;
		}
	}

	// ֹͣ���ݽ��պͷ����߳�
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
	// Description     : ��������λ���������ݵ����з�ʽ(��ʽ���������ڣ�����)
	// Return type     : ��
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

	//������CFilterUp��ͨ��ͨ����·
	void CFormatTransport::SetFilterUpLinkCommunicates(CVirtualCommunicate *pUpCommunicates[], short uNumber, bool bRmvCurrCommunicate /*=true*/)
	{
		m_pFilterUp->SetFilterUpLinkCommunicates(pUpCommunicates,uNumber,bRmvCurrCommunicate);
	}

	void CFormatTransport::RmvFilterUpLinkCommunicate(CVirtualCommunicate *pUpCommunicate)
	{
		m_pFilterUp->RmvFilterUpLinkCommunicate(pUpCommunicate);
	}
	//������CFilterDown��ͨ��ͨ����·
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

	//�������е�Irp���䵽�ϲ��
	CVirtualIrp * CFormatTransport::TransportIrpInUplst()
	{
		boost::mutex::scoped_lock  lock(muUpIrp);
		CVirtualIrp *pRtnIrp = *m_lstUpIrps.begin();
		m_lstUpIrps.pop_front();
		return pRtnIrp;
	}

	// ������׼��ͨ�Ų�
	void CFormatTransport::CreateStandantCommunicate(CVirtualCommunicate * pCommCommunicatePtr)
	{
		CVirtualCommunicate *plstPtr[1];
		plstPtr[0] = pCommCommunicatePtr;
		//������CFilterDown��ͨ��ͨ����·
		SetFilterDownLinkCommunicates(plstPtr,1, false);
		//�������ϴ��ݵ�ͨ����·
		SetUpCommunicates(plstPtr,1);
	}

	//�Ƴ���׼��ͨ�Ų�
	void CFormatTransport::RmvStandantCommunicate(CVirtualCommunicate * pCommCommunicatePtr)
	{
		CVirtualCommunicate *plstPtr[1];
		plstPtr[0] = pCommCommunicatePtr;
		if( m_pFilterDown != NULL )
		{
			m_pFilterDown->RmvFilterDownLinkCommunicates(plstPtr, 1);
		}
		//ȡ�����ϴ��ݵ�ͨ����·
		pCommCommunicatePtr->SetFilterUpPtr(NULL);
	}

	//���ϴ���Irp
	void CFormatTransport::OnTranslateUpIrp(CVirtualIrp * pUpIrp)
	{
		m_pFilterUp->TransportIrp(pUpIrp);
	}

	//���´���Irp
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
	// �������ƣ� OnTransportDownOrderToSimulater
	// ���ܣ�  ��ģ���˷���ָ��
	// ������ 
	// ����ֵ:  
	void CFormatTransport::OnTransportDownOrderToSimulater(irp::CSimulatorOrderIrp *pOrderIrp)
	{
		if( pOrderIrp != NULL )
		{
			TranslateDownIrp( NULL, pOrderIrp );
		}
	}

	/*******************************************************************************/
	// �������ƣ� NetworkTranslateUpIrp
	// ���ܣ�  ͨ���������ϴ���Irp
	// ������ 
	// ����ֵ:  
	void CFormatTransport::OnTranslateUpIrpNoNetwork( CVirtualIrp * pUpIrp )
	{
		if( pUpIrp != NULL )
		{
			m_pFilterUp->TranslateUpIrpNoNetwork( pUpIrp );
		}
	}

	//�������Ϸ��͵�Irp
	bool CFormatTransport::OnFilterTransUpIrp(CVirtualIrp *pTransUpIrp)
	{
	//	if( pTransUpIrp && pTransUpIrp->Get_eIrpType() == eSimulateTrigger_Event )
	//	{
	//		// ����Event��ָ��
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

	//���ٹ��˼���ʱ��
	void CFormatTransport::DecreaseFilterTransUpIrpTime(short  sSecond)
	{
		m_nPaceDelayTime          -= sSecond;
	}

	//�����¼�����
	void CFormatTransport::ResetTransportHandle()
	{
		m_nPaceDelayTime          = -1;
	}
}}
