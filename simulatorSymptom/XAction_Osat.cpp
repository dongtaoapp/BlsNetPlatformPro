#include <boost/format.hpp>
#include ".\XAction_Osat.h"

#include "..\elementParse\SAction_Osat.h"

namespace jysoft { namespace simulator 
{
	CXAction_Osat::CXAction_Osat(void)
	{
		m_lBloodOxygenValue = 98;
		m_bRelatePercent    = false;
	}

	CXAction_Osat::~CXAction_Osat(void)
	{
	}

	bool CXAction_Osat::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXAction_Osat")
		{
			return true;
		}
		return CXActionVitalSignVir::isKindOf(strClassName);
	}

	/*******************************************************************************/
	// �������ƣ� GetActionCaption
	// ���ܣ�   ����������ʶ��
	// ������   
	// ����ֵ: 
	std::string CXAction_Osat::getActionCaption() const
	{
		return CSAction_Osat::getAction_Osat_Caption();
	}

	/*******************************************************************************/
	// �������ƣ� Parse_ActionFromXml
	// ���ܣ�   ����������������
	// ������   IXMLDOMNode *pXMLShapeNode:
	// ����ֵ:
	bool CXAction_Osat::Parse_ActionFromXml(pugi::xml_node* pXMLShapeNode)
	{
		return CSAction_Osat::explainParamsFromXML(pXMLShapeNode, &m_lBloodOxygenValue);
	}

	/*******************************************************************************/
	// �������ƣ� CombineActionParam
	// ���ܣ�   �����������ò���
	// ������   CXActionVirtual *pDstActionVir:
	// ����ֵ: 
	void CXAction_Osat::CombineActionParam(CXActionVirtual *pDstActionVir)
	{
	#ifdef  _DEBUG
		if( getActionCaption() != pDstActionVir->getActionCaption() )
			BOOST_ASSERT( 0 );
	#endif
		CXAction_Osat  *pDestActionOxygen = (CXAction_Osat  *)pDstActionVir;
		//Ѫ��
		m_lBloodOxygenValue  = pDestActionOxygen->GetBloodOxygenValue();
		m_bRelatePercent     = pDestActionOxygen->Get_bRelatePercent();
	}

	/*******************************************************************************/
	// �������ƣ� CloneAction
	// ���ܣ�   ������������
	// ������   
	// ����ֵ: 
	CXActionVirtual * CXAction_Osat::CloneAction()
	{	
		CXAction_Osat  *pNewAction = new CXAction_Osat();
		pNewAction->SetValue_BloodOxygen( m_lBloodOxygenValue );
		pNewAction->Set_bRelatePercent( m_bRelatePercent );
		return pNewAction;
	}

	long  CXAction_Osat::GetValue_AbsoluteSpO2(long  lSrcValue)
	{
		long   lSpO2Value  = m_lBloodOxygenValue;
		if( m_bRelatePercent == true )
		{
			lSpO2Value  = (1+m_lBloodOxygenValue/100.0f) * lSrcValue;
		}
		return lSpO2Value;
	}
}}
