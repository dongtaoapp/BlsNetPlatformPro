#include ".\saction_etco2.h"

#include <boost/format.hpp>

CSAction_etCO2::CSAction_etCO2(void)
{
}

CSAction_etCO2::~CSAction_etCO2(void)
{
}

bool CSAction_etCO2::isAction_etCO2(const std::string &caption)
{
	if( caption == getAction_etCO2_Caption() )
	{
		return true;
	}
	return false;
}

// 将属性保存到字符窜中
std::string CSAction_etCO2::saveParams(long lEtCO2Value)
{
	boost::format fmt("<Action_etCO2 value=\"%d\" />");
	fmt % lEtCO2Value ;
	return fmt.str();
}

void CSAction_etCO2::saveParamsToXML(pugi::xml_node* pXMLEtCO2Child, long lEtCO2Value)
{
	pXMLEtCO2Child->append_attribute("value").set_value(lEtCO2Value);
}

bool CSAction_etCO2::explainParamsFromXML(pugi::xml_node*pXMLEtCO2Child,/*out*/long *lEtCO2Value)
{
	*lEtCO2Value = pXMLEtCO2Child->attribute("value").as_int();
	return true;
}
