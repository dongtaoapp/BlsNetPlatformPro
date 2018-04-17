#pragma once

#include "..\simulatorbase\icardiogramleads.h"


namespace jysoft { namespace simulator { namespace ecg {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     "���Ȣ��ͷ��Ҵ�������"�ĵ�ͼ��ͬ��������������
	�����ˣ�	 hjg
	����ʱ�䣺   2013/5/13
	//-----------------------------------------------------------------------------------------------------------------*/

	class CCardiogram2degree_AVBI : public ICardiogramLeads
	{
	public:
		CCardiogram2degree_AVBI( IStorage *pRootStorage );
		virtual ~CCardiogram2degree_AVBI(void);
	public:  //�ӿ�ICardiogramLeads��������
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
		// �������ƣ� IsCanExpressCardiogramParam
		// ���ܣ� ���ݴ�����ĵ�ͼ�������Ƿ����ô˶���õ������ĵ�ͼ����Ҫ�Ĳ�����
		// ������  
		// ����ֵ: 
        virtual bool IsCanExpressCardiogramParam(BasicRhythm eRhythm, int uHR);
		/*******************************************************************************/
		// �������ƣ� SeteRefurbishDataRange
		// ���ܣ� �趨�������ݵĳ̶�
		// ������  
		// ����ֵ: 
		virtual void SeteRefurbishDataRange(_eRefurbishDataRange eRange);
		// ���ع������ݵĳ̶������ö��ֵ��RD_LoadConfigFile���RD_NoChange��ǳ��
		virtual _eRefurbishDataRange GeteRefurbishDataRange();
	public:
		/*******************************************************************************/
		// �������ƣ� ResetSyncFlag
		// ���ܣ� ����ͬ����ʶ�������������ڵ���������Э��
		// ������  
		// ����ֵ: 
		virtual void ResetSyncFlag();
		//�Ƿ��ʼ����ʱ���������ĵ�ͼ����
		virtual bool IsInitialSendDoubleSampleData() { return true; };
	public:
		//�Ƿ���ȱʡ���粥
		virtual bool IsHaveDefalutExtrasyst() {return true;};
		virtual void LoadExtrasystParamPre(Extrasys eExtrasyst);
		virtual void LoadExtrasystParam(Extrasys eExtrasyst) ;
	public:
        static bool IsCanParamExpress(BasicRhythm eRhythm, int uHR);
	};

}}}
