#include <boost/lexical_cast.hpp>
#include ".\adultapneusticrespparam.h"

namespace jysoft { namespace simulator { namespace resp {

	CAdultApneusticRespParam::CAdultApneusticRespParam(void)
	{
	}

	CAdultApneusticRespParam::~CAdultApneusticRespParam(void)
	{
	}

	//����ĳ�������ʵĲ���ֵ
	void CAdultApneusticRespParam::LoadRespParams(int nIndex)
	{
		//����ֵ�ĺ��壺��������(��λ:ml)���������(��λ:ml)������ʱ��(��λ:0.1ms)��������ʱ��(��λ:0.1ms)��CO2(����)��CO2(����)
		static std::string strParams[][7] = {
            {"1500","1500","15000","60000","2000","0","0"},//0
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
		//�Ƴ����еĲ���
		m_setParams.clear();
		//��������(��λ:ml)
		m_setParams["RemainVolume"] = pAimPtr[0];
		//�������(��λ:ml)
		m_setParams["RespVolume"] = pAimPtr[1];
		//����ʱ��(��λ:0.1ms)
		m_setParams["Inspiration_Time"] = pAimPtr[2];
		//������ʱ��(��λ:0.1ms)
		m_setParams["RespTime"] = pAimPtr[3];
		//CO2(����)
		m_setParams["CO2Time_Inspirate"] = pAimPtr[4];
		//CO2(����)
		m_setParams["CO2Time_Exhale"] = pAimPtr[5];
		//��������
		m_setParams["RespRate"] = pAimPtr[6];

		m_eRefurbishDataRange = RD_LoadConfigFile;
	}

	//����������ʱ��(��λ��0.1ms)
	int  CAdultApneusticRespParam::GetInspriationTime()
	{
		return boost::lexical_cast<int>(m_setParams["Inspiration_Time"]);
	}

	//���غ�����ʱ��(��λ��0.1ms)
	int  CAdultApneusticRespParam::GetExhaleTime()
	{
		return GetRespCycleTime() - GetInspriationTime();
	}

	//��������ʱ��(��λ��0.1ms)
	int   CAdultApneusticRespParam::GetRespCycleTime()
	{
		return boost::lexical_cast<int>(m_setParams["RespTime"]);
	}

	//����������
	float CAdultApneusticRespParam::GetRespVolume()
	{
		return boost::lexical_cast<float>(m_setParams["RespVolume"]);
	}

	//���غ������ʣ������
	float CAdultApneusticRespParam::GetRespRemainVolume()
	{
		return boost::lexical_cast<float>(m_setParams["RemainVolume"]);
	}

	//��������ʱ��CO2���½�ʱ��(��λ��0.1ms)
	int  CAdultApneusticRespParam::GetCO2Time_Inspiration()
	{
		return boost::lexical_cast<int>(m_setParams["CO2Time_Inspirate"]);
	}

	//���غ���ʱ��CO2������ʱ��(��λ��0.1ms)
	int  CAdultApneusticRespParam::GetCO2Time_Exhale()
	{
		return boost::lexical_cast<int>(m_setParams["CO2Time_Exhale"]);
	}

	//���غ�������
	int  CAdultApneusticRespParam::GetRespRate()
	{
		return boost::lexical_cast<int>(m_setParams["RespRate"]);
	}
}}}
