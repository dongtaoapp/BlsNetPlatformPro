#include <boost/lexical_cast.hpp>
#include ".\adultbiotsrespparam.h"


namespace jysoft { namespace simulator { namespace resp {

	CAdultBiotsRespParam::CAdultBiotsRespParam(void)
	{
	}

	CAdultBiotsRespParam::~CAdultBiotsRespParam(void)
	{
	}

	//加载某呼吸速率的参数值
	void CAdultBiotsRespParam::LoadRespParams(int nIndex)
	{
		//各数值的含义：常留气量(单位:ml)；最大气量(单位:ml)；吸气时间(单位:0.1ms)；总周期时间(单位:0.1ms)；CO2(吸气)；CO2(呼气)
		static std::string strParams[][7] = {
            {"1500","1500","15000","40000","2000","0","0"},//0
            {"2600","3200","16500","50000","4000","5000","12"}//12
		};
		std::string *pAimPtr = NULL;
		if( nIndex == 0 )
		{
			pAimPtr = strParams[0];
		}
		else
		{
			pAimPtr = strParams[1];
		}
		//移除所有的参数
		m_setParams.clear();
		//常留气量(单位:ml)
		m_setParams["RemainVolume"] = pAimPtr[0];
		//最大气量(单位:ml)
		m_setParams["RespVolume"] = pAimPtr[1];
		//吸气时间(单位:0.1ms)
		m_setParams["Inspiration_Time"] = pAimPtr[2];
		//总周期时间(单位:0.1ms)
		m_setParams["RespTime"] = pAimPtr[3];
		//CO2(吸气)
		m_setParams["CO2Time_Inspirate"] = pAimPtr[4];
		//CO2(呼气)
		m_setParams["CO2Time_Exhale"] = pAimPtr[5];
		//呼吸次数
		m_setParams["RespRate"] = pAimPtr[6];

		m_eRefurbishDataRange = RD_LoadConfigFile;
	}

	//返回吸气的时间(单位：0.1ms)
	int  CAdultBiotsRespParam::GetInspriationTime()
	{
		return boost::lexical_cast<int>(m_setParams["Inspiration_Time"]);
	}

	//返回呼气的时间(单位：0.1ms)
	int  CAdultBiotsRespParam::GetExhaleTime()
	{
		return GetRespCycleTime() - GetInspriationTime();
	}

	//返回周期时间(单位：0.1ms)
	int   CAdultBiotsRespParam::GetRespCycleTime()
	{
		return boost::lexical_cast<int>(m_setParams["RespTime"]);
	}

	//返回总气量
	float CAdultBiotsRespParam::GetRespVolume()
	{
		return boost::lexical_cast<float>(m_setParams["RespVolume"]);
	}

	//返回呼气后的剩余气量
	float CAdultBiotsRespParam::GetRespRemainVolume()
	{
		return boost::lexical_cast<float>(m_setParams["RemainVolume"]);
	}

	//返回吸气时，CO2的下降时间(单位：0.1ms)
	int  CAdultBiotsRespParam::GetCO2Time_Inspiration()
	{
		return boost::lexical_cast<int>(m_setParams["CO2Time_Inspirate"]);
	}

	//返回呼气时，CO2的上升时间(单位：0.1ms)
	int  CAdultBiotsRespParam::GetCO2Time_Exhale()
	{
		return boost::lexical_cast<int>(m_setParams["CO2Time_Exhale"]);
	}

	//返回呼吸次数
	int  CAdultBiotsRespParam::GetRespRate()
	{
		return boost::lexical_cast<int>(m_setParams["RespRate"]);
	}
}}}
