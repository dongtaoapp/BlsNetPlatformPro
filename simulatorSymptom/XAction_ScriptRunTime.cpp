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
	// �������ƣ� GetActionCaption
	// ���ܣ�   ����������ʶ��
	// ������   
	// ����ֵ: 
	std::string CXAction_ScriptRunTime::getActionCaption() const
	{
		return CSAction_SceneTime::getAction_SceneTime_Caption();
	}

	/*******************************************************************************/
	// �������ƣ� Parse_ActionFromXml
	// ���ܣ�   ����������������
	// ������   IXMLDOMNode *pXMLShapeNode:
	// ����ֵ: 
	bool CXAction_ScriptRunTime::Parse_ActionFromXml(pugi::xml_node* pXMLShapeNode)
	{
		bool bParseSec = CSAction_SceneTime::explainParamsFromXML(pXMLShapeNode, &m_lSceneRunTime);
		return bParseSec ;
	}

	/*******************************************************************************/
	// �������ƣ� CombineActionParam
	// ���ܣ�   �����������ò���
	// ������   CXActionVirtual *pDstActionVir:
	// ����ֵ: 
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
	// �������ƣ� CloneAction
	// ���ܣ�   ������������
	// ������   
	// ����ֵ: 
	CXActionVirtual * CXAction_ScriptRunTime::CloneAction()
	{
		CXAction_ScriptRunTime   *pCloneAction = new CXAction_ScriptRunTime();
		pCloneAction->SetValue_SceneRunTime( m_lSceneRunTime );
		return pCloneAction;
	}
}}
