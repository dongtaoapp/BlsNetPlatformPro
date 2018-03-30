#pragma once
#include ".\simulatorbase_global.h"

#include <boost/optional.hpp>
#include "..\Common\CommonGlobal.h"
#include "..\Common\IUpdateShowVir.h"


namespace jysoft{  namespace cpr {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     CPR操作统计显示接口显示接口
	创建人：	 hjg
	创建时间：   2017/2/25
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT CShowCPRStatisticUpdateInterface : public IUpdateShowVir
	{
	public:
		CShowCPRStatisticUpdateInterface(void);
		virtual ~CShowCPRStatisticUpdateInterface(void);
	public:
		virtual bool isKindOf(const std::string &className);
	public://接口函数重载
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	protected:
		//对接显示后通知
		virtual void doLinkCPRStatisticUpdateShow() { };
		//断开显示后通知
		virtual void cutLinkCPRStatisticUpdateShow() { };
		//重置统计
		virtual void ResetCPRStatistic(_CPRManageState  eState) = 0;
		//更新统计次数
		virtual void UpdateCPRStatistic(boost::optional<int> calcGradePec, int nPressureSumNum, int nPressureRightNum, int nBreathSumNum, int nBreathRightNum) = 0;
		//操作时间、按压中断时间通知、按压时间占比
		virtual void UpdateCPRTimeStatic(int cprPeriodTime, boost::optional<int> interruptTime,  boost::optional<int> pressureTimePercent) = 0;
		//循环统计：按压:吹气、循环次数
		virtual void UpdateCPRCycle(int pressureNum, int breathNum, boost::optional<int> cycleNum) = 0;
		//按压位置统计(包括进胃)：
		virtual void UpdatePositionStatic(short pos_low, short pos_high, short pos_left, short pos_Right) = 0;
		//进胃统计
		virtual void UpdateInStomachNumber( short sInStomachNum) = 0;
		//按压统计：正确百分比、中断时间、平均深度、平均频率、位置正确百分比、释放正确百分比、按压过大、按压过小
		virtual void UpdatePressureStatic(int calcGradePec, int interruptTime, int nAvergeDepth, int nAvergeRate, int sumNum, int posRightPec, int releasRightPec, int depthOverNum, int depthLowerNum) = 0;
		//吹气统计：正确百分比、平均吹气量、平均吹气频率、总吹气数、过大、过小、通气多长、通气多短
		virtual void UpdateBreathStatic(int calGradePec, int nAvergeVolume, int nAvergeRate, int sumNum, int volumeOverNum, int volumeLowerNum, int ventiOverTimeNum, int ventiLowerTimeNum) = 0;
	public:
		//重置统计
		virtual void OnResetCPRStatistic(_CPRManageState  eState);
		//更新统计次数
		void OnUpdateStatistic(boost::optional<int> calcGradePec, int nPressureSumNum, int nPressureRightNum, int nBreathSumNum, int nBreathRightNum);
		//操作时间、按压中断时间通知、按压时间占比
		virtual void OnUpdateCPRTimeStatic(int cprPeriodTime, boost::optional<int> interruptTime,  boost::optional<int> pressureTimePercent);
		//循环统计：按压:吹气、循环次数
		virtual void OnUpdateCPRCycle(int pressureNum, int breathNum, boost::optional<int> cycleNum);
		//按压位置统计
		virtual void OnUpdatePositionStatic(short pos_low, short pos_high, short pos_left, short pos_Right);
		//进胃统计
		virtual void OnUpdateInStomachNumber( short sInStomachNum);
		//按压统计：正确百分比、中断时间、平均深度、平均频率、位置正确百分比、释放正确百分比、按压过大、按压过小
		virtual void OnUpdatePressureStatic(int calcGradePec, int interruptTime, int nAvergeDepth, int nAvergeRate, int sumNum, int posRightPec, int releasRightPec, int depthOverNum, int depthLowerNum);
		//吹气统计：正确百分比、平均吹气量、平均吹气频率、总吹气数、过大、过小、通气多长、通气多短
		virtual void OnUpdateBreathStatic(int calGradePec, int nAvergeVolume, int nAvergeRate, int sumNum, int volumeOverNum, int volumeLowerNum, int ventiOverTimeNum, int ventiLowerTimeNum);
	};

}}
