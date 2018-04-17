#pragma once
#include <string>

#include "..\simulatorbase\vircardiogramparam.h"


namespace jysoft { namespace simulator { namespace ecg {
	
	class CCardiogram3degree_AVBParam_I12 : public CVirCardiogramParam
	{
		friend class CCardiogram3degree_AVB;
	public:
		CCardiogram3degree_AVBParam_I12(IStorage *pRootStorage );
		virtual ~CCardiogram3degree_AVBParam_I12(void);
	public:
		//加载参数值
        virtual void LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm,int uHR, short sConduct = 0, short sExtendParam = 0);
		//产生心电时，血氧的启动时间
		virtual bool GetSpO2BeginTimeToCardiogram(/*out*/long &lBeginTime, /*out*/long &lCycleTime);
	public:
		virtual bool GetParamValue(const std::string &strKey, const std::string &strParam, std::string &strValue);
		virtual bool GetParamValue(const std::string &strKey, std::string &strValue);
	protected:
		unsigned int               m_dwSumRunTime;//总运行的时间
		unsigned int               m_nSumBasicSegTime;//已显示的基本段的时间
		int                        m_nBasicSeg_LExtentTime;
	};

}}}
