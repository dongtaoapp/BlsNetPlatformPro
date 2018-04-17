#include ".\symptom_pupil.h"
#include ".\IModifiedSymptomsOp.h"
#include ".\XAction_Pupil.h"

#include "..\Common\DecodeUtil.h"

#include "..\ElementParse\SAction_Pupil.h"


using namespace jysoft::simulator::base;
namespace jysoft { namespace simulator 
{
	CSymptom_Pupil::CSymptom_Pupil(void)
	{
		m_bNatural = false;
	}

	CSymptom_Pupil::~CSymptom_Pupil(void)
	{
	}

	/*******************************************************************************/
	// �������ƣ� IsKindOf
	// ���ܣ�   �ж����������
	// ������   const CString &strClassName
	// ����ֵ: 
	bool CSymptom_Pupil::isKindOf( const std::string &strClassName )
	{
		if( strClassName == "CSymptom_Pupil" )
		{
			return true;
		}
		return false;
	}

	//���ݱ�ʾ�����ж���������
	bool CSymptom_Pupil::isSymptomCaption(const std::string &strCaption)
	{
		return CSAction_Pupil::isAction_Pupil( strCaption );
	}

	/*******************************************************************************/
	// �������ƣ� InitialSymptomValue
	// ���ܣ�   ��ʼ������ֵ
	// ������   IModifiedSymptomsOp *pInterfacePtr
	// ����ֵ: 
	void CSymptom_Pupil::InitialSymptomValue(IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType)
	{
		m_pModifiedSymptomsOp  = pInterfacePtr;
		m_bNatural = false;

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
	void CSymptom_Pupil::InitialSymptomValue(CXActionVirtual *pVirAction, short sTransTime/*=0*/)
	{
	#ifdef _DEBUG
		if( pVirAction == NULL || !pVirAction->isActionNameOf( CSAction_Pupil::getAction_Pupil_Caption() ) )
		{
			BOOST_ASSERT( 0 );
		}
	#endif 	
		CXAction_Pupil *pAction_Pupil = (CXAction_Pupil *)pVirAction;
		if( m_bNatural != pAction_Pupil->getPupilState() )
		{
			m_bNatural = pAction_Pupil->getPupilState();

			m_pModifiedSymptomsOp->AddNewModifiedSymptom( this );
		}
	}
}}
