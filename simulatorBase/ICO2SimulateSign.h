#pragma once
#include ".\simulatorbase_global.h"

namespace jysoft { namespace simulator {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     吸气时,CO2下降；呼气时，CO2上升
	创建人：	 hjg
	创建时间：   2016/7/22
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT ICO2SimulateSign
	{
	public:
		ICO2SimulateSign(void);
		virtual ~ICO2SimulateSign(void);
	public:
		/*******************************************************************************/
		// 函数名称： OnCO2SimulateSignOp
		// 功能： 呼吸时，产生对CO2的模拟信号处理
		// 参数：  BOOL bInspiration: 吸气(TRUE); 呼气(FALSE)
		//         int nMilliChangeTime: CO2骤升（降）的时间（0.1毫秒）
		//         int nMilliOtherTime:  骤升（降）后接下来的时间（0.1毫秒）
		// 返回值:  
		virtual void OnCO2SimulateSignOp(bool bInspiration, int nMilliChangeTime, int nMilliOtherTime) = 0;
		/*******************************************************************************/
		// 函数名称： OnStartAutoRespOp
		// 功能： 启动/暂停自主呼吸
		// 参数： 
		//         BOOL bAutoResp:
		// 返回值:  
		virtual void OnStartAutoRespOp( bool bAutoResp ) = 0;
	};

}}
