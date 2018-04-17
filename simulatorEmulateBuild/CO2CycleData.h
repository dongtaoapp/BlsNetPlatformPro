#pragma once
#include ".\ExhaledCO2Segment.h"
#include ".\InspiratedCO2Segment.h"

#include "..\common\criticalmutex.h"

namespace jysoft { namespace simulator { namespace etCO2 {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     结合吸气段和呼出段数据操作类，生成一个周期的CO2数据
	创建人：	 hjg
	创建时间：   2008/7/31
	//-----------------------------------------------------------------------------------------------------------------*/
	class ICO2SimulateState;
	class CCO2CycleData
	{
	public:
		CCO2CycleData(void);
		virtual ~CCO2CycleData(void);
	protected:
		CExhaledCO2Segment            m_cExhaledCO2Segment;
		CInspiratedCO2Segment         m_cInspiratedCO2Segment;
	private:
		//采样数据读取情况记录
		resp::CVirtualRespSegment          *m_pReadSegment;
		unsigned long                         m_dwReadPos;
		utility::CCriticalMutex              m_cMutex;
	public:
		void InitialCO2CycleData( const std::string &etCO2ResoucePath, int nCO2Per );
		void ModifyCO2PerValue( int nCO2Per );
		//返回呼吸次数
		int  GetRespRate();
		/*******************************************************************************/
		// 函数名称： CO2SimulateSignOp
		// 功能： 呼吸时，产生对CO2的模拟信号处理
		// 参数：  BOOL bInspiration: 吸气(TRUE); 呼气(FALSE)
		//         int nMilliChangeTime: CO2骤升（降）的时间（0.1毫秒）
		//         int nMilliOtherTime:  骤升（降）后接下来的时间（0.1毫秒）
		// 返回值:  
		void CO2SimulateSignOp(bool bInspiration, int nMilliChangeTime, int nMilliOtherTime);
		/*******************************************************************************/
		//功能：获取滑块区域内的曲线数据
		//参数：
		//      int iMilliTime:                           时间（0.1豪秒）
		//      ICO2SimulateState *pEtCO2SimulateState:  
		//      float *pcBuffer:                          返回的曲线数据
		//返回值:  曲线数据的长度
		DWORD GetPhysioloySimulateData(int iMilliTime, ICO2SimulateState *pEtCO2SimulateState, /*out*/float *pcBuffer);
	};
}}}