#pragma once
#include ".\XActionVitalSignVir.h"


namespace jysoft { namespace simulator {
    class SIMULATORSYMPTOMSHARED_EXPORT CXAction_etCO2 : public CXActionVitalSignVir
	{
	public:
		CXAction_etCO2(void);
		virtual ~CXAction_etCO2(void);
	public: //���ຯ������
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
		long  GetValue_AbsoluteEtCO2( long lSrcValue );
	public:
		inline long GetValue_etCO2() { return m_lEtCO2Value; };
		inline void SetValue_etCO2(long lValue) { m_lEtCO2Value = lValue; };
	public:
		long           m_lEtCO2Value;
	};
}}
