#pragma once

#include ".\virtualrespsegment.h"
#include ".\InspirationSegment.h"

namespace jysoft { namespace simulator { namespace etCO2 {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     呼吸呼出时，CO2上升；此类用于此段数据操作类
	创建人：	 hjg
	创建时间：   2017/2/27
	//-----------------------------------------------------------------------------------------------------------------*/

	class CExhaledCO2Segment : public resp::CVirtualRespSegment
	{
	public:
		CExhaledCO2Segment(void);
		virtual ~CExhaledCO2Segment(void);
	protected:
		resp::CInspirationSegment     m_cOriginCO2Segment;
		int                     m_nCO2Percent;           //二氧化碳的百分比
	private:
		int                     m_nCurrentCO2Per;        //当前的二氧化碳的百分比
	public:
		bool isKindOf(const std::string &className );
		/*******************************************************************************/
		//功能： 加载文件内的CO2数据
		//参数： const CString &strFilePath: 数据文件路径
		//返回值:  
		virtual bool LoadOriginSegmentData(const std::string &strFilePath);
	protected:
		/*******************************************************************************/
		// 函数名称： GetVolumeMessageFromSegmentData
		// 功能： 由采样数据获取当前的残留气量和潮气量
		// 参数： [out]float &fRemainVolume：残留气量（单位：ml）
		//        [out]float &fSumVolume ：  最大气量  （单位：ml）
		// 返回值:  
		virtual void GetVolumeMessageFromSegmentData(float &fRemainVolume, float &fSumVolume) { };
		//直线延伸操作
		void  LineIntervalLinkSampleData(float fValue, int nIntervalTime);
	public:
		/*******************************************************************************/
		// 函数名称： InitilaCO2Segment
		// 功能： 呼吸呼出时，产生对CO2的模拟信号处理
		// 参数：  
		//         int nMilliChangeTime: CO2骤升的时间（0.1毫秒）
		//         int nMilliOtherTime:  骤升后接下来的时间（0.1毫秒）
		// 返回值:  
		void InitilaCO2Segment(int nMilliChangeTime, int nMilliOtherTime);
	public:
		void Set_CO2Percent(int nValue);
		inline int Get_CurrentCO2Percent() { return m_nCurrentCO2Per; };
	};
}}}