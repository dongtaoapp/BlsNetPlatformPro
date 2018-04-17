#include <boost/assert.hpp>
#include ".\EcgLeadSamples.h"


namespace jysoft { namespace simulator { namespace ecg {

	//==================================test================================================//
	#define   _LEAD_SUM     12 /*12*/
	//================================End test==============================================//

	CEcgLeadSamples::CEcgLeadSamples(void)
	{
		m_pTempBuff            = NULL;
		m_dwTempBuffSize       = 0;
	}

	CEcgLeadSamples::~CEcgLeadSamples(void)
	{
		delete [] m_pTempBuff;;
		m_dwTempBuffSize   = 0;
	}

	/*******************************************************************************/
	// �������ƣ� DirectOverlapLinkSampleData
	// ���ܣ� ��ʼλ�õ��Ӳ���
	// ������  
	//        CEcgLeadSamples &cSrcLeadSamples:
	// ����ֵ: 
	void CEcgLeadSamples::DirectOverlapLinkSampleData( CEcgLeadSamples &cSrcLeadSamples )
	{
		for( int nLead = 0; nLead < _LEAD_SUM/*12*/; ++nLead )
		{
			CSample *pSrcLeadSample = cSrcLeadSamples.GetEcgLeadSample((RhythmLead)nLead);
			//���Ӳ���
			GetEcgLeadSample((RhythmLead)nLead)->DirectOverlapLinkSampleData( pSrcLeadSample );
		}
	}

	/*******************************************************************************/
	// �������ƣ� CombineLeadSamples
	// ���ܣ� ���ϸ����������ݵ����ݽ�������أ��������
	// ������ 
	//        int nMiliCycleTime:          ����ʱ��(0.1ms)        
	// ����ֵ:  
	I12LeadSample * CEcgLeadSamples::CombineLeadSamples(int nMiliCycleTime)
	{
		DWORD   dwSampleNum = (DWORD)GetSampleNum( nMiliCycleTime );
		//������ʱ���ݽ�������ش�С
		ResetTempBuffSize( dwSampleNum );
		for (DWORD dwStep = 0; dwStep < dwSampleNum; ++dwStep)
		{
			// I ����
			float *fptrSample = m_cLeadSample[0].m_pPtrData + dwStep;
			m_pTempBuff[dwStep].m_fSampleI = *fptrSample;
			// II ����
			if( m_cLeadSample[1].m_pPtrData != NULL )
			{
				fptrSample = m_cLeadSample[1].m_pPtrData + dwStep;
				m_pTempBuff[dwStep].m_fSampleII = *fptrSample;
			}
			// III ����
			if( m_cLeadSample[2].m_pPtrData != NULL )
			{
				fptrSample = m_cLeadSample[2].m_pPtrData + dwStep;
				m_pTempBuff[dwStep].m_fSampleIII = *fptrSample;
			}
			// aVR ����
			if( m_cLeadSample[3].m_pPtrData != NULL )
			{
				fptrSample = m_cLeadSample[3].m_pPtrData + dwStep;
				m_pTempBuff[dwStep].m_fSampleaVR = *fptrSample;
			}
			// aVL ����
			if( m_cLeadSample[4].m_pPtrData != NULL )
			{
				fptrSample = m_cLeadSample[4].m_pPtrData + dwStep;
				m_pTempBuff[dwStep].m_fSampleaVL = *fptrSample;
			}
			// aVF ����
			if( m_cLeadSample[5].m_pPtrData != NULL )
			{
				fptrSample = m_cLeadSample[5].m_pPtrData + dwStep;
				m_pTempBuff[dwStep].m_fSampleaVF = *fptrSample;
			}
			// V1 ����
			if( m_cLeadSample[6].m_pPtrData != NULL )
			{
				fptrSample = m_cLeadSample[6].m_pPtrData + dwStep;
				m_pTempBuff[dwStep].m_fSampleV1 = *fptrSample;
			}
			// V2 ����
			if( m_cLeadSample[7].m_pPtrData != NULL )
			{
				fptrSample = m_cLeadSample[7].m_pPtrData + dwStep;
				m_pTempBuff[dwStep].m_fSampleV2 = *fptrSample;
			}
			// V3 ����
			if( m_cLeadSample[8].m_pPtrData != NULL )
			{
				fptrSample = m_cLeadSample[8].m_pPtrData + dwStep;
				m_pTempBuff[dwStep].m_fSampleV3 = *fptrSample;
			}
			// V4 ����
			if( m_cLeadSample[9].m_pPtrData != NULL )
			{
				fptrSample = m_cLeadSample[9].m_pPtrData + dwStep;
				m_pTempBuff[dwStep].m_fSampleV4 = *fptrSample;
			}
			// V5 ����
			if( m_cLeadSample[10].m_pPtrData != NULL )
			{
				fptrSample = m_cLeadSample[10].m_pPtrData + dwStep;
				m_pTempBuff[dwStep].m_fSampleV5 = *fptrSample;
			}
			// V6 ����
			if( m_cLeadSample[11].m_pPtrData != NULL )
			{
				fptrSample = m_cLeadSample[11].m_pPtrData + dwStep;
				m_pTempBuff[dwStep].m_fSampleV6 = *fptrSample;
			}
		}
		return m_pTempBuff;
	}

	/*******************************************************************************/
	// �������ƣ� ClearEcgLeadCycleData
	// ���ܣ� �������������ʱ���ڵ��ĵ�ͼ���ݣ�������ʣ������
	// ������ 
	//        int nMiliCycleTime:          ����ʱ��(0.1ms)
	// ����ֵ:  
	void CEcgLeadSamples::ClearEcgLeadCycleData(int nMiliCycleTime)
	{
		for( int nLead = 0; nLead < _LEAD_SUM/*12*/; ++nLead )
		{
			int iSumTime = m_cLeadSample[nLead].GetSampleSumTime();
			if( iSumTime > nMiliCycleTime )
			{
				float *fBegin = m_cLeadSample[nLead].GetSamplePtr(0);
				float *fEnd = m_cLeadSample[nLead].GetSamplePtr(nMiliCycleTime);
				float *fEnd2 = fBegin + m_cLeadSample[nLead].m_dwSize; 
				for(;fEnd < fEnd2;++fEnd,++fBegin)
					*fBegin = *fEnd;
				m_cLeadSample[nLead].m_dwSize = m_cLeadSample[nLead].GetSampleNum(iSumTime-nMiliCycleTime);
			}
			else
			{
				m_cLeadSample[nLead].m_dwSize = 0;
			}
		}
	}

	/*******************************************************************************/
	// �������ƣ� CutEcgLeadCycleExtendData
	// ���ܣ� �г��������ڲ��ֵ����� 
	// ������ 
	//        int nMiliCycleTime:          ����ʱ��(0.1ms)
	// ����ֵ:  
	bool CEcgLeadSamples::CutEcgLeadCycleExtendData(int nMiliCycleTime)
	{
		bool   bCutExtendData = false;
		for( int nLead = 0; nLead < _LEAD_SUM/*12*/; ++nLead )
		{
			if(m_cLeadSample[nLead].GetSampleSumTime() > nMiliCycleTime)
			{//���������ڵĲ����г���
				float fBeginValue = 0.0f;
				m_cLeadSample[nLead].CutSampleDataHandle(nMiliCycleTime-20,true);
				fBeginValue = *m_cLeadSample[nLead].GetSamplePtr(nMiliCycleTime-20);
				m_cLeadSample[nLead].AddSampleData(nMiliCycleTime-20,20,fBeginValue,0.0f);
				//--------------------------------------------------------------------------------------------
				if( !bCutExtendData )
				{
					bCutExtendData = true;
				}
			}
		}
		return bCutExtendData;
	}

	/*******************************************************************************/
	// �������ƣ� GetBuildEcgLeadSampleNum
	// ���ܣ� ���ع������ĵ�ͼ��������
	// ������ 
	//        
	// ����ֵ: 
	UINT CEcgLeadSamples::GetBuildEcgLeadSampleNum()
	{
		UINT    uBuildSize = 0;
		for( int nLead = 0; nLead < _LEAD_SUM/*12*/; ++nLead )
		{
			if( m_cLeadSample[nLead].m_dwSize == 0 )
			{
				uBuildSize = 0;
				break;
			}
	#ifdef  _DEBUG
			if( uBuildSize != 0 && uBuildSize != m_cLeadSample[nLead].m_dwSize )
			{
                BOOST_ASSERT( 0 );
			}
	#endif
			uBuildSize = m_cLeadSample[nLead].m_dwSize;
		}
		return uBuildSize;
	}

	//��ո��������ĵ�ͼ����
	void CEcgLeadSamples::EmptyEcgLeadSamples()
	{
		for( int nLead = 0; nLead < _LEAD_SUM/*12*/; ++nLead )
		{
			m_cLeadSample[nLead].m_dwSize = 0;
		}
	}

	/*******************************************************************************/
	// �������ƣ� CombineArtifactData
	// ���ܣ� ��Ӽ�����50/60HZʱ������
	// ������ 
	//        Artifact eArtiface:  
	//        int iCycleTime:  
	//        UINT uArtifactNum:         
	// ����ֵ:  
	UINT  CEcgLeadSamples::CombineArtifactData(Artifact eArtiface, int iCycleTime, UINT uArtifactNum)
	{
	#define  PI    3.1415926
		switch(eArtiface)
		{
		case AF_None:
			{
				break;
			}
		case AF_Muscular: //�������
			{
				UINT uCycleNum = 0;
				unsigned int  nSampleNum = GetSampleNum( iCycleTime );
				float *fValuePtr = GetTriangleCycleData(30,uCycleNum);
				for( unsigned int iIndex = 0; iIndex < nSampleNum; ++iIndex )
				{
					for( int nLead = 0; nLead < _LEAD_SUM/*12*/; ++nLead )
					{
						float *fptrSample = m_cLeadSample[nLead].GetSamplePtr( 0 ) + iIndex;
						float df = 0.0f;
						*fptrSample += 0.07 * fValuePtr[uArtifactNum%uCycleNum] * (1+sin(2.0f*PI*13*uArtifactNum*0.0025));
					}
					++uArtifactNum;
				}
				break;
			}
		case AF_Frequent: //50/60���ȵĸ���
			{
				unsigned int  nSampleNum = GetSampleNum( iCycleTime );
				for( unsigned int iIndex = 0; iIndex < nSampleNum; ++iIndex )
				{
					for( int nLead = 0; nLead < _LEAD_SUM/*12*/; ++nLead )
					{
						float *fptrSample = m_cLeadSample[nLead].GetSamplePtr( 0 ) + iIndex;
						*fptrSample += 0.15 * (1+sin(2.0f*PI*50*uArtifactNum*0.0025));
					}
					++uArtifactNum;
				}
				break;
			}
		}
		return uArtifactNum;
	}

	float* CEcgLeadSamples::GetTriangleCycleData(int nFrequent, UINT &uCycleNum)
	{
	#define  PI    3.1415926
		static float fValue[100];
		uCycleNum = 400/nFrequent;//���ڵĵ���
		bool bBeforeHalf = true;
		for(int i=1; i<= uCycleNum; ++i)
		{
			if(bBeforeHalf == true)
				fValue[i-1] = 2.0f*nFrequent*i*0.0025;
			if(bBeforeHalf && fValue[i-1] > 1.0f)
			{
				bBeforeHalf = false;
			}
			if(bBeforeHalf == false)
			{//��һ�εĺ�������
				fValue[i-1] = 2.0f*nFrequent*(1.0f/nFrequent - i*0.0025);
			}
		}
		return fValue;
	}

	//������ʱ���ݽ�������ش�С
	void CEcgLeadSamples::ResetTempBuffSize(DWORD dwSize)
	{
		if( m_dwTempBuffSize < dwSize )
		{
			if( m_pTempBuff != NULL )
			{
				delete [] m_pTempBuff;
			}
			m_pTempBuff = new I12LeadSample[dwSize];
			m_dwTempBuffSize    = dwSize;
		}
	}
}}}
