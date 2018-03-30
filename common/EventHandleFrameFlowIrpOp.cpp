#include ".\VirtualIrp.h"
#include ".\eventhandleframeflowirpop.h"

namespace jysoft { namespace irp {

	CEventHandleFrameFlowIrpOp::CEventHandleFrameFlowIrpOp(void)
	{
	}

	CEventHandleFrameFlowIrpOp::~CEventHandleFrameFlowIrpOp(void)
	{
	}

	/*******************************************************************************/
	//功能：处理IRP函数
	//参数：CVirtualIrp *pCurrIrp：
	//返回值:  后续不再处理（FALSE);
	bool CEventHandleFrameFlowIrpOp::handleIrpOp(CVirtualIrp *pCurrIrp)
	{
		m_eIrpHandleState  = IH_Execed;
		_IrpType  eIrpType = pCurrIrp->Get_eIrpType();
		if( eIrpType == eFrameModify_Event )
		{
			return doHandleFrameFlowIrpOp( pCurrIrp );
		}
		return true;
	}
}}
