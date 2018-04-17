#include ".\XAction_CPR.h"


namespace jysoft { namespace simulator 
{
	CXAction_CPR::CXAction_CPR(void)
	{
	}

	CXAction_CPR::~CXAction_CPR(void)
	{
	}

	bool CXAction_CPR::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXAction_CPR" )
		{
			return true;
		}
		return CXActionVirtual::isKindOf( strClassName );
	}

	/*******************************************************************************/
	// 函数名称： GetActionCaption
	// 功能：   返回体征标识名
	// 参数：   
	// 返回值: 
	std::string CXAction_CPR::getActionCaption() const
	{
        return "";
	}

	/*******************************************************************************/
	// 函数名称： Parse_ActionFromXml
	// 功能：   解析体征参数内容
	// 参数：   IXMLDOMNode *pXMLShapeNode:
	// 返回值: 
	bool CXAction_CPR::Parse_ActionFromXml(pugi::xml_node* pXMLShapeNode)
	{
		return false;
	}

	/*******************************************************************************/
	// 函数名称： CombineActionParam
	// 功能：   整合体征设置参数
	// 参数：   CXActionVirtual *pDstActionVir:
	// 返回值: 
	void CXAction_CPR::CombineActionParam(CXActionVirtual *pDstActionVir)
	{
	}

	/*******************************************************************************/
	// 函数名称： CloneAction
	// 功能：   拷贝体征参数
	// 参数：   
	// 返回值: 
	CXActionVirtual * CXAction_CPR::CloneAction()
	{
		return NULL;
	}
}}
