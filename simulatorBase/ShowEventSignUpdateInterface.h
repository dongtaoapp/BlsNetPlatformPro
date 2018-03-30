#pragma once
#include ".\simulatorbase_global.h"

#include "..\Common\IUpdateshowVir.h"
#include "..\Common\CommonGlobal.h"

namespace jysoft { namespace simulator { namespace base {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     事件显示接口
	创建人：	 las
	创建时间：   2009/6/18
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT CShowEventSignUpdateInterface : public IUpdateShowVir
	{
	public:
		CShowEventSignUpdateInterface(void);
		virtual ~CShowEventSignUpdateInterface(void);
	public:
		virtual bool isKindOf(const std::string &className);
	public:
		// 添加新的标志
		void OnAddNewEventSign(eEventSign eSign);
		// 移除标志
		void OnRemoveEventSign(eEventSign eSign);
		//默认设置
		void OnDefaultHandle(void);
	public:
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	public:
		// 除颤侦测事件
		void OnSimulateDefibrTriggerEventUpdateShow( short sEnergy = -1 );
		// 脉搏检查事件（1:颈动脉,2:左股动脉,3:右股动脉,4:右臂肱动脉,5:右臂桡动脉,6:左臂肱动脉,7:左臂桡动脉,8:右腿腘动脉,9:右足背动脉, 10:左腿腘动脉, 11:左足背动脉）
		void OnSimulatePulseCheckTriggerEventUpdateShow( short sPosition = 1 );
		// CPR侦测事件
		void OnSimulateCPRTriggerEventUpdateShow();
		// 起搏侦测事件
		void OnSimulatePaceTriggerEventUpdateShow( short sHeartRate );
		// 气管插管事件
		void OnSimulateIntubateTriggerEventUpdateShow( short sPosition );
	protected:
		// 添加新的标志
		virtual void AddNewEventSign(eEventSign eSign) = 0;
		// 移除标志
		virtual void RemoveEventSign(eEventSign eSign) = 0;
		//默认设置
		virtual void DefaultHandle(void) = 0;
		// 除颤侦测事件
		virtual void SimulateDefibrTriggerEventUpdateShow( short sEnergy = -1 ) = 0;
		// 脉搏检查事件（1:颈动脉）
		virtual void SimulatePulseCheckTriggerEventUpdateShow( short sPosition ) = 0;
		// CPR侦测事件
		virtual void SimulateCPRTriggerEventUpdateShow() = 0;
		// 起搏侦测事件
		virtual void SimulatePaceTriggerEventUpdateShow( short sHeartRate ) = 0;
		// 气管插管事件
		virtual void SimulateIntubateTriggerEventUpdateShow( short sPosition ) = 0;
		//对接显示后通知
		virtual void doLinkEventSignUpdateShow() { };
		//断开显示后通知
		virtual void cutLinkEventSignUpdateShow() { };
	};

}}}
