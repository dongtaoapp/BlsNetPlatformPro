#pragma once
#include <string>
#include <pugixml.hpp>
#include ".\elementParse_global.h"


//AED电池电量
class AFX_EXT_CLASS CSAction_CellColumn
{
public:
	CSAction_CellColumn(void);
	virtual ~CSAction_CellColumn(void);
public:
	static bool isAction_CellColumn(const std::string &caption);
	static std::string getAction_CellColumn_Caption() { return "Action_CellColumn"; };
	// 将属性保存到字符窜中
	static std::string saveParams(bool bNatural);
	static void saveParamsToXML(pugi::xml_node* pXMLCellColumnChild, bool bNatural);
	static bool explainParamsFromXML(pugi::xml_node* pXMLCellColumnChild, /*out*/bool *bNatural); 
};

