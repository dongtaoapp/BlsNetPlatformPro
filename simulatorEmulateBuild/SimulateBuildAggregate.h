#pragma once
#include ".\simulatoremulatebuild_global.h"

#include ".\CardiogramBuild.h"
#include ".\SpO2SampleDataBuild.h"
#include ".\RespSimulateBuild.h"
#include ".\CO2SimulateBuild.h"
#include ".\ECGSimulateCanvas.h"
#include ".\RespSimulateCanvas.h"
#include ".\ABPSimulateBuild.h"
#include ".\GeneralSimulateControledCanvas.h"

#include "..\SimulatorBase\ShowCPRActUpdateInterface.h"
#include "..\SimulatorBase\OpPhysBuildInterfacesAggregate.h"


namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ����ģ����������
	�����ˣ�	 hjg
	����ʱ�䣺   2017/2/18
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATOREMULATEBUILDSHARED_EXPORT CSimulateBuildAggregate : public COpPhysBuildInterfacesAggregate
												, public cpr::CShowCPRActUpdateInterface
	{
	public:
		CSimulateBuildAggregate( );
		virtual ~CSimulateBuildAggregate(void);
	protected:
		ecg::CCardiogramBuild                  m_cECGBuild;        //�ĵ�ͼģ����
		SpO2::CSpO2SampleDataBuild             m_cSpO2Build;       //Ѫ��ģ����
		resp::CRespSimulateBuild               m_cRespBuild;       //����ģ����
		etCO2::CCO2SimulateBuild               m_cEtCO2Build;      //����������̼Ũ�ȷ�ѹģ����
		bp::CABPSimulateBuild                  m_cABPBuild;        //�д�Ѫѹģ����
	protected:  
		ecg::CECGSimulateCanvas                 m_cEcgSimulateCanvas;
		CRespSimulateCanvas                m_cRespSimulateCanvas;
		CGeneralSimulateControledCanvas    m_cSpO2SimulateCanvas;
		CGeneralSimulateControledCanvas    m_cABPSimulateCanvas;
		CGeneralSimulateControledCanvas    m_cEtCO2SimulateCanvas;
	private:
		std::string      resourcePath;
	public://����COpPhysBuildInterfacesAggregate����
		//��ʼ����������ģ����
		virtual void InitialPhysBuilds();
		//�ر���������ģ����
		virtual void ClosePhysBuilds();
		/*******************************************************************************/
		// �������ƣ� OnWatchECGHandle
		// ���ܣ� ����/�Ͽ��ĵ�ͼ�ļ���
		// ������
		//        IDistributeEcgLeadsSimulateData  *pDistributeECGInterface: �����ɷ��ӿ�
		//        BOOL bCutWatch:
		// ����ֵ:  
		virtual void OnWatchECGHandle(IDistributeEcgLeadsSimulateData  *pDistributeECGInterface, base::CShowECGUpdateInterface *pInterface, bool bCutWatch);
		/*******************************************************************************/
		// �������ƣ� OnWatchSpO2Handle
		// ���ܣ� ����/�Ͽ�SpO2�ļ���
		// ������
		//        IDistributeSimulateData  *pDistributeInterface: �����ɷ��ӿ�
		//        BOOL bCutWatch:
		// ����ֵ:  
		virtual void OnWatchSpO2Handle(IDistributeSimulateData  *pDistributeInterface, base::CShowSpO2UpdateInterface *pInterface, bool bCutWatch);
		/*******************************************************************************/
		// �������ƣ� OnWatchEtCO2Handle
		// ���ܣ� ����/�Ͽ������ļ���
		// ������
		//        IDistributeSimulateData  *pDistributeInterface: �����ɷ��ӿ�
		//        BOOL bCutWatch:
		// ����ֵ: 
		virtual void OnWatchEtCO2Handle(IDistributeSimulateData *pDistributeInterface, base::CShowEtCO2UpdateInterface *pInterface, bool bCutWatch);
		/*******************************************************************************/
		// �������ƣ� OnWatchRespHandle
		// ���ܣ� ����/�Ͽ������ļ���
		// ������
		//        IDistributeSimulateData  *pDistributeInterface: �����ɷ��ӿ�
		//        BOOL bCutWatch:
		// ����ֵ: 
		virtual void OnWatchRespHandle(IDistributeRespSimulateData *pDistributeInterface, base::CShowRespRateUpdateInterface *pInterface, bool bCutWatch);
		/*******************************************************************************/
		// �������ƣ� OnWatchABPHandle
		// ���ܣ� ����/�Ͽ�ABP�ļ���
		// ������
		//        IDistributeSimulateData  *pDistributeInterface: �����ɷ��ӿ�
		//        CShowABPUpdateInterface *pInterface
		//        BOOL bCutWatch:
		// ����ֵ:  
		virtual void OnWatchABPHandle(IDistributeSimulateData  *pDistributeInterface, base::CShowABPUpdateInterface *pInterface, bool bCutWatch);
		/*******************************************************************************/
		// �������ƣ� StartLinkWatchBarsShowInterfaces
		// ���ܣ� ��ʼ����ģ����������ʾ�ӿ�
		// ������ CWatchBarsShowInterfacesAggregate *pShowAggregate:        
		// ����ֵ:  
		virtual void StartLinkWatchBarsShowInterfaces(CWatchBarsShowInterfacesAggregate *pShowAggregate);
		/*******************************************************************************/
		// �������ƣ� UnLinkWatchBarsShowInterfaces
		// ���ܣ� �Ͽ�ģ����������ʾ�ӿ�
		// ������ CWatchBarsShowInterfacesAggregate *pShowAggregate:        
		// ����ֵ:  
		virtual void UnLinkWatchBarsShowInterfaces(CWatchBarsShowInterfacesAggregate *pShowAggregate);
	public:
		//ֹͣģ�����ݵ�ʵʱ����
		void StopSimulateBuilds();
		/*******************************************************************************/
		// �������ƣ� StartSimulateBuild
		// ���ܣ� ����ģ�����ݵ����ɣ�������SpO2��ABPʵʱ����
		// ������ 
		// ����ֵ:  
		void StartSimulateBuild();
		/*******************************************************************************/
		// �������ƣ� InitialPhysBuildsRelationAndResources
		// ���ܣ� ��ʼ��������������ص�ָ���趨��������Դ
		// ������   
		// ����ֵ:  
		void InitialPhysBuildsRelationAndResources(const std::string &resPath, transLayer::ITransportOrderIrpToSimulator *pTransportOrderIrp = NULL, SimulatePatientType ePatientType = SPT_Adult);
	protected:
		virtual void RaiseJowAct(bool bLookUp) { };
		//�˹�������ʼ\����(TRUE:��ʼ��FALSE:����)
		virtual void BreathStateAct(bool bState) { };
		//������ѭ����CPR
		virtual void FiveCycleCompleteAct() { };
		//��ѹ��ʼ\����(TRUE:��ʼ��FALSE:����)
		virtual void PressureStateAct(bool bState);
		//����CPR����
		virtual void FinishCPROperator(bool bSecceed);
	public:
		//�����Ƿ�����ĵ����Ӽ��
		void Set_IsClearEcgWatchLink(bool bClear);
		//�����ĵ����Ӽ��״̬
		void Set_EcgWatchLinkState(bool bLinking);
		bool Get_IsEcgWatchLink();
		//�����Ƿ����SpO2���Ӽ��
		void Set_IsClearSpO2WatchLink(bool bClear);
		//����SpO2���Ӽ��״̬
		void Set_SpO2WatchLinkState(bool bLinking);
		bool Get_IsSpO2WatchLink();
		//�����Ƿ����ABP���Ӽ��
		void Set_IsClearABPWatchLink(bool bClear);
		//����ABP���Ӽ��״̬
		void Set_ABPWatchLinkState(bool bLinking);
		//�����Ƿ����EtCO2���Ӽ��
		void Set_IsClearEtCO2WatchLink(bool bClear);
		//����EtCO2���Ӽ��״̬
		void Set_EtCO2WatchLinkState(bool bLinking);
		//�����Ƿ����Resp���Ӽ��
		void Set_IsClearRespWatchLink(bool bClear);
		//����Resp���Ӽ��״̬
		void Set_RespWatchLinkState(bool bLinking);
	};
}}
