#pragma once
#include ".\virhandleirpop.h"

namespace jysoft { namespace irp {
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ���ش����������Դ������¼�IRP
	�����ˣ�	 hjg
	����ʱ�䣺   2017/2/8
	//-----------------------------------------------------------------------------------------------------------------*/
	class AFX_EXT_CLASS CEventHandleCustomIrpOp : public CVirHandleIrpOp
	{
	public:
		CEventHandleCustomIrpOp(void);
		virtual ~CEventHandleCustomIrpOp(void);
	public://���ຯ������
		/*******************************************************************************/
		//���ܣ�����IRP����
		//������CVirtualIrp *pCurrIrp��
		//����ֵ:  �������ٴ���FALSE);
		virtual bool handleIrpOp(CVirtualIrp *pCurrIrp);
	public:
		/*******************************************************************************/
		//���ܣ��������¼�IRP����
		//������
		//      CVirtualIrp *pCurrIrp��
		//����ֵ:  �������ٴ���FALSE);
		virtual bool doHandleCustomEventIrpOp(CVirtualIrp *pCurrIrp) = 0;
	};
}}