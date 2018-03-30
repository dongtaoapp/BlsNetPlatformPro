#include ".\eventirp_clocktime.h"

namespace jysoft { namespace irp {

	CEventIrp_ClockTime::CEventIrp_ClockTime(void)
	{
		m_sClockNum  = 1;
	}

	CEventIrp_ClockTime::~CEventIrp_ClockTime(void)
	{
	}

	bool CEventIrp_ClockTime::isKindOf(const std::string &strClass)
	{
		if( strClass == "CEventIrp_ClockTime" )
		{
			return true;
		}
		return CVirEventIrp::isKindOf( strClass );
	}

	/*******************************************************************************/
	// 函数名称： CreateEvent_ClockIrp
	// 功能： 创建时钟事件Irp类
	// 参数： short sSecond:       
	// 返回值:  
	CEventIrp_ClockTime * CEventIrp_ClockTime::CreateEvent_ClockIrp(short sSecond /*=1*/)
	{
		CEventIrp_ClockTime *pEventIrp = new CEventIrp_ClockTime();
		pEventIrp->SetValue_ClockEvent( sSecond );
		return pEventIrp;
	}

}}
