#pragma once

#include "..\simulatorbase\icardiogramleads.h"


namespace jysoft { namespace simulator { namespace ecg {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     "���Ҳ���"�ĵ�ͼ��ͬ��������������
	�����ˣ�	 hjg
	����ʱ�䣺   2013/6/8
	��ע��    �������ִ�ϸ�Ĳ���
	//-----------------------------------------------------------------------------------------------------------------*/
	class CCardiogramVFibr : public ICardiogramLeads
	{
	public:
		CCardiogramVFibr( IStorage *pRootStorage );
		virtual ~CCardiogramVFibr(void);
	public:  //�ӿ�ICardiogramLeads��������
		/*******************************************************************************/
		// �������ƣ� IsCanExpressCardiogramParam
		// ���ܣ� ���ݴ������ĵ�ͼ�������Ƿ����ô˶����õ������ĵ�ͼ����Ҫ�Ĳ�����
		// ������  
		// ����ֵ: 
        virtual bool IsCanExpressCardiogramParam(BasicRhythm eRhythm, int uHR);
		/*******************************************************************************/
		// �������ƣ� LoadCardiogramLeadsParam
		// ���ܣ� �����ĵ�ͼ�������Ĳ���ֵ
		// ������ 
		//         
		// ����ֵ:
        virtual bool LoadCardiogramLeadsParam( BasicRhythm eRhythm, int uHR, short sConduct, short sExtendParam );
		/*******************************************************************************/
		// �������ƣ� ReLoadCardiogramParam
		// ���ܣ� 
		// ������  
		// ����ֵ: 
		virtual void ReLoadCardiogramParam();
		/*******************************************************************************/
		// �������ƣ� SeteRefurbishDataRange
		// ���ܣ� �趨�������ݵĳ̶�
		// ������  
		// ����ֵ: 
		virtual void SeteRefurbishDataRange(_eRefurbishDataRange eRange);
		// ���ع������ݵĳ̶�������ö��ֵ��RD_LoadConfigFile���RD_NoChange��ǳ��
		virtual _eRefurbishDataRange GeteRefurbishDataRange();
	public:
		//�Ƿ���ȱʡ���粥
		virtual bool IsHaveDefalutExtrasyst() {return false;};
	public:
        static bool IsCanParamExpress(BasicRhythm eRhythm, int uHR);
	};
}}}
