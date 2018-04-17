#pragma once

#include "..\simulatorbase\vircardiogramparam.h"


namespace jysoft { namespace simulator { namespace ecg {

	class CCardiogramAgonaleParam_I12 : public CVirCardiogramParam
	{
		friend class CCardiogramAgonale;
	public:
		CCardiogramAgonaleParam_I12( IStorage *pRootStorage );
		virtual ~CCardiogramAgonaleParam_I12(void);
	public:
		//���ز���ֵ
        virtual void LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm,int uHR, short sConduct = 0, short sExtendParam = 0);
		//�����ĵ�ʱ��Ѫ��������ʱ��
		virtual bool GetSpO2BeginTimeToCardiogram(/*out*/long &lBeginTime, /*out*/long &lCycleTime);
		//�Ƿ��ʼ����ʱ���������ĵ�ͼ����
		virtual bool IsInitialSendDoubleSampleData() { return true; };
	public:
		virtual bool GetParamValue(const std::string &strKey, std::string &strValue);
	public:
		//�����Ƿ������ಫ���ź�
		virtual bool  IsHaveHeartStartSign() { return true; };
		//����Q����S��ʱ��ε�ʱ�䣨��λ��0.1���룩
		virtual int GetPhaseTimeFromQtoS() { return 1000; };
		//����S����T��ʱ��ε�ʱ�䣨��λ��0.1���룩
		virtual int GetPhaseTimeFromStoT() { return 3000; };
	protected:
		unsigned long                   m_dwSumRunTime;              //�����е�ʱ��
		unsigned long                   m_nSumBasicSegTime;          //����ʾ�Ļ����ε�ʱ��
		int                             m_nBasicSeg_LExtentTime;
	};
}}}
