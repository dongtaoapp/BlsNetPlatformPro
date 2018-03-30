#pragma once
#include "virhandleirpop.h"

namespace jysoft { namespace irp {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ���ش����������Դ���ģ���˴����¼�IRP
	�����ˣ�	 hjg
	����ʱ�䣺   2009/5/4
	//-----------------------------------------------------------------------------------------------------------------*/
	class AFX_EXT_CLASS CEventHandleSimulateTriggerIrpOp : public CVirHandleIrpOp
	{
	public:
		CEventHandleSimulateTriggerIrpOp(void);
		virtual ~CEventHandleSimulateTriggerIrpOp(void);
	public://���ຯ������
		/*******************************************************************************/
		//���ܣ�����IRP����
		//������CVirtualIrp *pCurrIrp��
		//����ֵ:  �������ٴ���FALSE);
		virtual bool handleIrpOp(CVirtualIrp *pCurrIrp);
	protected:
		/*******************************************************************************/
		//���ܣ�����ģ���˴����¼�IRP����
		//������
		//      CVirtualIrp *pCurrIrp��
		//����ֵ:  �������ٴ���FALSE);
		virtual bool doHandleSimulateTriggerIrpOp(CVirtualIrp *pCurrIrp) = 0;
	};

}}