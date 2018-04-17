#pragma once
#include <list>
#include "..\Common\CommonGlobal.h"


namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ���������޸Ĳ����ӿ���
	�����ˣ�	 hjg
	����ʱ�䣺   2017/2/23
	//-----------------------------------------------------------------------------------------------------------------*/
	class CXActionVirtual;
	class ISetSimulateSymptoms
	{
	public:
		ISetSimulateSymptoms(void);
		virtual ~ISetSimulateSymptoms(void);
	public:
		/*******************************************************************************/
		// �������ƣ� initialScenario
		// ���ܣ�   ����������ʼ��Ϊ��ǰ����״̬
		// ������   CList<CXActionVirtual *, CXActionVirtual *> lstActions: 
		// ����ֵ:  tag_TrendValue: ��ǰ���������õ�����ֵ
		virtual void initialScenarioSet(std::list<CXActionVirtual *> *plstActions, SimulatePatientType ePatientType) = 0;
		/*******************************************************************************/
		// �������ƣ� modifyScenario
		// ���ܣ�   �޸ĵ�ǰ����״̬����������ֵ
		// ������   CList<CXActionVirtual *, CXActionVirtual *> lstActions: 
		//          eEventSign eEventValue:  ����ת�����¼��ź�
		//          BOOL bExecActions:       �Ƿ�ִ������
		//          short sTransferTime:
		// ����ֵ:  tag_TrendValue: ��ǰ���������õ�����ֵ
		virtual void modifyScenarioSet(std::list<CXActionVirtual *> *plstActions, eEventSign eEventValue, bool bExecActions = true, short sTransferTime = 0) = 0;
		//��ʼ������ģ�����߹�����
		virtual void initialSimulateSymptomsBuild(SimulatePatientType ePatientType) = 0;
	};
}}