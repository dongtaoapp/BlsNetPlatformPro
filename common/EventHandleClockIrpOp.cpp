#include ".\VirtualIrp.h"
#include ".\eventhandleclockirpop.h"

namespace jysoft { namespace irp {

	CEventHandleClockIrpOp::CEventHandleClockIrpOp(void)
	{
	}

	CEventHandleClockIrpOp::~CEventHandleClockIrpOp(void)
	{
	}

	/*******************************************************************************/
	//功能：处理IRP函数
	//参数：CVirtualIrp *pCurrIrp：
	//返回值:  后续不再处理（FALSE);
	bool CEventHandleClockIrpOp::handleIrpOp(CVirtualIrp *pCurrIrp)
	{
		m_eIrpHandleState  = IH_Execed;
		_IrpType  eIrpType = pCurrIrp->Get_eIrpType();
		if( eIrpType == eClock_Event )
		{
			return doHandleClockIrpOp( pCurrIrp );
		}
		return true;
	}

}}
