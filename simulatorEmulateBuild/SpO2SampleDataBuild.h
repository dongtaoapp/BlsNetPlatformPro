#pragma once
#include <boost/thread.hpp>
#include ".\simulatoremulatebuild_global.h"

#include "..\Common\LoopBuffer.h"

#include "..\SimulatorBase\IPhysiologyStartSign.h"
#include "..\SimulatorBase\Sample.h"
#include "..\SimulatorBase\IGetPhysioloySimulateData.h"
#include "..\SimulatorBase\OpSpO2BuildInterface.h"


namespace jysoft { namespace simulator { namespace SpO2 {

    class SIMULATOREMULATEBUILDSHARED_EXPORT CSpO2SampleDataBuild : public IPhysiologyStartSign
											  ,public IGetPhysioloySimulateData
											  ,public base::COpSpO2BuildInterface
	{
	public:
		CSpO2SampleDataBuild(void);
		virtual ~CSpO2SampleDataBuild(void);
	protected: //IPhysiologyStartSign���ຯ������
		/*******************************************************************************/
		//���ܣ�Ѫ���������ݼ���
		//������int nDifferMilliTime:          ʱ�䣨0.1���룩
		//      int nQtoSMilliTime:            Q����S����ʱ�䣨0.1���룩
		//      int nStoTMilliTime:            S����T����ʱ�䣨0.1���룩
		//      int nCycleTime:                ����ʱ�䣨0.1���룩
		//����ֵ:  
		virtual void StartPhysiologySimpleLoad(int nDifferMilliTime, int nQtoSMilliTime, int nStoTMilliTime, int nCycleTime);
	protected: //COpSpO2BuildInterface���ຯ������
		/*******************************************************************************/
		// �������ƣ� ModifySpO2ValuePrecent
		// ���ܣ� �޸�Ѫ���İٷֱ�Ũ��
		// ������  int nSpO2Value:            Ѫ���ٷֱ�Ũ��ֵ
		// ����ֵ:  
		virtual void ModifySpO2ValuePrecent( int nSpO2Value );
	public://IGetPhysioloySimulateData���ຯ������
		/*******************************************************************************
		//���ܣ���ȡ���������ڵ���������
		//������int iMilliTime:          ʱ�䣨0.1���룩
		//      float *pcBuffer:         ���ص���������
		//����ֵ:  �������ݵĳ���
		*********************************************************************************/
		virtual unsigned long GetPhysioloySimulateData(int iMilliTime, /*out*/float *pcBuffer = NULL);
		/*******************************************************************************/
		// �������ƣ� Get_IGetPhysioloySimulateDataPtr
		// ���ܣ� ����IGetPhysioloySimulateData�ӿ�ָ��
		// ������ 
		// ����ֵ: 
		virtual IGetPhysioloySimulateData * Get_IGetPhysioloySimulateDataPtr(){ return dynamic_cast<IGetPhysioloySimulateData*>(this); };
	public:
		CSample * GetCurrSamplePtr(void);
		//�ر�Ѫ��ģ����
		void CloseSpO2SimulateBuild();
		//����SpO2����״̬�������Ƿ���ʾSpO2����
		bool IsShowSpO2yLinkState();
		//�����Ƿ����SpO2���Ӽ��
		void Set_IsClearSpO2WatchLink(bool bClear);
		//����SpO2���Ӽ��״̬
		void Set_SpO2WatchLinkState(bool bLinking);
	public:
		inline int  GetValue_SpO2Value() { return m_nSpO2Value; };
		//��ʼ������
		void initialSpO2Sample(const std::string &resPath);
	protected:
		utility::CLoopBuffer<float>      m_DataBuffer; //Ѫ�����ݻ�����
		CSample                 m_cSrcSpO2SampleData; //ԭѪ������
		CSample                 m_cCurrSpO2SampleData; //��ǰʹ�õ�Ѫ������
		int                     m_nSpO2Value;          //Ѫ��ֵ
	private:
		boost::mutex            m_cSwapMutex;
		HANDLE                  m_hHeapHandle;
		bool                     m_bClearWatchLink;//�Ƿ����SpO2���Ӽ��
		bool                     m_bLinkWatchSpO2;
		int                      m_nReflushCalculate;   //��ֵˢ�¼�����
	};
}}}
