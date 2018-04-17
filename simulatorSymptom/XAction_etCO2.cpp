#include <boost/format.hpp>
#include ".\xaction_etco2.h"

#include "..\ElementParse\SAction_etCO2.h"


namespace jysoft { namespace simulator 
{
	CXAction_etCO2::CXAction_etCO2(void)
	{
	}

	CXAction_etCO2::~CXAction_etCO2(void)
	{
	}

	bool CXAction_etCO2::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXAction_etCO2" )
		{
			return true;
		}
		return CXActionVitalSignVir::isKindOf( strClassName );
	}

	/*******************************************************************************/
	// 函数名称： GetActionCaption
	// 功能：   返回体征标识名
	// 参数：   
	// 返回值: 
	std::string CXAction_etCO2::getActionCaption() const
	{
		return CSAction_etCO2::getAction_etCO2_Caption();
	}

	/*******************************************************************************/
	// 函数名称： Parse_ActionFromXml
	// 功能：   解析体征参数内容
	// 参数：   IXMLDOMNode *pXMLShapeNode:
	// 返回值: 
	bool CXAction_etCO2::Parse_ActionFromXml(pugi::xml_node* pXMLShapeNode)
	{
		return CSAction_etCO2::explainParamsFromXML(pXMLShapeNode, /*out*/&m_lEtCO2Value);
	}

	/*******************************************************************************/
	// 函数名称： CombineActionParam
	// 功能：   整合体征设置参数
	// 参数：   CXActionVirtual *pDstActionVir:
	// 返回值: 
	void CXAction_etCO2::CombineActionParam(CXActionVirtual *pDstActionVir)
	{
	#ifdef  _DEBUG
		if( getActionCaption() != pDstActionVir->getActionCaption() )
			BOOST_ASSERT( 0 );
	#endif
		CXAction_etCO2 *pDstAction_etCO2 = (CXAction_etCO2 *)pDstActionVir;

		m_lEtCO2Value    = pDstAction_etCO2->GetValue_etCO2();
	}

	/*******************************************************************************/
	// 函数名称： CloneAction
	// 功能：   拷贝体征参数
	// 参数：   
	// 返回值: 
	CXActionVirtual * CXAction_etCO2::CloneAction()
	{
		CXAction_etCO2 *pNewAction = new CXAction_etCO2();
		pNewAction->SetValue_etCO2( m_lEtCO2Value );
		return pNewAction;
	}

	long  CXAction_etCO2::GetValue_AbsoluteEtCO2( long lSrcValue )
	{
		long   lEtCO2Value  = m_lEtCO2Value;
		return lEtCO2Value;
	}
}}
