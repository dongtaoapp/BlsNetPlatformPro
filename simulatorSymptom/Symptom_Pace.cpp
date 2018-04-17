#include ".\symptom_pace.h"
#include ".\IModifiedSymptomsOp.h"
#include ".\XAction_Pace.h"

#include "..\Common\DecodeUtil.h"

#include "..\ElementParse\SAction_Pace.h"


using namespace jysoft::simulator::base;
namespace jysoft { namespace simulator 
{
	CSymptom_Pace::CSymptom_Pace(void)
	{
		m_pShowPaceInterface  = NULL;
	}

	CSymptom_Pace::~CSymptom_Pace(void)
	{
	}

	/*******************************************************************************/
	// �������ƣ� IsKindOf
	// ���ܣ�   �ж����������
	// ������   const CString &strClassName
	// ����ֵ: 
	bool CSymptom_Pace::isKindOf( const std::string &strClassName )
	{
		if( strClassName == "CSymptom_Pace" )
		{
			return true;
		}
		return false;
	}

	//���ݱ�ʾ�����ж���������
	bool CSymptom_Pace::isSymptomCaption(const std::string &strCaption)
	{
		return CSAction_Pace::isAction_Pace( strCaption );
	}

	/*******************************************************************************/
	// �������ƣ� InitialSymptomValue
	// ���ܣ�   ��ʼ������ֵ
	// ������   IModifiedSymptomsOp *pInterfacePtr
	//          tag_TrendValue *pDefaultTrendValue:  ��Ӧ�����޸ĵ�ֵ����
	// ����ֵ: 
	void CSymptom_Pace::InitialSymptomValue(IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType)
	{
		m_pModifiedSymptomsOp  = pInterfacePtr;
		//����Ĭ��ֵ
		m_bEnablePace     = TRUE;
		m_sData           = 20;

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
	void CSymptom_Pace::InitialSymptomValue(CXActionVirtual *pVirAction, short sTransTime/*=0*/)
	{
	#ifdef _DEBUG
		if( pVirAction == NULL || !pVirAction->isActionNameOf( CSAction_Pace::getAction_Pace_Caption() ) )
		{
			BOOST_ASSERT( 0 );
		}
	#endif 
		CXAction_Pace  *pAction_Pace = (CXAction_Pace *)pVirAction;
		m_sData       = pAction_Pace->GetValue_PaceElectricData();
		m_bEnablePace = pAction_Pace->GetValue_EnablePace();

		m_pModifiedSymptomsOp->AddNewModifiedSymptom( this );
	}

	// �������ƣ� OnUpdateInterfaceShow
	// ���ܣ�   ���½�����ʾ
	// ������   
	// ����ֵ: 
	void CSymptom_Pace::OnUpdateInterfaceShow()
	{
		if( m_pShowPaceInterface != NULL )
		{
			m_pShowPaceInterface->OnShowPaceset( m_bEnablePace, m_sData );
		}
	}

	/*******************************************************************************/
	// �������ƣ� OnLinkSimulatorBarUpdateInterfaceShow
	// ���ܣ�   �Ͽ�ģ���������ʾ����
	// ������   
	// ����ֵ:
	void CSymptom_Pace::OnLinkSimulatorBarUpdateInterfaceShow(CSymptomsShowInterfacesAggregate *pShowAggregate )
	{
		//��������ʾ�ӿ�
		CShowPaceUpdateInterface  *pShowInterface = pShowAggregate->Get_ShowPaceUpdateInterfacePtr();
		if( m_pShowPaceInterface == NULL )
		{
			m_pShowPaceInterface = pShowInterface;
		}
		else if( pShowInterface != NULL )
		{
			m_pShowPaceInterface->SetNextInterfacePtr( pShowInterface );
		}
		if( pShowInterface != NULL )
		{
			pShowInterface->LinkUpdateShow();
			pShowInterface->OnShowPaceset( m_bEnablePace, m_sData );
		}
	}

	/*******************************************************************************/
	// �������ƣ� OnUnLinkSimulatorBarUpdateInterfaceShow
	// ���ܣ�   �Ͽ�ģ���������ʾ����
	// ������   
	// ����ֵ:
	void CSymptom_Pace::OnUnLinkSimulatorBarUpdateInterfaceShow(CSymptomsShowInterfacesAggregate *pShowAggregate )
	{
		//��������ʾ�ӿ�
		CShowPaceUpdateInterface  *pShowInterface = pShowAggregate->Get_ShowPaceUpdateInterfacePtr();
		if( pShowInterface != NULL )
		{
			m_pShowPaceInterface = (CShowPaceUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowPaceInterface, pShowInterface);
			//�Ͽ���ʾ����
			pShowInterface->UnLinkUpdateShow();
		}
	}
}}
