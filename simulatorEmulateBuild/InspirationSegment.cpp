#include <boost/assert.hpp>
#include ".\inspirationsegment.h"


namespace jysoft { namespace simulator { namespace resp {

	CInspirationSegment::CInspirationSegment(void)
	{
	}

	CInspirationSegment::~CInspirationSegment(void)
	{
	}

	/*******************************************************************************/
	// 函数名称： GetVolumeMessageFromSegmentData
	// 功能： 由采样数据获取当前的残留气量和潮气量
	// 参数： [out]float &fRemainVolume：残留气量（单位：ml）
	//        [out]float &fSumVolume ：  最大气量 （单位：ml）
	// 返回值:  
	void  CInspirationSegment::GetVolumeMessageFromSegmentData(float &fRemainVolume, float &fSumVolume)
	{
        BOOST_ASSERT(!m_bEmpty);
		fRemainVolume = m_pPtrData[0];
		fSumVolume  = m_pPtrData[m_dwSize-1] ;
	}

	bool CInspirationSegment::isKindOf(const std::string &className )
	{
		if( className == "CInspirationSegment" )
			return true;
		return false;
	}

}}}
