#include ".\itypephysiologydefaultrange.h"

namespace jysoft { namespace simulator { namespace base {

	ITypePhysiologyDefaultRange::ITypePhysiologyDefaultRange(void)
	{
	}

	ITypePhysiologyDefaultRange::~ITypePhysiologyDefaultRange(void)
	{
	}


	//-----------------------------------------------------------------------------------------------------------------------
	//class CAdultPhysiologyDefaultRange
	CAdultPhysiologyDefaultRange::CAdultPhysiologyDefaultRange(void)
	{

	}

	CAdultPhysiologyDefaultRange::~CAdultPhysiologyDefaultRange(void)
	{

	}

	//获取心率的有效范围
	void CAdultPhysiologyDefaultRange::Get_HRDefaultRanage(/*out*/int *pMinRate, /*out*/int *pMaxRate)
	{
		*pMinRate  = 50;
		*pMaxRate  = 100;
	}

	//获取血氧的有效缺省范围
	void CAdultPhysiologyDefaultRange::Get_SpO2DefaultRange(/*out*/int *pMinSpO2Value, /*out*/int *pMaxSpO2Value)
	{
		*pMinSpO2Value = 90;
		*pMaxSpO2Value = 100;
	}

	//获取ABP收缩压得有效缺省范围
	void CAdultPhysiologyDefaultRange::Get_ABPShrinkValueDefaultRange(/*out*/int *pMinShrinkValue, /*out*/int *pMaxShrinkValue)
	{
		*pMinShrinkValue = 90;
		*pMaxShrinkValue = 160;
	}

	//获取呼吸的有效缺省范围
	void CAdultPhysiologyDefaultRange::Get_RespRateDefaultRange(/*out*/int *pMinRespRate, /*out*/int *pMaxRespRate)
	{
		*pMinRespRate = 8;
		*pMaxRespRate = 30;
	}

	//获取呼吸末二氧化碳的有效缺省范围
	void CAdultPhysiologyDefaultRange::Get_etCO2ValueDefaultRange(/*out*/int *pMinEtCO2Value, /*out*/int *pMaxEtCO2Value)
	{
		*pMinEtCO2Value = 25;
		*pMaxEtCO2Value = 65;
	}

	//获取体温的有效缺省范围
	void CAdultPhysiologyDefaultRange::Get_TempValueDefaultRange(/*out*/float *pMinTempValue, /*out*/float *pMaxTempValue)
	{
		*pMinTempValue = 35.5f;
		*pMaxTempValue = 38.0f;
	}
	//获取外围体温的有效缺省范围
	void CAdultPhysiologyDefaultRange::Get_PTempValueDefaultRange(/*out*/float *pMinTempValue, /*out*/float *pMaxTempValue)
	{
		*pMinTempValue = 22.0f;
		*pMaxTempValue = 38.0f;
	}

	//获取呼出末二氧化碳浓度的有效缺省范围
	void CAdultPhysiologyDefaultRange::Get_CO2ValueDefaultRange(/*out*/int *pMinCO2Value, /*out*/int *pMaxCO2Value)
	{
		*pMinCO2Value = 6;
		*pMaxCO2Value = 30;
	}

	//获取吸氧浓度
	void CAdultPhysiologyDefaultRange::Get_inO2PercentDefaultRange(/*out*/int *pMinInO2Percent, /*out*/int *pMaxInO2Percent)
	{
		*pMinInO2Percent = 10;
		*pMaxInO2Percent = 100;
	}

	//获取PAP的有效缺省范围
	void CAdultPhysiologyDefaultRange::Get_PAPShrinkValueDefaultRange(/*out*/int *pMinShrinkValue, /*out*/int *pMaxShrinkValue)
	{
		*pMinShrinkValue = 20;
		*pMaxShrinkValue = 40;
	}

}}}
