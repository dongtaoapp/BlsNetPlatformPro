#pragma once
#include ".\VirSimulateSymptomsCollect.h"
#include ".\ISetSimulateSymptoms.h"
#include ".\XActionVirtual.h"
#include ".\PnPFacilityGlobal.h"

#include "..\SimulatorBase\SyncPnpFacilities.h"
#include "..\SimulatorBase\OpPhysBuildInterfacesAggregate.h"
#include "..\SimulatorBase\SymptomsShowInterfacesAggregate.h"

#include "..\Common\CommonGlobal.h"
#include "..\Common\EventHandleClockIrpOp.h"
#include "..\Common\EventHandleCPRStatIrpOp.h"
#include "..\Common\RealTimeDataHandleIrpOp.h"
#include "..\Common\EventHandleCustomIrpOp.h"

namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     模拟人生理体征参数集合管理类，存贮当前模拟的状态
	创建人：	 hjg
	创建时间：   2017/2/17
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORSYMPTOMSHARED_EXPORT CSimulateSymptomsCollect   : public CVirSimulateSymptomsCollect
													,public ISetSimulateSymptoms
													,public irp::CEventHandleClockIrpOp
													,public irp::CEventHandleCustomIrpOp
													,public irp::CEventHandleCPRStatIrpOp
													,public irp::CRealTimeDataHandleIrpOp
	{
	public:
		CSimulateSymptomsCollect(void);
		virtual ~CSimulateSymptomsCollect(void);
	public://接口ISetSimulateSymptoms的函数重载
		/*******************************************************************************/
		// 函数名称： initialScenarioSet
		// 功能：   生理体征初始化为当前场景状态
		// 参数：   std::list<CXActionVirtual *> *plstActions: 
		////        SimulatePatientType ePatientType: 模拟人类型
		// 返回值:  tag_TrendValue: 当前场景所设置的体征值
		virtual void initialScenarioSet(std::list<CXActionVirtual *> *plstActions, SimulatePatientType ePatientType);
		//初始化体征模拟曲线构造器
		virtual void initialSimulateSymptomsBuild(SimulatePatientType ePatientType);
		/*******************************************************************************/
		// 函数名称： modifyScenario
		// 功能：   修改当前场景状态的生理体征值
		// 参数：   CList<CXActionVirtual *, CXActionVirtual *> lstActions: 
		//          eEventSign eEventValue:  场景转换的事件信号
		//          BOOL bExecActions:       是否执行体征
		//          short sTransferTime:
		// 返回值:  tag_TrendValue: 当前场景所设置的体征值
		virtual void modifyScenarioSet(std::list<CXActionVirtual *> *plstActions, eEventSign eEventValue, bool bExecActions = true, short sTransferTime = 0);
	public: //接口CEventHandleClockIrpOp的函数重载
		/*******************************************************************************/
		//功能：处理时钟事件IRP函数
		//参数：
		//      CVirtualIrp *pCurrIrp：
		//返回值:  后续不再处理（FALSE);
		virtual bool doHandleClockIrpOp(irp::CVirtualIrp *pCurrIrp);
	public: //接口CEventHandleCustomIrpOp的函数重载
		/*******************************************************************************/
		//功能：处理场景事件IRP函数
		//参数：
		//      CVirtualIrp *pCurrIrp：
		//返回值:  后续不再处理（FALSE);
		virtual bool doHandleCustomEventIrpOp(irp::CVirtualIrp *pCurrIrp);
	public: //接口CEventHandleCPRStatIrpOp的函数重载
		/*******************************************************************************/
		//功能：处理CPR操作统计结果IRP函数
		//参数：
		//      CVirtualIrp *pCurrIrp：
		//返回值:  后续不再处理（FALSE);
		virtual bool doHandleCPRStatIrpOp(irp::CVirtualIrp *pCurrIrp);
	public:  //接口CRealTimeDataHandleIrpOp的函数重载
		/*******************************************************************************/
		//功能：处理场景框转移IRP函数
		//参数：
		//      CVirtualIrp *pCurrIrp：
		//返回值:  后续不再处理（FALSE);
		virtual bool doHandleRealTimeDataIrpOp(irp::CVirtualIrp *pCurrIrp);
	public:
		/*******************************************************************************/
		// 函数名称： TransmitSimulatorOrders
		// 功能： 传输模拟人体征通信指令
		// 参数：         
		// 返回值:
		virtual void TransmitSimulatorOrders();
		/*******************************************************************************/
		// 函数名称： ModifiedSymptomsUpdateShow
		// 功能： 被修改的参数更新显示
		// 参数： 
		//        BOOL bClearModifiedFlag:      是否清除修改标识   
		// 返回值:
		virtual void ModifiedSymptomsUpdateShow( bool bClearModifiedFlag );
	public:
		//设置模拟人体征通信指令传输接口
		void set_TransportOrderIrpToSimulatorInterface(transLayer::ITransportOrderIrpToSimulator *pInterface) { m_pTransportOrderInterface  = pInterface; };
	public:
		/*******************************************************************************/
		// 函数名称： StartLinkeSimulateBarShowInterfaces
		// 功能： 初始连接模拟模拟人设置面板的相关显示接口
		// 参数： CSymptomsShowInterfacesAggregate *pShowAggregate:        
		// 返回值:  
		void StartLinkeSimulateBarShowInterfaces(CSymptomsShowInterfacesAggregate *pShowAggregate);
		/*******************************************************************************/
		// 函数名称： UnLinkSimulateBarShowInterfaces
		// 功能： 断开模拟模拟人设置面板的相关显示接口
		// 参数： CSymptomsShowInterfacesAggregate *pShowAggregate:        
		// 返回值:
		void UnLinkSimulateBarShowInterfaces(CSymptomsShowInterfacesAggregate *pShowAggregate);
	protected:
		//搜索对应的体征对象指针
		bool FindSymptomByAction(std::list<CSymptomVirtual *>* /*out*/plstFindSymptoms, CXActionVirtual* /*in*/pVirAction);
		//添加可不被监控的参数的体征
		void AddUnMonitorSymptom(CXActionVirtual *pVirAction);
	private:
		//处理当前场景中的生理体征处理顺序的排列
		void doActionsHandleArrange(std::list<CXActionVirtual *> *plstActions);
		CXActionVirtual * findActionByName(std::list<CXActionVirtual *> *ptrlstActions, const std::string &strActionName);
	public:
		//获取修改的生理体征
		void getsynchronizeSymptoms(std::list<CSymptomVirtual *> /*out*/*plstModifiedSymptoms, bool bInitial);
	public:
		std::string									m_strScriptName;
	private:
		transLayer::ITransportOrderIrpToSimulator*  m_pTransportOrderInterface;
		pnp::CSyncPnpFacilities          m_cSyncPnPFacilities;   
	};
}}
