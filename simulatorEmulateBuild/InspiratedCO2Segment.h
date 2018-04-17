#pragma once
#include ".\virtualrespsegment.h"
#include ".\ExhaleSegment.h"


namespace jysoft { namespace simulator { namespace etCO2 {
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     呼吸吸气时，CO2下降；此类用于此段数据操作类
	创建人：	 hjg
	创建时间：   2017/2/27
	//-----------------------------------------------------------------------------------------------------------------*/

	class CInspiratedCO2Segment : public resp::CVirtualRespSegment
	{
	public:
		CInspiratedCO2Segment(void);
		virtual ~CInspiratedCO2Segment(void);
	protected:
		resp::CExhaleSegment  m_cOriginCO2Segment;  //原始CO2下降段
	public:
		virtual bool isKindOf(const std::string &className );
		/*******************************************************************************/
		//功能： 加载文件内的呼吸数据
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
		void  HoriIntervalLinkData(int nTime);
	public:
		/*******************************************************************************/
		// 函数名称： InitilaCO2Segment
		// 功能： 呼吸时，产生对CO2的模拟信号处理
		// 参数：  int nCO2Per:          CO2百分比
		//         int nMilliChangeTime: CO2骤降的时间（0.1毫秒）
		//         int nMilliOtherTime:  骤降后接下来的时间（0.1毫秒）
		// 返回值:  
		void InitilaCO2Segment(int nCO2Per, int nMilliChangeTime, int nMilliOtherTime);
	};
}}}