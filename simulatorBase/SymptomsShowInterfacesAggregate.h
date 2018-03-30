#pragma once
#include ".\ShowECGUpdateInterface.h"
#include ".\ShowNIBPUpdateInterface.h"
#include ".\ShowPaceUpdateInterface.h"
#include ".\ShowRespRateUpdateInterface.h"


namespace jysoft { namespace simulator {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：    模拟人体征状态控件显示接口集合（气道以及心肺肠音）
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORBASESHARED_EXPORT CSymptomsShowInterfacesAggregate
	{
	public:
		CSymptomsShowInterfacesAggregate(void);
		virtual ~CSymptomsShowInterfacesAggregate(void);
	protected:
		//心电图显示接口
		base::CShowECGUpdateInterface               *m_pShowECGInterface;
		//EMD显示接口
		base::CShowECGUpdateInterface               *m_pShowEMDInterface;
		//血压显示接口
		base::CShowNIBPUpdateInterface              *m_pShowNIBPInterface;
		//呼吸模式显示接口
		base::CShowRespRateUpdateInterface          *m_pShowRespInterface;
		//起搏设置显示接口
		base::CShowPaceUpdateInterface              *m_pShowPaceInterface;
	public:
		//断开模拟人体征状态控件显示接口集合
		virtual void OnCutSymptomShowInterfacesAggregate() = 0;
	public:
		//设置心电图显示接口
		void Set_ShowECGUpdateInterfacePtr(base::CShowECGUpdateInterface *pShowECGInterface);
		//设置EMD显示接口
		void Set_ShowEMDUpdateInterfacePtr(base::CShowECGUpdateInterface *pShowEMDInterface);
		//呼吸模式显示接口
		void Set_ShowRespUpdateInterfacePtr(base::CShowRespRateUpdateInterface *pShowRespInterface);
		//血压显示接口
		void Set_ShowNIBPUpdateInterfacePtr(base::CShowNIBPUpdateInterface *pShowNIBPUpdateInterface);
		//
		void Set_ShowPaceUpdateInterfacePtr(base::CShowPaceUpdateInterface *pShowPaceInterface);
	public:
		//返回心电图显示接口
		inline base::CShowECGUpdateInterface * Get_ShowECGUpdateInterfacePtr() { return m_pShowECGInterface; };
		//返回EMD显示接口
		inline base::CShowECGUpdateInterface * Get_ShowEMDUpdateInterfacePtr() { return m_pShowEMDInterface; };
		//返回血压显示接口
		inline base::CShowNIBPUpdateInterface * Get_ShowNIBPUpdateInterfacePtr() { return m_pShowNIBPInterface; };
		//返回呼吸模式显示接口
		inline base::CShowRespRateUpdateInterface * Get_ShowRespUpdateInterfacePtr() { return m_pShowRespInterface; };
		//返回起搏设置显示接口
		inline base::CShowPaceUpdateInterface * Get_ShowPaceUpdateInterfacePtr() { return m_pShowPaceInterface; };
	protected:
		/*******************************************************************************/
		// 函数名称： InitialSimulatorSymptomShowInterfacesAggregate
		// 功能： 获取模拟人体征状态控件内所有的信息显示接口
		// 注：参数为NULL，表示清除所有信息显示接口
		// 返回值:  
		virtual void InitialSimulatorSymptomShowInterfacesAggregate( ) = 0;
	};
}}

