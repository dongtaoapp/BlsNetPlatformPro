#pragma once
#include ".\CommonGlobal.h"

//-------------------------------------------------------------------------------------------
//类功能：重载此类的子类可以处理IRP
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
		//功能：处理IRP函数
		//参数：CVirtualIrp *pCurrIrp：
		//返回值:  后续不再处理（false);
		virtual bool handleIrpOp(CVirtualIrp *pCurrIrp) = 0;
	};
}}