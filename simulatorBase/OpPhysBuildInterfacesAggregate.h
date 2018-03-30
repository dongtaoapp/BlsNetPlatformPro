#pragma once
#include ".\OpECGBuildInterface.h"
#include ".\OpSpO2BuildInterface.h"
#include ".\OpEtCO2BuildInterface.h"
#include ".\OpRespBuildInterface.h"
#include ".\OpABPBuildInterface.h"
#include ".\ITransportOrderIrpToSimulator.h"
#include ".\IDistributeSimulateData.h"

#include "..\Common\CommonGlobal.h"

namespace jysoft { namespace simulator {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     生理体征模拟器的构造接口集合
	创建人：	 hjg
	创建时间：   2008/8/12
	//-----------------------------------------------------------------------------------------------------------------*/
	class CWatchBarsShowInterfacesAggregate;
    class SIMULATORBASESHARED_EXPORT COpPhysBuildInterfacesAggregate
	{
	public:
		COpPhysBuildInterfacesAggregate(void);
		virtual ~COpPhysBuildInterfacesAggregate(void);
	protected:
		base::COpECGBuildInterface                    *m_pOpECGBuildInterface;    //心电图模拟器接口
		base::COpSpO2BuildInterface                   *m_pOpSpO2BuildInterface;   //血氧模拟器接口
		base::COpEtCO2BuildInterface                  *m_pEtCO2BuildInterface;    //呼出二氧化碳浓度分压模拟器接口
		base::COpRespBuildInterface                   *m_pRespBuildInterface;     //呼吸模拟器接口
		base::COpABPBuildInterface                    *m_pABPBuildInterface;      //有创血压模拟器接口
	public:
		//初始化生理体征模拟器
		virtual void InitialPhysBuilds(transLayer::ITransportOrderIrpToSimulator *pTransportOrderIrp, SimulatePatientType ePatientType) = 0;
		//关闭生理体征模拟器
		virtual void ClosePhysBuilds() = 0;
	public:  
		/*******************************************************************************/
		// 函数名称： OnWatchECGHandle
		// 功能： 启动/断开心电图的监视
		// 参数：
		//        IDistributeEcgLeadsSimulateData  *pDistributeECGInterface: 数据派发接口
		//        BOOL bCutWatch:
		// 返回值:  
		virtual void OnWatchECGHandle(IDistributeEcgLeadsSimulateData  *pDistributeECGInterface, base::CShowECGUpdateInterface *pInterface, bool bCutWatch) = 0;
		/*******************************************************************************/
		// 函数名称： OnWatchRespHandle
		// 功能： 启动/断开呼吸的监视
		// 参数：
		//        IDistributeSimulateData  *pDistributeInterface: 数据派发接口
		//        BOOL bCutWatch:
		// 返回值: 
		virtual void OnWatchRespHandle(IDistributeRespSimulateData *pDistributeInterface, base::CShowRespRateUpdateInterface *pInterface, bool bCutWatch) = 0;
		/*******************************************************************************/
		// 函数名称： OnWatchEtCO2Handle
		// 功能： 启动/断开呼吸的监视
		// 参数：
		//        IDistributeSimulateData  *pDistributeInterface: 数据派发接口
		//        BOOL bCutWatch:
		// 返回值: 
		virtual void OnWatchEtCO2Handle(IDistributeSimulateData *pDistributeInterface, base::CShowEtCO2UpdateInterface *pInterface, bool bCutWatch) = 0;
		/*******************************************************************************/
		// 函数名称： OnWatchSpO2Handle
		// 功能： 启动/断开SpO2的监视
		// 参数：
		//        IDistributeSimulateData  *pDistributeInterface: 数据派发接口
		//        BOOL bCutWatch:
		// 返回值:  
		virtual void OnWatchSpO2Handle(IDistributeSimulateData  *pDistributeInterface, base::CShowSpO2UpdateInterface *pInterface, bool bCutWatch) = 0;
		/*******************************************************************************/
		// 函数名称： OnWatchABPHandle
		// 功能： 启动/断开ABP的监视
		// 参数：
		//        IDistributeSimulateData  *pDistributeInterface: 数据派发接口
		//        CShowABPUpdateInterface *pInterface
		//        BOOL bCutWatch:
		// 返回值:  
		virtual void OnWatchABPHandle(IDistributeSimulateData  *pDistributeInterface, base::CShowABPUpdateInterface *pInterface, bool bCutWatch) = 0;
	public:
		//返回心电图模拟器接口
		inline base::COpECGBuildInterface * Get_OpECGBuildInterfacePtr() { return m_pOpECGBuildInterface; };
		//返回血氧模拟器接口
		inline base::COpSpO2BuildInterface * Get_OpSpO2BuildInterfacePtr() { return m_pOpSpO2BuildInterface; };
		//返回呼出二氧化碳浓度分压模拟器接口
		inline base::COpEtCO2BuildInterface * Get_OpEtCO2BuildInterfacePtr() { return m_pEtCO2BuildInterface; };
		//返回呼吸模拟器接口
		inline base::COpRespBuildInterface * Get_OpRespBuildInterfacePtr() { return m_pRespBuildInterface; };
		//返回有创血压模拟器接口
		inline base::COpABPBuildInterface  * Get_OpABPBuildInterface() { return m_pABPBuildInterface; };
	public:
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
	};

}}
