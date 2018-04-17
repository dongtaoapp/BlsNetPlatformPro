#include ".\Symptom_ContactPatient.h"

#include "..\elementParse\SAction_ContactPatient.h"


namespace jysoft { namespace simulator 
{
	CSymptom_ContactPatient::CSymptom_ContactPatient(void)
	{
		m_bContactPatient = false;
	}

	CSymptom_ContactPatient::~CSymptom_ContactPatient(void)
	{
	}

	/*******************************************************************************/
	// �������ƣ� IsKindOf
	// ���ܣ�   �ж����������
	// ������   const CString &strClassName
	// ����ֵ: 
	bool CSymptom_ContactPatient::isKindOf( const std::string &strClassName )
	{
		if( strClassName == "CSymptom_ContactPatient" )
		{
			return true;
		}
		return false;
	}

	//���ݱ�ʾ�����ж���������
	bool CSymptom_ContactPatient::isSymptomCaption(const std::string &strCaption)
	{
		return CSAction_ContactPatient::isAction_ContactPatient( strCaption );
	}

	/*******************************************************************************/
	// �������ƣ� InitialSymptomValue
	// ���ܣ�   ��ʼ������ֵ
	// ������   IModifiedSymptomsOp *pInterfacePtr
	// ����ֵ: 
	void CSymptom_ContactPatient::InitialSymptomValue(IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType)
	{
	}

	/*******************************************************************************/
	// �������ƣ� InitialSymptomValue
	// ���ܣ�   ��ʼ������ֵ
	// ������   
	//          tag_TrendValue *pDefaultTrendValue:  ��Ӧ�����޸ĵ�ֵ����
	//          CXActionVirtual *pVirAction:         ��Ӧ����ֵ
	//          short sTransTime:                    ת��ʱ�䣨��λ���룩
	// ����ֵ: 
	void CSymptom_ContactPatient::InitialSymptomValue(CXActionVirtual *pVirAction, short sTransTime)
	{
	}

	/*******************************************************************************/
	// �������ƣ� isTransmitAEDState
	// ���ܣ�   �Ƿ�AED״̬�ı�
	// ������   
	//          /*in,out*/unsigned char *sAEDState:        AED״̬
	// ����ֵ: 
	bool CSymptom_ContactPatient::isTransmitAEDState(/*in,out*/unsigned char *sAEDState)
	{
		if( sAEDState != NULL )
		{
			*sAEDState |= (m_bContactPatient ? 0x04 : 0x00);
		}
		return true;
	}
}}
