#pragma once
#include <string>
#include <pugixml.hpp>
#include ".\elementParse_global.h"

/*-----------------------------------------------------------------------------------------------------------------
类说明：     有创血压解析类，NIBP为ABP在1分钟内的均值，脉搏跳动强度 
创建人：	 hjg
创建时间：   
//-----------------------------------------------------------------------------------------------------------------*/

class AFX_EXT_CLASS CSAction_ABP
{
public:
	CSAction_ABP(void);
	~CSAction_ABP(void);
public:
	static bool isAction_BP(const std::string &caption);
	static std::string getAction_BP_Caption() { return "Action_BP"; };
	// 将属性保存到字符窜中
	static std::string saveParams(long lShrinkValue, long lStretchValue);
	static void saveParamsToXML(pugi::xml_node* pXMLABPChild, long lShrinkValue, long lStretchValue);
	static bool explainParamsFromXML(pugi::xml_node* pXMLABPChild, long *lShrinkValue, /*out*/long *lStretchValue); 
};
