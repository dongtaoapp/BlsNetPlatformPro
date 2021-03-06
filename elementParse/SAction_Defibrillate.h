#pragma once
#include <string>
#include <pugixml.hpp>
#include ".\elementParse_global.h"

class AFX_EXT_CLASS CSAction_Defibrillate
{
public:
	CSAction_Defibrillate(void);
	virtual ~CSAction_Defibrillate(void);
public:
	static bool isAction_Defibri(const std::string &caption);
	static std::string getAction_Defibri_Caption() { return "Action_Defibrillate"; };
	// 将属性保存到字符窜中
	static std::string saveParams( bool bEnable, bool bClearCount);
	static void saveParamsToXML(pugi::xml_node*  pXMLDefibrChild, bool bEnable, bool bClearCount);
	static bool explainParamsFromXML(pugi::xml_node*  pXMLDefibrChild, /*out*/bool *bEnable, /*out*/bool *bClearCount);
};
