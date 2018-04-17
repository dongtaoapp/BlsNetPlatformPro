#pragma once
#include <list>
#include ".\symptomvirtual.h"
#include ".\XActionVirtual.h"

#include "..\SimulatorBase\OpSpO2BuildInterface.h"


namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ģ���˵�Ѫ��
	�����ˣ�	 hjg
	����ʱ�䣺   2017/2/22
	//-----------------------------------------------------------------------------------------------------------------*/
	class CSymptom_SpO2 : public CSymptomVirtual
	{
	public:
		CSymptom_SpO2(void);
		virtual ~CSymptom_SpO2(void);
	public: //���ຯ������
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
		//          tag_TrendValue *pDefaultTrendValue:  ��Ӧ�����޸ĵ�ֵ����
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
		virtual  void InitialSymptomValue( CXActionVirtual *pVirAction, short sTransTime = 0);
		// �������ƣ� OnUpdateInterfaceShow
		// ���ܣ�   ���½�����ʾ
		// ������   
		// ����ֵ: 
		virtual  void OnUpdateInterfaceShow() { };
	public:
		//��ʼ��Ѫ��ģ�����߹�����
		void InitialSpO2Build(SimulatePatientType ePatientType);
		//�޸�Ѫ��ģ�����߹�����
		void ModifySpO2Build();
	public:
		//����Ѫ��ģ�⹹���������ӿ�
		inline void SetSpO2BuildInterface(base::COpSpO2BuildInterface *pInterface) { m_pSpO2BuildInterface = pInterface; };
		inline int  GetValue_SpO2() { return m_nSpO2Value; };
	protected:
		base::COpSpO2BuildInterface   *m_pSpO2BuildInterface; //Ѫ��ģ�⹹���������ӿ�
	protected:
		int                      m_nSpO2Value;
	};
}}