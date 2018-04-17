#pragma once
#include <list>
#include <string>
#include <boost/thread.hpp>
#include ".\VirtualCommunicate.h"
#include ".\FilterDown.h"
#include ".\FilterUp.h"
#include ".\TriggerJudgeGlobal.h"

#include "..\Common\VirtualIrp.h"

#include "..\SimulatorBase\ITransportOrderIrpToSimulator.h"
#include "..\SimulatorBase\SimulatorOrderIrp.h"


namespace jysoft { namespace transLayer 
{
	//命令传输类
    class TRANSLAYERSHARED_EXPORT CFormatTransport : public ITransportOrderIrpToSimulator
										  ,public ITransportOrderIrpToUp
	{
		friend class CFilterUp;
		friend class CFilterDown;
	public:
		CFormatTransport( int nCommunicateVersion );
		virtual ~CFormatTransport(void);
	protected:
		boost::condition_variable_any*       cond_IrpUp;
		boost::condition_variable_any        cond_getDownIrp;
		boost::mutex     muUpIrp;
		boost::mutex     muDownIrp;
		//向上位机转发的IRP缓冲链表
		std::list<irp::CVirtualIrp *> m_lstUpIrps;
		//向下位机转发的IRP缓冲链表
		std::list<irp::CVirtualIrp *> m_lstDownIrps;
	protected:
		bool                    m_bInitialize;
		CFilterDown *           m_pFilterDown;
		CFilterUp *             m_pFilterUp;
		ISimulateTriggerJudge*  m_pTriggerJudgeInterface; 
		int                     m_nPaceDelayTime;                //起搏延迟计数
		boost::thread_group     tgDownIrpThread;
	public:
		inline void SetReceivePackageIrpHandlePtr(boost::condition_variable_any *pHandle) { cond_IrpUp = pHandle; };
		//重置事件处理
		void ResetTransportHandle();
	public: //基类函数重载
		/*******************************************************************************/
		// 函数名称： OnTransportDownOrderToSimulater
		// 功能：  向模拟人发送指令
		// 参数： 
		// 返回值:  
		virtual void OnTransportDownOrderToSimulater(irp::CSimulatorOrderIrp *pOrderIrp);
		/*******************************************************************************/
		// 函数名称： GetCommunicateVersion
		// 功能：  返回通信版本号
		// 参数： 
		// 返回值:  
		virtual short GetCommunicateVersion() { return 0x00; };
	public://接口ITransportOrderIrpToUp函数重载
		//----------------------------------------------------------------------------------
		// 函数名称： TranslateUpIrp
		// 功能：  通过传输层向上传输Irp
		// 参数： 
		// 返回值:  
		virtual void OnTranslateUpIrp(irp::CVirtualIrp * pUpIrp);
		/*******************************************************************************/
		// 函数名称： NetworkTranslateUpIrp
		// 功能：  传输的Irp由本案例处理
		// 参数： 
		// 返回值:  
		virtual void OnTranslateUpIrpNoNetwork( irp::CVirtualIrp * pUpIrp );
	protected:
		//由CFilerUp类调用
		void AddUpIrpToList(irp::CVirtualIrp * pUpIrp);
		//由CFileterDown类调用
		void AddDownIrpToList(irp::CVirtualIrp * pDownIrp);
	public:
		// 构建数据接收和发送线程
		void StartTransportData(void);
		// 停止数据接收和发送线程
		void StopTransportData(void);
		//设置向上传数据的通信类
		void SetUpCommunicates(CVirtualCommunicate *pUpCommunicates[], short uNumber);
		void RmvUpCommunicate(CVirtualCommunicate *pUpCommunicate);
		//设置与CFilterUp连通的通信链路
		void SetFilterUpLinkCommunicates(CVirtualCommunicate *pUpCommunicates[], short uNumber, bool bRmvCurrCommunicate = true);
		void RmvFilterUpLinkCommunicate(CVirtualCommunicate *pUpCommunicate);
		//设置与CFilterDown连通的通信链路
		void SetFilterDownLinkCommunicates(CVirtualCommunicate *pDownCommunicates[], short uNumber, bool bRmvCurrCommunicate = true);
		void RmvFilterDownLinkCommunicates(CVirtualCommunicate *pDownCommunicate);
		//向下传输Irp
		void TranslateDownIrp(CVirtualCommunicate *pSrcCommunicate, irp::CVirtualIrp * pDownIrp);
		//将链表中的Irp传输到上层端
		irp::CVirtualIrp * TransportIrpInUplst();
		// 创建标准的通信层
		void CreateStandantCommunicate(CVirtualCommunicate * pCommCommunicatePtr);
		//移除标准的通信层
		void RmvStandantCommunicate(CVirtualCommunicate * pCommCommunicatePtr);
	public:
		//过滤向上发送的Irp
		bool OnFilterTransUpIrp(irp::CVirtualIrp *pTransUpIrp);
		//减少过滤计数时间
		void DecreaseFilterTransUpIrpTime(short  sSecond);
		bool isTransInDownIrps() { return (m_bInitialize && m_lstDownIrps.size() > 0) ? true : false;};
		bool isTransUpIrps();
	private:
		void ThrdTransDownIrpFunc();
	};
}}
