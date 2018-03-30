#pragma once
#include ".\IGetPhysioloySimulateData.h"

#include "..\common\opinterfacevir.h"
#include "..\common\criticalMutex.h"

namespace jysoft { namespace simulator { namespace base {

	class CShowABPUpdateInterface;
    class SIMULATORBASESHARED_EXPORT COpABPBuildInterface : public COpInterfaceVir
	{
	public:
		COpABPBuildInterface(void);
		virtual ~COpABPBuildInterface(void);
	protected:
		CShowABPUpdateInterface          *m_pShowABPUpdate;
        utility::CCriticalMutex           m_cInterfaceMutex;
	public:
		virtual bool isKindOf(const std::string &className);
	protected:
		/*******************************************************************************/
		// 函数名称： ModifyABPValue
		// 功能： 修改ABP的值
		// 参数：  
		// 返回值:  
		virtual void ModifyABPValue(int nShrinkValue, int nStretchValue) = 0;
	public:
		//修改ABP的值
		void OnModifyABPValue(int nShrinkValue, int nStretchValue);
	public:
		/*******************************************************************************/
		// 函数名称： SetRelateABPShowInterface
		// 功能： 联接ABP显示接口
		// 参数： CShowABPUpdateInterface *pShowInterface:       
		// 返回值:  
		//注： 通过CShowABPUpdateInterface的串联指针，可连接相关的多个ABP显示接口
		void SetRelateABPShowInterface(CShowABPUpdateInterface *pShowInterface);
		//断开指定的ABP显示接口
		void RemoveRelateABPShowInterface(CShowABPUpdateInterface *pRmvShowInterface);
	public:
		/*******************************************************************************/
		// 函数名称： Get_IGetPhysioloySimulateDataPtr
		// 功能： 返回IGetPhysioloySimulateData接口指针
		// 参数： 
		// 返回值: 
		virtual IGetPhysioloySimulateData * Get_IGetPhysioloySimulateDataPtr() = 0;
	};

}}}
