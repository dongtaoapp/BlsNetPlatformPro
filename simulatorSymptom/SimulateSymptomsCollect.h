#pragma once
#include ".\VirSimulateSymptomsCollect.h"
#include ".\ISetSimulateSymptoms.h"
#include ".\XActionVirtual.h"
#include ".\PnPFacilityGlobal.h"

#include "..\SimulatorBase\SyncPnpFacilities.h"
#include "..\SimulatorBase\OpPhysBuildInterfacesAggregate.h"
#include "..\SimulatorBase\SymptomsShowInterfacesAggregate.h"

#include "..\Common\CommonGlobal.h"
#include "..\Common\EventHandleClockIrpOp.h"
#include "..\Common\EventHandleCPRStatIrpOp.h"
#include "..\Common\RealTimeDataHandleIrpOp.h"
#include "..\Common\EventHandleCustomIrpOp.h"

namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ģ�������������������Ϲ����࣬������ǰģ���״̬
	�����ˣ�	 hjg
	����ʱ�䣺   2017/2/17
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORSYMPTOMSHARED_EXPORT CSimulateSymptomsCollect   : public CVirSimulateSymptomsCollect
													,public ISetSimulateSymptoms
													,public irp::CEventHandleClockIrpOp
													,public irp::CEventHandleCustomIrpOp
													,public irp::CEventHandleCPRStatIrpOp
													,public irp::CRealTimeDataHandleIrpOp
	{
	public:
		CSimulateSymptomsCollect(void);
		virtual ~CSimulateSymptomsCollect(void);
	public://�ӿ�ISetSimulateSymptoms�ĺ�������
		/*******************************************************************************/
		// �������ƣ� initialScenarioSet
		// ���ܣ�   ����������ʼ��Ϊ��ǰ����״̬
		// ������   std::list<CXActionVirtual *> *plstActions: 
		////        SimulatePatientType ePatientType: ģ��������
		// ����ֵ:  tag_TrendValue: ��ǰ���������õ�����ֵ
		virtual void initialScenarioSet(std::list<CXActionVirtual *> *plstActions, SimulatePatientType ePatientType);
		//��ʼ������ģ�����߹�����
		virtual void initialSimulateSymptomsBuild(SimulatePatientType ePatientType);
		/*******************************************************************************/
		// �������ƣ� modifyScenario
		// ���ܣ�   �޸ĵ�ǰ����״̬����������ֵ
		// ������   CList<CXActionVirtual *, CXActionVirtual *> lstActions: 
		//          eEventSign eEventValue:  ����ת�����¼��ź�
		//          BOOL bExecActions:       �Ƿ�ִ������
		//          short sTransferTime:
		// ����ֵ:  tag_TrendValue: ��ǰ���������õ�����ֵ
		virtual void modifyScenarioSet(std::list<CXActionVirtual *> *plstActions, eEventSign eEventValue, bool bExecActions = true, short sTransferTime = 0);
	public: //�ӿ�CEventHandleClockIrpOp�ĺ�������
		/*******************************************************************************/
		//���ܣ�����ʱ���¼�IRP����
		//������
		//      CVirtualIrp *pCurrIrp��
		//����ֵ:  �������ٴ���FALSE);
		virtual bool doHandleClockIrpOp(irp::CVirtualIrp *pCurrIrp);
	public: //�ӿ�CEventHandleCustomIrpOp�ĺ�������
		/*******************************************************************************/
		//���ܣ��������¼�IRP����
		//������
		//      CVirtualIrp *pCurrIrp��
		//����ֵ:  �������ٴ���FALSE);
		virtual bool doHandleCustomEventIrpOp(irp::CVirtualIrp *pCurrIrp);
	public: //�ӿ�CEventHandleCPRStatIrpOp�ĺ�������
		/*******************************************************************************/
		//���ܣ�����CPR����ͳ�ƽ��IRP����
		//������
		//      CVirtualIrp *pCurrIrp��
		//����ֵ:  �������ٴ���FALSE);
		virtual bool doHandleCPRStatIrpOp(irp::CVirtualIrp *pCurrIrp);
	public:  //�ӿ�CRealTimeDataHandleIrpOp�ĺ�������
		/*******************************************************************************/
		//���ܣ���������ת��IRP����
		//������
		//      CVirtualIrp *pCurrIrp��
		//����ֵ:  �������ٴ���FALSE);
		virtual bool doHandleRealTimeDataIrpOp(irp::CVirtualIrp *pCurrIrp);
	public:
		/*******************************************************************************/
		// �������ƣ� TransmitSimulatorOrders
		// ���ܣ� ����ģ��������ͨ��ָ��
		// ������         
		// ����ֵ:
		virtual void TransmitSimulatorOrders();
		/*******************************************************************************/
		// �������ƣ� ModifiedSymptomsUpdateShow
		// ���ܣ� ���޸ĵĲ���������ʾ
		// ������ 
		//        BOOL bClearModifiedFlag:      �Ƿ�����޸ı�ʶ   
		// ����ֵ:
		virtual void ModifiedSymptomsUpdateShow( bool bClearModifiedFlag );
	public:
		//����ģ��������ͨ��ָ���ӿ�
		void set_TransportOrderIrpToSimulatorInterface(transLayer::ITransportOrderIrpToSimulator *pInterface) { m_pTransportOrderInterface  = pInterface; };
	public:
		/*******************************************************************************/
		// �������ƣ� StartLinkeSimulateBarShowInterfaces
		// ���ܣ� ��ʼ����ģ��ģ�����������������ʾ�ӿ�
		// ������ CSymptomsShowInterfacesAggregate *pShowAggregate:        
		// ����ֵ:  
		void StartLinkeSimulateBarShowInterfaces(CSymptomsShowInterfacesAggregate *pShowAggregate);
		/*******************************************************************************/
		// �������ƣ� UnLinkSimulateBarShowInterfaces
		// ���ܣ� �Ͽ�ģ��ģ�����������������ʾ�ӿ�
		// ������ CSymptomsShowInterfacesAggregate *pShowAggregate:        
		// ����ֵ:
		void UnLinkSimulateBarShowInterfaces(CSymptomsShowInterfacesAggregate *pShowAggregate);
	protected:
		//������Ӧ����������ָ��
		bool FindSymptomByAction(std::list<CSymptomVirtual *>* /*out*/plstFindSymptoms, CXActionVirtual* /*in*/pVirAction);
		//��ӿɲ�����صĲ���������
		void AddUnMonitorSymptom(CXActionVirtual *pVirAction);
	private:
		//����ǰ�����е�������������˳�������
		void doActionsHandleArrange(std::list<CXActionVirtual *> *plstActions);
		CXActionVirtual * findActionByName(std::list<CXActionVirtual *> *ptrlstActions, const std::string &strActionName);
	public:
		//��ȡ�޸ĵ���������
		void getsynchronizeSymptoms(std::list<CSymptomVirtual *> /*out*/*plstModifiedSymptoms, bool bInitial);
	public:
		std::string									m_strScriptName;
	private:
		transLayer::ITransportOrderIrpToSimulator*  m_pTransportOrderInterface;
		pnp::CSyncPnpFacilities          m_cSyncPnPFacilities;   
	};
}}
