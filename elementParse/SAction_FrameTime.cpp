#include ".\saction_frametime.h"

#include <boost/format.hpp>

CSAction_FrameTime::CSAction_FrameTime(void)
{
}

CSAction_FrameTime::~CSAction_FrameTime(void)
{
}

bool CSAction_FrameTime::isAction_FrameTime(const std::string &caption)
{
	if( caption == getAction_FrameTime_Caption() )
	{
		return true;
	}
	return false;
}

// 将属性保存到字符窜中
std::string CSAction_FrameTime::saveParams( long lTimeValue)
{
	boost::format  fmt("<Action_FrameTime value=\"%d\" />");
	fmt % lTimeValue;
	return fmt.str();
}

void CSAction_FrameTime::saveParamsToXML(pugi::xml_node* pXMLFrameTimeChild, long lTimeValue)
{
	pXMLFrameTimeChild->append_attribute("value").set_value(lTimeValue);
}

bool CSAction_FrameTime::explainParamsFromXML(pugi::xml_node* pXMLFrameTimeChild, /*out*/long *lTimeValue)
{
	*lTimeValue = pXMLFrameTimeChild->attribute("value").as_int();
	return true;
}
