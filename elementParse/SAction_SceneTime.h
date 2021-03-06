#pragma once
#include <string>
#include <pugixml.hpp>
#include ".\elementParse_global.h"

/*-----------------------------------------------------------------------------------------------------------------
类说明：     脚本运行时间设定
创建人：	 hjg
创建时间：   2013/8/23
//-----------------------------------------------------------------------------------------------------------------*/
class AFX_EXT_CLASS CSAction_SceneTime
{
public:
	CSAction_SceneTime(void);
	virtual ~CSAction_SceneTime(void);
public:
	static bool isAction_SceneTime(const std::string &caption);
	static std::string getAction_SceneTime_Caption() { return "Action_SceneTime"; };
	// 将属性保存到字符窜中
	static std::string saveParams( long lTimeValue);
	static void saveParamsToXML(pugi::xml_node* pXMLSceneTimeChild, long lTimeValue);
	static bool explainParamsFromXML(pugi::xml_node* pXMLSceneTimeChild, /*out*/long *lTimeValue);
};

