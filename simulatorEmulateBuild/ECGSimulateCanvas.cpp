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
		//�ͷŹ���
		FreeHook();
	}

	void CECGSimulateCanvas::InitialEcgSimulate(IGetEcgSimulateData *pGetEcgSimulateData, IPaneMoveControlInterface *pMoveControlInterface, const std::string &resPath, int iMilliTime /*= 400*/)
	{
		//�ͷŹ���
		FreeHook();

		m_pPaneMoveControl       = pMoveControlInterface;
		m_pDistributeECGData     = NULL;
		m_pGetECGSimulateData    = pGetEcgSimulateData;
		m_iMilliTime             = iMilliTime;
		//���ذ�ѹʱ���ĵ�ͼ�ĸ�������
		std::string  strDisturbDataFile = resPath + _PRESSURE_FILE;
		InitialLoadPressureDisturbDatas( strDisturbDataFile );
	}

	//�ͷŹ���
	void CECGSimulateCanvas::FreeHook()
	{
		StopTimerHandle();
		m_bStartDistribute = false;
		m_bPressureAct     = false;
	}

	//ֹͣ��������
	void CECGSimulateCanvas::StopTimerHandle()
	{
		if( t != NULL )
		{
			t->killTimer();
			delete t;
		}
		t = NULL;
	}

	// ��ʼ�ַ��ĵ�ͼʵʱ����
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
		//�趨��ʱ��
		t = new utility::CEmulateTimer(m_iMilliTime/10, boost::bind(&CECGSimulateCanvas::OnDistributeSimulateDataHandle, this));
		t->startTimer();
	}

	void CECGSimulateCanvas::OnDistributeSimulateDataHandle()
	{
		short dwSize = 0;
		m_cMutex.Lock();
		if( m_pGetECGSimulateData )
		{
			//�õ����������ڵ����� hjg  2013.11.16 modify����ӵ�5msΪ�˾�����ʱ�������
			m_pGetECGSimulateData->GetI12LeadEcgSimulateData(m_iMilliTime, m_fTempBuffer);//��ʼλ��
			dwSize = m_pGetECGSimulateData->GetI12LeadEcgSimulateData(m_iMilliTime, NULL);//��ʼλ��
		}
		if( dwSize != 0 )
		{
			//���Ӱ�ѹʱ�����ĵ�ͼ������  hjg 2014.10.8 add
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

	//ֹͣ�ַ��ĵ�ͼʵʱ����
	void CECGSimulateCanvas::StopDistributeSimulateData()
	{
		StopTimerHandle();
		m_bStartDistribute = false;
	}

	//��ʼ�����ĵ�ͼ����
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

	//�Ͽ����ĵ�ͼ�ļ��
	void CECGSimulateCanvas::OnCutWatchEcg(IDistributeEcgLeadsSimulateData *pCutDistributeECGData)
	{
		m_cMutex.Lock();
		if( m_pDistributeECGData != NULL && pCutDistributeECGData != NULL )
		{
			m_pDistributeECGData = (IDistributeEcgLeadsSimulateData *)IBedirecteLinksVir::RemoveInterfacePtr(m_pDistributeECGData, pCutDistributeECGData);
		}
		m_cMutex.Unlock();
	}

	//��ѹ��ʼ\����(TRUE:��ʼ��FALSE:����)
	void CECGSimulateCanvas::SetPressureActState( bool bState )
	{
		m_bPressureAct = bState;
	}
	void CECGSimulateCanvas::OverlapPressureDisturbData( I12LeadSample *pEcgLeadSamples, short dwNumber )
	{
		BOOL  bUnStopDisturbDataOverlap = FALSE;
		//���Ӹ��������Ƿ�ûȫ��������
		bUnStopDisturbDataOverlap = m_cPressureDisturbDatas.GetNoneReadedNum() != m_cPressureDisturbDatas.GetCurrBufferNum() ? TRUE : FALSE;
		if( m_bPressureAct ||  bUnStopDisturbDataOverlap )
		{
			//��ȡ��������
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
			//�Բ�ͬ�ĵ��������Ӱ�ѹʱ�����ĵ�ͼ������
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
					//�������ݿռ�
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
