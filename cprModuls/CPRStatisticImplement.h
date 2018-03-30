#pragma once
#include <boost/optional.hpp>
#include <boost/logic/tribool.hpp>
#include ".\Collates.h"
#include ".\CPRConfigue.h"
#include ".\CPRCommonGlobal.h"
#include ".\CPRPhaseStatistic.h"

#include "..\SimulatorBase\OpLogInterface.h"
#include "..\SimulatorBase\CPRShowInterfacesAggregate.h"


namespace jysoft{  namespace cpr {
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     CPR统计实施类
	创建人：	 hjg
	创建时间：   2017/5/21
	//-----------------------------------------------------------------------------------------------------------------*/
    class CPRMODULSSHARED_EXPORT CCPRStatisticImplement
	{
	public:
		CCPRStatisticImplement(CPressureCollate *pPressureCollate, CBreathCollate *pBreathCollate);
		virtual ~CCPRStatisticImplement(void);
	public:
		CPressurePhaseStatistic    pressurePhaseStat;  //按压阶段性操作统计类
		CBreathPhaseStatistic      breathPhaseStat;    //吹气阶段性操作统计类
	public:
		HANDLE                                    m_hRun;    //运行
		HANDLE                                    m_hPause;  //暂停
		HANDLE                                    m_hThrdOut;  //线程退出
		HANDLE                                    m_hThrdFinish;//线程结束
	protected:
		bool                                      bCPROperatoring;       //CPR操作是否正进行标识
		CPressureCollate*                         pressureCollate;
		CBreathCollate*                           breathCollate;
		CShowCPRStatisticUpdateInterface*         cprStatisticShowInterface;
		//--------------------------------------------------------------------------------------------------
		//CPR统计处于重置状态
		//true: 允许重置; false: 不允许重置; freezed: 冻结状态
		boost::tribool                 cprResetStating;
		boost::optional<int>           cycleNum;
		//本周期内的按压、吹气次数
		int      pressurePeriodNum;
		int      breathPeriodNum;
		//CPR循环定时启动标识时间点
		time_duration                  cprCycleInitiateTime;
		//累加时间(秒）
		time_duration                  accumulateSec;
		//-------------------------------------------------------------------------------------------------
		//CPR总绩效值%、按压绩效值%、吹气绩效值%
		boost::optional<int>     cprGradePec;
		boost::optional<int>     interruptTime;
	public: 
		/*******************************************************************************/
		// 函数名称： initialCPRStaticImpl
		// 功能： 初始化数据，启动时间事件线程
		// 参数：   
		// 返回值:  
		void initialCPRStaticImpl(void);
		/*******************************************************************************/
		// 函数名称： acceptAndStatisticImp
		// 功能： 通过接收到的幅度数值判断CPR操作的正确性及错误原因
		// 参数： DWORD  dwData: 按压/吹气的幅度值
		// 返回值:  CPR错误状态标示
		void acceptAndStatisticImp(const _CPRData &cprData, _eCPRErrorSign  eErrorSign, UINT uLackNum, _eCPRErrorSign ePractiseExtendSign, boost::optional<int> cycleNewNum, _CPRManageState eState, CCPRConfigue* pCPRConfigue);
		//重置内容
		void resetStatisticImpl(bool bUpdateStatistics = false);
		//允许重新开始统计
		void allowRestatisticImpl(const time_duration &scriptRunTime);
		//冻结时钟
		void freezedStatisticImpl();
		//增加100毫秒时间事件处理
		void increaseMillisecTimeTick();
		//时钟事件处理（单位：1秒）
		void doHandleSecondClockTick();
		//CPR开始处理
		void CPRStartHandle();
		//CPR结束处理
		void CPRStopHandle();
		/*******************************************************************************/
		// 函数名称： StartLinkCPRShowInterfaces
		// 功能： 初始连接CPR显示的相关显示接口
		// 参数： CCPRShowInterfacesAggregate *pShowAggregate:        
		// 返回值:  
		void startLinkCPRShowInterfaces(CCPRShowInterfacesAggregate *pShowAggregate);
		/*******************************************************************************/
		// 函数名称： UnLinkCPRShowInterfaces
		// 功能： 断开CPR显示的相关显示接口
		// 参数： CCPRShowInterfacesAggregate *pShowAggregate:        
		// 返回值:
		void unLinkCPRShowInterfaces(CCPRShowInterfacesAggregate *pShowAggregate);
		//设置阶段CPR统计日志接口
		void setPhaseCPRLogInterfacePtr(log::COpLogInterface *pLogInterface);
	protected:
		/*******************************************************************************/
		// 函数名称： StatisticOtherCPRValues
		// 功能： 统计其它数据量(平均速率、平均深度)
		// 参数： DWORD  dwData:        按压/吹气的幅度值
		//        _eCPRErrorSign eSign: CPR错误状态标示
		// 返回值:  
		void statisticOtherCPRValues(const _CPRData &cprData, _eCPRErrorSign eSign);
		//计算并同步更新统计数值
		//bScopeJudge： true:按压幅度，false:吹气幅度， unknown:幅度指令
		void calcAndUpdateStatisticValues(CShowCPRStatisticUpdateInterface *pShowInterface, boost::tribool bScopeJudge);
	public:
		void loadCPRData(const _CPRData *lptrCPRData, int nLength);
		inline bool isCPROperatoring() { return bCPROperatoring; };
		inline boost::optional<int> getCPRCycleNum() { return cycleNum; };
	protected:
		//计算并返回总分值(%)
		boost::optional<int>  calcCPRGradePecent(_CPRManageState eState, CCPRConfigue* pCPRConfigue);
		//计算并返回按压分值(%)
		boost::optional<int>  calcPressureGradePecent();
		//计算并返回吹气分值(%)
		boost::optional<int>  calcBreathGradePecent();
		//计算并返回按压释放正确分值(%)
		boost::optional<int>  calcPressureReleaseGradePecent();
		//计算并返回按压位置正确分值(%)
		boost::optional<int>  calcPressurePosGradePecent();
		//计算正确按压范围百分比
		boost::optional<int>  calcPressureDepthRightPecent();
		//计算循环统计：按压:吹气、循环次数
		void calcCPRCycleStatistic(const _CPRData &cprData, boost::optional<int> cycleNewNum);
	public:
		int GetPressureRate();
		//平均按压次数
		int GetPressureAverageCount(int nOpSumSecond);
		int GetPressureAverageDepth();
		int GetPressureSumRightNum();
		int GetPressureSumIncomplete();
		int GetPressureSumErrorsNum();
		int GetPressureOverNum();
		int GetPressureLackNum();
		int GetPressurePosErrorNum();
		//吹气
		int GetBreathAverageVol();
		int GetBreathAverageVolInMinute(int nOpSumSecond);
		int GetBreathAverageCountInMinute(int nOpSumSecond);
		int GetBreathSumRightNum();
		int GetBreathSumErrorsNum();
		int GetBreathOverNum();
		int GetBreathLackNum();
		int GetBreathInStomachNum();
		int GetBreathPipeCloseNum();
		int GetBreathOthersNum();
	public:
		static UINT ThrdCPRMicroSecondTimeFunc(LPVOID lpVoid);
	};
}}
