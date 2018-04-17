#pragma once

#include "..\simulatorbase\vircardiogramparam.h"


namespace jysoft { namespace simulator { namespace ecg {

	class CCardiogramIdiovParam_I12 : public CVirCardiogramParam
	{
	public:
		CCardiogramIdiovParam_I12(IStorage *pRootStorage );
		virtual ~CCardiogramIdiovParam_I12(void);
	public:
		//加载参数值
        virtual void LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm,int uHR, short sConduct = 0, short sExtendParam = 0);
		//产生心电时，血氧的启动时间
		bool GetSpO2BeginTimeToCardiogram(/*out*/long &lBeginTime, /*out*/long &lCycleTime);
		//是否初始构建时发送两次心电图数据
		virtual bool IsInitialSendDoubleSampleData() { return false; };
	public:
		//返回是否有心脏搏动信号
		virtual bool  IsHaveHeartStartSign() { return true; };
		//返回Q波到S波时间段的时间（单位：0.1毫秒）
		virtual int GetPhaseTimeFromQtoS();
		//返回S波到T波时间段的时间（单位：0.1毫秒）
		virtual int GetPhaseTimeFromStoT();
	};
}}}
