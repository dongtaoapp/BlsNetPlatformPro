#include ".\opabpbuildinterface.h"
#include ".\ShowABPUpdateInterface.h"

namespace jysoft { namespace simulator { namespace base {

	COpABPBuildInterface::COpABPBuildInterface(void)
	{
		m_pShowABPUpdate  = NULL;
	}

	COpABPBuildInterface::~COpABPBuildInterface(void)
	{
	}

	bool COpABPBuildInterface::isKindOf(const std::string &className)
	{
		if( className == "COpABPBuildInterface" )
		{
			return true;
		}
		return COpInterfaceVir::isKindOf( className );
	}

	/*******************************************************************************/
	// �������ƣ� SetRelateABPShowInterface
	// ���ܣ� ����ABP��ʾ�ӿ�
	// ������ CShowABPUpdateInterface *pShowInterface:       
	// ����ֵ:  
	//ע�� ͨ��CShowABPUpdateInterface�Ĵ���ָ�룬��������صĶ��ABP��ʾ�ӿ�
	void COpABPBuildInterface::SetRelateABPShowInterface(CShowABPUpdateInterface *pShowInterface)
	{
		m_cInterfaceMutex.Lock();
		if( m_pShowABPUpdate == NULL )
		{
			m_pShowABPUpdate   =  pShowInterface;
		}
		else
		{
			m_pShowABPUpdate->SetNextInterfacePtr( pShowInterface );
		}
		m_cInterfaceMutex.Unlock();
	}

	//�Ͽ�ָ����ABP��ʾ�ӿ�
	void COpABPBuildInterface::RemoveRelateABPShowInterface(CShowABPUpdateInterface *pRmvShowInterface)
	{
		m_cInterfaceMutex.Lock();
		if( m_pShowABPUpdate != NULL )
		{
			m_pShowABPUpdate = (CShowABPUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowABPUpdate, pRmvShowInterface);
		}
		m_cInterfaceMutex.Unlock();
	}

	//�޸�ABP��ֵ
	void COpABPBuildInterface::OnModifyABPValue(int nShrinkValue, int nStretchValue)
	{
		IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
		while ( pInterfaceVir != NULL )
		{
			if( pInterfaceVir->isKindOf( "COpABPBuildInterface" ) )
			{
				COpABPBuildInterface *pOpABPBuildInterface = (COpABPBuildInterface *)pInterfaceVir;
				pOpABPBuildInterface->ModifyABPValue( nShrinkValue, nStretchValue );
			}
			pInterfaceVir = pInterfaceVir->GetNextInterfacePtr();
		}
		m_cInterfaceMutex.Lock();
		if( m_pShowABPUpdate != NULL )
		{
			m_pShowABPUpdate->OnShowABPValue(nShrinkValue, nStretchValue);
		}
		m_cInterfaceMutex.Unlock();
	}

}}}
