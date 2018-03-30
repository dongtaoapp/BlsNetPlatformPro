#include ".\idistributesimulatedata.h"

#include <boost/assert.hpp>

namespace jysoft { namespace simulator {

	IDistributeSimulateData::IDistributeSimulateData(void)
	{
	}

	IDistributeSimulateData::~IDistributeSimulateData(void)
	{
	}

	bool IDistributeSimulateData::isKindOf(const std::string &className)
	{
		return isKindOfDistribute( className );
	}

	//分发实时采样数据
	void IDistributeSimulateData::OnDistributeSimulateData(float *lptrData, unsigned long  dwNumber)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface )
		{
			if( pInterface->isKindOf( "IDistributeSimulateData" ) )
			{
				IDistributeSimulateData *pStartDistribute = (IDistributeSimulateData *)pInterface;
				pStartDistribute->DistributeSimulateData(lptrData, dwNumber);
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	//启动
	void IDistributeSimulateData::OnStartDistributeSimulateData()
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface )
		{
			if( pInterface->isKindOf( "IDistributeSimulateData" ) )
			{
				IDistributeSimulateData *pStartDistribute = (IDistributeSimulateData *)pInterface;
				pStartDistribute->StartDistributeSimulateData();
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	bool IDistributeSimulateData::isKindOfDistribute(const std::string &className)
	{
		if( className == "IDistributeSimulateData" )
		{
			return true;
		}
		return false;
	}

	//---------------------------------------------------------------------------------------------------------------------------
	//接口IDistributeEcgLeadsSimulateData
	IDistributeEcgLeadsSimulateData::IDistributeEcgLeadsSimulateData()
	{

	}

	IDistributeEcgLeadsSimulateData::~IDistributeEcgLeadsSimulateData()
	{

	}

	bool IDistributeEcgLeadsSimulateData::isKindOfDistribute(const std::string &className)
	{
		if( className == "IDistributeEcgLeadsSimulateData" )
		{
			return true;
		}
		return IDistributeSimulateData::isKindOfDistribute(className);
	}

	void IDistributeEcgLeadsSimulateData::DistributeSimulateData(float *lptrData, unsigned long  dwNumber)
	{
		I12LeadSample *pEcgLeadSamples = new I12LeadSample[dwNumber];
		DistributeEcgLeadsSimulateData(/*out*/pEcgLeadSamples, dwNumber);
		//分发 II 导联的数据
		for (unsigned long dwStep = 0; dwStep < dwNumber; ++dwStep)
		{
			lptrData[dwStep] = pEcgLeadSamples[dwStep].m_fSampleII;
		}
		delete [] pEcgLeadSamples;
	}

	//分发实时采样数据
	void IDistributeEcgLeadsSimulateData::OnDistributeEcgLeadsSimulateData(I12LeadSample *pEcgLeadSamples, unsigned long  dwNumber)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface )
		{
			if( pInterface->isKindOf( "IDistributeEcgLeadsSimulateData" ) )
			{
				IDistributeEcgLeadsSimulateData *pDistribute = (IDistributeEcgLeadsSimulateData *)pInterface;
				pDistribute->DistributeEcgLeadsSimulateData(pEcgLeadSamples, dwNumber);
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	//---------------------------------------------------------------------------------------------------------------------------
	//接口IDistributeRespSimulateData
	IDistributeRespSimulateData::IDistributeRespSimulateData()
	{

	}

	IDistributeRespSimulateData::~IDistributeRespSimulateData()
	{

	}

	void IDistributeRespSimulateData::DistributeSimulateData(float *lptrData, unsigned long  dwNumber)
	{
        BOOST_ASSERT(0);
	}

	//分发实时采样数据
	void IDistributeRespSimulateData::OnDistributeSimulateData(float *lptrSumLungData,float *lptrLeftLungData, unsigned long  dwNumber)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface )
		{
			if( pInterface->isKindOf( "IDistributeRespSimulateData" ) )
			{
				IDistributeRespSimulateData *pDistribute = (IDistributeRespSimulateData *)pInterface;
				pDistribute->DistributeSimulateData(lptrSumLungData, lptrLeftLungData, dwNumber);
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}


	bool IDistributeRespSimulateData::isKindOfDistribute(const std::string &className)
	{
		if( className == "IDistributeRespSimulateData" )
		{
			return true;
		}
		return IDistributeSimulateData::isKindOfDistribute(className);
	}

}}
