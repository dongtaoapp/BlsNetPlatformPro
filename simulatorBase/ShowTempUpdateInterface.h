#pragma once
#include ".\simulatorbase_global.h"

#include "..\common\iupdateshowvir.h"


namespace jysoft { namespace simulator { namespace base {

    class SIMULATORBASESHARED_EXPORT CShowTempUpdateInterface : public IUpdateShowVir
	{
	public:
		CShowTempUpdateInterface(void);
		virtual ~CShowTempUpdateInterface(void);
	public:
		virtual bool isKindOf(const std::string &className);
	public:
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	protected:
		//显示的数值
		virtual void ShowTempValue(float fValue) = 0;
		//显示正常的范围区间
		virtual void ShowTempRange(float fMinValue, float fMaxValue) = 0;
		//对接显示后通知
		virtual void doLinkTempUpdateShow() { };
		//断开显示后通知
		virtual void cutLinkTempUpdateShow() { };
	public:
		/*******************************************************************************/
		// 函数名称： OnShowTempValue
		// 功能： 显示的数值
		// 参数： int nSpO2Value:              值
		// 返回值:  
		void OnShowTempValue(float fValue);
		/*******************************************************************************/
		// 函数名称： OnShowTempRange
		// 功能： 显示正常的范围区间
		// 参数： float fMinValue:              区间最小值
		//        float fMaxValue:              区间最大值
		// 返回值:  
		void OnShowTempRange(float fMinValue, float fMaxValue);
	};

}}}
