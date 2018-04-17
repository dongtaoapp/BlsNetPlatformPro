#include ".\opecgbuildinterface.h"
#include ".\ShowECGUpdateInterface.h"

namespace jysoft { namespace simulator { namespace base {

	COpECGBuildInterface::COpECGBuildInterface(void)
	{
		m_pShowECGUpdate  = NULL;
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
	// ������ cECGParams:  
	// ����ֵ:  
	void COpECGBuildInterface::OnModifyECGHandle(const CECGParams &cECGParams)
	{
		IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
		while ( pInterfaceVir != NULL )
		{
			if( pInterfaceVir->isKindOf( "COpECGBuildInterface" ) )
			{
				COpECGBuildInterface *pOpECGBuildInterface = (COpECGBuildInterface *)pInterfaceVir;
				pOpECGBuildInterface->ModifyECGHandle( cECGParams );
			}
			pInterfaceVir = pInterfaceVir->GetNextInterfacePtr();
		}
	}

	/*******************************************************************************/
	// �������ƣ� OnDirectModifyECGHandle
	// ���ܣ� ֱ���޸��ĵ�ͼ
	// ������ cECGParams: 
	//ע�� ���ĵ�ͼBuild��ʼ������ʱҲ�ô˺���
	// ����ֵ:  
	void COpECGBuildInterface::OnDirectModifyECGHandle(const CECGParams &cECGParams)
	{
		IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
		while ( pInterfaceVir != NULL )
		{
			if( pInterfaceVir->isKindOf( "COpECGBuildInterface" ) )
			{
				COpECGBuildInterface *pOpECGBuildInterface = (COpECGBuildInterface *)pInterfaceVir;
				pOpECGBuildInterface->DirectModifyECGHandle( cECGParams );
			}
			pInterfaceVir = pInterfaceVir->GetNextInterfacePtr();
		}
	}

	/*******************************************************************************/
	// �������ƣ� OnModifyECGInDefibrEventHandle
	// ���ܣ� ��Ϊ�������޸Ĳ���
	// ������ cECGParams: 
	// ����ֵ:  
	void COpECGBuildInterface::OnModifyECGInDefibrEventHandle(const CECGParams *pECGParams)
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

}}}
