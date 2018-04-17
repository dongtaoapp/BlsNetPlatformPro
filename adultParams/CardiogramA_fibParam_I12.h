#pragma once
#include <string>

#include "..\simulatorbase\vircardiogramparam.h"


namespace jysoft { namespace simulator { namespace ecg {

	class CCardiogramA_fib;
	class CCardiogramA_fibParam_I12 : public CVirCardiogramParam
	{
		friend class CCardiogramA_fib;
	public:
		CCardiogramA_fibParam_I12(CCardiogramA_fib *pAFibEcg, IStorage *pRootStorage );
		virtual ~CCardiogramA_fibParam_I12(void);
	public:
		//加载参数值
        void LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm,int uHR, short sConduct = 0, short sExtendParam = 0);
		//产生心电时，血氧的启动时间
		bool GetSpO2BeginTimeToCardiogram(/*out*/long &lBeginTime, /*out*/long &lCycleTime);
	public:
		bool GetParamValue(const std::string &strKey, const std::string &strParam, std::string &strValue);
		bool GetParamValue(const std::string &strKey, std::string &strValue);
	protected:
        void GetNormalA_fibParams(/*out*/std::string *pParams, int uHR);
        void GetFastA_fibParams(/*out*/std::string *pParams, int uHR);
	protected:
		void SetR_FileName( const std::string * pStrParams) { m_setParams["R_FileName"] = pStrParams[0];};
		void SetR_ZoomTime( const std::string * pStrParams) { m_setParams["R_ZoomTime"] = pStrParams[1];};
		void SetR_LExtendTime(const std::string *pStrParams);
		void SetR_RExtendTime(const std::string *pStrParams) { m_setParams["R_RExtendTime"] = pStrParams[2];};
		void SetT_FileName( const std::string * pStrParams) { m_setParams["T_FileName"] = pStrParams[3];};
		void SetT_ZoomTime( const std::string * pStrParams) { m_setParams["T_ZoomTime"] = pStrParams[4];};
		void SetT_ExtendTime(const std::string * pStrParams) { m_setParams["T_ExtendTime"] = pStrParams[5];};
		void Set_CycleTime(const std::string * pStrParams);
	private:
		unsigned long                   m_dwSumRunTime;              //总运行的时间
		unsigned long                   m_nSumBasicSegTime;          //已显示的基本段的时间
		int                             m_nBasicSeg_LExtentTime;
		//-----------------------------------------------------------------------------------------------------------
		CCardiogramA_fib *      m_pAFibEcg;
	};

}}}
