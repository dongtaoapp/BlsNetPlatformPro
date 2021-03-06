#include "SAction_Pace.h"

#include <boost/format.hpp>

CSAction_Pace::CSAction_Pace(void)
{
}

CSAction_Pace::~CSAction_Pace(void)
{
}

bool CSAction_Pace::isAction_Pace(const std::string &caption)
{
	if( caption == getAction_Pace_Caption() )
	{
		return true;
	}
	return false;
}

// 将属性保存到字符窜中
std::string CSAction_Pace::saveParams( bool bEnable, short sThreshold)
{
	boost::format  fmt("<Action_Pace set=\"%s\" threshold=\"%d\" />");
	fmt % (bEnable ? "Enable" : "Ignore") % sThreshold;
	return fmt.str();
}

void CSAction_Pace::saveParamsToXML(pugi::xml_node*  pXMLPaceChild, bool bEnable, short sThreshold)
{
	pXMLPaceChild->append_attribute("set").set_value( bEnable ? "Enable" : "Ignore" );
	pXMLPaceChild->append_attribute("threshold").set_value( sThreshold );
}

bool CSAction_Pace::explainParamsFromXML(pugi::xml_node*  pXMLPaceChild, /*out*/bool *bEnable, /*out*/short *sThreshold)
{
	std::string  paceEnable = pXMLPaceChild->attribute("set").as_string("Enable");
	if( paceEnable == "Enable" )
	{
		*bEnable = true;
	}
	else
	{
		*bEnable = false;
	}
	*sThreshold = pXMLPaceChild->attribute("threshold").as_int(10);
	return true;
}
