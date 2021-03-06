#include ".\SEvent_Pace.h"

#include <sstream>
#include <boost/format.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>


using namespace boost::property_tree;
CSEvent_Pace::CSEvent_Pace(void)
{
}


CSEvent_Pace::~CSEvent_Pace(void)
{
}

bool CSEvent_Pace::isEvent_Pace(const std::string &caption)
{
	if( caption == getEvent_Pace_Caption() )
		return true;
	return false;
}

// 将属性保存到字符窜中
std::string CSEvent_Pace::saveParams(short iSign, short sTime)
{
	boost::format  fmt;
	if( sTime != 0 )
	{
		fmt.parse("<Event_Pace state=\"%d\" time=\"%d\" />");
		fmt % iSign % sTime;
	}
	else
	{
		fmt.parse("<Event_Pace state=\"%d\" />");
		fmt % iSign;
	}
	return fmt.str();
}

void CSEvent_Pace::saveParamsToXML(pugi::xml_node* pXMLPaceChild, short iSign, short sTime)
{
	if( sTime != 0 )
	{
		pXMLPaceChild->append_attribute("state").set_value(iSign);
		//时间
		pXMLPaceChild->append_attribute("time").set_value(sTime);
	}
	else
	{
		pXMLPaceChild->append_attribute("state").set_value(iSign);
	}
}

bool CSEvent_Pace::explainParamsFromXML(pugi::xml_node* pXMLPaceChild, /*out*/short *iSign, /*out*/short *sTime)
{
	*iSign = pXMLPaceChild->attribute("state").as_int(0);
	//时间
	*sTime = pXMLPaceChild->attribute("time").as_int(0);
	return true;
}

bool CSEvent_Pace::explainSimulateTriggerPaceEvent(const std::string &paceTriggerXML, /*out*/short *iSign, /*out*/short *sTime)
{
	std::istringstream  istr(paceTriggerXML);
	try
	{
		ptree  pt;
		read_xml(istr, pt);
		//
		*iSign = pt.get<short>("Event_Pace.<xmlattr>.state");
		//时间
		*sTime =  pt.get<short>("Event_Pace.<xmlattr>.time");
	}
	catch (...)
	{
		return false;
	}
	return true;
}
