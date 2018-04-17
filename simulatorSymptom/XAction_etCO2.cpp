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
	// �������ƣ� GetActionCaption
	// ���ܣ�   ����������ʶ��
	// ������   
	// ����ֵ: 
	std::string CXAction_etCO2::getActionCaption() const
	{
		return CSAction_etCO2::getAction_etCO2_Caption();
	}

	/*******************************************************************************/
	// �������ƣ� Parse_ActionFromXml
	// ���ܣ�   ����������������
	// ������   IXMLDOMNode *pXMLShapeNode:
	// ����ֵ: 
	bool CXAction_etCO2::Parse_ActionFromXml(pugi::xml_node* pXMLShapeNode)
	{
		return CSAction_etCO2::explainParamsFromXML(pXMLShapeNode, /*out*/&m_lEtCO2Value);
	}

	/*******************************************************************************/
	// �������ƣ� CombineActionParam
	// ���ܣ�   �����������ò���
	// ������   CXActionVirtual *pDstActionVir:
	// ����ֵ: 
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
	// �������ƣ� CloneAction
	// ���ܣ�   ������������
	// ������   
	// ����ֵ: 
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
