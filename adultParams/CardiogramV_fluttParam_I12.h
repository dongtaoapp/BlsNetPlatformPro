#pragma once

#include "..\simulatorbase\vircardiogramparam.h"


namespace jysoft { namespace simulator { namespace ecg {

	class CCardiogramV_fluttParam_I12 : public CVirCardiogramParam
	{
	public:
		CCardiogramV_fluttParam_I12( IStorage *pRootStorage );
		virtual ~CCardiogramV_fluttParam_I12(void);
	public:
		//���ز���ֵ
        virtual void LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm,int uHR, short sConduct = 0, short sExtendParam = 0);
		//�����ĵ�ʱ��Ѫ��������ʱ��
		bool GetSpO2BeginTimeToCardiogram(/*out*/long &lBeginTime, /*out*/long &lCycleTime);
		//�Ƿ���ʼ����ʱ���������ĵ�ͼ����
		virtual bool IsInitialSendDoubleSampleData() { return false; };
	private:
        int Get_HRStep(int uHR);
	};
}}}
