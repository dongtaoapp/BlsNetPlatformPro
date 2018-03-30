#include ".\CPRStatisticImplement.h"

#include "..\Common\ParseCPRData_Singleton.h"


using namespace boost;
BOOST_TRIBOOL_THIRD_STATE(freezed)
namespace jysoft{  namespace cpr {

	//=======================线程函数======================================
	//100毫秒时钟线程
	UINT CCPRStatisticImplement::ThrdCPRMicroSecondTimeFunc(LPVOID lpVoid)
	{
        /*CCPRStatisticImplement  *pCPRAggregate = (CCPRStatisticImplement *)lpVoid;
		::ResetEvent(pCPRAggregate->m_hThrdFinish);
		HANDLE  pHandles[2];
		pHandles[0] = pCPRAggregate->m_hThrdOut;
		pHandles[1] = pCPRAggregate->m_hRun;
		while(1)
		{
			DWORD dwRtn = ::WaitForMultipleObjects(2,pHandles,false,INFINITE);
			if(dwRtn == WAIT_OBJECT_0)
			{
				break;
			}
			HANDLE pHandles2[2];
			pHandles2[0] = pCPRAggregate->m_hThrdOut;
			pHandles2[1] = pCPRAggregate->m_hPause;
			dwRtn = ::WaitForMultipleObjects(2,pHandles2,false,100);
			switch(dwRtn)
			{
			case WAIT_TIMEOUT://发送100毫秒时针
				{
					pCPRAggregate->increaseMillisecTimeTick();
					break;
				}
			case WAIT_OBJECT_0:
				{//退出
					::SetEvent(pCPRAggregate->m_hThrdFinish);
					return 0;
				}
			}
		}
        ::SetEvent(pCPRAggregate->m_hThrdFinish);*/
		return 0;
	}

	CCPRStatisticImplement::CCPRStatisticImplement(CPressureCollate *pPressureCollate, CBreathCollate *pBreathCollate)
	{
		cprResetStating    = true;
		bCPROperatoring    = false;
		pressureCollate   = pPressureCollate;
		breathCollate     = pBreathCollate;
		cycleNum   = boost::none;
		cprGradePec = boost::none;
		interruptTime = boost::none;
		pressurePeriodNum = 0;
		breathPeriodNum = 0;
		//-------------------------------------------------------------------------------------
		m_hRun        = NULL;//暂停
		m_hPause      = NULL;//暂停
		m_hThrdOut    = NULL;
		m_hThrdFinish = NULL;

		cprStatisticShowInterface  = NULL;
	}

	CCPRStatisticImplement::~CCPRStatisticImplement(void)
	{
		resetStatisticImpl();
		//退出时间线程
		if(m_hThrdOut)
		{
			::SetEvent(m_hThrdOut);
			::WaitForSingleObject(m_hThrdFinish,INFINITE);
		}
		//删除事件句柄
		if(m_hRun)
			CloseHandle(m_hRun);
		if(m_hPause)
			CloseHandle(m_hPause);
		if(m_hThrdOut)
			CloseHandle(m_hThrdOut);
		if(m_hThrdFinish)
			CloseHandle(m_hThrdFinish);
		cprStatisticShowInterface  = NULL;
	}

	/*******************************************************************************/
	// 函数名称： initialCPRStaticImpl
	// 功能： 初始化数据，启动时间事件线程
	// 参数：   
	// 返回值:  
	void CCPRStatisticImplement::initialCPRStaticImpl(void)
	{
		bCPROperatoring    = false;
		cycleNum   = boost::none;
		cprGradePec = boost::none;
		interruptTime = boost::none;
		pressurePeriodNum = 0;
		breathPeriodNum = 0;
		//设置事件句柄
		m_hRun = ::CreateEvent(NULL,true,false,NULL);//暂停
		m_hPause = ::CreateEvent(NULL,true,true,NULL);//暂停
		m_hThrdOut = ::CreateEvent(NULL,true,false,NULL);
		m_hThrdFinish = ::CreateEvent(NULL,true,true,NULL);
		//启动线程
        //::AfxBeginThread((AFX_THREADPROC)CCPRStatisticImplement::ThrdCPRMicroSecondTimeFunc,(LPVOID)this,THREAD_PRIORITY_ABOVE_NORMAL);
	}

	/*******************************************************************************/
	// 函数名称： acceptAndStatisticImp
	// 功能： 通过接收到的幅度数值判断CPR操作的正确性及错误原因
	// 参数： cprData: 按压/吹气的幅度值
	// 返回值:  CPR错误状态标示
	void CCPRStatisticImplement::acceptAndStatisticImp(const _CPRData &cprData, _eCPRErrorSign  eErrorSign, UINT uLackNum, _eCPRErrorSign ePractiseExtendSign, boost::optional<int> cycleNewNum, _CPRManageState eState, CCPRConfigue* pCPRConfigue)
	{
		bool   bEnableRefresh  = false;
		const CParseCPRData_Singleton &cCPRParse = CParseCPRData_Singleton::get_const_instance();
		if( !cCPRParse.judgeCPRPhaseStartOrFinishOrder(cprData, indeterminate) )
		{
			if( cCPRParse.judgeCPRStartOrStopOrder(cprData, true) )
			{
				CPRStartHandle();
			}
			else if( cCPRParse.judgeCPRStartOrStopOrder(cprData, false) )
			{
				CPRStopHandle();
			}
			else
			{
				bEnableRefresh = true;
			}
			pressurePhaseStat.cprPhaseStatisticHandle(cprData, eErrorSign, uLackNum, ePractiseExtendSign, eState);
			breathPhaseStat.cprPhaseStatisticHandle(cprData, eErrorSign, uLackNum, ePractiseExtendSign, eState);
			//显示错误标志内容
			cprGradePec = calcCPRGradePecent(eState, pCPRConfigue);
			//计算循环统计：按压:吹气、循环次数
			calcCPRCycleStatistic(cprData, cycleNewNum);
			if( bEnableRefresh && cprStatisticShowInterface != NULL )
			{
				//计算并同步更新统计数值
				calcAndUpdateStatisticValues( cprStatisticShowInterface, cCPRParse.isCPRScopeOrder(cprData, true) );
			}
		}
	}

	void CCPRStatisticImplement::loadCPRData(const _CPRData *lptrCPRData, int nLength)
	{
		const CParseCPRData_Singleton &cCPRParse = CParseCPRData_Singleton::get_const_instance();
		if( nLength > 0 && !cCPRParse.judgeCPRStartOrStopOrder(lptrCPRData[0]) && !cCPRParse.judgeCPRPhaseStartOrFinishOrder(lptrCPRData[0], indeterminate) )
		{
			//CPR操作数据处理函数 
			pressurePhaseStat.cprPressureRealTimeDataHandle(lptrCPRData, nLength, pressureCollate);
			breathPhaseStat.cprBreathRealTimeDataHandle(lptrCPRData, nLength, breathCollate);
		}
	}

	//重置内容
	void CCPRStatisticImplement::resetStatisticImpl(bool bUpdateStatistics/*=false*/)
	{
		//暂停时间线程
		if( m_hRun != NULL )
			::ResetEvent( m_hRun );
		if( m_hPause != NULL )
			::SetEvent( m_hPause );
		//-----------------------------------------------------------
		cprResetStating  = true;
		cycleNum   = boost::none;
		cprGradePec = boost::none;
		interruptTime = boost::none;
		pressurePeriodNum = 0;
		breathPeriodNum = 0;
		accumulateSec    = seconds(0);
		bCPROperatoring  = false;
		pressurePhaseStat.resetPhaseStatistic();
		breathPhaseStat.resetPhaseStatistic();
		//同步更新统计数值
		if( bUpdateStatistics && cprStatisticShowInterface )
		{
			calcAndUpdateStatisticValues( cprStatisticShowInterface, indeterminate );
		}
	}

	//允许重新开始统计
	void CCPRStatisticImplement::allowRestatisticImpl(const time_duration &scriptRunTime)
	{
		if( cprResetStating == true)
		{
			cprResetStating  = false;
			cprCycleInitiateTime = scriptRunTime;
			accumulateSec    = seconds(0);
			//循环统计：按压:吹气、循环次数
			cycleNum = boost::none;
			pressurePeriodNum = 0;
			breathPeriodNum = 0;
			//CPR总绩效值%
			cprGradePec = boost::none;
			interruptTime = boost::none;
		}
		else if( freezed(cprResetStating) )
		{
			//冻结状态时，恢复时间计数
			cprResetStating = false;
		}
	}

	//冻结时钟
	void CCPRStatisticImplement::freezedStatisticImpl()
	{
		cprResetStating = freezed;
	}

	//时钟事件处理（单位：1秒）
	void CCPRStatisticImplement::doHandleSecondClockTick()
	{
		if( !cprResetStating || freezed(cprResetStating) )
		{
			if( cprResetStating == false )
			{
				accumulateSec += seconds(1);
				//每一秒时钟事件通知
				time_duration scriptRunTime = cprCycleInitiateTime + accumulateSec;
				pressurePhaseStat.increaseSecondTickNotify( scriptRunTime );
				breathPhaseStat.increaseSecondTickNotify( scriptRunTime );
			}
			else
			{
				pressurePhaseStat.increaseSecondTickNotify( cprCycleInitiateTime );
			}
			//中断时间设置
			//if( interruptTime.is_initialized() )
			//{
			interruptTime = pressurePhaseStat.interruptTime.total_seconds();
			//}
			//操作时间、按压中断时间通知、按压时间占比
			if( cprStatisticShowInterface != NULL )
			{
				cprStatisticShowInterface->OnUpdateCPRTimeStatic(accumulateSec.total_seconds(), interruptTime, boost::none);
			}
		}
	}

	//增加100毫秒时间事件处理
	void CCPRStatisticImplement::increaseMillisecTimeTick()
	{
		//间隔时间处理函数（100毫秒）
		pressurePhaseStat.intervalTicktimeHandle(pressureCollate, breathCollate);
		breathPhaseStat.intervalTicktimeHandle(pressureCollate, breathCollate);
	}

	//CPR开始处理
	void CCPRStatisticImplement::CPRStartHandle()
	{
		//启动事件计数
		if( m_hPause != NULL )
			::ResetEvent( m_hPause );
		if( m_hRun != NULL )
			::SetEvent( m_hRun );
		//--------------------------------------------------------------------------
		bCPROperatoring = true;
	}

	//CPR结束处理
	void CCPRStatisticImplement::CPRStopHandle()
	{
		bCPROperatoring = false;
		//暂停事件计数
		if( m_hRun != NULL )
			::ResetEvent( m_hRun );
		if( m_hPause != NULL )
			::SetEvent( m_hPause );
	}

	/*******************************************************************************/
	// 函数名称： StartLinkCPRShowInterfaces
	// 功能： 初始连接CPR显示的相关显示接口
	// 参数： CCPRShowInterfacesAggregate *pShowAggregate:        
	// 返回值:  
	void CCPRStatisticImplement::startLinkCPRShowInterfaces(CCPRShowInterfacesAggregate *pShowAggregate)
	{
		CShowCPRStatisticUpdateInterface *pShowCPRStatisticInterface = pShowAggregate->Get_ShowCPRStatisticUpdateInterface();
		if( cprStatisticShowInterface == NULL )
		{
			cprStatisticShowInterface = pShowCPRStatisticInterface;
		}
		else if( pShowCPRStatisticInterface != NULL )
		{
			cprStatisticShowInterface->SetNextInterfacePtr( pShowCPRStatisticInterface );
		}
		if( pShowCPRStatisticInterface != NULL )
		{
			pShowCPRStatisticInterface->LinkUpdateShow();
			//同步更新统计数值
			calcAndUpdateStatisticValues( pShowCPRStatisticInterface, indeterminate);
		}
		//设定CPR操作细节显示接口
		CShowCPRActUpdateInterface  *pShowCPRDetailActInterface = pShowAggregate->Get_ShowCPRDetailActUpdateInterface();
		pressurePhaseStat.setShowCPRDetailActInterfacePtr( pShowCPRDetailActInterface );
		breathPhaseStat.setShowCPRDetailActInterfacePtr( pShowCPRDetailActInterface );
	}

	/*******************************************************************************/
	// 函数名称： UnLinkCPRShowInterfaces
	// 功能： 断开CPR显示的相关显示接口
	// 参数： CCPRShowInterfacesAggregate *pShowAggregate:        
	// 返回值:
	void CCPRStatisticImplement::unLinkCPRShowInterfaces(CCPRShowInterfacesAggregate *pShowAggregate)
	{
		CShowCPRStatisticUpdateInterface *pShowCPRStatisticInterface = pShowAggregate->Get_ShowCPRStatisticUpdateInterface();
		if( pShowCPRStatisticInterface != NULL )
		{
			cprStatisticShowInterface = (CShowCPRStatisticUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(cprStatisticShowInterface, pShowCPRStatisticInterface);
			pShowCPRStatisticInterface->UnLinkUpdateShow();
		}
		//移除CPR操作细节显示接口
		CShowCPRActUpdateInterface  *pShowCPRDetailActInterface = pShowAggregate->Get_ShowCPRDetailActUpdateInterface();
		pressurePhaseStat.setShowCPRDetailActInterfacePtr( pShowCPRDetailActInterface );
		breathPhaseStat.setShowCPRDetailActInterfacePtr( pShowCPRDetailActInterface );
	}

	//设置阶段CPR统计日志接口
	void  CCPRStatisticImplement::setPhaseCPRLogInterfacePtr(log::COpLogInterface *pLogInterface)
	{
		pressurePhaseStat.setLogInterfacePtr( pLogInterface );
		breathPhaseStat.setLogInterfacePtr( pLogInterface );
	}

	/*******************************************************************************/
	// 函数名称： StatisticOtherCPRValues
	// 功能： 统计其它数据量
	// 参数： DWORD  dwData:        按压/吹气的幅度值
	//        _eCPRErrorSign eSign: CPR错误状态标示
	// 返回值:  
	void CCPRStatisticImplement::statisticOtherCPRValues(const _CPRData &cprData, _eCPRErrorSign eSign)
	{

	}

	//计算并同步更新统计数值
	//bScopeJudge： true:按压幅度，false:吹气幅度， unknown:幅度指令
	void CCPRStatisticImplement::calcAndUpdateStatisticValues(CShowCPRStatisticUpdateInterface *pShowInterface, tribool bScopeJudge)
	{
		short nBSumRight = breathPhaseStat.getBreathSumRightNum();
		short nBSumError = breathPhaseStat.getBreathSumErrorsNum();
		short nPSumRight = pressurePhaseStat.getPressureSumRightNum();
		short nPSumError = pressurePhaseStat.getPressureSumErrorsNum();
		pShowInterface->OnUpdateStatistic(cprGradePec, nPSumRight, nPSumError, nBSumRight, nBSumError);
		//循环统计：按压:吹气、循环次数
		pShowInterface->OnUpdateCPRCycle(pressurePeriodNum, breathPeriodNum, cycleNum);
		//按压
		if( bScopeJudge == true || indeterminate(bScopeJudge) )
		{
			//按压位置统计
			short pos_low, pos_high, pos_left, pos_Right;
			pressurePhaseStat.getPressurePosErrorNum(&pos_low, &pos_high, &pos_left, &pos_Right);
			pShowInterface->OnUpdatePositionStatic(pos_low, pos_high, pos_left, pos_Right);

			//按压统计：正确百分比、中断时间、平均深度、平均频率、位置正确百分比、释放正确百分比、按压过大、按压过小...

		}
		//吹气
		if( bScopeJudge == false || indeterminate(bScopeJudge) )
		{
			//进胃统计
			short sInStomachNum = breathPhaseStat.getBreathInStomachNum();
			pShowInterface->OnUpdateInStomachNumber( sInStomachNum );
			//吹气统计：正确百分比、平均吹气量、平均吹气频率、总吹气数、过大、过小、通气多长、通气多短...

		}
		if( indeterminate(bScopeJudge) )
		{
			//操作时间、按压中断时间通知、按压时间占比...
			pShowInterface->OnUpdateCPRTimeStatic(accumulateSec.total_seconds(), interruptTime, boost::none);
		}
	}

	//计算并返回按压分值(%)
	boost::optional<int>  CCPRStatisticImplement::calcPressureGradePecent()
	{
		boost::optional<int> gradePec = boost::none;
		if( pressurePhaseStat.getPressureSumNum() != 0 )
		{
			gradePec = 100 * pressurePhaseStat.getPressureSumRightNum() / pressurePhaseStat.getPressureSumNum();
		}
		return gradePec;
	}

	//计算并返回按压释放正确分值(%)
	boost::optional<int>  CCPRStatisticImplement::calcPressureReleaseGradePecent()
	{
		boost::optional<int> gradePec = boost::none;
		if( pressurePhaseStat.getPressureSumNum() != 0 )
		{
			gradePec = 100 - 100 * pressurePhaseStat.getPressureSumIncomplete() / pressurePhaseStat.getPressureSumNum();
		}
		return gradePec;
	}

	//计算并返回按压位置正确分值(%)
	boost::optional<int>  CCPRStatisticImplement::calcPressurePosGradePecent()
	{
		boost::optional<int> gradePec = boost::none;
		if( pressurePhaseStat.getPressureSumNum() != 0 )
		{
			gradePec = 100 - 100 * pressurePhaseStat.getPressurePosErrorNum() / pressurePhaseStat.getPressureSumNum();
		}
		return gradePec;
	}

	//计算正确按压范围百分比
	boost::optional<int>  CCPRStatisticImplement::calcPressureDepthRightPecent()
	{
		boost::optional<int> rightPec = boost::none;
		if( pressurePhaseStat.getPressureSumNum() > 0 )
		{
			rightPec = 100 * pressurePhaseStat.getPressureDepthRightNum() / pressurePhaseStat.getPressureSumNum();
		}
		return rightPec;
	}

	//计算并返回吹气分值(%)
	boost::optional<int>  CCPRStatisticImplement::calcBreathGradePecent()
	{
		boost::optional<int> gradePec = boost::none;
		if( breathPhaseStat.getBreathSumNum() != 0 )
		{
			gradePec = 100 * breathPhaseStat.getBreathSumRightNum() / breathPhaseStat.getBreathSumNum();
		}
		return gradePec;
	}

	//计算并返回总分值(%)
	boost::optional<int>  CCPRStatisticImplement::calcCPRGradePecent(_CPRManageState eState, CCPRConfigue* pCPRConfigue)
	{
		short  uPressureSumNum = pressurePhaseStat.getPressureSumNum();
		short  uBreathSumNum = breathPhaseStat.getBreathSumNum();
		boost::optional<int>  cprGradePec = boost::none;
		if( uPressureSumNum != 0  || uBreathSumNum != 0 )
		{
			//按压绩效值(%)
			boost::optional<int>  PGradePec = calcPressureGradePecent();
			//吹气绩效值(%)
			boost::optional<int>  BGradePec = calcBreathGradePecent();
			//计算CPR绩效值(%): 按压/吹气占比：3:1
			switch( eState )
			{
			case aCPRPopularMode:
			case aCPRPractiseMode:
				{
					int  nRulePSum  = 150;
					int  nRuleBSum = 10;
					if( pCPRConfigue->isSpecialityMemberOp() )
					{
						if( !pCPRConfigue->isFiveCycleRule() )
						{
							nRulePSum = 90;
							nRuleBSum = 6;
						}
					}
					else
					{
						nRuleBSum = 0;
						nRulePSum = pCPRConfigue->getSumPressureNumber();
					}
					float  fPNumAcc = pressurePhaseStat.getPressureSumNum() * 1.0f / nRulePSum;
					float  fBNumAcc =  nRuleBSum == 0 ? 1.0f : (breathPhaseStat.getBreathSumNum() * 1.0f / nRuleBSum);
					//计算: 按压占比*按压绩效值*0.75 + 吹气占比*吹气绩效值*0.25
					int nPGradePec = PGradePec.is_initialized() ? PGradePec.get() : 0;
					int nBGradePec = BGradePec.is_initialized() ? BGradePec.get() : 0;
					if( pCPRConfigue->isSpecialityMemberOp() && eState == aCPRPractiseMode )
					{
						cprGradePec = int((fPNumAcc >= 1.0f ? 1.0f : fPNumAcc) * nPGradePec * 0.75 + (fBNumAcc >= 1.0f ? 1.0f : fBNumAcc) * nBGradePec * 0.25);
					}
					else
					{
						cprGradePec = int((fPNumAcc >= 1.0f ? 1.0f : fPNumAcc) * nPGradePec);
					}
					break;
				}
			}
		}
		return cprGradePec;
	}

	//计算循环统计：按压:吹气、循环次数
	void CCPRStatisticImplement::calcCPRCycleStatistic(const _CPRData &cprData, boost::optional<int> cycleNewNum)
	{
		const CParseCPRData_Singleton &cCPRParse = CParseCPRData_Singleton::get_const_instance();
		//计算循环统计
		if( cycleNewNum == boost::none || cycleNum == boost::none || cycleNum == cycleNewNum )
		{
			if( cCPRParse.isCPRScopeOrder( cprData, true) )
			{
				pressurePeriodNum += 1;
			}
			else if( cCPRParse.isCPRScopeOrder( cprData, false) )
			{
				breathPeriodNum += 1;
			}
			if( cycleNewNum != boost::none )
			{
				cycleNum = cycleNewNum;
			}
		}
		else
		{
			if( cCPRParse.isCPRScopeOrder( cprData, true) )
			{
				pressurePeriodNum = 1;
				breathPeriodNum = 0;
			}
			else if( cCPRParse.isCPRScopeOrder( cprData, false) )
			{
				breathPeriodNum = 1;
				pressurePeriodNum = 0;
			}
			cycleNum = cycleNewNum;
		}
	}

	//按压平均频率
	int CCPRStatisticImplement::GetPressureRate()
	{
		return pressurePhaseStat.getAverageRate();
	}
	//平均按压次数  nSumSecond: 总操作时间(秒)
	int CCPRStatisticImplement::GetPressureAverageCount(int nOpSumSecond)
	{
		int  nSumNumber = pressurePhaseStat.getPressureSumNum();
		return nOpSumSecond > 0 ? int( nSumNumber * 60.0f / nOpSumSecond) : 0;
	}

	int CCPRStatisticImplement::GetPressureAverageDepth()
	{
		return pressurePhaseStat.getAverageDepth();
	}

	int CCPRStatisticImplement::GetPressurePosErrorNum()
	{
		return pressurePhaseStat.getPressurePosErrorNum();
	}

	int CCPRStatisticImplement::GetPressureSumRightNum()
	{
		return pressurePhaseStat.getPressureSumRightNum();
	}

	int CCPRStatisticImplement::GetPressureSumIncomplete()
	{
		return pressurePhaseStat.getPressureSumIncomplete();
	}

	int CCPRStatisticImplement::GetPressureSumErrorsNum()
	{
		return pressurePhaseStat.getPressureSumErrorsNum();
	}

	int CCPRStatisticImplement::GetPressureOverNum()
	{
		return pressurePhaseStat.getPressureOverNum();
	}
	//按压过小
	int CCPRStatisticImplement::GetPressureLackNum()
	{
		return pressurePhaseStat.getPressureLackNum();
	}

	//吹气
	int CCPRStatisticImplement::GetBreathAverageVol()
	{
		return breathPhaseStat.getAverageVolume();
	}

	int CCPRStatisticImplement::GetBreathAverageVolInMinute(int nOpSumSecond)
	{
		int nAverageVol = GetBreathAverageVol();
		return nAverageVol * GetBreathAverageCountInMinute( nOpSumSecond );
	}

	int CCPRStatisticImplement::GetBreathAverageCountInMinute(int nOpSumSecond)
	{
		int nSumNumber = breathPhaseStat.getBreathSumNum();
		return nOpSumSecond > 0 ? int( nSumNumber * 60.0f / nOpSumSecond) : 0;
	}

	int CCPRStatisticImplement::GetBreathSumRightNum()
	{
		return breathPhaseStat.getBreathSumRightNum();
	}

	int CCPRStatisticImplement::GetBreathSumErrorsNum()
	{
		return breathPhaseStat.getBreathSumErrorsNum();
	}

	int CCPRStatisticImplement::GetBreathOverNum()
	{
		return breathPhaseStat.getBreathOverNum();
	}

	int CCPRStatisticImplement::GetBreathLackNum()
	{
		return breathPhaseStat.getBreathLackNum();
	}

	int CCPRStatisticImplement::GetBreathInStomachNum()
	{
		return breathPhaseStat.getBreathInStomachNum();
	}

	int CCPRStatisticImplement::GetBreathPipeCloseNum()
	{
		return breathPhaseStat.getBreathPipeCloseNum();
	}
}}
