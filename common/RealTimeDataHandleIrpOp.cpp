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
	//���ܣ�����IRP����
	//������CVirtualIrp *pCurrIrp��
	//����ֵ:  �������ٴ���FALSE);
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
