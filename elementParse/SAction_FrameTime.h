#pragma once
#include <string>
#include <pugixml.hpp>
#include ".\elementParse_global.h"

/*-----------------------------------------------------------------------------------------------------------------
类说明：     场景框持续时间解析类
创建人：	 hjg
创建时间：   2017.2.6
//-----------------------------------------------------------------------------------------------------------------*/
class AFX_EXT_CLASS CSAction_FrameTime
{
public:
	CSAction_FrameTime(void);
	virtual ~CSAction_FrameTime(void);
public:
	static bool isAction_FrameTime(const std::string &caption);
	static std::string getAction_FrameTime_Caption() { return "Action_FrameTime"; };
	// 将属性保存到字符窜中
	static std::string saveParams( long lTimeValue);
	static void saveParamsToXML(pugi::xml_node* pXMLFrameTimeChild, long lTimeValue);
	static bool explainParamsFromXML(pugi::xml_node* pXMLFrameTimeChild, /*out*/long *lTimeValue); 
};
