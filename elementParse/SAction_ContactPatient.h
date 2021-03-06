#pragma once
#include <string>
#include <pugixml.hpp>
#include ".\elementParse_global.h"


//接触病人
class AFX_EXT_CLASS CSAction_ContactPatient
{
public:
	CSAction_ContactPatient(void);
	virtual ~CSAction_ContactPatient(void);
public:
	static bool isAction_ContactPatient(const std::string &caption);
	static std::string getAction_ContactPatient_Caption() { return "Action_ContactPatient"; };
	// 将属性保存到字符窜中
	static std::string saveParams(bool bContact);
	static void saveParamsToXML(pugi::xml_node* pXMLContactPatientChild, bool bContact);
	static bool explainParamsFromXML(pugi::xml_node* pXMLContactPatientChild, /*out*/bool *bContact);
};

