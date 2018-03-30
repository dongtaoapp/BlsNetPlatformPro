#pragma once
#include ".\ShowECGUpdateInterface.h"
#include ".\ShowNIBPUpdateInterface.h"
#include ".\ShowPaceUpdateInterface.h"
#include ".\ShowRespRateUpdateInterface.h"


namespace jysoft { namespace simulator {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����    ģ��������״̬�ؼ���ʾ�ӿڼ��ϣ������Լ��ķγ�����
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORBASESHARED_EXPORT CSymptomsShowInterfacesAggregate
	{
	public:
		CSymptomsShowInterfacesAggregate(void);
		virtual ~CSymptomsShowInterfacesAggregate(void);
	protected:
		//�ĵ�ͼ��ʾ�ӿ�
		base::CShowECGUpdateInterface               *m_pShowECGInterface;
		//EMD��ʾ�ӿ�
		base::CShowECGUpdateInterface               *m_pShowEMDInterface;
		//Ѫѹ��ʾ�ӿ�
		base::CShowNIBPUpdateInterface              *m_pShowNIBPInterface;
		//����ģʽ��ʾ�ӿ�
		base::CShowRespRateUpdateInterface          *m_pShowRespInterface;
		//��������ʾ�ӿ�
		base::CShowPaceUpdateInterface              *m_pShowPaceInterface;
	public:
		//�Ͽ�ģ��������״̬�ؼ���ʾ�ӿڼ���
		virtual void OnCutSymptomShowInterfacesAggregate() = 0;
	public:
		//�����ĵ�ͼ��ʾ�ӿ�
		void Set_ShowECGUpdateInterfacePtr(base::CShowECGUpdateInterface *pShowECGInterface);
		//����EMD��ʾ�ӿ�
		void Set_ShowEMDUpdateInterfacePtr(base::CShowECGUpdateInterface *pShowEMDInterface);
		//����ģʽ��ʾ�ӿ�
		void Set_ShowRespUpdateInterfacePtr(base::CShowRespRateUpdateInterface *pShowRespInterface);
		//Ѫѹ��ʾ�ӿ�
		void Set_ShowNIBPUpdateInterfacePtr(base::CShowNIBPUpdateInterface *pShowNIBPUpdateInterface);
		//
		void Set_ShowPaceUpdateInterfacePtr(base::CShowPaceUpdateInterface *pShowPaceInterface);
	public:
		//�����ĵ�ͼ��ʾ�ӿ�
		inline base::CShowECGUpdateInterface * Get_ShowECGUpdateInterfacePtr() { return m_pShowECGInterface; };
		//����EMD��ʾ�ӿ�
		inline base::CShowECGUpdateInterface * Get_ShowEMDUpdateInterfacePtr() { return m_pShowEMDInterface; };
		//����Ѫѹ��ʾ�ӿ�
		inline base::CShowNIBPUpdateInterface * Get_ShowNIBPUpdateInterfacePtr() { return m_pShowNIBPInterface; };
		//���غ���ģʽ��ʾ�ӿ�
		inline base::CShowRespRateUpdateInterface * Get_ShowRespUpdateInterfacePtr() { return m_pShowRespInterface; };
		//������������ʾ�ӿ�
		inline base::CShowPaceUpdateInterface * Get_ShowPaceUpdateInterfacePtr() { return m_pShowPaceInterface; };
	protected:
		/*******************************************************************************/
		// �������ƣ� InitialSimulatorSymptomShowInterfacesAggregate
		// ���ܣ� ��ȡģ��������״̬�ؼ������е���Ϣ��ʾ�ӿ�
		// ע������ΪNULL����ʾ���������Ϣ��ʾ�ӿ�
		// ����ֵ:  
		virtual void InitialSimulatorSymptomShowInterfacesAggregate( ) = 0;
	};
}}

