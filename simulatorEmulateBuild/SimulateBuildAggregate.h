#pragma once
#include ".\simulatoremulatebuild_global.h"

#include ".\CardiogramBuild.h"
#include ".\SpO2SampleDataBuild.h"
#include ".\RespSimulateBuild.h"
#include ".\CO2SimulateBuild.h"
#include ".\ECGSimulateCanvas.h"
#include ".\RespSimulateCanvas.h"
#include ".\ABPSimulateBuild.h"
#include ".\GeneralSimulateControledCanvas.h"

#include "..\SimulatorBase\ShowCPRActUpdateInterface.h"
#include "..\SimulatorBase\OpPhysBuildInterfacesAggregate.h"


namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     体征模拟器集合类
	创建人：	 hjg
	创建时间：   2017/2/18
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATOREMULATEBUILDSHARED_EXPORT CSimulateBuildAggregate : public COpPhysBuildInterfacesAggregate
												, public cpr::CShowCPRActUpdateInterface
	{
	public:
		CSimulateBuildAggregate( );
		virtual ~CSimulateBuildAggregate(void);
	protected:
		ecg::CCardiogramBuild                  m_cECGBuild;        //心电图模拟器
		SpO2::CSpO2SampleDataBuild             m_cSpO2Build;       //血氧模拟器
		resp::CRespSimulateBuild               m_cRespBuild;       //呼吸模拟器
		etCO2::CCO2SimulateBuild               m_cEtCO2Build;      //呼出二氧化碳浓度分压模拟器
		bp::CABPSimulateBuild                  m_cABPBuild;        //有创血压模拟器
	protected:  
		ecg::CECGSimulateCanvas                 m_cEcgSimulateCanvas;
		CRespSimulateCanvas                m_cRespSimulateCanvas;
		CGeneralSimulateControledCanvas    m_cSpO2SimulateCanvas;
		CGeneralSimulateControledCanvas    m_cABPSimulateCanvas;
		CGeneralSimulateControledCanvas    m_cEtCO2SimulateCanvas;
	private:
		std::string      resourcePath;
	public://基类COpPhysBuildInterfacesAggregate重载
		//初始化生理体征模拟器
		virtual void InitialPhysBuilds();
		//关闭生理体征模拟器
		virtual void ClosePhysBuilds();
		/*******************************************************************************/
		// 函数名称： OnWatchECGHandle
		// 功能： 启动/断开心电图的监视
		// 参数：
		//        IDistributeEcgLeadsSimulateData  *pDistributeECGInterface: 数据派发接口
		//        BOOL bCutWatch:
		// 返回值:  
		virtual void OnWatchECGHandle(IDistributeEcgLeadsSimulateData  *pDistributeECGInterface, base::CShowECGUpdateInterface *pInterface, bool bCutWatch);
		/*******************************************************************************/
		// 函数名称： OnWatchSpO2Handle
		// 功能： 启动/断开SpO2的监视
		// 参数：
		//        IDistributeSimulateData  *pDistributeInterface: 数据派发接口
		//        BOOL bCutWatch:
		// 返回值:  
		virtual void OnWatchSpO2Handle(IDistributeSimulateData  *pDistributeInterface, base::CShowSpO2UpdateInterface *pInterface, bool bCutWatch);
		/*******************************************************************************/
		// 函数名称： OnWatchEtCO2Handle
		// 功能： 启动/断开呼吸的监视
		// 参数：
		//        IDistributeSimulateData  *pDistributeInterface: 数据派发接口
		//        BOOL bCutWatch:
		// 返回值: 
		virtual void OnWatchEtCO2Handle(IDistributeSimulateData *pDistributeInterface, base::CShowEtCO2UpdateInterface *pInterface, bool bCutWatch);
		/*******************************************************************************/
		// 函数名称： OnWatchRespHandle
		// 功能： 启动/断开呼吸的监视
		// 参数：
		//        IDistributeSimulateData  *pDistributeInterface: 数据派发接口
		//        BOOL bCutWatch:
		// 返回值: 
		virtual void OnWatchRespHandle(IDistributeRespSimulateData *pDistributeInterface, base::CShowRespRateUpdateInterface *pInterface, bool bCutWatch);
		/*******************************************************************************/
		// 函数名称： OnWatchABPHandle
		// 功能： 启动/断开ABP的监视
		// 参数：
		//        IDistributeSimulateData  *pDistributeInterface: 数据派发接口
		//        CShowABPUpdateInterface *pInterface
		//        BOOL bCutWatch:
		// 返回值:  
		virtual void OnWatchABPHandle(IDistributeSimulateData  *pDistributeInterface, base::CShowABPUpdateInterface *pInterface, bool bCutWatch);
		/*******************************************************************************/
		// 函数名称： StartLinkWatchBarsShowInterfaces
		// 功能： 初始连接模拟监控面板的显示接口
		// 参数： CWatchBarsShowInterfacesAggregate *pShowAggregate:        
		// 返回值:  
		virtual void StartLinkWatchBarsShowInterfaces(CWatchBarsShowInterfacesAggregate *pShowAggregate);
		/*******************************************************************************/
		// 函数名称： UnLinkWatchBarsShowInterfaces
		// 功能： 断开模拟监控面板的显示接口
		// 参数： CWatchBarsShowInterfacesAggregate *pShowAggregate:        
		// 返回值:  
		virtual void UnLinkWatchBarsShowInterfaces(CWatchBarsShowInterfacesAggregate *pShowAggregate);
	public:
		//停止模拟数据的实时生成
		void StopSimulateBuilds();
		/*******************************************************************************/
		// 函数名称： StartSimulateBuild
		// 功能： 启动模拟数据的生成，并带动SpO2及ABP实时数据
		// 参数： 
		// 返回值:  
		void StartSimulateBuild();
		/*******************************************************************************/
		// 函数名称： InitialPhysBuildsRelationAndResources
		// 功能： 初始化体征构造器相关的指针设定及加载资源
		// 参数：   
		// 返回值:  
		void InitialPhysBuildsRelationAndResources(const std::string &resPath, transLayer::ITransportOrderIrpToSimulator *pTransportOrderIrp = NULL, SimulatePatientType ePatientType = SPT_Adult);
	protected:
		virtual void RaiseJowAct(bool bLookUp) { };
		//人工呼吸开始\结束(TRUE:开始；FALSE:结束)
		virtual void BreathStateAct(bool bState) { };
		//完成五个循环的CPR
		virtual void FiveCycleCompleteAct() { };
		//按压开始\结束(TRUE:开始；FALSE:结束)
		virtual void PressureStateAct(bool bState);
		//结束CPR操作
		virtual void FinishCPROperator(bool bSecceed);
	public:
		//设置是否忽略心电链接检查
		void Set_IsClearEcgWatchLink(bool bClear);
		//设置心电链接检查状态
		void Set_EcgWatchLinkState(bool bLinking);
		bool Get_IsEcgWatchLink();
		//设置是否忽略SpO2链接检查
		void Set_IsClearSpO2WatchLink(bool bClear);
		//设置SpO2链接检查状态
		void Set_SpO2WatchLinkState(bool bLinking);
		bool Get_IsSpO2WatchLink();
		//设置是否忽略ABP链接检查
		void Set_IsClearABPWatchLink(bool bClear);
		//设置ABP链接检查状态
		void Set_ABPWatchLinkState(bool bLinking);
		//设置是否忽略EtCO2链接检查
		void Set_IsClearEtCO2WatchLink(bool bClear);
		//设置EtCO2链接检查状态
		void Set_EtCO2WatchLinkState(bool bLinking);
		//设置是否忽略Resp链接检查
		void Set_IsClearRespWatchLink(bool bClear);
		//设置Resp链接检查状态
		void Set_RespWatchLinkState(bool bLinking);
	};
}}
