#pragma once
#include <pugixml.hpp>
#include ".\IHandleIrpsCollect.h"

#include "..\simulatorsymptom\xvirtualcomponent.h"

namespace jysoft { namespace flowEngine 
{
	class CXVirtualLink : public simulator::CXVirtualComponent
	{
	public:
		CXVirtualLink(void);
		virtual ~CXVirtualLink(void);
	protected:
		pugi::xml_node         m_xmlLinkAimDOMNodePtr;   //连接对象的节点指针
	public:
		virtual bool isKindOf(const std::string &strClassName);
		inline pugi::xml_node* GetLinkAimDOMNodePtr() { return &m_xmlLinkAimDOMNodePtr; };
	public:
		//添加连接对象到队列中，以便可以处理Irp
		virtual void AddLinkObjToHandleIrpCollect(IHandleIrpsCollect *pHandleIrpsCollect) = 0;
		//移除连接对象
		virtual void RemoveLinkObjFromHandleIrpCollect(IHandleIrpsCollect *pHandleIrpsCollect) = 0;
	protected:
		pugi::xml_node getFrameDOMNodePtr(const std::string &strNodeName, const std::string &strAimId, pugi::xml_node *pScenarioNode);
	};
}}
