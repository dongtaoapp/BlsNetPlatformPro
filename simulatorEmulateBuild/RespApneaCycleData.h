#pragma once
#include "respcycledata.h"


namespace jysoft { namespace simulator { namespace resp {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ֹͣ����ʱ����������
	�����ˣ�	 hjg
	����ʱ�䣺   2017/2/22
	//-----------------------------------------------------------------------------------------------------------------*/

	class CRespApneaCycleData : public CRespCycleData
	{
	public:
		CRespApneaCycleData(CInspirationSegment *pInspirationSegment, CExhaleSegment *pExhaleSegment, int nRespRate, int nInspirationTime);
		virtual ~CRespApneaCycleData(void);
	protected:
		int        m_iSampleSec;      //ÿ��Ĳ�����
	public:
		//���ص�ǰ��������
		virtual int GetCurrentRespRate() { return 0; };
		//���õ�ǰ��������
		inline void Set_CurrentRemainVolume(float fVolume) { m_fCurrentRemainVolume = fVolume; };
		//���ñ����ڽ�����Ĳ�������
		inline void Set_RemainVolume(float fVolume) { m_fRemainVolume = fVolume; };
		/*******************************************************************************/
		// �������ƣ� JudgeIsRepeatCycleData
		// ���ܣ� �ж��Ƿ�ͬһ���ڵ�����
		// ������ int nRespRate:  ��������
		//        int nMillitInspirationTime: ����ʱ��(��λ:0.1ms)
		//        float fCurrentRemainVolume: ��ǰ��������    
		//        float fSumVolume:           �����ڵ�������
		//        float fRemainVolume:        �����ڽ�����Ĳ�������
		// ����ֵ:  
		virtual bool JudgeIsRepeatCycleData(int nRespRate, int nMillitInspirationTime, float fCurrentRemainVolume, float fSumVolume, float fRemainVolume);
		/*******************************************************************************/
		// �������ƣ� ResetPrepareReadSampleData
		// ���ܣ�  �������ݵĶ�ȡ׼��
		// ������ 
		// ����ֵ:  
		virtual void ResetPrepareReadSampleData();
		/*******************************************************************************
		//���ܣ���ȡʱ�������ڵĺ�������
		//������int iMilliTime:          ʱ�䣨0.1���룩
		//      float *pcBuffer:         ���صĺ�������
		//      BYTE byteAddress:        Ŀ���豸��ַ��
		//����ֵ: ���ݵĳ���
		*********************************************************************************/
        virtual short GetRespSimulateData(int iMilliTime, unsigned char byteAddress, /*out*/float *pcLeftBuffer = NULL, /*out*/float *pcRightBuffer = NULL);
	};
}}}
