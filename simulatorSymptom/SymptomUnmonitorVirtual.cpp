#include ".\symptomunmonitorvirtual.h"


namespace jysoft { namespace simulator 
{
	CSymptomUnmonitorVirtual::CSymptomUnmonitorVirtual(void)
	{
	}

	CSymptomUnmonitorVirtual::~CSymptomUnmonitorVirtual(void)
	{
	}

	/*******************************************************************************/
	// �������ƣ� IsKindOf
	// ���ܣ�   �ж����������
	// ������   const CString &strClassName
	// ����ֵ: 
	bool CSymptomUnmonitorVirtual::isKindOf( const std::string &strClassName )
	{
		if( strClassName == "CSymptomUnmonitorVirtual" )
		{
			return true;
		}
		return false;
	}

	/*******************************************************************************/
	// �������ƣ� InitialSymptomValue
	// ���ܣ�   ��ʼ������ֵ
	// ������   IModifiedSymptomsOp *pInterfacePtr
	//          tag_TrendValue *pDefaultTrendValue:  ��Ӧ�����޸ĵ�ֵ����
	// ����ֵ: 
	void CSymptomUnmonitorVirtual::InitialSymptomValue( IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType)
	{
		BOOST_ASSERT( 0 );
	}

	/*******************************************************************************/
	// �������ƣ� InitialSymptomValue
	// ���ܣ�   ��ʼ������ֵ
	// ������   
	//          tag_TrendValue *pDefaultTrendValue:  ��Ӧ�����޸ĵ�ֵ����
	//          CXActionVirtual *pVirAction:         ��Ӧ����ֵ
	//          short sTransTime:                    ת��ʱ�䣨��λ���룩
	// ����ֵ: 
	void CSymptomUnmonitorVirtual::InitialSymptomValue( CXActionVirtual *pVirAction, short sTransTime/*=0*/)
	{
		BOOST_ASSERT( m_pModifiedSymptomsOp != NULL );
		ModifyUnmonitorSymptomValue( m_pModifiedSymptomsOp, pVirAction );
	}
}}
