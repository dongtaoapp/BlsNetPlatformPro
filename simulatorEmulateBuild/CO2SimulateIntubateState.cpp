#include ".\CO2SimulateBuild.h"
#include ".\co2simulateintubatestate.h"


namespace jysoft { namespace simulator { namespace etCO2 {

	CCO2SimulateIntubateState::CCO2SimulateIntubateState()
	{
		m_pEtCO2SimulateBuild  = NULL;
		m_nCPROpSegmentT   = -1;

		m_pEmulateTimer = new utility::CEmulateTimer(25*1000, boost::bind(&CCO2SimulateIntubateState::IncreaseCPROpTime, this));
	}

	CCO2SimulateIntubateState::~CCO2SimulateIntubateState(void)
	{
		if( m_pEmulateTimer != NULL )
		{
			m_pEmulateTimer->killTimer();
			delete m_pEmulateTimer;
		}
		m_pEmulateTimer = NULL;
		m_pEtCO2SimulateBuild  = NULL;
	}

	void CCO2SimulateIntubateState::InitialStartTimeThread(CCO2SimulateBuild *pEtCO2SimulateBuild)
	{
		if( m_pEtCO2SimulateBuild == NULL )
		{
			m_pEtCO2SimulateBuild = pEtCO2SimulateBuild;
			//=======�����߳�==============
			m_pEmulateTimer->startTimer();
		}
	}

	bool CCO2SimulateIntubateState::isKindOf(const std::string &className)
	{
		if( className == "CCO2SimulateIntubateState" )
		{
			return true;
		}
		return false;
	}

	int  CCO2SimulateIntubateState::GetCO2PerValue()
	{
	#define  _STAGE1_CO2        8
	/*#define  _STATE2_CO2        25
		//��һ�����ڵĳ�ʼPEtCO2����12.5mmHg,ָʾ����С���ڶ����Ӻ͵������ӣ�PEtCO2������12.5��25mmHg֮��
		if( m_nCPROpSegmentT >= 3 && m_nCO2Percent < _STATE2_CO2 )
		{
			m_nCO2Percent  = 25;
		}
		else 
		{*/
			if( m_nCO2Percent == 0 ) 
			{
				m_nCO2Percent  = _STAGE1_CO2;
			}
		//}
		return m_nCO2Percent;
	}

	//��¼�ķθ��ղ���ʱ��
	void CCO2SimulateIntubateState::IncreaseCPROpTime()
	{
		boost::mutex::scoped_lock  lock(mu);
		if( m_nCPROpSegmentT > -1 )
		{
			m_nCPROpSegmentT += 1;
		}
		//�޸ĺ���ĩ������ֵ̼
		if( m_pEtCO2SimulateBuild != NULL )
		{
			int  nEtCo2Value = GetCO2PerValue();
			m_pEtCO2SimulateBuild->ModifyEtCO2ValueIntubationState( nEtCo2Value );
		}
	}

	/*******************************************************************************/
	// �������ƣ� DoOnceBreathEventHandle
	// ���ܣ� һ�δ����¼�
	// ������ 
	// ����ֵ:  
	void CCO2SimulateIntubateState::DoOnceBreathEventHandle()
	{
		//����һ�ζ�����̼��ѹ����
		if( m_pEtCO2SimulateBuild != NULL )
		{
			m_pEtCO2SimulateBuild->OnCO2SimulateSignOp(false, 1500, 3000);
		}
	}

	/*******************************************************************************/
	// �������ƣ� DoCPREventHandle
	// ���ܣ� �׶���CPR�¼�
	// ������ 
	// ����ֵ:  
	void CCO2SimulateIntubateState::DoCPREventHandle(bool bStop)
	{
		boost::mutex::scoped_lock  lock(mu);
		if( bStop == true )
		{
			m_nCPROpSegmentT  = -1;
		}
		else 
		{
			m_nCPROpSegmentT  = 0;
		}
		//�޸ĺ���ĩ������ֵ̼
		if( m_pEtCO2SimulateBuild != NULL )
		{
			int  nEtCo2Value = GetCO2PerValue();
			m_pEtCO2SimulateBuild->ModifyEtCO2ValueIntubationState( nEtCo2Value );
		}
	}

	/*******************************************************************************/
	// �������ƣ� DoExhaledCO2EndHandle
	// ���ܣ� �����׶Σ�����
	// ������ 
	// ����ֵ: FALSE: û����Ĭ�Ϸ�ʽʵʩ��TRUE: ��������
	bool CCO2SimulateIntubateState::DoExhaledCO2EndHandle(resp::CVirtualRespSegment *pReadSegment)
	{
		if( pReadSegment != NULL && pReadSegment->isKindOf( "CExhaledCO2Segment" ) )
		{
			//����һ�ζ�����̼��ѹ����
			if( m_pEtCO2SimulateBuild != NULL )
			{
				m_pEtCO2SimulateBuild->OnCO2SimulateSignOp(true, 1000, 1500);
			}
		}
		return false;
	}
}}}
