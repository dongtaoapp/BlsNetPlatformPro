#pragma once
#include ".\SyncPnpFacilities.h"
#include ".\IGetPhysioloySimulateData.h"
#include ".\ShowRespRateUpdateInterface.h"

#include "..\common\criticalMutex.h"
#include "..\common\opinterfacevir.h"
#include "..\Common\CommonGlobal.h"


namespace jysoft { namespace simulator { namespace base {

    class SIMULATORBASESHARED_EXPORT COpRespBuildInterface : public COpInterfaceVir
	{
	public:
		COpRespBuildInterface(void);
		virtual ~COpRespBuildInterface(void);
	protected:
		CShowRespRateUpdateInterface          *m_pShowRespUpdate;
        utility::CCriticalMutex                m_cInterfaceMutex;
	private:
		pnp::CSyncPnpFacilities *                   m_pSyncPnPFacilities;
	public:
		virtual bool isKindOf(const std::string &className);
	protected:
		/*******************************************************************************/
		// 函数名称： ModifyRespRate
		// 功能： 修改呼吸次数
		// 参数：  int nBreathRate:            呼吸次数（单位：次/分钟）
		// 返回值:  
		virtual void ModifyRespRate(int nBreathRate) = 0;
		/*******************************************************************************/
		// 函数名称： ModifyRespBuildType
		// 功能： 修改类型及次数
		// 参数：  eRespMode eMode:            呼吸类型
		//         int nBreathRate:                       呼吸次数（单位：次/分钟）
		// 返回值:  
		virtual void ModifyRespBuildType(eRespMode eMode, int nBreathRate) = 0;
	public:
		/*******************************************************************************/
		// 函数名称： OnModifyRespRate
		// 功能： 修改呼吸次数
		// 参数：  int nBreathRate:            呼吸次数（单位：次/分钟）
		// 返回值:  
		void OnModifyRespRate(int nBreathRate);
		/*******************************************************************************/
		// 函数名称： OnModifyRespBuildType
		// 功能： 修改类型及次数
		// 参数：  eRespMode eMode:            呼吸类型
		//         int nBreathRate:                       呼吸次数（单位：次/分钟）
		// 返回值:  
		void OnModifyRespBuildType(eRespMode eMode, int nBreathRate);
		/*******************************************************************************/
		// 函数名称： OnModifyPnPFacility
		// 功能： 改变热插拔设备
		// 参数： 
		//         CSyncPnpFacilities *pSyncPnPFacilities:
		// 返回值:  
		virtual void OnModifyPnPFacility(pnp::CSyncPnpFacilities *pSyncPnPFacilities);
	public:
		/*******************************************************************************/
		// 函数名称： Get_IGetPhysioloySimulateDataPtr
		// 功能： 返回IGetRespSimulateData接口指针
		// 参数： 
		// 返回值: 
		virtual IGetRespSimulateData * Get_IGetPhysioloySimulateDataPtr() = 0;
		/*********************************************************************************/
		//功能：初始化模拟呼吸构造器
		//参数：eRespMode eMode:  模式类型
		//      int nBreathRate:             呼吸次数
		//返回值:  
		virtual void InitializeBuild(eRespMode eMode, int nBreathRate) = 0;
	public:
		/*******************************************************************************/
		// 函数名称： SetRelateRespRateShowInterface
		// 功能： 联接呼吸次数显示接口
		// 参数： CShowRespRateUpdateInterface *pShowInterface:       
		// 返回值:  
		//注： 通过CShowRespRateUpdateInterface的串联指针，可连接相关的多个呼吸次数显示接口
		void SetRelateRespRateShowInterface(CShowRespRateUpdateInterface *pShowInterface);
		//断开指定的呼吸次数显示接口
		void RemoveRelateRespRateShowInterface(CShowRespRateUpdateInterface *pRmvShowInterface);
	protected:
		void ModifyTransmitAddress(/*out*/short &sAddress);
	};

}}}
