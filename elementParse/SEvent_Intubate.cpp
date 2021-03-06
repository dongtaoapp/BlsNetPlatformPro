#include ".\SEvent_Intubate.h"

#include <sstream>
#include <boost/format.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

using namespace boost::property_tree;
CSEvent_Intubate::CSEvent_Intubate(void)
{
}

CSEvent_Intubate::~CSEvent_Intubate(void)
{
}

bool CSEvent_Intubate::isEvent_Intubate(const std::string &caption)
{
	if( caption == getEvent_Intubate_Caption() )
		return true;
	return false;
}

// 将属性保存到字符窜中
std::string CSEvent_Intubate::saveParams(short sPosition, short sAct)
{
	boost::format  fmt("<Event_Intubate position=\"%d\" act=\"%d\" />");
	fmt % sPosition % sAct;
	return fmt.str();
}

/*******************************************************************************/
// 功能： 
// 参数： 
//        /*out*/short *sPosition: 插管位置：气管(0x01)；右肺组织(0x02)
//        /*out*/short *sAct:      插管动作：插入(0x00)；拔出(0x11)；
// 返回值:  
void CSEvent_Intubate::saveParamsToXML(pugi::xml_node* pXMLIntubateChild, short sPosition, short sAct)
{
	pXMLIntubateChild->append_attribute("position").set_value(sPosition);
	pXMLIntubateChild->append_attribute("act").set_value(sAct);
}

bool CSEvent_Intubate::explainParamsFromXML(pugi::xml_node* pXMLIntubateChild, /*out*/short *sPosition, /*out*/short *sAct)
{
	//插管位置
	*sPosition = pXMLIntubateChild->attribute("position").as_int(0x01);
	//动作
	*sAct = pXMLIntubateChild->attribute("act").as_int(0x00);
	return true;
}

bool CSEvent_Intubate::explainSimulateTriggerIntubateEvent(const std::string &intubateTriggerXML, /*out*/short *sPosition, /*out*/short *sAct)
{
	std::istringstream  istr(intubateTriggerXML);
	try
	{
		ptree  pt;
		read_xml(istr, pt);
		//插管位置
		*sPosition = pt.get<short>("Event_Intubate.<xmlattr>.position");
		//动作
		*sAct =  pt.get<short>("Event_Intubate.<xmlattr>.act");
	}
	catch (...)
	{
		return false;
	}
	return true;
}
