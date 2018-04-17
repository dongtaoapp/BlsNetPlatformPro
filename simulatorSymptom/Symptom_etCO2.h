#pragma once
#include ".\symptomvirtual.h"

#include "..\SimulatorBase\OpEtCO2BuildInterface.h"


namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ģ���˵ĺ���ĩ������̼��ѹ
	�����ˣ�	 hjg
	����ʱ�䣺   2008/10/22
	//-----------------------------------------------------------------------------------------------------------------*/

	class CSymptom_etCO2 : public CSymptomVirtual
	{
	public:
		CSymptom_etCO2(void);
		virtual ~CSymptom_etCO2(void);
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
		// ����ֵ: 
		virtual  void InitialSymptomValue(IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType);
		/*******************************************************************************/
		// �������ƣ� InitialSymptomValue
		// ���ܣ�   ��ʼ������ֵ
		// ������   
		//          CXActionVirtual *pVirAction:         ��Ӧ����ֵ
		//          short sTransTime:                    ת��ʱ�䣨��λ���룩
		// ����ֵ: 
		virtual  void InitialSymptomValue(CXActionVirtual *pVirAction, short sTransTime = 0);
		// �������ƣ� OnUpdateInterfaceShow
		// ���ܣ�   ���½�����ʾ
		// ������   
		// ����ֵ: 
		virtual  void OnUpdateInterfaceShow() { };
	public:
		//��ʼ������ĩCO2ģ�����߹�����
		void InitialetCO2Build(SimulatePatientType ePatientType);
		//�޸ĺ���ĩCO2ģ�����߹�����
		void ModifyetCO2Build(bool bClearIntubate=false);
	public:
		//���ú���ĩ������̼ģ�⹹���������ӿ�
		inline void SetEtCO2BuildInterface(base::COpEtCO2BuildInterface *pInterface) { m_pEtCO2BuildInterface = pInterface; };
		inline base::COpEtCO2BuildInterface * GetEtCO2BuildInterface() { return m_pEtCO2BuildInterface; };
		inline int  GetValue_EtCO2() { return m_nEtCO2Value; };
	protected:
		base::COpEtCO2BuildInterface   *m_pEtCO2BuildInterface; //����ĩ������̼ģ�⹹���������ӿ�
	protected:
		int                       m_nEtCO2Value;
	};
}}