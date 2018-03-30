#pragma once
#include ".\VirHandleIrpOp.h"

namespace jysoft { namespace irp {
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ���ش����������Դ���ʵʱ��������IRP
	�����ˣ�	 hjg
	����ʱ�䣺   2009/4/8
	//-----------------------------------------------------------------------------------------------------------------*/
	class AFX_EXT_CLASS CRealTimeDataHandleIrpOp : public CVirHandleIrpOp
	{
	public:
		CRealTimeDataHandleIrpOp(void);
		virtual ~CRealTimeDataHandleIrpOp(void);
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
		virtual bool doHandleRealTimeDataIrpOp(CVirtualIrp *pCurrIrp) = 0;
	};

}}