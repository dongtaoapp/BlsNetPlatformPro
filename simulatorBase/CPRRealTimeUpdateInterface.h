#pragma once
#include ".\simulatorbase_global.h"

#include "..\common\iupdateshowvir.h"
#include "..\common\CommonGlobal.h"

namespace jysoft{  namespace cpr {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     CPR采样数据显示接口
	创建人：	 hjg
	创建时间：   2017/2/25
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT CCPRRealTimeUpdateInterface : public IUpdateShowVir
	{
	public:
		CCPRRealTimeUpdateInterface(void);
		virtual ~CCPRRealTimeUpdateInterface(void);
	public://接口函数重载
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
		virtual bool isKindOf(const std::string &className);
	public:
		//得到CPR的数据
		void OnLoadCPRSample(const _CPRData *ptrCPRDatas, int nLength);
		// 加入错误标志
		void OnAddCPRErrorSign(_eCPRErrorSign eErrorSign);
	protected:
		//对接显示后通知
		virtual void doLinkCPRRealTimeUpdateShow() { };
		//断开显示后通知
		virtual void cutLinkCPRRealTimeUpdateShow() { };
		//得到CPR的数据
		virtual void LoadCPRSample(const _CPRData *ptrCPRDatas, int nLength) = 0;
		//加入错误标志
		virtual void AddCPRErrorSign(_eCPRErrorSign eErrorSign) = 0;
	};

}}
