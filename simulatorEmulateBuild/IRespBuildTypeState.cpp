#include ".\irespbuildtypestate.h"
#include ".\InspirationSegment.h"
#include ".\ExhaleSegment.h"


namespace jysoft { namespace simulator { namespace resp {

	IRespBuildTypeState::IRespBuildTypeState()
	{
		m_nRespRate = 12;
		m_pOriginInspirationSegment = NULL;
		m_pOriginExhaleSegment      = NULL;
		m_pRespParams               = NULL;
	}

	IRespBuildTypeState::~IRespBuildTypeState(void)
	{
		if( m_pOriginInspirationSegment )
		{
			delete m_pOriginInspirationSegment;
			m_pOriginInspirationSegment = NULL;
		}
		if( m_pOriginExhaleSegment )
		{
			delete m_pOriginExhaleSegment;
			m_pOriginExhaleSegment = NULL;
		}
	}

	//返回无呼吸时的剩余气量
	float IRespBuildTypeState::GetApneaRemainVolume()
	{
		return m_pRespParams->GetApneaRemainVolume();
	}
}}}
