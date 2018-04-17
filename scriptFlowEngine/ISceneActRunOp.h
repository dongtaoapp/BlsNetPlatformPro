#pragma once

#include "..\Common\CommonGlobal.h"

#include "..\SimulatorBase\VirEventIrp.h"
#include "..\SimulatorBase\EventIrp_ClockTime.h"


namespace jysoft { namespace flowEngine 
{
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     情景操作接口类
	创建人：	 hjg
	创建时间：   2013/11/17
	//-----------------------------------------------------------------------------------------------------------------*/
	class  ISceneActRunOp
	{
	public:
		ISceneActRunOp(void);
		virtual ~ISceneActRunOp(void);
	protected:
		short                         m_sActTime;    //激活时间（-1：未激活）
	public:
		/*******************************************************************************/
		//功能：处理事件IRP函数虚函数
		//参数：
		//      CVirEventIrp *pCurrEventIrp：
		//      /*out*/_ScheduleSceneState &eSceneState:    
		//返回值:  触发事件是否满足(TURE:满足；FALSE:不满足)
		virtual bool DoHandleEventIrp(irp::CVirEventIrp *pCurrEventIrp, /*out*/_ScheduleSceneState &eSceneState) = 0;
		/*******************************************************************************/
		//功能：处理时钟事件IRP函数
		//参数：
		//      CEventIrp_ClockTime *pCurrClockTimeIrp：
		//返回值:  后续不再处理（FALSE);
		virtual bool DoHandleClockIrpOp(irp::CEventIrp_ClockTime *pCurrClockTimeIrp, /*out*/_ScheduleSceneState &eSceneState) = 0;
		/*******************************************************************************/
		//功能：激活情景框的处理状态
		//参数：   
		//      BOOL bReactive:     是否重新激活
		//返回值: 
		virtual void DoStateActiveSceneFrame(bool bReactive) = 0;
	public:
		//返回情景框的ID值
		virtual unsigned short Get_SceneActFrameId() = 0;
	};
}}