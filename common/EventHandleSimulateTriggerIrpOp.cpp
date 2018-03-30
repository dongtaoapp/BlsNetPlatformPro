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
	//���ܣ�����IRP����
	//������CVirtualIrp *pCurrIrp��
	//����ֵ:  �������ٴ���FALSE);
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
