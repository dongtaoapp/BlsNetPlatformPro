#pragma once
#include ".\InspirationSegment.h"
#include ".\ExhaleSegment.h"

#include "..\Common\CommonGlobal.h"
#include "..\Common\LoopBuffer.h"

#include "..\SimulatorBase\ICO2SimulateSign.h"
#include "..\SimulatorBase\SimulatorOrderIrp.h"
#include "..\SimulatorBase\ITransportOrderIrpToSimulator.h"

namespace jysoft { namespace simulator { namespace resp {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ��������κͺ��������ݲ����࣬����һ�����ڵĺ�������
	�����ˣ�	 hjg
	����ʱ�䣺   2017/2/22
	//-----------------------------------------------------------------------------------------------------------------*/
	class CRespCycleData
	{
	protected:
		struct RespDataStruct
		{
			float      m_fLungVolumeValue_L;   //�������
			float      m_fLungVolumeValue_R;   //�ҷ�����
		};
	public:
		CRespCycleData(CInspirationSegment *pInspirationSegment, CExhaleSegment *pExhaleSegment, int nRespRate, int nInspirationTime);
		virtual ~CRespCycleData(void);
	protected:
		CInspirationSegment *       m_pInspirationSegment;  //����������
		CExhaleSegment *            m_pExhaleSegment;       //����������
		//------------------------------------------------------------------------------------------
		int                         m_nRespRate;            //��������
		int                         m_nRespCycleTime;       //����ʱ��(��λ:0.1ms)
		int                         m_nInspirationTime;     //����ʱ��(��λ:0.1ms)
		int                         m_nInspirationToCO2Time;//����ʱ��CO2�轵ʱ��(��λ:0.1ms)
		int                         m_nExhaleToCO2Time;     //����ʱ��CO2����ʱ��(��λ:0.1ms)
		float                       m_fCurrentRemainVolume; //��ǰ��������       (��λ:ml)  
		float                       m_fSumVolume;           //�����ڵ�������     (��λ:ml)
		float                       m_fRemainVolume;        //�����ں�Ĳ������� (��λ:ml)
		//-------------------------------------------------------------------------------------------
		utility::CLoopBuffer<RespDataStruct> m_cInspirationLungVolumes;
		utility::CLoopBuffer<RespDataStruct> m_cExhaleLungVolumes;
	private:
		int                        *m_pbSynchronizeSignSend;  //ͬ���ź��Ƿ��ѷ���
	protected:
		ICO2SimulateSign               *m_pCO2SimulateSignInteface;
		transLayer::ITransportOrderIrpToSimulator  *m_pTransportOrderInterface; 
	public:
		_eRefurbishDataRange            m_eRefurbishDataRange;
	public:
		//���ص�ǰ��������
		virtual int GetCurrentRespRate() { return m_nRespRate; };
		//�������ݵ�������ʱ��(��λ:0.1ms)
		inline int Get_RespCycleTime() { return m_nRespCycleTime; };
		inline void Set_RespCycleTime(int nTime ) { m_nRespCycleTime = nTime; };
		//���ر����ں�Ĳ������� (��λ:ml)
		virtual float Get_RemainRespVolume() { return m_fRemainVolume; };
		//��������ʱ��CO2�轵ʱ��(��λ:0.1ms)
		inline void Set_InspirationToCO2Time(int nTime) { m_nInspirationToCO2Time = nTime; };
		//���ú���ʱ��CO2����ʱ��(��λ:0.1ms)
		inline void Set_ExhaleToCO2Time(int nTime) { m_nExhaleToCO2Time = nTime; };
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
	public:
		void Set_CO2SimulateSignInteface(ICO2SimulateSign *pInterface);
		void Set_TransportOrderIrpToSimulatorInteface(transLayer::ITransportOrderIrpToSimulator *pInterface, int *pIsSynSignSendFlag);
	public:
		//����ָ��,����ģ���˵ĺ���
		void TransportOrderToSimulator();
	protected:
		//����ָ��Irp
		irp::CSimulatorOrderIrp * TranslateRespIrp( bool bSynchronizeSignOrder );
	};
}}}
