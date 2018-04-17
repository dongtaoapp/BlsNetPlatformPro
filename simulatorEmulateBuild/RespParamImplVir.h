#pragma once
#include <string>

#include "..\Common\CommonGlobal.h"

namespace jysoft { namespace simulator { namespace resp {

	class CRespParamImplVir
	{
	public:
		CRespParamImplVir(void);
		virtual ~CRespParamImplVir(void);
	public:
		//加载某呼吸速率的参数值
		virtual void LoadRespParams(int nIndex) = 0;
		//返回吸气的时间(单位：0.1ms)
		virtual int  GetInspriationTime() = 0;
		//返回呼气的时间(单位：0.1ms)
		virtual int  GetExhaleTime() = 0;
		//返回周期时间(单位：0.1ms)
		virtual int  GetRespCycleTime() = 0;
		//返回总气量
		virtual float GetRespVolume() = 0;
		//返回呼气后的剩余气量
		virtual float GetRespRemainVolume() = 0;
		//返回吸气时，CO2的下降时间(单位：0.1ms)
		virtual int  GetCO2Time_Inspiration() = 0;
		//返回呼气时，CO2的上升时间(单位：0.1ms)
		virtual int  GetCO2Time_Exhale() = 0;
		//返回无呼吸时的剩余气量
		virtual float GetApneaRemainVolume() = 0;
		//返回呼吸次数
		virtual int GetRespRate() = 0;
	public:
		//设置数据刷新范围为没改变
		virtual void SetRefurbishDataRangeToNoChange() = 0;
		//返回数据刷新范围
		virtual _eRefurbishDataRange Get_eRefurbishDataRange() = 0;
	};
}}}