#pragma once
#include ".\simulatorbase_global.h"

#include "..\Common\CommonGlobal.h"


namespace jysoft { namespace simulator {

	//��ȡʵʱ��������ģ�������ֵ
    class SIMULATORBASESHARED_EXPORT IGetPhysioloySimulateData
	{
	public:
		IGetPhysioloySimulateData(void);
		virtual ~IGetPhysioloySimulateData(void);
	public:
		/*******************************************************************************
		//���ܣ���ȡ���������ڵ���������
		//������int iMilliTime:          ʱ�䣨0.1���룩
		//      float *pcBuffer:         ���ص���������
		//����ֵ:  �������ݵĳ���
		*********************************************************************************/
		virtual unsigned long GetPhysioloySimulateData(int iMilliTime, /*out*/float *pcBuffer = NULL) = 0;
	};

	//��ȡI12�����ĵ�ͼʵʱ��������ģ�������ֵ
    class SIMULATORBASESHARED_EXPORT IGetEcgSimulateData : public IGetPhysioloySimulateData
	{
	public:
		IGetEcgSimulateData();
		virtual ~IGetEcgSimulateData();
	protected:
		RhythmLead                  m_eRhythmLead;          //��ǰ�ĵ���
	private:
		I12LeadSample *             m_pTempBuff;
		unsigned long                       m_dwSize;
	public:
		/*******************************************************************************/
		//���ܣ���ȡ���������ڵ���������
		//������int iMilliTime:          ʱ�䣨0.1���룩
		//      float *pcBuffer:         ���ص���������
		//����ֵ:  �������ݵĳ���
		virtual unsigned long GetPhysioloySimulateData(int iMilliTime, /*out*/float *pcBuffer = NULL);
	public:
		/*******************************************************************************/
		//���ܣ���ȡ���������ڵĸ�������������
		//������int iMilliTime:             ʱ�䣨0.1���룩
		//      I12LeadSample *pcBuffer:    ���صĸ�������������
		//����ֵ:  �������ݵĳ���
		virtual unsigned long GetI12LeadEcgSimulateData(int iMilliTime, /*out*/I12LeadSample *pcBuffer = NULL) = 0;
	private:
		//������ʱ���ݽ�������ش�С
		void ResetTempBuffSize(unsigned long dwSize);
	};

	//��ȡ����ʵʱ��������ģ�������ֵ
    class SIMULATORBASESHARED_EXPORT IGetRespSimulateData : public IGetPhysioloySimulateData
	{
	public:
		IGetRespSimulateData();
		virtual ~IGetRespSimulateData();
	public:
		/*******************************************************************************
		//���ܣ���ȡ���������ڵ���������
		//������int iMilliTime:          ʱ�䣨0.1���룩
		//      float *pcBuffer:         ���ص���������
		//����ֵ:  �������ݵĳ���
		*********************************************************************************/
		virtual unsigned long GetPhysioloySimulateData(int iMilliTime, /*out*/float *pcBuffer = NULL);
	public:
		/*******************************************************************************
		//���ܣ���ȡ���������ڵ���������
		//������int iMilliTime:          ʱ�䣨0.1���룩
		//      float *pcBuffer:         ���ص���������
		//����ֵ:  �������ݵĳ���
		*********************************************************************************/
		virtual unsigned long GetRespSimulateData(int iMilliTime, /*out*/float *pcLeftBuffer = NULL, /*out*/float *pcRightBuffer = NULL) = 0;
	};

}}
