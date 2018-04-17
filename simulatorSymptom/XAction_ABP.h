#pragma once
#include ".\XActionVirtual.h"


namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     �д�Ѫѹ
	�����ˣ�	 hjg
	����ʱ�䣺   2017/2/1
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORSYMPTOMSHARED_EXPORT CXAction_ABP : public CXActionVirtual
	{
	public:
		CXAction_ABP(void);
		virtual ~CXAction_ABP(void);
	public://������������
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
		long   GetValue_AbsoluteShrink( long lSrcShrink );
		long   GetValue_AbsoluteStretch( long lSrcStretch );
	public:
		//��������ѹֵ
		inline long Get_ShrinkValue_ABP() { return m_nShrinkValue_ABP; };
		//��������ѹֵ
		inline long Get_StretchValue_ABP() { return m_nStretchValue_ABP; };
		//��������ѹֵ
		inline void Set_ShrinkValue_ABP(long lValue) { m_nShrinkValue_ABP = lValue; };
		//��������ѹֵ
		inline void Set_StretchValue_ABP(long lValue) { m_nStretchValue_ABP = lValue; };
	public:
		long        m_nShrinkValue_ABP;        //�д�����ѹ
		long        m_nStretchValue_ABP;       //�д�����ѹ
	public:
		int         m_nKorotkOffVolume;        //KorotkOff����ֵ
        unsigned long       m_dwField;                 //0x01: ����ѹ��0x02��KorotkOff����ֵ
	};
}}
