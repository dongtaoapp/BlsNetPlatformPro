#pragma once
#include "irespbuildtypestate.h"

#include "..\Common\CommonGlobal.h"

namespace jysoft { namespace simulator { namespace resp {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     毕奥呼吸(或"间停呼吸")模式实现类；特点：间插不规则的周期性呼吸暂停打乱了呼吸的连续性
	创建人：	 hjg
	创建时间：   2008/7/29
	//-----------------------------------------------------------------------------------------------------------------*/

	class CRespBiotTypeState : public IRespBuildTypeState
	{
	public:
		CRespBiotTypeState(SimulatePatientType ePatientType);
		virtual ~CRespBiotTypeState(void);
	public:
		bool isKindOf(const std::string &className);
		//返回呼吸类别
		virtual eRespMode Get_RespMode() { return RM_Biots; };
	protected:
		int                                       m_nOriginRate;
		int                                       m_nStepNum;             //用于确定暂停策略
		int                                       m_nSumStepNum;
	public:
		/*******************************************************************************/
		// 函数名称： InitialLoadOriginSimulateData
		// 功能： 加载原始呼吸数据
		// 参数： 
		// 返回值:  
		virtual void InitialLoadOriginSimulateData(const std::string &respResoucePath, int nRespRate) ;
		/*******************************************************************************/
		// 函数名称： OnModifyRespRate
		// 功能： 修改呼吸次数
		// 参数： int nRespRate: 新的呼吸次数
		// 返回值:  
		virtual void OnModifyRespRate(int nRespRate);
		/*******************************************************************************/
		// 函数名称： OnCombineNextRespCycleData
		// 功能： 返回下周期的呼吸数据
		// 参数： float fCurrentRemainVolume:           当前的气量
		//        CRespCycleDataCollects *pRespCollect: 
		// 返回值:  
		virtual CRespCycleData * OnCombineNextRespCycleData(float fCurrentRemainVolume, CRespCycleDataCollects *pRespCollect);
	protected:
		//初始化暂停策略
		void InitialApneaStrategy(int nRespRate);
	};
}}}