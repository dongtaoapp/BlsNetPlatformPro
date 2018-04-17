#pragma once
#include <boost/thread.hpp>
#include ".\IGetPhysioloySimulateData.h"

#include "..\common\opinterfacevir.h"

namespace jysoft { namespace simulator { namespace base {

	class CShowEtCO2UpdateInterface;
    class SIMULATORBASESHARED_EXPORT COpEtCO2BuildInterface : public COpInterfaceVir
	{
	public:
		COpEtCO2BuildInterface(void);
		virtual ~COpEtCO2BuildInterface(void);
	protected:
		CShowEtCO2UpdateInterface*        m_pShowEtCO2Update;
		boost::mutex                      m_cInterfaceMutex;
	public:
		virtual bool isKindOf(const std::string &className);
	protected:
		//修改CO2%
		virtual void ModifyCO2PercentValue( int nCO2Per ) = 0;
		/*******************************************************************************/
		// 函数名称： OnIntubateOp
		// 功能： 拔/插管事件
		// 参数： 
		//         BOOL bIntubate:
		// 返回值:  
		virtual void IntubateEventOp( bool bIntubate ) = 0;
		/*******************************************************************************/
		// 函数名称： OnOnceBreathEventOp
		// 功能： 一次吹气事件
		// 参数： 
		// 返回值:  
		virtual void OnceBreathEventOp() = 0;
		/*******************************************************************************/
		// 函数名称： OnCPREventOp
		// 功能： 阶段性CPR事件
		// 参数： 
		// 返回值:  
		virtual void CPREventOp( bool bStop ) = 0;
	public:
		//修改CO2%
		void OnModifyCO2PercentValue( int nCO2Per );
		// 拔/插管事件
		void OnIntubateEventOp( bool bIntubate );
		//一次吹气事件
		void OnOnceBreathEventOp();
		//阶段性CPR事件
		void OnCPREventOp( bool bStop );
	public:
		/*******************************************************************************/
		// 函数名称： SetRelateEtCO2ShowInterface
		// 功能： 联接EtCO2显示接口
		// 参数： CShowEtCO2UpdateInterface *pShowInterface:       
		// 返回值:  
		//注： 通过CShowEtCO2UpdateInterface的串联指针，可连接相关的多个EtCO2显示接口
		void SetRelateEtCO2ShowInterface(CShowEtCO2UpdateInterface *pShowInterface);
		//断开指定的EtCO2显示接口
		void RemoveRelateEtCO2ShowInterface(CShowEtCO2UpdateInterface *pRmvShowEtCO2Interface);
	public:
		/*******************************************************************************/
		// 函数名称： Get_IGetPhysioloySimulateDataPtr
		// 功能： 返回IGetPhysioloySimulateData接口指针
		// 参数： 
		// 返回值: 
		virtual IGetPhysioloySimulateData * Get_IGetPhysioloySimulateDataPtr() = 0;
		/*********************************************************************************/
		//功能：初始化模拟CO2构造器
		//参数：
		//      int nCO2Per:             CO2%
		//返回值:  
		virtual void InitializeBuild(int nCO2Per) = 0;
	};

}}}
