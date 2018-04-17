#pragma once
#include <string>
#include <boost/thread.hpp>
#include ".\abpsample.h"
#include ".\simulatoremulatebuild_global.h"

#include "..\Common\LoopBuffer.h"

#include "..\SimulatorBase\IGetPhysioloySimulateData.h"
#include "..\SimulatorBase\IPhysiologyStartSign.h"
#include "..\SimulatorBase\OpABPBuildInterface.h"


namespace jysoft { namespace simulator { namespace bp {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     有创血压模拟实时数据生成类
	创建人：	 hjg
	创建时间：   2017/2/19
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATOREMULATEBUILDSHARED_EXPORT CABPSimulateBuild : public IPhysiologyStartSign
										   ,public IGetPhysioloySimulateData
										   ,public base::COpABPBuildInterface
	{
	public:
		CABPSimulateBuild(void);
		virtual ~CABPSimulateBuild(void);
	protected:  //接口IPhysiologyStartSign函数重载
		/*******************************************************************************/
		//功能：血氧采样数据加载
		//参数：int nDifferMilliTime:          时间（0.1豪秒）
		//      int nQtoSMilliTime:            Q波到S波的时间（0.1豪秒）
		//      int nStoTMilliTime:            S波到T波的时间（0.1豪秒）
		//      int nCycleTime:                周期时间（0.1豪秒）
		//返回值:  
		virtual void StartPhysiologySimpleLoad(int nDifferMilliTime, int nQtoSMilliTime, int nStoTMilliTime, int nCycleTime);
	public:     //接口IGetPhysioloySimulateData函数重载
		/*******************************************************************************
		//功能：获取滑块区域内的曲线数据
		//参数：int iMilliTime:          时间（0.1豪秒）
		//      float *pcBuffer:         返回的曲线数据
		//返回值:  曲线数据的长度
		*********************************************************************************/
		virtual unsigned long GetPhysioloySimulateData(int iMilliTime, /*out*/float *pcBuffer = NULL);
	public:
		/*******************************************************************************/
		// 函数名称： ModifyABPValue
		// 功能： 修改ABP的值
		// 参数：  
		// 返回值:  
		virtual void ModifyABPValue(int nShrinkValue, int nStretchValue);
	public:
		/*******************************************************************************/
		// 函数名称： Get_IGetPhysioloySimulateDataPtr
		// 功能： 返回IGetPhysioloySimulateData接口指针
		// 参数： 
		// 返回值: 
		IGetPhysioloySimulateData * Get_IGetPhysioloySimulateDataPtr() { return (IGetPhysioloySimulateData *)this; };
		//初始化数据
		void initialABPSample(const std::string &resPath);
	public:
		CSample * GetCurrSamplePtr(void);
		//关闭ABP模拟器
		void CloseABPSimulateBuild();
		//根据ABP链接状态，返回是否显示ABP数据
		bool IsShowABPLinkState();
		//设置是否忽略ABP链接检查
		void Set_IsClearABPWatchLink(BOOL bClear);
		//设置ABP链接检查状态
		void Set_ABPWatchLinkState(BOOL bLinking);
	private:
		//获取一周期的数据，nSystolicTime为前一段的时间，nCycleTime为周期时间
		void GetABPOutputData(int nQtoSMilliTime, int nStoTMilliTime, int nCycleTime);
		//根据数据start和stop，获取这两个数据在sample中的相关位置
		void	GetSampleDataPos(CABPSample &sample,float start,float stop,int& startpos,int& stoppos);
	protected:
		utility::CLoopBuffer<float>      m_DataBuffer;
		CABPSample              m_cSrcFirstABPSampleData; //原ABP前一段数据
		CABPSample              m_cCurrFirstABPSampleData;
		CABPSample				m_cCurrFirstABPSampleData2;
		CABPSample              m_cSrcNextABPSampleData; //原ABP后一段数据
		CABPSample              m_cCurrNextABPSampleData;
		CABPSample				m_cOutput;//最终输出的一个数据的数据
		int						m_nShrinkValue;//收缩压
		int						m_nStretchValue;//舒张压
		float					m_fLastData;//前一个波段的最后一个数据						
	private:
		boost::mutex            m_cSwapMutex;
		bool                     m_bClearWatchLink;  //是否忽略ABP链接检查
		bool                     m_bLinkWatchABP;
		HANDLE					 m_hHeapHandle;
	};
}}}
