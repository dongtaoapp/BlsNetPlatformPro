#include ".\xaction_defibri.h"

#include "..\elementParse\SAction_Defibrillate.h"


namespace jysoft { namespace simulator 
{
	CXAction_Defibri::CXAction_Defibri(void)
	{
	}

	CXAction_Defibri::CXAction_Defibri(bool fEnableDefibr, bool bClearCount)
	{
		m_bEnableDefibri  = fEnableDefibr;
		m_bClearCount     = bClearCount;
	}

	CXAction_Defibri::~CXAction_Defibri(void)
	{
	}

	bool CXAction_Defibri::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXAction_Defibri" )
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
	std::string CXAction_Defibri::getActionCaption() const
	{
		return CSAction_Defibrillate::getAction_Defibri_Caption();
	}
	/*******************************************************************************/
	// �������ƣ� Parse_ActionFromXml
	// ���ܣ�   ����������������
	// ������   IXMLDOMNode *pXMLShapeNode:
	// ����ֵ: 
	bool CXAction_Defibri::Parse_ActionFromXml(pugi::xml_node* pXMLShapeNode)
	{
		bool bParseSec = CSAction_Defibrillate::explainParamsFromXML(pXMLShapeNode, /*out*/&m_bEnableDefibri, /*out*/&m_bClearCount);
		return bParseSec ;
	}

	/*******************************************************************************/
	// �������ƣ� CombineActionParam
	// ���ܣ�   �����������ò���
	// ������   CXActionVirtual *pDstActionVir:
	// ����ֵ: 
	void CXAction_Defibri::CombineActionParam(CXActionVirtual *pDstActionVir)
	{
	#ifdef  _DEBUG
		if( getActionCaption() != pDstActionVir->getActionCaption() )
			BOOST_ASSERT( 0 );
	#endif
		CXAction_Defibri *pDstAction_Defibri = (CXAction_Defibri *)pDstActionVir;
		//�Ƿ��ܳ���
		m_bEnableDefibri  = pDstAction_Defibri->getValue_EnableDefibri();
		//ȥ����������
		m_bClearCount     = pDstAction_Defibri->getValue_ClearCount();
	}

	/*******************************************************************************/
	// �������ƣ� CloneAction
	// ���ܣ�   ������������
	// ������   
	// ����ֵ: 
	CXActionVirtual * CXAction_Defibri::CloneAction()
	{
		CXAction_Defibri *pNewAction = new CXAction_Defibri(m_bEnableDefibri, m_bClearCount);
		return pNewAction;
	}
}}
