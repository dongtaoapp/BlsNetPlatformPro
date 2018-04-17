#pragma once
#include <string>
#include <boost/thread.hpp>
#include ".\abpsample.h"
#include ".\simulatoremulatebuild_global.h"

#include "..\Common\LoopBuffer.h"

#include "..\SimulatorBase\IGetPhysioloySimulateData.h"
#include "..\SimulatorBase\IPhysiologyStartSign.h"
#include "..\SimulatorBase\OpABPBuildInterface.h"


namespace jysoft { namespace simulator { namespace bp {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     �д�Ѫѹģ��ʵʱ����������
	�����ˣ�	 hjg
	����ʱ�䣺   2017/2/19
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATOREMULATEBUILDSHARED_EXPORT CABPSimulateBuild : public IPhysiologyStartSign
										   ,public IGetPhysioloySimulateData
										   ,public base::COpABPBuildInterface
	{
	public:
		CABPSimulateBuild(void);
		virtual ~CABPSimulateBuild(void);
	protected:  //�ӿ�IPhysiologyStartSign��������
		/*******************************************************************************/
		//���ܣ�Ѫ���������ݼ���
		//������int nDifferMilliTime:          ʱ�䣨0.1���룩
		//      int nQtoSMilliTime:            Q����S����ʱ�䣨0.1���룩
		//      int nStoTMilliTime:            S����T����ʱ�䣨0.1���룩
		//      int nCycleTime:                ����ʱ�䣨0.1���룩
		//����ֵ:  
		virtual void StartPhysiologySimpleLoad(int nDifferMilliTime, int nQtoSMilliTime, int nStoTMilliTime, int nCycleTime);
	public:     //�ӿ�IGetPhysioloySimulateData��������
		/*******************************************************************************
		//���ܣ���ȡ���������ڵ���������
		//������int iMilliTime:          ʱ�䣨0.1���룩
		//      float *pcBuffer:         ���ص���������
		//����ֵ:  �������ݵĳ���
		*********************************************************************************/
		virtual unsigned long GetPhysioloySimulateData(int iMilliTime, /*out*/float *pcBuffer = NULL);
	public:
		/*******************************************************************************/
		// �������ƣ� ModifyABPValue
		// ���ܣ� �޸�ABP��ֵ
		// ������  
		// ����ֵ:  
		virtual void ModifyABPValue(int nShrinkValue, int nStretchValue);
	public:
		/*******************************************************************************/
		// �������ƣ� Get_IGetPhysioloySimulateDataPtr
		// ���ܣ� ����IGetPhysioloySimulateData�ӿ�ָ��
		// ������ 
		// ����ֵ: 
		IGetPhysioloySimulateData * Get_IGetPhysioloySimulateDataPtr() { return (IGetPhysioloySimulateData *)this; };
		//��ʼ������
		void initialABPSample(const std::string &resPath);
	public:
		CSample * GetCurrSamplePtr(void);
		//�ر�ABPģ����
		void CloseABPSimulateBuild();
		//����ABP����״̬�������Ƿ���ʾABP����
		bool IsShowABPLinkState();
		//�����Ƿ����ABP���Ӽ��
		void Set_IsClearABPWatchLink(BOOL bClear);
		//����ABP���Ӽ��״̬
		void Set_ABPWatchLinkState(BOOL bLinking);
	private:
		//��ȡһ���ڵ����ݣ�nSystolicTimeΪǰһ�ε�ʱ�䣬nCycleTimeΪ����ʱ��
		void GetABPOutputData(int nQtoSMilliTime, int nStoTMilliTime, int nCycleTime);
		//��������start��stop����ȡ������������sample�е����λ��
		void	GetSampleDataPos(CABPSample &sample,float start,float stop,int& startpos,int& stoppos);
	protected:
		utility::CLoopBuffer<float>      m_DataBuffer;
		CABPSample              m_cSrcFirstABPSampleData; //ԭABPǰһ������
		CABPSample              m_cCurrFirstABPSampleData;
		CABPSample				m_cCurrFirstABPSampleData2;
		CABPSample              m_cSrcNextABPSampleData; //ԭABP��һ������
		CABPSample              m_cCurrNextABPSampleData;
		CABPSample				m_cOutput;//���������һ�����ݵ�����
		int						m_nShrinkValue;//����ѹ
		int						m_nStretchValue;//����ѹ
		float					m_fLastData;//ǰһ�����ε����һ������						
	private:
		boost::mutex            m_cSwapMutex;
		bool                     m_bClearWatchLink;  //�Ƿ����ABP���Ӽ��
		bool                     m_bLinkWatchABP;
		HANDLE					 m_hHeapHandle;
	};
}}}
