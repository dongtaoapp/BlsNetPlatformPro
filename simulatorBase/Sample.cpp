#include <math.h>
#include <fstream>
#include ".\sample.h"
#include <boost/lexical_cast.hpp>
#include <boost/assert.hpp>

#include "..\Common\CommonGlobal.h"

namespace jysoft { namespace simulator {

	CSample::CSample(void)
	{
		m_iSampleSec = 400;
		m_iSampleVolt = 4096;
		//============================================
		m_eAllocType  = Customized;
		m_hHandle     = NULL;
		m_pPtrData    = NULL;
		m_dwGlobalSize = 0;
		m_dwSize      = 0;
		m_dwID        = 0;
	}

	CSample::CSample( HANDLE hAllocHeap, int nAllocSize ) 
	{
		CSample();
		//-------------------------------------------------------------------------
		m_hHandle = hAllocHeap;
		m_eAllocType = ExternalDeliver;
		//��ʼ�����ڴ�
		if( nAllocSize > 0 )
		{
			AllocSample( (unsigned long)nAllocSize );
		}
	}

	CSample::CSample(unsigned long dwID)
	{
		m_dwID = dwID;
		m_iSampleSec = 400;
		m_iSampleVolt = 4096;
		//--------------------------------------------------------------------------
		m_eAllocType   = Customized;
		m_hHandle      = NULL;
		m_pPtrData     = NULL;
		m_dwGlobalSize = 0;
		m_dwSize  = 0;
	}

	CSample::CSample( HANDLE hAllocHeap, unsigned long dwID, int nAllocSize)
	{
		m_dwID = dwID;
		m_iSampleSec = 400;
		m_iSampleVolt = 4096;
		//--------------------------------------------------------------------------
		m_eAllocType   = Customized;
		m_hHandle      = NULL;
		m_pPtrData     = NULL;
		m_dwGlobalSize = 0;
		m_dwSize  = 0;
		//--------------------------------------------------------------------------
		m_hHandle = hAllocHeap;
		m_eAllocType = ExternalDeliver;
		//��ʼ�����ڴ�
		if( nAllocSize > 0 )
		{
			AllocSample( (unsigned long)nAllocSize );
		}
	}

	CSample::~CSample(void)
	{
		try
		{
			if(m_hHandle != NULL && m_pPtrData )
			{
				::HeapFree(m_hHandle,HEAP_NO_SERIALIZE,m_pPtrData);
			}
		}
        catch (...)
		{
		}
		if( m_hHandle != NULL && m_eAllocType != ExternalDeliver )
		{
			::HeapDestroy(m_hHandle);
		}
	}

	void CSample::ResetSample(void)
	{
		try
		{
			if(m_hHandle != NULL && m_pPtrData )
			{
				::HeapFree(m_hHandle,HEAP_NO_SERIALIZE,m_pPtrData);
			}
		}
        catch (...)
		{
		}
		m_pPtrData = NULL;
		m_dwGlobalSize = 0;
		m_dwSize  = 0;
	}

    bool CSample::LoadSampleDataFromTxt(const std::string &strPathFile)
    {
        m_dwSize   = 0;
        //----------------------------------------------------------------------------------
        std::ifstream  ifs( strPathFile.c_str() );
        if( !ifs.bad() )
        {
            long  dwSumSize  = 0;
            std::string strData;
            do
            {
                char cData[21];
                strData.clear();
                ifs.getline(cData, 20);
                strData = std::string( cData );
                if( !strData.empty() )
                {
                    float fData = boost::lexical_cast<float>(strData);
                    //�������ݿռ�
                    if( m_dwGlobalSize < (dwSumSize+1) )
                    {
                        AllocSample( dwSumSize + 512 );
                    }
                    m_pPtrData[dwSumSize] = fData;
                    dwSumSize += 1;
                }
            } while (!strData.empty());
            ifs.close();
            m_dwSize  = dwSumSize;
        }
        else
        {
            return false;
        }
        return true;
    }

	//�����ļ��еĲ�������
	bool CSample::LoadSampleDataFromStream(LPSTREAM lpFileSteam)
	{
		if(lpFileSteam == NULL)
			return false;
		m_dwSize   = 0;
		//----------------------------------------------------------------------------------
		static float fDatalst[50];
		ULONG uReadSize = 0;
		lpFileSteam->Read(fDatalst, 50*sizeof(float), &uReadSize);
		uReadSize /= sizeof(float);
	
		unsigned long  dwSumSize  = 0;
		while(uReadSize > 0)
		{
			//�������ݿռ�
			if( m_dwGlobalSize < (dwSumSize+50) )
			{
				AllocSample( dwSumSize + 512 );
			}
			::memcpy(m_pPtrData+dwSumSize, fDatalst, uReadSize*sizeof(float));
			dwSumSize += (unsigned long)uReadSize;
			lpFileSteam->Read(fDatalst, 50*sizeof(float), &uReadSize);
			uReadSize /= sizeof(float);
		}
		m_dwSize  = dwSumSize;
		return true;
	}


	// �������ƣ� ChangeSampleData
	// ����˵���� 
	// ����ֵ�� 
	// ������ float *fSrcBegin��
	// ������ const int nCount��
	// ������ int nBeginTime��ȷ����ʼλ��
	void CSample::ChangeSampleData(float *fSrcBegin,const int nCount,int nBeginTime)
	{
		float *fBeginPtr = GetSamplePtr(nBeginTime);
		unsigned long nNeedCount = (fBeginPtr-m_pPtrData)+nCount;
		if(nNeedCount > m_dwGlobalSize)
		{
			//�������ݿռ�
			AllocSample( nNeedCount );
		}
		m_dwSize = nNeedCount;
		fBeginPtr = GetSamplePtr(nBeginTime);
		::memcpy((void *)fBeginPtr,(void *)fSrcBegin,nCount*sizeof(float));
	}

	//����
	void CSample::Clone(CSample *pOrgSample)
	{
		m_iSampleSec = pOrgSample->m_iSampleSec;
		m_iSampleVolt = pOrgSample->m_iSampleVolt;
		//�������ݿռ�
		AllocSample( pOrgSample->m_dwSize ); 

		m_dwSize = pOrgSample->m_dwSize;
		if(pOrgSample->m_pPtrData != NULL)
			::memcpy((void *)m_pPtrData,(void *)pOrgSample->m_pPtrData,m_dwSize*sizeof(float));
	}

	void CSample::Clone(CSample *pSrcSample,float *fpBegin,float *fpEnd)
	{
		m_iSampleSec = pSrcSample->m_iSampleSec;
		m_iSampleVolt = pSrcSample->m_iSampleVolt;
		unsigned long dwGlobalSize = (fpEnd-fpBegin)+1;
	
		//�������ݿռ�
		AllocSample( dwGlobalSize ); 
	
		m_dwSize = fpEnd-fpBegin;
		::memcpy((void *)m_pPtrData,(void *)fpBegin,m_dwSize*sizeof(float));
	}

	//���ز����ε�ʱ��(0.1΢��)
	int  CSample::GetSampleSumTime()
	{
		return 1000*10*m_dwSize/m_iSampleSec;
	}

	//����ʱ��(0.1΢��)���ز������ָ��
	//ע��iTime����0
	float * CSample::GetSamplePtr(int  iTime)
	{
		int iStep = m_iSampleSec * iTime/10000;
		return m_pPtrData+iStep;
	}

	//����X��ĳ���(����)�����ش˳����������ʱ��(0.1΢��)
	int CSample::GetSampleTime(float fX)
	{
		return int(fX/25*10000 + DEFINITE);
	}

	//int nTime����λ0.1΢��
	//����ֵ����λ(����)
	float CSample::GetLength(int nTime)
	{
		return nTime*1.0f*25/10000;
	}

	//����Y�����ֵ�����ر�ʾ�ĵ�ѹ(��λ������)
	float CSample::GetMilliVolt(float fH)
	{
		return fH/10;
	}

	//���ݵ�ѹ(��λ������)������Y�����ֵ
	float CSample::GetYFromMilliVolt(float fMillVolt)
	{
		return fMillVolt * 10;
	}


	// �������ƣ� AddSampleData
	// ����˵���� ��ˮƽֵfValue���
	// ����ֵ�� 
	// ������ int nTime������ʱ��(��λ��0.1����)
	// ������ float fValue���趨��ֵ(��λ������)
	void  CSample::AddSampleData(int nDstBeginTime, int nTime, float fValue)
	{
		int iNum = int(1.0f*nTime/10000*m_iSampleSec+DEFINITE);
		if( (m_dwSize + iNum ) > m_dwGlobalSize)
		{
			//�������ݿռ�
			AllocSample( m_dwGlobalSize + iNum ); 
		}
		float *pPtr = GetSamplePtr(nDstBeginTime);
		for(int i=0;i<iNum;i++)
			pPtr[i] = fValue;
		m_dwSize += iNum;
	}


	// �������ƣ� AddSampleData
	// ����˵���� ���߶�fBeginValue��fEndValue���
	// ����ֵ�� 
	// ������ int nDstBeginTime��
	// ������ int nTime��
	// ������ float fBeginValue��
	// ������ float fEndValue��

	void  CSample::AddSampleData(int nDstBeginTime, int nTime, float fBeginValue, float fEndValue)
	{
		int iNum = int(1.0f*nTime/10000*m_iSampleSec+DEFINITE);
		//�������ݿռ�
		AllocSample( m_dwSize + iNum ); 
	
		float *pPtr = GetSamplePtr(nDstBeginTime);
		float k = (fEndValue-fBeginValue)/iNum;
		for(int i=0;i<iNum;i++)
		{
			pPtr[i] = fBeginValue + i*k;
		}
		m_dwSize += iNum;
	}

	void CSample::AddSampleData(int nDstBeginTime, CSample *pSrcSample,float *fpBegin,float *fpEnd)
	{
		int iAddNum = (fpEnd-fpBegin) + 1;
		//�������ݿռ�
		AllocSample( m_dwSize + iAddNum ); 
	
		float *pPtr = GetSamplePtr(nDstBeginTime);
		::memcpy((void *)pPtr,(void *)fpBegin,(fpEnd-fpBegin)*sizeof(float));
		m_dwSize += (fpEnd-fpBegin);
	}

	void  CSample::OverlapSampleData(int nDstBeginTime,int nLogicTime,CSample *pSrcSample,float *fpBegin,float *fpEnd)
	{
		int iAddNum = (fpEnd-fpBegin) + 1;
		//�������ݿռ�
		AllocSample( m_dwSize + iAddNum ); 

		float *pPtr = GetSamplePtr(nDstBeginTime);
		float *pDstEndPtr = GetSamplePtr(nDstBeginTime + nLogicTime);
        BOOST_ASSERT((pDstEndPtr-pPtr) <= (fpEnd-fpBegin));
        int dIntervalSize = int(pDstEndPtr - pPtr);
		for(;pPtr<pDstEndPtr;++fpBegin,++pPtr)
		{
			*pPtr += *fpBegin;
		}
		::memcpy((void *)pPtr,(void *)fpBegin,(fpEnd-fpBegin)*sizeof(float));
		m_dwSize += (fpEnd-fpBegin);
		//���ص�������5�����
		//RidSampleYawp(nDstBeginTime,nLogicTime);
	}

	//������������
	void CSample::AdjustSampleData(float fData)
	{
		for(unsigned long i=0;i<m_dwSize;++i)
			m_pPtrData[i] -= fData;
	}

	//����ָ�룬���ش�λ���������ʱ��
	int CSample::GetValidTime(float *pfPos,int nBeginTime)
	{
		float *pfBegin = GetSamplePtr(nBeginTime);
		return 10000*(pfPos-pfBegin)/m_iSampleSec;
	}

	//����������ת��Ϊ8bit����������
	void CSample::ChangeSampleDataTo8Big()
	{
		for(unsigned long i=0;i<m_dwSize;++i)
		{	
			int n = int(256*(m_pPtrData[i]+2)/4);//X/256=(V-Vmin)/(Vmax-Vmin)
			m_pPtrData[i] =  -2.0f + n * 4/256.0f;
		}
	}

	//����
	void  CSample::RidSampleYawp(int nBeginTime, int nValidTime)
	{
		float *fBeginPtr = GetSamplePtr(nBeginTime);
		float *fEndPtr = GetSamplePtr(nBeginTime+nValidTime);
		float *pPtr = (float *)::HeapAlloc(m_hHandle,HEAP_ZERO_MEMORY,(fEndPtr-fBeginPtr+8)*sizeof(float));
		::memcpy((void *)(pPtr+4),(void *)fBeginPtr,(fEndPtr-fBeginPtr)*sizeof(float));
		for(int i=0;i<(fEndPtr-fBeginPtr);++i)
		{
			float fValue = 0.0f;
			for(int iStep = 0;iStep<5;++iStep)
				fValue += pPtr[i+iStep];
			pPtr[i] = fValue/5;
		}
		float fValue = pPtr[4] - fBeginPtr[0];
		for(int i=0;i<(fEndPtr-fBeginPtr);++i)
		{
			fBeginPtr[i] = pPtr[4+i]-fValue;
		}
		::HeapFree(m_hHandle,HEAP_NO_SERIALIZE,pPtr);
	}


	// �������ƣ� ZoomSampleDataHandle
	// ����˵���� ���Ų������ݴ���
	// ����ֵ�� 
	// ������ int iChgedTime���޸ĺ��ʱ��
	void  CSample::ZoomSampleDataHandle(int iChgedTime)
	{
		int iValidTime = 10000 * m_dwSize / m_iSampleSec;
		if(iValidTime == iChgedTime)
			return;
		float fZoom = 1.0f * iChgedTime/iValidTime;
		if(::fabs(fZoom-1.0) > DEFINITE)
		{
			int iSize = GetSampleNum(iChgedTime)+100;
			float *pPtr = (float *)::HeapAlloc(m_hHandle,HEAP_NO_SERIALIZE|HEAP_ZERO_MEMORY,iSize*sizeof(float));
			unsigned long iNum =0;//ʵ�ʱ���ĸ���
			if(fZoom > 1.0)
			{//��չ����
				float fSample = 1.0f/fZoom;
				pPtr[iNum++] = *m_pPtrData;
				for(unsigned long iStep = 1; iStep < m_dwSize;)
				{
					float fValue = (*(m_pPtrData+iStep) - *(m_pPtrData+(iStep-1)))/2 + *(m_pPtrData+iStep-1);
					if((fSample - 1.0) > DEFINITE)
					{
						fSample -= 1.0f;
						++iStep;
					}
					fSample += 1.0f/fZoom;
					pPtr[iNum] =fValue;
					++iNum;
				}
			}else
			{//��������ȡ����
				float fRate = 1.0f/fZoom;
				float fSample = fRate;
				pPtr[iNum++] = *m_pPtrData;
				for(unsigned long iStep = 1; iStep < m_dwSize; ++iStep)
				{
					if( (fSample - (iStep-1)) > DEFINITE &&  fSample < (iStep + DEFINITE))
					{
						float fValue = (*(m_pPtrData + (iStep-1)) + *(m_pPtrData +iStep))/2;
						pPtr[iNum] =fValue;
						++iNum;
						fSample += fRate;
					}
				}
			}
			//�������ݿռ�
			AllocSample( iNum ); 
		
			::memcpy((void *)m_pPtrData,(void *)pPtr,iNum*sizeof(float));
			float *pEndPtr = GetSamplePtr(iChgedTime);
			float fValue = m_pPtrData[iNum-1];
			for(;m_pPtrData + iNum < pEndPtr;++iNum)
			{
				m_pPtrData[iNum] = fValue;
			}
			m_dwSize = iNum;
			::HeapFree(m_hHandle,HEAP_NO_SERIALIZE,pPtr);
		}
	}

	// �������ƣ� CutSampleDataHandle
	// ����˵���� �и�������ݴ���
	// ����ֵ�� 
	// ������ int iPosTime��  �и��ʱ���
	// ������ bool bRmvPostion���Ƴ��Ĳ�λ(true:�ұߣ�false:���)
	void  CSample::CutSampleDataHandle(int iPosTime, bool bRmvPostion)
	{
		float *fPtr = GetSamplePtr(iPosTime);
		if(bRmvPostion == true)
		{//�Ƴ��ұ�
			m_dwSize = fPtr - m_pPtrData;
		}
		else
		{
			//�ƶ���������
			int iNum = (m_pPtrData + m_dwSize) - fPtr;
			for(int iStep = 0; iStep < iNum; ++iStep)
			{
				m_pPtrData[iStep] = m_pPtrData[iStep+iNum];
			}
			m_dwSize = iNum;
		}
	}

	void  CSample::DirectLinkSampleData(CSample *pSrcSample)
	{
		if(pSrcSample->IsEmpty() || pSrcSample->m_dwSize == 0)
			return;
		//�������ݿռ�
		AllocSample( m_dwSize + pSrcSample->m_dwSize );

		::memcpy((void *)(m_pPtrData+m_dwSize),(void *)pSrcSample->m_pPtrData,pSrcSample->m_dwSize*sizeof(float));
		m_dwSize += pSrcSample->m_dwSize;
	}

	//ˮƽ������Ӳ���
	void  CSample::HoriIntervalLinkSampleData(CSample *pSrcSample,int nIntervalTime, float fValue)
	{
		AddSampleData(GetSampleSumTime(),nIntervalTime,fValue);
		DirectLinkSampleData(pSrcSample);
	}

	//ˮƽ�������
	//bool bHorDirect��TURE:�������죻FALSE:��������
	void CSample::HoriIntervalLinkSampleData(int nExtendTime, float fValue, bool bHorDirect/*=true*/)
	{
		if(bHorDirect == true)
			AddSampleData(GetSampleSumTime(),nExtendTime,fValue);
		else
		{
			int nAddSum = GetSampleNum(nExtendTime);//���ӵĵ���
			//�������ݿռ�
			AllocSample( m_dwSize + nAddSum );
		
			for(int i=m_dwSize-1;i>=0;--i)
			{
				m_pPtrData[i+nAddSum] = m_pPtrData[i];
				m_pPtrData[i] = 0.0f;
			}
			for(int i = 0; i< nAddSum;++i)
				m_pPtrData[i] = fValue;
			m_dwSize += nAddSum;
		}
	}

	//ˮƽ�ӳ���ָ��ʱ�䳤��
	//int nTime����λ0.1΢��
	void  CSample::HoriExtendSampleData(int nTime)
	{
		int  nSumTime = GetSampleSumTime();
		if( nSumTime < nTime )
		{
			AddSampleData(nSumTime, nTime-nSumTime, m_pPtrData[m_dwSize-1]);
		}
	}

	//ֱ�߼�����Ӳ���
	void  CSample::LineIntervalLinkSampleData(CSample *pSrcSample,int nIntervalTime)
	{
		float fBeginValue,fEndValue;
		fBeginValue = m_pPtrData[m_dwSize-1];
		fEndValue = pSrcSample->m_pPtrData[0];
		AddSampleData(GetSampleSumTime(),nIntervalTime,fBeginValue,fEndValue);
		DirectLinkSampleData(pSrcSample);
	}

	//�����ص�����(ע����pSrcSample���ཻ�������ǰ���)
	void  CSample::OverlapLinkSampleData(CSample *pSrcSample,int nOverlapTime)
	{
		int iGlobalTime = GetSampleSumTime();
		OverlapSampleData(iGlobalTime-nOverlapTime,nOverlapTime,pSrcSample,pSrcSample->m_pPtrData,pSrcSample->m_pPtrData+pSrcSample->m_dwSize);
	}

	//��ʼλ���ص�����
	void  CSample::DirectOverlapLinkSampleData(const CSample *pSrcSample)
	{
		if(pSrcSample->IsEmpty() || pSrcSample->m_dwSize == 0)
			return;//�յķ���
		AllocSample( pSrcSample->m_dwSize );
	
		//�ص�����
		unsigned long dwOverlapSize = m_dwSize < pSrcSample->m_dwSize ? m_dwSize : pSrcSample->m_dwSize;
		float *fpBegin = pSrcSample->m_pPtrData;
		float *pPtr = m_pPtrData;
		for(unsigned long i=0;i<dwOverlapSize;++fpBegin,++pPtr,++i)
		{
			*pPtr += *fpBegin;
		}
		//������������
		if(m_dwSize < pSrcSample->m_dwSize)
		{
			::memcpy(pPtr,fpBegin,(pSrcSample->m_dwSize-m_dwSize)*sizeof(float));
			m_dwSize = pSrcSample->m_dwSize;
		}
	}

	//�������ݿռ�
	void CSample::AllocSample(unsigned long  dwGlobalSize)
	{
		if( m_hHandle == NULL )
		{
			m_hHandle = ::HeapCreate(HEAP_NO_SERIALIZE,0,0);
		}
		if( m_dwGlobalSize < dwGlobalSize )
		{
			m_dwGlobalSize = (dwGlobalSize/512+1)*512;
			if( m_pPtrData == NULL )
			{
				m_pPtrData  = (float *)::HeapAlloc( m_hHandle,HEAP_NO_SERIALIZE|HEAP_ZERO_MEMORY,m_dwGlobalSize*sizeof(float) );
			}
			else
			{
				m_pPtrData = (float *)::HeapReAlloc(m_hHandle,HEAP_ZERO_MEMORY,(void *)m_pPtrData,m_dwGlobalSize*sizeof(float));
			}
		}
	}

	//��ʼλ�ÿ�ʼ��pSrcSample���ǲ���
	void  CSample::DirectCoverLinkeSampleData(const CSample *pSrcSample)
	{
		if(pSrcSample->IsEmpty() || pSrcSample->m_dwSize == 0)
			return;//�յķ���
		//�������ݿռ�
		AllocSample( pSrcSample->m_dwGlobalSize );
	
		if(m_dwSize < pSrcSample->m_dwSize)
			m_dwSize = pSrcSample->m_dwSize;
		float *fpBegin = pSrcSample->m_pPtrData;
		float *pPtr = m_pPtrData;
		float *pDstEndPtr = pPtr + pSrcSample->m_dwSize;
		for(;pPtr<pDstEndPtr;++fpBegin,++pPtr)
		{
			*pPtr = *fpBegin;
		}
	}

	//����ѹֵת���ɶ�Ӧ��BYTEֵ
    int  CSample::ModifyVoltToLogicValue(const float *pBeginPtr, long uSrcSize,/*out*/unsigned char *pDstPtr, int iRate/*=1*/)
	{
		int iRtn = 0;
		for(int iStep = 0; iStep < uSrcSize; iStep += iRate)
		{
            pDstPtr[iRtn] = (unsigned char)::abs(int(256*(pBeginPtr[iStep]+2)/4));
			++iRtn;
		}
		return iRtn;
	}

}}
