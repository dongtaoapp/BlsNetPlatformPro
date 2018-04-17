#include <algorithm>
#include <boost/lexical_cast.hpp>
#include ".\symptom_ecg.h"
#include ".\IModifiedSymptomsOp.h"
#include ".\XAction_ECG.h"

#include "..\Common\DecodeUtil.h"
#include "..\Common\PatientTypeFactory.h"

#include "..\ElementParse\SAction_ECG.h"


using namespace jysoft::simulator::base;
namespace jysoft { namespace simulator 
{
	CSymptom_Ecg::CSymptom_Ecg(void)
	{
		m_ePatientType         = SPT_Adult;
		m_pECGBuildInterface   = NULL;
		m_pEcgShowInterface    = NULL;
		m_nPaceCaptureHR       = -1;       //δ���
	}

	CSymptom_Ecg::~CSymptom_Ecg(void)
	{
	}

	/*******************************************************************************/
	// �������ƣ� IsKindOf
	// ���ܣ�   �ж����������
	// ������   const CString &strClassName
	// ����ֵ: 
	bool CSymptom_Ecg::isKindOf( const std::string &strClassName )
	{
		if( strClassName == "CSymptom_Ecg" )
			return true;
		return false;
	}

	//���ݱ�ʾ�����ж���������
	bool CSymptom_Ecg::isSymptomCaption(const std::string &strCaption)
	{
		return CSAction_ECG::isECG_Action( strCaption );
	}

	/*******************************************************************************/
	// �������ƣ� InitialSymptomValue
	// ���ܣ�   ��ʼ������ֵ
	// ������   
	//         IModifiedSymptomsOp *pInterfacePtr
	// ����ֵ: 
	void CSymptom_Ecg::InitialSymptomValue(IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType)
	{
		m_pModifiedSymptomsOp  = pInterfacePtr;
		m_ePatientType         = ePatientType;
	
		m_nPaceCaptureHR       = -1;       //δ���
		//����Ĭ�ϵ�����ֵ
		m_dwFields = PM_QRS | PM_BASICRHYTHM | PM_HR;
		m_eQRS          = QRS_A;
		m_eBasicRm      = BR_Sinus;
		m_eExtrasys     = ES_None;
		m_iExtrasysRate = 0;
		m_iHR           = 80;
		m_eArtifact     = AF_None;
		m_bEMD          = FALSE;
		m_sConduct      = 0;
		m_sExtendParam  = 0;
	
		pInterfacePtr->AddNewModifiedSymptom( this );
	}


	/*******************************************************************************/
	// �������ƣ� InitialSymptomValue
	// ���ܣ�   ��ʼ���ĵ�ͼ
	// ������   
	//          CXActionVirtual *pEcgAction:
	//          short sTransTime:                    ת��ʱ�䣨��λ���룩
	// ����ֵ: 
	void CSymptom_Ecg::InitialSymptomValue(CXActionVirtual *pVirAction, short sTransTime/*=0*/)
	{
	#ifdef _DEBUG
		if( pVirAction == NULL || !pVirAction->isActionNameOf( CSAction_ECG::getAction_ECG_Caption() ) )
		{
			BOOST_ASSERT( 0 );
		}
	#endif 
		//����Ĭ�ϵ�����ֵ
		if( !(m_dwFields & PM_HR) )
		{
			m_dwFields = PM_QRS | PM_BASICRHYTHM | PM_HR;
			m_eQRS          = QRS_A;
			m_eBasicRm      = BR_Sinus;
			m_eExtrasys     = ES_None;
			m_iExtrasysRate = 0;
			m_iHR           = 85;
			m_eArtifact     = AF_None;
			m_bEMD          = FALSE;
			m_sConduct      = 0;
			m_sExtendParam  = 0;
		}
		//----------------------------------------------------------------------------------------
		int            nSrcHR      = m_iHR;
		CXAction_ECG  *pAction_Ecg = (CXAction_ECG *)pVirAction;
        unsigned long   dwField = pAction_Ecg->Get_FieldsFlag();
		if( (dwField & PM_HR) && (dwField & PM_BASICRHYTHM) )
		{
			m_eBasicRm  = pAction_Ecg->GetValue_eBasicRhythm();
			if( sTransTime == 0 )
			{
				m_iHR       = pAction_Ecg->GetValue_AbsoluteHR( nSrcHR );
			}
			m_eExtrasys = pAction_Ecg->GetValue_eExtrasys();
			m_iExtrasysRate = pAction_Ecg->GetValue_ExtrasystRate();
			//�Ƿ��޸���Ϊ������
            bool    bModifArtifact = false;
			if( m_dwFields & PM_ARTIFACT || dwField & PM_ARTIFACT )
			{
				if( m_eArtifact != AF_None || pAction_Ecg->GetValue_eArtifact() != AF_None )
				{
                    bModifArtifact = true;
				}
			}
			m_eArtifact = pAction_Ecg->GetValue_eArtifact();
			//end hjg 2010.9.10
			if( (m_dwFields & PM_EMD) && !( dwField & PM_EMD) )
			{
				m_dwFields  = pAction_Ecg->Get_FieldsFlag();
				m_dwFields |= PM_EMD;
			}
			else
			{
				m_dwFields  = pAction_Ecg->Get_FieldsFlag();
				m_bEMD      = pAction_Ecg->GetValue_EMD();
			}
			m_sConduct     = pAction_Ecg->GetValue_Conduct();
			m_sExtendParam = pAction_Ecg->GetValue_ExtendParam();
            if( bModifArtifact )
			{
				m_dwFields |= PM_ARTIFACT;
			}
		}
		else
		{
			if( dwField & PM_HR )
			{
				m_iHR   =  pAction_Ecg->GetValue_HR();
				m_dwFields   |= PM_HR;
			}
			if( dwField & PM_EXTRASYS )
			{
				m_eExtrasys   = pAction_Ecg->GetValue_eExtrasys();
				m_dwFields   |= PM_EXTRASYS;
			}
			if( dwField & PM_EXTRASYSRATE )
			{
				m_iExtrasysRate = pAction_Ecg->GetValue_ExtrasystRate();
				m_dwFields   |= PM_EXTRASYSRATE;
			}
			if( dwField & PM_ARTIFACT )
			{
				m_eArtifact = pAction_Ecg->GetValue_eArtifact();
				m_dwFields   |= PM_ARTIFACT;
			}
			if( dwField & PM_EMD )
			{
				m_bEMD        = pAction_Ecg->GetValue_EMD();
				m_dwFields   |= PM_EMD;
			}
			if( dwField & PM_CONDUCT )
			{
				m_sConduct    = pAction_Ecg->GetValue_Conduct();
				m_dwFields   |= PM_CONDUCT;
			}
			if( dwField & PM_EXTEND )
			{
				m_sExtendParam  = pAction_Ecg->GetValue_ExtendParam();
				m_dwFields     |= PM_EXTEND;
			}
		}
		m_pModifiedSymptomsOp->AddNewModifiedSymptom( this );
	}

	//��ʼ���ĵ�ͼģ�����߹�����
	void CSymptom_Ecg::InitialEcgBuild(SimulatePatientType ePatientType)
	{
		CECGParams   cECGParams;
		cECGParams.m_dwField    = m_dwFields;
		cECGParams.m_eArtifact  = m_eArtifact;
		cECGParams.m_eBasicRm   = m_eBasicRm;
		cECGParams.m_eExtrasys  = m_eExtrasys;
		cECGParams.m_iExtrasysRate  = m_iExtrasysRate;
		cECGParams.m_iHR        = m_iHR;
		cECGParams.m_bEMD       = m_bEMD;
		cECGParams.m_sConduct   = m_sConduct;
		cECGParams.m_sExtendParam = m_sExtendParam;
		if( m_pECGBuildInterface != NULL )
		{
			m_pECGBuildInterface->OnInitializeBuild( cECGParams );
		}
	}

	//�޸��ĵ�ͼģ�����߹�����
	void CSymptom_Ecg::ModifyEcgBuild(eEventSign eEventValue)
	{
		CECGParams   cECGParams;
		cECGParams.m_dwField    = m_dwFields;
		cECGParams.m_eArtifact  = m_eArtifact;
		cECGParams.m_eBasicRm   = m_eBasicRm;
		cECGParams.m_eExtrasys  = m_eExtrasys;
		cECGParams.m_iExtrasysRate  = m_iExtrasysRate;
		cECGParams.m_iHR        = m_iHR;
		cECGParams.m_bEMD       = m_bEMD;
		cECGParams.m_sConduct   = m_sConduct;
		cECGParams.m_sExtendParam = m_sExtendParam;
		if( m_pECGBuildInterface != NULL && m_nPaceCaptureHR == -1)
		{
			if( eEventValue == ES_Defib )
			{
				m_pECGBuildInterface->OnModifyECGInDefibrEventHandle( &cECGParams );
			}
			else
			{
				m_pECGBuildInterface->OnModifyECGHandle( cECGParams );
			}
		}
	}

	//ֱ���޸��ĵ�ͼģ�����߹�����
	void CSymptom_Ecg::DirectEcgBuild()
	{
		CECGParams   cECGParams;
		cECGParams.m_dwField    = m_dwFields;
		cECGParams.m_eArtifact  = m_eArtifact;
		cECGParams.m_eBasicRm   = m_eBasicRm;
		cECGParams.m_eExtrasys  = m_eExtrasys;
		cECGParams.m_iExtrasysRate  = m_iExtrasysRate;
		cECGParams.m_iHR        = m_iHR;
		cECGParams.m_bEMD       = m_bEMD;
		cECGParams.m_sConduct   = m_sConduct;
		cECGParams.m_sExtendParam = m_sExtendParam;
		if( m_pECGBuildInterface != NULL && m_nPaceCaptureHR == -1)
		{
			m_pECGBuildInterface->OnDirectModifyECGHandle( cECGParams );
		}
	}

	/*******************************************************************************/
	// �������ƣ� isTransmitAEDState
	// ���ܣ�   �Ƿ�AED״̬�ı�
	// ������   
	//          /*in,out*/unsigned char *sAEDState:        AED״̬
	// ����ֵ: 
	bool CSymptom_Ecg::isTransmitAEDState(/*in,out*/unsigned char *sAEDState)
	{
		if( sAEDState != NULL )
		{
			switch( m_eBasicRm )
			{
			case BR_Sinus:
				{
					*sAEDState &= 0x1F;
					break;
				}
			case BR_VFibr:
				{
					*sAEDState &= 0x1F;
					*sAEDState |= 0x20;
					break;
				}
			case BR_Asystole:
				{
					*sAEDState &= 0x1F;
					*sAEDState |= 0x40;
					break;
				}
			}
		}
		return true;
	}

	// �������ƣ� OnUpdateInterfaceShow
	// ���ܣ�   ���½�����ʾ
	// ������   
	// ����ֵ: 
	void CSymptom_Ecg::OnUpdateInterfaceShow()
	{
		if( m_pEcgShowInterface != NULL )
		{
			std::string  strRhythm = IRhythmRule::GetstrBasicRhythm( m_eBasicRm );
			std::string  strExtrasysName;
			if( m_dwFields & PM_EXTRASYS )
				strExtrasysName = IRhythmRule::GetstrExtrasys( m_eExtrasys );
			m_pEcgShowInterface->OnShowECGName( strRhythm, strExtrasysName, m_iHR, m_bEMD);
		}
	}

	/*******************************************************************************/
	// �������ƣ� OnLinkSimulatorBarUpdateInterfaceShow
	// ���ܣ�   �Ͽ�ģ���������ʾ����
	// ������   
	// ����ֵ:
	void CSymptom_Ecg::OnLinkSimulatorBarUpdateInterfaceShow(CSymptomsShowInterfacesAggregate *pShowAggregate )
	{
		CShowECGUpdateInterface *pShowInterface = pShowAggregate->Get_ShowECGUpdateInterfacePtr();
		if( m_pEcgShowInterface == NULL )
		{
			m_pEcgShowInterface = pShowInterface;
		}
		else if( pShowInterface != NULL )
		{
			m_pEcgShowInterface->SetNextInterfacePtr( pShowInterface );
		}
		if( pShowInterface != NULL )
		{
			pShowInterface->LinkUpdateShow();
		}
		//EMD������ʾ
		CShowECGUpdateInterface *pShowEMDInterface = pShowAggregate->Get_ShowEMDUpdateInterfacePtr();
		if( m_pEcgShowInterface == NULL )
		{
			m_pEcgShowInterface  = pShowEMDInterface;
		}
		else if( pShowEMDInterface != NULL )
		{
			m_pEcgShowInterface->SetNextInterfacePtr( pShowEMDInterface );
		}
		if( pShowEMDInterface != NULL )
		{
			pShowEMDInterface->LinkUpdateShow();
		}
		//----------------------------------------------------------------------------------
		if( pShowInterface != NULL || pShowEMDInterface != NULL )
		{
			//������ʾ������
			std::string  strRhythm = IRhythmRule::GetstrBasicRhythm( m_eBasicRm );
			std::string  strExtrasysName;
			if( m_dwFields & PM_EXTRASYS )
				strExtrasysName = IRhythmRule::GetstrExtrasys( m_eExtrasys );
			m_pEcgShowInterface->OnShowECGName( strRhythm, strExtrasysName, m_iHR, m_bEMD);
		}
	}

	/*******************************************************************************/
	// �������ƣ� OnUnLinkSimulatorBarUpdateInterfaceShow
	// ���ܣ�   �Ͽ�ģ���������ʾ����
	// ������   
	// ����ֵ:
	void CSymptom_Ecg::OnUnLinkSimulatorBarUpdateInterfaceShow(CSymptomsShowInterfacesAggregate *pShowAggregate )
	{
		CShowECGUpdateInterface *pShowInterface = pShowAggregate->Get_ShowECGUpdateInterfacePtr();
		if( pShowInterface != NULL )
		{
			m_pEcgShowInterface = (CShowECGUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pEcgShowInterface, pShowInterface);
			//�Ͽ���ʾ����
			pShowInterface->UnLinkUpdateShow();
		}
		//EMD������ʾ
		CShowECGUpdateInterface *pShowEMDInterface = pShowAggregate->Get_ShowEMDUpdateInterfacePtr();
		if( pShowEMDInterface != NULL )
		{
			m_pEcgShowInterface = (CShowECGUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pEcgShowInterface, pShowEMDInterface);
			//�Ͽ���ʾ����
			pShowEMDInterface->UnLinkUpdateShow();
		}
	}

	//��ʼ�𲫶��
	void CSymptom_Ecg::StartPaceCapture()
	{
		m_nPaceCaptureHR  = m_iHR;
	}

	//�޸��𲫶��������
	void CSymptom_Ecg::ModifyPaceCaptureHR(int nCaptureHR)
	{
		if( m_nPaceCaptureHR != -1 && m_nPaceCaptureHR != nCaptureHR )
		{
			m_nPaceCaptureHR  = nCaptureHR;
			m_pModifiedSymptomsOp->AddNewModifiedSymptom( this );
		}
	}

	//�����𲫶��
	void CSymptom_Ecg::StopPaceCapture()
	{
		m_nPaceCaptureHR  = -1;
		m_pModifiedSymptomsOp->AddNewModifiedSymptom( this );
	}

	std::string CSymptom_Ecg::getBasicRmShowText()
	{
		std::string strRhythm;
		strRhythm   = IRhythmRule::GetstrBasicRhythm( m_eBasicRm );
		IRhythmRule *pRhyThmRuleInterface = CPatientTypeFactory::GetSimulateRhythmRulePtr();
		//��������
		std::string   strRhythmShowTxt  = pRhyThmRuleInterface->GetRhythmDisplayTxt( strRhythm );
		return strRhythmShowTxt;

	}
}}
