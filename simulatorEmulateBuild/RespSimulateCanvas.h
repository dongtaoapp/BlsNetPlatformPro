#pragma once
#include ".\simulatoremulatebuild_global.h"

#include "..\Common\EmulateTimer.h"
#include "..\common\criticalmutex.h"

#include "..\SimulatorBase\IPaneMoveControlInterface.h"

namespace jysoft { namespace simulator {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ����ʵʱ���ݷַ���
	�����ˣ�	 hjg
	����ʱ�䣺   2008/7/16
	//-----------------------------------------------------------------------------------------------------------------*/

	class IGetRespSimulateData;
	class IDistributeRespSimulateData;
    class SIMULATOREMULATEBUILDSHARED_EXPORT CRespSimulateCanvas
	{
	public:
		CRespSimulateCanvas();
		~CRespSimulateCanvas(void);
	protected:
		IGetRespSimulateData           *m_pGetSimulateData;
		IDistributeRespSimulateData    *m_pDistributeData;
		utility::IPaneMoveControlInterface      *m_pPaneMoveControl;
	private:
		float                       m_fTempSumLungBuffer[100]; //��ʱ���ݶ�ȡ����
		float                       m_fTempLeftLungBuffer[100];
		int                         m_iMilliTime;      //��λ��0.1ms
		utility::CCriticalMutex     m_cMutex;
		bool                        m_bStartDistribute;       //�Ƿ�ʼ�ɷ�
		//-------------------------------------------------------------------------------------------------
		utility::CEmulateTimer*     t;
	public:
		//ֹͣ��������
		void StopTimerHandle();
	public:
		void InitialRespSimulate(IGetRespSimulateData *pSimulateData, utility::IPaneMoveControlInterface *pMoveControlInterface, int iMilliTime = 800);
		//�ͷŹ���
		void FreeHook();
		// ��ʼ�ַ�����ʵʱ����
		void StartDistributeSimulateData();
		//�ַ���������
		void OnDistributeSimulateDataHandle();
		//ֹͣ�ַ�����ʵʱ����
		void StopDistributeSimulateData();
	public:
		//��ʼ���Ӻ�������
		void OnStartWatchResp(IDistributeRespSimulateData *pDistributeData);
		//�Ͽ�������ļ��
		void OnCutWatchResp(IDistributeRespSimulateData *pCutDistributeData);
	};
}}
