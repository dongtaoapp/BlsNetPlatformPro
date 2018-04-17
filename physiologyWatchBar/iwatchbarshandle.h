#pragma once
#include ".\physiologywatchbar_global.h"

#include "..\Common\CommonGlobal.h"

#include "..\SimulatorBase\OpPhysBuildInterfacesAggregate.h"

namespace jysoft { namespace controls { 

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     生理体征值模拟监视控件操作接口
	创建人：	 hjg
	创建时间：   2008/8/12
	//-----------------------------------------------------------------------------------------------------------------*/
    class PHYSIOLOGYWATCHBARSHARED_EXPORT IWatchBarsHandle
	{
	public:
		IWatchBarsHandle(void);
		virtual ~IWatchBarsHandle(void);
	public:
		/*******************************************************************************/
		// 函数名称： OnClearSimulateTypeDefineHandle
		// 功能： 清除模拟监视控件监控的模拟人对象，使其监控的模拟人类型未指定
		// 参数：
		// 返回值:  
		virtual void OnClearSimulateTypeDefineHandle() = 0;
		/*******************************************************************************/
		// 函数名称： OnClearSimulateTypeDefineHandle
		// 功能： 定义模拟监视控件监控的模拟人对象，使其监控的模拟人类型指定
		// 参数：
		//        SimulatePatientType ePatientType： 模拟人类型 
		// 返回值:  
		virtual void OnDefineWatchedSimulateTypeHandle(SimulatePatientType ePatientType) = 0;
		/*******************************************************************************/
		// 函数名称： OnClearSimulateTypeDefineHandle
		// 功能： 定义模拟监视控件监控的模拟人对象，使其监控的模拟人类型指定
		// 参数：
		//        SimulatePatientType ePatientType： 模拟人类型 
		//        COpPhysBuildInterfacesAggregate *pBuildInterfacesAggregate: 
		// 返回值:  
		virtual void OnDefineWatchedSimulateTypeHandle(SimulatePatientType ePatientType, simulator::COpPhysBuildInterfacesAggregate *pBuildInterfacesAggregate) = 0;
		/*******************************************************************************/
		// 函数名称： OnStartWatchPhysBuilds
		// 功能： 生理体征值模拟监视控件开始监控生理体征模拟器中数据
		// 参数：
		//        COpPhysBuildInterfacesAggregate *pBuildInterfacesAggregate: 
		// 返回值:  
		virtual void OnStartWatchPhysBuilds( simulator::COpPhysBuildInterfacesAggregate *pBuildInterfacesAggregate ) = 0;
		/*******************************************************************************/
		// 函数名称： OnStartWatchPhysBuilds
		// 功能： 生理体征值模拟监视控件断开与生理体征模拟器的监控
		// 参数：
		//        COpPhysBuildInterfacesAggregate *pBuildInterfacesAggregate: 
		// 返回值:  
		virtual void OnCutWatchPhysBuilds( simulator::COpPhysBuildInterfacesAggregate *pBuildInterfacesAggregate ) = 0;
		/*******************************************************************************/
		// 函数名称： OnFreezedEcgAndSpO2AndABP
		// 功能： Freeze生理体征值模拟监视控件中的ECG, SpO2, ABP
		// 参数：
		//        BOOL bFreezed: 
		// 返回值:  
		virtual void OnFreezedEcgAndSpO2AndABP( simulator::COpPhysBuildInterfacesAggregate *pBuildInterfacesAggregate, BOOL bFreezed ) = 0;
		/*******************************************************************************/
		// 函数名称： OnFreezedRespAndEtCO2
		// 功能： Freeze生理体征值模拟监视控件中的Resp和EtCO2
		// 参数：
		//        BOOL bFreezed: 
		// 返回值:  
		virtual void OnFreezedRespAndEtCO2(simulator::COpPhysBuildInterfacesAggregate *pBuildInterfacesAggregate,  BOOL bFreezed ) = 0;
	};
}}
