#pragma once
#include ".\simulatorbase_global.h"

#include "..\Common\IUpdateshowVir.h"

namespace jysoft { namespace simulator { namespace base {
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     当前脚本运行的场景名称显示接口
	创建人：	 hjg
	创建时间：   2016/6/19
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT CShowFrameNameUpdateInterface  : public IUpdateShowVir
	{
	public:
		CShowFrameNameUpdateInterface(void);
		virtual ~CShowFrameNameUpdateInterface(void);
	public:
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	public:
		virtual bool isKindOf(const std::string &className);
	protected:
		/*******************************************************************************/
		// 函数名称： ShowFrameNameUpdate
		// 功能： 显示当前运行场景的名称
		// 参数： unsigned long dwFrameId: 场景标识号
		// 返回值:  
		virtual void ShowFrameNameUpdate(unsigned long dwFrameId) = 0;
		//对接显示后通知
		virtual void doLinkFrameNameUpdateShow() { };
		//断开显示后通知
		virtual void cutLinkFrameNameUpdateShow() { };
	public:
		//显示当前运行场景的名称
		void OnShowFrameNameUpdate(unsigned long dwFrameId);
	};

}}}
