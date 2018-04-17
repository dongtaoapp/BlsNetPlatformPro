#pragma once
#include ".\VirtualRespSegment.h"

namespace jysoft { namespace simulator { namespace etCO2 {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     EtCO2实时模拟状态接口
	创建人：	 hjg
	创建时间：   2010/11/29
	//-----------------------------------------------------------------------------------------------------------------*/

	class ICO2SimulateState
	{
	public:
		ICO2SimulateState(void);
		virtual ~ICO2SimulateState(void);
	protected:
		int                     m_nCO2Percent;           //二氧化碳的百分比
	public:
		virtual void SetCO2PerValue(int nCO2Per) { m_nCO2Percent = nCO2Per; };
		virtual int  GetCO2PerValue() { return m_nCO2Percent; };
	public: //接口函数
		virtual bool isKindOf(const std::string &className) = 0;
		/*******************************************************************************/
		// 函数名称： DoOnceBreathEventHandle
		// 功能： 一次吹气事件
		// 参数： 
		// 返回值:  
		virtual void DoOnceBreathEventHandle() = 0;
		/*******************************************************************************/
		// 函数名称： DoCPREventHandle
		// 功能： 阶段性CPR事件
		// 参数： 
		// 返回值:  
		virtual void DoCPREventHandle(bool bStop) = 0;
		/*******************************************************************************/
		// 函数名称： DoExhaledCO2EndHandle
		// 功能： 呼气阶段，处理
		// 参数： 
		// 返回值: FALSE: 没处理，默认方式实施；TRUE: 已做处理
		virtual bool DoExhaledCO2EndHandle(resp::CVirtualRespSegment *pReadSegment) = 0;
	};

	//自主呼吸状态类
	class  CCO2SimulateBuild;
	class CCO2SimulateAutoRespState : public ICO2SimulateState
	{
	public:
		CCO2SimulateAutoRespState();
		virtual ~CCO2SimulateAutoRespState();
	private:
		BOOL                   m_bFirstAutoRespState;
		CCO2SimulateBuild *    m_pEtCO2SimulateBuild;
	public: //接口函数重载
		virtual bool isKindOf(const std::string &className);
		/*******************************************************************************/
		// 函数名称： DoOnceBreathEventHandle
		// 功能： 一次吹气事件
		// 参数： 
		// 返回值:  
		virtual void DoOnceBreathEventHandle() { };
		/*******************************************************************************/
		// 函数名称： DoCPREventHandle
		// 功能： 阶段性CPR事件
		// 参数： 
		// 返回值:  
		virtual void DoCPREventHandle(bool bStop) { };
		/*******************************************************************************/
		// 函数名称： DoExhaledCO2EndHandle
		// 功能： 呼气阶段，处理
		// 参数： 
		// 返回值: FALSE: 没处理，默认方式实施；TRUE: 已做处理
		virtual bool DoExhaledCO2EndHandle(resp::CVirtualRespSegment *pReadSegment);
	public:
		void Set_EtCO2SimulateBuildPtr( CCO2SimulateBuild *pEtCO2Build );
		inline void Set_IsFirstAutoRespState(BOOL bFirst) { m_bFirstAutoRespState = bFirst; };
	};

	//无自主呼吸状态类
	class CCO2SimulateNoRespState : public ICO2SimulateState
	{
	public:
		CCO2SimulateNoRespState();
		virtual ~CCO2SimulateNoRespState();
	public: //接口函数重载
		virtual bool isKindOf(const std::string &className);
		virtual int  GetCO2PerValue() { return 0; };
		/*******************************************************************************/
		// 函数名称： DoOnceBreathEventHandle
		// 功能： 一次吹气事件
		// 参数： 
		// 返回值:  
		virtual void DoOnceBreathEventHandle() { };
		/*******************************************************************************/
		// 函数名称： DoCPREventHandle
		// 功能： 阶段性CPR事件
		// 参数： 
		// 返回值:  
		virtual void DoCPREventHandle(bool bStop) { };
		/*******************************************************************************/
		// 函数名称： DoExhaledCO2EndHandle
		// 功能： 呼气阶段，处理
		// 参数： 
		// 返回值: FALSE: 没处理，默认方式实施；TRUE: 已做处理
		virtual bool DoExhaledCO2EndHandle(resp::CVirtualRespSegment *pReadSegment) { return false; };
	};
}}}
