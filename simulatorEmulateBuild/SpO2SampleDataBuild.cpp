#include ".\spo2sampledatabuild.h"

#include "..\SimulatorBase\ShowSpO2UpdateInterface.h"



#define  _SPO2_SAMPLE_FILE_    "\\SpO2SimulateData\\SpO2SampleData.txt"

namespace jysoft { namespace simulator { namespace SpO2 {

	CSpO2SampleDataBuild::CSpO2SampleDataBuild(void)
	{
		m_hHeapHandle = ::HeapCreate(HEAP_NO_SERIALIZE,2000*sizeof(float),4000*sizeof(float));
		m_DataBuffer.InitializeBuff(m_cSrcSpO2SampleData.GetSampleNum(20*10000));
		m_nSpO2Value = 98;  //默认值
		//忽略SpO2链接检查
		m_bClearWatchLink  = true;
		m_bLinkWatchSpO2   = false;

		m_nReflushCalculate  = 0;
	}

	CSpO2SampleDataBuild::~CSpO2SampleDataBuild(void)
	{
		::HeapDestroy(m_hHeapHandle);
	}

	//初始化数据
	void CSpO2SampleDataBuild::initialSpO2Sample(const std::string &resPath)
	{
		//加载血氧采样数据
		std::string  strFilePath = resPath + _SPO2_SAMPLE_FILE_;
		m_cSrcSpO2SampleData.LoadSampleDataFromTxt( strFilePath );
		m_cCurrSpO2SampleData.Clone( &m_cSrcSpO2SampleData );

		float fCoefficient = m_nSpO2Value/98.1818f;
		for(long dwStep = 0; dwStep < m_cCurrSpO2SampleData.m_dwSize ; ++dwStep)
		{
			m_cCurrSpO2SampleData.m_pPtrData[dwStep] = m_cSrcSpO2SampleData.m_pPtrData[dwStep] * fCoefficient;
		}
	}

	/*******************************************************************************
	//功能：获取滑块区域内的曲线数据
	//参数：int iMilliTime:          时间（0.1豪秒）
	//      float *pcBuffer:         返回的曲线数据
	//返回值:  曲线数据的长度
	*********************************************************************************/
	unsigned long CSpO2SampleDataBuild::GetPhysioloySimulateData(int iMilliTime, /*out*/float *pcBuffer /*= NULL*/)
	{
		short dwRtSize = m_cCurrSpO2SampleData.GetSampleNum(iMilliTime);
		if( pcBuffer != NULL )
		{
			m_cSwapMutex.lock();
			short dwActiveNum = 0;//实际返回的数据数
			short dwRemainBuffNum = m_DataBuffer.GetNoneReadedNum();
			if( dwRemainBuffNum > 0 ) 
			{
				m_DataBuffer.ReadDataMovePtr(pcBuffer,dwRtSize,&dwActiveNum);
			}
			if( !IsShowSpO2yLinkState() )
			{
				::memset(pcBuffer, 0, dwActiveNum*sizeof(float) );
			}
			if( dwRtSize > dwActiveNum)
			{
				for (DWORD dwItem = dwActiveNum; dwItem < dwRtSize; ++dwItem)
				{
					pcBuffer[dwItem] = 0.0f;
				}
			}
			m_cSwapMutex.unlock();
			m_nReflushCalculate += iMilliTime;
			if( m_nReflushCalculate >= 0 )
			{
				if( m_nReflushCalculate > 10000 )
				{
					//显示血氧的数值
					boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
					if( m_pShowSpO2Update )
					{
						m_pShowSpO2Update->OnShowSpO2Value( m_nSpO2Value );
					}
					m_nReflushCalculate  = 0;
				}
			}
		}
		return dwRtSize;
	}

	/*******************************************************************************/
	//功能：血氧采样数据加载
	//参数：int nDifferMilliTime:          时间（0.1豪秒）
	//      int nQtoSMilliTime:            Q波到S波的时间（0.1豪秒）
	//      int nStoTMilliTime:            S波到T波的时间（0.1豪秒）
	//      int nCycleTime:                周期时间（0.1豪秒）
	//返回值:  
	void CSpO2SampleDataBuild::StartPhysiologySimpleLoad(int nDifferMilliTime, int nQtoSMilliTime, int nStoTMilliTime, int nCycleTime)
	{
		if( !m_cCurrSpO2SampleData.IsEmpty() )
		{
			float fCompareValue = 0.0f;
		
			boost::mutex::scoped_lock lock(m_cSwapMutex);
			short dwRtSize = m_cCurrSpO2SampleData.GetSampleNum(nDifferMilliTime);
			float *fBeginValue = new float[dwRtSize+8];
			for(int i = 0; i < dwRtSize+8; ++i)
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
			for(; dwStep < m_cCurrSpO2SampleData.m_dwSize-1 ; ++dwStep)
			{
				float fSampleData = m_cCurrSpO2SampleData.m_pPtrData[dwStep];
				float fNextSampleData = m_cCurrSpO2SampleData.m_pPtrData[dwStep+1];
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
				float *fDstPtr = m_cCurrSpO2SampleData.m_pPtrData+dwStep;
				for(short n=0; n < dwRtSize; ++n)
				{
					fBeginValue[n+dwOverlapSize] = (fDstPtr[n]+fBeginValue[n+dwOverlapSize])/2;
				}
				m_DataBuffer.WriteData(fBeginValue, dwOverlapSize+dwRtSize);
				fDstPtr= fDstPtr + dwRtSize;
				m_DataBuffer.WriteData(fDstPtr, m_cCurrSpO2SampleData.m_dwSize-dwStep-dwRtSize);
			}
			delete [] fBeginValue;
		}
		//显示血氧的数值
		boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
		m_nReflushCalculate  = -20000;
		if( m_pShowSpO2Update )
		{
			m_pShowSpO2Update->OnShowSpO2Value( m_nSpO2Value );
		}
	}


	CSample * CSpO2SampleDataBuild::GetCurrSamplePtr(void)
	{
		return &m_cCurrSpO2SampleData;
	}

	/*******************************************************************************/
	// 函数名称： ModifySpO2ValuePrecent
	// 功能： 修改血氧的百分比浓度
	// 参数：  int nSpO2Value:            血氧百分比浓度值
	// 返回值:  
	void CSpO2SampleDataBuild::ModifySpO2ValuePrecent( int nSpO2Value )
	{
		if( m_nSpO2Value != nSpO2Value )
		{
			//修改血氧的采样数据
			boost::mutex::scoped_lock lock(m_cSwapMutex);
			float fCoefficient = nSpO2Value == 0 ? 0.0f : nSpO2Value/98.1818f;
			for(short dwStep = 0; dwStep < m_cCurrSpO2SampleData.m_dwSize ; ++dwStep)
			{
				m_cCurrSpO2SampleData.m_pPtrData[dwStep] = m_cSrcSpO2SampleData.m_pPtrData[dwStep] * fCoefficient;
			}
			m_nSpO2Value = nSpO2Value;
		}
	}

	//关闭血氧模拟器
	void CSpO2SampleDataBuild::CloseSpO2SimulateBuild()
	{
		m_nSpO2Value = 98;  //默认值
		m_cCurrSpO2SampleData.Clone( &m_cSrcSpO2SampleData );

		float fCoefficient = m_nSpO2Value/98.1818f;
		for(DWORD dwStep = 0; dwStep < m_cCurrSpO2SampleData.m_dwSize ; ++dwStep)
		{
			m_cCurrSpO2SampleData.m_pPtrData[dwStep] = m_cSrcSpO2SampleData.m_pPtrData[dwStep] * fCoefficient;
		}
		m_DataBuffer.ResetBeginPosToReadBeginPos();
		m_DataBuffer.Empty();
	}

	//根据SpO2链接状态，返回是否显示SpO2数据
	bool CSpO2SampleDataBuild::IsShowSpO2yLinkState()
	{
		if( m_bClearWatchLink || m_bLinkWatchSpO2 )
		{
			return true;
		}
		return false;
	}

	//设置是否忽略SpO2链接检查
	void CSpO2SampleDataBuild::Set_IsClearSpO2WatchLink(bool bClear)
	{
		m_bClearWatchLink  = bClear;
		boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
		if( m_pShowSpO2Update != NULL )
		{
			if( IsShowSpO2yLinkState() )
			{
				m_pShowSpO2Update->OnAllLinkUpdateShow();
			}
			else 
			{
				m_pShowSpO2Update->OnAllUnLinkUpdateShow();
			}
		}
	}

	//设置SpO2链接检查状态
	void CSpO2SampleDataBuild::Set_SpO2WatchLinkState(bool bLinking)
	{
		if( m_bLinkWatchSpO2 != bLinking )
		{
			m_bLinkWatchSpO2   = bLinking;
			boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
			if( m_pShowSpO2Update != NULL )
			{
				if( IsShowSpO2yLinkState() )
				{
					m_pShowSpO2Update->OnAllLinkUpdateShow();
				}
				else 
				{
					m_pShowSpO2Update->OnAllUnLinkUpdateShow();
				}
			}
		}
	}
}}}
