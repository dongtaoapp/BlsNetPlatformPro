#include ".\xaction_frametime.h"

#include "..\ElementParse\SAction_FrameTime.h"


namespace jysoft { namespace simulator 
{
	CXAction_FrameTime::CXAction_FrameTime(void)
	{
		m_lFrameTime = 0;
	}

	CXAction_FrameTime::~CXAction_FrameTime(void)
	{
	}

	bool CXAction_FrameTime::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXAction_FrameTime" )
		{
			return true;
		}
		return CXActionVirtual::isActionNameOf( strClassName );
	}

	/*******************************************************************************/
	// 函数名称： getActionCaption
	// 功能：   返回体征标识名
	// 参数：   
	// 返回值: 
	std::string CXAction_FrameTime::getActionCaption() const
	{
		return CSAction_FrameTime::getAction_FrameTime_Caption();
	}
	/*******************************************************************************/
	// 函数名称： Parse_ActionFromXml
	// 功能：   解析体征参数内容
	// 参数：   IXMLDOMNode *pXMLShapeNode:
	// 返回值: 
	bool CXAction_FrameTime::Parse_ActionFromXml(pugi::xml_node* pXMLShapeNode)
	{
		bool bParseSec = CSAction_FrameTime::explainParamsFromXML(pXMLShapeNode, &m_lFrameTime);
		return bParseSec;
	}
	/*******************************************************************************/
	// 函数名称： CombineActionParam
	// 功能：   整合体征设置参数
	// 参数：   CXActionVirtual *pDstActionVir:
	// 返回值: 
	void CXAction_FrameTime::CombineActionParam(CXActionVirtual *pDstActionVir)
	{
	#ifdef  _DEBUG
		if( getActionCaption() != pDstActionVir->getActionCaption() )
			BOOST_ASSERT( 0 );
	#endif
		CXAction_FrameTime  *pDestAction_FrameTime = (CXAction_FrameTime *)pDstActionVir;
		m_lFrameTime = pDestAction_FrameTime->GetValue_FrameTime();
	}
	/*******************************************************************************/
	// 函数名称： CloneAction
	// 功能：   拷贝体征参数
	// 参数：   
	// 返回值: 
	CXActionVirtual * CXAction_FrameTime::CloneAction()
	{
		CXAction_FrameTime   *pCloneAction = new CXAction_FrameTime();
		pCloneAction->SetValue_FrameTime( m_lFrameTime );
		return pCloneAction;
	}
}}
