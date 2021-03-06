#pragma once
#include <string>
#include <pugixml.hpp>
#include ".\elementParse_global.h"


class AFX_EXT_CLASS CSEvent_Time
{
public:
	CSEvent_Time(void);
	virtual ~CSEvent_Time(void);
public:
	static bool isEvent_Time(const std::string &caption);
	static std::string getEvent_Time_Caption() { return "Event_Time"; };
	// 将属性保存到字符窜中
	static std::string saveParams(bool bSelect, short sTime);
	static void saveParamsToXML(pugi::xml_node* pXMLEventChild, bool bSelect, short sTime);
	static bool explainParamsFromXML(pugi::xml_node* pXMLEventChild, /*out*/bool *bSelect, /*out*/short *sTime); 
};

