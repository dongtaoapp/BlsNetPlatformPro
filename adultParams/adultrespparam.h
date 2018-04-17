#pragma once
#include <string>
#include <boost/unordered_map.hpp>
#include ".\adultparams_global.h"

#include "..\Common\CommonGlobal.h"

namespace jysoft { namespace simulator { namespace resp {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     成人标准呼吸参数提供类
	创建人：	 hjg
	创建时间：   2017/2/22
	//-----------------------------------------------------------------------------------------------------------------*/

    class ADULTPARAMSSHARED_EXPORT CAdultRespParam
	{
	public:
		CAdultRespParam(void);
		virtual ~CAdultRespParam(void);
	public:
		//加载某呼吸速率的参数值
		void LoadRespParams(int nIndex);
		//返回吸气的时间(单位：0.1ms)
		int  GetInspriationTime();
		//返回呼气的时间(单位：0.1ms)
		int  GetExhaleTime();
		//返回周期时间(单位：0.1ms)
		int  GetRespCycleTime();
		//返回总气量
		float GetRespVolume();
		//返回呼气后的剩余气量
		float GetRespRemainVolume();
		//返回吸气时，CO2的下降时间(单位：0.1ms)
		int  GetCO2Time_Inspiration();
		//返回呼气时，CO2的上升时间(单位：0.1ms)
		int  GetCO2Time_Exhale();
		//返回呼吸次数
		int  GetRespRate();
	public:
		//返回无呼吸时的剩余气量
		inline float GetApneaRemainVolume() { return 1500.0f; };
	public:
		//设置数据刷新范围为没改变
		inline void SetRefurbishDataRangeToNoChange() { m_eRefurbishDataRange = RD_NoChange; };
		inline _eRefurbishDataRange Get_eRefurbishDataRange() { return m_eRefurbishDataRange; };
	protected:
		boost::unordered_map<std::string, std::string>  m_setParams;
		_eRefurbishDataRange       m_eRefurbishDataRange;
	};
}}}
