#include ".\SAction_Electrode.h"

#include <boost/format.hpp>

CSAction_Electrode::CSAction_Electrode(void)
{
}

CSAction_Electrode::~CSAction_Electrode(void)
{
}

bool CSAction_Electrode::isAction_Electrode(const std::string &caption)
{
	if( caption == getAction_Electrode_Caption() )
	{
		return true;
	}
	return false;
}

// 将属性保存到字符窜中
std::string  CSAction_Electrode::saveParams(bool bPosRight)
{
	boost::format  fmt("<Action_Electrode state=\"%s\" />");
	fmt % (bPosRight ? "normal" : "relax");
	return fmt.str();
}

void  CSAction_Electrode::saveParamsToXML(pugi::xml_node* pXMElectrodeChild, bool bPosRight)
{
	pXMElectrodeChild->append_attribute("state").set_value( bPosRight ? "normal" : "relax" );
}

bool  CSAction_Electrode::explainParamsFromXML(pugi::xml_node* pXMElectrodeChild, /*out*/bool *bPosRight)
{
	std::string  posRight = pXMElectrodeChild->attribute("state").as_string("normal");
	if( posRight == "normal" )
	{
		*bPosRight = true;
	}
	else
	{
		*bPosRight = false;
	}
	return true;
}
