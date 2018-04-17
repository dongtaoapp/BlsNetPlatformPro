#pragma once
#include ".\IGetPhysioloySimulateData.h"

#include "..\common\opinterfacevir.h"
#include "..\Common\ECGParams.h"
#include "..\common\CriticalMutex.h"

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
		CShowECGUpdateInterface*          m_pShowECGUpdate;
		utility::CCriticalMutex           m_cInterfaceMutex;
	protected:
		/*******************************************************************************/
		// 函数名称： ModifyECGHandle
		// 功能： 修改心电图
		// 参数： cECGParams:        
		// 返回值:  
		virtual void ModifyECGHandle(const CECGParams &cECGParams) = 0;
		/*******************************************************************************/
		// 函数名称： DirectModifyECGHandle
		// 功能： 直接修改心电图
		// 参数： cECGParams: 
		//注： 对心电图Build初始化构造时也用此函数
		// 返回值:  
		virtual void DirectModifyECGHandle(const CECGParams &cECGParams) = 0;
		/*******************************************************************************/
		// 函数名称： ModifyECGInDefibrEventHandle
		// 功能： 因为除颤而修改波形
		// 参数： cECGParams: 
		// 返回值:  
		virtual void ModifyECGInDefibrEventHandle(const CECGParams *pECGParams) = 0;
	public:
		/*******************************************************************************/
		// 函数名称： getIGetEcgLeadSimulateDataPtr
		// 功能： 返回IGetEcgSimulateData接口指针
		// 参数： 
		// 返回值: 
		virtual IGetEcgSimulateData * getIGetEcgLeadSimulateDataPtr() = 0;
		/*******************************************************************************/
		// 函数名称： OnInitializeBuild
		// 功能： 初始化心电图构造器
		// 参数： CECGParams *pECGParams:       
		// 返回值:  
		virtual bool OnInitializeBuild(const CECGParams &cECGParams) = 0;
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
		void OnModifyECGHandle(const CECGParams &cECGParams);
		//直接修改心电图
		void OnDirectModifyECGHandle(const CECGParams &cECGParams);
		//因为除颤而修改波形
		void OnModifyECGInDefibrEventHandle(const CECGParams *pECGParams);
	};

}}}
