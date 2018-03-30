#include ".\igetphysioloysimulatedata.h"

namespace jysoft { namespace simulator {

	IGetPhysioloySimulateData::IGetPhysioloySimulateData(void)
	{
	}

	IGetPhysioloySimulateData::~IGetPhysioloySimulateData(void)
	{
	}

	//--------------------------------------------------------------------------------------------------------------
	//class IGetEcgSimulateData
	IGetEcgSimulateData::IGetEcgSimulateData()
	{
		m_eRhythmLead = Lead_II;
		//----------------------------------------------------------------------
		m_pTempBuff   = NULL;
		m_dwSize      = 0;
	}

	IGetEcgSimulateData::~IGetEcgSimulateData()
	{
		if( m_pTempBuff && m_dwSize != 0 )
		{
			delete [] m_pTempBuff;
		}
		m_pTempBuff  = NULL;
	}

	/*******************************************************************************/
	//���ܣ���ȡ���������ڵ���������
	//������int iMilliTime:          ʱ�䣨0.1���룩
	//      float *pcBuffer:         ���ص���������
	//����ֵ:  �������ݵĳ���
	unsigned long IGetEcgSimulateData::GetPhysioloySimulateData(int iMilliTime, /*out*/float *pcBuffer/*=NULL*/)
	{
		unsigned long  dwRtn = GetI12LeadEcgSimulateData(iMilliTime, NULL);
		if( pcBuffer != NULL )
		{
			//������ʱ���ݽ�������ش�С
			ResetTempBuffSize( dwRtn );
			//��ȡ���������ڵĸ�������������
			GetI12LeadEcgSimulateData(iMilliTime, /*out*/m_pTempBuff);
			//����ָ������������
			for( unsigned long dwStep =0; dwStep < dwRtn; ++dwStep )
			{
				switch( m_eRhythmLead )
				{
				case Lead_I:
					{
						pcBuffer[dwStep] = m_pTempBuff[dwStep].m_fSampleI;
						break;;
					}
				case Lead_II:
					{
						pcBuffer[dwStep] = m_pTempBuff[dwStep].m_fSampleII;
						break;;
					}
				case Lead_III:
					{
						pcBuffer[dwStep] = m_pTempBuff[dwStep].m_fSampleIII;
						break;;
					}
				case Lead_aVR:
					{
						pcBuffer[dwStep] = m_pTempBuff[dwStep].m_fSampleaVR;
						break;;
					}
				case Lead_aVL:
					{
						pcBuffer[dwStep] = m_pTempBuff[dwStep].m_fSampleaVL;
						break;;
					}
				case Lead_aVF:
					{
						pcBuffer[dwStep] = m_pTempBuff[dwStep].m_fSampleaVF;
						break;;
					}
				case Lead_V1:
					{
						pcBuffer[dwStep] = m_pTempBuff[dwStep].m_fSampleV1;
						break;;
					}
				case Lead_V2:
					{
						pcBuffer[dwStep] = m_pTempBuff[dwStep].m_fSampleV2;
						break;;
					}
				case Lead_V3:
					{
						pcBuffer[dwStep] = m_pTempBuff[dwStep].m_fSampleV3;
						break;;
					}
				case Lead_V4:
					{
						pcBuffer[dwStep] = m_pTempBuff[dwStep].m_fSampleV4;
						break;;
					}
				case Lead_V5:
					{
						pcBuffer[dwStep] = m_pTempBuff[dwStep].m_fSampleV5;
						break;;
					}
				case Lead_V6:
					{
						pcBuffer[dwStep] = m_pTempBuff[dwStep].m_fSampleV6;
						break;;
					}
				}
			}
		}
		return dwRtn;
	}

	//������ʱ���ݽ�������ش�С
	void IGetEcgSimulateData::ResetTempBuffSize(unsigned long dwSize)
	{
		if( m_dwSize < dwSize )
		{
			if( m_pTempBuff != NULL )
			{
				delete [] m_pTempBuff;
			}
			m_pTempBuff = new I12LeadSample[dwSize];
			m_dwSize    = dwSize;
		}
	}

	//--------------------------------------------------------------------------------------------------------------
	//class IGetRespSimulateData
	IGetRespSimulateData::IGetRespSimulateData()
	{

	}

	IGetRespSimulateData::~IGetRespSimulateData()
	{

	}

	/*******************************************************************************
	//���ܣ���ȡ���������ڵ���������
	//������int iMilliTime:          ʱ�䣨0.1���룩
	//      float *pcBuffer:         ���ص���������
	//����ֵ:  �������ݵĳ���
	*********************************************************************************/
	unsigned long IGetRespSimulateData::GetPhysioloySimulateData(int iMilliTime, /*out*/float *pcBuffer /*= NULL*/)
	{
		unsigned long  dwRtn = GetRespSimulateData(iMilliTime, NULL, NULL);
		if( pcBuffer != NULL )
		{
			float *fLeftData = new float[dwRtn];
			float *fRightData = new float[dwRtn];
			GetRespSimulateData(iMilliTime, fLeftData, fRightData);
			for(unsigned long dwItem = 0; dwItem < dwRtn; ++dwItem)
			{
				pcBuffer[dwItem] = fLeftData[dwItem] + fRightData[dwItem];
			}
		}
		return dwRtn;
	}

}}
