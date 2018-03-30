#pragma once
#include <string>
#include ".\simulatorbase_global.h"

#include "..\common\iupdateshowvir.h"

namespace jysoft { namespace simulator { namespace base {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     有创血压信息显示接口
	创建人：	 hjg
	创建时间：   2016/8/5
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORBASESHARED_EXPORT CShowABPUpdateInterface : public IUpdateShowVir
	{
	public:
		CShowABPUpdateInterface(void);
		virtual ~CShowABPUpdateInterface(void);
	public:
		virtual bool isKindOf(const std::string &className);
	public:
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	protected:
		//显示有创血压的数值
		virtual void ShowABPValue(int nShrinkValue, int nStretchValue) = 0;
		//对接显示后通知
		virtual void doLinkABPUpdateShow() { };
		//断开显示后通知
		virtual void cutLinkABPUpdateShow() { };
	public:
		/*******************************************************************************/
		// 函数名称： OnShowABPValue
		// 功能： 显示有创血压的数值
		// 参数： int nShrinkValue:              收缩压
		//        int nStretchValue:             舒张压
		// 返回值:  
		void OnShowABPValue(int nShrinkValue, int nStretchValue);
		void OnShowABPValue(const std::string &strABP);
	public:
		//解析有创血压：nShrink：收缩压；nStretch：舒张压
		static bool ParseABPToShrinkAndnStretch(const std::string &strABP, int &nShrink, int &nStretch);
	};

}}}
