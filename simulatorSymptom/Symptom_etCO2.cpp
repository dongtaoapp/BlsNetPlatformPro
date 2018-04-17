#include ".\symptom_etco2.h"
#include ".\IModifiedSymptomsOp.h"
#include ".\XAction_etCO2.h"

#include "..\ElementParse\SAction_etCO2.h"


namespace jysoft { namespace simulator 
{
	CSymptom_etCO2::CSymptom_etCO2(void)
	{
		m_pEtCO2BuildInterface = NULL;
	}

	CSymptom_etCO2::~CSymptom_etCO2(void)
	{
	}

	/*******************************************************************************/
	// �������ƣ� IsKindOf
	// ���ܣ�   �ж����������
	// ������   const CString &strClassName
	// ����ֵ: 
	bool CSymptom_etCO2::isKindOf( const std::string &strClassName )
	{	
		if( strClassName == "CSymptom_etCO2" )
		{
			return true;
		}
		return false;
	}

	//���ݱ�ʾ�����ж���������
	bool  CSymptom_etCO2::isSymptomCaption(const std::string &strCaption)
	{
		return CSAction_etCO2::isAction_etCO2( strCaption );
	}

	/*******************************************************************************/
	// �������ƣ� InitialSymptomValue
	// ���ܣ�   ��ʼ������ֵ
	// ������   IModifiedSymptomsOp *pInterfacePtr
	// ����ֵ: 
	void CSymptom_etCO2::InitialSymptomValue(IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType)
	{
		m_pModifiedSymptomsOp  = pInterfacePtr;
		//����Ĭ��etCO2ֵ
		m_nEtCO2Value   = 34;
		
		pInterfacePtr->AddNewModifiedSymptom( this );
	}

	/*******************************************************************************/
	// �������ƣ� InitialSymptomValue
	// ���ܣ�   ��ʼ������ֵ
	// ������   
	//          CXActionVirtual *pVirAction:         ��Ӧ����ֵ
	//          short sTransTime:                    ת��ʱ�䣨��λ���룩
	// ����ֵ: 
	void CSymptom_etCO2::InitialSymptomValue(CXActionVirtual *pVirAction, short sTransTime/*=0*/)
	{
	#ifdef _DEBUG
		if( pVirAction == NULL || !pVirAction->isActionNameOf( CSAction_etCO2::getAction_etCO2_Caption() ) )
		{
			BOOST_ASSERT( 0 );
		}
	#endif 
		CXAction_etCO2 *pAction_etCO2 = (CXAction_etCO2 *)pVirAction;
		
		if( sTransTime == 0 && m_nEtCO2Value != pAction_etCO2->GetValue_AbsoluteEtCO2( m_nEtCO2Value ) )
		{
			m_nEtCO2Value = pAction_etCO2->GetValue_AbsoluteEtCO2( m_nEtCO2Value );

			m_pModifiedSymptomsOp->AddNewModifiedSymptom( this );
		}
	}

	//��ʼ������ĩCO2ģ�����߹�����
	void CSymptom_etCO2::InitialetCO2Build(SimulatePatientType ePatientType)
	{
		if( m_pEtCO2BuildInterface != NULL )
		{
			m_pEtCO2BuildInterface->InitializeBuild( m_nEtCO2Value );
		}
	}

	//�޸ĺ���ĩCO2ģ�����߹�����
	void CSymptom_etCO2::ModifyetCO2Build(bool bClearIntubate /*=false*/)
	{
		if( m_pEtCO2BuildInterface != NULL )
		{
			if( bClearIntubate  )
			{
				m_pEtCO2BuildInterface->OnIntubateEventOp( false );
			}
			//�޸ķ�ѹֵ
			m_pEtCO2BuildInterface->OnModifyCO2PercentValue( m_nEtCO2Value );
		}
	}
}}
