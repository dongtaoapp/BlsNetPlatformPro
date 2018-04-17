#pragma once

#include "..\simulatorbase\vircardiogramparam.h"


namespace jysoft { namespace simulator { namespace ecg {

	class CCardiogramAgonaleParam_I12 : public CVirCardiogramParam
	{
		friend class CCardiogramAgonale;
	public:
		CCardiogramAgonaleParam_I12( IStorage *pRootStorage );
		virtual ~CCardiogramAgonaleParam_I12(void);
	public:
		//加载参数值
        virtual void LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm,int uHR, short sConduct = 0, short sExtendParam = 0);
		//产生心电时，血氧的启动时间
		virtual bool GetSpO2BeginTimeToCardiogram(/*out*/long &lBeginTime, /*out*/long &lCycleTime);
		//是否初始构建时发送两次心电图数据
		virtual bool IsInitialSendDoubleSampleData() { return true; };
	public:
		virtual bool GetParamValue(const std::string &strKey, std::string &strValue);
	public:
		//返回是否有心脏搏动信号
		virtual bool  IsHaveHeartStartSign() { return true; };
		//返回Q波到S波时间段的时间（单位：0.1毫秒）
		virtual int GetPhaseTimeFromQtoS() { return 1000; };
		//返回S波到T波时间段的时间（单位：0.1毫秒）
		virtual int GetPhaseTimeFromStoT() { return 3000; };
	protected:
		unsigned long                   m_dwSumRunTime;              //总运行的时间
		unsigned long                   m_nSumBasicSegTime;          //已显示的基本段的时间
		int                             m_nBasicSeg_LExtentTime;
	};
}}}
