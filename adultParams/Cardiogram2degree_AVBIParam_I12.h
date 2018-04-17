#pragma once

#include "..\simulatorbase\vircardiogramparam.h"


namespace jysoft { namespace simulator { namespace ecg {

	class CCardiogram2degree_AVBIParam_I12 :  public CVirCardiogramParam
	{
		friend class CCardiogram2degree_AVBI;
	public:
		CCardiogram2degree_AVBIParam_I12( IStorage *pRootStorage );
		virtual ~CCardiogram2degree_AVBIParam_I12(void);
	public:
		//���ز���ֵ
        void LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm,int uHR, short sConduct = 0, short sExtendParam = 0);
		//���ض�Ӧ���粨�����ݲ���
		void LoadExtrasystParamPre(Extrasys eExtrasyst);
		std::string GetExtrasystFileName(Extrasys eExtrasyst, const std::string &strKey);
		//�����ĵ�ʱ��Ѫ��������ʱ��
		bool GetSpO2BeginTimeToCardiogram(/*out*/long &lBeginTime, /*out*/long &lCycleTime);
		//�����粩ʱ��Ѫ��������ʱ��
		bool GetSpO2BeginTimeToExtrasyst(/*out*/long &lBeginTime, /*out*/long &lPreSpO2BeginTime, /*out*/long &lCycleTime);
		//�Ƿ���ȱʡ���粥
		virtual bool IsHaveDefalutExtrasyst();
	public:
		virtual void ReLoadCardiogramParam();
	protected:
		void SetR_FileName( const std::string * pStrParams) { m_setParams["R_FileName"] = pStrParams[2];};
		void SetR_ZoomTime( const std::string * pStrParams) { m_setParams["R_ZoomTime"] = pStrParams[3];};
		void SetR_ExtendTime(const std::string *pStrParams) { m_setParams["R_ExtendTime"] = pStrParams[4];};
		void SetT_FileName( const std::string * pStrParams) { m_setParams["T_FileName"] = pStrParams[5];};
		void SetT_ZoomTime( const std::string * pStrParams) { m_setParams["T_ZoomTime"] = pStrParams[6];};
		void Set_CycleTime(const std::string * pStrParams) { m_setParams["CycleTime"] = pStrParams[7];};
	private:
		int          m_nStepNum;   //����ȷ��P�������쳤��
		int          m_nSumStepNum;
		int          m_bEmptQRS;  //��QRS��
	};

}}}
