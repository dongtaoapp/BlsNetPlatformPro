#include <fstream>
#include <boost/lexical_cast.hpp>
#include ".\ecgsimulatecanvas.h"

#define _PRESSURE_FILE  "\\cardiogram\\pressureDisturb.txt"

using namespace jysoft::utility;
namespace jysoft { namespace simulator { namespace ecg {

	CECGSimulateCanvas::CECGSimulateCanvas(void)
	{
		t = NULL;
		m_iMilliTime          = 0;;
		m_pDistributeECGData  = NULL;
		m_pGetECGSimulateData = NULL;
		m_pPaneMoveControl    = NULL;
		m_bStartDistribute    = false;
		m_bPressureAct     = false;
	}

	CECGSimulateCanvas::~CECGSimulateCanvas(void)
	{
		//释放钩子
		FreeHook();
	}

	void CECGSimulateCanvas::InitialEcgSimulate(IGetEcgSimulateData *pGetEcgSimulateData, IPaneMoveControlInterface *pMoveControlInterface, const std::string &resPath, int iMilliTime /*= 400*/)
	{
		//释放钩子
		FreeHook();

		m_pPaneMoveControl       = pMoveControlInterface;
		m_pDistributeECGData     = NULL;
		m_pGetECGSimulateData    = pGetEcgSimulateData;
		m_iMilliTime             = iMilliTime;
		//加载按压时对心电图的干扰数据
		std::string  strDisturbDataFile = resPath + _PRESSURE_FILE;
		InitialLoadPressureDisturbDatas( strDisturbDataFile );
	}

	//释放钩子
	void CECGSimulateCanvas::FreeHook()
	{
		StopTimerHandle();
		m_bStartDistribute = false;
		m_bPressureAct     = false;
	}

	//停止计数处理
	void CECGSimulateCanvas::StopTimerHandle()
	{
		if( t != NULL )
		{
			t->killTimer();
			delete t;
		}
		t = NULL;
	}

	// 开始分发心电图实时数据
	void CECGSimulateCanvas::StartDistributeSimulateData()
	{
		m_bStartDistribute = true;
		m_cMutex.Lock();
		if( m_pDistributeECGData )
		{
			m_pDistributeECGData->OnStartDistributeSimulateData();
		}
		if( m_pPaneMoveControl != NULL )
		{
			m_pPaneMoveControl->OnStart(true);
		}
		m_cMutex.Unlock();
		//设定计时器
		t = new utility::CEmulateTimer(m_iMilliTime/10, boost::bind(&CECGSimulateCanvas::OnDistributeSimulateDataHandle, this));
		t->startTimer();
	}

	void CECGSimulateCanvas::OnDistributeSimulateDataHandle()
	{
		short dwSize = 0;
		m_cMutex.Lock();
		if( m_pGetECGSimulateData )
		{
			//得到滑块区域内的数据 hjg  2013.11.16 modify，添加的5ms为了纠正定时器的误差
			m_pGetECGSimulateData->GetI12LeadEcgSimulateData(m_iMilliTime, m_fTempBuffer);//开始位置
			dwSize = m_pGetECGSimulateData->GetI12LeadEcgSimulateData(m_iMilliTime, NULL);//开始位置
		}
		if( dwSize != 0 )
		{
			//叠加按压时干扰心电图的数据  hjg 2014.10.8 add
			OverlapPressureDisturbData(m_fTempBuffer, dwSize);
			if( m_pDistributeECGData != NULL )
			{
				m_pDistributeECGData->OnDistributeEcgLeadsSimulateData(m_fTempBuffer, dwSize);
			}
			if( m_pPaneMoveControl != NULL )
			{
				m_pPaneMoveControl->OnPaneMoveOp();
			}
		}
		m_cMutex.Unlock();
	}

	//停止分发心电图实时数据
	void CECGSimulateCanvas::StopDistributeSimulateData()
	{
		StopTimerHandle();
		m_bStartDistribute = false;
	}

	//开始监视心电图波形
	void CECGSimulateCanvas::OnStartWatchEcg(IDistributeEcgLeadsSimulateData *pDistributeECGData)
	{
		m_cMutex.Lock();
		if( m_pDistributeECGData == NULL )
		{
			m_pDistributeECGData = pDistributeECGData;
		}
		else if( pDistributeECGData != NULL )
		{
			m_pDistributeECGData->SetNextInterfacePtr( pDistributeECGData );
		}
		m_cMutex.Unlock();
	}

	//断开与心电图的监控
	void CECGSimulateCanvas::OnCutWatchEcg(IDistributeEcgLeadsSimulateData *pCutDistributeECGData)
	{
		m_cMutex.Lock();
		if( m_pDistributeECGData != NULL && pCutDistributeECGData != NULL )
		{
			m_pDistributeECGData = (IDistributeEcgLeadsSimulateData *)IBedirecteLinksVir::RemoveInterfacePtr(m_pDistributeECGData, pCutDistributeECGData);
		}
		m_cMutex.Unlock();
	}

	//按压开始\结束(TRUE:开始；FALSE:结束)
	void CECGSimulateCanvas::SetPressureActState( bool bState )
	{
		m_bPressureAct = bState;
	}
	void CECGSimulateCanvas::OverlapPressureDisturbData( I12LeadSample *pEcgLeadSamples, short dwNumber )
	{
		BOOL  bUnStopDisturbDataOverlap = FALSE;
		//叠加干扰数据是否还没全部处理完
		bUnStopDisturbDataOverlap = m_cPressureDisturbDatas.GetNoneReadedNum() != m_cPressureDisturbDatas.GetCurrBufferNum() ? TRUE : FALSE;
		if( m_bPressureAct ||  bUnStopDisturbDataOverlap )
		{
			//读取干扰数据
			short dwReadSize = 0;
			float  *pTmpData = new float[dwNumber];
			m_cPressureDisturbDatas.ReadDataMovePtr(pTmpData, dwNumber, /*out*/&dwReadSize);
			if( dwReadSize < dwNumber )
			{
				m_cPressureDisturbDatas.ResetReadBeginPosPtr();
			}
			if( m_bPressureAct && dwReadSize < dwNumber )
			{
				m_cPressureDisturbDatas.ReadDataMovePtr(pTmpData+dwReadSize, dwNumber-dwReadSize);
				dwReadSize = dwNumber;
			}
			//对不同的导联都叠加按压时干扰心电图的数据
			for (short dwStep = 0; dwStep < dwReadSize; ++dwStep)
			{
#define _RATIO_VALUE      0.4f
				pEcgLeadSamples[dwStep].m_fSampleI = pEcgLeadSamples[dwStep].m_fSampleI * _RATIO_VALUE + pTmpData[dwStep];
				pEcgLeadSamples[dwStep].m_fSampleII = pEcgLeadSamples[dwStep].m_fSampleII * _RATIO_VALUE + pTmpData[dwStep];
				pEcgLeadSamples[dwStep].m_fSampleIII = pEcgLeadSamples[dwStep].m_fSampleIII * _RATIO_VALUE + pTmpData[dwStep];
				pEcgLeadSamples[dwStep].m_fSampleaVR = pEcgLeadSamples[dwStep].m_fSampleaVR * _RATIO_VALUE + pTmpData[dwStep];
				pEcgLeadSamples[dwStep].m_fSampleaVL = pEcgLeadSamples[dwStep].m_fSampleaVL * _RATIO_VALUE + pTmpData[dwStep];
				pEcgLeadSamples[dwStep].m_fSampleaVF = pEcgLeadSamples[dwStep].m_fSampleaVF * _RATIO_VALUE + pTmpData[dwStep];
				pEcgLeadSamples[dwStep].m_fSampleV1 = pEcgLeadSamples[dwStep].m_fSampleV1 * _RATIO_VALUE + pTmpData[dwStep];
				pEcgLeadSamples[dwStep].m_fSampleV2 = pEcgLeadSamples[dwStep].m_fSampleV2 * _RATIO_VALUE + pTmpData[dwStep];
				pEcgLeadSamples[dwStep].m_fSampleV3 = pEcgLeadSamples[dwStep].m_fSampleV3 * _RATIO_VALUE + pTmpData[dwStep];
				pEcgLeadSamples[dwStep].m_fSampleV4 = pEcgLeadSamples[dwStep].m_fSampleV4 * _RATIO_VALUE + pTmpData[dwStep];
				pEcgLeadSamples[dwStep].m_fSampleV5 = pEcgLeadSamples[dwStep].m_fSampleV5 * _RATIO_VALUE + pTmpData[dwStep];
				pEcgLeadSamples[dwStep].m_fSampleV6 = pEcgLeadSamples[dwStep].m_fSampleV6 * _RATIO_VALUE + pTmpData[dwStep];
			}	
		}
	}

	void CECGSimulateCanvas::InitialLoadPressureDisturbDatas( const std::string &strDisturbDataFile )
	{
#define   _BUFF_SIZE        300
		m_cPressureDisturbDatas.InitializeBuff( _BUFF_SIZE );
		std::ifstream  ifs( strDisturbDataFile.c_str() );
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
					//分配数据空间
					if( dwSumSize < _BUFF_SIZE )
					{
						m_cPressureDisturbDatas.WriteData(&fData, 1);
					}
					dwSumSize += 1;
				}
			} while (!strData.empty());
			ifs.close();
		}
		m_bPressureAct = false;
	}

}}}
