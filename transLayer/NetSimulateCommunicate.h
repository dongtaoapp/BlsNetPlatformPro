#pragma once
#include ".\LayerGlobal.h"
#include ".\virtualcommunicate.h"
#include ".\BufferAndJudgeCPR.h"
#include ".\TriggerJudgeGlobal.h"

#include "..\common\CommonGlobal.h"
#include "..\Common\VirTcpTransferOpGather.h"
#include "..\Common\NetTransferVir.h"

#include "..\simulatorBase\SimulatorOrderIrp.h"

namespace jysoft { namespace transLayer 
{
    class TRANSLAYERSHARED_EXPORT CNetSimulateCommunicate : public CVirtualCommunicate
								  , public network::CVirReceiveSimulateCommNetDataOp
	{
	public:
		CNetSimulateCommunicate(network::CNetTransferVir *pVirNetTransfer);
		virtual ~CNetSimulateCommunicate(void);
	public: //�ӿ�CVirReceiveSimulateCommNetDataOp��������
		virtual bool IsCanRecvNetDataOp(network::NET_BUFFER_OBJ *buf) { return true; };
		//������յ�������
		virtual void OnReceiveNetDataOp(network::NET_SOCKET_OBJ *sock, network::NET_BUFFER_OBJ *buf);
	public: //����CVirtualCommunicate��������
		// ��ʼ��ͨ�Žӿڣ�ʹ�����������շ�����
		virtual bool InitializeCommunicate(void);
		//�����ݴ�����λ��
		virtual void TransDownData(irp::CVirtualIrp * pDownIrp);
		//���ݴ���������
        virtual void TransUpData(void *lpData, short uNumber) ;
		//����CPR����
		virtual void TransUpCPRDataFromBuffer(const _CPRData *ptrdwCPRData, int nLength);
		//�ϴ�CPR��ʼ����
		virtual void TransUpCPRStartOrder();
		//�ϴ�CPR��������
		virtual void TransUpCPRStopOrder();
        virtual void SendData(void *lpByte, short uSize);
		//-------------------------------------------------------------------------------------------
		virtual void OnTime(int nMicroSecond);
		//��ʼCPR����ģ��
		void StartCPRSimulate();
		//����CPR���弰�ж�
		void ResetBufferAndJudgeCPR();
		//����ͨ��Э��汾�ӿ�
		void SetSimulateTriggerJudgePtr(ISimulateTriggerJudge *pJudgeInterface);
	public:
		//�жϲ��ϴ��¼�
		void JudgeDataTypeAndTransUp(_VirDataStruct *pDataStruct);
	public:
		inline void set_bTcpEstablishSec( bool bSec ) { m_bTcpEstablishSec = bSec; };
		inline bool get_bTcpEstablishSec() { return m_bTcpEstablishSec; };
	protected:
		ISimulateTriggerJudge*   m_pTriggerJudgeInterface; 
	public:
		CBufferAndJudgeCPR      m_cBufferAndJudgeCPR; 
		HANDLE                  m_hThrdOut;  //�߳��˳�
		HANDLE                  m_hThrdFinish;
		HANDLE                  m_hPause;    //��ͣ
	protected:
		network::CNetTransferVir   *              m_pVirNetTransferPtr;
		bool                             m_bTcpEstablishSec;
	};
}}
