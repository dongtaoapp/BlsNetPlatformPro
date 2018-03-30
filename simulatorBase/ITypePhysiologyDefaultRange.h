#pragma once
#include ".\simulatorbase_global.h"

namespace jysoft { namespace simulator { namespace base {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ��ͬģ�������͵�����������Ч��Χֵ�ӿ�
	�����ˣ�	 hjg
	����ʱ�䣺   2016/8/12
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT ITypePhysiologyDefaultRange
	{
	public:
		ITypePhysiologyDefaultRange(void);
		virtual ~ITypePhysiologyDefaultRange(void);
	public:
		//��ȡ���ʵ���Чȱʡ��Χ
		virtual void Get_HRDefaultRanage(/*out*/int *pMinRate, /*out*/int *pMaxRate) = 0;
		//��ȡѪ������Чȱʡ��Χ
		virtual void Get_SpO2DefaultRange(/*out*/int *pMinSpO2Value, /*out*/int *pMaxSpO2Value) = 0;
		//��ȡABP����ѹ����Чȱʡ��Χ
		virtual void Get_ABPShrinkValueDefaultRange(/*out*/int *pMinShrinkValue, /*out*/int *pMaxShrinkValue) = 0;
		//��ȡ��������Чȱʡ��Χ
		virtual void Get_RespRateDefaultRange(/*out*/int *pMinRespRate, /*out*/int *pMaxRespRate) = 0;
		//��ȡ����ĩ������̼��ѹ����Чȱʡ��Χ
		virtual void Get_etCO2ValueDefaultRange(/*out*/int *pMinEtCO2Value, /*out*/int *pMaxEtCO2Value) = 0;
		//��ȡ���µ���Чȱʡ��Χ
		virtual void Get_TempValueDefaultRange(/*out*/float *pMinTempValue, /*out*/float *pMaxTempValue) = 0;
		//��ȡ��Χ���µ���Чȱʡ��Χ
		virtual void Get_PTempValueDefaultRange(/*out*/float *pMinTempValue, /*out*/float *pMaxTempValue) = 0;
		//��ȡ����ĩ������̼Ũ�ȵ���Чȱʡ��Χ
		virtual void Get_CO2ValueDefaultRange(/*out*/int *pMinCO2Value, /*out*/int *pMaxCO2Value) = 0;
		//��ȡ����Ũ��
		virtual void Get_inO2PercentDefaultRange(/*out*/int *pMinInO2Percent, /*out*/int *pMaxInO2Percent) = 0;
		//��ȡPAP����Чȱʡ��Χ
		virtual void Get_PAPShrinkValueDefaultRange(/*out*/int *pMinShrinkValue, /*out*/int *pMaxShrinkValue) = 0;
	};



	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ����ģ�������͵�����������Ч��Χֵ
	�����ˣ�	 hjg
	����ʱ�䣺   2016/8/12
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORBASESHARED_EXPORT CAdultPhysiologyDefaultRange : public ITypePhysiologyDefaultRange
	{
	public:
		CAdultPhysiologyDefaultRange(void);
		virtual ~CAdultPhysiologyDefaultRange(void);
	public:
		//��ȡ���ʵ���Чȱʡ��Χ
		void Get_HRDefaultRanage(/*out*/int *pMinRate, /*out*/int *pMaxRate);
		//��ȡѪ������Чȱʡ��Χ
		void Get_SpO2DefaultRange(/*out*/int *pMinSpO2Value, /*out*/int *pMaxSpO2Value);
		//��ȡABP����ѹ����Чȱʡ��Χ
		void Get_ABPShrinkValueDefaultRange(/*out*/int *pMinShrinkValue, /*out*/int *pMaxShrinkValue);
		//��ȡ��������Чȱʡ��Χ
		void Get_RespRateDefaultRange(/*out*/int *pMinRespRate, /*out*/int *pMaxRespRate);
		//��ȡ����ĩ������̼����Чȱʡ��Χ
		void Get_etCO2ValueDefaultRange(/*out*/int *pMinEtCO2Value, /*out*/int *pMaxEtCO2Value);
		//��ȡ���µ���Чȱʡ��Χ
		void Get_TempValueDefaultRange(/*out*/float *pMinTempValue, /*out*/float *pMaxTempValue);
		//��ȡ��Χ���µ���Чȱʡ��Χ
		void Get_PTempValueDefaultRange(/*out*/float *pMinTempValue, /*out*/float *pMaxTempValue);
		//��ȡ����ĩ������̼Ũ�ȵ���Чȱʡ��Χ
		void Get_CO2ValueDefaultRange(/*out*/int *pMinCO2Value, /*out*/int *pMaxCO2Value);
		//��ȡ����Ũ��
		void Get_inO2PercentDefaultRange(/*out*/int *pMinInO2Percent, /*out*/int *pMaxInO2Percent);
		//��ȡPAP����Чȱʡ��Χ
		virtual void Get_PAPShrinkValueDefaultRange(/*out*/int *pMinShrinkValue, /*out*/int *pMaxShrinkValue);
	};

}}}
