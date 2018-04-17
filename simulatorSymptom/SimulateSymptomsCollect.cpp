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

	//搜索对应的体征对象指针
	bool CSimulateSymptomsCollect::FindSymptomByAction(std::list<CSymptomVirtual *>* /*out*/plstFindSymptoms, CXActionVirtual* /*in*/pVirAction)
	{
		return CVirSimulateSymptomsCollect::FindSymptomByAction(plstFindSymptoms, pVirAction->getActionCaption());
	}

	/*******************************************************************************/
	// 函数名称： initialScenarioSet
	// 功能：   生理体征初始化为当前场景状态
	// 参数：   std::list<CXActionVirtual *> *plstActions: 
	//          SimulatePatientType ePatientType: 模拟人类型
	// 返回值:  tag_TrendValue: 当前场景所设置的体征值
	void CSimulateSymptomsCollect::initialScenarioSet(std::list<CXActionVirtual *> *plstActions, SimulatePatientType ePatientType)
	{
		//处理当前场景中的生理体征处理顺序的排列
		doActionsHandleArrange(plstActions);
		//初始化默认状态的生理体征参数值
		InitialSimulateSymptoms(ePatientType);
		if( plstActions != NULL )
		{
			//当前场景的生理体征设置
            foreach(CXActionVirtual *pVirAction, *plstActions)
			{
				//搜索对应的体征对象指针
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
					//添加新体征参数
					AddUnMonitorSymptom( pVirAction );
				}
			}
		}
	}

	/*******************************************************************************/
	// 函数名称： modifyScenario
	// 功能：   修改当前场景状态的生理体征值
	// 参数：   CList<CXActionVirtual *, CXActionVirtual *> lstActions: 
	//          eEventSign eEventValue:  场景转换的事件信号
	//          BOOL bExecActions:       是否执行体征
	//          short sTransferTime:
	// 返回值:  tag_TrendValue: 当前场景所设置的体征值
	void CSimulateSymptomsCollect::modifyScenarioSet(std::list<CXActionVirtual *> *plstActions, eEventSign eEventValue, bool bExecActions/*=true*/, short sTransferTime/*=0*/)
	{
		//处理当前场景中的生理体征处理顺序的排列
		doActionsHandleArrange(plstActions);
		if( plstActions != NULL )
		{
			//当前场景的生理体征设置
            foreach(auto pVirAction, *plstActions)
			{
				//搜索对应的体征对象指针
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
					//添加新体征参数
					AddUnMonitorSymptom( pVirAction );
				}
			}
		}
		if( bExecActions )
		{
			//修改体征模拟曲线构造器
			ModifySimulateSymptomsBuild( eEventValue );
		}
	}

	//添加可不被监控的参数的体征
	void CSimulateSymptomsCollect::AddUnMonitorSymptom(CXActionVirtual *pVirAction)
	{
		IModifiedSymptomsOp  *pModifiedSymptomsOp = (IModifiedSymptomsOp *)this;
		CSymptomUnmonitorVirtual  *pNewSymptom = NULL;

		std::string   strActionCaption = pVirAction->getActionCaption();
		if( pNewSymptom != NULL )
		{
			pNewSymptom->ModifyUnmonitorSymptomValue( pModifiedSymptomsOp, pVirAction);
			m_lstUnMonitorSymptoms.push_back( pNewSymptom );
			//设置显示接口指针
			if( m_pWatchBarsShowAggregate != NULL )
			{
				pNewSymptom->OnLinkWatchBarUpdateInterfaceShow( m_pWatchBarsShowAggregate );
			}
		}
	}

	//初始化体征模拟曲线构造器
	void CSimulateSymptomsCollect::initialSimulateSymptomsBuild(SimulatePatientType ePatientType)
	{
		InitialSimulateSymptomsBuild( ePatientType );
	}

	//处理当前场景中的生理体征处理顺序的排列
	//注：体针参数间会互相影响，处理时先设定处理顺序
	void CSimulateSymptomsCollect::doActionsHandleArrange(std::list<CXActionVirtual *> *plstActions)
	{
		if( plstActions != NULL )
		{
			std::list<CXActionVirtual *>  lstArrangedActions;
			//心电图
			CXActionVirtual *pEcgAction = findActionByName(plstActions, CSAction_ECG::getAction_ECG_Caption());
			if( pEcgAction != NULL )
			{
				plstActions->remove( pEcgAction );
				lstArrangedActions.push_back( pEcgAction );
			}
			//呼吸
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
			//血氧
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
	// 函数名称： StartLinkeSimulateBarShowInterfaces
	// 功能： 初始连接模拟模拟人设置面板的相关显示接口
	// 参数： CSymptomsShowInterfacesAggregate *pShowAggregate:        
	// 返回值:  
	void CSimulateSymptomsCollect::StartLinkeSimulateBarShowInterfaces(CSymptomsShowInterfacesAggregate *pShowAggregate)
	{
		std::list<CSymptomVirtual *>    lstSymptoms;
		//搜索所有的体征对象指针
		SearchAllSymptoms( /*out*/&lstSymptoms );
		m_cUpdateMutex.Lock();
        foreach(auto pVirSymptom, lstSymptoms)
		{
			pVirSymptom->OnLinkSimulatorBarUpdateInterfaceShow( pShowAggregate );
		}
		m_cUpdateMutex.Unlock();
	}

	/*******************************************************************************/
	// 函数名称： UnLinkSimulateBarShowInterfaces
	// 功能： 断开模拟模拟人设置面板的相关显示接口
	// 参数： CSimulatorSymptomShowInterfacesAggregate *pShowAggregate:        
	// 返回值:
	void CSimulateSymptomsCollect::UnLinkSimulateBarShowInterfaces(CSymptomsShowInterfacesAggregate *pShowAggregate)
	{
		std::list<CSymptomVirtual *>    lstSymptoms;
		//搜索所有的体征对象指针
		SearchAllSymptoms( /*out*/&lstSymptoms );
		m_cUpdateMutex.Lock();
        foreach(auto pVirSymptom, lstSymptoms)
		{
			pVirSymptom->OnUnLinkSimulatorBarUpdateInterfaceShow( pShowAggregate );
		}
		m_cUpdateMutex.Unlock();
	}

	/*******************************************************************************/
	//功能：处理时钟事件IRP函数
	//参数：
	//      CVirtualIrp *pCurrIrp：
	//返回值:  后续不再处理（FALSE);
	bool CSimulateSymptomsCollect::doHandleClockIrpOp(CVirtualIrp *pCurrIrp)
	{
	#ifdef  _DEBUG
		BOOST_ASSERT( pCurrIrp->isKindOf("CEventIrp_ClockTime") );
	#endif
		CEventIrp_ClockTime  *pClockEventIrp = (CEventIrp_ClockTime *)pCurrIrp;
		//场景框持续时间
		CSymptom_FrameTime   *pFrameTime = GetFrameTimeSymptomPtr();
		pFrameTime->IncreaseFrameTime( (long)pClockEventIrp->GetValue_ClockEvent() );
		return true;
	}

	/*******************************************************************************/
	//功能：处理场景事件IRP函数
	//参数：
	//      CVirtualIrp *pCurrIrp：
	//返回值:  后续不再处理（FALSE);
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
					//插管信息
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
	//功能：处理CPR操作统计结果IRP函数
	//参数：
	//      CVirtualIrp *pCurrIrp：
	//返回值:  后续不再处理（FALSE);
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
					//CPR操作结束
					pEtCO2BuildInterface->OnCPREventOp( true );
				}
				else if( pCPRStatIrp->GetValue_Stat() == 1 )
				{
					//CPR操作开始
					pEtCO2BuildInterface->OnCPREventOp( false );
				}
			}
		}
		return true;
	}

	/*******************************************************************************/
	//功能：处理场景框转移IRP函数
	//参数：
	//      CVirtualIrp *pCurrIrp：
	//返回值:  后续不再处理（FALSE);
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
				//判断吹气幅度
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
	// 函数名称： TransmitSimulatorOrders
	// 功能： 传输模拟人体征通信指令
	// 参数： ITransportOrderIrpToSimulator *pInterface:        
	// 返回值:
	void CSimulateSymptomsCollect::TransmitSimulatorOrders()
	{
		if( m_pTransportOrderInterface != NULL )
		{
			//传输所有修改的模拟人体征通信指令
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
			//AED状态指令更新
			if( bTransAED == true )
			{
				irp::CSimulatorOrderIrp *pAEDOrderIrp = translateAEDOrderIrp();
				m_pTransportOrderInterface->OnTransportDownOrderToSimulater( pAEDOrderIrp );
			}
		}
	}

	/*******************************************************************************/
	// 函数名称： ModifiedSymptomsUpdateShow
	// 功能： 被修改的参数更新显示
	// 参数： 
	//        BOOL bClearModifiedFlag:      是否清除修改标识   
	// 返回值:
	void CSimulateSymptomsCollect::ModifiedSymptomsUpdateShow( bool bClearModifiedFlag )
	{
		m_cUpdateMutex.Lock();
        foreach(auto pVirSymptom, modifiedSymptoms)
		{
			pVirSymptom->OnUpdateInterfaceShow();
		}
		//清除被修改体征的标识
		if( bClearModifiedFlag )
		{
			emptyModifiedSymptomsFlag();
		}
		m_cUpdateMutex.Unlock();
	}

	//获取修改的生理体征
	void CSimulateSymptomsCollect::getsynchronizeSymptoms(std::list<CSymptomVirtual *> /*out*/*plstModifiedSymptoms, bool bInitial)
	{
		if( bInitial == TRUE )
		{
			//搜索所有的体征对象指针
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
