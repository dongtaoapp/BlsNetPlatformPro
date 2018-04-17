#pragma once
#include <string>
#include <boost/unordered_map.hpp>
#include ".\adultparams_global.h"

#include "..\Common\CommonGlobal.h"

namespace jysoft { namespace simulator { namespace resp {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ���˱�׼���������ṩ��
	�����ˣ�	 hjg
	����ʱ�䣺   2017/2/22
	//-----------------------------------------------------------------------------------------------------------------*/

    class ADULTPARAMSSHARED_EXPORT CAdultRespParam
	{
	public:
		CAdultRespParam(void);
		virtual ~CAdultRespParam(void);
	public:
		//����ĳ�������ʵĲ���ֵ
		void LoadRespParams(int nIndex);
		//����������ʱ��(��λ��0.1ms)
		int  GetInspriationTime();
		//���غ�����ʱ��(��λ��0.1ms)
		int  GetExhaleTime();
		//��������ʱ��(��λ��0.1ms)
		int  GetRespCycleTime();
		//����������
		float GetRespVolume();
		//���غ������ʣ������
		float GetRespRemainVolume();
		//��������ʱ��CO2���½�ʱ��(��λ��0.1ms)
		int  GetCO2Time_Inspiration();
		//���غ���ʱ��CO2������ʱ��(��λ��0.1ms)
		int  GetCO2Time_Exhale();
		//���غ�������
		int  GetRespRate();
	public:
		//�����޺���ʱ��ʣ������
		inline float GetApneaRemainVolume() { return 1500.0f; };
	public:
		//��������ˢ�·�ΧΪû�ı�
		inline void SetRefurbishDataRangeToNoChange() { m_eRefurbishDataRange = RD_NoChange; };
		inline _eRefurbishDataRange Get_eRefurbishDataRange() { return m_eRefurbishDataRange; };
	protected:
		boost::unordered_map<std::string, std::string>  m_setParams;
		_eRefurbishDataRange       m_eRefurbishDataRange;
	};
}}}
