#pragma once
#include ".\SyncPnpFacilities.h"
#include ".\IGetPhysioloySimulateData.h"

#include "..\common\opinterfacevir.h"
#include "..\common\criticalMutex.h"
#include "..\Common\ECGParams.h"

namespace jysoft { namespace simulator { namespace base {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     操作心电图数据产生器的接口类
	创建人：	 hjg
	创建时间：   2016/8/5
	//-----------------------------------------------------------------------------------------------------------------*/

	class CShowECGUpdateInterface;
    class SIMULATORBASESHARED_EXPORT COpECGBuildInterface : public COpInterfaceVir
	{
	public:
		COpECGBuildInterface(void);
		virtual ~COpECGBuildInterface(void);
	public:
		virtual bool isKindOf(const std::string &className);
	protected:
		CShowECGUpdateInterface          *m_pShowECGUpdate;
        utility::CCriticalMutex           m_cInterfaceMutex;
	private:
		pnp::CSyncPnpFacilities*          m_pSyncPnPFacilities;
	protected:
		/*******************************************************************************/
		// 函数名称： ModifyECGHandle
		// 功能： 修改心电图
		// 参数： CECGParams *pECGParams:       
		// 返回值:  
		virtual void ModifyECGHandle(CECGParams *pECGParams) = 0;
		/*******************************************************************************/
		// 函数名称： DirectModifyECGHandle
		// 功能： 直接修改心电图
		// 参数： CECGParams *pECGParams
		//注： 对心电图Build初始化构造时也用此函数
		// 返回值:  
		virtual void DirectModifyECGHandle(CECGParams *pECGParams) = 0;
		/*******************************************************************************/
		// 函数名称： ManualBuildExtrasystHandle
		// 功能： 手动生成一个早波
		// 参数：       
		// 返回值:  
		virtual void ManualBuildExtrasystHandle() = 0;
		/*******************************************************************************/
		// 函数名称： ModifyECGInDefibrEventHandle
		// 功能： 因为除颤而修改波形
		// 参数： CECGParams *pECGParams
		// 返回值:  
		virtual void ModifyECGInDefibrEventHandle(CECGParams *pECGParams) = 0;
		/*******************************************************************************/
		// 函数名称： StartPacingHandle
		// 功能： 启动起搏
		// 参数： 
		// 返回值:  
		virtual void StartPacingHandle(short sPaceHR) = 0;
		/*******************************************************************************/
		// 函数名称： ModifyPacingRateHandle
		// 功能： 修改起搏频率
		// 参数： 
		// 返回值:  
		virtual void ModifyPacingRateHandle(long nPaceRate) = 0;
		/*******************************************************************************/
		// 函数名称： StopPacingHandle
		// 功能： 停止起搏
		// 参数： 
		// 返回值: 
		virtual void StopPacingHandle() = 0;
	public:
		/*******************************************************************************/
		// 函数名称： Get_IGetEcgLeadSimulateDataPtr
		// 功能： 返回IGetEcgSimulateData接口指针
		// 参数： 
		// 返回值: 
		virtual IGetEcgSimulateData * Get_IGetEcgLeadSimulateDataPtr() = 0;
		/*******************************************************************************/
		// 函数名称： OnInitializeBuild
		// 功能： 初始化心电图构造器
		// 参数： CECGParams *pECGParams:       
		// 返回值:  
		virtual bool OnInitializeBuild(const CECGParams *ptrParam, SimulatePatientType ePatientType) = 0;
		/*******************************************************************************/
		// 函数名称： OnModifyPnPFacility
		// 功能： 改变热插拔设备
		// 参数： 
		//         CSyncPnpFacilities *pSyncPnPFacilities:
		// 返回值:  
		virtual void OnModifyPnPFacility(pnp::CSyncPnpFacilities *pSyncPnPFacilities);
	public:
		/*******************************************************************************/
		// 函数名称： SetRelateECGShowInterface
		// 功能： 联接心电图显示接口
		// 参数： CShowECGUpdateInterface *pShowECGInterface:       
		// 返回值:  
		//注： 通过CShowECGUpdateInterface的串联指针，可连接相关的多个心电图显示接口
		void SetRelateECGShowInterface(CShowECGUpdateInterface *pShowECGInterface);
		//断开指定的心电图显示接口
		void RemoveRelateECGShowInterface(CShowECGUpdateInterface *pRmvShowECGInterface);
	public:
		//修改心电图
		void OnModifyECGHandle(CECGParams *pECGParams);
		//直接修改心电图
		void OnDirectModifyECGHandle(CECGParams *pECGParams);
		//手动生成一个早波
		void OnManualBuildExtrasystHandle();
		//因为除颤而修改波形
		void OnModifyECGInDefibrEventHandle(CECGParams *pECGParams);
		//启动起搏  
		void OnStartPacingHandle(short sPaceHR);
		//修改起搏频率 
		void OnModifyPacingRateHandle(long nPaceRate);
		//停止起搏
		void OnStopPacingHandle() ;
	protected:
		void ModifyTransmitAddress(/*out*/short &sAddress);
	};

}}}
