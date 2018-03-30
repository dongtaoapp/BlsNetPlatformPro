#include ".\opecgbuildinterface.h"
#include ".\ShowECGUpdateInterface.h"

namespace jysoft { namespace simulator { namespace base {

	COpECGBuildInterface::COpECGBuildInterface(void)
	{
		m_pShowECGUpdate  = NULL;
		m_pSyncPnPFacilities    = NULL;
	}

	COpECGBuildInterface::~COpECGBuildInterface(void)
	{
	}

	bool COpECGBuildInterface::isKindOf(const std::string &className)
	{
		if( className == "COpECGBuildInterface" )
			return true;
		return COpInterfaceVir::isKindOf( className );
	}

	/*******************************************************************************/
	// �������ƣ� OnModifyECGHandle
	// ���ܣ� �޸��ĵ�ͼ
	// ������ CECGParams *pECGParams:       
	// ����ֵ:  
	void COpECGBuildInterface::OnModifyECGHandle(CECGParams *pECGParams)
	{
		IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
		while ( pInterfaceVir != NULL )
		{
			if( pInterfaceVir->isKindOf( "COpECGBuildInterface" ) )
			{
				COpECGBuildInterface *pOpECGBuildInterface = (COpECGBuildInterface *)pInterfaceVir;
				pOpECGBuildInterface->ModifyECGHandle( pECGParams );
			}
			pInterfaceVir = pInterfaceVir->GetNextInterfacePtr();
		}
	}

	/*******************************************************************************/
	// �������ƣ� OnDirectModifyECGHandle
	// ���ܣ� ֱ���޸��ĵ�ͼ
	// ������ CECGParams *pECGParams
	//ע�� ���ĵ�ͼBuild��ʼ������ʱҲ�ô˺���
	// ����ֵ:  
	void COpECGBuildInterface::OnDirectModifyECGHandle(CECGParams *pECGParams)
	{
		IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
		while ( pInterfaceVir != NULL )
		{
			if( pInterfaceVir->isKindOf( "COpECGBuildInterface" ) )
			{
				COpECGBuildInterface *pOpECGBuildInterface = (COpECGBuildInterface *)pInterfaceVir;
				pOpECGBuildInterface->DirectModifyECGHandle( pECGParams );
			}
			pInterfaceVir = pInterfaceVir->GetNextInterfacePtr();
		}
	}

	/*******************************************************************************/
	// �������ƣ� OnManualBuildExtrasystHandle
	// ���ܣ� �ֶ�����һ���粨
	// ������       
	// ����ֵ:  
	void COpECGBuildInterface::OnManualBuildExtrasystHandle()
	{
		IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
		while ( pInterfaceVir != NULL )
		{
			if( pInterfaceVir->isKindOf( "COpECGBuildInterface" ) )
			{
				COpECGBuildInterface *pOpECGBuildInterface = (COpECGBuildInterface *)pInterfaceVir;
				pOpECGBuildInterface->ManualBuildExtrasystHandle( );
			}
			pInterfaceVir = pInterfaceVir->GetNextInterfacePtr();
		}
	}
	/*******************************************************************************/
	// �������ƣ� OnModifyECGInDefibrEventHandle
	// ���ܣ� ��Ϊ�������޸Ĳ���
	// ������ CECGParams *pECGParams
	// ����ֵ:  
	void COpECGBuildInterface::OnModifyECGInDefibrEventHandle(CECGParams *pECGParams)
	{
		IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
		while ( pInterfaceVir != NULL )
		{
			if( pInterfaceVir->isKindOf( "COpECGBuildInterface" ) )
			{
				COpECGBuildInterface *pOpECGBuildInterface = (COpECGBuildInterface *)pInterfaceVir;
				pOpECGBuildInterface->ModifyECGInDefibrEventHandle( pECGParams );
			}
			pInterfaceVir = pInterfaceVir->GetNextInterfacePtr();
		}
	}
	/*******************************************************************************/
	// �������ƣ� OnStartPacingHandle
	// ���ܣ� ������
	// ������ 
	// ����ֵ:  
	void COpECGBuildInterface::OnStartPacingHandle(short sPaceHR)
	{
		IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
		while ( pInterfaceVir != NULL )
		{
			if( pInterfaceVir->isKindOf( "COpECGBuildInterface" ) )
			{
				COpECGBuildInterface *pOpECGBuildInterface = (COpECGBuildInterface *)pInterfaceVir;
				pOpECGBuildInterface->StartPacingHandle( sPaceHR );
			}
			pInterfaceVir = pInterfaceVir->GetNextInterfacePtr();
		}
	}
	/*******************************************************************************/
	// �������ƣ� OnStartPacingHandle
	// ���ܣ� �޸���Ƶ��
	// ������ 
	// ����ֵ:  
	void COpECGBuildInterface::OnModifyPacingRateHandle(long nPaceRate)
	{
		IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
		while ( pInterfaceVir != NULL )
		{
			if( pInterfaceVir->isKindOf( "COpECGBuildInterface" ) )
			{
				COpECGBuildInterface *pOpECGBuildInterface = (COpECGBuildInterface *)pInterfaceVir;
				pOpECGBuildInterface->ModifyPacingRateHandle( nPaceRate );
			}
			pInterfaceVir = pInterfaceVir->GetNextInterfacePtr();
		}
		m_cInterfaceMutex.Lock();
		if( m_pShowECGUpdate != NULL )
		{
			m_pShowECGUpdate->OnShowECGRate( (int)nPaceRate );
		}
		m_cInterfaceMutex.Unlock();
	}
	/*******************************************************************************/
	// �������ƣ� OnStopPacingHandle
	// ���ܣ� ֹͣ��
	// ������ 
	// ����ֵ: 
	void COpECGBuildInterface::OnStopPacingHandle()
	{
		IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
		while ( pInterfaceVir != NULL )
		{
			if( pInterfaceVir->isKindOf( "COpECGBuildInterface" ) )
			{
				COpECGBuildInterface *pOpECGBuildInterface = (COpECGBuildInterface *)pInterfaceVir;
				pOpECGBuildInterface->StopPacingHandle( );
			}
			pInterfaceVir = pInterfaceVir->GetNextInterfacePtr();
		}
	}

	/*******************************************************************************/
	// �������ƣ� SetRelateECGShowInterface
	// ���ܣ� �����ĵ�ͼ��ʾ�ӿ�
	// ������ CShowECGUpdateInterface *pShowECGInterface:       
	// ����ֵ:  
	//ע�� ͨ��CShowECGUpdateInterface�Ĵ���ָ�룬��������صĶ���ĵ�ͼ��ʾ�ӿ�
	void COpECGBuildInterface::SetRelateECGShowInterface(CShowECGUpdateInterface *pShowECGInterface)
	{
		m_cInterfaceMutex.Lock();
		if( m_pShowECGUpdate == NULL )
		{
			m_pShowECGUpdate  = pShowECGInterface;
		}
		else
		{
			m_pShowECGUpdate->SetNextInterfacePtr( pShowECGInterface );
		}
		m_cInterfaceMutex.Unlock();
	}

	//�Ͽ�ָ�����ĵ�ͼ��ʾ�ӿ�
	void COpECGBuildInterface::RemoveRelateECGShowInterface(CShowECGUpdateInterface *pRmvShowECGInterface)
	{
		m_cInterfaceMutex.Lock();
		if( m_pShowECGUpdate != NULL )
		{
			m_pShowECGUpdate = (CShowECGUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowECGUpdate, pRmvShowECGInterface);
		}
		m_cInterfaceMutex.Unlock();
	}

	/*******************************************************************************/
	// �������ƣ� OnModifyPnPFacility
	// ���ܣ� �ı��Ȳ���豸
	// ������ CSyncPnpFacilities *pSyncPnPFacilities: 
	// ����ֵ:  
	void COpECGBuildInterface::OnModifyPnPFacility(pnp::CSyncPnpFacilities *pSyncPnPFacilities)
	{
		if( pSyncPnPFacilities != NULL )
		{
			m_pSyncPnPFacilities = pSyncPnPFacilities;
		}
	}

	void COpECGBuildInterface::ModifyTransmitAddress(/*out*/short &sAddress)
	{
		if( m_pSyncPnPFacilities != NULL )
		{
			//ͬ�������޸�ͨѶָ���ת����ַ
            m_pSyncPnPFacilities->SyncModifyTransmitAddress(/*out*/sAddress, "Cardiogram_RealTimeData" );
		}
	}

}}}
