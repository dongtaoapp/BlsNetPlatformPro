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

	//��ȡ���ʵ���Ч��Χ
	void CAdultPhysiologyDefaultRange::Get_HRDefaultRanage(/*out*/int *pMinRate, /*out*/int *pMaxRate)
	{
		*pMinRate  = 50;
		*pMaxRate  = 100;
	}

	//��ȡѪ������Чȱʡ��Χ
	void CAdultPhysiologyDefaultRange::Get_SpO2DefaultRange(/*out*/int *pMinSpO2Value, /*out*/int *pMaxSpO2Value)
	{
		*pMinSpO2Value = 90;
		*pMaxSpO2Value = 100;
	}

	//��ȡABP����ѹ����Чȱʡ��Χ
	void CAdultPhysiologyDefaultRange::Get_ABPShrinkValueDefaultRange(/*out*/int *pMinShrinkValue, /*out*/int *pMaxShrinkValue)
	{
		*pMinShrinkValue = 90;
		*pMaxShrinkValue = 160;
	}

	//��ȡ��������Чȱʡ��Χ
	void CAdultPhysiologyDefaultRange::Get_RespRateDefaultRange(/*out*/int *pMinRespRate, /*out*/int *pMaxRespRate)
	{
		*pMinRespRate = 8;
		*pMaxRespRate = 30;
	}

	//��ȡ����ĩ������̼����Чȱʡ��Χ
	void CAdultPhysiologyDefaultRange::Get_etCO2ValueDefaultRange(/*out*/int *pMinEtCO2Value, /*out*/int *pMaxEtCO2Value)
	{
		*pMinEtCO2Value = 25;
		*pMaxEtCO2Value = 65;
	}

	//��ȡ���µ���Чȱʡ��Χ
	void CAdultPhysiologyDefaultRange::Get_TempValueDefaultRange(/*out*/float *pMinTempValue, /*out*/float *pMaxTempValue)
	{
		*pMinTempValue = 35.5f;
		*pMaxTempValue = 38.0f;
	}
	//��ȡ��Χ���µ���Чȱʡ��Χ
	void CAdultPhysiologyDefaultRange::Get_PTempValueDefaultRange(/*out*/float *pMinTempValue, /*out*/float *pMaxTempValue)
	{
		*pMinTempValue = 22.0f;
		*pMaxTempValue = 38.0f;
	}

	//��ȡ����ĩ������̼Ũ�ȵ���Чȱʡ��Χ
	void CAdultPhysiologyDefaultRange::Get_CO2ValueDefaultRange(/*out*/int *pMinCO2Value, /*out*/int *pMaxCO2Value)
	{
		*pMinCO2Value = 6;
		*pMaxCO2Value = 30;
	}

	//��ȡ����Ũ��
	void CAdultPhysiologyDefaultRange::Get_inO2PercentDefaultRange(/*out*/int *pMinInO2Percent, /*out*/int *pMaxInO2Percent)
	{
		*pMinInO2Percent = 10;
		*pMaxInO2Percent = 100;
	}

	//��ȡPAP����Чȱʡ��Χ
	void CAdultPhysiologyDefaultRange::Get_PAPShrinkValueDefaultRange(/*out*/int *pMinShrinkValue, /*out*/int *pMaxShrinkValue)
	{
		*pMinShrinkValue = 20;
		*pMaxShrinkValue = 40;
	}

}}}
