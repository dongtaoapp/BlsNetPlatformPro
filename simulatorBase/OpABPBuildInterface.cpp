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
		boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
		if( m_pShowABPUpdate == NULL )
		{
			m_pShowABPUpdate   =  pShowInterface;
		}
		else
		{
			m_pShowABPUpdate->SetNextInterfacePtr( pShowInterface );
		}
	}

	//�Ͽ�ָ����ABP��ʾ�ӿ�
	void COpABPBuildInterface::RemoveRelateABPShowInterface(CShowABPUpdateInterface *pRmvShowInterface)
	{
		boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
		if( m_pShowABPUpdate != NULL )
		{
			m_pShowABPUpdate = (CShowABPUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowABPUpdate, pRmvShowInterface);
		}
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
		boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
		if( m_pShowABPUpdate != NULL )
		{
			m_pShowABPUpdate->OnShowABPValue(nShrinkValue, nStretchValue);
		}
	}

}}}
