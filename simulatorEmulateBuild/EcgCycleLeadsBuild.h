#pragma once
#include ".\CardiogramConfigHandle.h"

#include "..\SimulatorBase\ICardiogramLeads.h"


namespace jysoft { namespace simulator { namespace ecg {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     不同导联心电图单周期数据构造封装类
	创建人：	 hjg
	创建时间：   2013/5/16
	//-----------------------------------------------------------------------------------------------------------------*/
	class CEcgLeadSamples;
	class CEcgCycleLeadsBuild
	{
	public:
		CEcgCycleLeadsBuild(void);
		virtual ~CEcgCycleLeadsBuild(void);
	public:
		/*******************************************************************************/
		// 函数名称： CreateCycleLeadsData
		// 功能： 构建针对不同导联的单周期数据
		// 参数：  
		//          ICardiogramLeads *pVirCardiogramLeads:         
		//          /*out*/CEcgLeadSamples *pDestLeadSamples:      I12各导联数据（aVR, aVL, aVF由其它心导联推算）
		// 返回值: 
		bool CreateCycleLeadsData(ICardiogramLeads *pVirCardiogramLeads, /*out*/CEcgLeadSamples *pDestLeadSamples);
		/*******************************************************************************/
		// 函数名称： CreateExtrasystData
		// 功能： 构建早搏数据
		// 参数：  
		//         int iCycleTime:                              心律周期时间（单位：0.1ms）
		//         Extrasys eExtrasyst:                         早搏类型
		//         ICardiogramLeads *pVirCardiogramLeads:       
		//         /*in,out*/CEcgLeadSamples *pDestLeadSamples:   
		// 返回值: 
		bool CreateExtrasystData(int iCycleTime, Extrasys eExtrasyst, ICardiogramLeads *pVirCardiogramLeads, /*in,out*/CEcgLeadSamples *pDestLeadSamples);
	protected:
        bool CreateCycleLeadData(CVirCardiogramParam *pVirParam, CCardiogramConfigHandle *pConfigHandle, /*out*/CSample *pDestSample);
		//返回导联构建类（aVR, aVL, aVF等的构造为空）
		CCardiogramConfigHandle * GetCardiogramConfigHandlePtr( RhythmLead eEcgLeadType);
	protected:
		//导联构建类，依次为：I, II, III, V1, V2, V3, V4, V5, V6
		CCardiogramConfigHandle                 m_cCardiogramConfigHandle[9];  
	};
}}}
