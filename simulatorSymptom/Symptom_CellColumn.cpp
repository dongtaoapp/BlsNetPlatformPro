#include ".\Symptom_CellColumn.h"
#include ".\XAction_CellColumn.h"
#include ".\IModifiedSymptomsOp.h"

#include "..\elementParse\SAction_CellColumn.h"


namespace jysoft { namespace simulator 
{
	CSymptom_CellColumn::CSymptom_CellColumn(void)
	{
		m_bNatural = true;
	}

	CSymptom_CellColumn::~CSymptom_CellColumn(void)
	{
	}

    /*******************************************************************************/
	// �������ƣ� IsKindOf
	// ���ܣ�   �ж����������
	// ������   const CString &strClassName
	// ����ֵ: 
	bool CSymptom_CellColumn::isKindOf( const std::string &strClassName )
	{
		if( strClassName == "CSymptom_CellColumn" )
		{
			return true;
		}
		return false;
	}

	//���ݱ�ʾ�����ж���������
	bool CSymptom_CellColumn::isSymptomCaption(const std::string &strCaption)
	{
		return CSAction_CellColumn::isAction_CellColumn( strCaption );
	}

	/*******************************************************************************/
	// �������ƣ� InitialSymptomValue
	// ���ܣ�   ��ʼ������ֵ
	// ������   IModifiedSymptomsOp *pInterfacePtr
	// ����ֵ: 
	void CSymptom_CellColumn::InitialSymptomValue(IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType)
	{
		m_pModifiedSymptomsOp  = pInterfacePtr;
		//AED��������
		m_bNatural = true;

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
	void CSymptom_CellColumn::InitialSymptomValue(CXActionVirtual *pVirAction, short sTransTime)
	{
	#ifdef _DEBUG
		if( pVirAction == NULL || !pVirAction->isActionNameOf( CSAction_CellColumn::getAction_CellColumn_Caption() ) )
		{
			BOOST_ASSERT( 0 );
		}
	#endif 
		CXAction_CellColumn *pActionCellColumn = (CXAction_CellColumn *)pVirAction;
		if( m_bNatural != pActionCellColumn->getValue_isNatural() )
		{
			m_bNatural = pActionCellColumn->getValue_isNatural();

			m_pModifiedSymptomsOp->AddNewModifiedSymptom( this );
		}
	}

	/*******************************************************************************/
	// �������ƣ� isTransmitAEDState
	// ���ܣ�   �Ƿ�AED״̬�ı�
	// ������   
	//          /*in,out*/unsigned char *sAEDState:        AED״̬
	// ����ֵ: 
	bool CSymptom_CellColumn::isTransmitAEDState(/*in,out*/unsigned char *sAEDState)
	{
		if( sAEDState != NULL )
		{
			*sAEDState |= (m_bNatural ? 0x00 : 0x08);
		}
		return true;
	}

}}
