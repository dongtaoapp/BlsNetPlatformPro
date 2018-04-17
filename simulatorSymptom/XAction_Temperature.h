#pragma once
#include ".\XActionVitalSignVir.h"


namespace jysoft { namespace simulator {
    class SIMULATORSYMPTOMSHARED_EXPORT CXAction_Temperature : public CXActionVitalSignVir
	{
	public:
		CXAction_Temperature(void);
		virtual ~CXAction_Temperature(void);
	public://���ຯ������
		virtual bool isKindOf(const std::string &strClassName);
		/*******************************************************************************/
		// �������ƣ� GetActionCaption
		// ���ܣ�   ����������ʶ��
		// ������   
		// ����ֵ: 
		virtual std::string getActionCaption() const;
		/*******************************************************************************/
		// �������ƣ� Parse_ActionFromXml
		// ���ܣ�   ����������������
		// ������   IXMLDOMNode *pXMLShapeNode:
		// ����ֵ: 
		virtual bool Parse_ActionFromXml(pugi::xml_node* pXMLShapeNode);
		/*******************************************************************************/
		// �������ƣ� CombineActionParam
		// ���ܣ�   �����������ò���
		// ������   CXActionVirtual *pDstActionVir:
		// ����ֵ: 
		virtual void CombineActionParam(CXActionVirtual *pDstActionVir);
		/*******************************************************************************/
		// �������ƣ� CloneAction
		// ���ܣ�   ������������
		// ������   
		// ����ֵ: 
		virtual CXActionVirtual * CloneAction();
	public:
		inline float GetValue_P_Temp() { return m_fP_TempValue; };
		void SetValue_P_Temp(float fValue ) { m_fP_TempValue = fValue; };
	protected:
		float       m_fP_TempValue;   //��Χ�¶�
	};
}}
