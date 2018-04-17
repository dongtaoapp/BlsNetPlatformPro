#pragma once
#include ".\vircardiogramparam.h"

#include "..\Common\CommonGlobal.h"


namespace jysoft { namespace simulator { 

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     I2�����ĵ�ͼ�������ϲ����ӿ���
	�����ˣ�	 hjg
	����ʱ�䣺   2013/5/13
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORBASESHARED_EXPORT ICardiogramLeads
	{
	public:
		ICardiogramLeads(void);
		virtual ~ICardiogramLeads(void);
	public:
		/*******************************************************************************/
		// �������ƣ� IsCanExpressCardiogramParam
		// ���ܣ� ���ݴ�����ĵ�ͼ�������Ƿ����ô˶���õ������ĵ�ͼ����Ҫ�Ĳ�����
		// ������  
		// ����ֵ: 
        virtual bool IsCanExpressCardiogramParam(BasicRhythm eRhythm, int uHR) = 0;
		/*******************************************************************************/
		// �������ƣ� LoadCardiogramLeadsParam
		// ���ܣ� �����ĵ�ͼ�������Ĳ���ֵ
		// ������ 
		//         
		// ����ֵ:
        virtual bool LoadCardiogramLeadsParam( BasicRhythm eRhythm, int uHR, short sConduct = 0, short sExtendParam = 0 ) = 0;
		/*******************************************************************************/
		// �������ƣ� ReLoadCardiogramParam
		// ���ܣ� 
		// ������  
		// ����ֵ: 
		virtual void ReLoadCardiogramParam() = 0;
		/*******************************************************************************/
		// �������ƣ� SeteRefurbishDataRange
		// ���ܣ� �趨ˢ�����ݵĳ̶�
		// ������  
		// ����ֵ: 
		virtual void SeteRefurbishDataRange(_eRefurbishDataRange eRange) = 0;
		/*******************************************************************************/
		// �������ƣ� GeteRefurbishDataRange
		// ���ܣ� ���ع������ݵĳ̶������ö��ֵ
		// ������  
		// ����ֵ:   RD_LoadConfigFile���RD_NoChange��ǳ 
		virtual _eRefurbishDataRange GeteRefurbishDataRange() = 0;
	public:
		/*******************************************************************************/
		// �������ƣ� GetEcgLeadParam
		// ���ܣ� ����ָ�������ĵ�ͼ�Ĳ���������
		// ������ 
		//        RhythmLead  eEcgLeadType:  
		// ����ֵ:  
		virtual CVirCardiogramParam * GetEcgLeadParam(RhythmLead  eEcgLeadType);
		//�����ĵ�ʱ��Ѫ��������ʱ��
		virtual bool GetSpO2BeginTimeToCardiogram(/*out*/long &lBeginTime, /*out*/long &lCycleTime);
		//�����粩ʱ��Ѫ��������ʱ��
		virtual bool GetSpO2BeginTimeToExtrasyst(/*out*/long &lBeginTime, /*out*/long &lPreSpO2BeginTime, /*out*/long &lCycleTime);
		/*******************************************************************************/
		// �������ƣ� ResetSyncFlag
		// ���ܣ� ����ͬ����ʶ�������������ڵ���������Э��
		// ������  
		// ����ֵ: 
		virtual void ResetSyncFlag()  { };
		//�Ƿ��ʼ����ʱ���������ĵ�ͼ����
		virtual bool IsInitialSendDoubleSampleData() { return false; };
		//�Ƿ���ȱʡ���粥
		virtual bool IsHaveDefalutExtrasyst() {return true;};
		virtual void LoadExtrasystParamPre(Extrasys eExtrasyst) { };
		virtual void LoadExtrasystParam(Extrasys eExtrasyst) { };
	public:
		//��������ʱ�䣨��λ��0.1���룩
		virtual int GetCycleTime();
		//���ص�ǰ������
		int Get_iRhythmHR();
		//���ص�ǰ������
		inline BasicRhythm Get_eCurrentRhythm() { return m_eBasicRhythm; };
	protected:
		CVirCardiogramParam *           m_pEcgLeadParam[9];
		BasicRhythm                     m_eBasicRhythm;
	protected:
		IStorage *                      m_pI12LeadsStorage;
	};

}}
