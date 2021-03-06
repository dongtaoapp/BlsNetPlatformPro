#include ".\SAction_Osat.h"

#include <boost/format.hpp>

CSAction_Osat::CSAction_Osat(void)
{
}


CSAction_Osat::~CSAction_Osat(void)
{
}

bool CSAction_Osat::isAction_Osat(const std::string &caption)
{
	if( caption == getAction_Osat_Caption() )
		return true;
	return false;
}

std::string CSAction_Osat::saveParams(long lOsatValue)
{
	boost::format  xmlOsat("<Action_Osat value=\"%d\" />");
	xmlOsat % lOsatValue ;
	return xmlOsat.str();
}

void CSAction_Osat::saveParamsToXML(pugi::xml_node* pXMLOsatChild, long lOsatValue)
{
	pXMLOsatChild->append_attribute("value").set_value(lOsatValue);
}

bool CSAction_Osat::explainParamsFromXML(pugi::xml_node* pXMLOsatChild, /*out*/long *lOsatValue)
{
	*lOsatValue = pXMLOsatChild->attribute("value").as_int();
	return true;
}
