#include ".\saction_defibrillate.h"

#include <boost/format.hpp>

CSAction_Defibrillate::CSAction_Defibrillate(void)
{
}

CSAction_Defibrillate::~CSAction_Defibrillate(void)
{
}

bool CSAction_Defibrillate::isAction_Defibri(const std::string &caption)
{
	if( caption == getAction_Defibri_Caption() )
		return true;
	return false;
}

// 将属性保存到字符窜中
std::string CSAction_Defibrillate::saveParams( bool bEnable, bool bClearCount)
{
	boost::format  fmt("<Action_Defibrillate set=\"%s\" clearShocks=\"%s\" />");
	fmt % (bEnable ? "Enable" : "Ignore") % (bClearCount ? "Clear" : "No Clear");
	return fmt.str();
}

void CSAction_Defibrillate::saveParamsToXML(pugi::xml_node*  pXMLDefibrChild, bool bEnable, bool bClearCount)
{
	pXMLDefibrChild->append_attribute("set").set_value( bEnable ? "Enable" : "Ignore" );
	pXMLDefibrChild->append_attribute("clearShocks").set_value( bClearCount ? "Clear" : "No Clear" );
}

bool CSAction_Defibrillate::explainParamsFromXML(pugi::xml_node*  pXMLDefibrChild, /*out*/bool *bEnable, /*out*/bool *bClearCount)
{
	std::string  defibrEnable = pXMLDefibrChild->attribute("set").as_string("Enable");
	if( defibrEnable == "Enable" )
	{
		*bEnable = true;
	}
	else
	{
		*bEnable = false;
	}
	std::string  clearCount = pXMLDefibrChild->attribute("clearShocks").as_string("Clear");
	if( clearCount == "Clear")
	{
		*bClearCount = true;
	}
	else
	{
		*bClearCount = false;
	}
	return true;
}
