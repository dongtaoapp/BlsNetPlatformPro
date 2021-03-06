#pragma once
#include <string>
#include <pugixml.hpp>
#include ".\elementParse_global.h"

class AFX_EXT_CLASS CSAction_Pace
{
public:
	CSAction_Pace(void);
	virtual ~CSAction_Pace(void);
public:
	static bool isAction_Pace(const std::string &caption);
	static std::string getAction_Pace_Caption() { return "Action_Pace"; };
	// 将属性保存到字符窜中
	static std::string saveParams( bool bEnable, short sThreshold);
	static void saveParamsToXML(pugi::xml_node*  pXMLPaceChild, bool bEnable, short sThreshold);
	static bool explainParamsFromXML(pugi::xml_node*  pXMLPaceChild, /*out*/bool *bEnable, /*out*/short *sThreshold);
};

