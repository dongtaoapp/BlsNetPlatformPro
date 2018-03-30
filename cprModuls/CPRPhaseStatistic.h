#pragma once
#include <list>
#include ".\Collates.h"
#include ".\CPRCommonGlobal.h"

#include "..\Common\CommonGlobal.h"
#include "..\Common\LoopBuffer.h"

#include "..\SimulatorBase\OpLogInterface.h"
#include "..\SimulatorBase\ShowCPRActUpdateInterface.h"

#include <boost/date_time/posix_time/posix_time.hpp>


using namespace boost::posix_time;
namespace jysoft{  namespace cpr {
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     CPR阶段性操作统计接口类
	创建人：	 hjg
	创建时间：   2017/4/9
	//-----------------------------------------------------------------------------------------------------------------*/
	class ICPRPhaseStatistic
	{
	public:
		ICPRPhaseStatistic(void);
		virtual ~ICPRPhaseStatistic(void);
	protected:
		std::list<_StatDataSeg *>       phaseStatSegs;
	protected:
		int                             delayTime;
		//间隔100毫秒的传输时钟
		UINT                            transEvent;
		UINT                            buffTimeEvent;//缓冲时间
		utility::CLoopBuffer<_CPRData>  loopBuff;
	protected:
		//日志事件接口
		log::COpLogInterface*          m_pEventLogInterface;  
		CShowCPRActUpdateInterface*    actCPRDetailShowInterface;
	public:
		/*******************************************************************************/
		// 函数名称： intervalTicktimeHandle
		// 功能： 间隔100毫秒时间处理函数
		// 参数： 
		//        
		// 返回值:  
		virtual void intervalTicktimeHandle(const CPressureCollate *pPressureColl, const CBreathCollate *pBreathColl) = 0;
		/*******************************************************************************/
		// 函数名称： increaseSecondTickNotify
		// 功能： 每一秒时钟事件通知
		// 参数： 
		//        scriptRunTime:   场景运行时间
		// 返回值:
		virtual void increaseSecondTickNotify(const time_duration &scriptRunTime) = 0;
		/*******************************************************************************/
		// 函数名称： cprPhaseStatisticHandle
		// 功能： CPR阶段性操作统计处理函数 
		// 参数： 
		//       cprData:
		// 返回值:  
        virtual void cprPhaseStatisticHandle(const _CPRData &cprData, _eCPRErrorSign  eErrorSign, short uLackNum, _eCPRErrorSign ePractiseExtendSign, _CPRManageState eState) = 0;
	public:
		//重置内容
		virtual void resetPhaseStatistic();
		//设置显示接口
		void setShowCPRDetailActInterfacePtr(CShowCPRActUpdateInterface *pInterface);
		//设置日志接口
		void setLogInterfacePtr(log::COpLogInterface *pLogInterface) { m_pEventLogInterface = pLogInterface; };
	};

	//按压阶段类
	class CPressurePhaseStatistic : public ICPRPhaseStatistic
	{
	public:
		CPressurePhaseStatistic();
		virtual ~CPressurePhaseStatistic();
	public:
		//中断时间（单位：秒）
		time_duration  interruptTime;
	protected:
		//当前按压阶段的统计
		_StatPressueSeg   currentSegStat;
		//中断累积时间（单位：秒）
		int     accumInterruptTime;
	public:
		/*******************************************************************************/
		// 函数名称： cprPressureRealTimeDataHandle
		// 功能： CPR操作数据处理函数 
		// 参数： 
		// 返回值:  
		void cprPressureRealTimeDataHandle(const _CPRData *lptrCPRDatas, int nLength, const CPressureCollate *pPressureColl);
		/*******************************************************************************/
		// 函数名称： intervalTicktimeHandle
		// 功能： 间隔100毫秒时间处理函数
		// 参数： 
		//        
		// 返回值:  
		virtual void intervalTicktimeHandle(const CPressureCollate *pPressureColl, const CBreathCollate *pBreathColl);
		/*******************************************************************************/
		// 函数名称： increaseSecondTickNotify
		// 功能： 每一秒时钟事件通知
		// 参数： 
		//        scriptRunTime:   场景运行时间
		// 返回值:
		virtual void increaseSecondTickNotify(const time_duration &scriptRunTime);
		/*******************************************************************************/
		// 函数名称： cprPhaseStatisticHandle
		// 功能： CPR阶段性操作统计处理函数 
		// 参数： 
		//       cprData:
		// 返回值:  
        virtual void cprPhaseStatisticHandle(const _CPRData &cprData, _eCPRErrorSign  eErrorSign, short uLackNum, _eCPRErrorSign ePractiseExtendSign, _CPRManageState eState);
	protected:
		/*******************************************************************************/
		// 函数名称： OnCPRRealTimePhaseStatisticHandle
		// 功能： CPR阶段性操作统计处理函数 
		// 参数： 
		//       _CPRData cCPRData:
		// 返回值:  
		void cprRealTimePhaseStatisticHandle(const _CPRData &cCPRData, const CPressureCollate *pPressureColl);
	private:
		void logPressurePhaseStatistic(const _StatPressueSeg *pPressureSeg, log::COpLogInterface* pLogInterface);
	public:
		//重置内容
		virtual void resetPhaseStatistic();
	public:
		short  getPressureSumNum();  //按压总次数
		short  getPressureSumRightNum(); //按压正确次数
		short  getPressureSumErrorsNum(); //按压错误次数
		short  getPressureSumIncomplete(); //按压释放不出次数
		short  getPressurePosErrorNum(short *pos_low = NULL, short *pos_high = NULL, short *pos_left = NULL, short *pos_Right = NULL); //按压位置错误次数
		short  getPressureOverNum();  //按压过大
		short  getPressureLackNum();  //按压过小
		//按压深度正确
		short  getPressureDepthRightNum();
		//返回平均按压深度
		short  getAverageDepth();
		//返回平均频率
		short  getAverageRate();
	};

	//吹气阶段类
	class CBreathPhaseStatistic : public ICPRPhaseStatistic
	{
	public:
		CBreathPhaseStatistic();
		virtual ~CBreathPhaseStatistic();
	protected:
		//当前吹气阶段的统计
		_StatBreathSeg     currentSegStat;
	public:
		/*******************************************************************************/
		// 函数名称： cprBreathRealTimeDataHandle
		// 功能： 吹气操作数据处理函数 
		// 参数： 
		// 返回值:  
		void cprBreathRealTimeDataHandle(const _CPRData *lptrCPRDatas, int nLength, const CBreathCollate *pBreathColl);
		/*******************************************************************************/
		// 函数名称： intervalTicktimeHandle
		// 功能： 间隔100毫秒时间处理函数
		// 参数： 
		//        
		// 返回值:  
		virtual void intervalTicktimeHandle(const CPressureCollate *pPressureColl, const CBreathCollate *pBreathColl);
		/*******************************************************************************/
		// 函数名称： increaseSecondTickNotify
		// 功能： 每一秒时钟事件通知
		// 参数： 
		//        scriptRunTime:   场景运行时间
		// 返回值:
		virtual void increaseSecondTickNotify(const time_duration &scriptRunTime);
		/*******************************************************************************/
		// 函数名称： cprPhaseStatisticHandle
		// 功能： CPR阶段性操作统计处理函数 
		// 参数： 
		//       cprData:
		// 返回值:  
        virtual void cprPhaseStatisticHandle(const _CPRData &cprData, _eCPRErrorSign  eErrorSign, short uLackNum, _eCPRErrorSign ePractiseExtendSign, _CPRManageState eState);
	protected:
		/*******************************************************************************/
		// 函数名称： OnCPRRealTimePhaseStatisticHandle
		// 功能： CPR阶段性操作统计处理函数 
		// 参数： 
		//        _CPRData cCPRData:
		// 返回值:  
		virtual void cprRealTimePhaseStatisticHandle(const _CPRData &cCPRData, const CBreathCollate *pBreathColl);
	private:
		//统计吹气阶段性操作数据量
		void logBreathPhaseStatistic(const _StatBreathSeg *pBreathSeg,  log::COpLogInterface* pLogInterface);
	public:
		//重置内容
		virtual void resetPhaseStatistic();
	public:
		short  getBreathSumNum();  //吹气总次数
		short  getBreathSumRightNum(); //吹气正确次数
		short  getBreathSumErrorsNum(); //吹气错误次数
		short  getBreathOverNum();
		short  getBreathLackNum();
		short  getBreathInStomachNum();
		short  getBreathPipeCloseNum();
		//通气时间过长
		short  getVentiOverTimeNum();
		//通气时间过短
		short  getVentiLowerTimeNum();
		//返回平均吹气量
		short  getAverageVolume();
	};
}}
