#pragma once

#include "..\simulatorbase\icardiogramleads.h"


namespace jysoft { namespace simulator { namespace ecg {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     "�����˶�"�ĵ�ͼ��ͬ��������������(���粫��Ƶ��200~250��
	�����ˣ�	 hjg
	����ʱ�䣺   2013/7/18
	//-----------------------------------------------------------------------------------------------------------------*/
	class CCardiogramV_flutt : public ICardiogramLeads
	{
	public:
		CCardiogramV_flutt( IStorage *pRootStorage );
		virtual ~CCardiogramV_flutt(void);
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
