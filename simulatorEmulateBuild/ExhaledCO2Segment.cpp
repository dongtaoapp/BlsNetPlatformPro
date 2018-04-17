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
	//���ܣ� �����ļ��ڵĺ�������
	//������ const CString &strFilePath: �����ļ�·��
	//����ֵ:  
	bool CExhaledCO2Segment::LoadOriginSegmentData(const std::string &strFilePath)
	{
		return m_cOriginCO2Segment.LoadSegmentData( strFilePath );
	}

	/*******************************************************************************/
	// �������ƣ� InitilaCO2Segment
	// ���ܣ� ����ʱ��������CO2��ģ���źŴ���
	// ������  
	//         int nMilliChangeTime: CO2������ʱ�䣨0.1���룩
	//         int nMilliOtherTime:  �������������ʱ�䣨0.1���룩
	// ����ֵ:  
	void CExhaledCO2Segment::InitilaCO2Segment(int nMilliChangeTime, int nMilliOtherTime)
	{
		m_nCurrentCO2Per = m_nCO2Percent;
		if( m_nCurrentCO2Per != 0 )
		{
			float fPreCO2Per = m_nCurrentCO2Per - m_nCurrentCO2Per*0.05f;
			Clone( &m_cOriginCO2Segment );
			//ѹ��ʱ��
			ZoomSegmentDataHandle( nMilliChangeTime );
			m_fRemainVolume  = 0.0f;
			m_fSumVolume     = m_pPtrData[m_dwSize-1];
			ZoomRespVolumeHandle(0.0f, fPreCO2Per);
			//ֱ���������
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

	//ֱ���������
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
