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
	//���ܣ�����IRP����
	//������CVirtualIrp *pCurrIrp��
	//����ֵ:  �������ٴ���FALSE);
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
