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
		//释放钩子
		FreeHook();
	}

	void CRespSimulateCanvas::InitialRespSimulate(IGetRespSimulateData *pSimulateData, IPaneMoveControlInterface *pMoveControlInterface, int iMilliTime/*=800*/)
	{
		//释放钩子
		FreeHook();
		m_pPaneMoveControl    = pMoveControlInterface;
		m_pDistributeData     = NULL;
		m_pGetSimulateData    = pSimulateData;
		m_iMilliTime      = iMilliTime;;
	}


	//停止计数处理
	void CRespSimulateCanvas::StopTimerHandle()
	{
		if( t != NULL )
		{
			t->killTimer();
			delete t;
		}
		t = NULL;
	}

	//释放钩子
	void CRespSimulateCanvas::FreeHook()
	{
		StopTimerHandle();
		m_bStartDistribute = false;
	}

	// 开始分发呼吸实时数据
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
		//设定计时器
		t = new utility::CEmulateTimer(m_iMilliTime/10, boost::bind(&CRespSimulateCanvas::OnDistributeSimulateDataHandle, this));
		t->startTimer();
	}

	void CRespSimulateCanvas::OnDistributeSimulateDataHandle()
	{
		DWORD dwSize = 0;
		m_cMutex.Lock();
		if( m_pGetSimulateData )
		{
			//得到滑块区域内的数据 hjg  2013.11.16 modify，添加的10ms为了纠正定时器的误差
			dwSize = m_pGetSimulateData->GetRespSimulateData(m_iMilliTime, m_fTempLeftLungBuffer, m_fTempSumLungBuffer);//开始位置
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

	//停止分发呼吸实时数据
	void CRespSimulateCanvas::StopDistributeSimulateData()
	{
		StopTimerHandle();
		m_bStartDistribute = false;
	}

	//开始监视呼吸波形
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

	//断开与呼吸的监控
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
