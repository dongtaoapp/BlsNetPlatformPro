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
			//=======创建线程==============
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
		//第一分钟内的初始PEtCO2低于12.5mmHg,指示流量小；第二分钟和第三分钟，PEtCO2上升到12.5至25mmHg之间
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

	//记录心肺复苏操作时间
	void CCO2SimulateIntubateState::IncreaseCPROpTime()
	{
		boost::mutex::scoped_lock  lock(mu);
		if( m_nCPROpSegmentT > -1 )
		{
			m_nCPROpSegmentT += 1;
		}
		//修改呼出末二氧化碳值
		if( m_pEtCO2SimulateBuild != NULL )
		{
			int  nEtCo2Value = GetCO2PerValue();
			m_pEtCO2SimulateBuild->ModifyEtCO2ValueIntubationState( nEtCo2Value );
		}
	}

	/*******************************************************************************/
	// 函数名称： DoOnceBreathEventHandle
	// 功能： 一次吹气事件
	// 参数： 
	// 返回值:  
	void CCO2SimulateIntubateState::DoOnceBreathEventHandle()
	{
		//启动一次二氧化碳分压波形
		if( m_pEtCO2SimulateBuild != NULL )
		{
			m_pEtCO2SimulateBuild->OnCO2SimulateSignOp(false, 1500, 3000);
		}
	}

	/*******************************************************************************/
	// 函数名称： DoCPREventHandle
	// 功能： 阶段性CPR事件
	// 参数： 
	// 返回值:  
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
		//修改呼出末二氧化碳值
		if( m_pEtCO2SimulateBuild != NULL )
		{
			int  nEtCo2Value = GetCO2PerValue();
			m_pEtCO2SimulateBuild->ModifyEtCO2ValueIntubationState( nEtCo2Value );
		}
	}

	/*******************************************************************************/
	// 函数名称： DoExhaledCO2EndHandle
	// 功能： 呼气阶段，处理
	// 参数： 
	// 返回值: FALSE: 没处理，默认方式实施；TRUE: 已做处理
	bool CCO2SimulateIntubateState::DoExhaledCO2EndHandle(resp::CVirtualRespSegment *pReadSegment)
	{
		if( pReadSegment != NULL && pReadSegment->isKindOf( "CExhaledCO2Segment" ) )
		{
			//结束一次二氧化碳分压波形
			if( m_pEtCO2SimulateBuild != NULL )
			{
				m_pEtCO2SimulateBuild->OnCO2SimulateSignOp(true, 1000, 1500);
			}
		}
		return false;
	}
}}}
