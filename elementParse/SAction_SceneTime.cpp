#include ".\SAction_SceneTime.h"

#include <boost/format.hpp>


CSAction_SceneTime::CSAction_SceneTime(void)
{
}


CSAction_SceneTime::~CSAction_SceneTime(void)
{
}

bool CSAction_SceneTime::isAction_SceneTime(const std::string &caption)
{
	if( caption == getAction_SceneTime_Caption() )
	{
		return true;
	}
	return false;
}

// 将属性保存到字符窜中
std::string CSAction_SceneTime::saveParams( long lTimeValue)
{
	boost::format  fmt("<Action_SceneTime value=\"%d\" />");
	fmt % lTimeValue;
	return fmt.str();
}

void CSAction_SceneTime::saveParamsToXML(pugi::xml_node* pXMLSceneTimeChild, long lTimeValue)
{
	pXMLSceneTimeChild->append_attribute("value").set_value(lTimeValue);
}

bool CSAction_SceneTime::explainParamsFromXML(pugi::xml_node* pXMLSceneTimeChild, /*out*/long *lTimeValue)
{
	*lTimeValue = pXMLSceneTimeChild->attribute("value").as_int();
	return true;
}
