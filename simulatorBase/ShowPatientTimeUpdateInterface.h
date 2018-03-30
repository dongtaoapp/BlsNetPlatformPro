#pragma once
#include ".\simulatorbase_global.h"

#include "..\common\iupdateshowvir.h"

namespace jysoft { namespace simulator { namespace base {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     当前脚本运行的病人时间显示接口
	创建人：	 hjg
	创建时间：   2016/6/19
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT CShowPatientTimeUpdateInterface : public IUpdateShowVir
	{
	public:
		CShowPatientTimeUpdateInterface(void);
		virtual ~CShowPatientTimeUpdateInterface(void);
	public:
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	public:
		virtual bool isKindOf(const std::string &className);
	protected:
		/*******************************************************************************/
		// 函数名称： ShowPatientTimeUpdate
		// 功能： 显示当前病人的时间
		// 参数： 
		//        long  lPatientTime：    病人时间
		// 返回值:  
		virtual void ShowPatientTimeUpdate(long  lPatientTime) = 0;
		//对接显示后通知
		virtual void doLinkPatientTimeUpdateShow() { };
		//断开显示后通知
		virtual void cutLinkPatientTimeUpdateShow() { };
	public:
		//显示当前病人的时间
		void OnShowPatientTimeUpdate(long  lPatientTime);
		//清除当前病人的时间
		virtual void OnClearShowPateintTimeUpdate() = 0;
	};

}}}
