#pragma once
#include ".\blsmainflowvirtual.h"


namespace jysoft { namespace flowEngine 
{
	class CBlsMainFlowWatch : public CBlsMainFlowVirtual
	{
	public:
		CBlsMainFlowWatch(CBlsSimulateCase  *pSimulateCase, transLayer::CFormatTransport* pTransport);
		virtual ~CBlsMainFlowWatch(void);
	public: //基类重载
		/*******************************************************************************/
		// 函数名称： CreateScenario
		// 功能： 根据场景脚本文件，初始化ACLS流程处理中心
		// 参数： 
		//       pugi::xml_node *pRootElement: 
		// 返回值:  
		virtual pugi::xml_node  CreateScenario( pugi::xml_node rootElement );
	protected: //基类重载
		/*******************************************************************************/
		// 函数名称： ExecInitialFramework
		// 功能： 初始化执行当前的解析Actions
		// 参数： 
		//   
		// 返回值:  
		virtual void ExecInitialFramework(SimulatePatientType ePatientType);
	};
}}
