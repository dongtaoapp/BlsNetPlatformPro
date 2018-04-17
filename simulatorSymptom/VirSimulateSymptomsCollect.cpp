#include <algorithm>
#include <boost/format.hpp>
#include ".\virsimulatesymptomscollect.h"
#include ".\XActionVirtual.h"

#include "..\ElementParse\SAction_ABP.h"
#include "..\ElementParse\SAction_Osat.h"
#include "..\ElementParse\SAction_Resp.h"
#include "..\ElementParse\SAction_etCO2.h"
#include "..\ElementParse\SAction_ECG.h"
#include "..\ElementParse\SAction_Pupil.h"
#include "..\ElementParse\SAction_Temperature.h"
#include "..\ElementParse\SAction_FrameTime.h"
#include "..\ElementParse\SAction_FrameTime.h"
#include "..\ElementParse\SEvent_Defibr.h"
#include "..\ElementParse\SEvent_Pace.h"
#include "..\ElementParse\SAction_Pace.h"

#include "..\Common\PatientRuleInterfaceGlobal.h"
#include "..\Common\patienttypefactory.h"
#include "..\Common\EncodeConv.h"


using namespace boost;
namespace jysoft { namespace simulator 
{
	CVirSimulateSymptomsCollect::CVirSimulateSymptomsCollect(void)
	{
		m_pWatchBarsShowAggregate   = NULL;
	}

	CVirSimulateSymptomsCollect::~CVirSimulateSymptomsCollect(void)
	{
        foreach (auto x, m_lstOtherSymptoms) {
            delete x;
        }
		m_lstOtherSymptoms.clear();
        foreach (auto x, m_lstUnMonitorSymptoms) {
            delete x;
        }
		m_lstUnMonitorSymptoms.clear();
	}

	//����������������໥Լ����ϵ
	void CVirSimulateSymptomsCollect::LoadSymptomsRelateRestrict()
	{
	}

	/*******************************************************************************/
	// �������ƣ� LinkSimulateBuildInterfaces
	// ���ܣ� ��ʼ����ģ���������߹������Ľӿ�
	// ������ COpPhysBuildInterfacesAggregate *pBuildAggregate:        
	// ����ֵ:  
	// ע�������ǹ̶���ϵ����˳�ʼ���ý׶ε��ô˺���������������صĹ������ӿڹ�ϵ
	void CVirSimulateSymptomsCollect::LinkSimulateBuildInterfaces(COpPhysBuildInterfacesAggregate *pBuildAggregate)
	{
		//�ĵ�ͼ
		m_cEcg.SetECGBuildInterface( pBuildAggregate->Get_OpECGBuildInterfacePtr() );
		//�д�Ѫѹ
		m_cABP.SetABPBuildInterface( pBuildAggregate->Get_OpABPBuildInterface() );
		//Ѫ��
		m_cSpO2.SetSpO2BuildInterface( pBuildAggregate->Get_OpSpO2BuildInterfacePtr() );
		//����
		m_cResp.SetRespBuildInterface( pBuildAggregate->Get_OpRespBuildInterfacePtr() );
		//����ĩ������̼
		m_cEtCO2.SetEtCO2BuildInterface( pBuildAggregate->Get_OpEtCO2BuildInterfacePtr() );
	}

	/*******************************************************************************/
	// �������ƣ� StartLinkWatchBarsShowInterfaces
	// ���ܣ� ��ʼ����ģ�������������ʾ�ӿ�
	// ������ CWatchBarsShowInterfacesAggregate *pShowAggregate:        
	// ����ֵ:  
	void CVirSimulateSymptomsCollect::StartLinkWatchBarsShowInterfaces(CWatchBarsShowInterfacesAggregate *pShowAggregate)
	{
		m_pWatchBarsShowAggregate = pShowAggregate;
		std::list<CSymptomVirtual *>    lstSymptoms;
		//�������е���������ָ��
		SearchAllSymptoms( /*out*/&lstSymptoms );

		m_cUpdateMutex.Lock();
		//����ģ�������������ʾ�ӿ�
        foreach(auto pSymptom, lstSymptoms)
		{
			pSymptom->OnLinkWatchBarUpdateInterfaceShow( pShowAggregate );
		}
		m_cUpdateMutex.Unlock();
	}

	/*******************************************************************************/
	// �������ƣ� UnLinkWatchBarsShowInterfaces
	// ���ܣ� �Ͽ�ģ�������������ʾ�ӿ�
	// ������ CWatchBarsShowInterfacesAggregate *pShowAggregate:        
	// ����ֵ:
	void CVirSimulateSymptomsCollect::UnLinkWatchBarsShowInterfaces(CWatchBarsShowInterfacesAggregate *pShowAggregate)
	{
		std::list<CSymptomVirtual *>    lstSymptoms;
		//�������е���������ָ��
		SearchAllSymptoms( /*out*/&lstSymptoms );
		m_cUpdateMutex.Lock();
		//����ģ�������������ʾ�ӿ�
        foreach(auto pSymptom, lstSymptoms)
		{
			pSymptom->OnUnLinkWatchBarUpdateInterfaceShow( pShowAggregate );
		}
		m_cUpdateMutex.Unlock();
		m_pWatchBarsShowAggregate = NULL;
	}

	//��ȡ���������ʱ��
	CSymptom_FrameTime * CVirSimulateSymptomsCollect::GetFrameTimeSymptomPtr()
	{
		CSymptom_FrameTime   *pFrameTimeSymptom = NULL;
        foreach(auto pVirSymptom, m_lstOtherSymptoms)
		{
			if( pVirSymptom->isKindOf( "CSymptom_FrameTime" ) )
			{
				pFrameTimeSymptom = (CSymptom_FrameTime *)pVirSymptom;
				break;
			}
		}
		return pFrameTimeSymptom;
	}

	//��ȡ������
	CSymptom_Pace * CVirSimulateSymptomsCollect::GetPaceSymptomPtr()
	{
		CSymptom_Pace  *pPaceSymptom = NULL;
        foreach(auto pVirSymptom, m_lstOtherSymptoms)
		{
			if( pVirSymptom->isKindOf( "CSymptom_Pace" ) )
			{
				pPaceSymptom = (CSymptom_Pace *)pVirSymptom;
				break;
			}
		}
		return pPaceSymptom;
	}

	//������Ӧ����������ָ��
	bool CVirSimulateSymptomsCollect::FindSymptomByAction(std::list<CSymptomVirtual *>* /*out*/plstFindSymptoms, const std::string &strActionCaption)
	{
		bool   bFindSymptom = false;
		std::list<CSymptomVirtual *>  lstSymptoms;
		//�������е���������ָ��
		SearchAllSymptoms( /*out*/&lstSymptoms );
		//==============================================================================
		//��ѯ��Ӧ����������ָ��
        foreach(auto pVirSymptom, lstSymptoms)
		{
			if( pVirSymptom->isSymptomCaption( strActionCaption ) )
			{
				bFindSymptom  = true;
				if( plstFindSymptoms != NULL )
				{
					plstFindSymptoms->push_back( pVirSymptom );
				}
			}
		}
		return bFindSymptom;
	}

	//�޸�����ģ�����߹�����
	void CVirSimulateSymptomsCollect::ModifySimulateSymptomsBuild(eEventSign eEventValue)
	{
		IModifiedSymptomsOp *pInterface = this;
		//Ѫѹ
		if( pInterface->findModifiedSymptom( &m_cABP ) )
		{
			m_cABP.ModifyABPBuild();
		}
		//Ѫ��
		if( pInterface->findModifiedSymptom( &m_cSpO2) )
		{
			m_cSpO2.ModifySpO2Build();
		}
		//�ĵ�ͼ
		if( pInterface->findModifiedSymptom( &m_cEcg ) )
		{
			m_cEcg.ModifyEcgBuild( eEventValue );
		}
		//etCO2
		if( pInterface->findModifiedSymptom( &m_cEtCO2 ) )
		{
			m_cEtCO2.ModifyetCO2Build();
		}
		//����
		if( pInterface->findModifiedSymptom( &m_cResp ) )
		{
			m_cResp.ModifyRespBuild();
		}
	}

	//����Ĭ�ϵ�������������
	void CVirSimulateSymptomsCollect::InitialOtherSymptoms(SimulatePatientType ePatientType)
	{
		IModifiedSymptomsOp  *pModifiedSymptomsOp = (IModifiedSymptomsOp *)this;
		//����ʱ��
		CSymptom_FrameTime      *pFrameTime = (CSymptom_FrameTime *)SeachOtherSymptom("CSymptom_FrameTime"); 
		if( pFrameTime == NULL )
		{
			pFrameTime  = new CSymptom_FrameTime();
			m_lstOtherSymptoms.push_back( pFrameTime );
		}
		pFrameTime->InitialSymptomValue( pModifiedSymptomsOp, ePatientType );
		//������
		CSymptom_Pace           *pPaceSet  = (CSymptom_Pace *)SeachOtherSymptom("CSymptom_Pace"); 
		if( pPaceSet == NULL )
		{
			pPaceSet  = new CSymptom_Pace();
			m_lstOtherSymptoms.push_back( pPaceSet );
		}
		pPaceSet->InitialSymptomValue( pModifiedSymptomsOp, ePatientType );
	}

	//ͨ������������������
	CSymptomVirtual * CVirSimulateSymptomsCollect::SeachOtherSymptom(const std::string &strClassName)
	{
        foreach(auto pVirSymptom, m_lstOtherSymptoms)
		{
			if( pVirSymptom->isKindOf( strClassName ) )
			{
				return pVirSymptom;
			}
		}
        foreach(auto pVirUnmonitorSymptom, m_lstOtherSymptoms)
		{
			if( pVirUnmonitorSymptom->isKindOf( strClassName ) )
			{
				return pVirUnmonitorSymptom;
			}
		}
		return NULL;
	}

	//��ʼ��Ĭ��״̬��������������ֵ
	void CVirSimulateSymptomsCollect::InitialSimulateSymptoms(SimulatePatientType ePatientType)
	{
		IModifiedSymptomsOp  *pModifiedSymptomsOp = (IModifiedSymptomsOp *)this;
		//�������е���������ָ��
		std::list<CSymptomVirtual *>  lstSymptoms;
		//�������е���������ָ��
		SearchAllSymptoms( /*out*/&lstSymptoms );
		//������ص�������Ĭ��ֵ�趨
        foreach(auto pVirSymptom, lstSymptoms)
		{
			pVirSymptom->InitialSymptomValue( pModifiedSymptomsOp, ePatientType );
		}
		InitialOtherSymptoms( ePatientType );
	}

	//��ʼ������ģ�����߹�����
	void CVirSimulateSymptomsCollect::InitialSimulateSymptomsBuild(SimulatePatientType ePatientType)
	{
		IModifiedSymptomsOp *pInterface = this;
		//Ѫѹ
		if( pInterface->findModifiedSymptom( &m_cABP ) )
		{
			m_cABP.InitialABPBuild( ePatientType );
		}
		//Ѫ��
		if( pInterface->findModifiedSymptom( &m_cSpO2 ) )
		{
			m_cSpO2.InitialSpO2Build( ePatientType );
		}
		//�ĵ�ͼ
		if( pInterface->findModifiedSymptom( &m_cEcg ) )
		{
			m_cEcg.InitialEcgBuild( ePatientType );
		}
		//etCO2
		if( pInterface->findModifiedSymptom( &m_cEtCO2 ) )
		{
			m_cEtCO2.InitialetCO2Build( ePatientType );
		}
		//����
		if( pInterface->findModifiedSymptom( &m_cResp ) )
		{
			m_cResp.InitialRespBuild( ePatientType );
		}
	}

	//ֱ���޸�����ģ�����߹�����
	void CVirSimulateSymptomsCollect::DirectModifySymptomsBuild(bool bClearIntubate /*=FALSE*/)
	{
		IModifiedSymptomsOp *pInterface = this;
		//Ѫѹ
		if( pInterface->findModifiedSymptom( &m_cABP ) )
		{
			m_cABP.ModifyABPBuild();
		}
		//Ѫ��
		if( pInterface->findModifiedSymptom( &m_cSpO2) )
		{
			m_cSpO2.ModifySpO2Build();
		}
		//�ĵ�ͼ
		if( pInterface->findModifiedSymptom( &m_cEcg ) )
		{
			m_cEcg.DirectEcgBuild();
		}
		//����
		if( pInterface->findModifiedSymptom( &m_cResp ) )
		{
			m_cResp.ModifyRespBuild();
		}
		//etCO2
		if( bClearIntubate || pInterface->findModifiedSymptom( &m_cEtCO2 ) )
		{
			m_cEtCO2.ModifyetCO2Build( bClearIntubate );
		}
	}

	//�������е���������ָ��
	void CVirSimulateSymptomsCollect::SearchAllSymptoms( std::list<CSymptomVirtual *>* /*out*/plstFindSymptoms )
	{
		plstFindSymptoms->push_back( &m_cEcg );
		plstFindSymptoms->push_back( &m_cSpO2 );
		plstFindSymptoms->push_back( &m_cABP );
		plstFindSymptoms->push_back( &m_cResp );
		plstFindSymptoms->push_back( &m_cEtCO2 );
		plstFindSymptoms->push_back( &m_cPupil );
		plstFindSymptoms->push_back( &m_cTemperature );
		//------------------------------------------------------------------------
		//��������
        foreach(auto pVirSymptom, m_lstOtherSymptoms)
		{
			plstFindSymptoms->push_back(pVirSymptom);
		}
		//---------------------------------------------------------------------------
		//�ɲ�����صĲ���������
        foreach(auto pVirSymptom, m_lstUnMonitorSymptoms)
		{
			plstFindSymptoms->push_back(pVirSymptom);
		}
	}

	//����AED״ָ̬��Irp
	irp::CSimulatorOrderIrp * CVirSimulateSymptomsCollect::translateAEDOrderIrp()
	{
		unsigned char sAEDState = 0;
		//�������е���������ָ��
		std::list<CSymptomVirtual *>  lstFindSymptoms;
		SearchAllSymptoms( &lstFindSymptoms );
        foreach(auto pVirSymptom, lstFindSymptoms)
		{
			pVirSymptom->isTransmitAEDState( &sAEDState );
		}
		return irp::CSimulatorOrderIrp::createSimulatorOrderIrp(0x71, (byte)sAEDState);
	}
}}
