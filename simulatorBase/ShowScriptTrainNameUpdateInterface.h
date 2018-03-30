#pragma once
#include ".\simulatorbase_global.h"

#include "..\Common\IUpdateshowVir.h"

namespace jysoft { namespace simulator { namespace base {
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     培训脚本名称显示接口
	创建人：	 hjg
	创建时间：   2009/6/19
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT CShowScriptTrainNameUpdateInterface  : public IUpdateShowVir
	{
	public:
		CShowScriptTrainNameUpdateInterface(void);
		virtual ~CShowScriptTrainNameUpdateInterface(void);
	public:
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	public:
		virtual bool isKindOf(const std::string &className);
	protected:
		/*******************************************************************************/
		// 函数名称： ShowScriptTrainNameUpdate
		// 功能： 显示培训脚本名称
		// 参数： 
		//        const CString &strScriptName：    脚本名称
		// 返回值:  
		virtual void ShowScriptTrainNameUpdate(const std::string &strScriptName) = 0;
		//对接显示后通知
		virtual void doLinkScriptNameUpdateShow() { };
		//断开显示后通知
		virtual void cutLinkScriptNameUpdateShow() { };
	public:
		//显示培训脚本名称
		void OnShowScriptTrainNameUpdate(const std::string &strScriptName);
	};

}}}
