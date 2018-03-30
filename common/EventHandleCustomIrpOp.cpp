#include ".\eventhandlecustomirpop.h"

#include "..\Common\VirtualIrp.h"

namespace jysoft { namespace irp 
{
	CEventHandleCustomIrpOp::CEventHandleCustomIrpOp(void)
	{
	}

	CEventHandleCustomIrpOp::~CEventHandleCustomIrpOp(void)
	{
	}

	/*******************************************************************************/
	//功能：处理IRP函数
	//参数：CVirtualIrp *pCurrIrp：
	//返回值:  后续不再处理（FALSE);
	bool CEventHandleCustomIrpOp::handleIrpOp(CVirtualIrp *pCurrIrp)
	{
		m_eIrpHandleState  = IH_Execed;
		_IrpType  eIrpType = pCurrIrp->Get_eIrpType();
		if( eIrpType == eABC_Event || eIrpType == eDrug_Event || eIrpType == eMisce_Event \
					   || eIrpType == eSimulateTrigger_Event || eIrpType == eCPR_Stat || eIrpType == eOxygen_Event )
		{
			return doHandleCustomEventIrpOp( pCurrIrp );
		}
		return true;
	}
}}
