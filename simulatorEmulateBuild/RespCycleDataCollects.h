#pragma once
#include <list>

#include "..\common\criticalmutex.h"

namespace jysoft { namespace simulator { namespace resp {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     呼吸模拟实时数据包垃圾受理器
	创建人：	 hjg
	创建时间：   2017/2/24
	//-----------------------------------------------------------------------------------------------------------------*/

	class CRespCycleData;
	class CRespCycleDataCollects
	{
	public:
		CRespCycleDataCollects(void);
		virtual ~CRespCycleDataCollects(void);
	protected:
		std::list<CRespCycleData *>  m_lstRespSegments;
		utility::CCriticalMutex       m_cMutex;
	public:
		//加入到垃圾受理器
		void AddRespCycleDataPtr(CRespCycleData *pSegment);
		//移除呼吸数据包
		CRespCycleData * RemoveRespCycleData();
		//清空实时数据包
		void EmptyRespCycleDataCollects();
	};
}}}