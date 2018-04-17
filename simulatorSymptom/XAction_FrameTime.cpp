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
	// �������ƣ� getActionCaption
	// ���ܣ�   ����������ʶ��
	// ������   
	// ����ֵ: 
	std::string CXAction_FrameTime::getActionCaption() const
	{
		return CSAction_FrameTime::getAction_FrameTime_Caption();
	}
	/*******************************************************************************/
	// �������ƣ� Parse_ActionFromXml
	// ���ܣ�   ����������������
	// ������   IXMLDOMNode *pXMLShapeNode:
	// ����ֵ: 
	bool CXAction_FrameTime::Parse_ActionFromXml(pugi::xml_node* pXMLShapeNode)
	{
		bool bParseSec = CSAction_FrameTime::explainParamsFromXML(pXMLShapeNode, &m_lFrameTime);
		return bParseSec;
	}
	/*******************************************************************************/
	// �������ƣ� CombineActionParam
	// ���ܣ�   �����������ò���
	// ������   CXActionVirtual *pDstActionVir:
	// ����ֵ: 
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
	// �������ƣ� CloneAction
	// ���ܣ�   ������������
	// ������   
	// ����ֵ: 
	CXActionVirtual * CXAction_FrameTime::CloneAction()
	{
		CXAction_FrameTime   *pCloneAction = new CXAction_FrameTime();
		pCloneAction->SetValue_FrameTime( m_lFrameTime );
		return pCloneAction;
	}
}}
