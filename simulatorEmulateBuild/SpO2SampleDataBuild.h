#pragma once
#include <boost/thread.hpp>
#include ".\simulatoremulatebuild_global.h"

#include "..\Common\LoopBuffer.h"

#include "..\SimulatorBase\IPhysiologyStartSign.h"
#include "..\SimulatorBase\Sample.h"
#include "..\SimulatorBase\IGetPhysioloySimulateData.h"
#include "..\SimulatorBase\OpSpO2BuildInterface.h"


namespace jysoft { namespace simulator { namespace SpO2 {

    class SIMULATOREMULATEBUILDSHARED_EXPORT CSpO2SampleDataBuild : public IPhysiologyStartSign
											  ,public IGetPhysioloySimulateData
											  ,public base::COpSpO2BuildInterface
	{
	public:
		CSpO2SampleDataBuild(void);
		virtual ~CSpO2SampleDataBuild(void);
	protected: //IPhysiologyStartSign基类函数重载
		/*******************************************************************************/
		//功能：血氧采样数据加载
		//参数：int nDifferMilliTime:          时间（0.1豪秒）
		//      int nQtoSMilliTime:            Q波到S波的时间（0.1豪秒）
		//      int nStoTMilliTime:            S波到T波的时间（0.1豪秒）
		//      int nCycleTime:                周期时间（0.1豪秒）
		//返回值:  
		virtual void StartPhysiologySimpleLoad(int nDifferMilliTime, int nQtoSMilliTime, int nStoTMilliTime, int nCycleTime);
	protected: //COpSpO2BuildInterface基类函数重载
		/*******************************************************************************/
		// 函数名称： ModifySpO2ValuePrecent
		// 功能： 修改血氧的百分比浓度
		// 参数：  int nSpO2Value:            血氧百分比浓度值
		// 返回值:  
		virtual void ModifySpO2ValuePrecent( int nSpO2Value );
	public://IGetPhysioloySimulateData基类函数重载
		/*******************************************************************************
		//功能：获取滑块区域内的曲线数据
		//参数：int iMilliTime:          时间（0.1豪秒）
		//      float *pcBuffer:         返回的曲线数据
		//返回值:  曲线数据的长度
		*********************************************************************************/
		virtual unsigned long GetPhysioloySimulateData(int iMilliTime, /*out*/float *pcBuffer = NULL);
		/*******************************************************************************/
		// 函数名称： Get_IGetPhysioloySimulateDataPtr
		// 功能： 返回IGetPhysioloySimulateData接口指针
		// 参数： 
		// 返回值: 
		virtual IGetPhysioloySimulateData * Get_IGetPhysioloySimulateDataPtr(){ return dynamic_cast<IGetPhysioloySimulateData*>(this); };
	public:
		CSample * GetCurrSamplePtr(void);
		//关闭血氧模拟器
		void CloseSpO2SimulateBuild();
		//根据SpO2链接状态，返回是否显示SpO2数据
		bool IsShowSpO2yLinkState();
		//设置是否忽略SpO2链接检查
		void Set_IsClearSpO2WatchLink(bool bClear);
		//设置SpO2链接检查状态
		void Set_SpO2WatchLinkState(bool bLinking);
	public:
		inline int  GetValue_SpO2Value() { return m_nSpO2Value; };
		//初始化数据
		void initialSpO2Sample(const std::string &resPath);
	protected:
		utility::CLoopBuffer<float>      m_DataBuffer; //血氧数据缓冲区
		CSample                 m_cSrcSpO2SampleData; //原血氧数据
		CSample                 m_cCurrSpO2SampleData; //当前使用的血氧数据
		int                     m_nSpO2Value;          //血氧值
	private:
		boost::mutex            m_cSwapMutex;
		HANDLE                  m_hHeapHandle;
		bool                     m_bClearWatchLink;//是否忽略SpO2链接检查
		bool                     m_bLinkWatchSpO2;
		int                      m_nReflushCalculate;   //数值刷新计数器
	};
}}}
