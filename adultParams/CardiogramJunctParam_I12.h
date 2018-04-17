#pragma once

#include "..\simulatorbase\vircardiogramparam.h"


namespace jysoft { namespace simulator { namespace ecg {

	class CCardiogramJunctParam_I12 : public CVirCardiogramParam
	{
	public:
		CCardiogramJunctParam_I12(IStorage *pRootStorage );
		virtual ~CCardiogramJunctParam_I12(void);
	public:
		//加载参数值
        virtual void LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm,int uHR, short sConduct = 0, short sExtendParam = 0);
		//产生心电时，血氧的启动时间
		bool GetSpO2BeginTimeToCardiogram(/*out*/long &lBeginTime, /*out*/long &lCycleTime);
		//是否初始构建时发送两次心电图数据
		virtual bool IsInitialSendDoubleSampleData() { return false; };
	protected:
		void SetR_ExtendTime(const std::string *pStrParams) { m_setParams["R_RExtendTime"] = pStrParams[5];};
		void SetR_LExtendTime(const std::string *pStrParams) { m_setParams["R_LExtendTime"] = pStrParams[6];};
		void SetT_FileName( const std::string * pStrParams) { m_setParams["T_FileName"] = pStrParams[7];};
		void SetT_ZoomTime( const std::string * pStrParams) { m_setParams["T_ZoomTime"] = pStrParams[8];};
		void SetT_ExtendTime(const std::string * pStrParams) { m_setParams["T_RExtendTime"] = pStrParams[9];};
		void SetT_LExtendTime(const std::string *pStrParams) { m_setParams["T_LExtendTime"] = pStrParams[10];};
		void Set_CycleTime(const std::string * pStrParams) { m_setParams["CycleTime"] = pStrParams[11];};
	private:
        int Get_HRStep(int uHR);
	};

}}}
