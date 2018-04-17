#pragma once
#include ".\XActionVitalSignVir.h"


namespace jysoft { namespace simulator {
    class SIMULATORSYMPTOMSHARED_EXPORT CXAction_Osat : public CXActionVitalSignVir
	{
	public:
		CXAction_Osat(void);
		virtual ~CXAction_Osat(void);
	protected:
		long							m_lBloodOxygenValue;
	protected:
		bool                            m_bRelatePercent;
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
		long  GetValue_AbsoluteSpO2(long  lSrcValue);
	public:
		inline long GetBloodOxygenValue() { return m_lBloodOxygenValue; };
		inline void SetValue_BloodOxygen(long lValue) { m_lBloodOxygenValue = lValue; };
		//�ٷֱ�����
		inline void Set_bRelatePercent( bool bPercent ) { m_bRelatePercent = bPercent; };
		inline bool Get_bRelatePercent() { return m_bRelatePercent; };
	};
}}
