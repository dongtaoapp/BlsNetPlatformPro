#pragma once
#include ".\simulatorbase_global.h"
#include ".\ShowEventSignUpdateInterface.h"

#include "..\Common\VirtualIrp.h"

namespace jysoft { namespace irp {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     事件Irp基类
	创建人：	 hjg
	创建时间：   2017/2/8
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORBASESHARED_EXPORT CVirEventIrp : public CVirtualIrp
	{
	public:
		CVirEventIrp(void);
		virtual ~CVirEventIrp(void);
	public:
		virtual _IrpType Get_eIrpType() = 0;
	public:
		virtual bool isKindOf(const std::string &strClass);
		//返回事件标志
		virtual eEventSign Get_EventSign() { return ES_Normal; };
		/*******************************************************************************/
		// 函数名称： doPackageIrp
		// 功能：  打包Irp的内容
		// 参数： 
		// 返回值: 
		virtual std::string doPackageIrp() = 0;
		/*******************************************************************************/
		// 函数名称： UpdateEventSignShow
		// 功能：  显示事件动作
		// 参数： 
		// 返回值: 
		virtual void UpdateEventSignShow(simulator::base::CShowEventSignUpdateInterface  *pInterface ) { };
		/*******************************************************************************/
		// 函数名称： getIrpLogMessage
		// 功能：  返回Irp包含的日志信息
		// 参数： 
		//        /*out*/_EventLog_struct *pLogStruct: 
		// 返回值: 
		virtual bool getIrpLogMessage(/*out*/_EventLog_struct *pLogStruct) { return false; };
	};

}}
