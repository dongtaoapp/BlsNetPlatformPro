#pragma once
#include <string>
#include <pugixml.hpp>
#include <boost/logic/tribool.hpp>
#include ".\elementParse_global.h"


using namespace boost;
class AFX_EXT_CLASS CSEvent_AED
{
public:
	CSEvent_AED(void);
	virtual ~CSEvent_AED(void);
public:
	static bool isEvent_AED(const std::string &caption);
	static std::string getEvent_AED_Caption() { return "Event_AED"; };
	// 将属性保存到字符窜中
	static std::string saveParams(boost::tribool bStartupAED);
	static void saveParamsToXML(pugi::xml_node* pXMLAEDChild, boost::tribool bStartupAED = indeterminate);
	static bool explainParamsFromXML(pugi::xml_node* pXMLAEDChild, /*out*/boost::tribool *bStartupAED); 
};

