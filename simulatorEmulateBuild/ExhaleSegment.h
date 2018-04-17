#pragma once
#include ".\VirtualRespSegment.h"

namespace jysoft { namespace simulator { namespace resp {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     呼吸周期分为吸气段和呼出段；此类用于呼出段数据操作类
	创建人：	 hjg
	创建时间：   2017/2/22
	//-----------------------------------------------------------------------------------------------------------------*/

	class CExhaleSegment : public CVirtualRespSegment
	{
	public:
		CExhaleSegment(void);
		virtual ~CExhaleSegment(void);
	protected:
		/*******************************************************************************/
		// 函数名称： GetVolumeMessageFromSegmentData
		// 功能： 由采样数据获取当前的残留气量和潮气量
		// 参数： [out]float &fRemainVolume：残留气量（单位：ml）
		//        [out]float &fSumVolume ：  最大气量  （单位：ml）
		// 返回值:  
		void GetVolumeMessageFromSegmentData(float &fRemainVolume, float &fSumVolume);
	public:
		bool isKindOf(const std::string &className );
	};
}}}