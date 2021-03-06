#pragma once
#include <string>
#include <pugixml.hpp>
#include ".\elementParse_global.h"


//病人时间
class AFX_EXT_CLASS CSAction_PatientTime
{
public:
	CSAction_PatientTime(void);
	virtual ~CSAction_PatientTime(void);
public:
	static bool isAction_PatientTime(const std::string &caption);
	static std::string getAction_PatientTime_Caption() { return "Action_PatientTime"; };
	// 将属性保存到字符窜中
	static std::string saveParams( long lTimeMode, long lTimeValue);
	static void saveParamsToXML(pugi::xml_node* pXMLPatientTimeChild, long lTimeMode, long lTimeValue);
	static bool explainParamsFromXML(pugi::xml_node* pXMLPatientTimeChild, /*out*/long *lTimeMode, /*out*/long *lTimeValue); 
};

