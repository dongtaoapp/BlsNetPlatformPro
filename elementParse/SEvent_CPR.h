#pragma once
#include <string>
#include <pugixml.hpp>
#include ".\elementParse_global.h"


class AFX_EXT_CLASS CSEvent_CPR
{
public:
	CSEvent_CPR(void);
	virtual ~CSEvent_CPR(void);
public:
	static bool isEvent_CPR(const std::string &caption);
	static std::string getEvent_CPR_Caption() { return "Event_CPR"; };
	// 将属性保存到字符窜中
	static std::string saveParams(short iSel, short sParamValue, short sAccumulateNum);
	static void saveParamsToXML(pugi::xml_node* pXMLCPRChild, short iSel, short sParamValue, short sAccumulateNum);
	static bool explainParamsFromXML(pugi::xml_node* pXMLCPRChild, /*out*/short *iSel, /*out*/short *sParamValue, /*out*/short *sAccumulateNum); 
};

