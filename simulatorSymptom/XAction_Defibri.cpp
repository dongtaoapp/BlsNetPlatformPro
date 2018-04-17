#include ".\xaction_defibri.h"

#include "..\elementParse\SAction_Defibrillate.h"


namespace jysoft { namespace simulator 
{
	CXAction_Defibri::CXAction_Defibri(void)
	{
	}

	CXAction_Defibri::CXAction_Defibri(bool fEnableDefibr, bool bClearCount)
	{
		m_bEnableDefibri  = fEnableDefibr;
		m_bClearCount     = bClearCount;
	}

	CXAction_Defibri::~CXAction_Defibri(void)
	{
	}

	bool CXAction_Defibri::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXAction_Defibri" )
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
	std::string CXAction_Defibri::getActionCaption() const
	{
		return CSAction_Defibrillate::getAction_Defibri_Caption();
	}
	/*******************************************************************************/
	// 函数名称： Parse_ActionFromXml
	// 功能：   解析体征参数内容
	// 参数：   IXMLDOMNode *pXMLShapeNode:
	// 返回值: 
	bool CXAction_Defibri::Parse_ActionFromXml(pugi::xml_node* pXMLShapeNode)
	{
		bool bParseSec = CSAction_Defibrillate::explainParamsFromXML(pXMLShapeNode, /*out*/&m_bEnableDefibri, /*out*/&m_bClearCount);
		return bParseSec ;
	}

	/*******************************************************************************/
	// 函数名称： CombineActionParam
	// 功能：   整合体征设置参数
	// 参数：   CXActionVirtual *pDstActionVir:
	// 返回值: 
	void CXAction_Defibri::CombineActionParam(CXActionVirtual *pDstActionVir)
	{
	#ifdef  _DEBUG
		if( getActionCaption() != pDstActionVir->getActionCaption() )
			BOOST_ASSERT( 0 );
	#endif
		CXAction_Defibri *pDstAction_Defibri = (CXAction_Defibri *)pDstActionVir;
		//是否能除颤
		m_bEnableDefibri  = pDstAction_Defibri->getValue_EnableDefibri();
		//去除除颤次数
		m_bClearCount     = pDstAction_Defibri->getValue_ClearCount();
	}

	/*******************************************************************************/
	// 函数名称： CloneAction
	// 功能：   拷贝体征参数
	// 参数：   
	// 返回值: 
	CXActionVirtual * CXAction_Defibri::CloneAction()
	{
		CXAction_Defibri *pNewAction = new CXAction_Defibri(m_bEnableDefibri, m_bClearCount);
		return pNewAction;
	}
}}
