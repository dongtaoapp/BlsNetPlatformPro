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

	//�ַ�ʵʱ��������
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

	//����
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
	//�ӿ�IDistributeEcgLeadsSimulateData
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
		//�ַ� II ����������
		for (unsigned long dwStep = 0; dwStep < dwNumber; ++dwStep)
		{
			lptrData[dwStep] = pEcgLeadSamples[dwStep].m_fSampleII;
		}
		delete [] pEcgLeadSamples;
	}

	//�ַ�ʵʱ��������
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
	//�ӿ�IDistributeRespSimulateData
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

	//�ַ�ʵʱ��������
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
