#include <algorithm>
#include <boost/foreach.hpp>
#include ".\formattransport.h"
#include ".\NetSimulateCommunicate.h"

#include "..\SimulatorBase\EventIrp_SimulateTrigger.h"


using namespace jysoft::irp;
namespace jysoft { namespace transLayer 
{
	//============================================================================
	//�̺߳���
	UINT WINAPI ThrdTransUpIrpFunc(LPVOID lpVoid)
	{
		CFormatTransport *pFormatTranspt = (CFormatTransport *)lpVoid;
		::ResetEvent(pFormatTranspt->m_hThrdFinish[0]);
		HANDLE  phEvents[2];
		phEvents[0] = pFormatTranspt->m_hThreadOut;
		phEvents[1] = pFormatTranspt->m_hUp;
		while(1)
		{
            unsigned long dwRtn = ::WaitForMultipleObjects(2,phEvents,false,INFINITE);
			switch(dwRtn)
			{
			case WAIT_OBJECT_0:
				{
					::SetEvent(pFormatTranspt->m_hThrdFinish[0]);
					return 0;
				}
			case WAIT_OBJECT_0 + 1:
				{
					::SetEvent(*pFormatTranspt->GetTransportIrpHandlePtr());
					HANDLE phTransport[2];
					phTransport[0] = pFormatTranspt->m_hThreadOut;
					phTransport[1] = pFormatTranspt->m_hTransportFinish;//���������־�¼�
					DWORD dwRtn1 = ::WaitForMultipleObjects(2,phTransport,false,200);
					switch(dwRtn1)
					{
					case WAIT_OBJECT_0:
						{
							::SetEvent(pFormatTranspt->m_hThrdFinish[0]);
							return 0;
						}
					default:
						{
							::ResetEvent(pFormatTranspt->m_hTransportFinish);
							if(pFormatTranspt->m_lstUpIrps.size() == 0)
								::ResetEvent(pFormatTranspt->m_hUp);
							break;
						}
					}
					break;
				}
			}
		}
		return 0;
	}

	UINT WINAPI ThrdTransDownIrpFunc(LPVOID lpVoid)
	{
		CFormatTransport *pFormatTranspt = (CFormatTransport *)lpVoid;
		::ResetEvent(pFormatTranspt->m_hThrdFinish[1]);
		HANDLE  phEvents[2];
		phEvents[0] = pFormatTranspt->m_hThreadOut;
		phEvents[1] = pFormatTranspt->m_hDown;
		while(1)
		{
            unsigned long dwRtn = ::WaitForMultipleObjects(2,phEvents,false,INFINITE);
			switch(dwRtn)
			{
			case WAIT_OBJECT_0:
				{
					::SetEvent(pFormatTranspt->m_hThrdFinish[1]);
					return 0;
				}
			case WAIT_OBJECT_0 + 1:
				{
					pFormatTranspt->m_cDownMutex.Lock();
					CVirtualIrp *pIrp = *pFormatTranspt->m_lstDownIrps.begin();
					pFormatTranspt->m_lstDownIrps.pop_front();
					if(pFormatTranspt->m_lstDownIrps.size() == 0)
						::ResetEvent(pFormatTranspt->m_hDown);
					pFormatTranspt->GetFilterDownPtr()->TransportIrp(NULL,pIrp);
					delete pIrp;
					pFormatTranspt->m_cDownMutex.Unlock();
					break;
				}
			}
		}
		return 0;
	}
	//============================================================================
	CFormatTransport::CFormatTransport( int nCommunicateVersion )
	{
		m_phHaveIrp = NULL;
		m_pFilterDown   = new CFilterDown();
		m_pFilterUp     = new CFilterUp( this );
		//------------------------------------------------
		m_hUp = ::CreateEvent(NULL,true,false,NULL);;
		m_hDown = ::CreateEvent(NULL,true,false,NULL);;
		m_hThreadOut = ::CreateEvent(NULL,true,false,NULL);
		m_hThrdFinish[0] = ::CreateEvent(NULL,true,true,NULL);;
		m_hThrdFinish[1] = ::CreateEvent(NULL,true,true,NULL);;
		m_hTransportFinish = ::CreateEvent(NULL,true,false,NULL);
		m_bInitialize = FALSE;
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

	CFilterDown * CFormatTransport::GetFilterDownPtr()
	{
		return m_pFilterDown;
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
			m_pFilterDown->StartFilterDownTransFuncThread();
			//=======�����߳�==============
			::AfxBeginThread((AFX_THREADPROC)ThrdTransUpIrpFunc,(LPVOID)this,THREAD_PRIORITY_ABOVE_NORMAL);
			::AfxBeginThread((AFX_THREADPROC)ThrdTransDownIrpFunc,(LPVOID)this,THREAD_PRIORITY_ABOVE_NORMAL);
			m_bInitialize = TRUE;

			m_nPaceDelayTime          = -1;
		}
	}

	// ֹͣ���ݽ��պͷ����߳�
	void CFormatTransport::StopTransportData(void)
	{
		if( m_bInitialize )
		{
			::SetEvent(m_hThreadOut);
			::WaitForMultipleObjects(2,m_hThrdFinish,true,INFINITE);
			CloseHandle(m_hThrdFinish[0]);
			CloseHandle(m_hThrdFinish[1]);
			CloseHandle(m_hUp);
			CloseHandle(m_hDown);
			CloseHandle(m_hThreadOut);
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
			m_bInitialize = false;
			delete m_pFilterDown;
			m_pFilterDown  = NULL;
		}
	}

	// Function name   : SetUpCommunicates
	// Description     : ��������λ���������ݵ����з�ʽ(��ʽ���������ڣ�����)
	// Return type     : ��
	// Argument        : CVirtualCommunicate *pUpCommunicates[]
	// Argument        : UINT uNumber
    void CFormatTransport::SetUpCommunicates(CVirtualCommunicate *pUpCommunicates[], short uNumber)
	{
		for(UINT i = 0; i<uNumber; ++i)
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
			m_cUpMutex.Lock();
			m_lstUpIrps.push_back(pUpIrp);
			::SetEvent(m_hUp);
			m_cUpMutex.Unlock();
		}
		else
			delete pUpIrp;
	}

	void CFormatTransport::AddDownIrpToList(CVirtualIrp * pDownIrp)
	{
		if(m_bInitialize)
		{
			m_cDownMutex.Lock();
			m_lstDownIrps.push_back(pDownIrp);
			::SetEvent(m_hDown);
			m_cDownMutex.Unlock();
		}
		else
			delete pDownIrp;
	}

	//�������е�Irp���䵽�ϲ��
	CVirtualIrp * CFormatTransport::TransportIrpInUplst()
	{
		CVirtualIrp *pRtnIrp = NULL;
		m_cUpMutex.Lock();
		pRtnIrp = *m_lstUpIrps.begin();
		m_lstUpIrps.pop_front();
		m_cUpMutex.Unlock();
		if( m_phHaveIrp != NULL )
		{
			::ResetEvent(*m_phHaveIrp);
		}
		::SetEvent(m_hTransportFinish);
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
	BOOL CFormatTransport::OnFilterTransUpIrp(CVirtualIrp *pTransUpIrp)
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
		return FALSE;
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
