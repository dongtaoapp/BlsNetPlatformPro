#pragma once
#include ".\simulatorbase_global.h"

#include "..\Common\CommonGlobal.h"
#include "..\Common\IBedirecteLinksVir.h"

namespace jysoft { namespace simulator {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     分发实时采样数据接口
	创建人：	 hjg
	创建时间：   2008/7/16
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT IDistributeSimulateData  : public IBedirecteLinksVir
	{
	public:
		IDistributeSimulateData(void);
		virtual ~IDistributeSimulateData(void);
	public:
		//分发实时采样数据
		void OnDistributeSimulateData(float *lptrData, unsigned long  dwNumber);
		//启动
		void OnStartDistributeSimulateData();
	public:
		virtual bool isKindOf(const std::string &className);
	public:
		virtual bool isKindOfDistribute(const std::string &className);
	protected:
		virtual void DistributeSimulateData(float *lptrData, unsigned long  dwNumber) = 0;
		virtual void StartDistributeSimulateData() = 0;
	};

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     分发实时心电导联采样数据接口
	创建人：	 hjg
	创建时间：   2013/5/22
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORBASESHARED_EXPORT IDistributeEcgLeadsSimulateData : public IDistributeSimulateData
	{
	public:
		IDistributeEcgLeadsSimulateData();
		virtual ~IDistributeEcgLeadsSimulateData();
	public:
		virtual bool isKindOfDistribute(const std::string &className);
	public:
		//分发实时采样数据
		void OnDistributeEcgLeadsSimulateData(I12LeadSample *pEcgLeadSamples, unsigned long  dwNumber);
	protected:
		virtual void DistributeSimulateData(float *lptrData, unsigned long  dwNumber);
	protected:
		virtual void DistributeEcgLeadsSimulateData(I12LeadSample *pEcgLeadSamples, unsigned long  dwNumber) = 0;
	};

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     分发实时呼吸采样数据接口
	创建人：	 hjg
	创建时间：   2008/8/16
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORBASESHARED_EXPORT IDistributeRespSimulateData : public IDistributeSimulateData
	{
	public:
		IDistributeRespSimulateData();
		virtual ~IDistributeRespSimulateData();
	public:
		virtual bool isKindOfDistribute(const std::string &className);
		//分发实时采样数据
		void OnDistributeSimulateData(float *lptrSumLungData,float *lptrLeftLungData, unsigned long  dwNumber);
	protected:
		virtual void DistributeSimulateData(float *lptrData, unsigned long  dwNumber);
	protected:
		virtual void DistributeSimulateData(float *lptrSumLungData,float *lptrLefttLungData, unsigned long  dwNumber) = 0;
	};

}}
