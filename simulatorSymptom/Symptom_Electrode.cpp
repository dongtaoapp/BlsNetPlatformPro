#include ".\Symptom_Electrode.h"
#include ".\XAction_Electrode.h"
#include ".\IModifiedSymptomsOp.h"

#include "..\elementParse\SAction_Electrode.h"


namespace jysoft { namespace simulator 
{

	CSymptom_Electrode::CSymptom_Electrode(void)
	{
		m_bPosRight = true;
	}

	CSymptom_Electrode::~CSymptom_Electrode(void)
	{
	}

	/*******************************************************************************/
	// �������ƣ� IsKindOf
	// ���ܣ�   �ж����������
	// ������   const CString &strClassName
	// ����ֵ: 
	bool CSymptom_Electrode::isKindOf( const std::string &strClassName )
	{
		if( strClassName == "CSymptom_Electrode" )
		{
			return true;
		}
		return false;
	}

	//���ݱ�ʾ�����ж���������
	bool CSymptom_Electrode::isSymptomCaption(const std::string &strCaption)
	{
		return CSAction_Electrode::isAction_Electrode( strCaption );
	}

	/*******************************************************************************/
	// �������ƣ� InitialSymptomValue
	// ���ܣ�   ��ʼ������ֵ
	// ������   IModifiedSymptomsOp *pInterfacePtr
	// ����ֵ: 
	void CSymptom_Electrode::InitialSymptomValue(IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType)
	{
		m_pModifiedSymptomsOp  = pInterfacePtr;
		//�缫Ƭ������
		m_bPosRight = true;

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
	void CSymptom_Electrode::InitialSymptomValue(CXActionVirtual *pVirAction, short sTransTime)
	{
	#ifdef _DEBUG
		if( pVirAction == NULL || !pVirAction->isActionNameOf( CSAction_Electrode::getAction_Electrode_Caption() ) )
		{
			BOOST_ASSERT( 0 );
		}
	#endif 
		CXAction_Electrode *pActionElec = (CXAction_Electrode *)pVirAction;
		m_bPosRight = pActionElec->m_bPosRight;

		m_pModifiedSymptomsOp->AddNewModifiedSymptom( this );
	}

	/*******************************************************************************/
	// �������ƣ� isTransmitAEDState
	// ���ܣ�   �Ƿ�AED״̬�ı�
	// ������   
	//          /*in,out*/unsigned char *sAEDState:        AED״̬
	// ����ֵ: 
	bool CSymptom_Electrode::isTransmitAEDState(/*in,out*/unsigned char *sAEDState)
	{
		if( sAEDState != NULL )
		{
			*sAEDState |= (m_bPosRight ? 0x00 : 0x02);
		}
		return true;
	}
}}
