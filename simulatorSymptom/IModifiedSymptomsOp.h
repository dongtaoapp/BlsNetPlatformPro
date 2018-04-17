#pragma once
#include <list>
#include ".\simulatorsymptom_global.h"

#include "..\common\criticalmutex.h"

#include "..\SimulatorBase\ITransportOrderIrpToSimulator.h"

namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ��ʶ���ռ����޸ĵ������Ľӿ���
	�����ˣ�	 hjg
	����ʱ�䣺   2008/10/20
	//-----------------------------------------------------------------------------------------------------------------*/
	class CSymptomVirtual;
    class SIMULATORSYMPTOMSHARED_EXPORT IModifiedSymptomsOp
	{
	public:
		IModifiedSymptomsOp(void);
		virtual ~IModifiedSymptomsOp(void);
	public:
		/*******************************************************************************/
		// �������ƣ� AddNewModifiedSymptom
		// ���ܣ�   ��ӱ��޸ĵ��������ռ���������Ҫ����Ψһ��
		// ������   CSymptomVirtual *pVirSymptom
		// ����ֵ:  
		virtual void AddNewModifiedSymptom(CSymptomVirtual *pVirSymptom);
		/*******************************************************************************/
		// �������ƣ� RemoveAllModifiedSymptoms
		// ���ܣ�   �Ƴ������ռ�������
		// ������   
		// ����ֵ:  
		virtual void RemoveAllModifiedSymptoms();
		/*******************************************************************************/
		// �������ƣ� TransmitSimulatorOrders
		// ���ܣ� ����ģ��������ͨ��ָ��
		// ������        
		// ����ֵ:
		virtual void TransmitSimulatorOrders() = 0;
		/*******************************************************************************/
		// �������ƣ� ModifiedSymptomsUpdateShow
		// ���ܣ� ���޸ĵĲ���������ʾ
		// ������ 
		//        bool bClearModifiedFlag:      �Ƿ�����޸ı�ʶ   
		// ����ֵ:
		virtual void ModifiedSymptomsUpdateShow( bool bClearModifiedFlag ) = 0;
	public:
		bool findModifiedSymptom(CSymptomVirtual *pVirSymptom);
		//������޸������ı�ʶ
		void emptyModifiedSymptomsFlag();
	protected:
		utility::CCriticalMutex               m_cMutex;
		std::list<CSymptomVirtual *>          modifiedSymptoms;
	};
}}
