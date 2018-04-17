#include ".\Symptom_Defibri.h"
#include ".\XAction_Defibri.h"
#include ".\IModifiedSymptomsOp.h"

#include "..\elementParse\SAction_Defibrillate.h"

namespace jysoft { namespace simulator 
{
	CSymptom_Defibri::CSymptom_Defibri(void)
	{
		m_bEnableDefibri = true;
		m_bClearCount = false;
	}

	CSymptom_Defibri::~CSymptom_Defibri(void)
	{
	}

	/*******************************************************************************/
	// �������ƣ� IsKindOf
	// ���ܣ�   �ж����������
	// ������   const CString &strClassName
	// ����ֵ: 
	bool CSymptom_Defibri::isKindOf( const std::string &strClassName )
	{
		if( strClassName == "CSymptom_Defibri" )
		{
			return true;
		}
		return false;
	}

	//���ݱ�ʾ�����ж���������
	bool CSymptom_Defibri::isSymptomCaption(const std::string &strCaption)
	{
		return CSAction_Defibrillate::isAction_Defibri( strCaption );
	}

	/*******************************************************************************/
	// �������ƣ� InitialSymptomValue
	// ���ܣ�   ��ʼ������ֵ
	// ������   IModifiedSymptomsOp *pInterfacePtr
	// ����ֵ: 
	void CSymptom_Defibri::InitialSymptomValue(IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType)
	{
		m_pModifiedSymptomsOp  = pInterfacePtr;
		//�����ܳ���
		m_bEnableDefibri = true;
		m_bClearCount = false;

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
	void CSymptom_Defibri::InitialSymptomValue(CXActionVirtual *pVirAction, short sTransTime)
	{
	#ifdef _DEBUG
		if( pVirAction == NULL || !pVirAction->isActionNameOf( CSAction_Defibrillate::getAction_Defibri_Caption() ) )
		{
			BOOST_ASSERT( 0 );
		}
	#endif 
		CXAction_Defibri *pActionDefibr = (CXAction_Defibri *)pVirAction;
		//�Ƿ��ܳ���
		m_bEnableDefibri = pActionDefibr->getValue_EnableDefibri();
		//ȥ����������
		m_bClearCount = pActionDefibr->getValue_ClearCount();

		m_pModifiedSymptomsOp->AddNewModifiedSymptom( this );
	}

	/*******************************************************************************/
	// �������ƣ� isTransmitAEDState
	// ���ܣ�   �Ƿ�AED״̬�ı�
	// ������   
	//          /*in,out*/unsigned char *sAEDState:        AED״̬
	// ����ֵ: 
	bool CSymptom_Defibri::isTransmitAEDState(/*in,out*/unsigned char *sAEDState)
	{
		if( sAEDState != NULL )
		{
			*sAEDState |= (m_bEnableDefibri ? 0x01 : 0x00);
		}
		return true;
	}
}}
