#pragma once
#include ".\symptomvirtual.h"
#include ".\XActionVirtual.h"

#include "..\SimulatorBase\SimulatorOrderIrp.h"
#include "..\SimulatorBase\SymptomsShowInterfacesAggregate.h"


namespace jysoft { namespace simulator {
	//AED��ص���
	class CSymptom_CellColumn : public CSymptomVirtual
	{
	public:
		CSymptom_CellColumn(void);
		virtual ~CSymptom_CellColumn(void);
	public: 
		/*******************************************************************************/
		// �������ƣ� IsKindOf
		// ���ܣ�   �ж����������
		// ������   const CString &strClassName
		// ����ֵ: 
		virtual  bool isKindOf( const std::string &strClassName );
		//���ݱ�ʾ�����ж���������
		virtual  bool isSymptomCaption(const std::string &strCaption);
		/*******************************************************************************/
		// �������ƣ� InitialSymptomValue
		// ���ܣ�   ��ʼ������ֵ
		// ������   IModifiedSymptomsOp *pInterfacePtr
		// ����ֵ: 
		virtual  void InitialSymptomValue(IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType);
		/*******************************************************************************/
		// �������ƣ� InitialSymptomValue
		// ���ܣ�   ��ʼ������ֵ
		// ������   
		//          tag_TrendValue *pDefaultTrendValue:  ��Ӧ�����޸ĵ�ֵ����
		//          CXActionVirtual *pVirAction:         ��Ӧ����ֵ
		//          short sTransTime:                    ת��ʱ�䣨��λ���룩
		// ����ֵ: 
		virtual  void InitialSymptomValue(CXActionVirtual *pVirAction, short sTransTime = 0);
		/*******************************************************************************/
		// �������ƣ� isTransmitAEDState
		// ���ܣ�   �Ƿ�AED״̬�ı�
		// ������   
		//          /*in,out*/unsigned char *sAEDState:        AED״̬
		// ����ֵ: 
		virtual  bool isTransmitAEDState(/*in,out*/unsigned char *sAEDState);
	protected:
		bool             m_bNatural;
	};
}}