#include ".\SAction_ContactPatient.h"

#include <boost/format.hpp>

CSAction_ContactPatient::CSAction_ContactPatient(void)
{
}

CSAction_ContactPatient::~CSAction_ContactPatient(void)
{
}

bool CSAction_ContactPatient::isAction_ContactPatient(const std::string &caption)
{
	if( caption == getAction_ContactPatient_Caption() )
	{
		return true;
	}
	return false;
}

// 将属性保存到字符窜中
std::string CSAction_ContactPatient::saveParams(bool bContact)
{
	boost::format  xmlContactPatient("<Action_ContactPatient value=\"%s\" />");
	xmlContactPatient % (bContact ? "contact" : "uncontact") ;
	return xmlContactPatient.str();
}

void CSAction_ContactPatient::saveParamsToXML(pugi::xml_node* pXMLContactPatientChild, bool bContact)
{
	pXMLContactPatientChild->append_attribute("value").set_value(bContact ? "contact" : "uncontact");
}

bool CSAction_ContactPatient::explainParamsFromXML(pugi::xml_node* pXMLContactPatientChild, /*out*/bool *bContact)
{
	std::string  contactPatient = pXMLContactPatientChild->attribute("value").as_string("contact");
	if( contactPatient == "contact")
	{
		*bContact = true;
	}
	else
	{
		*bContact = false;
	}
	return true;
}
