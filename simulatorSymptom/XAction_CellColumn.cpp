#include ".\XAction_CellColumn.h"

#include "..\elementParse\SAction_CellColumn.h"


namespace jysoft { namespace simulator 
{
	CXAction_CellColumn::CXAction_CellColumn(void)
	{
	}

	CXAction_CellColumn::~CXAction_CellColumn(void)
	{
	}

	bool CXAction_CellColumn::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXAction_CellColumn" )
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
	std::string CXAction_CellColumn::getActionCaption() const
	{
		return CSAction_CellColumn::getAction_CellColumn_Caption();
	}

	/*******************************************************************************/
	// �������ƣ� Parse_ActionFromXml
	// ���ܣ�   ����������������
	// ������   IXMLDOMNode *pXMLShapeNode:
	// ����ֵ: 
	bool CXAction_CellColumn::Parse_ActionFromXml(pugi::xml_node* pXMLShapeNode)
	{
		return CSAction_CellColumn::explainParamsFromXML( pXMLShapeNode, /*out*/&m_bNatural);
	}

	/*******************************************************************************/
	// �������ƣ� CombineActionParam
	// ���ܣ�   �����������ò���
	// ������   CXActionVirtual *pDstActionVir:
	// ����ֵ: 
	void CXAction_CellColumn::CombineActionParam(CXActionVirtual *pDstActionVir)
	{
	#ifdef  _DEBUG
		if( getActionCaption() != pDstActionVir->getActionCaption() )
			BOOST_ASSERT( 0 );
	#endif
		CXAction_CellColumn  *pDestAction_CellColumn = ( CXAction_CellColumn  * )pDstActionVir;
		m_bNatural = pDestAction_CellColumn->m_bNatural;
	}

	/*******************************************************************************/
	// �������ƣ� CloneAction
	// ���ܣ�   ������������
	// ������   
	// ����ֵ: 
	CXActionVirtual * CXAction_CellColumn::CloneAction()
	{
		CXAction_CellColumn  *pNewAction = new CXAction_CellColumn();
		pNewAction->m_bNatural = m_bNatural;
		return pNewAction;
	}
}}
