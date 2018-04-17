#pragma once
#include "xactionvirtual.h"


namespace jysoft { namespace simulator {
    class SIMULATORSYMPTOMSHARED_EXPORT CXAction_Pupil : public CXActionVirtual
	{
	public:
		CXAction_Pupil(void);
		virtual ~CXAction_Pupil(void);
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
		inline bool getPupilState() { return m_bNatural; };
		inline void setPupilState(bool bNatural) { m_bNatural = bNatural; };
	protected:
		bool        m_bNatural;
	};
}}
