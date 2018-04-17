#pragma once

#include "..\simulatorbase\vircardiogramparam.h"


namespace jysoft { namespace simulator { namespace ecg {

	class CCardiogramV_tachParam_I12 : public CVirCardiogramParam
	{
	public:
		CCardiogramV_tachParam_I12( IStorage *pRootStorage );
		virtual ~CCardiogramV_tachParam_I12(void);
	public:
		//���ز���ֵ
        virtual void LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm,int uHR, short sConduct = 0, short sExtendParam = 0);
		//�����ĵ�ʱ��Ѫ��������ʱ��
		bool GetSpO2BeginTimeToCardiogram(/*out*/long &lBeginTime, /*out*/long &lCycleTime);
		//�Ƿ���ʼ����ʱ���������ĵ�ͼ����
		virtual bool IsInitialSendDoubleSampleData() { return false; };
	public:
		//����Q����S��ʱ���ε�ʱ�䣨��λ��0.1���룩
		virtual int GetPhaseTimeFromQtoS() { return 1000; };
		//����S����T��ʱ���ε�ʱ�䣨��λ��0.1���룩
		virtual int GetPhaseTimeFromStoT() { return 2000; };
	private:
        int Get_HRStep(int uHR);
	};
}}}
