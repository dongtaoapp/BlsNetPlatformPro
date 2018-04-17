#include ".\simulatebuildaggregate.h"

#include "..\Common\ECGParams.h"

#include "..\SimulatorBase\ShowECGUpdateInterface.h"
#include "..\SimulatorBase\ShowSpO2UpdateInterface.h"
#include "..\SimulatorBase\ShowABPUpdateInterface.h"
#include "..\SimulatorBase\ShowEtCO2UpdateInterface.h"
#include "..\SimulatorBase\ShowRespRateUpdateInterface.h"
#include "..\SimulatorBase\WatchBarsShowInterfacesAggregate.h"


using namespace jysoft::utility;
using namespace jysoft::transLayer;
using namespace jysoft::simulator::base;
namespace jysoft { namespace simulator {

	CSimulateBuildAggregate::CSimulateBuildAggregate()
	{
		//�����ĵ�ͼģ�����ӿ�
		m_pOpECGBuildInterface  = dynamic_cast<COpECGBuildInterface *>(&m_cECGBuild);
		//Ѫ��ģ�����ӿ�
		m_pOpSpO2BuildInterface = dynamic_cast<COpSpO2BuildInterface *>(&m_cSpO2Build);
		//����������̼Ũ�ȷ�ѹģ�����ӿ�
		m_pEtCO2BuildInterface  = dynamic_cast<COpEtCO2BuildInterface *>(&m_cEtCO2Build);
		//����ģ�����ӿ�
		m_pRespBuildInterface   = dynamic_cast<COpRespBuildInterface *>(&m_cRespBuild);
		//�д�Ѫѹģ�����ӿ�
		m_pABPBuildInterface    = dynamic_cast<COpABPBuildInterface *>(&m_cABPBuild);

		//���ýӿڹ�ϵ
		IPaneMoveControlInterface  *pSpO2PaneMove = dynamic_cast<IPaneMoveControlInterface *>(&m_cSpO2SimulateCanvas);
		IPaneMoveControlInterface  *pABPPaneMove  = dynamic_cast<IPaneMoveControlInterface *>(&m_cABPSimulateCanvas);
		pSpO2PaneMove->SetNextInterfacePtr( pABPPaneMove );
	}

	CSimulateBuildAggregate::~CSimulateBuildAggregate(void)
	{
	}

	/*******************************************************************************/
	// �������ƣ� InitialPhysBuildsRelationAndResource
	// ���ܣ� ��ʼ��������������ص�ָ���趨��������Դ
	// ������
	//        
	// ����ֵ:  
	void CSimulateBuildAggregate::InitialPhysBuildsRelationAndResources(const std::string &resPath, transLayer::ITransportOrderIrpToSimulator *pTransportOrderIrp/*=NULL*/, SimulatePatientType ePatientType/*=SPT_Adult*/)
	{
		resourcePath = resPath;
		IPhysiologyStartSign  *pStartSignInterface = &m_cSpO2Build;
		IBedirecteLinksVir    *pABPStartSign  = dynamic_cast<IPhysiologyStartSign *>(&m_cABPBuild);
		pStartSignInterface->SetNextInterfacePtr(pABPStartSign);
		//�ĵ�ͼ������
		m_cECGBuild.SetEcgBuildRelateInterfacesPtr(pStartSignInterface, resPath, pTransportOrderIrp, ePatientType);
		//����ģ����
		m_cRespBuild.SetRespBuildRelateInterfacesPtr(&m_cEtCO2Build, resPath, pTransportOrderIrp, ePatientType);
		//---------------------------------------------------------------------------------------
		m_cEtCO2Build.setResouceFilePath( resPath );
		m_cSpO2Build.initialSpO2Sample( resPath );
		m_cABPBuild.initialABPSample( resPath );
	}

	//��ʼ����������ģ����
	void CSimulateBuildAggregate::InitialPhysBuilds()
	{
		//��ʼ���ĵ�ͼ
		CECGParams   cEcgParams;
		cEcgParams.m_dwField = PM_QRS|PM_BASICRHYTHM|PM_HR;
		m_cECGBuild.InitializeBuild(cEcgParams);
		//����������̼Ũ�ȷ�ѹģ����
		m_cEtCO2Build.InitializeBuild( 40 );
		//����ģ����
		m_cRespBuild.InitializeBuild(RM_Normal, 12);
	}

	//�ر���������ģ����
	void CSimulateBuildAggregate::ClosePhysBuilds()
	{
		//�ĵ�ͼģ����
		if( m_cECGBuild.IsInitialCardiogramBuild() )
		{
			m_cECGBuild.CloseCardiogramBuild();
		}
		//�ر�Ѫ��ģ����
		m_cSpO2Build.CloseSpO2SimulateBuild();
		//����ģ����
		m_cRespBuild.CloseRespSimulateBuild();
		//�ر�ABPģ����
		m_cABPBuild.CloseABPSimulateBuild();
	}

	/*******************************************************************************/
	// �������ƣ� StartSimulateBuild
	// ���ܣ� ����ģ�����ݵ����ɣ�������SpO2��ABPʵʱ����
	// ������
	//        CWnd  *pHootWnd: 
	// ����ֵ:  
	void CSimulateBuildAggregate::StartSimulateBuild()
	{
		IGetPhysioloySimulateData *pGetSpO2Data = m_cSpO2Build.Get_IGetPhysioloySimulateDataPtr();
		m_cSpO2SimulateCanvas.InitialSimulate(pGetSpO2Data);

		IGetPhysioloySimulateData *pGetABPData  = m_cABPBuild.Get_IGetPhysioloySimulateDataPtr();
		m_cABPSimulateCanvas.InitialSimulate( pGetABPData );

		IGetEcgSimulateData *pGetEcgData = m_cECGBuild.getIGetEcgLeadSimulateDataPtr();
		IPaneMoveControlInterface  *pSpO2PaneMovePtr = dynamic_cast<IPaneMoveControlInterface *>(&m_cSpO2SimulateCanvas);
		m_cEcgSimulateCanvas.InitialEcgSimulate( pGetEcgData, pSpO2PaneMovePtr, resourcePath);
		m_cEcgSimulateCanvas.StartDistributeSimulateData();
	
		//��������ʵʱ���ݵ����ɣ�������etCO2ʵʱ����
		IGetPhysioloySimulateData *pGetEtCO2Data = m_cEtCO2Build.Get_IGetPhysioloySimulateDataPtr();
		m_cEtCO2SimulateCanvas.InitialSimulate(pGetEtCO2Data, 800);

		IGetRespSimulateData   *pGetRespData  = m_cRespBuild.Get_IGetPhysioloySimulateDataPtr();
		m_cRespSimulateCanvas.InitialRespSimulate(pGetRespData, &m_cEtCO2SimulateCanvas);
		m_cRespSimulateCanvas.StartDistributeSimulateData();
	}

	//ֹͣģ�����ݵ�ʵʱ����
	void CSimulateBuildAggregate::StopSimulateBuilds()
	{
		//ֹͣ�ĵ�ͼ���ݵ�����
		m_cEcgSimulateCanvas.StopDistributeSimulateData();
		//ֹͣ�������ݵ�����
		m_cRespSimulateCanvas.StopDistributeSimulateData();
	}

	/*******************************************************************************/
	// �������ƣ� OnWatchECGHandle
	// ���ܣ� ����/�Ͽ��ĵ�ͼ�ļ���
	// ������
	//        IDistributeEcgLeadsSimulateData  *pDistributeECGInterface: �����ɷ��ӿ�
	//        CShowECGUpdateInterface *pInterface:
	//        BOOL bCutWatch:
	// ����ֵ:  
	void CSimulateBuildAggregate::OnWatchECGHandle(IDistributeEcgLeadsSimulateData  *pDistributeECGInterface, base::CShowECGUpdateInterface *pInterface, bool bCutWatch)
	{
		if( bCutWatch )
		{
			m_cEcgSimulateCanvas.OnCutWatchEcg( pDistributeECGInterface );
		}
		else
		{
			m_cEcgSimulateCanvas.OnStartWatchEcg( pDistributeECGInterface );
			if( pInterface != NULL )
			{
				//�Ƿ���ʾ���ɲ���
				if( !m_cECGBuild.IsShowEcgByLinkState() )
				{
					pInterface->OnAllUnLinkUpdateShow();
				}
				else
				{
					pInterface->OnAllLinkUpdateShow();
				}
			}
		}
	}

	/*******************************************************************************/
	// �������ƣ� OnWatchSpO2Handle
	// ���ܣ� ����/�Ͽ�SpO2�ļ���
	// ������
	//        IDistributeSimulateData  *pDistributeInterface: �����ɷ��ӿ�
	//        BOOL bCutWatch:
	// ����ֵ:  
	void CSimulateBuildAggregate::OnWatchSpO2Handle(IDistributeSimulateData  *pDistributeInterface, CShowSpO2UpdateInterface *pInterface, bool bCutWatch)
	{
		if( bCutWatch )
		{
			m_cSpO2SimulateCanvas.OnCutWatchPhyst( pDistributeInterface );
		}
		else
		{
			m_cSpO2SimulateCanvas.OnStartWatchPhyst( pDistributeInterface );
			if( pInterface != NULL )
			{
				//�Ƿ���ʾSpO2����
				if( !m_cSpO2Build.IsShowSpO2yLinkState() )
				{
					pInterface->OnAllUnLinkUpdateShow();
				}
				else
				{
					pInterface->OnAllLinkUpdateShow();
				}
			}
		}
	}

	/*******************************************************************************/
	// �������ƣ� OnWatchRespHandle
	// ���ܣ� ����/�Ͽ������ļ���
	// ������
	//        IDistributeSimulateData  *pDistributeInterface: �����ɷ��ӿ�
	//        BOOL bCutWatch:
	// ����ֵ: 
	void CSimulateBuildAggregate::OnWatchRespHandle(IDistributeRespSimulateData *pDistributeInterface, CShowRespRateUpdateInterface *pInterface, bool bCutWatch)
	{
		if( bCutWatch )
		{
			m_cRespSimulateCanvas.OnCutWatchResp( pDistributeInterface );
		}
		else
		{
			m_cRespSimulateCanvas.OnStartWatchResp( pDistributeInterface );
			if( pInterface != NULL )
			{
				//�Ƿ���ʾResp����
				if( !m_cRespBuild.IsShowRespLinkState() )
				{
					pInterface->OnAllUnLinkUpdateShow();
				}
				else
				{
					pInterface->OnAllLinkUpdateShow();
				}
			}
		}
	}

	/*******************************************************************************/
	// �������ƣ� OnWatchABPHandle
	// ���ܣ� ����/�Ͽ�ABP�ļ���
	// ������
	//        IDistributeSimulateData  *pDistributeInterface: �����ɷ��ӿ�
	//        CShowABPUpdateInterface *pInterface
	//        BOOL bCutWatch:
	// ����ֵ:  
	void CSimulateBuildAggregate::OnWatchABPHandle(IDistributeSimulateData  *pDistributeInterface, CShowABPUpdateInterface *pInterface, bool bCutWatch)
	{
		if( bCutWatch )
		{
			m_cABPSimulateCanvas.OnCutWatchPhyst( pDistributeInterface );
		}
		else
		{
			m_cABPSimulateCanvas.OnStartWatchPhyst( pDistributeInterface );
			if( pInterface != NULL )
			{
				//�Ƿ���ʾABP����
				if( !m_cABPBuild.IsShowABPLinkState() )
				{
					pInterface->OnAllUnLinkUpdateShow();
				}
				else
				{
					pInterface->OnAllLinkUpdateShow();
				}
			}
		}
	}

	/*******************************************************************************/
	// �������ƣ� OnWatchEtCO2Handle
	// ���ܣ� ����/�Ͽ������ļ���
	// ������
	//        IDistributeSimulateData  *pDistributeInterface: �����ɷ��ӿ�
	//        BOOL bCutWatch:
	// ����ֵ: 
	void CSimulateBuildAggregate::OnWatchEtCO2Handle(IDistributeSimulateData *pDistributeInterface, CShowEtCO2UpdateInterface *pInterface, bool bCutWatch)
	{
		if( bCutWatch )
		{
			m_cEtCO2SimulateCanvas.OnCutWatchPhyst( pDistributeInterface );
		}
		else
		{
			m_cEtCO2SimulateCanvas.OnStartWatchPhyst( pDistributeInterface );
			if( pInterface != NULL )
			{
				//�Ƿ���ʾEtCO2����
				if( !m_cEtCO2Build.IsShowEtCO2LinkState() )
				{
					pInterface->OnAllUnLinkUpdateShow();
				}
				else
				{
					pInterface->OnAllLinkUpdateShow();
				}
			}
		}
	}

	//�����Ƿ�����ĵ����Ӽ��
	void CSimulateBuildAggregate::Set_IsClearEcgWatchLink(bool bClear)
	{
		m_cECGBuild.Set_IsClearEcgWatchLink( bClear );
	}

	//�����ĵ����Ӽ��״̬
	void CSimulateBuildAggregate::Set_EcgWatchLinkState(bool bLinking)
	{
		m_cECGBuild.Set_EcgWatchLinkState( bLinking );
	}

	bool CSimulateBuildAggregate::Get_IsEcgWatchLink()
	{
		return m_cECGBuild.IsShowEcgByLinkState();
	}

	//�����Ƿ����SpO2���Ӽ��
	void CSimulateBuildAggregate::Set_IsClearSpO2WatchLink(bool bClear)
	{
		m_cSpO2Build.Set_IsClearSpO2WatchLink( bClear );
	}

	//����SpO2���Ӽ��״̬
	void CSimulateBuildAggregate::Set_SpO2WatchLinkState(bool bLinking)
	{
		m_cSpO2Build.Set_SpO2WatchLinkState( bLinking );
	}

	bool CSimulateBuildAggregate::Get_IsSpO2WatchLink()
	{
		return m_cSpO2Build.IsShowSpO2yLinkState();
	}

	//�����Ƿ����ABP���Ӽ��
	void CSimulateBuildAggregate::Set_IsClearABPWatchLink(bool bClear)
	{
		m_cABPBuild.Set_IsClearABPWatchLink( bClear );
	}

	//����ABP���Ӽ��״̬
	void CSimulateBuildAggregate::Set_ABPWatchLinkState(bool bLinking)
	{
		m_cABPBuild.Set_ABPWatchLinkState( bLinking );
	}

	//�����Ƿ����EtCO2���Ӽ��
	void CSimulateBuildAggregate::Set_IsClearEtCO2WatchLink(bool bClear)
	{
		m_cEtCO2Build.Set_IsClearEtCO2WatchLink( bClear );
	}
	//����EtCO2���Ӽ��״̬
	void CSimulateBuildAggregate::Set_EtCO2WatchLinkState(bool bLinking)
	{
		m_cEtCO2Build.Set_EtCO2WatchLinkState( bLinking );
	}

	//�����Ƿ����Resp���Ӽ��
	void CSimulateBuildAggregate::Set_IsClearRespWatchLink(bool bClear)
	{
		m_cRespBuild.Set_IsClearRespWatchLink( bClear );
	}

	//����Resp���Ӽ��״̬
	void CSimulateBuildAggregate::Set_RespWatchLinkState(bool bLinking)
	{
		m_cRespBuild.Set_RespWatchLinkState( bLinking );
	}

	/*******************************************************************************/
	// �������ƣ� StartLinkWatchBarsShowInterfaces
	// ���ܣ� ��ʼ����ģ����������ʾ�ӿ�
	// ������ CWatchBarsShowInterfacesAggregate *pShowAggregate:        
	// ����ֵ:  
	void CSimulateBuildAggregate::StartLinkWatchBarsShowInterfaces(CWatchBarsShowInterfacesAggregate *pShowAggregate)
	{
		COpPhysBuildInterfacesAggregate::StartLinkWatchBarsShowInterfaces( pShowAggregate );
		//���ģ������塰���֡�����ʾ�����ź�
		m_cECGBuild.InsertHeartStartSignPtr( pShowAggregate->Get_HeartStartSignInterface() );
	}

	/*******************************************************************************/
	// �������ƣ� UnLinkWatchBarsShowInterfaces
	// ���ܣ� �Ͽ�ģ����������ʾ�ӿ�
	// ������ CWatchBarsShowInterfacesAggregate *pShowAggregate:        
	// ����ֵ:  
	void CSimulateBuildAggregate::UnLinkWatchBarsShowInterfaces(CWatchBarsShowInterfacesAggregate *pShowAggregate)
	{
		COpPhysBuildInterfacesAggregate::UnLinkWatchBarsShowInterfaces( pShowAggregate );
		//�Ƴ�ģ������塰���֡�����ʾ�����ź�
		m_cECGBuild.RemoveHeartStartSignPtr( pShowAggregate->Get_HeartStartSignInterface() );
	}

	//��ѹ��ʼ\����(TRUE:��ʼ��FALSE:����)
	void CSimulateBuildAggregate::PressureStateAct(bool bState)
	{
		m_cEcgSimulateCanvas.SetPressureActState( bState );
	}

	//����CPR����
	void CSimulateBuildAggregate::FinishCPROperator(bool bSecceed)
	{
		//������ѹ
		PressureStateAct( false );
	}
}}
