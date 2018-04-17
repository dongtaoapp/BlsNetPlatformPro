#pragma once
#include "respcycledata.h"


namespace jysoft { namespace simulator { namespace resp {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     停止呼吸时的周期数据
	创建人：	 hjg
	创建时间：   2017/2/22
	//-----------------------------------------------------------------------------------------------------------------*/

	class CRespApneaCycleData : public CRespCycleData
	{
	public:
		CRespApneaCycleData(CInspirationSegment *pInspirationSegment, CExhaleSegment *pExhaleSegment, int nRespRate, int nInspirationTime);
		virtual ~CRespApneaCycleData(void);
	protected:
		int        m_iSampleSec;      //每秒的采样率
	public:
		//返回当前呼吸次数
		virtual int GetCurrentRespRate() { return 0; };
		//设置当前残留的量
		inline void Set_CurrentRemainVolume(float fVolume) { m_fCurrentRemainVolume = fVolume; };
		//设置本周期结束后的残留的量
		inline void Set_RemainVolume(float fVolume) { m_fRemainVolume = fVolume; };
		/*******************************************************************************/
		// 函数名称： JudgeIsRepeatCycleData
		// 功能： 判断是否同一周期的数据
		// 参数： int nRespRate:  呼吸次数
		//        int nMillitInspirationTime: 吸气时间(单位:0.1ms)
		//        float fCurrentRemainVolume: 当前残留的量    
		//        float fSumVolume:           本周期的总气量
		//        float fRemainVolume:        本周期结束后的残留的量
		// 返回值:  
		virtual bool JudgeIsRepeatCycleData(int nRespRate, int nMillitInspirationTime, float fCurrentRemainVolume, float fSumVolume, float fRemainVolume);
		/*******************************************************************************/
		// 函数名称： ResetPrepareReadSampleData
		// 功能：  重置数据的读取准备
		// 参数： 
		// 返回值:  
		virtual void ResetPrepareReadSampleData();
		/*******************************************************************************
		//功能：获取时间区间内的呼吸数据
		//参数：int iMilliTime:          时间（0.1豪秒）
		//      float *pcBuffer:         返回的呼吸数据
		//      BYTE byteAddress:        目的设备地址码
		//返回值: 数据的长度
		*********************************************************************************/
        virtual short GetRespSimulateData(int iMilliTime, unsigned char byteAddress, /*out*/float *pcLeftBuffer = NULL, /*out*/float *pcRightBuffer = NULL);
	};
}}}
