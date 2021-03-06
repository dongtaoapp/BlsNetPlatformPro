#pragma once
#include <string>
#include <pugixml.hpp>
#include ".\elementParse_global.h"


class AFX_EXT_CLASS CSEvent_Pace
{
public:
	CSEvent_Pace(void);
	virtual ~CSEvent_Pace(void);
public:
	static bool isEvent_Pace(const std::string &caption);
	static std::string getEvent_Pace_Caption() { return "Event_Pace"; };
	// 将属性保存到字符窜中
	static std::string saveParams(short iSign, short sTime);
	static void saveParamsToXML(pugi::xml_node* pXMLPaceChild, short iSign, short sTime);
	static bool explainParamsFromXML(pugi::xml_node* pXMLPaceChild, /*out*/short *iSign, /*out*/short *sTime); 
public:
	static bool explainSimulateTriggerPaceEvent(const std::string &paceTriggerXML, /*out*/short *iSign, /*out*/short *sTime);
};

