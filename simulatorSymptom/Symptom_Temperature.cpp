#include <math.h>
#include ".\symptom_temperature.h"
#include ".\IModifiedSymptomsOp.h"
#include ".\XActionVirtual.h"
#include ".\XAction_Temperature.h"

#include "..\ElementParse\SAction_Temperature.h"

#include "..\SimulatorBase\WatchBarsShowInterfacesAggregate.h"


using namespace jysoft::simulator::base;
namespace jysoft { namespace simulator 
{
	CSymptom_Temperature::CSymptom_Temperature(void)
	{
		m_pShowPTempValueInterface = NULL;
	}

	CSymptom_Temperature::~CSymptom_Temperature(void)
	{
	}

	/*******************************************************************************/
	// �������ƣ� IsKindOf
	// ���ܣ�   �ж����������
	// ������   const CString &strClassName
	// ����ֵ: 
	bool CSymptom_Temperature::isKindOf( const std::string &strClassName )
	{
		if( strClassName == "CSymptom_Temperature" )
		{
			return true;
		}
		return false;
	}

	//���ݱ�ʾ�����ж���������
	bool CSymptom_Temperature::isSymptomCaption(const std::string &strCaption)
	{
		return CSAction_Temperature::isAction_Temperature( strCaption );
	}
	/*******************************************************************************/
	// �������ƣ� InitialSymptomValue
	// ���ܣ�   ��ʼ������ֵ
	// ������   IModifiedSymptomsOp *pInterfacePtr
	// ����ֵ: 
	void CSymptom_Temperature::InitialSymptomValue(IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType)
	{
		m_pModifiedSymptomsOp  = pInterfacePtr;

		m_fP_TempValue   = 35.2f;

		pInterfacePtr->AddNewModifiedSymptom( this );
	}

	/*******************************************************************************/
	// �������ƣ� InitialSymptomValue
	// ���ܣ�   ��ʼ������ֵ
	// ������   
	//          CXActionVirtual *pVirAction:         ��Ӧ����ֵ
	//          short sTransTime:                    ת��ʱ�䣨��λ���룩
	// ����ֵ: 
	void CSymptom_Temperature::InitialSymptomValue(CXActionVirtual *pVirAction, short sTransTime/*=0*/)
	{
	#ifdef _DEBUG
		if( pVirAction == NULL || !pVirAction->isActionNameOf( CSAction_Temperature::getAction_Temperature_Caption() ) )
		{
			BOOST_ASSERT( 0 );
		}
	#endif 		
		CXAction_Temperature *pAction_Temp = (CXAction_Temperature *)pVirAction;

		if( sTransTime == 0 )
		{
			m_fP_TempValue  = pAction_Temp->GetValue_P_Temp();
		}
		m_pModifiedSymptomsOp->AddNewModifiedSymptom( this );

	}

	void CSymptom_Temperature::SetShowTemperatureValueInterface(CShowTempUpdateInterface *ptemp)
	{
		m_pShowPTempValueInterface = ptemp;
		if(m_pShowPTempValueInterface)
		{
			m_pShowPTempValueInterface->LinkUpdateShow();
			m_pShowPTempValueInterface->OnShowTempValue(m_fP_TempValue);
		}
	}

	// �������ƣ� OnUpdateInterfaceShow
	// ���ܣ�   ���½�����ʾ
	// ������   
	// ����ֵ: 
	void CSymptom_Temperature::OnUpdateInterfaceShow()
	{
		if( m_pShowPTempValueInterface ) 
		{
			m_pShowPTempValueInterface->OnShowTempValue(m_fP_TempValue);
		}
	}

	/*******************************************************************************/
	// �������ƣ� OnLinkWatchBarUpdateInterfaceShow
	// ���ܣ�   ����ģ������ʾ����
	// ������   
	// ����ֵ:
	void CSymptom_Temperature::OnLinkWatchBarUpdateInterfaceShow(CWatchBarsShowInterfacesAggregate *pShowAggregate)
	{
		CShowTempUpdateInterface *pShowPTempInterface = pShowAggregate->Get_ShowPTempValueInterfacePtr();
		//���ù�������ʾ�ӿ�
		SetShowTemperatureValueInterface( pShowPTempInterface);
	}

	/*******************************************************************************/
	// �������ƣ� OnUnLinkWatchBarUpdateInterfaceShow
	// ���ܣ�   �Ͽ���ʾ����
	// ������   
	// ����ֵ:
	void CSymptom_Temperature::OnUnLinkWatchBarUpdateInterfaceShow(CWatchBarsShowInterfacesAggregate *pShowAggregate)
	{
		CShowTempUpdateInterface *pShowPTempInterface = pShowAggregate->Get_ShowPTempValueInterfacePtr();
		if( pShowPTempInterface != NULL )
		{
			m_pShowPTempValueInterface = (CShowTempUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowPTempValueInterface, pShowPTempInterface);
			//�Ͽ���ʾ����
			pShowPTempInterface->UnLinkUpdateShow();
		}
	}
}}
