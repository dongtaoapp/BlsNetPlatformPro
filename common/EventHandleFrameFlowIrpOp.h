#pragma once
#include ".\virhandleirpop.h"

namespace jysoft { namespace irp {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ���ش����������Դ�������ת��IRP
	�����ˣ�	 hjg
	����ʱ�䣺   2009/4/8
	//-----------------------------------------------------------------------------------------------------------------*/
	class AFX_EXT_CLASS CEventHandleFrameFlowIrpOp : public CVirHandleIrpOp
	{
	public:
		CEventHandleFrameFlowIrpOp(void);
		virtual ~CEventHandleFrameFlowIrpOp(void);
	public://���ຯ������
		/*******************************************************************************/
		//���ܣ�����IRP����
		//������CVirtualIrp *pCurrIrp��
		//����ֵ:  �������ٴ���FALSE);
		virtual bool handleIrpOp(CVirtualIrp *pCurrIrp);
	protected:
		/*******************************************************************************/
		//���ܣ���������ת��IRP����
		//������
		//      CVirtualIrp *pCurrIrp��
		//����ֵ:  �������ٴ���FALSE);
		virtual bool doHandleFrameFlowIrpOp(CVirtualIrp *pCurrIrp) = 0;
	};

}}