#include ".\generalsimulatecontroledcanvas.h"

#include "..\SimulatorBase\IGetPhysioloySimulateData.h"
#include "..\SimulatorBase\IDistributeSimulateData.h"


namespace jysoft { namespace simulator {

	CGeneralSimulateControledCanvas::CGeneralSimulateControledCanvas(void)
	{
		m_pGetSimulateData   = NULL;
		m_pDistributeData    = NULL;
		m_bStartDistribute   = FALSE;
	}

	CGeneralSimulateControledCanvas::~CGeneralSimulateControledCanvas(void)
	{
	}

	void CGeneralSimulateControledCanvas::InitialSimulate(IGetPhysioloySimulateData *pGetSimulateData, int iMilliTime/*=400*/)
	{
		m_pGetSimulateData = pGetSimulateData;
		m_iMilliTime       = iMilliTime;
		m_bStartDistribute = FALSE;
		m_pDistributeData  = NULL;
	}


	//�ƶ��컬������
	void CGeneralSimulateControledCanvas::PaneMoveOp()
	{
		DWORD dwSize = 0;
		if( m_pGetSimulateData )
		{
			//�õ����������ڵ�����
			dwSize = m_pGetSimulateData->GetPhysioloySimulateData(m_iMilliTime, m_fTempBuffer);//��ʼλ��
		}
		m_cMutex.Lock();
		if( m_pDistributeData && dwSize != 0 )
		{
			m_pDistributeData->OnDistributeSimulateData(m_fTempBuffer, dwSize);
		}
		m_cMutex.Unlock();
	}

	// ��ʼ���ĵ�ͼ
	void CGeneralSimulateControledCanvas::Start(bool bClear)
	{
		m_bStartDistribute = TRUE;
		m_cMutex.Lock();
		if( m_pDistributeData != NULL )
		{
			m_pDistributeData->OnStartDistributeSimulateData();
		}
		m_cMutex.Unlock();
	}

	//��ʼ����ʱʵ����
	void CGeneralSimulateControledCanvas::OnStartWatchPhyst(IDistributeSimulateData *pDistributeData)
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

	//�Ͽ���ʱʵ�ļ��
	void CGeneralSimulateControledCanvas::OnCutWatchPhyst(IDistributeSimulateData *pCutDistributeData)
	{
		m_cMutex.Lock();
		if( m_pDistributeData != NULL && pCutDistributeData != NULL )
		{
			m_pDistributeData = (IDistributeRespSimulateData *)IBedirecteLinksVir::RemoveInterfacePtr(m_pDistributeData, pCutDistributeData);
		}
		m_cMutex.Unlock();
	}
}}
