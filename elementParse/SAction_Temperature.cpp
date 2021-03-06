#include ".\saction_temperature.h"

#include <boost/format.hpp>

CSAction_Temperature::CSAction_Temperature(void)
{
}

CSAction_Temperature::~CSAction_Temperature(void)
{
}

bool CSAction_Temperature::isAction_Temperature(const std::string &caption)
{
	if( caption == getAction_Temperature_Caption() )
		return true;
	return false;
}

// 将属性保存到字符串中
std::string CSAction_Temperature::saveParams(float fTmpValue)
{
#define  _INFINITE     0.0001
	boost::format  fmt("<Action_Temperature value=\"%.1f\" />");
	fmt % (fTmpValue+_INFINITE);
	return fmt.str();
}

void CSAction_Temperature::saveParamsToXML(pugi::xml_node* pXMLTempMess, float fTmpValue)
{
	pXMLTempMess->append_attribute("value").set_value(fTmpValue);
}

bool CSAction_Temperature::explainParamsFromXML(pugi::xml_node* pXMLTempMess, /*out*/float *fTmpValue)
{
	*fTmpValue = pXMLTempMess->attribute("value").as_float(37.4f);
	return true;
}
