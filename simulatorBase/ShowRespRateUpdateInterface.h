#pragma once
#include ".\simulatorbase_global.h"

#include "..\Common\CommonGlobal.h"
#include "..\common\iupdateshowvir.h"

namespace jysoft { namespace simulator { namespace base {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     呼吸次数信息显示接口
	创建人：	 hjg
	创建时间：   2008/8/5
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT CShowRespRateUpdateInterface : public IUpdateShowVir
	{
	public:
		CShowRespRateUpdateInterface(void);
		virtual ~CShowRespRateUpdateInterface(void);
	public:
		virtual bool isKindOf(const std::string &className);
	protected:
		//显示呼吸次数
		virtual void ShowRespRate(eRespMode  enumMode, int nRate) = 0;
		//显示呼吸次数正常的范围区间
		virtual void ShowRespRateRange(int nMinRate, int nMaxRate) = 0;
		//对接显示后通知
		virtual void doLinkRespRateUpdateShow() { };
		//断开显示后通知
		virtual void cutLinkRespRateUpdateShow() { };
	public:
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	public:
		/*******************************************************************************/
		// 函数名称： OnShowRespRate
		// 功能： 显示呼吸次数
		// 参数： int nRate:                呼吸次数（单位：次/分钟）
		// 返回值:  
		void OnShowRespRate(eRespMode  enumMode, int nRate);
		/*******************************************************************************/
		// 函数名称： OnShowRespRateRange
		// 功能： 显示呼吸次数正常的范围区间
		// 参数： int nMinRate:              区间最小呼吸次数（单位：次/分钟） 
		//        int nMaxRate:              区间最大呼吸次数（单位：次/分钟） 
		// 返回值:  
		void OnShowRespRateRange(int nMinRate, int nMaxRate);
	};

}}}
