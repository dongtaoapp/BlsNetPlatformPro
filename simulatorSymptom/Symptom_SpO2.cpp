#include <algorithm>
#include <boost/foreach.hpp>
#include ".\symptom_spo2.h"
#include ".\IModifiedSymptomsOp.h"
#include ".\XAction_Osat.h"

#include "..\elementParse\SAction_Osat.h"


using namespace jysoft::simulator::base;
namespace jysoft { namespace simulator 
{
	CSymptom_SpO2::CSymptom_SpO2(void)
	{
		m_pSpO2BuildInterface  = NULL;
	}

	CSymptom_SpO2::~CSymptom_SpO2(void)
	{
	}

	/*******************************************************************************/
	// �������ƣ� IsKindOf
	// ���ܣ�   �ж����������
	// ������   const CString &strClassName
	// ����ֵ: 
	bool CSymptom_SpO2::isKindOf( const std::string &strClassName )
	{
		if( strClassName == "CSymptom_SpO2" )
		{
			return true;
		}
		return false;
	}

	//���ݱ�ʾ�����ж���������
	bool CSymptom_SpO2::isSymptomCaption(const std::string &strCaption)
	{
		return CSAction_Osat::isAction_Osat( strCaption );
	}

	/*******************************************************************************/
	// �������ƣ� InitialSymptomValue
	// ���ܣ�   ��ʼ������ֵ
	// ������   IModifiedSymptomsOp *pInterfacePtr
	// ����ֵ: 
	void CSymptom_SpO2::InitialSymptomValue(IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType)
	{
		m_pModifiedSymptomsOp  = pInterfacePtr;

		m_nSpO2Value  = 98;

		pInterfacePtr->AddNewModifiedSymptom( this );
	}

	/*******************************************************************************/
	// �������ƣ� InitialSymptomValue
	// ���ܣ�   ��ʼ������ֵ
	// ������   
	//          tag_TrendValue *pDefaultTrendValue:  ��Ӧ�����޸ĵ�ֵ����
	//          CXActionVirtual *pVirAction:         ��Ӧ����ֵ
	//          short sTransTime:                    ת��ʱ�䣨��λ���룩
	// ����ֵ: 
	void CSymptom_SpO2::InitialSymptomValue( CXActionVirtual *pVirAction, short sTransTime/*=0*/)
	{
	#ifdef _DEBUG
		if( pVirAction == NULL || !pVirAction->isActionNameOf( CSAction_Osat::getAction_Osat_Caption() ) )
		{
			BOOST_ASSERT( 0 );
		}
	#endif 	
		int   nSrcSpO2Value  = m_nSpO2Value;
		CXAction_Osat  *pAction_BloodOxygen = (CXAction_Osat *)pVirAction;
		if( sTransTime == 0 && pAction_BloodOxygen->GetValue_AbsoluteSpO2( nSrcSpO2Value ) != m_nSpO2Value )
		{
			m_nSpO2Value = pAction_BloodOxygen->GetValue_AbsoluteSpO2( nSrcSpO2Value );

			m_pModifiedSymptomsOp->AddNewModifiedSymptom( this );
		}
	}

	//��ʼ��Ѫ��ģ�����߹�����
	void CSymptom_SpO2::InitialSpO2Build(SimulatePatientType ePatientType)
	{
		if( m_pSpO2BuildInterface != NULL )
		{
			m_pSpO2BuildInterface->OnModifySpO2ValuePrecent( m_nSpO2Value );
		}
	}

	//�޸�Ѫ��ģ�����߹�����
	void CSymptom_SpO2::ModifySpO2Build()
	{
		if( m_pSpO2BuildInterface != NULL )
		{
			m_pSpO2BuildInterface->OnModifySpO2ValuePrecent( m_nSpO2Value );
		}
	}
}}
