#pragma once
#include ".\virhandleirpop.h"

namespace jysoft { namespace irp {
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ���ش����������Դ���CPR����ͳ�ƽ��IRP
	�����ˣ�	 hjg
	����ʱ�䣺   2009/4/8
	//-----------------------------------------------------------------------------------------------------------------*/
	class AFX_EXT_CLASS CEventHandleCPRStatIrpOp : public CVirHandleIrpOp
	{
	public:
		CEventHandleCPRStatIrpOp(void);
		virtual ~CEventHandleCPRStatIrpOp(void);
	public://���ຯ������
		/*******************************************************************************/
		//���ܣ�����IRP����
		//������CVirtualIrp *pCurrIrp��
		//����ֵ:  �������ٴ���FALSE);
		virtual bool handleIrpOp(CVirtualIrp *pCurrIrp);
	protected:
		/*******************************************************************************/
		//���ܣ�����CPR����ͳ�ƽ��IRP����
		//������
		//      CVirtualIrp *pCurrIrp��
		//����ֵ:  �������ٴ���FALSE);
		virtual bool doHandleCPRStatIrpOp(CVirtualIrp *pCurrIrp) = 0;
	};

}}