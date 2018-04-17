#include <boost/format.hpp>
#include ".\xaction_pace.h"

#include "..\ElementParse\SAction_Pace.h"


namespace jysoft { namespace simulator 
{
	CXAction_Pace::CXAction_Pace(void)
	{
	}

	CXAction_Pace::CXAction_Pace(bool bEnablePace, short sData)
	{	
		m_bEnablePace = bEnablePace;
		m_sData       = sData;
	}

	CXAction_Pace::~CXAction_Pace(void)
	{
	}

	bool CXAction_Pace::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXAction_Pace" )
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
	std::string CXAction_Pace::getActionCaption() const
	{
		return CSAction_Pace::getAction_Pace_Caption();
	}

	/*******************************************************************************/
	// �������ƣ� Parse_ActionFromXml
	// ���ܣ�   ����������������
	// ������   IXMLDOMNode *pXMLShapeNode:
	// ����ֵ: 
	bool CXAction_Pace::Parse_ActionFromXml(pugi::xml_node* pXMLShapeNode)
	{
		bool bParseSec = CSAction_Pace::explainParamsFromXML( pXMLShapeNode, /*out*/&m_bEnablePace, /*out*/&m_sData);
		return bParseSec ;
	}

	/*******************************************************************************/
	// �������ƣ� CombineActionParam
	// ���ܣ�   �����������ò���
	// ������   CXActionVirtual *pDstActionVir:
	// ����ֵ: 
	void CXAction_Pace::CombineActionParam(CXActionVirtual *pDstActionVir)
	{
	#ifdef  _DEBUG
		if( getActionCaption() != pDstActionVir->getActionCaption() )
			BOOST_ASSERT( 0 );
	#endif
		CXAction_Pace  *pDstAction_Pace = (CXAction_Pace  *)pDstActionVir;
		//�Ƿ�����
		m_bEnablePace   = pDstAction_Pace->GetValue_EnablePace();
		//�𲫵�����
		m_sData         = pDstAction_Pace->GetValue_PaceElectricData();
	}

	/*******************************************************************************/
	// �������ƣ� CloneAction
	// ���ܣ�   ������������
	// ������   
	// ����ֵ: 
	CXActionVirtual * CXAction_Pace::CloneAction()
	{
		CXAction_Pace *pNewAction = new CXAction_Pace(m_bEnablePace, m_sData);
		return pNewAction;
	}
}}
