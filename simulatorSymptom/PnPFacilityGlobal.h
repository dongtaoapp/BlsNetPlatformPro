#pragma once

#include "..\SimulatorBase\IPnPFacility.h"


namespace jysoft { namespace pnp { 
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     即插即用设备血压测量训练仪类
	创建人：	 hjg
	创建时间：   2009/4/30
	//-----------------------------------------------------------------------------------------------------------------*/
	class CSphygmomanometerFacility : public IPnPFacility
	{
	public:
		CSphygmomanometerFacility(short sPnpID, short sPort);		
		virtual ~CSphygmomanometerFacility();
	public:
		/*******************************************************************************/
		// 函数名称： isModifyTransmitAddress
		// 功能：   判断是否修改通讯指令的转发地址
		// 参数：   
		//      const std::string &strSymptomCaption: 
		// 返回值: 
		virtual bool isModifyTransmitAddress( const std::string &symptomCaption );
	};
	
	//--------------------------------------------------------------------------------------------------------------------
	//模拟除颤训练仪: 设备号：0xB0
	class CSimulateDefibrillatorFacility : public IPnPFacility
	{
	public:
		CSimulateDefibrillatorFacility(short sPnpID, short sPort);
		virtual ~CSimulateDefibrillatorFacility();
	public:
		/*******************************************************************************/
		// 函数名称： isModifyTransmitAddress
		// 功能：   判断是否修改通讯指令的转发地址
		// 参数：   
		//      const std::string &strSymptomCaption: 
		// 返回值: 
		virtual bool isModifyTransmitAddress( const std::string &symptomCaption );
	};

	//--------------------------------------------------------------------------------------------------------------------
	//手动自主呼吸模块安装: 设备号：0xD4
	class  CManualRespInstrumentFacility : public IPnPFacility
	{
	public:
		CManualRespInstrumentFacility(short sPnpID, short sPort);
		virtual ~CManualRespInstrumentFacility();
	public:
		/*******************************************************************************/
		// 函数名称： IsModifyTransmitAddress
		// 功能：   判断是否修改通讯指令的转发地址
		// 参数：   
		//      const CString &strSymptomCaption: 
		// 返回值: 
		virtual  bool isModifyTransmitAddress( const std::string &symptomCaption );
	};
}}