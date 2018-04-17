#pragma once
#include ".\XActionVirtual.h"

#include "..\Common\CommonGlobal.h"

#include "..\simulatorBase\ITransportOrderIrpToSimulator.h"
#include "..\simulatorBase\SyncPnpFacilities.h"
#include "..\simulatorBase\WatchBarsShowInterfacesAggregate.h"
#include "..\simulatorBase\SymptomsShowInterfacesAggregate.h"


namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ģ�������������������࣬����ĳһ������ǰ��״̬����
	�����ˣ�	 hjg
	����ʱ�䣺   2008/10/17
	//-----------------------------------------------------------------------------------------------------------------*/

	class IModifiedSymptomsOp;
    class SIMULATORSYMPTOMSHARED_EXPORT CSymptomVirtual
	{
	public:
		CSymptomVirtual(void);
		virtual ~CSymptomVirtual(void);
	public:
		IModifiedSymptomsOp     *m_pModifiedSymptomsOp;
	public: 
		/*******************************************************************************/
		// �������ƣ� IsKindOf
		// ���ܣ�   �ж����������
		// ������   const CString &strClassName
		// ����ֵ: 
		virtual  bool isKindOf( const std::string &strClassName ) = 0;
		//���ݱ�ʾ�����ж���������
		virtual  bool isSymptomCaption(const std::string &strCaption) = 0;
		/*******************************************************************************/
		// �������ƣ� InitialSymptomValue
		// ���ܣ�   ��ʼ������ֵ
		// ������   IModifiedSymptomsOp *pInterfacePtr
		// ����ֵ: 
		virtual  void InitialSymptomValue(IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType) = 0;
		/*******************************************************************************/
		// �������ƣ� InitialSymptomValue
		// ���ܣ�   ��ʼ������ֵ
		// ������   
		//          tag_TrendValue *pDefaultTrendValue:  ��Ӧ�����޸ĵ�ֵ����
		//          CXActionVirtual *pVirAction:         ��Ӧ����ֵ
		//          short sTransTime:                    ת��ʱ�䣨��λ���룩
		// ����ֵ: 
		virtual  void InitialSymptomValue(CXActionVirtual *pVirAction, short sTransTime = 0) = 0;
		/*******************************************************************************/
		// �������ƣ� isTransmitAEDState
		// ���ܣ�   �Ƿ�AED״̬�ı�
		// ������   
		//          /*in,out*/unsigned char *sAEDState:        AED״̬
		// ����ֵ: 
		virtual  bool isTransmitAEDState(/*in,out*/unsigned char *sAEDState) { return false; };
		/*******************************************************************************/
		// �������ƣ� DoTransmitOrder
		// ���ܣ�   ģ�������������
		// ������   
		//          CSyncPnpFacilities *pPnPFacilities:        �Բ���豸��
		//          /*in,out*/unsigned char *sAEDState:        AED״̬
		//          ITransportOrderIrpToSimulator *pInterface: �����ӿ�
		// ����ֵ: 
		virtual  void DoTransmitOrder(pnp::CSyncPnpFacilities *pPnPFacilities,  transLayer::ITransportOrderIrpToSimulator *pInterface) { };
		/*******************************************************************************/
		// �������ƣ� OnUpdateInterfaceShow
		// ���ܣ�   ���½�����ʾ
		// ������   
		// ����ֵ: 
		virtual  void OnUpdateInterfaceShow() { };
		/*******************************************************************************/
		// �������ƣ� OnLinkWatchBarUpdateInterfaceShow
		// ���ܣ�   ����ģ������ʾ����
		// ������   
		// ����ֵ:
		virtual  void OnLinkWatchBarUpdateInterfaceShow(CWatchBarsShowInterfacesAggregate *pShowAggregate) { };
		/*******************************************************************************/
		// �������ƣ� OnUnLinkWatchBarUpdateInterfaceShow
		// ���ܣ�   �Ͽ�ģ������ʾ����
		// ������   
		// ����ֵ:
		virtual  void OnUnLinkWatchBarUpdateInterfaceShow(CWatchBarsShowInterfacesAggregate *pShowAggregate) { };
		/*******************************************************************************/
		// �������ƣ� OnLinkSimulatorBarUpdateInterfaceShow
		// ���ܣ�   �Ͽ�ģ���������ʾ����
		// ������   
		// ����ֵ:
		virtual  void OnLinkSimulatorBarUpdateInterfaceShow(CSymptomsShowInterfacesAggregate *pShowAggregate ) { };
		/*******************************************************************************/
		// �������ƣ� OnUnLinkSimulatorBarUpdateInterfaceShow
		// ���ܣ�   �Ͽ�ģ���������ʾ����
		// ������   
		// ����ֵ:
		virtual  void OnUnLinkSimulatorBarUpdateInterfaceShow(CSymptomsShowInterfacesAggregate *pShowAggregate ){ };
		/*******************************************************************************/
		// �������ƣ� ResetFlag
		// ���ܣ�   �����޸ĵı�ʶ
		// ������   
		// ����ֵ:
		virtual  void ResetFlag() { };
	};
}}
