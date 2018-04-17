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


	//移动快滑动操作
	void CGeneralSimulateControledCanvas::PaneMoveOp()
	{
		DWORD dwSize = 0;
		if( m_pGetSimulateData )
		{
			//得到滑块区域内的数据
			dwSize = m_pGetSimulateData->GetPhysioloySimulateData(m_iMilliTime, m_fTempBuffer);//开始位置
		}
		m_cMutex.Lock();
		if( m_pDistributeData && dwSize != 0 )
		{
			m_pDistributeData->OnDistributeSimulateData(m_fTempBuffer, dwSize);
		}
		m_cMutex.Unlock();
	}

	// 开始绘心电图
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

	//开始监视时实波形
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

	//断开与时实的监控
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
