#pragma once
#include <boost/thread.hpp>
#include ".\co2simulatestateglobal.h"

#include "..\common\EmulateTimer.h"


namespace jysoft { namespace simulator { namespace etCO2 {
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     EtCO2ʵʱģ�����޺������ʱ��״̬
	�����ˣ�	 hjg
	����ʱ�䣺   2016/11/29
	//-----------------------------------------------------------------------------------------------------------------*/
	class CCO2SimulateBuild;
	class CCO2SimulateIntubateState : public ICO2SimulateState
	{
	public:
		CCO2SimulateIntubateState();
		virtual ~CCO2SimulateIntubateState(void);
	protected:
		CCO2SimulateBuild *   m_pEtCO2SimulateBuild;
	private:
		int    m_nCPROpSegmentT;     //�ķθ��ղ���ʱ���¼��-1:ֹͣCPR��0:��ʼCPR��+0:ʱ�䣨��λ��30�룩
		boost::mutex         mu;
		utility::CEmulateTimer *      m_pEmulateTimer;
	public:
		void InitialStartTimeThread(CCO2SimulateBuild *pEtCO2SimulateBuild);
		//��¼�ķθ��ղ���ʱ��
		void IncreaseCPROpTime();
	public: //�ӿں�������
		virtual bool isKindOf(const std::string &className);
		virtual int  GetCO2PerValue();
		/*******************************************************************************/
		// �������ƣ� DoOnceBreathEventHandle
		// ���ܣ� һ�δ����¼�
		// ������ 
		// ����ֵ:  
		virtual void DoOnceBreathEventHandle();
		/*******************************************************************************/
		// �������ƣ� DoCPREventHandle
		// ���ܣ� �׶���CPR�¼�
		// ������ 
		// ����ֵ:  
		virtual void DoCPREventHandle(bool bStop);
		/*******************************************************************************/
		// �������ƣ� DoExhaledCO2EndHandle
		// ���ܣ� �����׶Σ�����
		// ������ 
		// ����ֵ: FALSE: û����Ĭ�Ϸ�ʽʵʩ��TRUE: ��������
		virtual bool DoExhaledCO2EndHandle(resp::CVirtualRespSegment *pReadSegment);
	};
}}}