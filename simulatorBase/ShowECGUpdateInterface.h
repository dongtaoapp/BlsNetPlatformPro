#pragma once
#include ".\simulatorbase_global.h"

#include "..\common\iupdateshowvir.h"

namespace jysoft { namespace simulator { namespace base {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     心电图信息显示接口，包括心律名称、心率次数、心率正常范围等信息
	创建人：	 hjg
	创建时间：   2016/8/5
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT CShowECGUpdateInterface : public IUpdateShowVir
	{
	public:
		CShowECGUpdateInterface(void);
		virtual ~CShowECGUpdateInterface(void);
	public:
		virtual bool isKindOf(const std::string &className);
	protected:
		//显示心电图名称
        virtual void ShowECGName(const std::string & strRhythm, const std::string &strExtrasyst, int nHR, bool bEMD) = 0;
		// 功能： 因除颤而修改心电图名称
        virtual void ShowECGNameInDefib(const std::string &strRhythm, const std::string &strExtrasyst, int nHR, bool bEMD, int nMillDelayTime) = 0;
		//显示正确心率的范围
		virtual void ShowECGRateRange(int nMinRate, int nMaxRate) = 0;
		//显示当前的心率值
		virtual void ShowECGRate(int nHR) = 0;
		//因除颤而修改当前的心率值
		virtual void ShowECGRateInDefib(int nHR, int nMillDelayTime) = 0;
		//-------------------------------------------------------------------------------
		//对接显示后通知
		virtual void doLinkECGUpdateShow() { };
		//断开显示后通知
		virtual void cutLinkECGUpdateShow() { };
	public:
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	public:
		/*******************************************************************************/
		// 函数名称： OnShowECGName
		// 功能： 显示心电图名称
		// 参数： 
		//        CString strRhythm:          基本心律名称
		//        CString strExtrasyst:       早搏    
		//        CString  strHR:             心率
		//        BOOL bEMD: 
		//注：  参数的内容为内置名称，显示时再转换为显示名称
		// 返回值:  
        void OnShowECGName(const std::string &strRhythm, const std::string &strExtrasyst, int nHR, bool bEMD);
		/*******************************************************************************/
		// 函数名称： OnShowECGNameInDefib
		// 功能： 因除颤而修改心电图名称
		// 参数： 
		//        CString strRhythm:          基本心律名称
		//        CString strExtrasyst:       早搏    
		//        CString  strHR:             心率
		//        BOOL bEMD: 
		//注：  参数的内容为内置名称，显示时再转换为显示名称
		// 返回值:  
        void OnShowECGNameInDefib(const std::string &strRhythm, const std::string &strExtrasyst, int nHR, bool bEMD, int nMillDelayTime);
		/*******************************************************************************/
		// 函数名称： OnShowECGRateRange
		// 功能： 显示正确心率的范围
		// 参数： int nMinRate:               区间最小心率（单位：次/分钟）
		//        int nMaxRate:               区间最大心率（单位：次/分钟）  
		// 返回值:  
		void OnShowECGRateRange(int nMinRate, int nMaxRate);
		/*******************************************************************************/
		// 函数名称： OnShowECGRate
		// 功能： 显示当前的心率值
		// 参数： int nHR:                    心率值（单位：次/分钟）
		// 返回值:  
		void OnShowECGRate(int nHR);
		/*******************************************************************************/
		// 函数名称： OnShowECGRate
		// 功能： 因除颤而修改当前的心率值
		// 参数： int nHR:                    心率值（单位：次/分钟）
		// 返回值: 
		void OnShowECGRateInDefib(int nHR, int nMillDelayTime);
	};

}}}
