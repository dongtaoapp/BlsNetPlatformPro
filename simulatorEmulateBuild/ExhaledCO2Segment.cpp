#include ".\exhaledco2segment.h"


namespace jysoft { namespace simulator { namespace etCO2 {

	CExhaledCO2Segment::CExhaledCO2Segment(void)
	{
		m_nCO2Percent = 40;
		m_nCurrentCO2Per = 0;
	}

	CExhaledCO2Segment::~CExhaledCO2Segment(void)
	{
	}

	bool CExhaledCO2Segment::isKindOf(const std::string &className )
	{ 
		if( className == "CExhaledCO2Segment" )
			return true;
		return false;
	}

	/*******************************************************************************/
	//功能： 加载文件内的呼吸数据
	//参数： const CString &strFilePath: 数据文件路径
	//返回值:  
	bool CExhaledCO2Segment::LoadOriginSegmentData(const std::string &strFilePath)
	{
		return m_cOriginCO2Segment.LoadSegmentData( strFilePath );
	}

	/*******************************************************************************/
	// 函数名称： InitilaCO2Segment
	// 功能： 呼气时，产生对CO2的模拟信号处理
	// 参数：  
	//         int nMilliChangeTime: CO2骤升的时间（0.1毫秒）
	//         int nMilliOtherTime:  骤升后接下来的时间（0.1毫秒）
	// 返回值:  
	void CExhaledCO2Segment::InitilaCO2Segment(int nMilliChangeTime, int nMilliOtherTime)
	{
		m_nCurrentCO2Per = m_nCO2Percent;
		if( m_nCurrentCO2Per != 0 )
		{
			float fPreCO2Per = m_nCurrentCO2Per - m_nCurrentCO2Per*0.05f;
			Clone( &m_cOriginCO2Segment );
			//压缩时间
			ZoomSegmentDataHandle( nMilliChangeTime );
			m_fRemainVolume  = 0.0f;
			m_fSumVolume     = m_pPtrData[m_dwSize-1];
			ZoomRespVolumeHandle(0.0f, fPreCO2Per);
			//直线延伸操作
			LineIntervalLinkSampleData(m_nCurrentCO2Per*1.0f, nMilliOtherTime);
		}
		else
		{
			ResetEmptySegment();
		}
	}

	void CExhaledCO2Segment::Set_CO2Percent(int nValue)
	{
		m_nCO2Percent = nValue;
	}

	//直线延伸操作
	void  CExhaledCO2Segment::LineIntervalLinkSampleData(float fValue, int nIntervalTime)
	{
	#define DEFINITE                 0.0001
		float fPreCO2Per = m_pPtrData[m_dwSize-1];
		int iNum = int(1.0f*nIntervalTime/10000*m_iSampleSec+DEFINITE);
		if( (m_dwSize + iNum ) > m_dwGlobalSize)
		{
			m_dwGlobalSize += iNum;
			m_dwGlobalSize =  (m_dwGlobalSize/256 + 1) * 256;
			m_pPtrData = (float *)::HeapReAlloc(m_hHandle,HEAP_ZERO_MEMORY,(void *)m_pPtrData,m_dwGlobalSize*sizeof(float));
		}
		float *pPtr = &m_pPtrData[m_dwSize-1];
		for(int i = 1;i <= iNum; i++)
		{
			pPtr[i] = pPtr[i-1] + (fValue - fPreCO2Per)/iNum; 
		}
		m_dwSize += iNum;
	}
}}}
