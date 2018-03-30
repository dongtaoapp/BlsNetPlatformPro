#pragma once
#include ".\simulatorbase_global.h"

#include "..\common\iupdateshowvir.h"

namespace jysoft{  namespace cpr {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     CPR操作细节动作显示接口
	创建人：	 hjg
	创建时间：   2017/2/25
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT CShowCPRActUpdateInterface : public IUpdateShowVir
	{
	public:
		CShowCPRActUpdateInterface(void);
		virtual ~CShowCPRActUpdateInterface(void);
	public://接口函数重载
		virtual bool isKindOf(const std::string &className);
	public:
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	protected:
		//对接显示后通知
		virtual void doLinkCPRDetailActUpdateShow() { };
		//断开显示后通知
		virtual void cutLinkCPRDetailActUpdateShow() { };
		virtual void RaiseJowAct(bool bLookUp) = 0;
		//人工呼吸开始\结束(TRUE:开始；FALSE:结束)
		virtual void BreathStateAct(bool bState) = 0;
		//按压开始\结束(TRUE:开始；FALSE:结束)
		virtual void PressureStateAct(bool bState) = 0;
		//完成五个循环的CPR
		virtual void FiveCycleCompleteAct() = 0;
		//结束CPR操作
		virtual void FinishCPROperator(bool bSecceed) = 0;
	public:
		//仰头、平躺
		void OnRaiseJowAct(bool bLookUp);
		//人工呼吸开始\结束(TRUE:开始；FALSE:结束)
		void OnBreathStateAct(bool bState);
		//按压开始\结束(TRUE:开始；FALSE:结束)
		void OnPressureStateAct(bool bState);
		//完成五个循环的CPR
		virtual void OnFiveCycleCompleteAct();
		//结束CPR操作
		void OnFinishCPROperator(bool bSecceed);
	};
}}
