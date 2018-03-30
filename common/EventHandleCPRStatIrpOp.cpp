#include ".\VirtualIrp.h"
#include ".\eventhandlecprstatirpop.h"

namespace jysoft { namespace irp {

	CEventHandleCPRStatIrpOp::CEventHandleCPRStatIrpOp(void)
	{
	}

	CEventHandleCPRStatIrpOp::~CEventHandleCPRStatIrpOp(void)
	{
	}

	/*******************************************************************************/
	//功能：处理IRP函数
	//参数：CVirtualIrp *pCurrIrp：
	//返回值:  后续不再处理（FALSE);
	bool CEventHandleCPRStatIrpOp::handleIrpOp(CVirtualIrp *pCurrIrp)
	{
		m_eIrpHandleState  = IH_Execed;
		_IrpType  eIrpType = pCurrIrp->Get_eIrpType();
		if( eIrpType == eCPR_Stat )
		{
			return doHandleCPRStatIrpOp( pCurrIrp );
		}
		return true;
	}

}}
