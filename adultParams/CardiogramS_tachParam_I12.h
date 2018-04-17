#pragma once

#include "..\simulatorbase\vircardiogramparam.h"


namespace jysoft { namespace simulator { namespace ecg {

	class CCardiogramS_tachParam_I12 : public CVirCardiogramParam
	{
	public:
		CCardiogramS_tachParam_I12( IStorage *pRootStorage );
		virtual ~CCardiogramS_tachParam_I12(void);
	public:
		//���ز���ֵ
        virtual void LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm,int uHR, short sConduct = 0, short sExtendParam = 0);
		//�����ĵ�ʱ��Ѫ��������ʱ��
		bool GetSpO2BeginTimeToCardiogram(/*out*/long &lBeginTime, /*out*/long &lCycleTime);
		//�Ƿ���ʼ����ʱ���������ĵ�ͼ����
		virtual bool IsInitialSendDoubleSampleData() { return false; };
		//�Ƿ���ȱʡ���粥
		virtual bool IsHaveDefalutExtrasyst() {return false;};
		//����Q����S��ʱ���ε�ʱ�䣨��λ��0.1���룩
		virtual int GetPhaseTimeFromQtoS();
		//����S����T��ʱ���ε�ʱ�䣨��λ��0.1���룩
		virtual int GetPhaseTimeFromStoT();
	protected:
		void SetR_ExtendTime(const std::string *pStrParams) { m_setParams["R_RExtendTime"] = pStrParams[5];};
		void SetR_LExtendTime(const std::string *pStrParams) { m_setParams["R_LExtendTime"] = pStrParams[6];};
		void SetT_FileName( const std::string * pStrParams) { m_setParams["T_FileName"] = pStrParams[7];};
		void SetT_ZoomTime( const std::string * pStrParams) { m_setParams["T_ZoomTime"] = pStrParams[8];};
		void SetT_ExtendTime(const std::string * pStrParams) { m_setParams["T_RExtendTime"] = pStrParams[9];};
		void SetT_LExtendTime(const std::string *pStrParams) { m_setParams["T_LExtendTime"] = pStrParams[10];};
		void Set_CycleTime(const std::string * pStrParams) { m_setParams["CycleTime"] = pStrParams[11];};
	};

}}}
