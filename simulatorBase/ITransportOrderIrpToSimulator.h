#pragma once
#include ".\SimulatorOrderIrp.h"

#include "..\Common\VirtualIrp.h"

namespace jysoft { namespace transLayer {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     向模拟人发送指令的接口类
	创建人：	 hjg
	创建时间：   2016/7/31
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT ITransportOrderIrpToSimulator
	{
	public:
		ITransportOrderIrpToSimulator(void);
		virtual ~ITransportOrderIrpToSimulator(void);
	public:
		/*******************************************************************************/
		// 函数名称： OnTransportDownOrderToSimulater
		// 功能：  向模拟人发送指令
		// 参数： 
		// 返回值:  
		virtual void OnTransportDownOrderToSimulater(irp::CSimulatorOrderIrp *pOrderIrp) = 0;
		/*******************************************************************************/
		// 函数名称： GetCommunicateVersion
		// 功能：  返回通信版本
		// 参数： 
		// 返回值:  
		virtual short GetCommunicateVersion() = 0;
	};

	/*-------------------------------------------------------------------------------------------------------------------
	类说明：     上传设置指令的接口类
	创建人：	 hjg
	创建时间：   2009/5/13
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORBASESHARED_EXPORT ITransportOrderIrpToUp
	{
	public:
		ITransportOrderIrpToUp();
		virtual ~ITransportOrderIrpToUp();
	public:
		//----------------------------------------------------------------------------------
		// 函数名称： TranslateUpIrp
		// 功能：  通过传输层向上传输Irp
		// 参数： 
		// 返回值:  
		virtual void OnTranslateUpIrp( irp::CVirtualIrp * pUpIrp ) = 0;
		//-----------------------------------------------------------------------------------
		// 函数名称： TranslateUpIrpNoNetwork
		// 功能：  传输的Irp由本案例处理
		// 参数： 
		// 返回值:  
		virtual void OnTranslateUpIrpNoNetwork( irp::CVirtualIrp * pUpIrp ) = 0;
	};

}}
