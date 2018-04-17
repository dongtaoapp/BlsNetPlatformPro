#pragma once
#include <string>

#include "..\simulatorbase\vircardiogramparam.h"


namespace jysoft { namespace simulator { namespace ecg {

	class CCardiogramSinusParam_I12 : public CVirCardiogramParam
	{
	public:
		CCardiogramSinusParam_I12();
		CCardiogramSinusParam_I12( IStorage *pRootStorage );
		virtual ~CCardiogramSinusParam_I12(void);
	public:
		//���ز���ֵ
        virtual void LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm,int uHR, short sConduct = 0, short sExtendParam = 0);
		//���ض�Ӧ���粨�����ݲ���
		virtual void LoadExtrasystParam(Extrasys eExtrasyst);
		virtual void LoadExtrasystParamPre(Extrasys eExtrasyst);
		virtual std::string GetExtrasystFileName(Extrasys eExtrasyst, const std::string &strKey);
		//�����ĵ�ʱ��Ѫ��������ʱ��
		virtual bool GetSpO2BeginTimeToCardiogram(/*out*/long &lBeginTime, /*out*/long &lCycleTime);
		//�����粩ʱ��Ѫ��������ʱ��
		virtual bool GetSpO2BeginTimeToExtrasyst(/*out*/long &lBeginTime, /*out*/long &lPreSpO2BeginTime, /*out*/long &lCycleTime);
		//�Ƿ���ʼ����ʱ���������ĵ�ͼ����
		virtual bool IsInitialSendDoubleSampleData() { return false; };
	protected:
        void GetNormalSinusParams(/*out*/std::string *pParams, int uHR);
        void GetFastSinusParams(/*out*/std::string *pParams, int uHR);
		//��ȡUnifocalPVC�粫�β���
        void GetUnifocalPVC_Params(/*out*/std::string *pParams, int uHR);
		//��ȡ�����粫RonT�β���
        void GetRonT_Params(/*out*/std::string *pParams, int uHR);
		//��ȡ���粫�Զ����ɲ���
        void GetCoupled_PVC_Params(/*out*/std::string *pParams, int uHR);
		//��ȡ�����粫����
        void GetPAC_Params(/*out*/std::string *pParams, int uHR);
		//��ȡPJC����
        void GetPJC_Params(/*out*/std::string *pParams, int uHR);
	};

}}}
