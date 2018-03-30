#pragma once
#include ".\simulatorbase_global.h"

#include "..\Common\IUpdateshowVir.h"

namespace jysoft { namespace simulator { namespace base {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     当前脚本运行的场景持续时间显示接口
	创建人：	 hjg
	创建时间：   2009/6/19
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORBASESHARED_EXPORT CShowFrameTimeUpdateInterface : public IUpdateShowVir
	{
	public:
		CShowFrameTimeUpdateInterface(void);
		virtual ~CShowFrameTimeUpdateInterface(void);
	public:
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	public:
		virtual bool isKindOf(const std::string &className);
	protected:
		/*******************************************************************************/
		// 函数名称： ShowFrameTimeUpdate
		// 功能： 显示当前运行场景的时间
		// 参数： 
		//        long  lFrameTime：    场景持续时间
		// 返回值:  
		virtual void ShowFrameTimeUpdate(long  lFrameTime) = 0;
		//对接显示后通知
		virtual void doLinkFrameTimeUpdateShow() { };
		//断开显示后通知
		virtual void cutLinkFrameTimeUpdateShow() { };
	public:
		//显示当前运行场景的时间
		void OnShowFrameTimeUpdate(long  lFrameTime);
	};
}}}
