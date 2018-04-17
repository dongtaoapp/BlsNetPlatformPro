#pragma once
#include ".\physiologywatchbar_global.h"

#include "..\Common\CommonGlobal.h"

#include "..\SimulatorBase\OpPhysBuildInterfacesAggregate.h"

namespace jysoft { namespace controls { 

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ��������ֵģ����ӿؼ������ӿ�
	�����ˣ�	 hjg
	����ʱ�䣺   2008/8/12
	//-----------------------------------------------------------------------------------------------------------------*/
    class PHYSIOLOGYWATCHBARSHARED_EXPORT IWatchBarsHandle
	{
	public:
		IWatchBarsHandle(void);
		virtual ~IWatchBarsHandle(void);
	public:
		/*******************************************************************************/
		// �������ƣ� OnClearSimulateTypeDefineHandle
		// ���ܣ� ���ģ����ӿؼ���ص�ģ���˶���ʹ���ص�ģ��������δָ��
		// ������
		// ����ֵ:  
		virtual void OnClearSimulateTypeDefineHandle() = 0;
		/*******************************************************************************/
		// �������ƣ� OnClearSimulateTypeDefineHandle
		// ���ܣ� ����ģ����ӿؼ���ص�ģ���˶���ʹ���ص�ģ��������ָ��
		// ������
		//        SimulatePatientType ePatientType�� ģ�������� 
		// ����ֵ:  
		virtual void OnDefineWatchedSimulateTypeHandle(SimulatePatientType ePatientType) = 0;
		/*******************************************************************************/
		// �������ƣ� OnClearSimulateTypeDefineHandle
		// ���ܣ� ����ģ����ӿؼ���ص�ģ���˶���ʹ���ص�ģ��������ָ��
		// ������
		//        SimulatePatientType ePatientType�� ģ�������� 
		//        COpPhysBuildInterfacesAggregate *pBuildInterfacesAggregate: 
		// ����ֵ:  
		virtual void OnDefineWatchedSimulateTypeHandle(SimulatePatientType ePatientType, simulator::COpPhysBuildInterfacesAggregate *pBuildInterfacesAggregate) = 0;
		/*******************************************************************************/
		// �������ƣ� OnStartWatchPhysBuilds
		// ���ܣ� ��������ֵģ����ӿؼ���ʼ�����������ģ����������
		// ������
		//        COpPhysBuildInterfacesAggregate *pBuildInterfacesAggregate: 
		// ����ֵ:  
		virtual void OnStartWatchPhysBuilds( simulator::COpPhysBuildInterfacesAggregate *pBuildInterfacesAggregate ) = 0;
		/*******************************************************************************/
		// �������ƣ� OnStartWatchPhysBuilds
		// ���ܣ� ��������ֵģ����ӿؼ��Ͽ�����������ģ�����ļ��
		// ������
		//        COpPhysBuildInterfacesAggregate *pBuildInterfacesAggregate: 
		// ����ֵ:  
		virtual void OnCutWatchPhysBuilds( simulator::COpPhysBuildInterfacesAggregate *pBuildInterfacesAggregate ) = 0;
		/*******************************************************************************/
		// �������ƣ� OnFreezedEcgAndSpO2AndABP
		// ���ܣ� Freeze��������ֵģ����ӿؼ��е�ECG, SpO2, ABP
		// ������
		//        BOOL bFreezed: 
		// ����ֵ:  
		virtual void OnFreezedEcgAndSpO2AndABP( simulator::COpPhysBuildInterfacesAggregate *pBuildInterfacesAggregate, BOOL bFreezed ) = 0;
		/*******************************************************************************/
		// �������ƣ� OnFreezedRespAndEtCO2
		// ���ܣ� Freeze��������ֵģ����ӿؼ��е�Resp��EtCO2
		// ������
		//        BOOL bFreezed: 
		// ����ֵ:  
		virtual void OnFreezedRespAndEtCO2(simulator::COpPhysBuildInterfacesAggregate *pBuildInterfacesAggregate,  BOOL bFreezed ) = 0;
	};
}}
