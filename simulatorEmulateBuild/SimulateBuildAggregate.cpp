#include ".\simulatebuildaggregate.h"

#include "..\Common\ECGParams.h"

#include "..\SimulatorBase\ShowECGUpdateInterface.h"
#include "..\SimulatorBase\ShowSpO2UpdateInterface.h"
#include "..\SimulatorBase\ShowABPUpdateInterface.h"
#include "..\SimulatorBase\ShowEtCO2UpdateInterface.h"
#include "..\SimulatorBase\ShowRespRateUpdateInterface.h"
#include "..\SimulatorBase\WatchBarsShowInterfacesAggregate.h"


using namespace jysoft::utility;
using namespace jysoft::transLayer;
using namespace jysoft::simulator::base;
namespace jysoft { namespace simulator {

	CSimulateBuildAggregate::CSimulateBuildAggregate()
	{
		//设置心电图模拟器接口
		m_pOpECGBuildInterface  = dynamic_cast<COpECGBuildInterface *>(&m_cECGBuild);
		//血氧模拟器接口
		m_pOpSpO2BuildInterface = dynamic_cast<COpSpO2BuildInterface *>(&m_cSpO2Build);
		//呼出二氧化碳浓度分压模拟器接口
		m_pEtCO2BuildInterface  = dynamic_cast<COpEtCO2BuildInterface *>(&m_cEtCO2Build);
		//呼吸模拟器接口
		m_pRespBuildInterface   = dynamic_cast<COpRespBuildInterface *>(&m_cRespBuild);
		//有创血压模拟器接口
		m_pABPBuildInterface    = dynamic_cast<COpABPBuildInterface *>(&m_cABPBuild);

		//设置接口关系
		IPaneMoveControlInterface  *pSpO2PaneMove = dynamic_cast<IPaneMoveControlInterface *>(&m_cSpO2SimulateCanvas);
		IPaneMoveControlInterface  *pABPPaneMove  = dynamic_cast<IPaneMoveControlInterface *>(&m_cABPSimulateCanvas);
		pSpO2PaneMove->SetNextInterfacePtr( pABPPaneMove );
	}

	CSimulateBuildAggregate::~CSimulateBuildAggregate(void)
	{
	}

	/*******************************************************************************/
	// 函数名称： InitialPhysBuildsRelationAndResource
	// 功能： 初始化体征构造器相关的指针设定及加载资源
	// 参数：
	//        
	// 返回值:  
	void CSimulateBuildAggregate::InitialPhysBuildsRelationAndResources(const std::string &resPath, transLayer::ITransportOrderIrpToSimulator *pTransportOrderIrp/*=NULL*/, SimulatePatientType ePatientType/*=SPT_Adult*/)
	{
		resourcePath = resPath;
		IPhysiologyStartSign  *pStartSignInterface = &m_cSpO2Build;
		IBedirecteLinksVir    *pABPStartSign  = dynamic_cast<IPhysiologyStartSign *>(&m_cABPBuild);
		pStartSignInterface->SetNextInterfacePtr(pABPStartSign);
		//心电图构造器
		m_cECGBuild.SetEcgBuildRelateInterfacesPtr(pStartSignInterface, resPath, pTransportOrderIrp, ePatientType);
		//呼吸模拟器
		m_cRespBuild.SetRespBuildRelateInterfacesPtr(&m_cEtCO2Build, resPath, pTransportOrderIrp, ePatientType);
		//---------------------------------------------------------------------------------------
		m_cEtCO2Build.setResouceFilePath( resPath );
		m_cSpO2Build.initialSpO2Sample( resPath );
		m_cABPBuild.initialABPSample( resPath );
	}

	//初始化生理体征模拟器
	void CSimulateBuildAggregate::InitialPhysBuilds()
	{
		//初始化心电图
		CECGParams   cEcgParams;
		cEcgParams.m_dwField = PM_QRS|PM_BASICRHYTHM|PM_HR;
		m_cECGBuild.InitializeBuild(cEcgParams);
		//呼出二氧化碳浓度分压模拟器
		m_cEtCO2Build.InitializeBuild( 40 );
		//呼吸模拟器
		m_cRespBuild.InitializeBuild(RM_Normal, 12);
	}

	//关闭生理体征模拟器
	void CSimulateBuildAggregate::ClosePhysBuilds()
	{
		//心电图模拟器
		if( m_cECGBuild.IsInitialCardiogramBuild() )
		{
			m_cECGBuild.CloseCardiogramBuild();
		}
		//关闭血氧模拟器
		m_cSpO2Build.CloseSpO2SimulateBuild();
		//呼吸模拟器
		m_cRespBuild.CloseRespSimulateBuild();
		//关闭ABP模拟器
		m_cABPBuild.CloseABPSimulateBuild();
	}

	/*******************************************************************************/
	// 函数名称： StartSimulateBuild
	// 功能： 启动模拟数据的生成，并带动SpO2及ABP实时数据
	// 参数：
	//        CWnd  *pHootWnd: 
	// 返回值:  
	void CSimulateBuildAggregate::StartSimulateBuild()
	{
		IGetPhysioloySimulateData *pGetSpO2Data = m_cSpO2Build.Get_IGetPhysioloySimulateDataPtr();
		m_cSpO2SimulateCanvas.InitialSimulate(pGetSpO2Data);

		IGetPhysioloySimulateData *pGetABPData  = m_cABPBuild.Get_IGetPhysioloySimulateDataPtr();
		m_cABPSimulateCanvas.InitialSimulate( pGetABPData );

		IGetEcgSimulateData *pGetEcgData = m_cECGBuild.getIGetEcgLeadSimulateDataPtr();
		IPaneMoveControlInterface  *pSpO2PaneMovePtr = dynamic_cast<IPaneMoveControlInterface *>(&m_cSpO2SimulateCanvas);
		m_cEcgSimulateCanvas.InitialEcgSimulate( pGetEcgData, pSpO2PaneMovePtr, resourcePath);
		m_cEcgSimulateCanvas.StartDistributeSimulateData();
	
		//启动呼吸实时数据的生成，并带动etCO2实时数据
		IGetPhysioloySimulateData *pGetEtCO2Data = m_cEtCO2Build.Get_IGetPhysioloySimulateDataPtr();
		m_cEtCO2SimulateCanvas.InitialSimulate(pGetEtCO2Data, 800);

		IGetRespSimulateData   *pGetRespData  = m_cRespBuild.Get_IGetPhysioloySimulateDataPtr();
		m_cRespSimulateCanvas.InitialRespSimulate(pGetRespData, &m_cEtCO2SimulateCanvas);
		m_cRespSimulateCanvas.StartDistributeSimulateData();
	}

	//停止模拟数据的实时生成
	void CSimulateBuildAggregate::StopSimulateBuilds()
	{
		//停止心电图数据的生成
		m_cEcgSimulateCanvas.StopDistributeSimulateData();
		//停止呼吸数据的生成
		m_cRespSimulateCanvas.StopDistributeSimulateData();
	}

	/*******************************************************************************/
	// 函数名称： OnWatchECGHandle
	// 功能： 启动/断开心电图的监视
	// 参数：
	//        IDistributeEcgLeadsSimulateData  *pDistributeECGInterface: 数据派发接口
	//        CShowECGUpdateInterface *pInterface:
	//        BOOL bCutWatch:
	// 返回值:  
	void CSimulateBuildAggregate::OnWatchECGHandle(IDistributeEcgLeadsSimulateData  *pDistributeECGInterface, base::CShowECGUpdateInterface *pInterface, bool bCutWatch)
	{
		if( bCutWatch )
		{
			m_cEcgSimulateCanvas.OnCutWatchEcg( pDistributeECGInterface );
		}
		else
		{
			m_cEcgSimulateCanvas.OnStartWatchEcg( pDistributeECGInterface );
			if( pInterface != NULL )
			{
				//是否显示心律波形
				if( !m_cECGBuild.IsShowEcgByLinkState() )
				{
					pInterface->OnAllUnLinkUpdateShow();
				}
				else
				{
					pInterface->OnAllLinkUpdateShow();
				}
			}
		}
	}

	/*******************************************************************************/
	// 函数名称： OnWatchSpO2Handle
	// 功能： 启动/断开SpO2的监视
	// 参数：
	//        IDistributeSimulateData  *pDistributeInterface: 数据派发接口
	//        BOOL bCutWatch:
	// 返回值:  
	void CSimulateBuildAggregate::OnWatchSpO2Handle(IDistributeSimulateData  *pDistributeInterface, CShowSpO2UpdateInterface *pInterface, bool bCutWatch)
	{
		if( bCutWatch )
		{
			m_cSpO2SimulateCanvas.OnCutWatchPhyst( pDistributeInterface );
		}
		else
		{
			m_cSpO2SimulateCanvas.OnStartWatchPhyst( pDistributeInterface );
			if( pInterface != NULL )
			{
				//是否显示SpO2波形
				if( !m_cSpO2Build.IsShowSpO2yLinkState() )
				{
					pInterface->OnAllUnLinkUpdateShow();
				}
				else
				{
					pInterface->OnAllLinkUpdateShow();
				}
			}
		}
	}

	/*******************************************************************************/
	// 函数名称： OnWatchRespHandle
	// 功能： 启动/断开呼吸的监视
	// 参数：
	//        IDistributeSimulateData  *pDistributeInterface: 数据派发接口
	//        BOOL bCutWatch:
	// 返回值: 
	void CSimulateBuildAggregate::OnWatchRespHandle(IDistributeRespSimulateData *pDistributeInterface, CShowRespRateUpdateInterface *pInterface, bool bCutWatch)
	{
		if( bCutWatch )
		{
			m_cRespSimulateCanvas.OnCutWatchResp( pDistributeInterface );
		}
		else
		{
			m_cRespSimulateCanvas.OnStartWatchResp( pDistributeInterface );
			if( pInterface != NULL )
			{
				//是否显示Resp波形
				if( !m_cRespBuild.IsShowRespLinkState() )
				{
					pInterface->OnAllUnLinkUpdateShow();
				}
				else
				{
					pInterface->OnAllLinkUpdateShow();
				}
			}
		}
	}

	/*******************************************************************************/
	// 函数名称： OnWatchABPHandle
	// 功能： 启动/断开ABP的监视
	// 参数：
	//        IDistributeSimulateData  *pDistributeInterface: 数据派发接口
	//        CShowABPUpdateInterface *pInterface
	//        BOOL bCutWatch:
	// 返回值:  
	void CSimulateBuildAggregate::OnWatchABPHandle(IDistributeSimulateData  *pDistributeInterface, CShowABPUpdateInterface *pInterface, bool bCutWatch)
	{
		if( bCutWatch )
		{
			m_cABPSimulateCanvas.OnCutWatchPhyst( pDistributeInterface );
		}
		else
		{
			m_cABPSimulateCanvas.OnStartWatchPhyst( pDistributeInterface );
			if( pInterface != NULL )
			{
				//是否显示ABP波形
				if( !m_cABPBuild.IsShowABPLinkState() )
				{
					pInterface->OnAllUnLinkUpdateShow();
				}
				else
				{
					pInterface->OnAllLinkUpdateShow();
				}
			}
		}
	}

	/*******************************************************************************/
	// 函数名称： OnWatchEtCO2Handle
	// 功能： 启动/断开呼吸的监视
	// 参数：
	//        IDistributeSimulateData  *pDistributeInterface: 数据派发接口
	//        BOOL bCutWatch:
	// 返回值: 
	void CSimulateBuildAggregate::OnWatchEtCO2Handle(IDistributeSimulateData *pDistributeInterface, CShowEtCO2UpdateInterface *pInterface, bool bCutWatch)
	{
		if( bCutWatch )
		{
			m_cEtCO2SimulateCanvas.OnCutWatchPhyst( pDistributeInterface );
		}
		else
		{
			m_cEtCO2SimulateCanvas.OnStartWatchPhyst( pDistributeInterface );
			if( pInterface != NULL )
			{
				//是否显示EtCO2波形
				if( !m_cEtCO2Build.IsShowEtCO2LinkState() )
				{
					pInterface->OnAllUnLinkUpdateShow();
				}
				else
				{
					pInterface->OnAllLinkUpdateShow();
				}
			}
		}
	}

	//设置是否忽略心电链接检查
	void CSimulateBuildAggregate::Set_IsClearEcgWatchLink(bool bClear)
	{
		m_cECGBuild.Set_IsClearEcgWatchLink( bClear );
	}

	//设置心电链接检查状态
	void CSimulateBuildAggregate::Set_EcgWatchLinkState(bool bLinking)
	{
		m_cECGBuild.Set_EcgWatchLinkState( bLinking );
	}

	bool CSimulateBuildAggregate::Get_IsEcgWatchLink()
	{
		return m_cECGBuild.IsShowEcgByLinkState();
	}

	//设置是否忽略SpO2链接检查
	void CSimulateBuildAggregate::Set_IsClearSpO2WatchLink(bool bClear)
	{
		m_cSpO2Build.Set_IsClearSpO2WatchLink( bClear );
	}

	//设置SpO2链接检查状态
	void CSimulateBuildAggregate::Set_SpO2WatchLinkState(bool bLinking)
	{
		m_cSpO2Build.Set_SpO2WatchLinkState( bLinking );
	}

	bool CSimulateBuildAggregate::Get_IsSpO2WatchLink()
	{
		return m_cSpO2Build.IsShowSpO2yLinkState();
	}

	//设置是否忽略ABP链接检查
	void CSimulateBuildAggregate::Set_IsClearABPWatchLink(bool bClear)
	{
		m_cABPBuild.Set_IsClearABPWatchLink( bClear );
	}

	//设置ABP链接检查状态
	void CSimulateBuildAggregate::Set_ABPWatchLinkState(bool bLinking)
	{
		m_cABPBuild.Set_ABPWatchLinkState( bLinking );
	}

	//设置是否忽略EtCO2链接检查
	void CSimulateBuildAggregate::Set_IsClearEtCO2WatchLink(bool bClear)
	{
		m_cEtCO2Build.Set_IsClearEtCO2WatchLink( bClear );
	}
	//设置EtCO2链接检查状态
	void CSimulateBuildAggregate::Set_EtCO2WatchLinkState(bool bLinking)
	{
		m_cEtCO2Build.Set_EtCO2WatchLinkState( bLinking );
	}

	//设置是否忽略Resp链接检查
	void CSimulateBuildAggregate::Set_IsClearRespWatchLink(bool bClear)
	{
		m_cRespBuild.Set_IsClearRespWatchLink( bClear );
	}

	//设置Resp链接检查状态
	void CSimulateBuildAggregate::Set_RespWatchLinkState(bool bLinking)
	{
		m_cRespBuild.Set_RespWatchLinkState( bLinking );
	}

	/*******************************************************************************/
	// 函数名称： StartLinkWatchBarsShowInterfaces
	// 功能： 初始连接模拟监控面板的显示接口
	// 参数： CWatchBarsShowInterfacesAggregate *pShowAggregate:        
	// 返回值:  
	void CSimulateBuildAggregate::StartLinkWatchBarsShowInterfaces(CWatchBarsShowInterfacesAggregate *pShowAggregate)
	{
		COpPhysBuildInterfacesAggregate::StartLinkWatchBarsShowInterfaces( pShowAggregate );
		//填加模拟监控面板“嘀嘀”音提示启动信号
		m_cECGBuild.InsertHeartStartSignPtr( pShowAggregate->Get_HeartStartSignInterface() );
	}

	/*******************************************************************************/
	// 函数名称： UnLinkWatchBarsShowInterfaces
	// 功能： 断开模拟监控面板的显示接口
	// 参数： CWatchBarsShowInterfacesAggregate *pShowAggregate:        
	// 返回值:  
	void CSimulateBuildAggregate::UnLinkWatchBarsShowInterfaces(CWatchBarsShowInterfacesAggregate *pShowAggregate)
	{
		COpPhysBuildInterfacesAggregate::UnLinkWatchBarsShowInterfaces( pShowAggregate );
		//移除模拟监控面板“嘀嘀”音提示启动信号
		m_cECGBuild.RemoveHeartStartSignPtr( pShowAggregate->Get_HeartStartSignInterface() );
	}

	//按压开始\结束(TRUE:开始；FALSE:结束)
	void CSimulateBuildAggregate::PressureStateAct(bool bState)
	{
		m_cEcgSimulateCanvas.SetPressureActState( bState );
	}

	//结束CPR操作
	void CSimulateBuildAggregate::FinishCPROperator(bool bSecceed)
	{
		//结束按压
		PressureStateAct( false );
	}
}}
