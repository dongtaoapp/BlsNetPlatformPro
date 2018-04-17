#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include ".\xaction_ecg.h"

#include "..\ElementParse\SAction_ECG.h"

#include "..\Common\PatientTypeFactory.h"


namespace jysoft { namespace simulator 
{
	CXAction_ECG::CXAction_ECG(void)
	{
		m_nArtifacts = -1;
		m_strRhythm  = "Sinus";
		m_strHR      = "80";
		m_sEMD       = 0;
		m_sConduct   = 0;
		m_sExtendParam = 0;
		m_dwFields   = PM_HR | PM_QRS | PM_BASICRHYTHM;
		m_bRelatePercent = false;
	}

	CXAction_ECG::CXAction_ECG(const std::string &strRhythm, const std::string &strHR)
	{
		m_dwFields   = PM_HR | PM_QRS | PM_BASICRHYTHM;
		m_strRhythm  = strRhythm;
		m_strHR      = strHR;
		m_bRelatePercent = false;
	}

	CXAction_ECG::~CXAction_ECG(void)
	{
	}

	bool CXAction_ECG::isKindOf(const std::string &strClassName)
	{
		if(strClassName == "CXAction_ECG")
		{
			return true;
		}
		return CXActionVirtual::isKindOf(strClassName);
	}

	/*******************************************************************************/
	// 函数名称： GetActionCaption
	// 功能：   返回体征标识名
	// 参数：   
	// 返回值: 
	std::string CXAction_ECG::getActionCaption() const
	{
		return CSAction_ECG::getAction_ECG_Caption();
	}

	bool CXAction_ECG::Parse_ActionFromXml(pugi::xml_node* pXMLShapeNode)
	{
		std::string   strRhythm, strHR, strExtrasyst, strExtrasystRate;
		int       nArtifacts;
		short     sEMD;
		short     sConduct = 0;
		short     sExtendParam = 0;
		std::string   strHRPercent;
		bool   bParseSec = CSAction_ECG::explainParamsFromXML(pXMLShapeNode, /*out*/strRhythm, /*out*/strHR, /*out*/strHRPercent, /*out*/strExtrasyst, /*out*/strExtrasystRate,/*out*/nArtifacts,/*out*/sEMD, /*out*/sConduct, /*out*/sExtendParam);
		if( bParseSec )
		{
			if( strHRPercent.empty() )
			{
                m_bRelatePercent  = false;
			}
			else
			{
                m_bRelatePercent  = true;
				strHR             = strHRPercent;
			}
			SetAction_Ecg(strRhythm, strHR, strExtrasyst, strExtrasystRate, nArtifacts, sEMD, sConduct, sExtendParam);
		}
		return bParseSec;
	}

	void CXAction_ECG::SetAction_Ecg(const std::string &strRhythm, const std::string &strHR, const std::string &strExtrasyst,const std::string &strExtrasystRate,int nArtifacts,short sEMD, short sConduct, short sExtendParam)
	{
		m_dwFields  = 0;

		if( sEMD != 0 )
		{
			m_dwFields = PM_EMD;
		}

		m_sEMD   = sEMD;

		if( sConduct != 0 )
		{
			m_sConduct  = sConduct;
			m_dwFields |= PM_CONDUCT;
		}

		if(nArtifacts != -1)
		{
			m_nArtifacts = nArtifacts;
			m_dwFields |= PM_ARTIFACT;
		}
		//早搏
		if(strExtrasyst != m_strExtrasyst || strExtrasystRate != m_strExtrasystRate )
		{
			m_strExtrasyst = strExtrasyst;
			m_dwFields |= PM_EXTRASYS;
			m_strExtrasystRate = strExtrasystRate;
			m_dwFields |= PM_EXTRASYSRATE;
		}
		if( !m_strExtrasyst.empty() || !m_strExtrasystRate.empty())
		{
			m_dwFields |= (PM_EXTRASYS|PM_EXTRASYSRATE);
		}
		//心率
		if( !strHR.empty() )
		{
			m_strHR = strHR;
			m_dwFields |= PM_HR;
		}
		//基本心律
		if( !strRhythm.empty() )
		{
			m_strRhythm = strRhythm;
			m_dwFields |= PM_BASICRHYTHM;
		}
		if( sExtendParam != 0 )
		{
			m_sExtendParam  = sExtendParam;
			m_dwFields |= PM_EXTEND;
		}
	}

	//返回心律名
	BasicRhythm CXAction_ECG::GetValue_eBasicRhythm()
	{
		return IRhythmRule::Get_eRhythm( m_strRhythm );
	}

	//返回早搏名
	Extrasys    CXAction_ECG::GetValue_eExtrasys()
	{
		if( m_dwFields & PM_EXTRASYS )
		{
			return IRhythmRule::Get_eExtrasys( m_strExtrasyst );
		}
		return ES_None;
	}

	//返回早搏测试/分钟
	int CXAction_ECG::GetValue_ExtrasystRate()
	{
		if( (m_dwFields & PM_EXTRASYS) && (m_dwFields & PM_EXTRASYSRATE) )
		{
			if( m_strExtrasystRate.empty() )
				return 0;
			return boost::lexical_cast<int>(m_strExtrasystRate);
		}
		return 0;
	}

	//返回心跳次数/分钟
	int CXAction_ECG::GetValue_HR()
	{
		return boost::lexical_cast<int>( m_strHR );
	}

	//返回干扰选项
	Artifact CXAction_ECG::GetValue_eArtifact()
	{
		if( m_dwFields & PM_ARTIFACT )
		{
			return IRhythmRule::Get_eArtifact( m_nArtifacts );
		}
		return AF_None;
	}

	//返回EMD
	bool CXAction_ECG::GetValue_EMD()
	{
		if( m_dwFields & PM_EMD )
		{
			return m_sEMD == 2 ? true : false;
		}
		return false;
	}

	//返回传导值
	short CXAction_ECG::GetValue_Conduct()
	{
		if( m_dwFields & PM_CONDUCT )
		{
			return m_sConduct;
		}
		return 0;
	}

	//返回扩展值
	short CXAction_ECG::GetValue_ExtendParam()
	{
		if( m_dwFields & PM_EXTEND )
		{
			return m_sExtendParam;
		}
		return 0;
	}

	/*******************************************************************************/
	// 函数名称： CombineActionParam
	// 功能：   整合体征设置参数
	// 参数：   CXActionVirtual *pDstActionVir:
	// 返回值: 
	void CXAction_ECG::CombineActionParam(CXActionVirtual *pDstActionVir)
	{
	#ifdef  _DEBUG
		if( getActionCaption() != pDstActionVir->getActionCaption() )
			BOOST_ASSERT( 0 );
	#endif
		CXAction_ECG  *pDstAction_ECG  = (CXAction_ECG *)pDstActionVir;

        unsigned long dwFields   = pDstAction_ECG->Get_FieldsFlag();
		if( dwFields &  PM_QRS )
		{
			m_dwFields  |= PM_QRS;
		}
		if( dwFields & PM_BASICRHYTHM )
		{
			m_strRhythm  = pDstAction_ECG->m_strRhythm;
			m_dwFields  |= PM_BASICRHYTHM;
		}
		if( dwFields & PM_HR)
		{
			m_strHR      = pDstAction_ECG->m_strHR;
			m_dwFields  |= PM_HR;
		}
		if( (dwFields & PM_BASICRHYTHM) && (dwFields & PM_HR) )
		{
			m_dwFields   = dwFields;
			if( dwFields & PM_EXTRASYS )
			{
				m_strExtrasyst  = pDstAction_ECG->m_strExtrasyst;
				m_dwFields     |= PM_EXTRASYS;
			}
			else
			{
				m_dwFields  &= ~PM_EXTRASYS;
				m_strExtrasyst.clear();
			}
			if( dwFields & PM_EXTRASYSRATE)
			{
				m_strExtrasystRate = pDstAction_ECG->m_strExtrasystRate;
				m_dwFields     |= PM_EXTRASYSRATE;
			}
			else
			{
				m_dwFields  &= ~PM_EXTRASYSRATE;
				m_strExtrasystRate.clear();
			}
			if( dwFields & PM_ARTIFACT )
			{
				m_nArtifacts = pDstAction_ECG->m_nArtifacts;
				m_dwFields   |= PM_ARTIFACT;
			}
			else
			{
				m_dwFields  &= ~PM_ARTIFACT;
				m_nArtifacts = -1;
			}
			if( (dwFields & PM_EMD) && m_sEMD != 0 )
			{
				m_sEMD   = pDstAction_ECG->m_sEMD;
				m_dwFields |= PM_EMD;
			}
			if( dwFields & PM_CONDUCT )
			{
				m_sConduct  = pDstAction_ECG->m_sConduct;
				m_dwFields |= PM_CONDUCT;
			}
			else
			{
				m_sConduct  = 0;
			}
			if( dwFields & PM_EXTEND )
			{
				m_sExtendParam = pDstAction_ECG->m_sExtendParam;
				m_dwFields |= PM_EXTEND;
			}
			else
			{
				m_sExtendParam = 0;
			}
		}
		m_bRelatePercent   = pDstAction_ECG->Get_bRelatePercent();
	}

	/*******************************************************************************/
	// 函数名称： CloneAction
	// 功能：   拷贝体征参数
	// 参数：   
	// 返回值: 
	CXActionVirtual * CXAction_ECG::CloneAction()
	{
		CXAction_ECG *pNewAction = new CXAction_ECG();

		pNewAction->Set_FieldsFlag( m_dwFields );
		pNewAction->m_nArtifacts = m_nArtifacts;
		pNewAction->m_strExtrasystRate = m_strExtrasystRate;
		pNewAction->m_strRhythm = m_strRhythm;
		pNewAction->m_strExtrasyst = m_strExtrasyst;
		pNewAction->m_strHR    = m_strHR;
		pNewAction->m_sEMD     = m_sEMD;
		pNewAction->m_sConduct     = m_sConduct;
		pNewAction->m_sExtendParam = m_sExtendParam;
		pNewAction->Set_bRelatePercent( m_bRelatePercent );
		return pNewAction;
	}

	void CXAction_ECG::Set_EcgActionParam( const CECGParams &cEcgParam )
	{
		m_dwFields     = cEcgParam.m_dwField;
		m_strRhythm   = IRhythmRule::GetstrBasicRhythm( cEcgParam.m_eBasicRm );
		if( m_dwFields & PM_EXTRASYS )
		{
			m_strExtrasyst  = IRhythmRule::GetstrExtrasys( cEcgParam.m_eExtrasys );
		}
		if( m_dwFields & PM_EXTRASYSRATE )
		{
			m_strExtrasystRate = boost::lexical_cast<std::string>( cEcgParam.m_iExtrasysRate );
		}
		m_strHR = boost::lexical_cast<std::string>(cEcgParam.m_iHR );
		if( m_dwFields & PM_EMD )
		{
			m_sEMD   = cEcgParam.m_bEMD;
		}
		if( m_dwFields & PM_CONDUCT )
		{
			m_sConduct  = cEcgParam.m_sConduct;
		}
		if( m_dwFields & PM_EXTEND )
		{
			m_sExtendParam  = cEcgParam.m_sExtendParam;
		}
		if( m_dwFields & PM_ARTIFACT )
		{
			switch( cEcgParam.m_eArtifact )
			{
			case AF_None:
				{
					m_nArtifacts  = -1;
					break;
				}
			case AF_Muscular:
				{
					m_nArtifacts  = 0;
					break;
				}
			case AF_Frequent:
				{
					m_nArtifacts  = 1;
					break;
				}
			}
		}
	}

	//返回绝对心率值
	int CXAction_ECG::GetValue_AbsoluteHR( int nSrcHR )
	{
		int   nHRValue  = GetValue_HR();
        if( m_bRelatePercent )
		{
			nHRValue  = ( 1 + GetValue_HR()/100.0f ) * nSrcHR;
		}
		return nHRValue;
	}
}}
