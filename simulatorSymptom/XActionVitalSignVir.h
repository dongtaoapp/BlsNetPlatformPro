#pragma once
#include ".\xactionvirtual.h"


namespace jysoft { namespace simulator {

    class SIMULATORSYMPTOMSHARED_EXPORT CXActionVitalSignVir : public CXActionVirtual
	{
	public:
		CXActionVitalSignVir(void);
		virtual ~CXActionVitalSignVir(void);
	public:
		virtual bool isKindOf(const std::string &strClassName);
	public:
		/*******************************************************************************/
		// �������ƣ� GetActionCaption
		// ���ܣ�   ����������ʶ��
		// ������   
		// ����ֵ: 
		virtual std::string getActionCaption() const = 0;
		/*******************************************************************************/
		// �������ƣ� Parse_ActionFromXml
		// ���ܣ�   ����������������
		// ������   IXMLDOMNode *pXMLShapeNode:
		// ����ֵ: 
		virtual bool Parse_ActionFromXml(pugi::xml_node* pXMLShapeNode) = 0;
		/*******************************************************************************/
		// �������ƣ� CombineActionParam
		// ���ܣ�   �����������ò���
		// ������   CXActionVirtual *pDstActionVir:
		// ����ֵ: 
		virtual void CombineActionParam(CXActionVirtual *pDstActionVir) = 0;
		/*******************************************************************************/
		// �������ƣ� CloneAction
		// ���ܣ�   ������������
		// ������   
		// ����ֵ: 
		virtual CXActionVirtual * CloneAction() = 0;
	};
}}
