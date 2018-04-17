#include ".\co2simulatebuild.h"
#include ".\CO2SimulateIntubateState.h"

#include "..\SimulatorBase\ShowEtCO2UpdateInterface.h"


namespace jysoft { namespace simulator { namespace etCO2 {

	CCO2SimulateBuild::CCO2SimulateBuild(void)
	{
		//忽略EtCO2链接检查
		m_bClearWatchLink  = true;
		m_bLinkWatchEtCO2  = false;

		m_nReflushCalculate  = 0;

		m_pIntubateState   = new CCO2SimulateIntubateState( );
		m_pCurrCO2SimulateState = NULL;
		m_pNextCO2SimulateState = NULL;
	}

	CCO2SimulateBuild::~CCO2SimulateBuild(void)
	{
		if( m_pIntubateState != NULL )
		{
			delete m_pIntubateState;
		}
		m_pIntubateState  = NULL;
	}

	/*********************************************************************************/
	//功能：初始化模拟CO2构造器
	//参数：
	//      int nCO2Per:             CO2%
	//返回值:  
	void CCO2SimulateBuild::InitializeBuild(int nCO2Per)
	{
		m_pCurrCO2SimulateState = NULL;
		m_pNextCO2SimulateState = NULL;
		//初始化插管状态
		m_pIntubateState->InitialStartTimeThread( this );
		m_cAutoRespState.Set_EtCO2SimulateBuildPtr( this );
		//---------------------------------------------------------------------------------------------------
		if( nCO2Per > 70 )
		{
			nCO2Per = 70;
		}
		m_cAutoRespState.SetCO2PerValue( nCO2Per );
		m_cCO2CycleData.InitialCO2CycleData( m_strCO2ResourePath, nCO2Per );
	}

	//修改CO2%
	void CCO2SimulateBuild::ModifyCO2PercentValue( int nCO2Per )
	{
		if( nCO2Per > 70 )
		{
			nCO2Per = 70;
		}
		m_cAutoRespState.SetCO2PerValue( nCO2Per );
		//设置气管插管时的etCO2值
		if( m_pCurrCO2SimulateState == m_pIntubateState || m_pNextCO2SimulateState == m_pIntubateState )
		{
			m_pIntubateState->SetCO2PerValue( nCO2Per );
		}
		nCO2Per   = -1;  //未指定
		{
			boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
			if( m_pCurrCO2SimulateState != NULL )
			{
				nCO2Per  = m_pCurrCO2SimulateState->GetCO2PerValue();
			}
		}
		
		if( nCO2Per != -1 )
		{
			m_cCO2CycleData.ModifyCO2PerValue( nCO2Per );
		}
	}
	/*******************************************************************************/
	//功能：获取滑块区域内的曲线数据
	//参数：int iMilliTime:          时间（0.1豪秒）
	//      float *pcBuffer:         返回的曲线数据
	//返回值:  曲线数据的长度
	unsigned long CCO2SimulateBuild::GetPhysioloySimulateData(int iMilliTime, /*out*/float *pcBuffer /*= NULL*/)
	{
		if( pcBuffer != NULL )
		{
			m_nReflushCalculate += iMilliTime;
			if( m_nReflushCalculate >= 0 )
			{
				//显示EtCO2的数值
				boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
				if( m_pShowEtCO2Update && m_pCurrCO2SimulateState)
				{
					int  nEtCO2Value = m_pCurrCO2SimulateState->GetCO2PerValue();
					m_pShowEtCO2Update->OnShowEtCO2Value( nEtCO2Value );
				}
				m_nReflushCalculate  = -100000;
			}
		}
		return m_cCO2CycleData.GetPhysioloySimulateData(iMilliTime, m_pCurrCO2SimulateState, pcBuffer);
	}

	/*******************************************************************************/
	// 函数名称： OnCO2SimulateSignOp
	// 功能： 呼吸时，产生对CO2的模拟信号处理
	// 参数：  BOOL bInspiration: 吸气(TRUE); 呼气(FALSE)
	//         int nMilliChangeTime: CO2骤升（降）的时间（0.1毫秒）
	//         int nMilliOtherTime:  骤升（降）后接下来的时间（0.1毫秒）
	// 返回值:  
	void CCO2SimulateBuild::OnCO2SimulateSignOp(bool bInspiration, int nMilliChangeTime, int nMilliOtherTime)
	{
		m_cCO2CycleData.CO2SimulateSignOp(bInspiration, nMilliChangeTime, nMilliOtherTime);
		//显示EtCO2数值
		boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
		if( bInspiration == TRUE )
		{
			m_nReflushCalculate  = -(nMilliChangeTime+nMilliOtherTime);
		}
		if( m_pShowEtCO2Update && m_pCurrCO2SimulateState)
		{
			int  nEtCO2Value = m_pCurrCO2SimulateState->GetCO2PerValue();
			m_pShowEtCO2Update->OnShowEtCO2Value( nEtCO2Value );
		}
	}


	//根据EtCO2链接状态，返回是否显示EtCO2数据
	bool CCO2SimulateBuild::IsShowEtCO2LinkState()
	{
		if( m_bClearWatchLink || m_bLinkWatchEtCO2 )
		{
			return true;
		}
		return false;
	}

	//设置是否忽略EtCO2链接检查
	void CCO2SimulateBuild::Set_IsClearEtCO2WatchLink(bool bClear)
	{
		m_bClearWatchLink  = bClear;
		boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
		if( m_pShowEtCO2Update != NULL )
		{
			if( IsShowEtCO2LinkState() )
			{
				m_pShowEtCO2Update->OnAllLinkUpdateShow();
			}
			else 
			{
				m_pShowEtCO2Update->OnAllUnLinkUpdateShow();
			}
		}
	}

	//设置EtCO2链接检查状态
	void CCO2SimulateBuild::Set_EtCO2WatchLinkState(bool bLinking)
	{	
		m_bLinkWatchEtCO2   = bLinking;
		boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
		if( m_pShowEtCO2Update != NULL )
		{
			if( IsShowEtCO2LinkState() )
			{
				m_pShowEtCO2Update->OnAllLinkUpdateShow();
			}
			else 
			{
				m_pShowEtCO2Update->OnAllUnLinkUpdateShow();
			}
		}
	}

	/*******************************************************************************/
	// 函数名称： OnStartAutoRespOp
	// 功能： 启动/暂停自主呼吸
	// 参数： 
	//         BOOL bAutoResp:
	// 返回值:  
	void CCO2SimulateBuild::OnStartAutoRespOp( bool bAutoResp )
	{
		boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
		if( bAutoResp )
		{
			//如果当前为插管状态，将其移到后备状态
			if( m_pCurrCO2SimulateState != NULL && m_pCurrCO2SimulateState->isKindOf( "CCO2SimulateIntubateState" ) )
			{
				m_pNextCO2SimulateState = m_pIntubateState;
			}
			else if( m_pNextCO2SimulateState != NULL && !m_pNextCO2SimulateState->isKindOf( "CCO2SimulateIntubateState" ) )
			{
				m_pNextCO2SimulateState  = NULL;
			}
			//当前模式为自主呼吸
			m_pCurrCO2SimulateState  = &m_cAutoRespState;
			m_cAutoRespState.Set_IsFirstAutoRespState( TRUE );
		}
		else
		{
			if( m_pNextCO2SimulateState != NULL )
			{
				//当前模式为插管
				m_pCurrCO2SimulateState  = m_pNextCO2SimulateState;
			}
			else if( m_pCurrCO2SimulateState == NULL || !m_pCurrCO2SimulateState->isKindOf( "CCO2SimulateIntubateState" ) )
			{
				//当前模式为无呼吸状态
				m_pCurrCO2SimulateState = &m_cNoRespState;
			}
			m_pNextCO2SimulateState  = NULL;
		}
	}

	/*******************************************************************************/
	// 函数名称： OnIntubateOp
	// 功能： 拔/插管事件
	// 参数： 
	//         BOOL bIntubate:
	// 返回值:  
	void CCO2SimulateBuild::IntubateEventOp( bool bIntubate )
	{
		boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
		if( m_pCurrCO2SimulateState != NULL && m_pCurrCO2SimulateState->isKindOf( "CCO2SimulateAutoRespState" ) )
		{
			m_pNextCO2SimulateState = bIntubate ? m_pIntubateState : NULL;
		}
		else
		{
			m_pCurrCO2SimulateState = bIntubate ? m_pIntubateState : (ICO2SimulateState *)&m_cNoRespState;
			m_pNextCO2SimulateState = NULL;
		};
	}

	/*******************************************************************************/
	// 函数名称： OnOnceBreathEventOp
	// 功能： 一次吹气事件
	// 参数： 
	// 返回值:  
	void CCO2SimulateBuild::OnceBreathEventOp()
	{
		boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
		if( m_pCurrCO2SimulateState != NULL )
		{
			m_pCurrCO2SimulateState->DoOnceBreathEventHandle();
		}
		//显示EtCO2数值
		m_nReflushCalculate  = -20000;
		if( m_pShowEtCO2Update && m_pCurrCO2SimulateState)
		{
			int  nEtCO2Value = m_pCurrCO2SimulateState->GetCO2PerValue();
			m_pShowEtCO2Update->OnShowEtCO2Value( nEtCO2Value );
		}
	}

	/*******************************************************************************/
	// 函数名称： OnCPREventOp
	// 功能： 阶段性CPR事件
	// 参数： 
	// 返回值:  
	void CCO2SimulateBuild::CPREventOp( bool bStop )
	{
		m_pIntubateState->DoCPREventHandle( bStop );
	}

	/*********************************************************************************/
	//功能：修改插管状态下EtCO2值
	//参数：
	//      int nEtCO2Value:             CO2%
	//返回值:  
	void CCO2SimulateBuild::ModifyEtCO2ValueIntubationState(int nEtCO2Value)
	{
		if( m_pCurrCO2SimulateState != NULL && m_pCurrCO2SimulateState->isKindOf( "CCO2SimulateIntubateState" ) )
		{
			m_cCO2CycleData.ModifyCO2PerValue( nEtCO2Value );
		}
	}
}}}
