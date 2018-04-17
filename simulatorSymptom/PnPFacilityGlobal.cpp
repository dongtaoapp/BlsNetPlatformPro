#include ".\pnpfacilityglobal.h"

#include "..\ElementParse\SAction_ABP.h"
#include "..\ElementParse\SAction_ECG.h"
#include "..\ElementParse\SAction_Pace.h"
#include "..\ElementParse\SAction_Resp.h"


namespace jysoft { namespace pnp 
{
	//-----------------------------------------------------------------------------------------------
	//class CSphygmomanometerFacility
	CSphygmomanometerFacility::CSphygmomanometerFacility(short sPnpID, short sPort)
							 : IPnPFacility( sPnpID, sPort )
	{

	}

	CSphygmomanometerFacility::~CSphygmomanometerFacility()
	{

	}

	/*******************************************************************************/
	// 函数名称： IsModifyTransmitAddress
	// 功能：   判断是否修改通讯指令的转发地址
	// 参数：   
	//      const std::string &strSymptomCaption: 
	// 返回值: 
	bool CSphygmomanometerFacility::isModifyTransmitAddress( const std::string &symptomCaption )
	{
		bool   bModifyAddress = false;
		if( symptomCaption == CSAction_ABP::getAction_BP_Caption() )
		{
			bModifyAddress  = false;
		}
		else if( symptomCaption == CSAction_ECG::getAction_ECG_Caption() )
		{
			bModifyAddress  = false;
		}
		return bModifyAddress;
	}

	//-----------------------------------------------------------------------------------------------
	//class CSimulateDefibrillatorFacility
	CSimulateDefibrillatorFacility::CSimulateDefibrillatorFacility(short sPnpID, short sPort)
								  : IPnPFacility( sPnpID, sPort )
	{

	}

	CSimulateDefibrillatorFacility::~CSimulateDefibrillatorFacility()
	{

	}

	/*******************************************************************************/
	// 函数名称： IsModifyTransmitAddress
	// 功能：   判断是否修改通讯指令的转发地址
	// 参数：   
	//      const std::string &strSymptomCaption: 
	// 返回值: 
	bool CSimulateDefibrillatorFacility::isModifyTransmitAddress( const std::string &symptomCaption )
	{
		bool   bModifyAddress = false;
		if( symptomCaption == CSAction_ECG::getAction_ECG_Caption() )
		{
			bModifyAddress  = true;
		}
		else if( symptomCaption == "Cardiogram_RealTimeData" )
		{
			bModifyAddress  = true;
		}
		else if( symptomCaption == CSAction_Pace::getAction_Pace_Caption() )
		{
			bModifyAddress  = true;
		}
		return bModifyAddress;
	}

	//--------------------------------------------------------------------------------------------------
	//class CManualRespInstrumentFacility
	CManualRespInstrumentFacility::CManualRespInstrumentFacility(short sPnpID, short sPort) : IPnPFacility( sPnpID, sPort )
	{

	}

	CManualRespInstrumentFacility::~CManualRespInstrumentFacility()
	{

	}

	/*******************************************************************************/
	// 函数名称： isModifyTransmitAddress
	// 功能：   判断是否修改通讯指令的转发地址
	// 参数：   
	//      const std::string &symptomCaption: 
	// 返回值: 
	bool CManualRespInstrumentFacility::isModifyTransmitAddress( const std::string &symptomCaption )
	{
		if( symptomCaption == CSAction_Resp::getAction_Resp_Caption() )
		{
			return true;
		}
		return false;
	}
}}
