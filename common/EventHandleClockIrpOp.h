#pragma once
#include ".\virhandleirpop.h"

namespace jysoft { namespace irp {
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ���ش����������Դ���ʱ���¼�IRP
	�����ˣ�	 hjg
	����ʱ�䣺   2009/4/8
	//-----------------------------------------------------------------------------------------------------------------*/
	class AFX_EXT_CLASS CEventHandleClockIrpOp : public CVirHandleIrpOp
	{
	public:
		CEventHandleClockIrpOp(void);
		virtual ~CEventHandleClockIrpOp(void);
	public://���ຯ������
		/*******************************************************************************/
		//���ܣ�����IRP����
		//������CVirtualIrp *pCurrIrp��
		//����ֵ:  �������ٴ���FALSE);
		virtual bool handleIrpOp(CVirtualIrp *pCurrIrp);
	protected:
		/*******************************************************************************/
		//���ܣ�����ʱ���¼�IRP����
		//������
		//      CVirtualIrp *pCurrIrp��
		//����ֵ:  �������ٴ���FALSE);
		virtual bool doHandleClockIrpOp(CVirtualIrp *pCurrIrp) = 0;
	};
}}