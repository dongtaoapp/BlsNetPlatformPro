#pragma once
#include ".\simulatorbase_global.h"

namespace jysoft { namespace simulator { namespace base {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     不同模拟人类型的生理体征有效范围值接口
	创建人：	 hjg
	创建时间：   2016/8/12
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT ITypePhysiologyDefaultRange
	{
	public:
		ITypePhysiologyDefaultRange(void);
		virtual ~ITypePhysiologyDefaultRange(void);
	public:
		//获取心率的有效缺省范围
		virtual void Get_HRDefaultRanage(/*out*/int *pMinRate, /*out*/int *pMaxRate) = 0;
		//获取血氧的有效缺省范围
		virtual void Get_SpO2DefaultRange(/*out*/int *pMinSpO2Value, /*out*/int *pMaxSpO2Value) = 0;
		//获取ABP收缩压得有效缺省范围
		virtual void Get_ABPShrinkValueDefaultRange(/*out*/int *pMinShrinkValue, /*out*/int *pMaxShrinkValue) = 0;
		//获取呼吸的有效缺省范围
		virtual void Get_RespRateDefaultRange(/*out*/int *pMinRespRate, /*out*/int *pMaxRespRate) = 0;
		//获取呼出末二氧化碳分压的有效缺省范围
		virtual void Get_etCO2ValueDefaultRange(/*out*/int *pMinEtCO2Value, /*out*/int *pMaxEtCO2Value) = 0;
		//获取体温的有效缺省范围
		virtual void Get_TempValueDefaultRange(/*out*/float *pMinTempValue, /*out*/float *pMaxTempValue) = 0;
		//获取外围体温的有效缺省范围
		virtual void Get_PTempValueDefaultRange(/*out*/float *pMinTempValue, /*out*/float *pMaxTempValue) = 0;
		//获取呼出末二氧化碳浓度的有效缺省范围
		virtual void Get_CO2ValueDefaultRange(/*out*/int *pMinCO2Value, /*out*/int *pMaxCO2Value) = 0;
		//获取吸氧浓度
		virtual void Get_inO2PercentDefaultRange(/*out*/int *pMinInO2Percent, /*out*/int *pMaxInO2Percent) = 0;
		//获取PAP的有效缺省范围
		virtual void Get_PAPShrinkValueDefaultRange(/*out*/int *pMinShrinkValue, /*out*/int *pMaxShrinkValue) = 0;
	};



	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     成人模拟人类型的生理体征有效范围值
	创建人：	 hjg
	创建时间：   2016/8/12
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORBASESHARED_EXPORT CAdultPhysiologyDefaultRange : public ITypePhysiologyDefaultRange
	{
	public:
		CAdultPhysiologyDefaultRange(void);
		virtual ~CAdultPhysiologyDefaultRange(void);
	public:
		//获取心率的有效缺省范围
		void Get_HRDefaultRanage(/*out*/int *pMinRate, /*out*/int *pMaxRate);
		//获取血氧的有效缺省范围
		void Get_SpO2DefaultRange(/*out*/int *pMinSpO2Value, /*out*/int *pMaxSpO2Value);
		//获取ABP收缩压得有效缺省范围
		void Get_ABPShrinkValueDefaultRange(/*out*/int *pMinShrinkValue, /*out*/int *pMaxShrinkValue);
		//获取呼吸的有效缺省范围
		void Get_RespRateDefaultRange(/*out*/int *pMinRespRate, /*out*/int *pMaxRespRate);
		//获取呼吸末二氧化碳的有效缺省范围
		void Get_etCO2ValueDefaultRange(/*out*/int *pMinEtCO2Value, /*out*/int *pMaxEtCO2Value);
		//获取体温的有效缺省范围
		void Get_TempValueDefaultRange(/*out*/float *pMinTempValue, /*out*/float *pMaxTempValue);
		//获取外围体温的有效缺省范围
		void Get_PTempValueDefaultRange(/*out*/float *pMinTempValue, /*out*/float *pMaxTempValue);
		//获取呼出末二氧化碳浓度的有效缺省范围
		void Get_CO2ValueDefaultRange(/*out*/int *pMinCO2Value, /*out*/int *pMaxCO2Value);
		//获取吸氧浓度
		void Get_inO2PercentDefaultRange(/*out*/int *pMinInO2Percent, /*out*/int *pMaxInO2Percent);
		//获取PAP的有效缺省范围
		virtual void Get_PAPShrinkValueDefaultRange(/*out*/int *pMinShrinkValue, /*out*/int *pMaxShrinkValue);
	};

}}}
