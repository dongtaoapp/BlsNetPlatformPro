#include <boost/format.hpp>
#include ".\xaction_abp.h"

#include "..\ElementParse\SAction_ABP.h"


namespace jysoft { namespace simulator 
{
	CXAction_ABP::CXAction_ABP(void)
	{
		m_dwField  = 0;
		m_nKorotkOffVolume = 0;
		m_nShrinkValue_ABP = 120;
		m_nStretchValue_ABP = 90;
	}

	CXAction_ABP::~CXAction_ABP(void)
	{
	}

	bool CXAction_ABP::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXAction_ABP" )
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
	std::string CXAction_ABP::getActionCaption() const
	{
		return CSAction_ABP::getAction_BP_Caption();
	}

	/*******************************************************************************/
	// �������ƣ� Parse_ActionFromXml
	// ���ܣ�   ����������������
	// ������   IXMLDOMNode *pXMLShapeNode:
	// ����ֵ: 
	bool CXAction_ABP::Parse_ActionFromXml(pugi::xml_node* pXMLShapeNode)
	{
		m_dwField = 0x01;
		return CSAction_ABP::explainParamsFromXML(pXMLShapeNode, &m_nShrinkValue_ABP, &m_nStretchValue_ABP);
	}

	/*******************************************************************************/
	// �������ƣ� CombineActionParam
	// ���ܣ�   �����������ò���
	// ������   CXActionVirtual *pDstActionVir:
	// ����ֵ: 
	void CXAction_ABP::CombineActionParam(CXActionVirtual *pDstActionVir)
	{
	#ifdef  _DEBUG
		if( getActionCaption() != pDstActionVir->getActionCaption() )
			BOOST_ASSERT( 0 );
	#endif
		CXAction_ABP  *pDestAction_ABP = ( CXAction_ABP  * )pDstActionVir;
		if( pDestAction_ABP->m_dwField == 0x01 )
		{
			m_nShrinkValue_ABP  = pDestAction_ABP->Get_ShrinkValue_ABP();
			m_nStretchValue_ABP = pDestAction_ABP->Get_StretchValue_ABP();
		}
		else if( pDestAction_ABP->m_dwField == 0x02 )
		{
			m_nKorotkOffVolume  = pDestAction_ABP->m_nKorotkOffVolume;
		}
		m_dwField  = 0x00;
	}

	/*******************************************************************************/
	// �������ƣ� CloneAction
	// ���ܣ�   ������������
	// ������   
	// ����ֵ: 
	CXActionVirtual * CXAction_ABP::CloneAction()
	{
		CXAction_ABP  *pNewAction = new CXAction_ABP();
		//��������ѹֵ
		pNewAction->Set_ShrinkValue_ABP( m_nShrinkValue_ABP );
		//��������ѹֵ
		pNewAction->Set_StretchValue_ABP( m_nStretchValue_ABP );
		//------------------------------------------------------------------------------
		pNewAction->m_nKorotkOffVolume = m_nKorotkOffVolume;
		pNewAction->m_dwField          = m_dwField;
		return pNewAction;
	}

	long  CXAction_ABP::GetValue_AbsoluteShrink( long lSrcShrink )
	{
		long    lAbsoluteValue = m_nShrinkValue_ABP;
		return lAbsoluteValue;
	}

	long CXAction_ABP::GetValue_AbsoluteStretch( long lSrcStretch )
	{
		long   lAbsoluteValue = m_nStretchValue_ABP;
		return lAbsoluteValue;
	}
}}
