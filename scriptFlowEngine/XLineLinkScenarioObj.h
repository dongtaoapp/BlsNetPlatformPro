#pragma once
#include "xlinelink.h"
#include ".\IAclsFlowStrategy.h"

#include "..\SimulatorBase\FrameFlowIrp.h"


namespace jysoft { namespace flowEngine 
{
	class CXLineLinkScenarioObj : public CXLineLink
	{
	public:
		CXLineLinkScenarioObj();
		virtual ~CXLineLinkScenarioObj(void);
	public:
		virtual bool isKindOf(const std::string &strClassName);
		/*******************************************************************************
		//功能：解析连接对象
		//参数：const CString &strAimId:          连接的目标对象的ID号
		//      IXMLDOMNode *pScenarioNode:       元素scenario节点指针
		//返回值:  是否解析成功
		*********************************************************************************/
		virtual bool InitialLineLink(const std::string &strAimId, pugi::xml_node *pScenarioNode, IAclsFlowStrategy  *pFlowStrategy);
	public: //基类函数重载
		//添加连接对象到队列中，以便可以处理Irp
		void AddLinkObjToHandleIrpCollect(IHandleIrpsCollect *pHandleIrpsCollect) { };
		//移除连接对象
		void RemoveLinkObjFromHandleIrpCollect(IHandleIrpsCollect *pHandleIrpsCollect) { };
	public:
		//返回场景转移Irp
		irp::CFrameFlowIrp * GetFrameFlowIrp(eEventSign eEvent);
	};
}}