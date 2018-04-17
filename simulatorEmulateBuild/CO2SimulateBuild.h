#pragma once
#include ".\simulatoremulatebuild_global.h"
#include ".\CO2CycleData.h"
#include ".\CO2SimulateStateGlobal.h"

#include "..\SimulatorBase\IGetPhysioloySimulateData.h"
#include "..\SimulatorBase\ICO2SimulateSign.h"
#include "..\SimulatorBase\OpEtCO2BuildInterface.h"


namespace jysoft { namespace simulator { namespace etCO2 {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     CO2模拟实时数据生成类
	创建人：	 hjg
	创建时间：   2008/7/30
	//-----------------------------------------------------------------------------------------------------------------*/

	class CCO2SimulateIntubateState;
    class SIMULATOREMULATEBUILDSHARED_EXPORT CCO2SimulateBuild  : public IGetPhysioloySimulateData
											 ,public ICO2SimulateSign
											 ,public base::COpEtCO2BuildInterface
	{
	public:
		CCO2SimulateBuild(void);
		virtual ~CCO2SimulateBuild(void);
	protected:
		CCO2CycleData                 m_cCO2CycleData;
		//------------------------------------------------------------------------------------
		CCO2SimulateAutoRespState     m_cAutoRespState;
		CCO2SimulateNoRespState       m_cNoRespState;
		CCO2SimulateIntubateState *   m_pIntubateState;
	protected:
		std::string       m_strCO2ResourePath;
	private:
		ICO2SimulateState  *          m_pCurrCO2SimulateState;   //当前的状态
		ICO2SimulateState  *          m_pNextCO2SimulateState;   //后备状态指针用于存贮插管状态
	public: //基类函数重载
		/*******************************************************************************/
		//功能：获取滑块区域内的曲线数据
		//参数：int iMilliTime:          时间（0.1豪秒）
		//      float *pcBuffer:         返回的曲线数据
		//返回值:  曲线数据的长度
		virtual unsigned long GetPhysioloySimulateData(int iMilliTime, /*out*/float *pcBuffer = NULL);
		/*******************************************************************************/
		// 函数名称： OnCO2SimulateSignOp
		// 功能： 呼吸时，产生对CO2的模拟信号处理
		// 参数：  BOOL bInspiration: 吸气(TRUE); 呼气(FALSE)
		//         int nMilliChangeTime: CO2骤升（降）的时间（0.1毫秒）
		//         int nMilliOtherTime:  骤升（降）后接下来的时间（0.1毫秒）
		// 返回值:  
		virtual void OnCO2SimulateSignOp(bool bInspiration, int nMilliChangeTime, int nMilliOtherTime);
		/*******************************************************************************/
		// 函数名称： OnStartAutoRespOp
		// 功能： 启动/暂停自主呼吸
		// 参数： 
		//         BOOL bAutoResp:
		// 返回值:  
		virtual void OnStartAutoRespOp( bool bAutoResp );
		/*******************************************************************************/
		// 函数名称： Get_IGetPhysioloySimulateDataPtr
		// 功能： 返回IGetPhysioloySimulateData接口指针
		// 参数： 
		// 返回值: 
		virtual IGetPhysioloySimulateData * Get_IGetPhysioloySimulateDataPtr() { return dynamic_cast<IGetPhysioloySimulateData *>(this); };
	protected:
		//修改CO2%
		virtual void ModifyCO2PercentValue( int nCO2Per );
		/*******************************************************************************/
		// 函数名称： OnIntubateOp
		// 功能： 拔/插管事件
		// 参数： 
		//         BOOL bIntubate:
		// 返回值:  
		virtual void IntubateEventOp( bool bIntubate );
		/*******************************************************************************/
		// 函数名称： OnOnceBreathEventOp
		// 功能： 一次吹气事件
		// 参数： 
		// 返回值:  
		virtual void OnceBreathEventOp();
		/*******************************************************************************/
		// 函数名称： OnCPREventOp
		// 功能： 阶段性CPR事件
		// 参数： 
		// 返回值:  
		virtual void CPREventOp( bool bStop );
	public:
		/*********************************************************************************/
		//功能：初始化模拟CO2构造器
		//参数：
		//      int nCO2Per:             CO2%
		//返回值:  
		void InitializeBuild(int nCO2Per);
		/*********************************************************************************/
		//功能：修改插管状态下EtCO2值
		//参数：
		//      int nEtCO2Value:             CO2%
		//返回值:  
		void ModifyEtCO2ValueIntubationState(int nEtCO2Value);
		void setResouceFilePath(const std::string &resPath) { m_strCO2ResourePath = resPath + "\\CO2SimulateData";};
		//根据EtCO2链接状态，返回是否显示EtCO2数据
		bool IsShowEtCO2LinkState();
		//设置是否忽略EtCO2链接检查
		void Set_IsClearEtCO2WatchLink(bool bClear);
		//设置EtCO2链接检查状态
		void Set_EtCO2WatchLinkState(bool bLinking);
	private:
		bool                     m_bClearWatchLink;  //是否忽略EtCO2链接检查
		bool                     m_bLinkWatchEtCO2;

		int                      m_nReflushCalculate;   //数值刷新计数器
	};
}}}
