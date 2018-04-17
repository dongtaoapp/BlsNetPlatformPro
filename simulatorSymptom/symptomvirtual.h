#pragma once
#include ".\XActionVirtual.h"

#include "..\Common\CommonGlobal.h"

#include "..\simulatorBase\ITransportOrderIrpToSimulator.h"
#include "..\simulatorBase\SyncPnpFacilities.h"
#include "..\simulatorBase\WatchBarsShowInterfacesAggregate.h"
#include "..\simulatorBase\SymptomsShowInterfacesAggregate.h"


namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     模拟人生理体征参数基类，描述某一体征当前的状态数据
	创建人：	 hjg
	创建时间：   2008/10/17
	//-----------------------------------------------------------------------------------------------------------------*/

	class IModifiedSymptomsOp;
    class SIMULATORSYMPTOMSHARED_EXPORT CSymptomVirtual
	{
	public:
		CSymptomVirtual(void);
		virtual ~CSymptomVirtual(void);
	public:
		IModifiedSymptomsOp     *m_pModifiedSymptomsOp;
	public: 
		/*******************************************************************************/
		// 函数名称： IsKindOf
		// 功能：   判断体征的类别
		// 参数：   const CString &strClassName
		// 返回值: 
		virtual  bool isKindOf( const std::string &strClassName ) = 0;
		//根据标示名称判断体征参数
		virtual  bool isSymptomCaption(const std::string &strCaption) = 0;
		/*******************************************************************************/
		// 函数名称： InitialSymptomValue
		// 功能：   初始化体征值
		// 参数：   IModifiedSymptomsOp *pInterfacePtr
		// 返回值: 
		virtual  void InitialSymptomValue(IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType) = 0;
		/*******************************************************************************/
		// 函数名称： InitialSymptomValue
		// 功能：   初始化体征值
		// 参数：   
		//          tag_TrendValue *pDefaultTrendValue:  相应体征修改的值返回
		//          CXActionVirtual *pVirAction:         对应体征值
		//          short sTransTime:                    转换时间（单位：秒）
		// 返回值: 
		virtual  void InitialSymptomValue(CXActionVirtual *pVirAction, short sTransTime = 0) = 0;
		/*******************************************************************************/
		// 函数名称： isTransmitAEDState
		// 功能：   是否AED状态改变
		// 参数：   
		//          /*in,out*/unsigned char *sAEDState:        AED状态
		// 返回值: 
		virtual  bool isTransmitAEDState(/*in,out*/unsigned char *sAEDState) { return false; };
		/*******************************************************************************/
		// 函数名称： DoTransmitOrder
		// 功能：   模拟人体征命令传输
		// 参数：   
		//          CSyncPnpFacilities *pPnPFacilities:        自插拔设备集
		//          /*in,out*/unsigned char *sAEDState:        AED状态
		//          ITransportOrderIrpToSimulator *pInterface: 命令传输接口
		// 返回值: 
		virtual  void DoTransmitOrder(pnp::CSyncPnpFacilities *pPnPFacilities,  transLayer::ITransportOrderIrpToSimulator *pInterface) { };
		/*******************************************************************************/
		// 函数名称： OnUpdateInterfaceShow
		// 功能：   更新界面显示
		// 参数：   
		// 返回值: 
		virtual  void OnUpdateInterfaceShow() { };
		/*******************************************************************************/
		// 函数名称： OnLinkWatchBarUpdateInterfaceShow
		// 功能：   连接模拟监控显示连接
		// 参数：   
		// 返回值:
		virtual  void OnLinkWatchBarUpdateInterfaceShow(CWatchBarsShowInterfacesAggregate *pShowAggregate) { };
		/*******************************************************************************/
		// 函数名称： OnUnLinkWatchBarUpdateInterfaceShow
		// 功能：   断开模拟监控显示连接
		// 参数：   
		// 返回值:
		virtual  void OnUnLinkWatchBarUpdateInterfaceShow(CWatchBarsShowInterfacesAggregate *pShowAggregate) { };
		/*******************************************************************************/
		// 函数名称： OnLinkSimulatorBarUpdateInterfaceShow
		// 功能：   断开模拟人面板显示连接
		// 参数：   
		// 返回值:
		virtual  void OnLinkSimulatorBarUpdateInterfaceShow(CSymptomsShowInterfacesAggregate *pShowAggregate ) { };
		/*******************************************************************************/
		// 函数名称： OnUnLinkSimulatorBarUpdateInterfaceShow
		// 功能：   断开模拟人面板显示连接
		// 参数：   
		// 返回值:
		virtual  void OnUnLinkSimulatorBarUpdateInterfaceShow(CSymptomsShowInterfacesAggregate *pShowAggregate ){ };
		/*******************************************************************************/
		// 函数名称： ResetFlag
		// 功能：   重置修改的标识
		// 参数：   
		// 返回值:
		virtual  void ResetFlag() { };
	};
}}
