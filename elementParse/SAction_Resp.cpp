#include ".\SAction_Resp.h"

#include <boost/format.hpp>


CSAction_Resp::CSAction_Resp(void)
{
}


CSAction_Resp::~CSAction_Resp(void)
{
}

bool CSAction_Resp::isAction_Resp(const std::string &caption)
{
	if( caption == getAction_Resp_Caption() )
		return true;
	return false;
}

// 将属性保存到字符窜中
std::string CSAction_Resp::saveParams( const std::string &breathType, long lBreathValue)
{
	boost::format  fmt("<Action_Resp breathType=\"%s\" value=\"%d\" />");
	fmt % breathType % lBreathValue;
	return fmt.str();
}

void CSAction_Resp::saveParamsToXML(pugi::xml_node* pXMLRespChild, const std::string &breathType, long lBreathnValue)
{
	pXMLRespChild->append_attribute("breathType").set_value(breathType.c_str());
	pXMLRespChild->append_attribute("value").set_value(lBreathnValue);
}

bool CSAction_Resp::explainParamsFromXML(pugi::xml_node* pXMLRespChild, /*out*/std::string *pstrBreathType, /*out*/long *lBreathnValue)
{
	*pstrBreathType = pXMLRespChild->attribute("breathType").as_string();
	*lBreathnValue = pXMLRespChild->attribute("value").as_int();
	return true;
}
