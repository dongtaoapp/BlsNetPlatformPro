#include <boost/assert.hpp>
#include ".\abpsimulatebuild.h"

#include "..\SimulatorBase\ShowABPUpdateInterface.h"


#define  MAX_DIFFH  30  //定义舒张压与收缩压之间的高度差，用于确定平均压的计算方式
#define  AVG_HEIGHT 20.0f  //当平均压收缩压差大于30时，用于计算平均压高度增加值

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
		//忽略ABP链接检查
		m_bClearWatchLink  = true;
		m_bLinkWatchABP    = false;
	}

	CABPSimulateBuild::~CABPSimulateBuild(void)
	{
		::HeapDestroy(m_hHeapHandle);
	}

	//初始化数据
	void CABPSimulateBuild::initialABPSample(const std::string &resPath)
	{
		std::string  strFilePath = resPath + _ABP_SAMPLE_FILE_1_;
		m_cSrcFirstABPSampleData.LoadSampleDataFromTxt( strFilePath );
		m_cCurrFirstABPSampleData.Clone( &m_cSrcFirstABPSampleData );

		strFilePath = resPath + _ABP_SAMPLE_FILE_2_;
		m_cSrcNextABPSampleData.LoadSampleDataFromTxt( strFilePath );
		m_cCurrNextABPSampleData.Clone(&m_cSrcNextABPSampleData);

		//计算比例关系，根据比例转化相关点
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
	//功能：血氧采样数据加载
	//参数：int nDifferMilliTime:          时间（0.1豪秒）
	//      int nQtoSMilliTime:            Q波到S波的时间（0.1豪秒）
	//      int nStoTMilliTime:            S波到T波的时间（0.1豪秒）
	//      int nCycleTime:                周期时间（0.1豪秒）
	//返回值:  
	void CABPSimulateBuild::StartPhysiologySimpleLoad(int nDifferMilliTime, int nQtoSMilliTime, int nStoTMilliTime, int nCycleTime)
	{	
		//m_nShrinkValue=60;
		//m_nStretchValue=60;
		int nSystolicTime = nQtoSMilliTime + nStoTMilliTime;
		//重新获取相关数据
		m_cSwapMutex.lock();
		m_cOutput.Clone(&m_cCurrFirstABPSampleData);
		m_cCurrFirstABPSampleData2.Clone(&m_cCurrFirstABPSampleData);
		m_cCurrNextABPSampleData.Clone(&m_cSrcNextABPSampleData);
		m_cSwapMutex.unlock();

		//根据时间，获取一个周期的ABP数据
		//GetABPOutputData(nSystolicTime,nCycleTime);
		GetABPOutputData(nQtoSMilliTime,nStoTMilliTime,nCycleTime);
		
		//将数据写入缓存
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
		//显示此时数值
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
		//当舒张压等于收缩压时
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
		//判断舒张压与收缩压是否相同
		if(m_nShrinkValue > m_nStretchValue)
		{
			float f = 0.0f;//第二段波峰的峰值
			//nFirstStartPos,nFirstStopPos,nFirstTime为第一段数据前半部分的起始点，接束点，以及经过拉升后实际的总时间
			//nNextStartPos,nNextStopPos,nNextTime为第一段数据后半部分的起始点，接束点，以及经过拉升后实际的总时间
			//nLastStartPos,nLastStopPos,nLastTime为第二段段数据的起始点，接束点，以及经过拉升后实际的总时间
			int nFirstStartPos,nFirstStopPos,nNextStartPos,nNextStopPos,nLastStartPos,nLastStopPos,nFirstTime,nNextTime,nLastTime;
			//获取前一段数据前半部分的起始点，接束点
			GetSampleDataPos(m_cOutput,m_fLastData,(float)m_nShrinkValue,nFirstStartPos,nFirstStopPos);
			//根据比例获取实际时间
			nFirstTime=nQtoSMilliTime*m_cOutput.m_dwSize/(nFirstStopPos-nFirstStartPos+1);
			//根据实际时间压缩数据
			m_cSwapMutex.lock();
			m_cOutput.ZoomSampleDataHandle(nFirstTime);
			m_cSwapMutex.unlock();
			//根据新的数据获取起始点和接束点
			GetSampleDataPos(m_cOutput,m_fLastData,(float)m_nShrinkValue,nFirstStartPos,nFirstStopPos);
			//获取第一段后半部分的结束点的数据
			float nMid=(float)(m_nStretchValue)+(float)((m_nShrinkValue-m_nStretchValue)*2/3);//计算前一段数据结束点的值
			GetSampleDataPos(m_cCurrFirstABPSampleData2,(float)m_nShrinkValue,(float)nMid,nNextStartPos,nNextStopPos);
			nNextTime=nStoTMilliTime*m_cCurrFirstABPSampleData2.m_dwSize/(nNextStopPos-nNextStartPos+1);
			m_cSwapMutex.lock();
			m_cCurrFirstABPSampleData2.ZoomSampleDataHandle(nNextTime);
			m_cSwapMutex.unlock();
			GetSampleDataPos(m_cCurrFirstABPSampleData2,(float)m_nShrinkValue,(float)nMid,nNextStartPos,nNextStopPos);
			//根据前一个点的结束点获取后一段的最高点
			if(nNextStopPos<nNextStartPos+2)
				f=m_cCurrFirstABPSampleData2.m_pPtrData[nNextStopPos]+0.00001f;
			else
			{
				f=(float)((m_nShrinkValue-m_cCurrFirstABPSampleData2.m_pPtrData[nNextStopPos])/4)+m_cCurrFirstABPSampleData2.m_pPtrData[nNextStopPos];
			}
			//对后一段数据进行拉升
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
			//根据各段数据的起始点结束点进行切割，然后连接
			m_cOutput.CutBefore(nFirstStartPos);
			m_cOutput.CutAfter(nFirstStopPos-nFirstStartPos);
			m_cCurrFirstABPSampleData2.CutBefore(nNextStartPos);
			m_cCurrFirstABPSampleData2.CutAfter(nNextStopPos-nNextStartPos);
			m_cCurrNextABPSampleData.CutBefore(nLastStartPos);
			m_cCurrNextABPSampleData.CutAfter(nLastStopPos-nLastStartPos);
		
		}
		else  //但收缩压都等于舒张压时,所有值都相等
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
	//功能：获取滑块区域内的曲线数据
	//参数：int iMilliTime:          时间（0.1豪秒）
	//      float *pcBuffer:         返回的曲线数据
	//返回值:  曲线数据的长度
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
				short dwActiveNum = 0;//实际返回的数据数
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
	// 函数名称： ModifyABPValue
	// 功能： 修改ABP的值
	// 参数：  
	// 返回值:  
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
			//修改血氧的采样数据
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

	//关闭ABP模拟器
	void CABPSimulateBuild::CloseABPSimulateBuild()
	{
		m_nShrinkValue=120;
		m_nStretchValue=80;
		m_cCurrFirstABPSampleData.Clone( &m_cSrcFirstABPSampleData );
		m_cCurrNextABPSampleData.Clone(&m_cSrcNextABPSampleData);
		m_DataBuffer.ResetBeginPosToReadBeginPos();
		m_DataBuffer.Empty();
	}

	//根据ABP链接状态，返回是否显示ABP数据
	bool CABPSimulateBuild::IsShowABPLinkState()
	{
		if( m_bClearWatchLink || m_bLinkWatchABP )
		{
			return true;
		}
		return false;
	}

	//设置是否忽略ABP链接检查
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

	//设置ABP链接检查状态
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
