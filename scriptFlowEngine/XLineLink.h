#pragma once
#include <pugixml.hpp>
#include "xvirtuallink.h"
#include ".\IAclsFlowStrategy.h"
#include ".\IGetPhysiologyActionObj.h"


namespace jysoft { namespace flowEngine 
{
	class IAclsFlowStrategy;
	class CXLineLink : public CXVirtualLink
	{
	public:
		CXLineLink();
		virtual ~CXLineLink(void);
	protected:
		IAclsFlowStrategy          *m_pFlowStrategy;
	public:
		virtual bool isKindOf(const std::string &strClassName);
		/*******************************************************************************
		//功能：解析连接对象
		//参数：const std::string &strAimId:          连接的目标对象的ID号
		//      pugi::xml_node *pScenarioNode:       元素scenario节点指针
		//返回值:  是否解析成功
		*********************************************************************************/
		virtual bool InitialLineLink(const std::string &strAimId, pugi::xml_node *pScenarioNode, IAclsFlowStrategy  *pFlowStrategy) = 0;
	public: //基类函数重载
		//添加连接对象到队列中，以便可以处理Irp
		virtual void AddLinkObjToHandleIrpCollect(IHandleIrpsCollect *pHandleIrpsCollect) = 0;
		//移除连接对象
		virtual void RemoveLinkObjFromHandleIrpCollect(IHandleIrpsCollect *pHandleIrpsCollect) = 0;
	};
}}