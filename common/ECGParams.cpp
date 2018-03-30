#include ".\ecgparams.h"

namespace jysoft { namespace simulator {

	CECGParams::CECGParams(void)
	{
		m_dwField = 0;
		m_eBasicRm = BR_Sinus;
		m_eArtifact = AF_None;
		m_iExtrasysRate = 0;
		m_eExtrasys = ES_None;
		m_iHR       = 80;
        m_bEMD      = false;
		m_sConduct  = 0;
		m_sExtendParam = 0;
        m_bHRPercent  = false;
	}

	CECGParams::~CECGParams(void)
	{
	}

	/**
	*	��ֵ����
	*/
	const CECGParams & CECGParams::operator = (const CECGParams & params)
	{
		m_dwField = params.m_dwField;        //����ָ����Щ��������ֵ
		m_eArtifact = params.m_eArtifact ;      //PM_ARTIFACT = 0x00000001
		m_iExtrasysRate = params.m_iExtrasysRate;  //�粫�ı��� PM_EXTRASYSRATE = 0x00000002
		m_eBasicRm = params.m_eBasicRm;       //��������   PM_BASICRHYTHM = 0x00000008
		m_eExtrasys = params.m_eExtrasys;      //�����������粫�� PM_EXTRASYS = 0x00000010
		m_iHR = params.m_iHR;            //��������   PM_HR = 0x00000020
		m_uSize = params.m_uSize;          //�Ŵ�ߴ�   PM_SIZE = 0x00000040
		m_eSpeed = params.m_eSpeed;         //�����ٶ�   PM_SPEED = 0x00000080
		m_bEMD     = params.m_bEMD;
		m_sConduct = params.m_sConduct;
		m_sExtendParam = params.m_sExtendParam;
		m_bHRPercent  = params.m_bHRPercent;
		return *this;
	}

	// ��Ϊ�������ĵ�ͼ����
	void CECGParams::SetDefault(SimulatePatientType ePatientType)
	{
		m_dwField = PM_QRS | PM_BASICRHYTHM | PM_HR | PM_SIZE | PM_SPEED;
		m_eBasicRm = BR_Sinus;
		switch( ePatientType)
		{
		case SPT_Infant:
			{
				m_iHR       = 130; //ÿ����130��
				break;
			}
		case SPT_Enfant:
		case SPT_Adult:
		case SPT_PregnantWoman:
			{
				m_iHR       = 80; //ÿ����80��
				break;
			}
		}
		m_eExtrasys    = ES_None;
		m_sExtendParam = 0;
		m_uSize     = 1;  //�޷Ŵ�
		m_eSpeed    = HS_Normal;  //����
	}

	//����ĵ�ͼ����
	void CECGParams::ClearEcgParams()
	{
		m_dwField       = 0;
		m_eBasicRm      = BR_None;
		m_eArtifact     = AF_None;
		m_iExtrasysRate = 0;
		m_eExtrasys     = ES_None;
		m_iHR           = 80;
        m_bEMD          = false;
		m_sConduct      = 0;
		m_eSpeed        = HS_Normal;
		m_uSize         = 1;  //�޷Ŵ�
        m_bHRPercent    = false;
		m_sExtendParam  = 0;
	}

}}
