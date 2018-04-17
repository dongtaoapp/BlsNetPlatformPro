#include <boost/assert.hpp>
#include ".\abpsimulatebuild.h"

#include "..\SimulatorBase\ShowABPUpdateInterface.h"


#define  MAX_DIFFH  30  //��������ѹ������ѹ֮��ĸ߶Ȳ����ȷ��ƽ��ѹ�ļ��㷽ʽ
#define  AVG_HEIGHT 20.0f  //��ƽ��ѹ����ѹ�����30ʱ�����ڼ���ƽ��ѹ�߶�����ֵ

#define  _ABP_SAMPLE_FILE_1_    "\\IBPSimulateData\\IBPSimulateData1.txt"
#define  _ABP_SAMPLE_FILE_2_    "\\IBPSimulateData\\IBPSimulateData2.txt"

namespace jysoft { namespace simulator { namespace bp {

	CABPSimulateBuild::CABPSimulateBuild(void)
	{
		m_hHeapHandle = ::HeapCreate(HEAP_NO_SERIALIZE,2000*sizeof(float),4000*sizeof(float));
		m_DataBuffer.InitializeBuff(m_cSrcFirstABPSampleData.GetSampleNum(20*10000));
		m_nShrinkValue=120;
		m_nStretchValue=60;
		m_fLastData = 60.0f;
		//����ABP���Ӽ��
		m_bClearWatchLink  = true;
		m_bLinkWatchABP    = false;
	}

	CABPSimulateBuild::~CABPSimulateBuild(void)
	{
		::HeapDestroy(m_hHeapHandle);
	}

	//��ʼ������
	void CABPSimulateBuild::initialABPSample(const std::string &resPath)
	{
		std::string  strFilePath = resPath + _ABP_SAMPLE_FILE_1_;
		m_cSrcFirstABPSampleData.LoadSampleDataFromTxt( strFilePath );
		m_cCurrFirstABPSampleData.Clone( &m_cSrcFirstABPSampleData );

		strFilePath = resPath + _ABP_SAMPLE_FILE_2_;
		m_cSrcNextABPSampleData.LoadSampleDataFromTxt( strFilePath );
		m_cCurrNextABPSampleData.Clone(&m_cSrcNextABPSampleData);

		//���������ϵ�����ݱ���ת����ص�
		float fCoefficient =m_nShrinkValue/147.4235f;
		for(long dwStep = 0; dwStep < m_cCurrFirstABPSampleData.m_dwSize ; ++dwStep)
		{
			if(m_nShrinkValue==m_nStretchValue)
				m_cCurrFirstABPSampleData.m_pPtrData[dwStep] = (float)m_nShrinkValue;
			else
				m_cCurrFirstABPSampleData.m_pPtrData[dwStep] = m_cSrcFirstABPSampleData.m_pPtrData[dwStep] * fCoefficient;
		}
		m_cOutput.Clone(&m_cCurrFirstABPSampleData);
		m_cCurrFirstABPSampleData2.Clone(&m_cCurrFirstABPSampleData);
	}
	/*******************************************************************************/
	//���ܣ�Ѫ���������ݼ���
	//������int nDifferMilliTime:          ʱ�䣨0.1���룩
	//      int nQtoSMilliTime:            Q����S����ʱ�䣨0.1���룩
	//      int nStoTMilliTime:            S����T����ʱ�䣨0.1���룩
	//      int nCycleTime:                ����ʱ�䣨0.1���룩
	//����ֵ:  
	void CABPSimulateBuild::StartPhysiologySimpleLoad(int nDifferMilliTime, int nQtoSMilliTime, int nStoTMilliTime, int nCycleTime)
	{	
		//m_nShrinkValue=60;
		//m_nStretchValue=60;
		int nSystolicTime = nQtoSMilliTime + nStoTMilliTime;
		//���»�ȡ�������
		m_cSwapMutex.lock();
		m_cOutput.Clone(&m_cCurrFirstABPSampleData);
		m_cCurrFirstABPSampleData2.Clone(&m_cCurrFirstABPSampleData);
		m_cCurrNextABPSampleData.Clone(&m_cSrcNextABPSampleData);
		m_cSwapMutex.unlock();

		//����ʱ�䣬��ȡһ�����ڵ�ABP����
		//GetABPOutputData(nSystolicTime,nCycleTime);
		GetABPOutputData(nQtoSMilliTime,nStoTMilliTime,nCycleTime);
		
		//������д�뻺��
		if( !m_cOutput.IsEmpty() )
		{
			float fCompareValue = 0.0f;

			m_cSwapMutex.lock();
			short dwRtSize = m_cOutput.GetSampleNum(nDifferMilliTime);
			float *fBeginValue = new float[dwRtSize+8];
			for(short i = 0; i < dwRtSize+8; ++i)
				fBeginValue[i] = 0.0f;
			short dwOverlapSize = 0;
			if(m_DataBuffer.GetNoneReadedNum() > 0)
			{
				m_DataBuffer.ReadDataMovePtr(fBeginValue,dwRtSize, &dwOverlapSize);
				fCompareValue = fBeginValue[dwOverlapSize-1];
			}
			if(m_DataBuffer.GetNoneReadedNum() > 0)
			{
				m_DataBuffer.ReadDataMovePtr(fBeginValue+dwOverlapSize,8, &dwRtSize);
			}
			else
			{
				dwRtSize = 0;
			}
			m_DataBuffer.Empty();
			short dwStep = 0;
			bool  bFindInsertPos = false;
			for(; dwStep < m_cOutput.m_dwSize-1 ; ++dwStep)
			{
				float fSampleData = m_cOutput.m_pPtrData[dwStep];
				float fNextSampleData = m_cOutput.m_pPtrData[dwStep+1];
				if(fSampleData < fCompareValue && fNextSampleData > fCompareValue)
				{
					bFindInsertPos = true;
					break;
				}
				else if(fSampleData > fCompareValue && fNextSampleData > fCompareValue)
				{
					bFindInsertPos = true;
					break;
				}
				else if( fCompareValue > fSampleData && fCompareValue > fNextSampleData && fNextSampleData < fSampleData)
				{
					bFindInsertPos = true;
					break;
				}

			}
			if( bFindInsertPos )
			{
				float *fDstPtr = m_cOutput.m_pPtrData+dwStep;
				for(DWORD n=0; n < dwRtSize; ++n)
				{
					fBeginValue[n+dwOverlapSize] = (fDstPtr[n]+fBeginValue[n+dwOverlapSize])/2;				
				}
				m_DataBuffer.WriteData(fBeginValue, dwOverlapSize+dwRtSize);
				fDstPtr= fDstPtr + dwRtSize;
				m_DataBuffer.WriteData(fDstPtr, m_cOutput.m_dwSize-dwStep-dwRtSize);

			}
			delete [] fBeginValue;
			m_cSwapMutex.unlock();
		}
		//��ʾ��ʱ��ֵ
		m_cInterfaceMutex.lock();
		if( m_pShowABPUpdate )
		{
			m_pShowABPUpdate->OnShowABPValue( m_nShrinkValue,m_nStretchValue );
		}
		m_cInterfaceMutex.unlock();
	
	}

	void CABPSimulateBuild::GetSampleDataPos(CABPSample &sample,float start,float stop,int& startpos,int& stoppos)
	{
        BOOST_ASSERT( sample.m_dwSize >= 1 );
		stoppos = sample.m_dwSize-1;
		//������ѹ��������ѹʱ
		float fMax=-1.0f;
		int nMax;
		if(m_nShrinkValue==m_nStretchValue)
		{
			startpos=0;
			stoppos=sample.m_dwSize-1;
			return;
		}
	
        for(long i=0;i < sample.m_dwSize;i++)
		{
			if(sample.m_pPtrData[i]>fMax)
			{
				fMax=sample.m_pPtrData[i];
				nMax=i;
			}
		}
	 
		for(DWORD i=0;i < sample.m_dwSize;i++)
		{
			if(start>fMax)
			{
				startpos=nMax;
				break;
			}
			if(sample.m_pPtrData[i]==start)
			{
				startpos=i;
				break;
			}
			if(sample.m_pPtrData[i-1]<start&&start<sample.m_pPtrData[i])
			{
				startpos=i;
				break;
			}
		}

		for(DWORD j=startpos+1;j<sample.m_dwSize;j++)
		{
			if(stop>fMax)
			{
				stoppos=nMax;
				break;
			}
			if(sample.m_pPtrData[j]==stop)
			{
				stoppos=j;
				break;
			}
			if(sample.m_pPtrData[j-1]>stop
			&&stop>sample.m_pPtrData[j])
			{
				stoppos=j;
				break;
			}
		}
		if(stoppos==-1)
			stoppos=sample.m_dwSize-1;
	}

	void CABPSimulateBuild::GetABPOutputData(int nQtoSMilliTime, int nStoTMilliTime, int nCycleTime)
	{
		//�ж�����ѹ������ѹ�Ƿ���ͬ
		if(m_nShrinkValue > m_nStretchValue)
		{
			float f = 0.0f;//�ڶ��β���ķ�ֵ
			//nFirstStartPos,nFirstStopPos,nFirstTimeΪ��һ������ǰ�벿�ֵ���ʼ�㣬�����㣬�Լ�����������ʵ�ʵ���ʱ��
			//nNextStartPos,nNextStopPos,nNextTimeΪ��һ�����ݺ�벿�ֵ���ʼ�㣬�����㣬�Լ�����������ʵ�ʵ���ʱ��
			//nLastStartPos,nLastStopPos,nLastTimeΪ�ڶ��ζ����ݵ���ʼ�㣬�����㣬�Լ�����������ʵ�ʵ���ʱ��
			int nFirstStartPos,nFirstStopPos,nNextStartPos,nNextStopPos,nLastStartPos,nLastStopPos,nFirstTime,nNextTime,nLastTime;
			//��ȡǰһ������ǰ�벿�ֵ���ʼ�㣬������
			GetSampleDataPos(m_cOutput,m_fLastData,(float)m_nShrinkValue,nFirstStartPos,nFirstStopPos);
			//���ݱ�����ȡʵ��ʱ��
			nFirstTime=nQtoSMilliTime*m_cOutput.m_dwSize/(nFirstStopPos-nFirstStartPos+1);
			//����ʵ��ʱ��ѹ������
			m_cSwapMutex.lock();
			m_cOutput.ZoomSampleDataHandle(nFirstTime);
			m_cSwapMutex.unlock();
			//�����µ����ݻ�ȡ��ʼ��ͽ�����
			GetSampleDataPos(m_cOutput,m_fLastData,(float)m_nShrinkValue,nFirstStartPos,nFirstStopPos);
			//��ȡ��һ�κ�벿�ֵĽ����������
			float nMid=(float)(m_nStretchValue)+(float)((m_nShrinkValue-m_nStretchValue)*2/3);//����ǰһ�����ݽ������ֵ
			GetSampleDataPos(m_cCurrFirstABPSampleData2,(float)m_nShrinkValue,(float)nMid,nNextStartPos,nNextStopPos);
			nNextTime=nStoTMilliTime*m_cCurrFirstABPSampleData2.m_dwSize/(nNextStopPos-nNextStartPos+1);
			m_cSwapMutex.lock();
			m_cCurrFirstABPSampleData2.ZoomSampleDataHandle(nNextTime);
			m_cSwapMutex.unlock();
			GetSampleDataPos(m_cCurrFirstABPSampleData2,(float)m_nShrinkValue,(float)nMid,nNextStartPos,nNextStopPos);
			//����ǰһ����Ľ������ȡ��һ�ε���ߵ�
			if(nNextStopPos<nNextStartPos+2)
				f=m_cCurrFirstABPSampleData2.m_pPtrData[nNextStopPos]+0.00001f;
			else
			{
				f=(float)((m_nShrinkValue-m_cCurrFirstABPSampleData2.m_pPtrData[nNextStopPos])/4)+m_cCurrFirstABPSampleData2.m_pPtrData[nNextStopPos];
			}
			//�Ժ�һ�����ݽ�������
			m_cSwapMutex.lock();
			float fCoefficient = f/87.0635f;
			for(DWORD dwStep=0; dwStep < m_cCurrNextABPSampleData.m_dwSize ; ++dwStep)
			{
				m_cCurrNextABPSampleData.m_pPtrData[dwStep] = m_cSrcNextABPSampleData.m_pPtrData[dwStep] * fCoefficient;
			}
			m_cSwapMutex.unlock();
			GetSampleDataPos(m_cCurrNextABPSampleData,m_cCurrFirstABPSampleData2.m_pPtrData[nNextStopPos],m_fLastData,nLastStartPos,nLastStopPos);
			nLastTime=(nCycleTime-nStoTMilliTime-nQtoSMilliTime)*m_cCurrNextABPSampleData.m_dwSize/(nLastStopPos-nLastStartPos+1);
			m_cSwapMutex.lock();
			m_cCurrNextABPSampleData.ZoomSampleDataHandle(nLastTime);
			m_cSwapMutex.unlock();
			GetSampleDataPos(m_cCurrNextABPSampleData,m_cCurrFirstABPSampleData2.m_pPtrData[nNextStopPos],m_fLastData,nLastStartPos,nLastStopPos);
			m_fLastData=m_cCurrNextABPSampleData.m_pPtrData[nLastStopPos];
			//���ݸ������ݵ���ʼ�����������иȻ������
			m_cOutput.CutBefore(nFirstStartPos);
			m_cOutput.CutAfter(nFirstStopPos-nFirstStartPos);
			m_cCurrFirstABPSampleData2.CutBefore(nNextStartPos);
			m_cCurrFirstABPSampleData2.CutAfter(nNextStopPos-nNextStartPos);
			m_cCurrNextABPSampleData.CutBefore(nLastStartPos);
			m_cCurrNextABPSampleData.CutAfter(nLastStopPos-nLastStartPos);
		
		}
		else  //������ѹ����������ѹʱ,����ֵ�����
		{
			m_cSwapMutex.lock();
			for(DWORD dwStep=0; dwStep < m_cCurrNextABPSampleData.m_dwSize ; ++dwStep)
			{
				m_cCurrNextABPSampleData.m_pPtrData[dwStep] =(float)m_nStretchValue;
			}
			m_cSwapMutex.unlock();
		}
	
		m_cOutput.DirectLinkSampleData(&m_cCurrFirstABPSampleData2);
		m_cOutput.DirectLinkSampleData(&m_cCurrNextABPSampleData);
	}

	/*******************************************************************************
	//���ܣ���ȡ���������ڵ���������
	//������int iMilliTime:          ʱ�䣨0.1���룩
	//      float *pcBuffer:         ���ص���������
	//����ֵ:  �������ݵĳ���
	*********************************************************************************/
	unsigned long CABPSimulateBuild::GetPhysioloySimulateData(int iMilliTime, /*out*/float *pcBuffer /*= NULL*/)
	{
		short dwRtSize = m_cSrcFirstABPSampleData.GetSampleNum(iMilliTime);
		if( pcBuffer != NULL )
		{
			m_cSwapMutex.lock();
			/*for(DWORD dwItem = dwRtSize; dwItem < dwRtSize; dwItem++)
			{
				pcBuffer[dwItem] = 0.0f;
			}*/
			short dwRemainBuffNum = m_DataBuffer.GetNoneReadedNum();
			if( dwRemainBuffNum > 0 ) 
			{
				short dwActiveNum = 0;//ʵ�ʷ��ص�������
				m_DataBuffer.ReadDataMovePtr(pcBuffer,dwRtSize,&dwActiveNum);
				if( dwActiveNum != dwRtSize )
				{
					for(short dwItem = dwActiveNum; dwItem < dwRtSize; dwItem++)
					{
						pcBuffer[dwItem] = pcBuffer[dwActiveNum-1];
					}
				}
			}
			else
			{
				for(short dwItem = 0; dwItem < dwRtSize; dwItem++)
				{
					pcBuffer[dwItem] = (float)m_nStretchValue;
				}
			}
		
			m_cSwapMutex.unlock();
		}
		return dwRtSize;
	}


	/*******************************************************************************/
	// �������ƣ� ModifyABPValue
	// ���ܣ� �޸�ABP��ֵ
	// ������  
	// ����ֵ:  
	void CABPSimulateBuild::ModifyABPValue(int nShrinkValue, int nStretchValue)
	{
		//nStretchValue=79;
		//nShrinkValue=80;
		if( m_nShrinkValue != nShrinkValue||m_nStretchValue!=nStretchValue )
		{
			if(nStretchValue == 0)
				m_nStretchValue = 1;
			else
				m_nStretchValue=nStretchValue;
			m_nShrinkValue = nShrinkValue;
			if(nStretchValue == 0)
				m_fLastData = 1.0f;
			else
				m_fLastData = (float)nStretchValue;
			//�޸�Ѫ���Ĳ�������
			m_cSwapMutex.lock();
			float fCoefficient =m_nShrinkValue/147.4235f;
			for(DWORD dwStep = 0; dwStep < m_cCurrFirstABPSampleData.m_dwSize ; ++dwStep)
			{
				if(m_nShrinkValue==m_nStretchValue)
					m_cCurrFirstABPSampleData.m_pPtrData[dwStep] = (float)m_nShrinkValue;
				else
					m_cCurrFirstABPSampleData.m_pPtrData[dwStep] = m_cSrcFirstABPSampleData.m_pPtrData[dwStep] * fCoefficient;
			}
			m_cSwapMutex.unlock();
		}
	}

	CSample * CABPSimulateBuild::GetCurrSamplePtr(void)
	{
		return &m_cOutput;
	}

	//�ر�ABPģ����
	void CABPSimulateBuild::CloseABPSimulateBuild()
	{
		m_nShrinkValue=120;
		m_nStretchValue=80;
		m_cCurrFirstABPSampleData.Clone( &m_cSrcFirstABPSampleData );
		m_cCurrNextABPSampleData.Clone(&m_cSrcNextABPSampleData);
		m_DataBuffer.ResetBeginPosToReadBeginPos();
		m_DataBuffer.Empty();
	}

	//����ABP����״̬�������Ƿ���ʾABP����
	bool CABPSimulateBuild::IsShowABPLinkState()
	{
		if( m_bClearWatchLink || m_bLinkWatchABP )
		{
			return true;
		}
		return false;
	}

	//�����Ƿ����ABP���Ӽ��
	void CABPSimulateBuild::Set_IsClearABPWatchLink(BOOL bClear)
	{
		m_bClearWatchLink  = bClear;
		boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
		if( m_pShowABPUpdate != NULL )
		{
			if( IsShowABPLinkState() )
			{
				m_pShowABPUpdate->OnAllLinkUpdateShow();
			}
			else 
			{
				m_pShowABPUpdate->OnAllUnLinkUpdateShow();
			}
		}
	}

	//����ABP���Ӽ��״̬
	void CABPSimulateBuild::Set_ABPWatchLinkState(BOOL bLinking)
	{
		m_bLinkWatchABP   = bLinking;
		boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
		if( m_pShowABPUpdate != NULL )
		{
			if( IsShowABPLinkState() )
			{
				m_pShowABPUpdate->OnAllLinkUpdateShow();
			}
			else 
			{
				m_pShowABPUpdate->OnAllUnLinkUpdateShow();
			}
		}
	}

}}}
