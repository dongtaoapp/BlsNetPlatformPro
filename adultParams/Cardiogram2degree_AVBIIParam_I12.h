#pragma once

#include "..\simulatorbase\vircardiogramparam.h"


namespace jysoft { namespace simulator { namespace ecg {

	class CCardiogram2degree_AVBIIParam_I12 : public CVirCardiogramParam
	{
		friend class CCardiogram2degree_AVBII;
	public:
		CCardiogram2degree_AVBIIParam_I12( IStorage *pRootStorage );
		virtual ~CCardiogram2degree_AVBIIParam_I12(void);
	public:
		//���ز���ֵ
        virtual void LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm,int uHR, short sConduct = 0, short sExtendParam = 0);
		//���ض�Ӧ���粨�����ݲ���
		virtual void LoadExtrasystParam(Extrasys eExtrasyst);
		virtual void LoadExtrasystParamPre(Extrasys eExtrasyst);
		virtual std::string GetExtrasystFileName(Extrasys eExtrasyst, const std::string &strKey);
		virtual void ReLoadCardiogramParam();
		//---------------------------------------------------------------------------------------------------------------
		//�����ĵ�ʱ��Ѫ��������ʱ��
		virtual bool GetSpO2BeginTimeToCardiogram(/*out*/long &lBeginTime, /*out*/long &lCycleTime);
		//�����粩ʱ��Ѫ��������ʱ��
		virtual bool GetSpO2BeginTimeToExtrasyst(/*out*/long &lBeginTime, /*out*/long &lPreSpO2BeginTime, /*out*/long &lCycleTime);
	private:
		int             m_nStepNum;      //����ȷ��P�������쳤��
		int             m_nSumStepNum;
		int             m_bEmptQRS;      //��QRS��
	};

}}}
