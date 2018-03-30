#pragma once
#include ".\simulatorbase_global.h"

#include "..\common\iupdateshowvir.h"

namespace jysoft { namespace simulator { namespace base {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     血氧信息显示接口
	创建人：	 hjg
	创建时间：   2008/8/5
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT CShowSpO2UpdateInterface : public IUpdateShowVir
	{
	public:
		CShowSpO2UpdateInterface(void);
		virtual ~CShowSpO2UpdateInterface(void);
	public:
		virtual bool isKindOf(const std::string &className);
	protected:
		//显示血氧的数值
		virtual void ShowSpO2Value(int nSpO2Value) = 0;
		//显示血氧正常的范围区间
		virtual void ShowSpO2Range(int nMinValue, int nMaxValue) = 0;
		//对接显示后通知
		virtual void doLinkSpO2UpdateShow() { };
		//断开显示后通知
		virtual void cutLinkSpO2UpdateShow() { };
	public:
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	public:
		/*******************************************************************************/
		// 函数名称： OnShowSpO2Value
		// 功能： 显示血氧的数值
		// 参数： int nSpO2Value:              血氧值（单位：百分比） 
		// 返回值:  
		void OnShowSpO2Value(int nSpO2Value);
		/*******************************************************************************/
		// 函数名称： OnShowSpO2Range
		// 功能： 显示血氧正常的范围区间
		// 参数： int nMinValue:              区间最小血氧值（单位：百分比） 
		//        int nMaxValue:              区间最大血氧值（单位：百分比） 
		// 返回值:  
		void OnShowSpO2Range(int nMinValue, int nMaxValue);
	};
}}}
