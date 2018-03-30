#include ".\eventhandlesimulatetriggerirpop.h"
#include ".\VirtualIrp.h"


namespace jysoft { namespace irp {

	CEventHandleSimulateTriggerIrpOp::CEventHandleSimulateTriggerIrpOp(void)
	{
	}

	CEventHandleSimulateTriggerIrpOp::~CEventHandleSimulateTriggerIrpOp(void)
	{
	}

	/*******************************************************************************/
	//功能：处理IRP函数
	//参数：CVirtualIrp *pCurrIrp：
	//返回值:  后续不再处理（FALSE);
	bool CEventHandleSimulateTriggerIrpOp::handleIrpOp(CVirtualIrp *pCurrIrp)
	{
		m_eIrpHandleState  = IH_Execed;
		_IrpType  eIrpType = pCurrIrp->Get_eIrpType();
		if( eIrpType == eSimulateTrigger_Event )
		{
			return doHandleSimulateTriggerIrpOp( pCurrIrp );
		}
		return true;
	}

}}
