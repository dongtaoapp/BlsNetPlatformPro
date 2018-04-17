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
		//����������������໥Լ����ϵ
		void LoadSymptomsRelateRestrict();
		/*******************************************************************************/
		// �������ƣ� LinkSimulateBuildInterfaces
		// ���ܣ� ��ʼ����ģ���������߹������Ľӿ�
		// ������ COpPhysBuildInterfacesAggregate *pBuildAggregate:        
		// ����ֵ:  
		void LinkSimulateBuildInterfaces(COpPhysBuildInterfacesAggregate *pBuildAggregate);
		/*******************************************************************************/
		// �������ƣ� StartLinkWatchBarsShowInterfaces
		// ���ܣ� ��ʼ����ģ�������������ʾ�ӿ�
		// ������ CWatchBarsShowInterfacesAggregate *pShowAggregate:        
		// ����ֵ:  
		void StartLinkWatchBarsShowInterfaces(CWatchBarsShowInterfacesAggregate *pShowAggregate);
		/*******************************************************************************/
		// �������ƣ� UnLinkWatchBarsShowInterfaces
		// ���ܣ� �Ͽ�ģ�������������ʾ�ӿ�
		// ������ CWatchBarsShowInterfacesAggregate *pShowAggregate:        
		// ����ֵ:
		void UnLinkWatchBarsShowInterfaces(CWatchBarsShowInterfacesAggregate *pShowAggregate);
	public: //�ӿ�IModifiedSymptomsOp��������
		/*******************************************************************************/
		// �������ƣ� TransmitSimulatorOrders
		// ���ܣ� ����ģ��������ͨ��ָ��
		// ������        
		// ����ֵ:
		virtual void TransmitSimulatorOrders() { };
		/*******************************************************************************/
		// �������ƣ� ModifiedSymptomsUpdateShow
		// ���ܣ� ���޸ĵĲ���������ʾ
		// ������ 
		//        BOOL bClearModifiedFlag:      �Ƿ�����޸ı�ʶ   
		// ����ֵ:
		virtual void ModifiedSymptomsUpdateShow( bool bClearModifiedFlag ) { };
	public:
		//��ȡ���������ʱ��
		CSymptom_FrameTime * GetFrameTimeSymptomPtr();
		//��ȡ������
		CSymptom_Pace * GetPaceSymptomPtr();
	public:
		//ֱ���޸�����ģ�����߹�����
		void DirectModifySymptomsBuild(bool bClearIntubate=false);
	protected:
		//��ʼ��Ĭ��״̬��������������ֵ
		void InitialSimulateSymptoms(SimulatePatientType ePatientType);
		//������Ӧ����������ָ��
		bool FindSymptomByAction(std::list<CSymptomVirtual *>* /*out*/plstFindSymptoms, const std::string &strActionCaption);
		//�޸�����ģ�����߹�����
		void ModifySimulateSymptomsBuild(eEventSign eEventValue);
		//����Ĭ�ϵ�������������
		void InitialOtherSymptoms(SimulatePatientType ePatientType);
		//��ʼ������ģ�����߹�����
		void InitialSimulateSymptomsBuild(SimulatePatientType ePatientType);
	protected:
		//ͨ������������������
		CSymptomVirtual * SeachOtherSymptom(const std::string &strClassName);
		//�������е���������ָ��
		void SearchAllSymptoms( std::list<CSymptomVirtual *>* /*out*/plstFindSymptoms );
		//����AED״ָ̬��Irp
		irp::CSimulatorOrderIrp * translateAEDOrderIrp();
	protected:
		CSymptom_Ecg                  m_cEcg;
		CSymptom_SpO2                 m_cSpO2;
		CSymptom_ABP                  m_cABP;
		CSymptom_Resp                 m_cResp;
		CSymptom_etCO2                m_cEtCO2;
		CSymptom_Pupil                m_cPupil;
		CSymptom_Temperature          m_cTemperature;
		//��������
		std::list<CSymptomVirtual *>                      m_lstOtherSymptoms;
		//�ɲ�����صĲ���������
		std::list<CSymptomUnmonitorVirtual *>             m_lstUnMonitorSymptoms;
	protected:
		utility::CCriticalMutex       m_cUpdateMutex;
	protected:
		CWatchBarsShowInterfacesAggregate *      m_pWatchBarsShowAggregate;
	};
}}
