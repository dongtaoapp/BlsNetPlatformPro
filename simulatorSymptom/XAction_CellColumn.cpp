#include ".\XAction_CellColumn.h"

#include "..\elementParse\SAction_CellColumn.h"


namespace jysoft { namespace simulator 
{
	CXAction_CellColumn::CXAction_CellColumn(void)
	{
	}

	CXAction_CellColumn::~CXAction_CellColumn(void)
	{
	}

	bool CXAction_CellColumn::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXAction_CellColumn" )
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
	std::string CXAction_CellColumn::getActionCaption() const
	{
		return CSAction_CellColumn::getAction_CellColumn_Caption();
	}

	/*******************************************************************************/
	// 函数名称： Parse_ActionFromXml
	// 功能：   解析体征参数内容
	// 参数：   IXMLDOMNode *pXMLShapeNode:
	// 返回值: 
	bool CXAction_CellColumn::Parse_ActionFromXml(pugi::xml_node* pXMLShapeNode)
	{
		return CSAction_CellColumn::explainParamsFromXML( pXMLShapeNode, /*out*/&m_bNatural);
	}

	/*******************************************************************************/
	// 函数名称： CombineActionParam
	// 功能：   整合体征设置参数
	// 参数：   CXActionVirtual *pDstActionVir:
	// 返回值: 
	void CXAction_CellColumn::CombineActionParam(CXActionVirtual *pDstActionVir)
	{
	#ifdef  _DEBUG
		if( getActionCaption() != pDstActionVir->getActionCaption() )
			BOOST_ASSERT( 0 );
	#endif
		CXAction_CellColumn  *pDestAction_CellColumn = ( CXAction_CellColumn  * )pDstActionVir;
		m_bNatural = pDestAction_CellColumn->m_bNatural;
	}

	/*******************************************************************************/
	// 函数名称： CloneAction
	// 功能：   拷贝体征参数
	// 参数：   
	// 返回值: 
	CXActionVirtual * CXAction_CellColumn::CloneAction()
	{
		CXAction_CellColumn  *pNewAction = new CXAction_CellColumn();
		pNewAction->m_bNatural = m_bNatural;
		return pNewAction;
	}
}}
