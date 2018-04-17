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
		pugi::xml_node         m_xmlLinkAimDOMNodePtr;   //���Ӷ���Ľڵ�ָ��
	public:
		virtual bool isKindOf(const std::string &strClassName);
		inline pugi::xml_node* GetLinkAimDOMNodePtr() { return &m_xmlLinkAimDOMNodePtr; };
	public:
		//������Ӷ��󵽶����У��Ա���Դ���Irp
		virtual void AddLinkObjToHandleIrpCollect(IHandleIrpsCollect *pHandleIrpsCollect) = 0;
		//�Ƴ����Ӷ���
		virtual void RemoveLinkObjFromHandleIrpCollect(IHandleIrpsCollect *pHandleIrpsCollect) = 0;
	protected:
		pugi::xml_node getFrameDOMNodePtr(const std::string &strNodeName, const std::string &strAimId, pugi::xml_node *pScenarioNode);
	};
}}
