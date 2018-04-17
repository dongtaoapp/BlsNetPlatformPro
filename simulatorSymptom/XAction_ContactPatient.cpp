#include ".\XAction_ContactPatient.h"

#include "..\elementParse\SAction_ContactPatient.h"


namespace jysoft { namespace simulator 
{
	CXAction_ContactPatient::CXAction_ContactPatient(void)
	{
		m_bContactPatient = false;
	}
	
	CXAction_ContactPatient::~CXAction_ContactPatient(void)
	{
	}

	bool CXAction_ContactPatient::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXAction_ContactPatient" )
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
	std::string CXAction_ContactPatient::getActionCaption() const
	{
		return CSAction_ContactPatient::getAction_ContactPatient_Caption();
	}

	/*******************************************************************************/
	// 函数名称： Parse_ActionFromXml
	// 功能：   解析体征参数内容
	// 参数：   IXMLDOMNode *pXMLShapeNode:
	// 返回值: 
	bool CXAction_ContactPatient::Parse_ActionFromXml(pugi::xml_node* pXMLShapeNode)
	{
		return CSAction_ContactPatient::explainParamsFromXML(pXMLShapeNode, &m_bContactPatient);
	}

	/*******************************************************************************/
	// 函数名称： CombineActionParam
	// 功能：   整合体征设置参数
	// 参数：   CXActionVirtual *pDstActionVir:
	// 返回值: 
	void CXAction_ContactPatient::CombineActionParam(CXActionVirtual *pDstActionVir)
	{
	#ifdef  _DEBUG
		if( getActionCaption() != pDstActionVir->getActionCaption() )
			BOOST_ASSERT( 0 );
	#endif
		CXAction_ContactPatient  *pDestAction_ContactPatient = ( CXAction_ContactPatient  * )pDstActionVir;
		m_bContactPatient = pDestAction_ContactPatient->m_bContactPatient;
	}

	/*******************************************************************************/
	// 函数名称： CloneAction
	// 功能：   拷贝体征参数
	// 参数：   
	// 返回值: 
	CXActionVirtual * CXAction_ContactPatient::CloneAction()
	{
		CXAction_ContactPatient  *pNewAction = new CXAction_ContactPatient();
		pNewAction->m_bContactPatient = m_bContactPatient;
		return pNewAction;
	}
}}
