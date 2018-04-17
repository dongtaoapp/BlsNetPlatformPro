#pragma once
#include ".\CardiogramConfigHandle.h"

#include "..\SimulatorBase\ICardiogramLeads.h"


namespace jysoft { namespace simulator { namespace ecg {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ��ͬ�����ĵ�ͼ���������ݹ����װ��
	�����ˣ�	 hjg
	����ʱ�䣺   2013/5/16
	//-----------------------------------------------------------------------------------------------------------------*/
	class CEcgLeadSamples;
	class CEcgCycleLeadsBuild
	{
	public:
		CEcgCycleLeadsBuild(void);
		virtual ~CEcgCycleLeadsBuild(void);
	public:
		/*******************************************************************************/
		// �������ƣ� CreateCycleLeadsData
		// ���ܣ� ������Բ�ͬ�����ĵ���������
		// ������  
		//          ICardiogramLeads *pVirCardiogramLeads:         
		//          /*out*/CEcgLeadSamples *pDestLeadSamples:      I12���������ݣ�aVR, aVL, aVF�������ĵ������㣩
		// ����ֵ: 
		bool CreateCycleLeadsData(ICardiogramLeads *pVirCardiogramLeads, /*out*/CEcgLeadSamples *pDestLeadSamples);
		/*******************************************************************************/
		// �������ƣ� CreateExtrasystData
		// ���ܣ� �����粫����
		// ������  
		//         int iCycleTime:                              ��������ʱ�䣨��λ��0.1ms��
		//         Extrasys eExtrasyst:                         �粫����
		//         ICardiogramLeads *pVirCardiogramLeads:       
		//         /*in,out*/CEcgLeadSamples *pDestLeadSamples:   
		// ����ֵ: 
		bool CreateExtrasystData(int iCycleTime, Extrasys eExtrasyst, ICardiogramLeads *pVirCardiogramLeads, /*in,out*/CEcgLeadSamples *pDestLeadSamples);
	protected:
        bool CreateCycleLeadData(CVirCardiogramParam *pVirParam, CCardiogramConfigHandle *pConfigHandle, /*out*/CSample *pDestSample);
		//���ص��������ࣨaVR, aVL, aVF�ȵĹ���Ϊ�գ�
		CCardiogramConfigHandle * GetCardiogramConfigHandlePtr( RhythmLead eEcgLeadType);
	protected:
		//���������࣬����Ϊ��I, II, III, V1, V2, V3, V4, V5, V6
		CCardiogramConfigHandle                 m_cCardiogramConfigHandle[9];  
	};
}}}
