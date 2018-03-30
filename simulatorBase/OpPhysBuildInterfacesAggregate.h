#pragma once
#include ".\OpECGBuildInterface.h"
#include ".\OpSpO2BuildInterface.h"
#include ".\OpEtCO2BuildInterface.h"
#include ".\OpRespBuildInterface.h"
#include ".\OpABPBuildInterface.h"
#include ".\ITransportOrderIrpToSimulator.h"
#include ".\IDistributeSimulateData.h"

#include "..\Common\CommonGlobal.h"

namespace jysoft { namespace simulator {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ��������ģ�����Ĺ���ӿڼ���
	�����ˣ�	 hjg
	����ʱ�䣺   2008/8/12
	//-----------------------------------------------------------------------------------------------------------------*/
	class CWatchBarsShowInterfacesAggregate;
    class SIMULATORBASESHARED_EXPORT COpPhysBuildInterfacesAggregate
	{
	public:
		COpPhysBuildInterfacesAggregate(void);
		virtual ~COpPhysBuildInterfacesAggregate(void);
	protected:
		base::COpECGBuildInterface                    *m_pOpECGBuildInterface;    //�ĵ�ͼģ�����ӿ�
		base::COpSpO2BuildInterface                   *m_pOpSpO2BuildInterface;   //Ѫ��ģ�����ӿ�
		base::COpEtCO2BuildInterface                  *m_pEtCO2BuildInterface;    //����������̼Ũ�ȷ�ѹģ�����ӿ�
		base::COpRespBuildInterface                   *m_pRespBuildInterface;     //����ģ�����ӿ�
		base::COpABPBuildInterface                    *m_pABPBuildInterface;      //�д�Ѫѹģ�����ӿ�
	public:
		//��ʼ����������ģ����
		virtual void InitialPhysBuilds(transLayer::ITransportOrderIrpToSimulator *pTransportOrderIrp, SimulatePatientType ePatientType) = 0;
		//�ر���������ģ����
		virtual void ClosePhysBuilds() = 0;
	public:  
		/*******************************************************************************/
		// �������ƣ� OnWatchECGHandle
		// ���ܣ� ����/�Ͽ��ĵ�ͼ�ļ���
		// ������
		//        IDistributeEcgLeadsSimulateData  *pDistributeECGInterface: �����ɷ��ӿ�
		//        BOOL bCutWatch:
		// ����ֵ:  
		virtual void OnWatchECGHandle(IDistributeEcgLeadsSimulateData  *pDistributeECGInterface, base::CShowECGUpdateInterface *pInterface, bool bCutWatch) = 0;
		/*******************************************************************************/
		// �������ƣ� OnWatchRespHandle
		// ���ܣ� ����/�Ͽ������ļ���
		// ������
		//        IDistributeSimulateData  *pDistributeInterface: �����ɷ��ӿ�
		//        BOOL bCutWatch:
		// ����ֵ: 
		virtual void OnWatchRespHandle(IDistributeRespSimulateData *pDistributeInterface, base::CShowRespRateUpdateInterface *pInterface, bool bCutWatch) = 0;
		/*******************************************************************************/
		// �������ƣ� OnWatchEtCO2Handle
		// ���ܣ� ����/�Ͽ������ļ���
		// ������
		//        IDistributeSimulateData  *pDistributeInterface: �����ɷ��ӿ�
		//        BOOL bCutWatch:
		// ����ֵ: 
		virtual void OnWatchEtCO2Handle(IDistributeSimulateData *pDistributeInterface, base::CShowEtCO2UpdateInterface *pInterface, bool bCutWatch) = 0;
		/*******************************************************************************/
		// �������ƣ� OnWatchSpO2Handle
		// ���ܣ� ����/�Ͽ�SpO2�ļ���
		// ������
		//        IDistributeSimulateData  *pDistributeInterface: �����ɷ��ӿ�
		//        BOOL bCutWatch:
		// ����ֵ:  
		virtual void OnWatchSpO2Handle(IDistributeSimulateData  *pDistributeInterface, base::CShowSpO2UpdateInterface *pInterface, bool bCutWatch) = 0;
		/*******************************************************************************/
		// �������ƣ� OnWatchABPHandle
		// ���ܣ� ����/�Ͽ�ABP�ļ���
		// ������
		//        IDistributeSimulateData  *pDistributeInterface: �����ɷ��ӿ�
		//        CShowABPUpdateInterface *pInterface
		//        BOOL bCutWatch:
		// ����ֵ:  
		virtual void OnWatchABPHandle(IDistributeSimulateData  *pDistributeInterface, base::CShowABPUpdateInterface *pInterface, bool bCutWatch) = 0;
	public:
		//�����ĵ�ͼģ�����ӿ�
		inline base::COpECGBuildInterface * Get_OpECGBuildInterfacePtr() { return m_pOpECGBuildInterface; };
		//����Ѫ��ģ�����ӿ�
		inline base::COpSpO2BuildInterface * Get_OpSpO2BuildInterfacePtr() { return m_pOpSpO2BuildInterface; };
		//���غ���������̼Ũ�ȷ�ѹģ�����ӿ�
		inline base::COpEtCO2BuildInterface * Get_OpEtCO2BuildInterfacePtr() { return m_pEtCO2BuildInterface; };
		//���غ���ģ�����ӿ�
		inline base::COpRespBuildInterface * Get_OpRespBuildInterfacePtr() { return m_pRespBuildInterface; };
		//�����д�Ѫѹģ�����ӿ�
		inline base::COpABPBuildInterface  * Get_OpABPBuildInterface() { return m_pABPBuildInterface; };
	public:
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
	};

}}
