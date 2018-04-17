#include ".\co2simulatestateglobal.h"
#include ".\CO2SimulateBuild.h"

namespace jysoft { namespace simulator { namespace etCO2 {

	//--------------------------------------------------------------------------------------------------
	//�ӿ�ICO2SimulateState
	ICO2SimulateState::ICO2SimulateState(void)
	{
		m_nCO2Percent  = 0;
	}

	ICO2SimulateState::~ICO2SimulateState(void)
	{
	}

}}}

namespace jysoft { namespace simulator { namespace etCO2 {
	//--------------------------------------------------------------------------------------------------
	//��CCO2SimulateAutoRespState
	CCO2SimulateAutoRespState::CCO2SimulateAutoRespState()
	{
		m_bFirstAutoRespState  = FALSE;
		m_pEtCO2SimulateBuild  = NULL;
	}

	CCO2SimulateAutoRespState::~CCO2SimulateAutoRespState()
	{

	}

	bool CCO2SimulateAutoRespState::isKindOf(const std::string &className)
	{
		if( className == "CCO2SimulateAutoRespState" )
		{
			return true;
		}
		return false;
	}

	void CCO2SimulateAutoRespState::Set_EtCO2SimulateBuildPtr( CCO2SimulateBuild *pEtCO2Build )
	{
		m_pEtCO2SimulateBuild  = pEtCO2Build;
	}
	
	/*******************************************************************************/
	// �������ƣ� DoExhaledCO2EndHandle
	// ���ܣ� �����׶Σ�����
	// ������ 
	// ����ֵ: FALSE: û����Ĭ�Ϸ�ʽʵʩ��TRUE: ��������
	bool CCO2SimulateAutoRespState::DoExhaledCO2EndHandle(resp::CVirtualRespSegment *pReadSegment)
	{
		if( pReadSegment != NULL && pReadSegment->isKindOf( "CInspiratedCO2Segment" ) )
		{
			//�޸Ķ�����̼��ѹ����
			if( m_pEtCO2SimulateBuild && m_bFirstAutoRespState )
			{
				m_pEtCO2SimulateBuild->OnModifyCO2PercentValue( m_nCO2Percent );
				m_bFirstAutoRespState = FALSE;
			}
		}
		return false;
	}

	//--------------------------------------------------------------------------------------------------
	//��CCO2SimulateNoRespState
	CCO2SimulateNoRespState::CCO2SimulateNoRespState()
	{
	
	}

	CCO2SimulateNoRespState::~CCO2SimulateNoRespState()
	{
	
	}

	bool CCO2SimulateNoRespState::isKindOf(const std::string &className)
	{
		if( className == "CCO2SimulateNoRespState" )
		{
			return true;
		}
		return false;
	}
}}}
