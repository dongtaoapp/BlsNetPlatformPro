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
	//���ܣ� �����ļ��ڵĺ�������
	//������ const CString &strFilePath: �����ļ�·��
	//����ֵ:  
	bool CInspiratedCO2Segment::LoadOriginSegmentData(const std::string &strFilePath)
	{
		return m_cOriginCO2Segment.LoadSegmentData( strFilePath );
	}

	/*******************************************************************************/
	// �������ƣ� InitilaCO2Segment
	// ���ܣ� ����ʱ��������CO2��ģ���źŴ���
	// ������  int nCO2Per:          CO2�ٷֱ�
	//         int nMilliChangeTime: CO2�轵��ʱ�䣨0.1���룩
	//         int nMilliOtherTime:  �轵���������ʱ�䣨0.1���룩
	// ����ֵ:  
	void CInspiratedCO2Segment::InitilaCO2Segment(int nCO2Per, int nMilliChangeTime, int nMilliOtherTime)
	{
		if( nCO2Per > 0 )
		{
			Clone( &m_cOriginCO2Segment );
			//ѹ��ʱ��
			ZoomSegmentDataHandle( nMilliChangeTime );
			m_fRemainVolume  = 0.0f;
			m_fSumVolume     = m_pPtrData[0];
			ZoomRespVolumeHandle(0.0f, nCO2Per * 1.0f);
			//ֱ������nMilliOtherTimeʱ�����
			HoriIntervalLinkData( nMilliOtherTime );
		}
		else
		{
			ResetEmptySegment();
		}
	
	}

	//ֱ���������
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
