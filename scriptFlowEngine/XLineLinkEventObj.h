#pragma once
#include "XLineLink.h"
#include ".\XVirtualEventFrame.h"


namespace jysoft { namespace flowEngine 
{
	class CXLineLinkEventObj : public CXLineLink
	{
	public:
		CXLineLinkEventObj();
		virtual ~CXLineLinkEventObj(void);
	protected:
		CXVirtualEventFrame    *m_pEventFrame;
	public:
		virtual bool isKindOf(const std::string &strClassName);
		/*******************************************************************************
		//功能：解析连接对象
		//参数：const CString &strAimId:          连接的目标对象的ID号
		//      pugi::xml_node *pScenarioNode:       元素scenario节点指针
		//返回值:  是否解析成功
		*********************************************************************************/
		virtual bool InitialLineLink(const std::string &strAimId, pugi::xml_node *pScenarioNode, IAclsFlowStrategy  *pFlowStrategy);
	public: //基类函数重载
		//添加连接对象到队列中，以便可以处理Irp
		void AddLinkObjToHandleIrpCollect(IHandleIrpsCollect *pHandleIrpsCollect);
		//移除连接对象
		void RemoveLinkObjFromHandleIrpCollect(IHandleIrpsCollect *pHandleIrpsCollect);
	};
}}