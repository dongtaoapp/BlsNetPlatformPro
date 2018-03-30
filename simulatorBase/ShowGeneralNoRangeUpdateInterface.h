#pragma once
#include ".\simulatorbase_global.h"

#include "..\common\iupdateshowvir.h"

namespace jysoft { namespace simulator { namespace base {

    class SIMULATORBASESHARED_EXPORT CShowGeneralNoRangeUpdateInterface : public IUpdateShowVir
	{
	public:
		CShowGeneralNoRangeUpdateInterface(void);
		virtual ~CShowGeneralNoRangeUpdateInterface(void);
	public:
		virtual bool isKindOf(const std::string &className);
	public:
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	protected:
		//显示的数值
		virtual void ShowPhystValue(float fPhystValue) = 0;
		//对接显示后通知
		virtual void doLinkGeneralNoRangeUpdateShow() { };
		//断开显示后通知
		virtual void cutLinkGeneralNoRangeUpdateShow() { };
	public:
		/*******************************************************************************/
		// 函数名称： OnShowPhystValue
		// 功能： 显示的数值
		// 参数： float fPhystValue:              值
		// 返回值:  
		void OnShowPhystValue(float fPhystValue);
	};

}}}
