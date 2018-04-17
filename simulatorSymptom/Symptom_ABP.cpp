#include <boost/bind.hpp>
#include <boost/assert.hpp>
#include ".\symptom_abp.h"
#include ".\IModifiedSymptomsOp.h"
#include ".\XAction_ABP.h"

#include "..\Common\DecodeUtil.h"

#include "..\elementParse\SAction_ABP.h"

#include "..\SimulatorBase\WatchBarsShowInterfacesAggregate.h"


using namespace jysoft::simulator::base;
namespace jysoft { namespace simulator 
{
	CSymptom_ABP::CSymptom_ABP(void) : m_cNIBPTimer(60*1000, boost::bind(&CSymptom_ABP::Set_NIBPCurrentValue, this))
	{
		m_pABPBuildInterface = NULL;
		m_pShowNIBPInterface = NULL;

		m_bModifyNIBPValue  = false;
		//����Ĭ��Ѫѹֵ
		m_nShrinkValue_ABP  = 120;
		m_nStretchValue_ABP = 80;
	}

	CSymptom_ABP::~CSymptom_ABP(void)
	{
		m_cNIBPTimer.killTimer();
	}

	/*******************************************************************************/
	// �������ƣ� IsKindOf
	// ���ܣ�   �ж����������
	// ������   const CString &strClassName
	// ����ֵ: 
	bool CSymptom_ABP::isKindOf( const std::string &strClassName )
	{
		if( strClassName == "CSymptom_ABP" )
		{
			return true;
		}
		return false;
	}

	//���ݱ�ʾ�����ж���������
	bool CSymptom_ABP::isSymptomCaption(const std::string &strCaption)
	{
		return CSAction_ABP::isAction_BP( strCaption );
	}

	/*******************************************************************************/
	// �������ƣ� InitialSymptomValue
	// ���ܣ�   ��ʼ������ֵ
	// ������   IModifiedSymptomsOp *pInterfacePtr
	// ����ֵ: 
	void CSymptom_ABP::InitialSymptomValue(IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType)
	{
		m_pModifiedSymptomsOp  = pInterfacePtr;

		m_nShrinkValue_NIBP  = 120;
		m_nStretchValue_NIBP = 80;

		m_bModifyNIBPValue  = true;

		pInterfacePtr->AddNewModifiedSymptom( this );
	}

	/*******************************************************************************/
	// �������ƣ� InitialSymptomValue
	// ���ܣ�   ��ʼ������ֵ
	// ������   
	//          CXActionVirtual *pVirAction:         ��Ӧ����ֵ
	//          short sTransTime:                    ת��ʱ�䣨��λ���룩
	// ����ֵ: 
	void CSymptom_ABP::InitialSymptomValue(CXActionVirtual *pVirAction, short sTransTime/*=0*/)
	{
	#ifdef _DEBUG
		if( pVirAction == NULL || !pVirAction->isActionNameOf( CSAction_ABP::getAction_BP_Caption()) )
		{
			BOOST_ASSERT( 0 );
		}
	#endif 
		CXAction_ABP  *pAction_ABP = (CXAction_ABP *)pVirAction;
		if( pAction_ABP->m_dwField == 0x01 )
		{
			//����Ѫѹ
			if( m_nShrinkValue_ABP != pAction_ABP->GetValue_AbsoluteShrink( m_nShrinkValue_ABP ) || m_nStretchValue_ABP != pAction_ABP->GetValue_AbsoluteStretch( m_nStretchValue_ABP ) )
			{
				if( sTransTime == 0 )
				{
					m_nShrinkValue_ABP  = pAction_ABP->GetValue_AbsoluteShrink( m_nShrinkValue_ABP );
					m_nStretchValue_ABP = pAction_ABP->GetValue_AbsoluteStretch( m_nStretchValue_ABP );
					//�����޴�Ѫѹ
					m_nShrinkValue_NIBP = m_nShrinkValue_ABP;
					m_nStretchValue_NIBP = m_nStretchValue_ABP;

					m_bModifyNIBPValue  = true;
					m_pModifiedSymptomsOp->AddNewModifiedSymptom( this );
				}
			}
		}
	}

	//��ʼ��Ѫѹģ�����߹�����
	void CSymptom_ABP::InitialABPBuild(SimulatePatientType ePatientType)
	{
		if( m_pABPBuildInterface != NULL )
		{
			m_pABPBuildInterface->OnModifyABPValue( m_nShrinkValue_ABP, m_nStretchValue_ABP );
		}
		//=======�����߳�==============
		m_cNIBPTimer.startTimer();
	}

	//�޸�Ѫѹģ�����߹�����
	void CSymptom_ABP::ModifyABPBuild()
	{
		if( m_pABPBuildInterface != NULL )
		{
			m_pABPBuildInterface->OnModifyABPValue( m_nShrinkValue_ABP, m_nStretchValue_ABP );
		}
	}

	//����ABP����ֵ����ȡNIBP(1����)
	void CSymptom_ABP::Set_NIBPCurrentValue()
	{
		if( m_nShrinkValue_NIBP != m_nShrinkValue_ABP || m_nStretchValue_NIBP != m_nStretchValue_ABP )
		{
			m_nShrinkValue_NIBP  =  m_nShrinkValue_ABP;
			m_nStretchValue_NIBP =  m_nStretchValue_ABP;

			m_bModifyNIBPValue  = true;

			//�����޸ı�־
			m_pModifiedSymptomsOp->AddNewModifiedSymptom( this );
		}
	}

	// �������ƣ� OnUpdateInterfaceShow
	// ���ܣ�   ���½�����ʾ
	// ������   
	// ����ֵ: 
	void CSymptom_ABP::OnUpdateInterfaceShow()
	{
		if( m_pShowNIBPInterface != NULL )
		{
			m_pShowNIBPInterface->OnShowNIBPValue(m_nShrinkValue_ABP, m_nStretchValue_ABP); 
		}
		//--------------------------------------------------------------------------------------
		m_bModifyNIBPValue  = false;
	}

	void CSymptom_ABP::SetShowNIBPInterface(CShowNIBPUpdateInterface *pShowInterface)
	{
		if( m_pShowNIBPInterface == NULL )
		{
			m_pShowNIBPInterface  = pShowInterface;
		}
		else if( pShowInterface != NULL )
		{
			m_pShowNIBPInterface->SetNextInterfacePtr( pShowInterface );
		}
		if( m_pShowNIBPInterface != NULL )
		{
			m_pShowNIBPInterface->LinkUpdateShow();
			m_pShowNIBPInterface->OnShowNIBPValue(m_nShrinkValue_NIBP, m_nStretchValue_NIBP);
		}
	}

	/*******************************************************************************/
	// �������ƣ� OnLinkWatchBarUpdateInterfaceShow
	// ���ܣ�   ����ģ������ʾ����
	// ������   
	// ����ֵ:
	void CSymptom_ABP::OnLinkWatchBarUpdateInterfaceShow(CWatchBarsShowInterfacesAggregate *pShowAggregate)
	{
		CShowNIBPUpdateInterface *pShowInterface = pShowAggregate->Get_ShowNIBPValueUpdateInterfacePtr();
		//����NIBP��ʾ�ӿ�
		SetShowNIBPInterface( pShowInterface );
	}

	/*******************************************************************************/
	// �������ƣ� OnUnLinkWatchBarUpdateInterfaceShow
	// ���ܣ�   �Ͽ�ģ������ʾ����
	// ������   
	// ����ֵ:
	void CSymptom_ABP::OnUnLinkWatchBarUpdateInterfaceShow(CWatchBarsShowInterfacesAggregate *pShowAggregate)
	{
		CShowNIBPUpdateInterface *pShowInterface = pShowAggregate->Get_ShowNIBPValueUpdateInterfacePtr();
		if( pShowInterface != NULL )
		{
			m_pShowNIBPInterface = (CShowNIBPUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowNIBPInterface, pShowInterface);
			//�Ͽ���ʾ����
			pShowInterface->UnLinkUpdateShow();
		}
	}

	/*******************************************************************************/
	// �������ƣ� OnLinkSimulatorBarUpdateInterfaceShow
	// ���ܣ�   ����ģ���������ʾ����
	// ������   
	// ����ֵ:
	void CSymptom_ABP::OnLinkSimulatorBarUpdateInterfaceShow(CSymptomsShowInterfacesAggregate *pShowAggregate )
	{
		CShowNIBPUpdateInterface *pShowInterface = pShowAggregate->Get_ShowNIBPUpdateInterfacePtr();

		SetShowNIBPInterface( pShowInterface );
	}	

	/*******************************************************************************/
	// �������ƣ� OnUnLinkSimulatorBarUpdateInterfaceShow
	// ���ܣ�   �Ͽ�ģ���������ʾ����
	// ������   
	// ����ֵ:
	void CSymptom_ABP::OnUnLinkSimulatorBarUpdateInterfaceShow(CSymptomsShowInterfacesAggregate *pShowAggregate )
	{
		CShowNIBPUpdateInterface *pShowInterface = pShowAggregate->Get_ShowNIBPUpdateInterfacePtr();
		if( pShowInterface != NULL )
		{
			m_pShowNIBPInterface = (CShowNIBPUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowNIBPInterface, pShowInterface);
			//�Ͽ���ʾ����
			pShowInterface->UnLinkUpdateShow();
		}
	}

	//���ô���NIBPָ��
	void  CSymptom_ABP::SetEnableTranslateNIBPOrder()
	{
		m_bModifyNIBPValue = true;
		m_pModifiedSymptomsOp->AddNewModifiedSymptom( this );
	}
}}
