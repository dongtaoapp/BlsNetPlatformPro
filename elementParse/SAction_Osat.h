#pragma once
#include <string>
#include <pugixml.hpp>
#include ".\elementParse_global.h"

class AFX_EXT_CLASS CSAction_Osat
{
public:
	CSAction_Osat(void);
	virtual ~CSAction_Osat(void);
public:
	static bool isAction_Osat(const std::string &caption);
	static std::string getAction_Osat_Caption() { return "Action_Osat"; };
	// 将属性保存到字符窜中
	static std::string saveParams(long lOsatValue);
	static void saveParamsToXML(pugi::xml_node* pXMLOsatChild, long lOsatValue);
	static bool explainParamsFromXML(pugi::xml_node* pXMLOsatChild, /*out*/long *lOsatValue); 
};

