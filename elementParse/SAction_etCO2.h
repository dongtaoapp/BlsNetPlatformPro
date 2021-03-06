#pragma once
#include <string>
#include <pugixml.hpp>
#include ".\elementParse_global.h"

/*-----------------------------------------------------------------------------------------------------------------
类说明：     呼出末二氧化碳分压数值解析类
创建人：	 hjg
创建时间：   2017.2.6
//-----------------------------------------------------------------------------------------------------------------*/
class AFX_EXT_CLASS CSAction_etCO2
{
public:
	CSAction_etCO2(void);
	~CSAction_etCO2(void);
public:
	static bool isAction_etCO2(const std::string &caption);
	static std::string getAction_etCO2_Caption() { return "Action_etCO2"; };
	// 将属性保存到字符窜中
	static std::string saveParams(long lEtCO2Value);
	static void saveParamsToXML(pugi::xml_node* pXMLEtCO2Child, long lEtCO2Value);
	static bool explainParamsFromXML(pugi::xml_node* pXMLEtCO2Child,/*out*/long *lEtCO2Value); 
};
