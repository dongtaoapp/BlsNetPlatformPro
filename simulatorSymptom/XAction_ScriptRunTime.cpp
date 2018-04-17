#include ".\XAction_ScriptRunTime.h"

#include "..\ElementParse\SAction_SceneTime.h"


namespace jysoft { namespace simulator 
{
	CXAction_ScriptRunTime::CXAction_ScriptRunTime(void)
	{
		m_lSceneRunTime = 0;
	}

	CXAction_ScriptRunTime::~CXAction_ScriptRunTime(void)
	{
	}

	bool CXAction_ScriptRunTime::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXAction_ScriptRunTime" )
		{
			return true;
		}
		return CXActionVirtual::isActionNameOf( strClassName );
	}

	/*******************************************************************************/
	// 函数名称： GetActionCaption
	// 功能：   返回体征标识名
	// 参数：   
	// 返回值: 
	std::string CXAction_ScriptRunTime::getActionCaption() const
	{
		return CSAction_SceneTime::getAction_SceneTime_Caption();
	}

	/*******************************************************************************/
	// 函数名称： Parse_ActionFromXml
	// 功能：   解析体征参数内容
	// 参数：   IXMLDOMNode *pXMLShapeNode:
	// 返回值: 
	bool CXAction_ScriptRunTime::Parse_ActionFromXml(pugi::xml_node* pXMLShapeNode)
	{
		bool bParseSec = CSAction_SceneTime::explainParamsFromXML(pXMLShapeNode, &m_lSceneRunTime);
		return bParseSec ;
	}

	/*******************************************************************************/
	// 函数名称： CombineActionParam
	// 功能：   整合体征设置参数
	// 参数：   CXActionVirtual *pDstActionVir:
	// 返回值: 
	void CXAction_ScriptRunTime::CombineActionParam(CXActionVirtual *pDstActionVir)
	{
	#ifdef  _DEBUG
		if( getActionCaption() != pDstActionVir->getActionCaption() )
			BOOST_ASSERT( 0 );
	#endif
		CXAction_ScriptRunTime  *pDestAction_SeceneTime = (CXAction_ScriptRunTime *)pDstActionVir;
		m_lSceneRunTime = pDestAction_SeceneTime->GetValue_SceneRunTime();
	}

	/*******************************************************************************/
	// 函数名称： CloneAction
	// 功能：   拷贝体征参数
	// 参数：   
	// 返回值: 
	CXActionVirtual * CXAction_ScriptRunTime::CloneAction()
	{
		CXAction_ScriptRunTime   *pCloneAction = new CXAction_ScriptRunTime();
		pCloneAction->SetValue_SceneRunTime( m_lSceneRunTime );
		return pCloneAction;
	}
}}
