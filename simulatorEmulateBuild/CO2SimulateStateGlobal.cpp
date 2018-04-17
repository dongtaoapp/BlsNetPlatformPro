#include ".\co2simulatestateglobal.h"
#include ".\CO2SimulateBuild.h"

namespace jysoft { namespace simulator { namespace etCO2 {

	//--------------------------------------------------------------------------------------------------
	//接口ICO2SimulateState
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
	//类CCO2SimulateAutoRespState
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
	// 函数名称： DoExhaledCO2EndHandle
	// 功能： 呼气阶段，处理
	// 参数： 
	// 返回值: FALSE: 没处理，默认方式实施；TRUE: 已做处理
	bool CCO2SimulateAutoRespState::DoExhaledCO2EndHandle(resp::CVirtualRespSegment *pReadSegment)
	{
		if( pReadSegment != NULL && pReadSegment->isKindOf( "CInspiratedCO2Segment" ) )
		{
			//修改二氧化碳分压波形
			if( m_pEtCO2SimulateBuild && m_bFirstAutoRespState )
			{
				m_pEtCO2SimulateBuild->OnModifyCO2PercentValue( m_nCO2Percent );
				m_bFirstAutoRespState = FALSE;
			}
		}
		return false;
	}

	//--------------------------------------------------------------------------------------------------
	//类CCO2SimulateNoRespState
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
