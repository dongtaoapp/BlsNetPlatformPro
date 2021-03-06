#include ".\SEvent_Thump.h"


CSEvent_Thump::CSEvent_Thump(void)
{
}

CSEvent_Thump::~CSEvent_Thump(void)
{
}

bool CSEvent_Thump::isAction_Thump(const std::string &caption)
{
	if( caption == getAction_Thump_Caption() )
		return true;
	return false;
}

// 将属性保存到字符窜中
std::string CSEvent_Thump::saveParams()
{
	return "<Action_Thump act=\"1\" />";
}

void CSEvent_Thump::saveParamsToXML(pugi::xml_node* pXMLThumpChild )
{
	pXMLThumpChild->append_attribute("act").set_value( 1 );
}

bool CSEvent_Thump::explainParamsFromXML(pugi::xml_node* pXMLThumpChild, /*out*/bool *bThumpAct)
{
	*bThumpAct = pXMLThumpChild->attribute("act").as_int(0x01) ? true : false;
	return true;
}
