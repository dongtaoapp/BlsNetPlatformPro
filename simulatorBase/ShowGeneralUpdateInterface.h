#pragma once
#include ".\simulatorbase_global.h"

#include "..\common\iupdateshowvir.h"


namespace jysoft { namespace simulator { namespace base {
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     信息显示接口
	创建人：	 hjg
	创建时间：   2016/8/21
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORBASESHARED_EXPORT CShowGeneralUpdateInterface : public IUpdateShowVir
	{
	public:
		CShowGeneralUpdateInterface(void);
		virtual ~CShowGeneralUpdateInterface(void);
	public:
		virtual bool isKindOf(const std::string &className);
	public:
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	protected:
		//显示的数值
		virtual void ShowPhystValue(float fValue) = 0;
		//显示正常的范围区间
		virtual void ShowPhystRange(float fMinValue, float fMaxValue) = 0;
		//对接显示后通知
		virtual void doLinkGeneralUpdateShow() { };
		//断开显示后通知
		virtual void cutLinkGeneralUpdateShow() { };
	public:
		/*******************************************************************************/
		// 函数名称： OnShowPhystValue
		// 功能： 显示的数值
		// 参数： float nPhystValue:              值
		// 返回值:  
		void OnShowPhystValue(float nPhystValue);
		/*******************************************************************************/
		// 函数名称： OnShowPhystRange
		// 功能： 显示正常的范围区间
		// 参数： float fMinValue:              区间最小值
		//        float fMaxValue:              区间最大值
		// 返回值:  
		void OnShowPhystRange(float fMinValue, float fMaxValue);
	};

}}}
