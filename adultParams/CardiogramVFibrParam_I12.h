#pragma once

#include "..\simulatorbase\vircardiogramparam.h"


namespace jysoft { namespace simulator { namespace ecg {

	class CCardiogramVFibrParam_I12 : public CVirCardiogramParam
	{
	public:
		CCardiogramVFibrParam_I12(IStorage *pRootStorage );
		virtual ~CCardiogramVFibrParam_I12(void);
	public:
		//���ز���ֵ
        virtual void LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm,int uHR, short sConduct = 0, short sExtendParam = 0);
		//�Ƿ���ʼ����ʱ���������ĵ�ͼ����
		virtual bool IsInitialSendDoubleSampleData() { return false; };
	private:
		short               m_sExtendParam;
	};
}}}
