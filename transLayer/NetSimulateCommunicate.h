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
	public: //接口CVirReceiveSimulateCommNetDataOp函数重载
		virtual bool IsCanRecvNetDataOp(network::NET_BUFFER_OBJ *buf) { return true; };
		//处理接收到的数据
		virtual void OnReceiveNetDataOp(network::NET_SOCKET_OBJ *sock, network::NET_BUFFER_OBJ *buf);
	public: //基类CVirtualCommunicate函数重载
		// 初始化通信接口，使其能正常的收发数据
		virtual bool InitializeCommunicate(void);
		//将内容传给下位机
		virtual void TransDownData(irp::CVirtualIrp * pDownIrp);
		//数据传到程序中
        virtual void TransUpData(void *lpData, short uNumber) ;
		//传输CPR数据
		virtual void TransUpCPRDataFromBuffer(const _CPRData *ptrdwCPRData, int nLength);
		//上传CPR开始命令
		virtual void TransUpCPRStartOrder();
		//上传CPR结束命令
		virtual void TransUpCPRStopOrder();
        virtual void SendData(void *lpByte, short uSize);
		//-------------------------------------------------------------------------------------------
		virtual void OnTime(int nMicroSecond);
		//开始CPR数据模拟
		void StartCPRSimulate();
		//重置CPR缓冲及判断
		void ResetBufferAndJudgeCPR();
		//设置通信协议版本接口
		void SetSimulateTriggerJudgePtr(ISimulateTriggerJudge *pJudgeInterface);
	public:
		//判断并上传事件
		void JudgeDataTypeAndTransUp(_VirDataStruct *pDataStruct);
	public:
		inline void set_bTcpEstablishSec( bool bSec ) { m_bTcpEstablishSec = bSec; };
		inline bool get_bTcpEstablishSec() { return m_bTcpEstablishSec; };
	protected:
		ISimulateTriggerJudge*   m_pTriggerJudgeInterface; 
	public:
		CBufferAndJudgeCPR      m_cBufferAndJudgeCPR; 
		HANDLE                  m_hThrdOut;  //线程退出
		HANDLE                  m_hThrdFinish;
		HANDLE                  m_hPause;    //暂停
	protected:
		network::CNetTransferVir   *              m_pVirNetTransferPtr;
		bool                             m_bTcpEstablishSec;
	};
}}
