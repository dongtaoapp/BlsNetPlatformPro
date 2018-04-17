#pragma once

#include "..\simulatorbase\vircardiogramparam.h"


namespace jysoft { namespace simulator { namespace ecg {

	class CCardiogramA_fluttParam_I12 : public CVirCardiogramParam
	{
	public:
		CCardiogramA_fluttParam_I12(IStorage *pRootStorage );
		virtual ~CCardiogramA_fluttParam_I12(void);
	public:
		//加载参数值
        virtual void LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm,int uHR, short sConduct = 0, short sExtendParam = 0);
		virtual bool GetParamValue(const std::string &strKey, const std::string &strParam, std::string &strValue);
		//产生心电时，血氧的启动时间
		virtual bool GetSpO2BeginTimeToCardiogram(/*out*/long &lBeginTime, /*out*/long &lCycleTime);
	protected:
		void SetR_FileName( const std::string * pStrParams) { m_setParams["R_FileName"] = pStrParams[0];};
		void SetR_ZoomTime( const std::string * pStrParams) { m_setParams["R_ZoomTime"] = pStrParams[1];};
		void SetR_LExtendTime(const std::string *pStrParams) { m_setParams["R_LExtentTime"] = pStrParams[2];};
		void SetR_RExtendTime(const std::string *pStrParams) { m_setParams["R_RExtendTime"] = pStrParams[3];};
		void SetT_FileName( const std::string * pStrParams) { m_setParams["T_FileName"] = pStrParams[4];};
		void SetT_ZoomTime( const std::string * pStrParams) { m_setParams["T_ZoomTime"] = pStrParams[5];};
		void SetT_ExtendTime(const std::string * pStrParams) { m_setParams["T_ExtendTime"] = pStrParams[6];};
		void Set_CycleTime(const std::string * pStrParams) { m_setParams["CycleTime"] = pStrParams[9];};
	};

}}}
