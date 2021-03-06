#include ".\SEvent_AED.h"

#include <boost/format.hpp>


CSEvent_AED::CSEvent_AED(void)
{
}

CSEvent_AED::~CSEvent_AED(void)
{
}

bool CSEvent_AED::isEvent_AED(const std::string &caption)
{
	if( caption == getEvent_AED_Caption() )
		return true;
	return false;
}

// 将属性保存到字符窜中
std::string CSEvent_AED::saveParams(boost::tribool bStartupAED)
{
	boost::format fmt("<Event_AED value=\"%s\" />");
	if( indeterminate( bStartupAED ) )
	{
		fmt % "arrive";
	}
	else
	{
		fmt % (bStartupAED ? "start" : "over") ;
	}
	return fmt.str();
}

void CSEvent_AED::saveParamsToXML(pugi::xml_node* pXMLAEDChild, boost::tribool bStartupAED/*=boost::indeterminate*/)
{
	if( indeterminate( bStartupAED ) )
	{
		pXMLAEDChild->append_attribute("value").set_value( "arrive" );
	}
	else
	{
		pXMLAEDChild->append_attribute("value").set_value( bStartupAED ? "start" : "over" );
	}
}

bool CSEvent_AED::explainParamsFromXML(pugi::xml_node* pXMLAEDChild, /*out*/boost::tribool *bStartupAED)
{
	std::string  startupAED = pXMLAEDChild->attribute("value").as_string("start");
	if( startupAED == "start" )
	{
		*bStartupAED = true;
	}
	else if( startupAED == "over" )
	{
		*bStartupAED = false;
	}
	else
	{
		*bStartupAED = indeterminate;
	}
	return true;
}
