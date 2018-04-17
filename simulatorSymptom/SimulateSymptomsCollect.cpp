#include <algorithm>
#include ".\simulatesymptomscollect.h"
#include ".\XActionVirtual.h"

#include ".\Symptom_Pace.h"
#include ".\Symptom_FrameTime.h"

#include "..\Common\ParseCPRData_Singleton.h"

#include "..\SimulatorBase\CPRStatIrp.h"
#include "..\SimulatorBase\RealTimeDataIrp.h"
#include "..\SimulatorBase\WatchBarsShowInterfacesAggregate.h"
#include "..\SimulatorBase\IPnPFacility.h"
#include "..\SimulatorBase\EventIrp_SimulateTrigger.h"
#include "..\SimulatorBase\EventIrp_ClockTime.h"

#include "..\ElementParse\SAction_ABP.h"
#include "..\ElementParse\SAction_Osat.h"
#include "..\ElementParse\SAction_Resp.h"
#include "..\ElementParse\SAction_ECG.h"
#include "..\ElementParse\SAction_Pupil.h"
#include "..\ElementParse\SAction_FrameTime.h"
#include "..\ElementParse\SEvent_Defibr.h"
#include "..\ElementParse\SAction_SceneTime.h"
#include "..\ElementParse\SAction_Pace.h"
#include "..\ElementParse\SEvent_Intubate.h"


using namespace jysoft::irp;
namespace jysoft { namespace simulator 
{
	CSimulateSymptomsCollect::CSimulateSymptomsCollect(void)
	{
		m_pTransportOrderInterface  = NULL;
	}

	CSimulateSymptomsCollect::~CSimulateSymptomsCollect(void)
	{
	}

	//������Ӧ����������ָ��
	bool CSimulateSymptomsCollect::FindSymptomByAction(std::list<CSymptomVirtual *>* /*out*/plstFindSymptoms, CXActionVirtual* /*in*/pVirAction)
	{
		return CVirSimulateSymptomsCollect::FindSymptomByAction(plstFindSymptoms, pVirAction->getActionCaption());
	}

	/*******************************************************************************/
	// �������ƣ� initialScenarioSet
	// ���ܣ�   ����������ʼ��Ϊ��ǰ����״̬
	// ������   std::list<CXActionVirtual *> *plstActions: 
	//          SimulatePatientType ePatientType: ģ��������
	// ����ֵ:  tag_TrendValue: ��ǰ���������õ�����ֵ
	void CSimulateSymptomsCollect::initialScenarioSet(std::list<CXActionVirtual *> *plstActions, SimulatePatientType ePatientType)
	{
		//����ǰ�����е�������������˳�������
		doActionsHandleArrange(plstActions);
		//��ʼ��Ĭ��״̬��������������ֵ
		InitialSimulateSymptoms(ePatientType);
		if( plstActions != NULL )
		{
			//��ǰ������������������
            foreach(CXActionVirtual *pVirAction, *plstActions)
			{
				//������Ӧ����������ָ��
				std::list<CSymptomVirtual *>   lstHandleSymptoms;
				if( FindSymptomByAction(&lstHandleSymptoms, pVirAction) )
				{
                    foreach(auto pPtr, lstHandleSymptoms)
					{
						pPtr->InitialSymptomValue( pVirAction);
					}
				}
				else
				{
					//�������������
					AddUnMonitorSymptom( pVirAction );
				}
			}
		}
	}

	/*******************************************************************************/
	// �������ƣ� modifyScenario
	// ���ܣ�   �޸ĵ�ǰ����״̬����������ֵ
	// ������   CList<CXActionVirtual *, CXActionVirtual *> lstActions: 
	//          eEventSign eEventValue:  ����ת�����¼��ź�
	//          BOOL bExecActions:       �Ƿ�ִ������
	//          short sTransferTime:
	// ����ֵ:  tag_TrendValue: ��ǰ���������õ�����ֵ
	void CSimulateSymptomsCollect::modifyScenarioSet(std::list<CXActionVirtual *> *plstActions, eEventSign eEventValue, bool bExecActions/*=true*/, short sTransferTime/*=0*/)
	{
		//����ǰ�����е�������������˳�������
		doActionsHandleArrange(plstActions);
		if( plstActions != NULL )
		{
			//��ǰ������������������
            foreach(auto pVirAction, *plstActions)
			{
				//������Ӧ����������ָ��
				std::list<CSymptomVirtual *>   lstHandleSymptoms;
				if( FindSymptomByAction(&lstHandleSymptoms, pVirAction) )
				{
                    foreach(CSymptomVirtual *pPtr, lstHandleSymptoms)
					{
						pPtr->InitialSymptomValue(pVirAction, sTransferTime);
					}
				}
				else
				{
					//�������������
					AddUnMonitorSymptom( pVirAction );
				}
			}
		}
		if( bExecActions )
		{
			//�޸�����ģ�����߹�����
			ModifySimulateSymptomsBuild( eEventValue );
		}
	}

	//��ӿɲ�����صĲ���������
	void CSimulateSymptomsCollect::AddUnMonitorSymptom(CXActionVirtual *pVirAction)
	{
		IModifiedSymptomsOp  *pModifiedSymptomsOp = (IModifiedSymptomsOp *)this;
		CSymptomUnmonitorVirtual  *pNewSymptom = NULL;

		std::string   strActionCaption = pVirAction->getActionCaption();
		if( pNewSymptom != NULL )
		{
			pNewSymptom->ModifyUnmonitorSymptomValue( pModifiedSymptomsOp, pVirAction);
			m_lstUnMonitorSymptoms.push_back( pNewSymptom );
			//������ʾ�ӿ�ָ��
			if( m_pWatchBarsShowAggregate != NULL )
			{
				pNewSymptom->OnLinkWatchBarUpdateInterfaceShow( m_pWatchBarsShowAggregate );
			}
		}
	}

	//��ʼ������ģ�����߹�����
	void CSimulateSymptomsCollect::initialSimulateSymptomsBuild(SimulatePatientType ePatientType)
	{
		InitialSimulateSymptomsBuild( ePatientType );
	}

	//����ǰ�����е�������������˳�������
	//ע�����������ụ��Ӱ�죬����ʱ���趨����˳��
	void CSimulateSymptomsCollect::doActionsHandleArrange(std::list<CXActionVirtual *> *plstActions)
	{
		if( plstActions != NULL )
		{
			std::list<CXActionVirtual *>  lstArrangedActions;
			//�ĵ�ͼ
			CXActionVirtual *pEcgAction = findActionByName(plstActions, CSAction_ECG::getAction_ECG_Caption());
			if( pEcgAction != NULL )
			{
				plstActions->remove( pEcgAction );
				lstArrangedActions.push_back( pEcgAction );
			}
			//����
			CXActionVirtual *pRespAction = findActionByName(plstActions, CSAction_Resp::getAction_Resp_Caption());
			if( pRespAction != NULL )
			{
				plstActions->remove( pRespAction );
				lstArrangedActions.push_back( pRespAction );
			}
			//ABP
			CXActionVirtual *pABPAction = findActionByName(plstActions, CSAction_ABP::getAction_BP_Caption());
			if( pABPAction != NULL )
			{
				plstActions->remove( pABPAction );
				lstArrangedActions.push_back( pABPAction );
			}
			//Ѫ��
			CXActionVirtual *pSpO2Action = findActionByName(plstActions, CSAction_Osat::getAction_Osat_Caption() );
			if( pSpO2Action != NULL )
			{
				plstActions->remove( pSpO2Action );
				lstArrangedActions.push_back( pSpO2Action );
			}
			//----------------------------------------------------------------------------------------------------------------
            foreach(auto pVirAction, *plstActions)
			{
				lstArrangedActions.push_back( pVirAction );
			}
			plstActions->clear();
			//------------------------------------------------------------------------------------------------------
            foreach(auto pVirAction, lstArrangedActions)
			{
				plstActions->push_back( pVirAction );
			}
		}
	}

	CXActionVirtual * CSimulateSymptomsCollect::findActionByName(std::list<CXActionVirtual *> *ptrlstActions, const std::string &strActionName)
	{
        foreach(auto pVirAction, *ptrlstActions)
		{
			if( pVirAction->isActionNameOf(strActionName) )
			{
				return pVirAction;
			}
		}
		return NULL;
	}

	/*******************************************************************************/
	// �������ƣ� StartLinkeSimulateBarShowInterfaces
	// ���ܣ� ��ʼ����ģ��ģ�����������������ʾ�ӿ�
	// ������ CSymptomsShowInterfacesAggregate *pShowAggregate:        
	// ����ֵ:  
	void CSimulateSymptomsCollect::StartLinkeSimulateBarShowInterfaces(CSymptomsShowInterfacesAggregate *pShowAggregate)
	{
		std::list<CSymptomVirtual *>    lstSymptoms;
		//�������е���������ָ��
		SearchAllSymptoms( /*out*/&lstSymptoms );
		m_cUpdateMutex.Lock();
        foreach(auto pVirSymptom, lstSymptoms)
		{
			pVirSymptom->OnLinkSimulatorBarUpdateInterfaceShow( pShowAggregate );
		}
		m_cUpdateMutex.Unlock();
	}

	/*******************************************************************************/
	// �������ƣ� UnLinkSimulateBarShowInterfaces
	// ���ܣ� �Ͽ�ģ��ģ�����������������ʾ�ӿ�
	// ������ CSimulatorSymptomShowInterfacesAggregate *pShowAggregate:        
	// ����ֵ:
	void CSimulateSymptomsCollect::UnLinkSimulateBarShowInterfaces(CSymptomsShowInterfacesAggregate *pShowAggregate)
	{
		std::list<CSymptomVirtual *>    lstSymptoms;
		//�������е���������ָ��
		SearchAllSymptoms( /*out*/&lstSymptoms );
		m_cUpdateMutex.Lock();
        foreach(auto pVirSymptom, lstSymptoms)
		{
			pVirSymptom->OnUnLinkSimulatorBarUpdateInterfaceShow( pShowAggregate );
		}
		m_cUpdateMutex.Unlock();
	}

	/*******************************************************************************/
	//���ܣ�����ʱ���¼�IRP����
	//������
	//      CVirtualIrp *pCurrIrp��
	//����ֵ:  �������ٴ���FALSE);
	bool CSimulateSymptomsCollect::doHandleClockIrpOp(CVirtualIrp *pCurrIrp)
	{
	#ifdef  _DEBUG
		BOOST_ASSERT( pCurrIrp->isKindOf("CEventIrp_ClockTime") );
	#endif
		CEventIrp_ClockTime  *pClockEventIrp = (CEventIrp_ClockTime *)pCurrIrp;
		//���������ʱ��
		CSymptom_FrameTime   *pFrameTime = GetFrameTimeSymptomPtr();
		pFrameTime->IncreaseFrameTime( (long)pClockEventIrp->GetValue_ClockEvent() );
		return true;
	}

	/*******************************************************************************/
	//���ܣ��������¼�IRP����
	//������
	//      CVirtualIrp *pCurrIrp��
	//����ֵ:  �������ٴ���FALSE);
	bool CSimulateSymptomsCollect::doHandleCustomEventIrpOp(CVirtualIrp *pCurrIrp)
	{
		if( pCurrIrp->isKindOf( "CEventIrp_SimulateTrigger" ) )
		{
			CEventIrp_SimulateTrigger *pTriggerEventIrp = (CEventIrp_SimulateTrigger *)pCurrIrp;
			if( pTriggerEventIrp->m_strTriggerEventName == CSEvent_Defibr::getEvent_Defibr_Caption() )
			{
				base::COpECGBuildInterface *pEcgBuildInterface = m_cEcg.GetECGBuildInterface();
				if( pEcgBuildInterface != NULL )
				{
					pEcgBuildInterface->OnModifyECGInDefibrEventHandle( NULL );
				}
			}
			else if( pTriggerEventIrp->Get_EventSign() == ES_Intubation )
			{
				if( pTriggerEventIrp->getName_TriggerEvent() == CSEvent_Intubate::getEvent_Intubate_Caption() )
				{
					//�����Ϣ
					short   sAct, sPosition;
					if( pTriggerEventIrp->explainSimulateTrigger_IntubateEventIrp(/*out*/sPosition, /*out*/sAct) )
					{
						base::COpEtCO2BuildInterface  *pEtCO2BuildInterface = m_cEtCO2.GetEtCO2BuildInterface();
						if( pEtCO2BuildInterface != NULL )
						{
							bool   bIntubate = false;
							if( sAct == 0x11 && sPosition == 0x02 )
							{
								bIntubate = true;
							}
							pEtCO2BuildInterface->OnIntubateEventOp( bIntubate );
						}
					}
				}
			}
		}
		return true;
	}

	/*******************************************************************************/
	//���ܣ�����CPR����ͳ�ƽ��IRP����
	//������
	//      CVirtualIrp *pCurrIrp��
	//����ֵ:  �������ٴ���FALSE);
	bool CSimulateSymptomsCollect::doHandleCPRStatIrpOp(irp::CVirtualIrp *pCurrIrp)
	{
		if( pCurrIrp->isKindOf( "CCPRStatIrp" ) )
		{
			base::COpEtCO2BuildInterface  *pEtCO2BuildInterface = m_cEtCO2.GetEtCO2BuildInterface();
			if( pEtCO2BuildInterface != NULL )
			{
				CCPRStatIrp  *pCPRStatIrp = (CCPRStatIrp *)pCurrIrp;
				if( pCPRStatIrp->GetValue_Stat() == 0 )
				{
					//CPR��������
					pEtCO2BuildInterface->OnCPREventOp( true );
				}
				else if( pCPRStatIrp->GetValue_Stat() == 1 )
				{
					//CPR������ʼ
					pEtCO2BuildInterface->OnCPREventOp( false );
				}
			}
		}
		return true;
	}

	/*******************************************************************************/
	//���ܣ���������ת��IRP����
	//������
	//      CVirtualIrp *pCurrIrp��
	//����ֵ:  �������ٴ���FALSE);
	bool CSimulateSymptomsCollect::doHandleRealTimeDataIrpOp(irp::CVirtualIrp *pCurrIrp)
	{
	//#ifdef  _DEBUG
	//	if( !pCurrIrp->isKindOf( "CRealTimeDataIrp" ) )
	//		BOOST_ASSERT( 0 );
	//#endif
		if( pCurrIrp->isKindOf( "CRealTimeDataIrp" ) )
		{
			CRealTimeDataIrp *pRealTimeDataIrp = (CRealTimeDataIrp *)pCurrIrp;
			const cpr::CParseCPRData_Singleton &cCPRParse = cpr::CParseCPRData_Singleton::get_const_instance();
			for (int nIndex = 0; nIndex < pRealTimeDataIrp->m_nLength; ++nIndex)
			{
				//�жϴ�������
				_CPRData *lptrData = &pRealTimeDataIrp->m_ptrCPRDatas[nIndex];
				if( cCPRParse.isCPRScopeOrder(*lptrData, false) )
				{
					base::COpEtCO2BuildInterface  *pEtCO2BuildInterface = m_cEtCO2.GetEtCO2BuildInterface();
					if( pEtCO2BuildInterface != NULL )
					{
						pEtCO2BuildInterface->OnOnceBreathEventOp();
					}
					break;
				}
			}
		}
		return true;
	}

	/*******************************************************************************/
	// �������ƣ� TransmitSimulatorOrders
	// ���ܣ� ����ģ��������ͨ��ָ��
	// ������ ITransportOrderIrpToSimulator *pInterface:        
	// ����ֵ:
	void CSimulateSymptomsCollect::TransmitSimulatorOrders()
	{
		if( m_pTransportOrderInterface != NULL )
		{
			//���������޸ĵ�ģ��������ͨ��ָ��
			std::list<CSymptomVirtual *>   lstTmpmodifiedSymptoms;
			m_cMutex.Lock();
			std::copy(modifiedSymptoms.begin(), modifiedSymptoms.end(), std::back_inserter(lstTmpmodifiedSymptoms));
			m_cMutex.Unlock();
			bool  bTransAED = false;
            foreach(auto pVirSymptom, lstTmpmodifiedSymptoms)
			{
				if( !bTransAED && pVirSymptom->isTransmitAEDState( NULL ) )
				{
					bTransAED = true;
				}
				pVirSymptom->DoTransmitOrder( &m_cSyncPnPFacilities, m_pTransportOrderInterface);
			}
			//AED״ָ̬�����
			if( bTransAED == true )
			{
				irp::CSimulatorOrderIrp *pAEDOrderIrp = translateAEDOrderIrp();
				m_pTransportOrderInterface->OnTransportDownOrderToSimulater( pAEDOrderIrp );
			}
		}
	}

	/*******************************************************************************/
	// �������ƣ� ModifiedSymptomsUpdateShow
	// ���ܣ� ���޸ĵĲ���������ʾ
	// ������ 
	//        BOOL bClearModifiedFlag:      �Ƿ�����޸ı�ʶ   
	// ����ֵ:
	void CSimulateSymptomsCollect::ModifiedSymptomsUpdateShow( bool bClearModifiedFlag )
	{
		m_cUpdateMutex.Lock();
        foreach(auto pVirSymptom, modifiedSymptoms)
		{
			pVirSymptom->OnUpdateInterfaceShow();
		}
		//������޸������ı�ʶ
		if( bClearModifiedFlag )
		{
			emptyModifiedSymptomsFlag();
		}
		m_cUpdateMutex.Unlock();
	}

	//��ȡ�޸ĵ���������
	void CSimulateSymptomsCollect::getsynchronizeSymptoms(std::list<CSymptomVirtual *> /*out*/*plstModifiedSymptoms, bool bInitial)
	{
		if( bInitial == TRUE )
		{
			//�������е���������ָ��
			SearchAllSymptoms( /*out*/plstModifiedSymptoms );
		}
		else
		{
			m_cMutex.Lock();
            foreach(auto pVirSymptom, modifiedSymptoms)
			{
				plstModifiedSymptoms->push_back( pVirSymptom );
			}
			m_cMutex.Unlock();
		}
	}
}}
