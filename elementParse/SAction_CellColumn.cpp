#include ".\SAction_CellColumn.h"

#include <boost/format.hpp>

CSAction_CellColumn::CSAction_CellColumn(void)
{
}

CSAction_CellColumn::~CSAction_CellColumn(void)
{
}

bool CSAction_CellColumn::isAction_CellColumn(const std::string &caption)
{
	if( caption == getAction_CellColumn_Caption() )
	{
		return true;
	}
	return false;
}

// 将属性保存到字符窜中
std::string CSAction_CellColumn::saveParams(bool bNatural)
{
	boost::format  xmlCellColumn("<Action_CellColumn value=\"%s\" />");
	xmlCellColumn % (bNatural ? "natural" : "insuff") ;
	return xmlCellColumn.str();
}

void CSAction_CellColumn::saveParamsToXML(pugi::xml_node* pXMLCellColumnChild, bool bNatural)
{
	pXMLCellColumnChild->append_attribute("value").set_value(bNatural ? "natural" : "insuff");
}

bool CSAction_CellColumn::explainParamsFromXML(pugi::xml_node* pXMLCellColumnChild, /*out*/bool *bNatural)
{
	std::string  cellColumn = pXMLCellColumnChild->attribute("value").as_string("natural");
	if( cellColumn == "natural")
	{
		*bNatural = true;
	}
	else
	{
		*bNatural = false;
	}
	return true;
}
