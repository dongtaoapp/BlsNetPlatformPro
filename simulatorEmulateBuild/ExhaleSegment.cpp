#include <boost/assert.hpp>
#include ".\exhalesegment.h"

namespace jysoft { namespace simulator { namespace resp {

	CExhaleSegment::CExhaleSegment(void)
	{
	}

	CExhaleSegment::~CExhaleSegment(void)
	{
	}

	/*******************************************************************************/
	// 函数名称： GetVolumeMessageFromSegmentData
	// 功能： 由采样数据获取当前的残留气量和潮气量
	// 参数： [out]float &fRemainVolume：残留气量（单位：ml）
	//        [out]float &fSumVolume ：最大气量  （单位：ml）
	// 返回值:  
	void  CExhaleSegment::GetVolumeMessageFromSegmentData(float &fRemainVolume, float &fSumVolume)
	{
        BOOST_ASSERT(!m_bEmpty);
		fRemainVolume = m_pPtrData[m_dwSize-1];
		fSumVolume  = m_pPtrData[0] ;
	}


	bool CExhaleSegment::isKindOf(const std::string &className )
	{
		if( className == "CExhaleSegment" )
			return true;
		return false;
	}
}}}
