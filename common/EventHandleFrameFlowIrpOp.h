#pragma once
#include ".\virhandleirpop.h"

namespace jysoft { namespace irp {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     重载此类的子类可以处理场景框转移IRP
	创建人：	 hjg
	创建时间：   2009/4/8
	//-----------------------------------------------------------------------------------------------------------------*/
	class AFX_EXT_CLASS CEventHandleFrameFlowIrpOp : public CVirHandleIrpOp
	{
	public:
		CEventHandleFrameFlowIrpOp(void);
		virtual ~CEventHandleFrameFlowIrpOp(void);
	public://基类函数重载
		/*******************************************************************************/
		//功能：处理IRP函数
		//参数：CVirtualIrp *pCurrIrp：
		//返回值:  后续不再处理（FALSE);
		virtual bool handleIrpOp(CVirtualIrp *pCurrIrp);
	protected:
		/*******************************************************************************/
		//功能：处理场景框转移IRP函数
		//参数：
		//      CVirtualIrp *pCurrIrp：
		//返回值:  后续不再处理（FALSE);
		virtual bool doHandleFrameFlowIrpOp(CVirtualIrp *pCurrIrp) = 0;
	};

}}