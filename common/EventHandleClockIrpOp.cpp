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
	//���ܣ�����IRP����
	//������CVirtualIrp *pCurrIrp��
	//����ֵ:  �������ٴ���FALSE);
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
