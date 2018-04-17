#pragma once
#include <boost/thread.hpp>
#include ".\co2simulatestateglobal.h"

#include "..\common\EmulateTimer.h"


namespace jysoft { namespace simulator { namespace etCO2 {
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     EtCO2实时模拟在无呼吸插管时的状态
	创建人：	 hjg
	创建时间：   2016/11/29
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
		int    m_nCPROpSegmentT;     //心肺复苏操作时间记录：-1:停止CPR；0:开始CPR；+0:时间（单位：30秒）
		boost::mutex         mu;
		utility::CEmulateTimer *      m_pEmulateTimer;
	public:
		void InitialStartTimeThread(CCO2SimulateBuild *pEtCO2SimulateBuild);
		//记录心肺复苏操作时间
		void IncreaseCPROpTime();
	public: //接口函数重载
		virtual bool isKindOf(const std::string &className);
		virtual int  GetCO2PerValue();
		/*******************************************************************************/
		// 函数名称： DoOnceBreathEventHandle
		// 功能： 一次吹气事件
		// 参数： 
		// 返回值:  
		virtual void DoOnceBreathEventHandle();
		/*******************************************************************************/
		// 函数名称： DoCPREventHandle
		// 功能： 阶段性CPR事件
		// 参数： 
		// 返回值:  
		virtual void DoCPREventHandle(bool bStop);
		/*******************************************************************************/
		// 函数名称： DoExhaledCO2EndHandle
		// 功能： 呼气阶段，处理
		// 参数： 
		// 返回值: FALSE: 没处理，默认方式实施；TRUE: 已做处理
		virtual bool DoExhaledCO2EndHandle(resp::CVirtualRespSegment *pReadSegment);
	};
}}}