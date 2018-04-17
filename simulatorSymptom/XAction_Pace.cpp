#include <boost/format.hpp>
#include ".\xaction_pace.h"

#include "..\ElementParse\SAction_Pace.h"


namespace jysoft { namespace simulator 
{
	CXAction_Pace::CXAction_Pace(void)
	{
	}

	CXAction_Pace::CXAction_Pace(bool bEnablePace, short sData)
	{	
		m_bEnablePace = bEnablePace;
		m_sData       = sData;
	}

	CXAction_Pace::~CXAction_Pace(void)
	{
	}

	bool CXAction_Pace::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXAction_Pace" )
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
	std::string CXAction_Pace::getActionCaption() const
	{
		return CSAction_Pace::getAction_Pace_Caption();
	}

	/*******************************************************************************/
	// 函数名称： Parse_ActionFromXml
	// 功能：   解析体征参数内容
	// 参数：   IXMLDOMNode *pXMLShapeNode:
	// 返回值: 
	bool CXAction_Pace::Parse_ActionFromXml(pugi::xml_node* pXMLShapeNode)
	{
		bool bParseSec = CSAction_Pace::explainParamsFromXML( pXMLShapeNode, /*out*/&m_bEnablePace, /*out*/&m_sData);
		return bParseSec ;
	}

	/*******************************************************************************/
	// 函数名称： CombineActionParam
	// 功能：   整合体征设置参数
	// 参数：   CXActionVirtual *pDstActionVir:
	// 返回值: 
	void CXAction_Pace::CombineActionParam(CXActionVirtual *pDstActionVir)
	{
	#ifdef  _DEBUG
		if( getActionCaption() != pDstActionVir->getActionCaption() )
			BOOST_ASSERT( 0 );
	#endif
		CXAction_Pace  *pDstAction_Pace = (CXAction_Pace  *)pDstActionVir;
		//是否能起搏
		m_bEnablePace   = pDstAction_Pace->GetValue_EnablePace();
		//起搏电流量
		m_sData         = pDstAction_Pace->GetValue_PaceElectricData();
	}

	/*******************************************************************************/
	// 函数名称： CloneAction
	// 功能：   拷贝体征参数
	// 参数：   
	// 返回值: 
	CXActionVirtual * CXAction_Pace::CloneAction()
	{
		CXAction_Pace *pNewAction = new CXAction_Pace(m_bEnablePace, m_sData);
		return pNewAction;
	}
}}
