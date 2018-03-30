#pragma once
#include ".\simulatorbase_global.h"

#include "..\common\iupdateshowvir.h"


namespace jysoft { namespace simulator { namespace base {

    class SIMULATORBASESHARED_EXPORT CShowPaceUpdateInterface : public IUpdateShowVir
	{
	public:
		CShowPaceUpdateInterface(void);
		virtual ~CShowPaceUpdateInterface(void);
	public:
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	public:
		virtual bool isKindOf(const std::string &className);
	protected:
		//显示起搏设置
        virtual void ShowPaceset(bool bEnablePace, short sElectric) = 0;
		//对接显示后通知
		virtual void doLinkPacesetUpdateShow() { };
		//断开显示后通知
		virtual void cutLinkPacesetUpdateShow() { };
	public:
		/*******************************************************************************/
		// 函数名称： OnShowPaceset
		// 功能：   更新起搏的设置
		// 参数：   
        //          bool bEnablePace:  是否能起搏
		//          short sElectric:   电流量
		// 返回值:
        void OnShowPaceset(bool bEnablePace, short sElectric);
	};

}}}
