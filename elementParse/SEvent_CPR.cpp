#include ".\SEvent_CPR.h"

#include <boost/format.hpp>

CSEvent_CPR::CSEvent_CPR(void)
{
}


CSEvent_CPR::~CSEvent_CPR(void)
{
}

bool CSEvent_CPR::isEvent_CPR(const std::string &caption)
{
	if( caption == getEvent_CPR_Caption() )
		return true;
	return false;
}

// 将属性保存到字符窜中
std::string CSEvent_CPR::saveParams(short iSel, short sParamValue, short sAccumulateNum)
{
	boost::format  fmt;
    return "";
}

void CSEvent_CPR::saveParamsToXML(pugi::xml_node* pXMLCPRChild, short iSel, short sParamValue, short sAccumulateNum)
{

}

bool CSEvent_CPR::explainParamsFromXML(pugi::xml_node* pXMLCPRChild, /*out*/short *iSel, /*out*/short *sParamValue, /*out*/short *sAccumulateNum)
{
	return false;
}
