#pragma once
#include <list>
#include <pugixml.hpp>
#include <boost/serialization/singleton.hpp>
#include ".\XEventVirtual.h"

#include "..\SimulatorSymptom\XActionVirtual.h"

using namespace boost::serialization;

namespace jysoft { namespace flowEngine 
{
	class CParseShapeFactory : public singleton<CParseShapeFactory>
	{
	public:
		CParseShapeFactory(void);
		virtual ~CParseShapeFactory(void);
	public:
		//解析场景框内的体征对象
		void ParseActionObject(pugi::xml_node *pXMLShapeNode, std::list<simulator::CXActionVirtual *> *plstNewActions) const;
		//解析事件框中的事件
		virtual CXEventVirtual * ParseEventObject(pugi::xml_node *pXMLShapeNode) const;
	protected:
		void DoParseActionOthersObj(pugi::xml_node *pXMLActonOthersNode, std::list<simulator::CXActionVirtual *> *plstNewActions) const;
		//生成体征对象
		simulator::CXActionVirtual *CreateActionObject(const std::string & strSignName) const ;
		//生成其它体征对象
		simulator::CXActionVirtual * CreateActionOtherObj(const std::string & strSignName) const;
	};
}}
