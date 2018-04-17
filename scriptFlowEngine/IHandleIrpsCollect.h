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
	��˵����     Irp����������
	�����ˣ�	 hjg
	����ʱ�䣺   2017/2/5
	//-----------------------------------------------------------------------------------------------------------------*/
    class SCRIPTFLOWENGINESHARED_EXPORT IHandleIrpsCollect
	{
	public:
		IHandleIrpsCollect(void);
		virtual ~IHandleIrpsCollect(void);
	public:
		//��Ӵ���IRP��Obj
		virtual void  addNewHandleIrpObj(irp::CVirHandleIrpOp  *pPtrObj, _IrpType eType, bool bAddHead=false);
		virtual void  addNewHandleEventIrpObj(irp::CEventHandleCustomIrpOp *pPtrObj, bool bAddHead=false);
		virtual void  addNewHandleOnlySimulateTriggerEventIrpOp(irp::CEventHandleSimulateTriggerIrpOp *pPtrObj);
		//�Ƴ�����IRP��Obj
		virtual void  removeHandleIrpObj(irp::CVirHandleIrpOp  *pPtrObj, _IrpType eType);
		virtual void  removeHandleEventIrpObj(irp::CEventHandleCustomIrpOp *pPtrObj);
		virtual void  removeHandleOnlySimulateTriggerEventIrpOp(irp::CEventHandleSimulateTriggerIrpOp *pPtrObj);
	public:
		//������Ϣ��
		virtual void OnHandleIrp(irp::CVirtualIrp *pVirIrp);
	protected:
		//����ӵĴ���IRP��Obj�����첽
		utility::CCriticalMutex   m_cAddHandleIrpOpMutex;
	protected://����
		std::list<irp::CEventHandleClockIrpOp *>             m_lstHandleClockIrpObjs;
		std::list<irp::CEventHandleCPRStatIrpOp *>           m_lstHandleCPRStatIrpObjs;
		std::list<irp::CEventHandleCustomIrpOp *>            m_lstHandleEventIrpObjs;
		std::list<irp::CEventHandleFrameFlowIrpOp *>         m_lstHandleFrameFlowIrpObjs;
		std::list<irp::CRealTimeDataHandleIrpOp *>           m_lstHandleRealTimeDataIrpObjs;
		std::list<irp::CEventHandleSimulateTriggerIrpOp *>   m_lstHandleSimulateTriggerIrpObjs;
	};
}}
