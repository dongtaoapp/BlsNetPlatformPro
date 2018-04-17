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

	//���ص��������ࣨaVR, aVL, aVF�ȵĹ���Ϊ�գ�
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
	// �������ƣ� CreateCycleLeadsData
	// ���ܣ� ������Բ�ͬ�����ĵ���������
	// ������  
	//          ICardiogramLeads *pVirCardiogramLeads:         
	//          /*out*/CEcgLeadSamples *pDestLeadSamples:      I12���������ݣ�aVR, aVL, aVF�������ĵ������㣩
	// ����ֵ: 
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
				//�������ݣ�ʹ�����ĸ����������ݴ�С >= ���ڲ�����
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
	// �������ƣ� CreateExtrasystData
	// ���ܣ� �����粫����
	// ������  
	//         int iCycleTime:                              ��������ʱ�䣨��λ��0.1ms��
	//         Extrasys eExtrasyst:                         �粫����
	//         ICardiogramLeads *pVirCardiogramLeads:       
	//         /*in,out*/CEcgLeadSamples *pDestLeadSamples:   
	// ����ֵ: 
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
		//�������ݣ�ʹ�����ĸ����������ݴ�С��ͬ...
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
		case RD_LoadConfigFile://��Ҫ���¼��������ļ�
			{
				bRtn = pConfigHandle->LoadConfigFile(pVirParam, pDestSample);
				break;
			}
		case RD_AllData://��Ҫ���¼�����������
			{
				bRtn = pConfigHandle->ReCreateMainCycleData(pVirParam, pDestSample);
				break;
			}
		case RD_OpSegmentData://��Ҫ���¼������ݲ�����
			{
				bRtn = pConfigHandle->ParseDataOperatorXMLSegment(pVirParam);
				if(bRtn == true)
					bRtn = pConfigHandle->ParseCombineXMLSegment(pVirParam);
				if(bRtn == true)
					bRtn = pConfigHandle->CreateMainCycleData(pVirParam, pDestSample);
				break;
			}
		case RD_CombineSegmentData://��Ҫ���¼���������϶�
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
