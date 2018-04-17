#pragma once
#include ".\RespCycleDataCollects.h"
#include ".\RespCycleData.h"
#include ".\RespParamImplVir.h"

#include "..\common\criticalmutex.h"

namespace jysoft { namespace simulator { namespace resp {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     呼吸模式接口
	创建人：	 hjg
	创建时间：   2008/7/22
	//-----------------------------------------------------------------------------------------------------------------*/

	class CInspirationSegment;
	class CExhaleSegment;
	class IRespBuildTypeState
	{
	public:
		IRespBuildTypeState();
		virtual ~IRespBuildTypeState(void);
	protected:
		int                     m_nRespRate;    //呼吸次数/分钟
		CInspirationSegment    *m_pOriginInspirationSegment;
		CExhaleSegment         *m_pOriginExhaleSegment;
	protected:
		utility::CCriticalMutex   m_cMutex;
		CRespParamImplVir      *m_pRespParams;
	public:
		virtual bool isKindOf(const std::string &className) = 0;
		//返回呼吸类别
		virtual eRespMode Get_RespMode() = 0;
	public:
		inline int  Get_nRespRate() { return m_nRespRate; };
		//返回无呼吸时的剩余气量
		virtual float GetApneaRemainVolume() ;
		/*******************************************************************************/
		// 函数名称： InitialLoadOriginSimulateData
		// 功能： 加载原始呼吸数据
		// 参数： 
		// 返回值:  
		virtual void InitialLoadOriginSimulateData(const std::string &respResoucePath, int nRespRate) = 0;
		/*******************************************************************************/
		// 函数名称： OnModifyRespRate
		// 功能： 修改呼吸次数
		// 参数： int nRespRate: 新的呼吸次数
		// 返回值:  
		virtual void OnModifyRespRate(int nRespRate) = 0;
		/*******************************************************************************/
		// 函数名称： OnCombineNextRespCycleData
		// 功能： 返回下周期的呼吸数据
		// 参数：  float fCurrentRemainVolume:           当前的气量
		//         CRespCycleDataCollects *pRespCollect: 
		// 返回值:  
		virtual CRespCycleData * OnCombineNextRespCycleData(float fCurrentRemainVolume, CRespCycleDataCollects *pRespCollect) = 0;
	};
}}}