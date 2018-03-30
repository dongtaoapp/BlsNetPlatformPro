#pragma once
#include ".\simulatorbase_global.h"

#include "..\common\iupdateshowvir.h"

namespace jysoft { namespace simulator { namespace base {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     呼出CO2浓度信息显示接口
	创建人：	 hjg
	创建时间：   2008/8/6
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT CShowEtCO2UpdateInterface : public IUpdateShowVir
	{
	public:
		CShowEtCO2UpdateInterface(void);
		virtual ~CShowEtCO2UpdateInterface(void);
	public:
		bool isKindOf(const std::string &className);
	protected:
		//显示呼出CO2浓度
		virtual void ShowEtCO2Value(int nCO2Value) = 0;
		//显示呼出CO2浓度正常的范围区间
		virtual void ShowEtCO2Range(int nMinCO2Value, int nMaxCO2Value) = 0;
		//对接显示后通知
		virtual void doLinkEtCO2UpdateShow() { };
		//断开显示后通知
		virtual void cutLinkEtCO2UpdateShow() { };
	public:
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	public:
		/*******************************************************************************/
		// 函数名称： OnShowEtCO2Value
		// 功能： 显示呼出CO2浓度
		// 参数： int nCO2Value:                CO2浓度（单位：百分百）
		// 返回值:  
		void OnShowEtCO2Value(int nCO2Value);
		/*******************************************************************************/
		// 函数名称： OnShowEtCO2Range
		// 功能： 显示呼出CO2浓度正常的范围区间
		// 参数： int nMinCO2Value:              区间最小CO2浓度（单位：百分百） 
		//        int nMaxCO2Value:              区间最大CO2浓度（单位：百分百） 
		// 返回值:  
		void OnShowEtCO2Range(int nMinCO2Value, int nMaxCO2Value);
	};

}}}
