#pragma once
#include <string>
#include <pugixml.hpp>
#include ".\elementParse_global.h"

class AFX_EXT_CLASS CSAction_Temperature
{
public:
	CSAction_Temperature(void);
	~CSAction_Temperature(void);
public:
	static bool isAction_Temperature(const std::string &caption);
	static std::string getAction_Temperature_Caption() { return "Action_Temperature"; };
	// 将属性保存到字符串中
	static std::string saveParams(float fTmpValue);
	static void saveParamsToXML(pugi::xml_node* pXMLTempMess, float fTmpValue);
	static bool explainParamsFromXML(pugi::xml_node* pXMLTempMess, /*out*/float *fTmpValue); 
};
