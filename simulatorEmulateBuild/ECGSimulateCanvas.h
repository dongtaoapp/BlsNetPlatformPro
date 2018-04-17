#pragma once
#include ".\simulatoremulatebuild_global.h"

#include "..\Common\EmulateTimer.h"
#include "..\common\criticalmutex.h"
#include "..\Common\CommonGlobal.h"
#include "..\Common\LineBuffer.h"

#include "..\SimulatorBase\IGetPhysioloySimulateData.h"
#include "..\SimulatorBase\IDistributeSimulateData.h"
#include "..\SimulatorBase\IPaneMoveControlInterface.h"


namespace jysoft { namespace simulator { namespace ecg {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     �ĵ�ͼʵʱ���ݷַ���
	�����ˣ�	 hjg
	����ʱ�䣺   2008/8/19
	//-----------------------------------------------------------------------------------------------------------------*/

    class  SIMULATOREMULATEBUILDSHARED_EXPORT CECGSimulateCanvas
	{
	public:
		CECGSimulateCanvas(void);
		virtual ~CECGSimulateCanvas(void);
	protected:
		I12LeadSample                      m_fTempBuffer[100];      //��ʱ���ݶ�ȡ����
		IGetEcgSimulateData *              m_pGetECGSimulateData;   //�ĵ�ͼ���ݻ�ȡ�ӿ�
		IDistributeEcgLeadsSimulateData *  m_pDistributeECGData;    //�ĵ�ͼ�����ɷ��ӿ�
		utility::IPaneMoveControlInterface *m_pPaneMoveControl;
		//------------------------------------------------------------------------------------------
		utility::CLineBuffer<float>  m_cPressureDisturbDatas; //��ѹʱ�����ĵ�ͼ������
	private:
		int                            m_iMilliTime;      //��λ��0.1ms
		utility::CCriticalMutex        m_cMutex;
		bool                           m_bStartDistribute;       //�Ƿ�ʼ�ɷ�
		bool                           m_bPressureAct;          //��ѹ��ʼ\����(TRUE:��ʼ��FALSE:����)
		//-------------------------------------------------------------------------------------------------
		utility::CEmulateTimer*        t;
	public:
		//ֹͣ��������
		void StopTimerHandle();
	public:
		void InitialEcgSimulate(IGetEcgSimulateData *pGetEcgSimulateData, utility::IPaneMoveControlInterface *pMoveControlInterface, const std::string &resPath, int iMilliTime = 400);
		//�ͷŹ���
		void FreeHook();
		// ��ʼ�ַ��ĵ�ͼʵʱ����
		void StartDistributeSimulateData();
		//�ַ���������
		void OnDistributeSimulateDataHandle();
		//ֹͣ�ַ��ĵ�ͼʵʱ����
		void StopDistributeSimulateData();
		//���ð�ѹ��ʼ\����״̬(TRUE:��ʼ��FALSE:����)
		void SetPressureActState(bool bState);
	public:
		//��ʼ�����ĵ�ͼ����
		void OnStartWatchEcg(IDistributeEcgLeadsSimulateData *pDistributeECGData);
		//�Ͽ����ĵ�ͼ�ļ��
		void OnCutWatchEcg(IDistributeEcgLeadsSimulateData *pCutDistributeECGData);
	private:
		//��ʼ�����ذ�ѹʱ�����ĵ�ͼ������
		void InitialLoadPressureDisturbDatas( const std::string &strDisturbDataFile );
		//���Ӱ�ѹʱ�����ĵ�ͼ������
		void OverlapPressureDisturbData(I12LeadSample *pEcgLeadSamples, short  dwNumber);
	};

}}}
