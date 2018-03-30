#pragma once
#include ".\simulatorbase_global.h"

#include "..\common\IUpdateshowvir.h"

namespace jysoft { namespace simulator { namespace base {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     无创血压信息显示接口
	创建人：	 hjg
	创建时间：   2016/5/4
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT CShowNIBPUpdateInterface : public IUpdateShowVir
	{
	public:
		CShowNIBPUpdateInterface(void);
		virtual ~CShowNIBPUpdateInterface(void);
	public:
		virtual bool isKindOf(const std::string &className);
	protected:
		//显示无创血压的数值
		virtual void ShowNIBPValue(int nShrinkValue, int nStretchValue) = 0;
		virtual void ShowNIBPSoundValue(int nNIBPSoundValue) = 0;
		//-----------------------------------------------------------------------------------
		//对接显示后通知
		virtual void doLinkNIBPUpdateShow() { };
		//断开显示后通知
		virtual void cutLinkNIBPUpdateShow() { };
	public:
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	public:
		/*******************************************************************************/
		// 函数名称： OnShowNIBPValue
		// 功能： 显示无创血压的数值
		// 参数： int nShrinkValue:              收缩压
		//        int nStretchValue:             舒张压
		// 返回值:  
		void OnShowNIBPValue(int nShrinkValue, int nStretchValue);
		/*******************************************************************************/
		// 函数名称： OnShowKorotkoffVolum
		// 功能： 显示无创血压声响的数值
		// 参数： int nNIBPSoundValue:              无创血压声响的数值
		// 返回值:  
		void OnShowKorotkoffVolume(int nNIBPSoundValue);
	};

}}}
