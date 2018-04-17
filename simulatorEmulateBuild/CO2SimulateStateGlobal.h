#pragma once
#include ".\VirtualRespSegment.h"

namespace jysoft { namespace simulator { namespace etCO2 {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     EtCO2ʵʱģ��״̬�ӿ�
	�����ˣ�	 hjg
	����ʱ�䣺   2010/11/29
	//-----------------------------------------------------------------------------------------------------------------*/

	class ICO2SimulateState
	{
	public:
		ICO2SimulateState(void);
		virtual ~ICO2SimulateState(void);
	protected:
		int                     m_nCO2Percent;           //������̼�İٷֱ�
	public:
		virtual void SetCO2PerValue(int nCO2Per) { m_nCO2Percent = nCO2Per; };
		virtual int  GetCO2PerValue() { return m_nCO2Percent; };
	public: //�ӿں���
		virtual bool isKindOf(const std::string &className) = 0;
		/*******************************************************************************/
		// �������ƣ� DoOnceBreathEventHandle
		// ���ܣ� һ�δ����¼�
		// ������ 
		// ����ֵ:  
		virtual void DoOnceBreathEventHandle() = 0;
		/*******************************************************************************/
		// �������ƣ� DoCPREventHandle
		// ���ܣ� �׶���CPR�¼�
		// ������ 
		// ����ֵ:  
		virtual void DoCPREventHandle(bool bStop) = 0;
		/*******************************************************************************/
		// �������ƣ� DoExhaledCO2EndHandle
		// ���ܣ� �����׶Σ�����
		// ������ 
		// ����ֵ: FALSE: û����Ĭ�Ϸ�ʽʵʩ��TRUE: ��������
		virtual bool DoExhaledCO2EndHandle(resp::CVirtualRespSegment *pReadSegment) = 0;
	};

	//��������״̬��
	class  CCO2SimulateBuild;
	class CCO2SimulateAutoRespState : public ICO2SimulateState
	{
	public:
		CCO2SimulateAutoRespState();
		virtual ~CCO2SimulateAutoRespState();
	private:
		BOOL                   m_bFirstAutoRespState;
		CCO2SimulateBuild *    m_pEtCO2SimulateBuild;
	public: //�ӿں�������
		virtual bool isKindOf(const std::string &className);
		/*******************************************************************************/
		// �������ƣ� DoOnceBreathEventHandle
		// ���ܣ� һ�δ����¼�
		// ������ 
		// ����ֵ:  
		virtual void DoOnceBreathEventHandle() { };
		/*******************************************************************************/
		// �������ƣ� DoCPREventHandle
		// ���ܣ� �׶���CPR�¼�
		// ������ 
		// ����ֵ:  
		virtual void DoCPREventHandle(bool bStop) { };
		/*******************************************************************************/
		// �������ƣ� DoExhaledCO2EndHandle
		// ���ܣ� �����׶Σ�����
		// ������ 
		// ����ֵ: FALSE: û����Ĭ�Ϸ�ʽʵʩ��TRUE: ��������
		virtual bool DoExhaledCO2EndHandle(resp::CVirtualRespSegment *pReadSegment);
	public:
		void Set_EtCO2SimulateBuildPtr( CCO2SimulateBuild *pEtCO2Build );
		inline void Set_IsFirstAutoRespState(BOOL bFirst) { m_bFirstAutoRespState = bFirst; };
	};

	//����������״̬��
	class CCO2SimulateNoRespState : public ICO2SimulateState
	{
	public:
		CCO2SimulateNoRespState();
		virtual ~CCO2SimulateNoRespState();
	public: //�ӿں�������
		virtual bool isKindOf(const std::string &className);
		virtual int  GetCO2PerValue() { return 0; };
		/*******************************************************************************/
		// �������ƣ� DoOnceBreathEventHandle
		// ���ܣ� һ�δ����¼�
		// ������ 
		// ����ֵ:  
		virtual void DoOnceBreathEventHandle() { };
		/*******************************************************************************/
		// �������ƣ� DoCPREventHandle
		// ���ܣ� �׶���CPR�¼�
		// ������ 
		// ����ֵ:  
		virtual void DoCPREventHandle(bool bStop) { };
		/*******************************************************************************/
		// �������ƣ� DoExhaledCO2EndHandle
		// ���ܣ� �����׶Σ�����
		// ������ 
		// ����ֵ: FALSE: û����Ĭ�Ϸ�ʽʵʩ��TRUE: ��������
		virtual bool DoExhaledCO2EndHandle(resp::CVirtualRespSegment *pReadSegment) { return false; };
	};
}}}
