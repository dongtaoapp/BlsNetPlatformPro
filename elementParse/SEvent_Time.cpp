#include ".\SEvent_Time.h"

#include <boost/format.hpp>

CSEvent_Time::CSEvent_Time(void)
{
}

CSEvent_Time::~CSEvent_Time(void)
{
}

bool CSEvent_Time::isEvent_Time(const std::string &caption)
{
	if( caption == getEvent_Time_Caption() )
		return true;
	return false;
}

// 将属性保存到字符窜中
std::string CSEvent_Time::saveParams(bool bSelect, short sTime)
{
	boost::format  fmt("<Event_Time timeType=\"%s\" time=\"%d\" />");
	fmt % ( bSelect ? "FrameTime" : "PatientTime" ) % sTime;
	return fmt.str();
}

void CSEvent_Time::saveParamsToXML(pugi::xml_node* pXMLEventChild, bool bSelect, short sTime)
{
	pXMLEventChild->append_attribute("timeType").set_value( bSelect ? "FrameTime" : "PatientTime" );
	pXMLEventChild->append_attribute("time").set_value( sTime );
}

bool CSEvent_Time::explainParamsFromXML(pugi::xml_node* pXMLEventChild, /*out*/bool *bSelect, /*out*/short *sTime)
{
	std::string  timeMode = pXMLEventChild->attribute("timeType").as_string("FrameTime");
	if( timeMode == "FrameTime" )
	{
		*bSelect = true;
	}
	else
	{
		*bSelect = false;
	}
	//时间
	*sTime = pXMLEventChild->attribute("time").as_int(0x00);
	return true;
}
