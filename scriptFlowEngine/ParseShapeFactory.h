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
		//�����������ڵ���������
		void ParseActionObject(pugi::xml_node *pXMLShapeNode, std::list<simulator::CXActionVirtual *> *plstNewActions) const;
		//�����¼����е��¼�
		virtual CXEventVirtual * ParseEventObject(pugi::xml_node *pXMLShapeNode) const;
	protected:
		void DoParseActionOthersObj(pugi::xml_node *pXMLActonOthersNode, std::list<simulator::CXActionVirtual *> *plstNewActions) const;
		//������������
		simulator::CXActionVirtual *CreateActionObject(const std::string & strSignName) const ;
		//����������������
		simulator::CXActionVirtual * CreateActionOtherObj(const std::string & strSignName) const;
	};
}}
