#pragma once
#include <list>
#include ".\scriptflowengine_global.h"

#include "..\Common\VirHandleIrpOp.h"
#include "..\Common\EventHandleClockIrpOp.h"
#include "..\Common\EventHandleSimulateTriggerIrpOp.h"
#include "..\Common\RealTimeDataHandleIrpOp.h"
#include "..\Common\EventHandleCPRStatIrpOp.h"
#include "..\Common\EventHandleCustomIrpOp.h"
#include "..\Common\EventHandleFrameFlowIrpOp.h"

#include "..\Common\CommonGlobal.h"
#include "..\Common\VirtualIrp.h"
#include "..\common\criticalmutex.h"


namespace jysoft { namespace flowEngine {
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     Irp处理集合虚类
	创建人：	 hjg
	创建时间：   2017/2/5
	//-----------------------------------------------------------------------------------------------------------------*/
    class SCRIPTFLOWENGINESHARED_EXPORT IHandleIrpsCollect
	{
	public:
		IHandleIrpsCollect(void);
		virtual ~IHandleIrpsCollect(void);
	public:
		//添加处理IRP的Obj
		virtual void  addNewHandleIrpObj(irp::CVirHandleIrpOp  *pPtrObj, _IrpType eType, bool bAddHead=false);
		virtual void  addNewHandleEventIrpObj(irp::CEventHandleCustomIrpOp *pPtrObj, bool bAddHead=false);
		virtual void  addNewHandleOnlySimulateTriggerEventIrpOp(irp::CEventHandleSimulateTriggerIrpOp *pPtrObj);
		//移除处理IRP的Obj
		virtual void  removeHandleIrpObj(irp::CVirHandleIrpOp  *pPtrObj, _IrpType eType);
		virtual void  removeHandleEventIrpObj(irp::CEventHandleCustomIrpOp *pPtrObj);
		virtual void  removeHandleOnlySimulateTriggerEventIrpOp(irp::CEventHandleSimulateTriggerIrpOp *pPtrObj);
	public:
		//处理消息包
		virtual void OnHandleIrp(irp::CVirtualIrp *pVirIrp);
	protected:
		//对添加的处理IRP的Obj进行异步
		utility::CCriticalMutex   m_cAddHandleIrpOpMutex;
	protected://属性
		std::list<irp::CEventHandleClockIrpOp *>             m_lstHandleClockIrpObjs;
		std::list<irp::CEventHandleCPRStatIrpOp *>           m_lstHandleCPRStatIrpObjs;
		std::list<irp::CEventHandleCustomIrpOp *>            m_lstHandleEventIrpObjs;
		std::list<irp::CEventHandleFrameFlowIrpOp *>         m_lstHandleFrameFlowIrpObjs;
		std::list<irp::CRealTimeDataHandleIrpOp *>           m_lstHandleRealTimeDataIrpObjs;
		std::list<irp::CEventHandleSimulateTriggerIrpOp *>   m_lstHandleSimulateTriggerIrpObjs;
	};
}}
