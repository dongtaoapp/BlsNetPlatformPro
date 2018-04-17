#pragma once
#include <list>
#include "irespbuildtypestate.h"

#include "..\Common\CommonGlobal.h"

namespace jysoft { namespace simulator { namespace resp {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     叹气样呼吸模式实现类；特点：频繁地间插深呼吸
	创建人：	 hjg
	创建时间：   2017/2/29
	//-----------------------------------------------------------------------------------------------------------------*/

	class CRespSignTypeState : public IRespBuildTypeState
	{
	public:
		CRespSignTypeState( SimulatePatientType ePatientType);
		virtual ~CRespSignTypeState(void);
	public:
		bool isKindOf(const std::string &className);
		//返回呼吸类别
		virtual eRespMode Get_RespMode() { return RM_Sign; };
	protected:
		std::list<int>            m_lstRespRate;
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
		virtual void OnModifyRespRate(int nRespRate) { };
		/*******************************************************************************/
		// 函数名称： OnCombineNextRespCycleData
		// 功能： 返回下周期的呼吸数据
		// 参数： float fCurrentRemainVolume:           当前的气量
		//        CRespCycleDataCollects *pRespCollect: 
		// 返回值:  
		virtual CRespCycleData * OnCombineNextRespCycleData(float fCurrentRemainVolume, CRespCycleDataCollects *pRespCollect);
	protected:
		void InitialRespRateList();
	};
}}}