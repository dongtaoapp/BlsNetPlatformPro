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
	//���ܣ�����IRP����
	//������CVirtualIrp *pCurrIrp��
	//����ֵ:  �������ٴ���FALSE);
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
