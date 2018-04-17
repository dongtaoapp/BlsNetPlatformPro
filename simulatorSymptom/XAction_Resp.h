#pragma once
#include ".\xactionvirtual.h"

#include "..\Common\CommonGlobal.h"


namespace jysoft { namespace simulator {
    class SIMULATORSYMPTOMSHARED_EXPORT CXAction_Resp : public CXActionVirtual
	{
	public:
		CXAction_Resp(void);
		CXAction_Resp(eRespMode enumRespMode, long nRespRate);
		virtual ~CXAction_Resp(void);
	public:
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
		long   GetValue_AbsoluteRR(long lSrcRR);
	public:
		inline eRespMode GetRespMode() { return m_eRespMode; };
		inline long GetBreathRate() { return m_lBreathRate; };
		inline void SetRespMode(eRespMode enumRespMode) { m_eRespMode = enumRespMode; };
		inline void SetBreathRate(long lBreathRate) { m_lBreathRate = lBreathRate; };
		//�ٷֱ�����
		inline void Set_bRelatePercent( bool bPercent ) { m_bRelatePercent = bPercent; };
		inline bool Get_bRelatePercent() { return m_bRelatePercent; };
	public:
		eRespMode          m_eRespMode;    //����ģʽ
		long               m_lBreathRate;  //��������
	protected:
		bool               m_bRelatePercent;
	};
}}
