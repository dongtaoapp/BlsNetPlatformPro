#pragma once

#include "..\simulatorbase\vircardiogramparam.h"


namespace jysoft { namespace simulator { namespace ecg {

	class CCardiogram1degree_AVBParam_I12 : public CVirCardiogramParam
	{
	public:
		CCardiogram1degree_AVBParam_I12( IStorage *pRootStorage );;
		virtual ~CCardiogram1degree_AVBParam_I12(void);
	public:
		//加载参数值
        virtual void LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm,int uHR, short sConduct = 0, short sExtendParam = 0);
		//加载对应的早波的数据参数
		virtual void LoadExtrasystParam(Extrasys eExtrasyst);
		virtual void LoadExtrasystParamPre(Extrasys eExtrasyst);
		virtual std::string GetExtrasystFileName(Extrasys eExtrasyst, const std::string &strKey);
		//---------------------------------------------------------------------------------------------------------------
		//产生心电时，血氧的启动时间
		virtual bool GetSpO2BeginTimeToCardiogram(/*out*/long &lBeginTime, /*out*/long &lCycleTime);
		//产生早博时，血氧的启动时间
		virtual bool GetSpO2BeginTimeToExtrasyst(/*out*/long &lBeginTime, /*out*/long &lPreSpO2BeginTime, /*out*/long &lCycleTime);
	};

}}}
