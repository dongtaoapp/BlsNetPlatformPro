#pragma once
#include <string>
#include <pugixml.hpp>
#include ".\elementParse_global.h"


class AFX_EXT_CLASS CSEvent_Thump
{
public:
	CSEvent_Thump(void);
	virtual ~CSEvent_Thump(void);
public:
	static bool isAction_Thump(const std::string &caption);
	static std::string getAction_Thump_Caption() { return "Action_Thump"; };
	// 将属性保存到字符窜中
	static std::string saveParams();
	static void saveParamsToXML(pugi::xml_node* pXMLThumpChild);
	static bool explainParamsFromXML(pugi::xml_node* pXMLThumpChild, /*out*/bool *bThumpAct); 
};

