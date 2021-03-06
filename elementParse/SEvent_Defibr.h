#pragma once
#include <string>
#include <pugixml.hpp>
#include ".\elementParse_global.h"


class AFX_EXT_CLASS CSEvent_Defibr
{
public:
	CSEvent_Defibr(void);
	virtual ~CSEvent_Defibr(void);
public:
	static bool isEvent_Defibr(const std::string &caption);
	static std::string getEvent_Defibr_Caption() { return "Event_Defibri"; };
	// 将属性保存到字符窜中
	static std::string saveParams(short sDefibrCount, short nDefibrEnergy, bool bSyncDefibr = false);
	static void saveParamsToXML(pugi::xml_node* pXMLDefibrChild, short sDefibrCount, short nDefibrEnergy, bool bSyncDefibr = false);
	static bool explainParamsFromXML(pugi::xml_node* pXMLDefibrChild, /*out*/short *sDefibrCount, /*out*/short *nDefibrEnergy, /*out*/bool *bSyncDefibr = NULL);
public:
	static bool explainSimulateTriggerDefibrEvent(const std::string &defibrTriggerXML, /*out*/short *sDefibrCount, /*out*/short *nDefibrEnergy, /*out*/bool *bSyncDefibr = NULL);
};

