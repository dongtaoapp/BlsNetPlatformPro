#pragma once
#include ".\CommonGlobal.h"

//-------------------------------------------------------------------------------------------
//�๦�ܣ����ش����������Դ���IRP
//-------------------------------------------------------------------------------------------
namespace jysoft { namespace irp {

	class CVirtualIrp;
	class AFX_EXT_CLASS CVirHandleIrpOp
	{
	public:
		CVirHandleIrpOp(void);
		virtual ~CVirHandleIrpOp(void);
	public:
		eIrpHandleState         m_eIrpHandleState;
	public:
		/*******************************************************************************/
		//���ܣ�����IRP����
		//������CVirtualIrp *pCurrIrp��
		//����ֵ:  �������ٴ���false);
		virtual bool handleIrpOp(CVirtualIrp *pCurrIrp) = 0;
	};
}}