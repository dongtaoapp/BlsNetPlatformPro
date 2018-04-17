#pragma once
#include ".\RespCycleDataCollects.h"
#include ".\simulatoremulatebuild_global.h"

#include "..\SimulatorBase\IGetPhysioloySimulateData.h"
#include "..\SimulatorBase\ITransportOrderIrpToSimulator.h"
#include "..\SimulatorBase\OpRespBuildInterface.h"
#include "..\SimulatorBase\ICO2SimulateSign.h"
#include "..\SimulatorBase\ShowRespRateUpdateInterface.h"

#include "..\Common\CommonGlobal.h"



namespace jysoft { namespace simulator { namespace resp {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     呼吸模拟实时数据生成类
	创建人：	 hjg
	创建时间：   2017/2/22
	//-----------------------------------------------------------------------------------------------------------------*/
	class CRespCycleData;
	class IRespBuildTypeState;
    class SIMULATOREMULATEBUILDSHARED_EXPORT CRespSimulateBuild : public IGetRespSimulateData
											,public base::COpRespBuildInterface
	{
	public:
		CRespSimulateBuild();
		virtual ~CRespSimulateBuild(void);
	private:
		SimulatePatientType             m_ePatientType;
	protected:
		IRespBuildTypeState            *m_pRespBuildState;
		CRespCycleData                 *m_pCurrentRespData[2];
		CRespCycleDataCollects          m_cRespDeletedCollects; //数据包垃圾收集器
	protected:
		int                             m_nRespRate;            //当前的呼吸次数
		int                             m_nRemainTime;          //单位: 0.1ms
		ICO2SimulateSign               *m_pCO2SimulateSignInterface;
		transLayer::ITransportOrderIrpToSimulator  *m_pTransportOrderToSimulatorInterface; 
		std::string          respResourcePath;
	private:
		bool                            m_bClearWatchLink;  //是否忽略RR链接检查
		bool                            m_bLinkWatchResp;
		int                            m_bSynchronizeSignSend;  //同步信号是否已发送
	public:
		//根据RR链接状态，返回是否显示Resp数据
		bool IsShowRespLinkState();
		//设置是否忽略RR链接检查
		void Set_IsClearRespWatchLink(bool bClear);
		//设置RR链接检查状态
		void Set_RespWatchLinkState(bool bLinking);
	public: //IGetPhysioloySimulateData接口基类函数重载
		/*******************************************************************************/
		//功能：获取滑块区域内的曲线数据
		//参数：int iMilliTime:          时间（0.1豪秒）
		//      float *pcBuffer:         返回的曲线数据
		//返回值:  曲线数据的长度
		virtual unsigned long GetRespSimulateData(int iMilliTime, /*out*/float *pcLeftBuffer = NULL, /*out*/float *pcRightBuffer = NULL);
	protected://COpRespBuildInterface接口基类函数重载
		/*******************************************************************************/
		// 函数名称： ModifyRespRate
		// 功能： 修改呼吸次数
		// 参数：  int nBreathRate:            呼吸次数（单位：次/分钟）
		// 返回值:  
		virtual void ModifyRespRate(int nBreathRate);
		/*******************************************************************************/
		// 函数名称： ModifyRespBuildType
		// 功能： 修改类型及次数
		// 参数：  eRespMode eMode:            呼吸类型
		//         int nBreathRate:                       呼吸次数（单位：次/分钟）
		// 返回值:  
		virtual void ModifyRespBuildType(eRespMode eMode, int nBreathRate);
	public:
		/*******************************************************************************/
		// 函数名称： Get_IGetPhysioloySimulateDataPtr
		// 功能： 返回IGetRespSimulateData接口指针
		// 参数： 
		// 返回值: 
		virtual IGetRespSimulateData * Get_IGetPhysioloySimulateDataPtr() { return dynamic_cast<IGetRespSimulateData *>(this); };
	public:
		/*********************************************************************************/
		//功能：初始化模拟呼吸构造器
		//参数：eRespMode eMode:             模式类型
		//      int nBreathRate:             呼吸次数
		//返回值:  
		virtual void InitializeBuild(eRespMode eMode, int nBreathRate);
		/*******************************************************************************/
		// 函数名称： OnModifyPnPFacility
		// 功能： 改变热插拔设备
		// 参数： 
		//         CSyncPnpFacilities *pSyncPnPFacilities:
		// 返回值:  
		virtual void OnModifyPnPFacility(pnp::CSyncPnpFacilities *pSyncPnPFacilities);
		/*******************************************************************************/
		// 函数名称： SetRespBuildRelateInterfacesPtr
		// 功能： 设置呼吸构造相关指针
		// 参数： 
		//        ICO2SimulateSign *pInterface:
		//        ITransportOrderIrpToSimulator *pTransportInterface:  
		//        SimulatePatientType ePateintType:    模拟人类别
		// 返回值: 
		void SetRespBuildRelateInterfacesPtr(ICO2SimulateSign *pInterface, const std::string &resPath, transLayer::ITransportOrderIrpToSimulator *pTransportInterface = NULL, SimulatePatientType eType = SPT_Adult);
		/*********************************************************************************/
		//功能：组织下周期的呼吸数据
		//参数：
		//返回值:  
		void CombineNextCycleSimulateData();
		//关闭呼吸构造器
		void CloseRespSimulateBuild();
	protected:
		/*********************************************************************************/
		//功能： 修改影响呼吸的行为
		//参数：
		//返回值:  
		void ModifyInfluentRespBehaviors();
	};
}}}
