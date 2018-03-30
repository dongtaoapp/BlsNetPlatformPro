#pragma once
#include ".\simulatorbase_global.h"
#include ".\VirEventIrp.h"

namespace jysoft { namespace irp {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     时钟事件Irp
	创建人：	 hjg
	创建时间：   2017/2/8
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT CEventIrp_ClockTime : public CVirEventIrp
	{
	public:
		CEventIrp_ClockTime(void);
		virtual ~CEventIrp_ClockTime(void);
	public:
		virtual _IrpType Get_eIrpType() { return eClock_Event; };
		virtual bool isKindOf(const std::string &strClass);
	public:
		inline short  GetValue_ClockEvent() { return m_sClockNum; };
		inline void   SetValue_ClockEvent(short sValue) { m_sClockNum = sValue; };
	protected:
		short        m_sClockNum;    //时钟数值
	public:
		/*******************************************************************************/
		// 函数名称： doPackageIrp
		// 功能：  打包Irp的内容
		// 参数： 
		// 返回值: 
		virtual std::string doPackageIrp() { return ""; };
	public:
		/*******************************************************************************/
		// 函数名称： CreateEvent_ClockIrp
		// 功能： 创建时钟事件Irp类
		// 参数： short sSecond:       
		// 返回值:  
		static CEventIrp_ClockTime * CreateEvent_ClockIrp(short sSecond = 1);
	};

}}
