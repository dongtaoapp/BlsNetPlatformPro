#pragma once

#include "..\simulatorbase\vircardiogramparam.h"


namespace jysoft { namespace simulator { namespace ecg {

	class CCardiogram1degree_AVBParam_I12 : public CVirCardiogramParam
	{
	public:
		CCardiogram1degree_AVBParam_I12( IStorage *pRootStorage );;
		virtual ~CCardiogram1degree_AVBParam_I12(void);
	public:
		//���ز���ֵ
        virtual void LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm,int uHR, short sConduct = 0, short sExtendParam = 0);
		//���ض�Ӧ���粨�����ݲ���
		virtual void LoadExtrasystParam(Extrasys eExtrasyst);
		virtual void LoadExtrasystParamPre(Extrasys eExtrasyst);
		virtual std::string GetExtrasystFileName(Extrasys eExtrasyst, const std::string &strKey);
		//---------------------------------------------------------------------------------------------------------------
		//�����ĵ�ʱ��Ѫ��������ʱ��
		virtual bool GetSpO2BeginTimeToCardiogram(/*out*/long &lBeginTime, /*out*/long &lCycleTime);
		//�����粩ʱ��Ѫ��������ʱ��
		virtual bool GetSpO2BeginTimeToExtrasyst(/*out*/long &lBeginTime, /*out*/long &lPreSpO2BeginTime, /*out*/long &lCycleTime);
	};

}}}
