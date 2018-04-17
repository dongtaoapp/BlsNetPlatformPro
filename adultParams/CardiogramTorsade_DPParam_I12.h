#pragma once

#include "..\simulatorbase\vircardiogramparam.h"


namespace jysoft { namespace simulator { namespace ecg {

	class CCardiogramTorsade_DPParam_I12 : public CVirCardiogramParam
	{
	public:
		CCardiogramTorsade_DPParam_I12(IStorage *pRootStorage );
		virtual ~CCardiogramTorsade_DPParam_I12(void);
	public:
		//���ز���ֵ
        virtual void LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm,int uHR, short sConduct = 0, short sExtendParam = 0);
		//�Ƿ���ʼ����ʱ���������ĵ�ͼ����
		virtual bool IsInitialSendDoubleSampleData() { return false; };
	};
}}}
