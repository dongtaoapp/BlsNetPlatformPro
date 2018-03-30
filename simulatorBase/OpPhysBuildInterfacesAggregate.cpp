#include ".\opphysbuildinterfacesaggregate.h"
#include ".\WatchBarsShowInterfacesAggregate.h"

using namespace jysoft::simulator::base;

namespace jysoft { namespace simulator {

	COpPhysBuildInterfacesAggregate::COpPhysBuildInterfacesAggregate(void)
	{
		m_pOpECGBuildInterface    =  NULL;
		m_pOpSpO2BuildInterface   =  NULL;
		m_pEtCO2BuildInterface    =  NULL;
		m_pRespBuildInterface     =  NULL;
		m_pABPBuildInterface      =  NULL;
	}

	COpPhysBuildInterfacesAggregate::~COpPhysBuildInterfacesAggregate(void)
	{
	
	}

	/*******************************************************************************/
	// �������ƣ� StartLinkWatchBarsShowInterfaces
	// ���ܣ� ��ʼ����ģ����������ʾ�ӿ�
	// ������ CWatchBarsShowInterfacesAggregate *pShowAggregate:        
	// ����ֵ:  
	void COpPhysBuildInterfacesAggregate::StartLinkWatchBarsShowInterfaces(CWatchBarsShowInterfacesAggregate *pShowAggregate)
	{
		//�����ĵ�ͼ��Ϣ��ʾ�ӿ�
		m_pOpECGBuildInterface->SetRelateECGShowInterface( pShowAggregate->Get_ShowHRUpdateInterfacePtr() );
		//Ѫ����Ϣ��ʾ�ӿ�
		m_pOpSpO2BuildInterface->SetRelateSpO2ShowInterface( pShowAggregate->Get_ShowSpO2ValueUpdateInterfacePtr() );
		//����������Ϣ��ʾ�ӿ�
		CShowRespRateUpdateInterface *pShowRespRateInterface  = pShowAggregate->Get_ShowRespRateUpdateInterfacePtr();
		m_pRespBuildInterface->SetRelateRespRateShowInterface( pShowRespRateInterface );
		//etCO2Ũ����Ϣ��ʾ�ӿ�
		CShowEtCO2UpdateInterface *pShowEtCO2Interface = pShowAggregate->Get_ShowEtCO2ValueUpdateInterfacePtr();
		m_pEtCO2BuildInterface->SetRelateEtCO2ShowInterface( pShowEtCO2Interface );
		//....
		m_pABPBuildInterface->SetRelateABPShowInterface( pShowAggregate->Get_ShowABPValueUpdateInterfacePtr() );

	}

	/*******************************************************************************/
	// �������ƣ� UnLinkWatchBarsShowInterfaces
	// ���ܣ� �Ͽ�ģ����������ʾ�ӿ�
	// ������ CWatchBarsShowInterfacesAggregate *pShowAggregate:        
	// ����ֵ:  
	void COpPhysBuildInterfacesAggregate::UnLinkWatchBarsShowInterfaces(CWatchBarsShowInterfacesAggregate *pShowAggregate)
	{
		//�����ĵ�ͼ��Ϣ��ʾ�ӿ�
		CShowECGUpdateInterface *pShowHRInterface = pShowAggregate->Get_ShowHRUpdateInterfacePtr();
		if( pShowHRInterface != NULL )
		{
			m_pOpECGBuildInterface->RemoveRelateECGShowInterface( pShowHRInterface );
			pShowHRInterface->UnLinkUpdateShow();
		}
		//Ѫ����Ϣ��ʾ�ӿ�
		CShowSpO2UpdateInterface *pShowSpO2Interface  = pShowAggregate->Get_ShowSpO2ValueUpdateInterfacePtr();
		if( pShowSpO2Interface != NULL )
		{
			m_pOpSpO2BuildInterface->RemoveRelateSpO2ShowInterface( pShowSpO2Interface );
			pShowSpO2Interface->UnLinkUpdateShow();
		}
		//ABP��Ϣ��ʾ�ӿ�
		CShowABPUpdateInterface *pShowABPInterface  = pShowAggregate->Get_ShowABPValueUpdateInterfacePtr();
		if( pShowABPInterface != NULL )
		{
			m_pABPBuildInterface->RemoveRelateABPShowInterface( pShowABPInterface );
			pShowABPInterface->UnLinkUpdateShow();
		}
		//����������Ϣ��ʾ�ӿ�
		CShowRespRateUpdateInterface *pShowRespRateInterface  = pShowAggregate->Get_ShowRespRateUpdateInterfacePtr();
		if( pShowRespRateInterface != NULL )
		{
			m_pRespBuildInterface->RemoveRelateRespRateShowInterface( pShowRespRateInterface );
			pShowRespRateInterface->UnLinkUpdateShow();
		}
		//etCO2Ũ����Ϣ��ʾ�ӿ�
		CShowEtCO2UpdateInterface *pShowEtCO2Interface  = pShowAggregate->Get_ShowEtCO2ValueUpdateInterfacePtr();
		if( pShowEtCO2Interface != NULL )
		{
			m_pEtCO2BuildInterface->RemoveRelateEtCO2ShowInterface( pShowEtCO2Interface );
			pShowEtCO2Interface->UnLinkUpdateShow();
		}
	}

}}
