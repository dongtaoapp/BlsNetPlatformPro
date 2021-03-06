#pragma once
#include <string>
#include <pugixml.hpp>
#include ".\elementParse_global.h"


class AFX_EXT_CLASS CSEvent_Pulse
{
public:
	CSEvent_Pulse(void);
	virtual ~CSEvent_Pulse(void);
public:
	static bool isEvent_Pulse(const std::string &caption);
	static std::string getEvent_Pulse_Caption() { return "Event_PulseCheck"; };
	// 将属性保存到字符窜中
	static std::string saveParams(short sPulseCount, short sPulseAct);
	static void saveParamsToXML(pugi::xml_node* pXMLPulseChild, short sPulseCount, short sPulseAct);
	static bool explainParamsFromXML(pugi::xml_node* pXMLPulseChild, /*out*/short *sPulseCount, /*out*/short *sPulseAct); 
public:
	static bool explainSimulateTriggerPulseEvent(const std::string &pulseTriggerXML, /*out*/short *sPulseCount, /*out*/short *sPulseAct);
};

