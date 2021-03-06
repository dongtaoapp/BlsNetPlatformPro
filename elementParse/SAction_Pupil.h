#pragma once
#include <string>
#include <pugixml.hpp>
#include ".\elementParse_global.h"

/*-----------------------------------------------------------------------------------------------------------------
类说明：     瞳孔解析类
创建人：	 hjg
创建时间：   2017.2.6
//-----------------------------------------------------------------------------------------------------------------*/
class AFX_EXT_CLASS CSAction_Pupil
{
public:
	CSAction_Pupil(void);
	~CSAction_Pupil(void);
public:
	static bool isAction_Pupil(const std::string &caption);
	static std::string getAction_Pupil_Caption() { return "Action_Pupil"; };
	// 将属性保存到字符串中
	static std::string saveParams(bool bNatural);
	static void saveParamsToXML(pugi::xml_node* pXMLPupilChild, bool bNatural);
	static bool explainParamsFromXML(pugi::xml_node* pXMLPupilChild, /*out*/bool *bNatural); 
};
