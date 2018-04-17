#include ".\respsimulatecanvas.h"

#include "..\SimulatorBase\IGetPhysioloySimulateData.h"
#include "..\SimulatorBase\IDistributeSimulateData.h"


using namespace jysoft::utility;
namespace jysoft { namespace simulator {
	CRespSimulateCanvas::CRespSimulateCanvas()
	{
		t = NULL;
		m_iMilliTime      = 0;;
		m_pDistributeData = NULL;
		m_pGetSimulateData = NULL;
		m_pPaneMoveControl = NULL;
		m_bStartDistribute = FALSE;
	}

	CRespSimulateCanvas::~CRespSimulateCanvas(void)
	{
		//�ͷŹ���
		FreeHook();
	}

	void CRespSimulateCanvas::InitialRespSimulate(IGetRespSimulateData *pSimulateData, IPaneMoveControlInterface *pMoveControlInterface, int iMilliTime/*=800*/)
	{
		//�ͷŹ���
		FreeHook();
		m_pPaneMoveControl    = pMoveControlInterface;
		m_pDistributeData     = NULL;
		m_pGetSimulateData    = pSimulateData;
		m_iMilliTime      = iMilliTime;;
	}


	//ֹͣ��������
	void CRespSimulateCanvas::StopTimerHandle()
	{
		if( t != NULL )
		{
			t->killTimer();
			delete t;
		}
		t = NULL;
	}

	//�ͷŹ���
	void CRespSimulateCanvas::FreeHook()
	{
		StopTimerHandle();
		m_bStartDistribute = false;
	}

	// ��ʼ�ַ�����ʵʱ����
	void CRespSimulateCanvas::StartDistributeSimulateData()
	{
		m_bStartDistribute = true;
		m_cMutex.Lock();
		if( m_pDistributeData )
		{
			m_pDistributeData->OnStartDistributeSimulateData();
		}
		if( m_pPaneMoveControl != NULL )
		{
			m_pPaneMoveControl->OnStart(TRUE);
		}
		m_cMutex.Unlock();
		//�趨��ʱ��
		t = new utility::CEmulateTimer(m_iMilliTime/10, boost::bind(&CRespSimulateCanvas::OnDistributeSimulateDataHandle, this));
		t->startTimer();
	}

	void CRespSimulateCanvas::OnDistributeSimulateDataHandle()
	{
		DWORD dwSize = 0;
		m_cMutex.Lock();
		if( m_pGetSimulateData )
		{
			//�õ����������ڵ����� hjg  2013.11.16 modify����ӵ�10msΪ�˾�����ʱ�������
			dwSize = m_pGetSimulateData->GetRespSimulateData(m_iMilliTime, m_fTempLeftLungBuffer, m_fTempSumLungBuffer);//��ʼλ��
			//m_pGetSimulateData->GetRespSimulateData(m_iMilliTime, NULL, NULL);
			for (DWORD dwItem = 0; dwItem < dwSize; ++dwItem)
			{
				m_fTempSumLungBuffer[dwItem] += m_fTempLeftLungBuffer[dwItem];
			}
		}
		if( dwSize != 0 )
		{
			if( m_pDistributeData != NULL )
			{
				m_pDistributeData->OnDistributeSimulateData(m_fTempSumLungBuffer,m_fTempLeftLungBuffer, dwSize);
			}
			if( m_pPaneMoveControl != NULL )
			{
				m_pPaneMoveControl->OnPaneMoveOp();
			}
		}
		m_cMutex.Unlock();
	}

	//ֹͣ�ַ�����ʵʱ����
	void CRespSimulateCanvas::StopDistributeSimulateData()
	{
		StopTimerHandle();
		m_bStartDistribute = false;
	}

	//��ʼ���Ӻ�������
	void CRespSimulateCanvas::OnStartWatchResp(IDistributeRespSimulateData *pDistributeData)
	{
		m_cMutex.Lock();
		if( m_pDistributeData == NULL )
		{
			m_pDistributeData = pDistributeData;
		}
		else if( pDistributeData != NULL )
		{
			m_pDistributeData->SetNextInterfacePtr( pDistributeData );
		}
		m_cMutex.Unlock();
	}

	//�Ͽ�������ļ��
	void CRespSimulateCanvas::OnCutWatchResp(IDistributeRespSimulateData *pCutDistributeData)
	{
		m_cMutex.Lock();
		if( m_pDistributeData != NULL )
		{
			m_pDistributeData = (IDistributeRespSimulateData *)IBedirecteLinksVir::RemoveInterfacePtr(m_pDistributeData, pCutDistributeData);
		}
		m_cMutex.Unlock();
	}
}}
