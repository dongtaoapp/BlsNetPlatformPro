#include ".\XAction_Electrode.h"

#include "..\elementParse\SAction_Electrode.h"


namespace jysoft { namespace simulator 
{
	CXAction_Electrode::CXAction_Electrode(void)
	{
		m_bPosRight = true;
	}

	CXAction_Electrode::~CXAction_Electrode(void)
	{
	}

	bool CXAction_Electrode::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXAction_Electrode" )
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
	std::string CXAction_Electrode::getActionCaption() const
	{
		return CSAction_Electrode::getAction_Electrode_Caption();
	}

	/*******************************************************************************/
	// 函数名称： Parse_ActionFromXml
	// 功能：   解析体征参数内容
	// 参数：   IXMLDOMNode *pXMLShapeNode:
	// 返回值: 
	bool CXAction_Electrode::Parse_ActionFromXml(pugi::xml_node* pXMLShapeNode)
	{
		return CSAction_Electrode::explainParamsFromXML(pXMLShapeNode, &m_bPosRight);
	}

	/*******************************************************************************/
	// 函数名称： CombineActionParam
	// 功能：   整合体征设置参数
	// 参数：   CXActionVirtual *pDstActionVir:
	// 返回值: 
	void CXAction_Electrode::CombineActionParam(CXActionVirtual *pDstActionVir)
	{
	#ifdef  _DEBUG
		if( getActionCaption() != pDstActionVir->getActionCaption() )
			BOOST_ASSERT( 0 );
	#endif
		CXAction_Electrode *pDstAction_Electrode = (CXAction_Electrode *)pDstActionVir;

		m_bPosRight = pDstAction_Electrode->m_bPosRight;
	}

	/*******************************************************************************/
	// 函数名称： CloneAction
	// 功能：   拷贝体征参数
	// 参数：   
	// 返回值: 
	CXActionVirtual * CXAction_Electrode::CloneAction()
	{
		CXAction_Electrode *pNewAction = new CXAction_Electrode();
		pNewAction->m_bPosRight = m_bPosRight;
		return pNewAction;
	}
}}
