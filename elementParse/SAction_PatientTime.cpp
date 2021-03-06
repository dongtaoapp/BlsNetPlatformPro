#include <boost/format.hpp>
#include ".\SAction_PatientTime.h"


CSAction_PatientTime::CSAction_PatientTime(void)
{
}

CSAction_PatientTime::~CSAction_PatientTime(void)
{
}

bool CSAction_PatientTime::isAction_PatientTime(const std::string &caption)
{
	if( caption == getAction_PatientTime_Caption() )
	{
		return true;
	}
	return false;
}

// 将属性保存到字符窜中
std::string CSAction_PatientTime::saveParams( long lTimeMode, long lTimeValue)
{
	std::string  strTimeMode;
	switch( lTimeMode )
	{
	case 0:
		{
            strTimeMode = "set";
			break;
		}
	case 1:
		{
            strTimeMode = "add";
			break;
		}
	case 2:
		{
            strTimeMode = "subtruct";
			break;
		}
	default:
		{
			break;
		}
	}
	boost::format  fmt("<Action_PatientTime timeMode=\"%s\" value=\"%d\" />");
	fmt % strTimeMode % lTimeValue;
	return fmt.str();
}

void CSAction_PatientTime::saveParamsToXML(pugi::xml_node* pXMLPatientTimeChild, long lTimeMode, long lTimeValue)
{
	std::string  strTimeMode;
	switch( lTimeMode )
	{
	case 0:
		{
            strTimeMode = "set";
			break;
		}
	case 1:
		{
            strTimeMode = "add";
			break;
		}
	case 2:
		{
            strTimeMode = "subtruct";
			break;
		}
	default:
		{
			break;
		}
	}
	pXMLPatientTimeChild->append_attribute("timeMode").set_value( strTimeMode.c_str() );
	pXMLPatientTimeChild->append_attribute("value").set_value( lTimeValue );
}

bool CSAction_PatientTime::explainParamsFromXML(pugi::xml_node* pXMLPatientTimeChild, /*out*/long *lTimeMode, /*out*/long *lTimeValue)
{
	std::string  timeMode = pXMLPatientTimeChild->attribute("timeMode").as_string("set");
	if( timeMode == "set" )
		*lTimeMode = 0;
	else if( timeMode == "add" )
		*lTimeMode = 1;
	else  
		*lTimeMode = 2;
	//病人时间
	*lTimeValue = pXMLPatientTimeChild->attribute("value").as_int();
	return true;
}
