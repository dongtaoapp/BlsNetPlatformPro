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
	// �������ƣ� GetActionCaption
	// ���ܣ�   ����������ʶ��
	// ������   
	// ����ֵ: 
	std::string CXAction_Electrode::getActionCaption() const
	{
		return CSAction_Electrode::getAction_Electrode_Caption();
	}

	/*******************************************************************************/
	// �������ƣ� Parse_ActionFromXml
	// ���ܣ�   ����������������
	// ������   IXMLDOMNode *pXMLShapeNode:
	// ����ֵ: 
	bool CXAction_Electrode::Parse_ActionFromXml(pugi::xml_node* pXMLShapeNode)
	{
		return CSAction_Electrode::explainParamsFromXML(pXMLShapeNode, &m_bPosRight);
	}

	/*******************************************************************************/
	// �������ƣ� CombineActionParam
	// ���ܣ�   �����������ò���
	// ������   CXActionVirtual *pDstActionVir:
	// ����ֵ: 
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
	// �������ƣ� CloneAction
	// ���ܣ�   ������������
	// ������   
	// ����ֵ: 
	CXActionVirtual * CXAction_Electrode::CloneAction()
	{
		CXAction_Electrode *pNewAction = new CXAction_Electrode();
		pNewAction->m_bPosRight = m_bPosRight;
		return pNewAction;
	}
}}
