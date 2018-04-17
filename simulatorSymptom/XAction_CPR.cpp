#include ".\XAction_CPR.h"


namespace jysoft { namespace simulator 
{
	CXAction_CPR::CXAction_CPR(void)
	{
	}

	CXAction_CPR::~CXAction_CPR(void)
	{
	}

	bool CXAction_CPR::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXAction_CPR" )
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
	std::string CXAction_CPR::getActionCaption() const
	{
        return "";
	}

	/*******************************************************************************/
	// �������ƣ� Parse_ActionFromXml
	// ���ܣ�   ����������������
	// ������   IXMLDOMNode *pXMLShapeNode:
	// ����ֵ: 
	bool CXAction_CPR::Parse_ActionFromXml(pugi::xml_node* pXMLShapeNode)
	{
		return false;
	}

	/*******************************************************************************/
	// �������ƣ� CombineActionParam
	// ���ܣ�   �����������ò���
	// ������   CXActionVirtual *pDstActionVir:
	// ����ֵ: 
	void CXAction_CPR::CombineActionParam(CXActionVirtual *pDstActionVir)
	{
	}

	/*******************************************************************************/
	// �������ƣ� CloneAction
	// ���ܣ�   ������������
	// ������   
	// ����ֵ: 
	CXActionVirtual * CXAction_CPR::CloneAction()
	{
		return NULL;
	}
}}
