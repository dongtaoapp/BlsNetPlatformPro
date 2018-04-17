#include ".\oprespbuildinterface.h"

#include "..\elementParse\SAction_Resp.h"

namespace jysoft { namespace simulator { namespace base {

	COpRespBuildInterface::COpRespBuildInterface(void)
	{
		m_pShowRespUpdate  = NULL;
		m_pSyncPnPFacilities = NULL;
	}

	COpRespBuildInterface::~COpRespBuildInterface(void)
	{
	}

	bool COpRespBuildInterface::isKindOf(const std::string &className)
	{
		if( className == "COpRespBuildInterface" )
		{
			return true;
		}
		return COpInterfaceVir::isKindOf( className );
	}

	/*******************************************************************************/
	// �������ƣ� OnModifyRespRate
	// ���ܣ� �޸ĺ�������
	// ������  int nBreathRate:            ������������λ����/���ӣ�
	// ����ֵ:  
	void COpRespBuildInterface::OnModifyRespRate(int nBreathRate)
	{
		IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
		while ( pInterfaceVir != NULL )
		{
			if( pInterfaceVir->isKindOf( "COpRespBuildInterface" ) )
			{
				COpRespBuildInterface *pOpRespBuildInterface = (COpRespBuildInterface *)pInterfaceVir;
				pOpRespBuildInterface->ModifyRespRate( nBreathRate );
			}
			pInterfaceVir = pInterfaceVir->GetNextInterfacePtr();
		}
	}

	/*******************************************************************************/
	// �������ƣ� OnModifyRespBuildType
	// ���ܣ� �޸����ͼ�����
	// ������  eRespMode eMode:            ��������
	//         int nBreathRate:                       ������������λ����/���ӣ�
	// ����ֵ:  
	void COpRespBuildInterface::OnModifyRespBuildType(eRespMode eMode, int nBreathRate)
	{
		IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
		while ( pInterfaceVir != NULL )
		{
			if( pInterfaceVir->isKindOf( "COpRespBuildInterface" ) )
			{
				COpRespBuildInterface *pOpRespBuildInterface = (COpRespBuildInterface *)pInterfaceVir;
				pOpRespBuildInterface->ModifyRespBuildType( eMode, nBreathRate );
			}
			pInterfaceVir = pInterfaceVir->GetNextInterfacePtr();
		}
	}

	/*******************************************************************************/
	// �������ƣ� SetRelateRespRateShowInterface
	// ���ܣ� ���Ӻ���������ʾ�ӿ�
	// ������ CShowRespRateUpdateInterface *pShowInterface:       
	// ����ֵ:  
	//ע�� ͨ��CShowRespRateUpdateInterface�Ĵ���ָ�룬��������صĶ������������ʾ�ӿ�
	void COpRespBuildInterface::SetRelateRespRateShowInterface(CShowRespRateUpdateInterface *pShowInterface)
	{
		boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
		if ( m_pShowRespUpdate == NULL )
		{
			m_pShowRespUpdate = pShowInterface;
		}
		else
		{
			m_pShowRespUpdate->SetNextInterfacePtr( pShowInterface );
		}
	}

	//�Ͽ�ָ���ĺ���������ʾ�ӿ�
	void COpRespBuildInterface::RemoveRelateRespRateShowInterface(CShowRespRateUpdateInterface *pRmvShowInterface)
	{
		boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
		if( m_pShowRespUpdate != NULL )
		{
			m_pShowRespUpdate = (CShowRespRateUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowRespUpdate, pRmvShowInterface);
		}
	}

	/*******************************************************************************/
	// �������ƣ� OnModifyPnPFacility
	// ���ܣ� �ı��Ȳ���豸
	// ������ CSyncPnpFacilities *pSyncPnPFacilities:       
	// ����ֵ:  
	void COpRespBuildInterface::OnModifyPnPFacility(pnp::CSyncPnpFacilities *pSyncPnPFacilities)
	{
		if( pSyncPnPFacilities != NULL )
		{
			m_pSyncPnPFacilities = pSyncPnPFacilities;
		}
	}

	void COpRespBuildInterface::ModifyTransmitAddress(/*out*/short &sAddress)
	{
		if( m_pSyncPnPFacilities != NULL )
		{
			//ͬ�������޸�ͨѶָ���ת����ַ
			std::string  symptomCaption = CSAction_Resp::getAction_Resp_Caption();
			m_pSyncPnPFacilities->SyncModifyTransmitAddress(/*out*/sAddress, symptomCaption );
		}
	}

}}}
