#pragma once
#include <string>

#include ".\IPnPFacility.h"

#include "..\common\criticalMutex.h"

namespace jysoft { namespace pnp {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     即插即用设备接口集合，同步操作管理
	创建人：	 hjg
	创建时间：   2013/3/5
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT CSyncPnpFacilities
	{
	public:
		CSyncPnpFacilities(void);
		virtual ~CSyncPnpFacilities(void);
	protected:
        IPnPFacility *     m_pPnPFacilities;
	private:
        utility::CCriticalMutex     m_cPnpMutex;
		//------------------------------------------------------------------------
        int                m_nWeepSpeedParam;   //流泪模式参数
        int                m_nSweatSpeedParam;  //流汗模式参数
	public:
		/*******************************************************************************/
		// 函数名称： SyncAddPnpInstrument
		// 功能：   同步管理添加新的Pnp设备
		// 参数：   
		//      IPnPFacility *pNewPnPFacility: 
		// 返回值: 
		void SyncAddPnpInstrument( IPnPFacility *pNewPnPFacility );
		/*******************************************************************************/
		// 函数名称： SyncRemovePnpInstrument
		// 功能：   同步管理移除Pnp设备
		// 参数：   
		//      IPnPFacility *pRmvPnPFacility: 
		// 返回值: 
        bool SyncRemovePnpInstrument( IPnPFacility  *pRmvPnPFacility );
		/*******************************************************************************/
		// 函数名称： SyncRemovePnpInstrument
		// 功能：   同步管理移除Pnp设备
		// 参数：   
		//      short sPort: 
		// 返回值: 
        bool SyncRemovePnpInstrument( short sPnpID );
		/*******************************************************************************/
		// 函数名称： SyncModifyTransmitAddress
		// 功能：   同步管理修改通讯指令的转发地址
		// 参数：   
		//      /*out*/short &sAddress: 
		// 返回值: 
		void SyncModifyTransmitAddress(/*out*/short &sAddress, const std::string &symptomCaption);
		/*******************************************************************************/
		// 函数名称： RemoveAllPnpInstrument
		// 功能：   清除所有的Pnp设备
		// 参数：   
		//      
		// 返回值: 
		void RemoveAllPnpInstrument();
	public:
		void Set_WaterSpeedParams(int nWeepSpeed, int nSeatSpeed);
		inline int Get_nWeepSpeedParam() { return m_nWeepSpeedParam; };
		inline int Get_nSweatSpeedParam() { return m_nSweatSpeedParam; };
	};

}}
