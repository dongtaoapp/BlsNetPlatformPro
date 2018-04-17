#pragma once
#include <list>
#include "..\Common\CommonGlobal.h"


namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     生理体征修改操作接口类
	创建人：	 hjg
	创建时间：   2017/2/23
	//-----------------------------------------------------------------------------------------------------------------*/
	class CXActionVirtual;
	class ISetSimulateSymptoms
	{
	public:
		ISetSimulateSymptoms(void);
		virtual ~ISetSimulateSymptoms(void);
	public:
		/*******************************************************************************/
		// 函数名称： initialScenario
		// 功能：   生理体征初始化为当前场景状态
		// 参数：   CList<CXActionVirtual *, CXActionVirtual *> lstActions: 
		// 返回值:  tag_TrendValue: 当前场景所设置的体征值
		virtual void initialScenarioSet(std::list<CXActionVirtual *> *plstActions, SimulatePatientType ePatientType) = 0;
		/*******************************************************************************/
		// 函数名称： modifyScenario
		// 功能：   修改当前场景状态的生理体征值
		// 参数：   CList<CXActionVirtual *, CXActionVirtual *> lstActions: 
		//          eEventSign eEventValue:  场景转换的事件信号
		//          BOOL bExecActions:       是否执行体征
		//          short sTransferTime:
		// 返回值:  tag_TrendValue: 当前场景所设置的体征值
		virtual void modifyScenarioSet(std::list<CXActionVirtual *> *plstActions, eEventSign eEventValue, bool bExecActions = true, short sTransferTime = 0) = 0;
		//初始化体征模拟曲线构造器
		virtual void initialSimulateSymptomsBuild(SimulatePatientType ePatientType) = 0;
	};
}}