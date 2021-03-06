#include ".\SEvent_Pulse.h"

#include <sstream>
#include <boost/format.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>


using namespace boost::property_tree;
CSEvent_Pulse::CSEvent_Pulse(void)
{
}

CSEvent_Pulse::~CSEvent_Pulse(void)
{
}

bool CSEvent_Pulse::isEvent_Pulse(const std::string &caption)
{
	if( caption == getEvent_Pulse_Caption() )
		return true;
	return false;
}

// 将属性保存到字符窜中
std::string CSEvent_Pulse::saveParams(short sPulseCount, short sPulseAct)
{
	boost::format  fmt("<Event_PulseCheck pulseCount=\"1\" act=\"%d\" />");
	fmt % sPulseCount % sPulseAct;
	return fmt.str();
}

void CSEvent_Pulse::saveParamsToXML(pugi::xml_node* pXMLPulseChild, short sPulseCount, short sPulseAct)
{
	pXMLPulseChild->append_attribute("pulseCount").set_value(sPulseCount);
	pXMLPulseChild->append_attribute("act").set_value(sPulseAct);
}

bool CSEvent_Pulse::explainParamsFromXML(pugi::xml_node* pXMLPulseChild, /*out*/short *sPulseCount, /*out*/short *sPulseAct)
{
	//次数
	*sPulseCount = pXMLPulseChild->attribute("pulseCount").as_int( 1 );
	//动作
	*sPulseAct = pXMLPulseChild->attribute("act").as_int(0x01);
	return true;
}

bool CSEvent_Pulse::explainSimulateTriggerPulseEvent(const std::string &pulseTriggerXML, /*out*/short *sPulseCount, /*out*/short *sPulseAct)
{
	std::istringstream  istr(pulseTriggerXML);
	try
	{
		ptree  pt;
		read_xml(istr, pt);
		//
		*sPulseCount = pt.get<short>("Event_PulseCheck.<xmlattr>.pulseCount");
		//动作
		*sPulseAct =  pt.get<short>("Event_PulseCheck.<xmlattr>.act");
	}
	catch (...)
	{
		return false;
	}
	return true;
}
