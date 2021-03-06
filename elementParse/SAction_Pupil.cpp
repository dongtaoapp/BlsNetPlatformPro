#include ".\saction_pupil.h"

#include <boost/format.hpp>

CSAction_Pupil::CSAction_Pupil(void)
{
}

CSAction_Pupil::~CSAction_Pupil(void)
{
}

bool CSAction_Pupil::isAction_Pupil(const std::string &caption)
{
	if( caption == getAction_Pupil_Caption() )
		return true;
	return false;
}

// 将属性保存到字符串中
std::string CSAction_Pupil::saveParams(bool bNatural)
{
	boost::format fmt("<Action_Pupil state=\"%s\" />");
	fmt % (bNatural ? "normal" : "mydriasis");
	return fmt.str();
}

void CSAction_Pupil::saveParamsToXML(pugi::xml_node* pXMLPupilChild, bool bNatural)
{
	pXMLPupilChild->append_attribute("state").set_value(bNatural ? "normal" : "mydriasis" );
}

bool CSAction_Pupil::explainParamsFromXML(pugi::xml_node* pXMLPupilChild, /*out*/bool *bNatural)
{
	std::string  pupilStat = pXMLPupilChild->attribute("state").as_string("normal");
	if( pupilStat == "normal" )
	{
		*bNatural = true;
	}
	else
	{
		*bNatural = false;
	}
	return true;
}
