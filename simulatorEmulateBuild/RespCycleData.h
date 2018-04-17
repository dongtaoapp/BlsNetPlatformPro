#pragma once
#include ".\InspirationSegment.h"
#include ".\ExhaleSegment.h"

#include "..\Common\CommonGlobal.h"
#include "..\Common\LoopBuffer.h"

#include "..\SimulatorBase\ICO2SimulateSign.h"
#include "..\SimulatorBase\SimulatorOrderIrp.h"
#include "..\SimulatorBase\ITransportOrderIrpToSimulator.h"

namespace jysoft { namespace simulator { namespace resp {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     结合吸气段和呼出段数据操作类，生成一个周期的呼吸数据
	创建人：	 hjg
	创建时间：   2017/2/22
	//-----------------------------------------------------------------------------------------------------------------*/
	class CRespCycleData
	{
	protected:
		struct RespDataStruct
		{
			float      m_fLungVolumeValue_L;   //左肺气量
			float      m_fLungVolumeValue_R;   //右肺气量
		};
	public:
		CRespCycleData(CInspirationSegment *pInspirationSegment, CExhaleSegment *pExhaleSegment, int nRespRate, int nInspirationTime);
		virtual ~CRespCycleData(void);
	protected:
		CInspirationSegment *       m_pInspirationSegment;  //吸气段数据
		CExhaleSegment *            m_pExhaleSegment;       //呼气段数据
		//------------------------------------------------------------------------------------------
		int                         m_nRespRate;            //呼吸次数
		int                         m_nRespCycleTime;       //周期时间(单位:0.1ms)
		int                         m_nInspirationTime;     //吸气时间(单位:0.1ms)
		int                         m_nInspirationToCO2Time;//吸气时，CO2骤降时间(单位:0.1ms)
		int                         m_nExhaleToCO2Time;     //呼气时，CO2骤升时间(单位:0.1ms)
		float                       m_fCurrentRemainVolume; //当前残留的量       (单位:ml)  
		float                       m_fSumVolume;           //本周期的总气量     (单位:ml)
		float                       m_fRemainVolume;        //本周期后的残留的量 (单位:ml)
		//-------------------------------------------------------------------------------------------
		utility::CLoopBuffer<RespDataStruct> m_cInspirationLungVolumes;
		utility::CLoopBuffer<RespDataStruct> m_cExhaleLungVolumes;
	private:
		int                        *m_pbSynchronizeSignSend;  //同步信号是否已发送
	protected:
		ICO2SimulateSign               *m_pCO2SimulateSignInteface;
		transLayer::ITransportOrderIrpToSimulator  *m_pTransportOrderInterface; 
	public:
		_eRefurbishDataRange            m_eRefurbishDataRange;
	public:
		//返回当前呼吸次数
		virtual int GetCurrentRespRate() { return m_nRespRate; };
		//返回数据的总周期时间(单位:0.1ms)
		inline int Get_RespCycleTime() { return m_nRespCycleTime; };
		inline void Set_RespCycleTime(int nTime ) { m_nRespCycleTime = nTime; };
		//返回本周期后的残留的量 (单位:ml)
		virtual float Get_RemainRespVolume() { return m_fRemainVolume; };
		//设置吸气时，CO2骤降时间(单位:0.1ms)
		inline void Set_InspirationToCO2Time(int nTime) { m_nInspirationToCO2Time = nTime; };
		//设置呼气时，CO2骤升时间(单位:0.1ms)
		inline void Set_ExhaleToCO2Time(int nTime) { m_nExhaleToCO2Time = nTime; };
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
	public:
		void Set_CO2SimulateSignInteface(ICO2SimulateSign *pInterface);
		void Set_TransportOrderIrpToSimulatorInteface(transLayer::ITransportOrderIrpToSimulator *pInterface, int *pIsSynSignSendFlag);
	public:
		//发送指令,控制模拟人的呼吸
		void TransportOrderToSimulator();
	protected:
		//生成指令Irp
		irp::CSimulatorOrderIrp * TranslateRespIrp( bool bSynchronizeSignOrder );
	};
}}}
