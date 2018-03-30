#pragma once
#include ".\simulatorbase_global.h"

#include "..\Common\CommonGlobal.h"


namespace jysoft { namespace simulator {

	//获取实时体征监视模拟采样数值
    class SIMULATORBASESHARED_EXPORT IGetPhysioloySimulateData
	{
	public:
		IGetPhysioloySimulateData(void);
		virtual ~IGetPhysioloySimulateData(void);
	public:
		/*******************************************************************************
		//功能：获取滑块区域内的曲线数据
		//参数：int iMilliTime:          时间（0.1豪秒）
		//      float *pcBuffer:         返回的曲线数据
		//返回值:  曲线数据的长度
		*********************************************************************************/
		virtual unsigned long GetPhysioloySimulateData(int iMilliTime, /*out*/float *pcBuffer = NULL) = 0;
	};

	//获取I12导联心电图实时体征监视模拟采样数值
    class SIMULATORBASESHARED_EXPORT IGetEcgSimulateData : public IGetPhysioloySimulateData
	{
	public:
		IGetEcgSimulateData();
		virtual ~IGetEcgSimulateData();
	protected:
		RhythmLead                  m_eRhythmLead;          //当前的导联
	private:
		I12LeadSample *             m_pTempBuff;
		unsigned long                       m_dwSize;
	public:
		/*******************************************************************************/
		//功能：获取滑块区域内的曲线数据
		//参数：int iMilliTime:          时间（0.1豪秒）
		//      float *pcBuffer:         返回的曲线数据
		//返回值:  曲线数据的长度
		virtual unsigned long GetPhysioloySimulateData(int iMilliTime, /*out*/float *pcBuffer = NULL);
	public:
		/*******************************************************************************/
		//功能：获取滑块区域内的各导联曲线数据
		//参数：int iMilliTime:             时间（0.1豪秒）
		//      I12LeadSample *pcBuffer:    返回的各导联曲线数据
		//返回值:  曲线数据的长度
		virtual unsigned long GetI12LeadEcgSimulateData(int iMilliTime, /*out*/I12LeadSample *pcBuffer = NULL) = 0;
	private:
		//重置临时数据交互缓冲池大小
		void ResetTempBuffSize(unsigned long dwSize);
	};

	//获取呼吸实时体征监视模拟采样数值
    class SIMULATORBASESHARED_EXPORT IGetRespSimulateData : public IGetPhysioloySimulateData
	{
	public:
		IGetRespSimulateData();
		virtual ~IGetRespSimulateData();
	public:
		/*******************************************************************************
		//功能：获取滑块区域内的曲线数据
		//参数：int iMilliTime:          时间（0.1豪秒）
		//      float *pcBuffer:         返回的曲线数据
		//返回值:  曲线数据的长度
		*********************************************************************************/
		virtual unsigned long GetPhysioloySimulateData(int iMilliTime, /*out*/float *pcBuffer = NULL);
	public:
		/*******************************************************************************
		//功能：获取滑块区域内的曲线数据
		//参数：int iMilliTime:          时间（0.1豪秒）
		//      float *pcBuffer:         返回的曲线数据
		//返回值:  曲线数据的长度
		*********************************************************************************/
		virtual unsigned long GetRespSimulateData(int iMilliTime, /*out*/float *pcLeftBuffer = NULL, /*out*/float *pcRightBuffer = NULL) = 0;
	};

}}
