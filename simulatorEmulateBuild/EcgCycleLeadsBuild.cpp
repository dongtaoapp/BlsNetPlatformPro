#include <boost/assert.hpp>
#include ".\EcgCycleLeadsBuild.h"
#include ".\EcgLeadSamples.h"


namespace jysoft { namespace simulator { namespace ecg {

	//==================================test================================================//
	#define   _LEAD_SUM_ENUM     Lead_V6 /*Lead_V6*/
	//================================End test==============================================//

	CEcgCycleLeadsBuild::CEcgCycleLeadsBuild(void)
	{
	}


	CEcgCycleLeadsBuild::~CEcgCycleLeadsBuild(void)
	{
	}

	//返回导联构建类（aVR, aVL, aVF等的构造为空）
	CCardiogramConfigHandle * CEcgCycleLeadsBuild::GetCardiogramConfigHandlePtr( RhythmLead eEcgLeadType)
	{
		CCardiogramConfigHandle  *pEcgConfigHandle = NULL;
		if( eEcgLeadType != Lead_aVR && eEcgLeadType != Lead_aVL && eEcgLeadType != Lead_aVF )
		{
			if( eEcgLeadType <= Lead_III )
			{
				pEcgConfigHandle = &m_cCardiogramConfigHandle[int(eEcgLeadType)];
			}
			else if( eEcgLeadType >= Lead_V1 )
			{
				pEcgConfigHandle = &m_cCardiogramConfigHandle[int(eEcgLeadType)-3];
			}
		}
		return pEcgConfigHandle;
	}

	/*******************************************************************************/
	// 函数名称： CreateCycleLeadsData
	// 功能： 构建针对不同导联的单周期数据
	// 参数：  
	//          ICardiogramLeads *pVirCardiogramLeads:         
	//          /*out*/CEcgLeadSamples *pDestLeadSamples:      I12各导联数据（aVR, aVL, aVF由其它心导联推算）
	// 返回值: 
	bool CEcgCycleLeadsBuild::CreateCycleLeadsData(ICardiogramLeads *pVirCardiogramLeads, /*out*/CEcgLeadSamples *pDestLeadSamples)
	{
		bool   bRtn  = true;
		for( RhythmLead  eLeadType = Lead_I; eLeadType <= _LEAD_SUM_ENUM;  )
		{
			CCardiogramConfigHandle *pEcgConfigHandle = GetCardiogramConfigHandlePtr( eLeadType );
			if( pEcgConfigHandle != NULL )
			{
				CVirCardiogramParam * pLeadParam = pVirCardiogramLeads->GetEcgLeadParam( eLeadType );
				CSample *pDestLeadSample = pDestLeadSamples->GetEcgLeadSample( eLeadType );
				if( !CreateCycleLeadData(pLeadParam, pEcgConfigHandle, /*out*/pDestLeadSample ) )
				{
					bRtn  = false;
					break;
				}
				//修正数据，使构建的各导联的数据大小 >= 周期采样率
				pDestLeadSample->HoriExtendSampleData( pVirCardiogramLeads->GetCycleTime() );
			}
			else
			{
				CSample *pILeadSample = pDestLeadSamples->GetEcgLeadSample( Lead_I );
				CSample *pDestLeadSample = pDestLeadSamples->GetEcgLeadSample( eLeadType );
				pDestLeadSample->Clone( pILeadSample );
				switch( eLeadType )
				{
				case Lead_aVR:
					{
						// aVR = -(I+II)/2
						CSample *pIILeadSample = pDestLeadSamples->GetEcgLeadSample( Lead_II );
						for( DWORD nStep = 0; nStep < pDestLeadSample->m_dwSize && nStep < pIILeadSample->m_dwSize; ++nStep )
						{
							*(pDestLeadSample->m_pPtrData + nStep) += *(pIILeadSample->m_pPtrData + nStep);
							*(pDestLeadSample->m_pPtrData + nStep)  = *(pDestLeadSample->m_pPtrData + nStep)/-2.0f;
						}
                        BOOST_ASSERT( pDestLeadSample->m_dwSize == pIILeadSample->m_dwSize );
						break;
					}
				case Lead_aVL:
					{
						// aVL = I - II/2;
						CSample *pIILeadSample = pDestLeadSamples->GetEcgLeadSample( Lead_II );
						for( DWORD nStep = 0; nStep < pDestLeadSample->m_dwSize && nStep < pIILeadSample->m_dwSize; ++nStep )
						{
							*(pDestLeadSample->m_pPtrData + nStep) -= *(pIILeadSample->m_pPtrData + nStep)/2.0f;
						}
                        BOOST_ASSERT( pDestLeadSample->m_dwSize == pIILeadSample->m_dwSize );
						break;
					}
				case Lead_aVF:
					{
						// aVF = II - I/2;
						CSample *pIILeadSample = pDestLeadSamples->GetEcgLeadSample( Lead_II );
						for( DWORD nStep = 0; nStep < pDestLeadSample->m_dwSize && nStep < pIILeadSample->m_dwSize; ++nStep )
						{
							*(pDestLeadSample->m_pPtrData + nStep) = *(pIILeadSample->m_pPtrData + nStep) - *(pDestLeadSample->m_pPtrData + nStep)/2.0f;
						}
                        BOOST_ASSERT( pDestLeadSample->m_dwSize == pIILeadSample->m_dwSize );
						break;
					}
				}
			}
			//----------------------------------------------------------------------------------------------------------
			if( eLeadType != _LEAD_SUM_ENUM )
			{
				eLeadType = RhythmLead((int)eLeadType + 1);
			}
			else
			{
				break;
			}
		}
		return bRtn;
	}

	/*******************************************************************************/
	// 函数名称： CreateExtrasystData
	// 功能： 构建早搏数据
	// 参数：  
	//         int iCycleTime:                              心律周期时间（单位：0.1ms）
	//         Extrasys eExtrasyst:                         早搏类型
	//         ICardiogramLeads *pVirCardiogramLeads:       
	//         /*in,out*/CEcgLeadSamples *pDestLeadSamples:   
	// 返回值: 
	bool CEcgCycleLeadsBuild::CreateExtrasystData(int iCycleTime, Extrasys eExtrasyst, ICardiogramLeads *pVirCardiogramLeads, /*in,out*/CEcgLeadSamples *pDestLeadSamples)
	{
		bool   bRtn  = true;
		for( RhythmLead  eLeadType = Lead_I; eLeadType <= _LEAD_SUM_ENUM;  )
		{
			CCardiogramConfigHandle *pEcgConfigHandle = GetCardiogramConfigHandlePtr( eLeadType );
			if( pEcgConfigHandle != NULL )
			{
				CVirCardiogramParam * pLeadParam = pVirCardiogramLeads->GetEcgLeadParam( eLeadType );
				CSample *pDestLeadSample = pDestLeadSamples->GetEcgLeadSample( eLeadType );
				if( !pEcgConfigHandle->CreateExtrasystData(iCycleTime, eExtrasyst, pLeadParam, /*out*/pDestLeadSample) )
				{
					bRtn  = false;
					break;
				}
			}
			else
			{
				CSample *pILeadSample = pDestLeadSamples->GetEcgLeadSample( Lead_I );
				CSample *pDestLeadSample = pDestLeadSamples->GetEcgLeadSample( eLeadType );
				pDestLeadSample->Clone( pILeadSample );
				switch( eLeadType )
				{
				case Lead_aVR:
					{
						// aVR = -(I+II)/2
						CSample *pIILeadSample = pDestLeadSamples->GetEcgLeadSample( Lead_II );
						for( DWORD nStep = 0; nStep < pDestLeadSample->m_dwSize && nStep < pIILeadSample->m_dwSize; ++nStep )
						{
							*(pDestLeadSample->m_pPtrData + nStep) += *(pIILeadSample->m_pPtrData + nStep);
							*(pDestLeadSample->m_pPtrData + nStep)  = *(pDestLeadSample->m_pPtrData + nStep)/-2.0f;
						}
                        BOOST_ASSERT( pDestLeadSample->m_dwSize == pIILeadSample->m_dwSize );
						break;
					}
				case Lead_aVL:
					{
						// aVL = I - II/2;
						CSample *pIILeadSample = pDestLeadSamples->GetEcgLeadSample( Lead_II );
						for( DWORD nStep = 0; nStep < pDestLeadSample->m_dwSize && nStep < pIILeadSample->m_dwSize; ++nStep )
						{
							*(pDestLeadSample->m_pPtrData + nStep) -= *(pIILeadSample->m_pPtrData + nStep)/2.0f;
						}
                        BOOST_ASSERT( pDestLeadSample->m_dwSize == pIILeadSample->m_dwSize );
						break;
					}
				case Lead_aVF:
					{
						// aVF = II - I/2;
						CSample *pIILeadSample = pDestLeadSamples->GetEcgLeadSample( Lead_II );
						for( DWORD nStep = 0; nStep < pDestLeadSample->m_dwSize && nStep < pIILeadSample->m_dwSize; ++nStep )
						{
							*(pDestLeadSample->m_pPtrData + nStep) = *(pIILeadSample->m_pPtrData + nStep) - *(pDestLeadSample->m_pPtrData + nStep)/2.0f;
						}
                        BOOST_ASSERT( pDestLeadSample->m_dwSize == pIILeadSample->m_dwSize );
						break;
					}
				}
			}
			//----------------------------------------------------------------------------------------------------------
			if( eLeadType != _LEAD_SUM_ENUM )
			{
				eLeadType = RhythmLead((int)eLeadType + 1);
			}
			else
			{
				break;
			}
		}
		//修正数据，使构建的各导联的数据大小相同...
		return bRtn;
	}

    bool CEcgCycleLeadsBuild::CreateCycleLeadData(CVirCardiogramParam *pVirParam, CCardiogramConfigHandle *pConfigHandle, /*out*/CSample *pDestSample)
	{
        BOOST_ASSERT( pVirParam != NULL && pDestSample != NULL );
		//----------------------------------------------------------------------------------------------------------
		bool bRtn = true;
		_eRefurbishDataRange eRange = pVirParam->GeteRefurbishDataRange();
		switch(eRange)
		{
		case RD_LoadConfigFile://需要重新加载配置文件
			{
				bRtn = pConfigHandle->LoadConfigFile(pVirParam, pDestSample);
				break;
			}
		case RD_AllData://需要重新加载所有数据
			{
				bRtn = pConfigHandle->ReCreateMainCycleData(pVirParam, pDestSample);
				break;
			}
		case RD_OpSegmentData://需要重新计算数据操作段
			{
				bRtn = pConfigHandle->ParseDataOperatorXMLSegment(pVirParam);
				if(bRtn == true)
					bRtn = pConfigHandle->ParseCombineXMLSegment(pVirParam);
				if(bRtn == true)
					bRtn = pConfigHandle->CreateMainCycleData(pVirParam, pDestSample);
				break;
			}
		case RD_CombineSegmentData://需要重新计算所有组合段
			{
				bRtn = pConfigHandle->ParseCombineXMLSegment(pVirParam);
				if(bRtn == true)
					bRtn = pConfigHandle->CreateMainCycleData(pVirParam,pDestSample);
				break;
			}
		case RD_MainSegmentData:
			{
				bRtn = pConfigHandle->CreateMainCycleData(pVirParam,pDestSample);
				break;
			}
		}
		pVirParam->SeteRefurbishDataRange(RD_NoChange);
	
        return bRtn ;
	}
}}}
