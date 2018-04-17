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
	// �������ƣ� GetActionCaption
	// ���ܣ�   ����������ʶ��
	// ������   
	// ����ֵ: 
	std::string CXAction_ContactPatient::getActionCaption() const
	{
		return CSAction_ContactPatient::getAction_ContactPatient_Caption();
	}

	/*******************************************************************************/
	// �������ƣ� Parse_ActionFromXml
	// ���ܣ�   ����������������
	// ������   IXMLDOMNode *pXMLShapeNode:
	// ����ֵ: 
	bool CXAction_ContactPatient::Parse_ActionFromXml(pugi::xml_node* pXMLShapeNode)
	{
		return CSAction_ContactPatient::explainParamsFromXML(pXMLShapeNode, &m_bContactPatient);
	}

	/*******************************************************************************/
	// �������ƣ� CombineActionParam
	// ���ܣ�   �����������ò���
	// ������   CXActionVirtual *pDstActionVir:
	// ����ֵ: 
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
	// �������ƣ� CloneAction
	// ���ܣ�   ������������
	// ������   
	// ����ֵ: 
	CXActionVirtual * CXAction_ContactPatient::CloneAction()
	{
		CXAction_ContactPatient  *pNewAction = new CXAction_ContactPatient();
		pNewAction->m_bContactPatient = m_bContactPatient;
		return pNewAction;
	}
}}
