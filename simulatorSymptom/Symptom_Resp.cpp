#include <algorithm>
#include <boost/foreach.hpp>
#include ".\symptom_resp.h"
#include ".\IModifiedSymptomsOp.h"
#include ".\XAction_Resp.h"

#include "..\Common\DecodeUtil.h"
#include "..\Common\PatientRuleInterfaceGlobal.h"

#include "..\elementParse\SAction_Resp.h"


using namespace jysoft::simulator::base;
namespace jysoft { namespace simulator 
{
	CSymptom_Resp::CSymptom_Resp(void)
	{
		m_pRespBuildInterface = NULL;
		m_pShowRespInterface  = NULL;
	}

	CSymptom_Resp::~CSymptom_Resp(void)
	{
		
	}

	/*******************************************************************************/
	// �������ƣ� IsKindOf
	// ���ܣ�   �ж����������
	// ������   const CString &strClassName
	// ����ֵ: 
	bool CSymptom_Resp::isKindOf( const std::string &strClassName )
	{
		if( strClassName == "CSymptom_Resp" )
			return true;
		return false;
	}

	//���ݱ�ʾ�����ж���������
	bool CSymptom_Resp::isSymptomCaption(const std::string &strCaption)
	{
		return CSAction_Resp::isAction_Resp( strCaption );
	}

	/*******************************************************************************/
	// �������ƣ� InitialSymptomValue
	// ���ܣ�   ��ʼ������ֵ
	// ������   IModifiedSymptomsOp *pInterfacePtr
	// ����ֵ: 
	void CSymptom_Resp::InitialSymptomValue(IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType)
	{
		m_pModifiedSymptomsOp  = pInterfacePtr;
	
		//����Ĭ�Ϻ���
		m_eRespMode  = RM_Normal;
		m_nRespRate  = 14;

		pInterfacePtr->AddNewModifiedSymptom( this );
	}

	/*******************************************************************************/
	// �������ƣ� InitialSymptomValue
	// ���ܣ�   ��ʼ������ֵ
	// ������   
	//          CXActionVirtual *pVirAction:         ��Ӧ����ֵ
	//          short sTransTime:                    ת��ʱ�䣨��λ���룩
	// ����ֵ: 
	void CSymptom_Resp::InitialSymptomValue(CXActionVirtual *pVirAction, short sTransTime/*=0*/)
	{
	#ifdef _DEBUG
		if( pVirAction == NULL || !pVirAction->isActionNameOf( CSAction_Resp::getAction_Resp_Caption() ) )
		{
			BOOST_ASSERT( 0 );
		}
	#endif 	
		//----------------------------------------------------------------------------------------------------
		int   nSrcRespRate  = m_nRespRate;
		CXAction_Resp *pAction_Breath = (CXAction_Resp *)pVirAction;
		if( pAction_Breath->GetRespMode() != m_eRespMode || pAction_Breath->GetValue_AbsoluteRR( nSrcRespRate ) != m_nRespRate )
		{
			m_eRespMode = pAction_Breath->GetRespMode();
			if( sTransTime == 0 )
			{
				m_nRespRate = pAction_Breath->GetValue_AbsoluteRR( nSrcRespRate );
			}

			m_pModifiedSymptomsOp->AddNewModifiedSymptom( this );
		}
	}

	//��ʼ������ģ�����߹�����
	void CSymptom_Resp::InitialRespBuild(SimulatePatientType ePatientType)
	{
		if( m_pRespBuildInterface != NULL )
		{
			m_pRespBuildInterface->InitializeBuild(m_eRespMode, m_nRespRate);
		}
	}

	//�޸ĺ���ģ�����߹�����
	void CSymptom_Resp::ModifyRespBuild()
	{
		if( m_pRespBuildInterface != NULL )
		{
			m_pRespBuildInterface->OnModifyRespBuildType(m_eRespMode, m_nRespRate);
		}
	}

	/*******************************************************************************/
	// �������ƣ� OnLinkSimulatorBarUpdateInterfaceShow
	// ���ܣ�   �Ͽ�ģ���������ʾ����
	// ������   
	// ����ֵ:
	void CSymptom_Resp::OnLinkSimulatorBarUpdateInterfaceShow(CSymptomsShowInterfacesAggregate *pShowAggregate )
	{
		//����ģʽ��ʾ�ӿ�
		CShowRespRateUpdateInterface *pShowRespInterface = pShowAggregate->Get_ShowRespUpdateInterfacePtr();
		if( m_pShowRespInterface == NULL )
		{
			m_pShowRespInterface  = pShowRespInterface;
		}
		else if( pShowRespInterface != NULL )
		{
			m_pShowRespInterface->SetNextInterfacePtr( pShowRespInterface );
		}
		if( pShowRespInterface != NULL )
		{
			pShowRespInterface->LinkUpdateShow();
			pShowRespInterface->OnShowRespRate( m_eRespMode, m_nRespRate );
		}
	}

	/*******************************************************************************/
	// �������ƣ� OnUnLinkSimulatorBarUpdateInterfaceShow
	// ���ܣ�   �Ͽ�ģ���������ʾ����
	// ������   
	// ����ֵ:
	void CSymptom_Resp::OnUnLinkSimulatorBarUpdateInterfaceShow(CSymptomsShowInterfacesAggregate *pShowAggregate )
	{
		CShowRespRateUpdateInterface *pShowInterface = pShowAggregate->Get_ShowRespUpdateInterfacePtr();
		if( pShowInterface != NULL )
		{
			m_pShowRespInterface = (CShowRespRateUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowRespInterface, pShowInterface);
			//�Ͽ���ʾ����
			pShowInterface->UnLinkUpdateShow();
		}
	}

	// �������ƣ� OnUpdateInterfaceShow
	// ���ܣ�   ���½�����ʾ
	// ������   
	// ����ֵ: 
	void CSymptom_Resp::OnUpdateInterfaceShow()
	{
		if( m_pShowRespInterface != NULL )
		{
			m_pShowRespInterface->OnShowRespRate(m_eRespMode, m_nRespRate);
		}
	}
}}
