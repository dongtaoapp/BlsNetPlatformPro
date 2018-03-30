#include ".\VirtualIrp.h"
#include ".\realtimedatahandleirpop.h"

namespace jysoft { namespace irp {

	CRealTimeDataHandleIrpOp::CRealTimeDataHandleIrpOp(void)
	{
	}

	CRealTimeDataHandleIrpOp::~CRealTimeDataHandleIrpOp(void)
	{
	}

	/*******************************************************************************/
	//功能：处理IRP函数
	//参数：CVirtualIrp *pCurrIrp：
	//返回值:  后续不再处理（FALSE);
	bool CRealTimeDataHandleIrpOp::handleIrpOp(CVirtualIrp *pCurrIrp)
	{
		m_eIrpHandleState  = IH_Execed;
		_IrpType  eIrpType = pCurrIrp->Get_eIrpType();
		if( eIrpType == eRealTimeData )
		{
			return doHandleRealTimeDataIrpOp( pCurrIrp );
		}
        return true;
	}

}}
