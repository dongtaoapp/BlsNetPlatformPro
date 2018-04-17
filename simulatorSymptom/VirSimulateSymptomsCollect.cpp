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

	//设置生理体征间的相互约束关系
	void CVirSimulateSymptomsCollect::LoadSymptomsRelateRestrict()
	{
	}

	/*******************************************************************************/
	// 函数名称： LinkSimulateBuildInterfaces
	// 功能： 初始连接模拟生理曲线构造器的接口
	// 参数： COpPhysBuildInterfacesAggregate *pBuildAggregate:        
	// 返回值:  
	// 注：由于是固定关系，因此初始配置阶段调用此函数创建体针与相关的构造器接口关系
	void CVirSimulateSymptomsCollect::LinkSimulateBuildInterfaces(COpPhysBuildInterfacesAggregate *pBuildAggregate)
	{
		//心电图
		m_cEcg.SetECGBuildInterface( pBuildAggregate->Get_OpECGBuildInterfacePtr() );
		//有创血压
		m_cABP.SetABPBuildInterface( pBuildAggregate->Get_OpABPBuildInterface() );
		//血氧
		m_cSpO2.SetSpO2BuildInterface( pBuildAggregate->Get_OpSpO2BuildInterfacePtr() );
		//呼吸
		m_cResp.SetRespBuildInterface( pBuildAggregate->Get_OpRespBuildInterfacePtr() );
		//呼吸末二氧化碳
		m_cEtCO2.SetEtCO2BuildInterface( pBuildAggregate->Get_OpEtCO2BuildInterfacePtr() );
	}

	/*******************************************************************************/
	// 函数名称： StartLinkWatchBarsShowInterfaces
	// 功能： 初始连接模拟监控面板的相关显示接口
	// 参数： CWatchBarsShowInterfacesAggregate *pShowAggregate:        
	// 返回值:  
	void CVirSimulateSymptomsCollect::StartLinkWatchBarsShowInterfaces(CWatchBarsShowInterfacesAggregate *pShowAggregate)
	{
		m_pWatchBarsShowAggregate = pShowAggregate;
		std::list<CSymptomVirtual *>    lstSymptoms;
		//搜索所有的体征对象指针
		SearchAllSymptoms( /*out*/&lstSymptoms );

		m_cUpdateMutex.Lock();
		//连接模拟监控面板的相关显示接口
        foreach(auto pSymptom, lstSymptoms)
		{
			pSymptom->OnLinkWatchBarUpdateInterfaceShow( pShowAggregate );
		}
		m_cUpdateMutex.Unlock();
	}

	/*******************************************************************************/
	// 函数名称： UnLinkWatchBarsShowInterfaces
	// 功能： 断开模拟监控面板的相关显示接口
	// 参数： CWatchBarsShowInterfacesAggregate *pShowAggregate:        
	// 返回值:
	void CVirSimulateSymptomsCollect::UnLinkWatchBarsShowInterfaces(CWatchBarsShowInterfacesAggregate *pShowAggregate)
	{
		std::list<CSymptomVirtual *>    lstSymptoms;
		//搜索所有的体征对象指针
		SearchAllSymptoms( /*out*/&lstSymptoms );
		m_cUpdateMutex.Lock();
		//连接模拟监控面板的相关显示接口
        foreach(auto pSymptom, lstSymptoms)
		{
			pSymptom->OnUnLinkWatchBarUpdateInterfaceShow( pShowAggregate );
		}
		m_cUpdateMutex.Unlock();
		m_pWatchBarsShowAggregate = NULL;
	}

	//获取场景框持续时间
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

	//获取起搏属性
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

	//搜索对应的体征对象指针
	bool CVirSimulateSymptomsCollect::FindSymptomByAction(std::list<CSymptomVirtual *>* /*out*/plstFindSymptoms, const std::string &strActionCaption)
	{
		bool   bFindSymptom = false;
		std::list<CSymptomVirtual *>  lstSymptoms;
		//搜索所有的体征对象指针
		SearchAllSymptoms( /*out*/&lstSymptoms );
		//==============================================================================
		//查询对应的体征对象指针
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

	//修改体征模拟曲线构造器
	void CVirSimulateSymptomsCollect::ModifySimulateSymptomsBuild(eEventSign eEventValue)
	{
		IModifiedSymptomsOp *pInterface = this;
		//血压
		if( pInterface->findModifiedSymptom( &m_cABP ) )
		{
			m_cABP.ModifyABPBuild();
		}
		//血氧
		if( pInterface->findModifiedSymptom( &m_cSpO2) )
		{
			m_cSpO2.ModifySpO2Build();
		}
		//心电图
		if( pInterface->findModifiedSymptom( &m_cEcg ) )
		{
			m_cEcg.ModifyEcgBuild( eEventValue );
		}
		//etCO2
		if( pInterface->findModifiedSymptom( &m_cEtCO2 ) )
		{
			m_cEtCO2.ModifyetCO2Build();
		}
		//呼吸
		if( pInterface->findModifiedSymptom( &m_cResp ) )
		{
			m_cResp.ModifyRespBuild();
		}
	}

	//生成默认的其它体征参数
	void CVirSimulateSymptomsCollect::InitialOtherSymptoms(SimulatePatientType ePatientType)
	{
		IModifiedSymptomsOp  *pModifiedSymptomsOp = (IModifiedSymptomsOp *)this;
		//场景时间
		CSymptom_FrameTime      *pFrameTime = (CSymptom_FrameTime *)SeachOtherSymptom("CSymptom_FrameTime"); 
		if( pFrameTime == NULL )
		{
			pFrameTime  = new CSymptom_FrameTime();
			m_lstOtherSymptoms.push_back( pFrameTime );
		}
		pFrameTime->InitialSymptomValue( pModifiedSymptomsOp, ePatientType );
		//起搏设置
		CSymptom_Pace           *pPaceSet  = (CSymptom_Pace *)SeachOtherSymptom("CSymptom_Pace"); 
		if( pPaceSet == NULL )
		{
			pPaceSet  = new CSymptom_Pace();
			m_lstOtherSymptoms.push_back( pPaceSet );
		}
		pPaceSet->InitialSymptomValue( pModifiedSymptomsOp, ePatientType );
	}

	//通过类名查找其它体征
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

	//初始化默认状态的生理体征参数值
	void CVirSimulateSymptomsCollect::InitialSimulateSymptoms(SimulatePatientType ePatientType)
	{
		IModifiedSymptomsOp  *pModifiedSymptomsOp = (IModifiedSymptomsOp *)this;
		//搜索所有的体征对象指针
		std::list<CSymptomVirtual *>  lstSymptoms;
		//搜索所有的体征对象指针
		SearchAllSymptoms( /*out*/&lstSymptoms );
		//趋势相关的体征的默认值设定
        foreach(auto pVirSymptom, lstSymptoms)
		{
			pVirSymptom->InitialSymptomValue( pModifiedSymptomsOp, ePatientType );
		}
		InitialOtherSymptoms( ePatientType );
	}

	//初始化体征模拟曲线构造器
	void CVirSimulateSymptomsCollect::InitialSimulateSymptomsBuild(SimulatePatientType ePatientType)
	{
		IModifiedSymptomsOp *pInterface = this;
		//血压
		if( pInterface->findModifiedSymptom( &m_cABP ) )
		{
			m_cABP.InitialABPBuild( ePatientType );
		}
		//血氧
		if( pInterface->findModifiedSymptom( &m_cSpO2 ) )
		{
			m_cSpO2.InitialSpO2Build( ePatientType );
		}
		//心电图
		if( pInterface->findModifiedSymptom( &m_cEcg ) )
		{
			m_cEcg.InitialEcgBuild( ePatientType );
		}
		//etCO2
		if( pInterface->findModifiedSymptom( &m_cEtCO2 ) )
		{
			m_cEtCO2.InitialetCO2Build( ePatientType );
		}
		//呼吸
		if( pInterface->findModifiedSymptom( &m_cResp ) )
		{
			m_cResp.InitialRespBuild( ePatientType );
		}
	}

	//直接修改体征模拟曲线构造器
	void CVirSimulateSymptomsCollect::DirectModifySymptomsBuild(bool bClearIntubate /*=FALSE*/)
	{
		IModifiedSymptomsOp *pInterface = this;
		//血压
		if( pInterface->findModifiedSymptom( &m_cABP ) )
		{
			m_cABP.ModifyABPBuild();
		}
		//血氧
		if( pInterface->findModifiedSymptom( &m_cSpO2) )
		{
			m_cSpO2.ModifySpO2Build();
		}
		//心电图
		if( pInterface->findModifiedSymptom( &m_cEcg ) )
		{
			m_cEcg.DirectEcgBuild();
		}
		//呼吸
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

	//搜索所有的体征对象指针
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
		//其它体征
        foreach(auto pVirSymptom, m_lstOtherSymptoms)
		{
			plstFindSymptoms->push_back(pVirSymptom);
		}
		//---------------------------------------------------------------------------
		//可不被监控的参数的体征
        foreach(auto pVirSymptom, m_lstUnMonitorSymptoms)
		{
			plstFindSymptoms->push_back(pVirSymptom);
		}
	}

	//生成AED状态指令Irp
	irp::CSimulatorOrderIrp * CVirSimulateSymptomsCollect::translateAEDOrderIrp()
	{
		unsigned char sAEDState = 0;
		//搜索所有的体征对象指针
		std::list<CSymptomVirtual *>  lstFindSymptoms;
		SearchAllSymptoms( &lstFindSymptoms );
        foreach(auto pVirSymptom, lstFindSymptoms)
		{
			pVirSymptom->isTransmitAEDState( &sAEDState );
		}
		return irp::CSimulatorOrderIrp::createSimulatorOrderIrp(0x71, (byte)sAEDState);
	}
}}
