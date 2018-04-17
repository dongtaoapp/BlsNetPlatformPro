#pragma once
#include <boost/thread.hpp>
#include ".\IGetPhysioloySimulateData.h"

#include "..\common\opinterfacevir.h"

namespace jysoft { namespace simulator { namespace base {

	class CShowSpO2UpdateInterface;
    class SIMULATORBASESHARED_EXPORT COpSpO2BuildInterface : public COpInterfaceVir
	{
	public:
		COpSpO2BuildInterface(void);
		virtual ~COpSpO2BuildInterface(void);
	protected:
		CShowSpO2UpdateInterface          *m_pShowSpO2Update;
		boost::mutex                      m_cInterfaceMutex;
	public:
		virtual bool isKindOf(const std::string &className);
	protected:
		/*******************************************************************************/
		// 函数名称： ModifySpO2ValuePrecent
		// 功能： 修改血氧的百分比浓度
		// 参数：  int nSpO2Value:            血氧百分比浓度值
		// 返回值:  
		virtual void ModifySpO2ValuePrecent( int nSpO2Value ) = 0;
	public:
		//修改血氧的百分比浓度
		void OnModifySpO2ValuePrecent( int nSpO2Value );
	public:
		/*******************************************************************************/
		// 函数名称： SetRelateSpO2ShowInterface
		// 功能： 联接SpO2显示接口
		// 参数： CShowSpO2UpdateInterface *pShowInterface:       
		// 返回值:  
		//注： 通过CShowSpO2UpdateInterface的串联指针，可连接相关的多个SpO2显示接口
		void SetRelateSpO2ShowInterface(CShowSpO2UpdateInterface *pShowInterface);
		//断开指定的SpO2显示接口
		void RemoveRelateSpO2ShowInterface(CShowSpO2UpdateInterface *pRmvShowInterface);
	public:
		/*******************************************************************************/
		// 函数名称： Get_IGetPhysioloySimulateDataPtr
		// 功能： 返回IGetPhysioloySimulateData接口指针
		// 参数： 
		// 返回值: 
		virtual IGetPhysioloySimulateData * Get_IGetPhysioloySimulateDataPtr() = 0;
	};

}}}
