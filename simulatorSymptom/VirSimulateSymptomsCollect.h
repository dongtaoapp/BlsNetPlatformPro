#pragma once
#include <list>
#include ".\IModifiedSymptomsOp.h"
#include ".\SymptomUnmonitorVirtual.h"
#include ".\Symptom_Ecg.h"
#include ".\Symptom_SpO2.h"
#include ".\Symptom_ABP.h"
#include ".\Symptom_Resp.h"
#include ".\Symptom_etCO2.h"
#include ".\Symptom_Pupil.h"
#include ".\Symptom_Temperature.h"
#include ".\Symptom_Pace.h"
#include ".\Symptom_FrameTime.h"

#include "..\Common\CommonGlobal.h"
#include "..\common\criticalmutex.h"

#include "..\SimulatorBase\OpPhysBuildInterfacesAggregate.h"
#include "..\SimulatorBase\WatchBarsShowInterfacesAggregate.h"


namespace jysoft { namespace simulator {
    class SIMULATORSYMPTOMSHARED_EXPORT CVirSimulateSymptomsCollect : public IModifiedSymptomsOp
	{
	public:
		CVirSimulateSymptomsCollect(void);
		virtual ~CVirSimulateSymptomsCollect(void);
	public:
		//设置生理体征间的相互约束关系
		void LoadSymptomsRelateRestrict();
		/*******************************************************************************/
		// 函数名称： LinkSimulateBuildInterfaces
		// 功能： 初始连接模拟生理曲线构造器的接口
		// 参数： COpPhysBuildInterfacesAggregate *pBuildAggregate:        
		// 返回值:  
		void LinkSimulateBuildInterfaces(COpPhysBuildInterfacesAggregate *pBuildAggregate);
		/*******************************************************************************/
		// 函数名称： StartLinkWatchBarsShowInterfaces
		// 功能： 初始连接模拟监控面板的相关显示接口
		// 参数： CWatchBarsShowInterfacesAggregate *pShowAggregate:        
		// 返回值:  
		void StartLinkWatchBarsShowInterfaces(CWatchBarsShowInterfacesAggregate *pShowAggregate);
		/*******************************************************************************/
		// 函数名称： UnLinkWatchBarsShowInterfaces
		// 功能： 断开模拟监控面板的相关显示接口
		// 参数： CWatchBarsShowInterfacesAggregate *pShowAggregate:        
		// 返回值:
		void UnLinkWatchBarsShowInterfaces(CWatchBarsShowInterfacesAggregate *pShowAggregate);
	public: //接口IModifiedSymptomsOp函数重载
		/*******************************************************************************/
		// 函数名称： TransmitSimulatorOrders
		// 功能： 传输模拟人体征通信指令
		// 参数：        
		// 返回值:
		virtual void TransmitSimulatorOrders() { };
		/*******************************************************************************/
		// 函数名称： ModifiedSymptomsUpdateShow
		// 功能： 被修改的参数更新显示
		// 参数： 
		//        BOOL bClearModifiedFlag:      是否清除修改标识   
		// 返回值:
		virtual void ModifiedSymptomsUpdateShow( bool bClearModifiedFlag ) { };
	public:
		//获取场景框持续时间
		CSymptom_FrameTime * GetFrameTimeSymptomPtr();
		//获取起搏属性
		CSymptom_Pace * GetPaceSymptomPtr();
	public:
		//直接修改体征模拟曲线构造器
		void DirectModifySymptomsBuild(bool bClearIntubate=false);
	protected:
		//初始化默认状态的生理体征参数值
		void InitialSimulateSymptoms(SimulatePatientType ePatientType);
		//搜索对应的体征对象指针
		bool FindSymptomByAction(std::list<CSymptomVirtual *>* /*out*/plstFindSymptoms, const std::string &strActionCaption);
		//修改体征模拟曲线构造器
		void ModifySimulateSymptomsBuild(eEventSign eEventValue);
		//生成默认的其它体征参数
		void InitialOtherSymptoms(SimulatePatientType ePatientType);
		//初始化体征模拟曲线构造器
		void InitialSimulateSymptomsBuild(SimulatePatientType ePatientType);
	protected:
		//通过类名查找其它体征
		CSymptomVirtual * SeachOtherSymptom(const std::string &strClassName);
		//搜索所有的体征对象指针
		void SearchAllSymptoms( std::list<CSymptomVirtual *>* /*out*/plstFindSymptoms );
		//生成AED状态指令Irp
		irp::CSimulatorOrderIrp * translateAEDOrderIrp();
	protected:
		CSymptom_Ecg                  m_cEcg;
		CSymptom_SpO2                 m_cSpO2;
		CSymptom_ABP                  m_cABP;
		CSymptom_Resp                 m_cResp;
		CSymptom_etCO2                m_cEtCO2;
		CSymptom_Pupil                m_cPupil;
		CSymptom_Temperature          m_cTemperature;
		//其它体征
		std::list<CSymptomVirtual *>                      m_lstOtherSymptoms;
		//可不被监控的参数的体征
		std::list<CSymptomUnmonitorVirtual *>             m_lstUnMonitorSymptoms;
	protected:
		utility::CCriticalMutex       m_cUpdateMutex;
	protected:
		CWatchBarsShowInterfacesAggregate *      m_pWatchBarsShowAggregate;
	};
}}
