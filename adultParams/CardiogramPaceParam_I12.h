#pragma once

#include "..\simulatorbase\vircardiogramparam.h"


namespace jysoft { namespace simulator { namespace ecg {

	class CCardiogramPaceParam_I12 : public CVirCardiogramParam
	{
	public:
		CCardiogramPaceParam_I12( IStorage *pRootStorage );
		virtual ~CCardiogramPaceParam_I12(void);
	public:
		//���ز���ֵ
        virtual void LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm,int uHR, short sConduct = 0, short sExtendParam = 0);
		//�����ĵ�ʱ��Ѫ��������ʱ��
		bool GetSpO2BeginTimeToCardiogram(/*out*/long &lBeginTime, /*out*/long &lCycleTime);
		//�Ƿ���ʼ����ʱ���������ĵ�ͼ����
		virtual bool IsInitialSendDoubleSampleData() { return false; };
	public:
		//�����Ƿ������ಫ���ź�
		virtual bool  IsHaveHeartStartSign() { return true; };
		//����Q����S��ʱ���ε�ʱ�䣨��λ��0.1���룩
		virtual int GetPhaseTimeFromQtoS();
		//����S����T��ʱ���ε�ʱ�䣨��λ��0.1���룩
		virtual int GetPhaseTimeFromStoT();
	};
}}}
