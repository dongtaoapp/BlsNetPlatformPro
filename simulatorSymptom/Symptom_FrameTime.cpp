#include ".\Symptom_FrameTime.h"
#include ".\XAction_FrameTime.h"
#include ".\IModifiedSymptomsOp.h"

#include "..\elementParse\SAction_FrameTime.h"


namespace jysoft { namespace simulator 
{
	CSymptom_FrameTime::CSymptom_FrameTime(void)
	{
		m_lFrameTime    = 0;
	}
	
	CSymptom_FrameTime::~CSymptom_FrameTime(void)
	{
	}

	/*******************************************************************************/
	// �������ƣ� IsKindOf
	// ���ܣ�   �ж����������
	// ������   const CString &strClassName
	// ����ֵ: 
	bool CSymptom_FrameTime::isKindOf( const std::string &strClassName )
	{
		if( strClassName == "CSymptom_FrameTime" )
		{
			return true;
		}
		return false;
	}

	//���ݱ�ʾ�����ж���������
	bool CSymptom_FrameTime::isSymptomCaption(const std::string &strCaption)
	{
		return CSAction_FrameTime::isAction_FrameTime( strCaption );
	}

	/*******************************************************************************/
	// �������ƣ� InitialSymptomValue
	// ���ܣ�   ��ʼ������ֵ
	// ������   IModifiedSymptomsOp *pInterfacePtr
	// ����ֵ: 
	void CSymptom_FrameTime::InitialSymptomValue(IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType)
	{
		m_pModifiedSymptomsOp  = pInterfacePtr;
		//����Ĭ��ֵ
		m_lFrameTime  = 0;

		m_pModifiedSymptomsOp->AddNewModifiedSymptom( this );
	}

	/*******************************************************************************/
	// �������ƣ� InitialSymptomValue
	// ���ܣ�   ��ʼ������ֵ
	// ������   
	//          tag_TrendValue *pDefaultTrendValue:  ��Ӧ�����޸ĵ�ֵ����
	//          CXActionVirtual *pVirAction:         ��Ӧ����ֵ
	//          short sTransTime:                    ת��ʱ�䣨��λ���룩
	// ����ֵ: 
	void CSymptom_FrameTime::InitialSymptomValue(CXActionVirtual *pVirAction, short sTransTime)
	{
	#ifdef _DEBUG
		if( pVirAction == NULL || !pVirAction->isActionNameOf( CSAction_FrameTime::getAction_FrameTime_Caption() ) )
		{
			BOOST_ASSERT( 0 );
		}
	#endif 
		CXAction_FrameTime   *pAction_FrameTime = (CXAction_FrameTime *)pVirAction;
		m_lFrameTime  = pAction_FrameTime->GetValue_FrameTime();

		m_pModifiedSymptomsOp->AddNewModifiedSymptom( this );
	}

	//���ó�����ʱ��Ϊ0
	void CSymptom_FrameTime::ResetFrameTimeToZero()
	{
		m_lFrameTime   = 0;
		//���½�����ʾ
		OnUpdateInterfaceShow();
	}

	//���ӳ��������ʱ��
	void CSymptom_FrameTime::IncreaseFrameTime(long  lAddTime) 
	{ 
		m_lFrameTime += lAddTime; 
		//���½�����ʾ
		OnUpdateInterfaceShow();
	};
}}
