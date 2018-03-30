#pragma once
#include ".\simulatorbase_global.h"

#include "..\common\iupdateshowvir.h"

namespace jysoft { namespace simulator { namespace base {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     当前脚本运行时间显示接口
	创建人：	 hjg
	创建时间：   2009/6/19
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT CShowScenarioRunTimeUpdateInterface : public IUpdateShowVir
	{
	public:
		CShowScenarioRunTimeUpdateInterface(void);
		virtual ~CShowScenarioRunTimeUpdateInterface(void);
	public:
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	public:
		virtual bool isKindOf(const std::string &className);
	protected:
		/*******************************************************************************/
		// 函数名称： ShowScenarioRunTimeUpdate
		// 功能： 显示当前脚本运行时间
		// 参数： 
        //        uScenarioTime：    脚本运行时间
		// 返回值:  
        virtual void ShowScenarioRunTimeUpdate(unsigned long  uScenarioTime) = 0;
		//对接显示后通知
		virtual void doLinkScenarioRunTimeUpdateShow() { };
		//断开显示后通知
		virtual void cutLinkScenarioRunTimeUpdateShow() { };
	public:
		//显示当前脚本运行时间
        void OnShowScenarioRunTimeUpdate(unsigned long  uScenarioTime);
	};

}}}
