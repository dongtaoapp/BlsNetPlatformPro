#include ".\xvirtuallink.h"


namespace jysoft { namespace flowEngine 
{
	CXVirtualLink::CXVirtualLink(void)
	{
	}

	CXVirtualLink::~CXVirtualLink(void)
	{
	}

	bool CXVirtualLink::isKindOf(const std::string &strClassName)
	{
		if(strClassName == "CXVirtualLink")
		{
			return true;
		}
		return false;
	}

	pugi::xml_node CXVirtualLink::getFrameDOMNodePtr(const std::string &strNodeName, const std::string &strAimId, pugi::xml_node *pScenarioNode)
	{
		pugi::xml_node  frameXMLNode;
		for (pugi::xml_node_iterator it = pScenarioNode->begin(); it != pScenarioNode->end(); ++it)
		{
			std::string  frameNodeName( it->name() );
			if( frameNodeName == strNodeName )
			{
				//»ñÈ¡IDºÅ
				std::string  strId = it->attribute("id").as_string();
				if( strId == strAimId )
				{
					frameXMLNode = *it;
					break;
				}
			}
		}
		return frameXMLNode;
	}
}}
