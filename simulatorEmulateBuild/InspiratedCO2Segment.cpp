#include ".\inspiratedco2segment.h"


namespace jysoft { namespace simulator { namespace etCO2 {

	CInspiratedCO2Segment::CInspiratedCO2Segment(void)
	{
	}

	CInspiratedCO2Segment::~CInspiratedCO2Segment(void)
	{
	}

	bool CInspiratedCO2Segment::isKindOf(const std::string &className )
	{ 
		if( className == "CInspiratedCO2Segment" )
			return true;
		return false;
	}

	/*******************************************************************************/
	//功能： 加载文件内的呼吸数据
	//参数： const CString &strFilePath: 数据文件路径
	//返回值:  
	bool CInspiratedCO2Segment::LoadOriginSegmentData(const std::string &strFilePath)
	{
		return m_cOriginCO2Segment.LoadSegmentData( strFilePath );
	}

	/*******************************************************************************/
	// 函数名称： InitilaCO2Segment
	// 功能： 呼吸时，产生对CO2的模拟信号处理
	// 参数：  int nCO2Per:          CO2百分比
	//         int nMilliChangeTime: CO2骤降的时间（0.1毫秒）
	//         int nMilliOtherTime:  骤降后接下来的时间（0.1毫秒）
	// 返回值:  
	void CInspiratedCO2Segment::InitilaCO2Segment(int nCO2Per, int nMilliChangeTime, int nMilliOtherTime)
	{
		if( nCO2Per > 0 )
		{
			Clone( &m_cOriginCO2Segment );
			//压缩时间
			ZoomSegmentDataHandle( nMilliChangeTime );
			m_fRemainVolume  = 0.0f;
			m_fSumVolume     = m_pPtrData[0];
			ZoomRespVolumeHandle(0.0f, nCO2Per * 1.0f);
			//直线延伸nMilliOtherTime时间操作
			HoriIntervalLinkData( nMilliOtherTime );
		}
		else
		{
			ResetEmptySegment();
		}
	
	}

	//直线延伸操作
	void  CInspiratedCO2Segment::HoriIntervalLinkData(int nTime)
	{
	#define DEFINITE                 0.0001
		int iNum = int(1.0f*nTime/10000*m_iSampleSec+DEFINITE);
		if( (m_dwSize + iNum ) > m_dwGlobalSize)
		{
			m_dwGlobalSize += iNum;
			m_dwGlobalSize =  (m_dwGlobalSize/256 + 1) * 256;
			m_pPtrData = (float *)::HeapReAlloc(m_hHandle,HEAP_ZERO_MEMORY,(void *)m_pPtrData,m_dwGlobalSize*sizeof(float));
		}
		float *pPtr = &m_pPtrData[m_dwSize];
		for(int i = 0;i < iNum; i++)
		{
			pPtr[i] = 0.0f; 
		}
		m_dwSize += iNum;
	}
}}}
