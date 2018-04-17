#pragma once
#include <list>
#include <Windows.h>
#include <pugixml.hpp>
#include <boost/thread.hpp>
#include ".\XRunFramework.h"
#include ".\XSceneActFrame.h"
#include ".\IAclsFlowStrategy.h"
#include ".\IHandleIrpsCollect.h"

#include "..\common\VirtualIrp.h"
#include "..\common\EmulateTimer.h"
#include "..\common\criticalmutex.h"

#include "..\transLayer\FormatTransport.h"

#include "..\simulatorBase\VirEventIrp.h"
#include "..\simulatorBase\ITransportOrderIrpToSimulator.h"
#include "..\simulatorBase\ShowEventSignUpdateInterface.h"


namespace jysoft { namespace flowEngine 
{
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     脚本流程处理基类
	创建人：	 hjg
	创建时间：   2017/3/1
	//-----------------------------------------------------------------------------------------------------------------*/
	class CBlsSimulateCase;
	class CBlsMainFlowVirtual : public IHandleIrpsCollect
	{
	public:
		CBlsMainFlowVirtual(CBlsSimulateCase  *pSimulateCase, transLayer::CFormatTransport* pTransport);
		virtual ~CBlsMainFlowVirtual(void);
	public:
		// 开始运行场景
		void StartCurrScenario();
		// 暂停目前运行的场景
		void PauseCurrScenario( bool bClearSimulator );
	protected://属性
		std::list<irp::CVirtualIrp *>  m_IrpList;
		//------------------------------------------------------------------------
		//boost::mutex     muIrpHandle;
		boost::mutex     muPackage;
		boost::condition_variable_any    cond_IrpHandle;
		boost::condition_variable_any    cond_IrpRecv;
		utility::CEmulateTimer*          secondEumlate;
		boost::thread_group   tg;
	protected:
		CXRunFramework                  m_cRunFramework;
		IAclsFlowStrategy *             m_pAclsFlowStrategy;   //脚本引擎场景转移策略
		CBlsSimulateCase *              m_pBlsSimulateCase;    //BLS场景训练的运行案例
		simulator::base::CShowEventSignUpdateInterface * m_pShowEventSignInterface;
	protected:
		utility::CCriticalMutex          m_cHandleActionIrpMutex;
	public://低层数据传输类
		transLayer::CFormatTransport*   m_pFormatTransport;
	private://属性
		_FlowState            m_eState;       //状态
	public:
		// 将需要处理的IRP发到处理队列或其它相应的处理
		bool AddNeedHandleIrp(irp::CVirtualIrp * pVirIrp);
		//处理消息包
		virtual void OnHandleIrp(irp::CVirtualIrp *pVirIrp);
	public:
		/*******************************************************************************/
		// 函数名称： ResetScenario
		// 功能： 重置ACLS流程处理中心
		// 参数： 
		// 返回值:  
		virtual pugi::xml_node ResetScenario();
		/*******************************************************************************/
		// 函数名称： DoFlowNextScenario
		// 功能： 执行下个场景框
		// 参数： 
		//       DWORD  dwFrameID:      场景框的标识值
		//       eEventSign eEvent:     
		// 返回值:  
		pugi::xml_node DoFlowNextScenario(unsigned short  dwFrameID, eEventSign eEvent = ES_Normal);
		/*******************************************************************************/
		// 函数名称： DoFlowNextScenario
		// 功能： 执行下个场景框
		// 参数： 
		//       IXMLDOMNode *pScenarioNode:      场景框的Node
		//       eEventSign eEvent:     
		// 返回值:  
		pugi::xml_node DoFlowNextScenario(pugi::xml_node *pScenarioNode, eEventSign eEvent = ES_Normal);
		/*******************************************************************************/
		// 函数名称： DoFlowSceneActRun
		// 功能： 执行情景框框
		// 参数： 
		//       DWORD dwSceneActFrameID:      情景框的标识值
		//       BOOL bLogoutFlow:             是否退出主流程
		//       eEventSign eEvent:     
		// 返回值:  
		CXSceneActFrame * DoFlowSceneActRun(unsigned short dwSceneActFrameID, bool bLogoutFlow, eEventSign eEvent = ES_Normal);
		//返回模拟人通信接口
		transLayer::ITransportOrderIrpToSimulator * GetTransportOrderIrpToSimulatorInterface() { return (transLayer::ITransportOrderIrpToSimulator *)m_pFormatTransport; };
		//返回当前对应设置的Action
		inline IGetPhysiologyActionObj * Get_PhysiologyActionPtr() { return (IGetPhysiologyActionObj *)&m_cRunFramework; };
		inline IAclsFlowStrategy * Get_IAclsFlowStrategyPtr() { return m_pAclsFlowStrategy; };
		//返回引擎的状态
		inline _FlowState Get_eFlowState() { return m_eState; };
	public:
		/*******************************************************************************/
		// 函数名称： CreateScenario
		// 功能： 根据场景脚本文件，初始化ACLS流程处理中心
		// 参数： 
		//       rootElement: 
		// 返回值:  
		virtual pugi::xml_node  CreateScenario( pugi::xml_node rootElement ) = 0;
	public:
		/*******************************************************************************/
		// 函数名称： StartLinkEventSignShowInterfaces
		// 功能： 初始化连接事件显示接口
		// 参数： 
		//        CModularBarsShowInterfacesAggregate *pShowAggregate:      
		// 返回值:  
		void StartLinkEventSignShowInterfaces(simulator::base::CShowEventSignUpdateInterface *pShowInterface);
		/*******************************************************************************/
		// 函数名称： DoManualDispatchEventFlow
		// 功能： 手动跳转事件框
		// 参数：      
		// 返回值: 
		void DoManualDispatchEventFlow(pugi::xml_node *pEventXMLNode);
		/*******************************************************************************/
		// 函数名称： UnLinkModularBarShowInterfaces
		// 功能： 断开连接事件显示接口
		// 参数： 
		//        CModularBarsShowInterfacesAggregate *pShowAggregate:      
		// 返回值:  
		void UnLinkEventSignShowInterfaces(simulator::base::CShowEventSignUpdateInterface *pShowInterface);
	public:
		/*******************************************************************************/
		// 函数名称： ExecInitialFramework
		// 功能： 初始化执行当前的解析Actions
		// 参数： 
		//   
		// 返回值:  
		virtual void ExecInitialFramework(SimulatePatientType ePatientType) = 0;
		/*******************************************************************************/
		// 函数名称： DoUpdateEventSignShow
		// 功能： 显示事件界面效果
		// 参数：  
		//         CVirEventIrp *pVirEventIrp: 
		//         CShowEventSignUpdateInterface  *pShowEventSignInterface:
		// 返回值:  
		virtual void DoUpdateEventSignShow(irp::CVirEventIrp *pVirEventIrp, simulator::base::CShowEventSignUpdateInterface  *pShowEventSignInterface, CBlsSimulateCase *pBlsCase);
		//执行当前的解析Actions
		void ExecNextFramework(eEventSign eEvent = ES_Normal);
		//创建流程线程
		bool CreateFlowThreads();
		//设置CPR事件的操作模式为当前模式
		void FilterCPREventIrp(irp::CVirEventIrp *pVirEventIrp, CBlsSimulateCase *pBlsCase);
	public:
		/*******************************************************************************/
		// 函数名称： ExecuteAction
		// 功能： 执行体征的设置
		// 参数： 
		//       IXMLDOMElement *pRootElement: 
		// 返回值:  
		void ExecuteActions(std::list<simulator::CXActionVirtual *> *plstVirActions, short sTransferTime = 0);
	protected:
		//时钟线程函数
		void  _ThrdTimeFunc();
		//从下端接收信息包线程函数
		void _ThrdReceiveIrpFunc();
		//消息包处理线程函数
		void _ThrdHandleIrpFunc();
		//是否能处理Irp
		bool isCanPackageHandle();
		//是否有通信层上传的Irp包
		bool isTransInUpIrps();
	};
}}
