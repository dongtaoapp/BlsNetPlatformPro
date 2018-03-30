#pragma once
#include <list>
#include <string>
#include ".\VirtualCommunicate.h"
#include ".\FilterDown.h"
#include ".\FilterUp.h"
#include ".\TriggerJudgeGlobal.h"

#include "..\Common\VirtualIrp.h"
#include "..\common\criticalmutex.h"

#include "..\SimulatorBase\ITransportOrderIrpToSimulator.h"
#include "..\SimulatorBase\SimulatorOrderIrp.h"


namespace jysoft { namespace transLayer 
{
	//�������
    class TRANSLAYERSHARED_EXPORT CFormatTransport : public ITransportOrderIrpToSimulator
										  ,public ITransportOrderIrpToUp
	{
		friend class CFilterUp;
		friend class CFilterDown;
	public:
		CFormatTransport( int nCommunicateVersion );
		virtual ~CFormatTransport(void);
	public:
		HANDLE        m_hUp;
		HANDLE        m_hDown;
		HANDLE        m_hThreadOut;
		HANDLE        m_hThrdFinish[2];
		HANDLE        m_hTransportFinish; //�ϴ�����һ�����
        utility::CCriticalMutex   m_cUpMutex;
        utility::CCriticalMutex   m_cDownMutex;
		//����λ��ת����IRP��������
		std::list<irp::CVirtualIrp *> m_lstUpIrps;
		//����λ��ת����IRP��������
		std::list<irp::CVirtualIrp *> m_lstDownIrps;
	protected:
		BOOL                    m_bInitialize;
		CFilterDown *           m_pFilterDown;
		CFilterUp *             m_pFilterUp;
		HANDLE*                 m_phHaveIrp;
		ISimulateTriggerJudge*  m_pTriggerJudgeInterface; 
		int                     m_nPaceDelayTime;                //���ӳټ���
	public:
		CFilterDown * GetFilterDownPtr();
		inline HANDLE *GetTransportIrpHandlePtr() { return m_phHaveIrp;};
		inline void SetReceivePackageIrpHandlePtr(HANDLE *pHandle) { m_phHaveIrp = pHandle; };
		//�����¼�����
		void ResetTransportHandle();
	public: //���ຯ������
		/*******************************************************************************/
		// �������ƣ� OnTransportDownOrderToSimulater
		// ���ܣ�  ��ģ���˷���ָ��
		// ������ 
		// ����ֵ:  
		virtual void OnTransportDownOrderToSimulater(irp::CSimulatorOrderIrp *pOrderIrp);
		/*******************************************************************************/
		// �������ƣ� GetCommunicateVersion
		// ���ܣ�  ����ͨ�Ű汾��
		// ������ 
		// ����ֵ:  
        virtual unsigned short GetCommunicateVersion() { return 0x00; };
	public://�ӿ�ITransportOrderIrpToUp��������
		//----------------------------------------------------------------------------------
		// �������ƣ� TranslateUpIrp
		// ���ܣ�  ͨ����������ϴ���Irp
		// ������ 
		// ����ֵ:  
		virtual void OnTranslateUpIrp(irp::CVirtualIrp * pUpIrp);
		/*******************************************************************************/
		// �������ƣ� NetworkTranslateUpIrp
		// ���ܣ�  �����Irp�ɱ���������
		// ������ 
		// ����ֵ:  
		virtual void OnTranslateUpIrpNoNetwork( irp::CVirtualIrp * pUpIrp );
	protected:
		//��CFilerUp�����
		void AddUpIrpToList(irp::CVirtualIrp * pUpIrp);
		//��CFileterDown�����
		void AddDownIrpToList(irp::CVirtualIrp * pDownIrp);
	public:
		// �������ݽ��պͷ����߳�
		void StartTransportData(void);
		// ֹͣ���ݽ��պͷ����߳�
		void StopTransportData(void);
		//�������ϴ����ݵ�ͨ����
        void SetUpCommunicates(CVirtualCommunicate *pUpCommunicates[], short uNumber);
		void RmvUpCommunicate(CVirtualCommunicate *pUpCommunicate);
		//������CFilterUp��ͨ��ͨ����·
        void SetFilterUpLinkCommunicates(CVirtualCommunicate *pUpCommunicates[], short uNumber, bool bRmvCurrCommunicate = true);
		void RmvFilterUpLinkCommunicate(CVirtualCommunicate *pUpCommunicate);
		//������CFilterDown��ͨ��ͨ����·
        void SetFilterDownLinkCommunicates(CVirtualCommunicate *pDownCommunicates[], short uNumber, bool bRmvCurrCommunicate = true);
		void RmvFilterDownLinkCommunicates(CVirtualCommunicate *pDownCommunicate);
		//���´���Irp
		void TranslateDownIrp(CVirtualCommunicate *pSrcCommunicate, irp::CVirtualIrp * pDownIrp);
		//�������е�Irp���䵽�ϲ��
		irp::CVirtualIrp * TransportIrpInUplst();
		// ������׼��ͨ�Ų�
		void CreateStandantCommunicate(CVirtualCommunicate * pCommCommunicatePtr);
		//�Ƴ���׼��ͨ�Ų�
		void RmvStandantCommunicate(CVirtualCommunicate * pCommCommunicatePtr);
	public:
		//�������Ϸ��͵�Irp
		BOOL OnFilterTransUpIrp(irp::CVirtualIrp *pTransUpIrp);
		//���ٹ��˼���ʱ��
		void DecreaseFilterTransUpIrpTime(short  sSecond);
	};
}}