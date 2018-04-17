#pragma once
#include ".\RespParamImplVir.h"

namespace jysoft { namespace simulator { namespace resp {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     呼吸参数模板类
	创建人：	 hjg
	创建时间：   2017/2/22
	//-----------------------------------------------------------------------------------------------------------------*/
	template<class DataType>
	class CRespParamImpl : public CRespParamImplVir
	{
	public:
		CRespParamImpl(void) { };
		virtual ~CRespParamImpl(void) { };
	protected:
		DataType              m_cRespParam;
	public:
		//加载某呼吸速率的参数值
		void LoadRespParams(int nIndex)
		{
			m_cRespParam.LoadRespParams( nIndex );
		};
	public:
		//返回吸气的时间(单位：0.1ms)
		int  GetInspriationTime()
		{
			return m_cRespParam.GetInspriationTime();
		};
	public:
		//返回呼气的时间(单位：0.1ms)
		int  GetExhaleTime()
		{
			return m_cRespParam.GetExhaleTime();
		};
	public:
		//返回周期时间(单位：0.1ms)
		int  GetRespCycleTime()
		{
			return m_cRespParam.GetRespCycleTime();
		};
	public:
		//返回总气量
		float GetRespVolume()
		{
			return m_cRespParam.GetRespVolume();
		};
	public:
		//返回呼气后的剩余气量
		float GetRespRemainVolume()
		{
			return m_cRespParam.GetRespRemainVolume();
		};
	public:
		//返回吸气时，CO2的下降时间(单位：0.1ms)
		int  GetCO2Time_Inspiration()
		{
			return m_cRespParam.GetCO2Time_Inspiration();
		};
	public:
		//返回呼气时，CO2的上升时间(单位：0.1ms)
		int  GetCO2Time_Exhale()
		{
			return m_cRespParam.GetCO2Time_Exhale();
		};
	public:
		//返回无呼吸时的剩余气量
		float GetApneaRemainVolume()
		{
			return m_cRespParam.GetApneaRemainVolume();
		};
	public:
		//返回呼吸次数
		int GetRespRate()
		{
			return m_cRespParam.GetRespRate();
		};
	public:
		//设置数据刷新范围为没改变
		void SetRefurbishDataRangeToNoChange()
		{
			m_cRespParam.SetRefurbishDataRangeToNoChange();
		};
		//返回数据刷新范围
		_eRefurbishDataRange Get_eRefurbishDataRange()
		{
			return m_cRespParam.Get_eRefurbishDataRange();
		};
	};

}}}