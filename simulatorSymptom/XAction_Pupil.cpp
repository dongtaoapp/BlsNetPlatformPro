#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include ".\xaction_pupil.h"

#include "..\elementParse\SAction_Pupil.h"


namespace jysoft { namespace simulator 
{
	CXAction_Pupil::CXAction_Pupil(void)
	{
		m_bNatural = true;
	}

	CXAction_Pupil::~CXAction_Pupil(void)
	{
	}

	bool CXAction_Pupil::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXAction_Pupil")
		{
			return true;
		}
		return CXActionVirtual::isKindOf(strClassName);
	}

	/*******************************************************************************/
	// �������ƣ� GetActionCaption
	// ���ܣ�   ����������ʶ��
	// ������   
	// ����ֵ: 
	std::string CXAction_Pupil::getActionCaption() const
	{
		return CSAction_Pupil::getAction_Pupil_Caption();
	}

	bool CXAction_Pupil::Parse_ActionFromXml(pugi::xml_node* pXMLShapeNode)
	{
		return CSAction_Pupil::explainParamsFromXML(pXMLShapeNode, &m_bNatural);
	}

	/*******************************************************************************/
	// �������ƣ� CombineActionParam
	// ���ܣ�   �����������ò���
	// ������   CXActionVirtual *pDstActionVir:
	// ����ֵ: 
	void CXAction_Pupil::CombineActionParam(CXActionVirtual *pDstActionVir)
	{
	#ifdef  _DEBUG
		if( getActionCaption() != pDstActionVir->getActionCaption() )
			BOOST_ASSERT( 0 );
	#endif
		CXAction_Pupil  *pDstAction_Pupil = (CXAction_Pupil  *)pDstActionVir;
		//ͫ�״�С
		m_bNatural  = pDstAction_Pupil->getPupilState();
	}

	/*******************************************************************************/
	// �������ƣ� CloneAction
	// ���ܣ�   ������������
	// ������   
	// ����ֵ: 
	CXActionVirtual * CXAction_Pupil::CloneAction()
	{
		CXAction_Pupil  *pNewAction = new CXAction_Pupil();
		pNewAction->setPupilState( m_bNatural );
		return pNewAction;
	}
}}

