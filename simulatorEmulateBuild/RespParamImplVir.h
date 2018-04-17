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
		//����ĳ�������ʵĲ���ֵ
		virtual void LoadRespParams(int nIndex) = 0;
		//����������ʱ��(��λ��0.1ms)
		virtual int  GetInspriationTime() = 0;
		//���غ�����ʱ��(��λ��0.1ms)
		virtual int  GetExhaleTime() = 0;
		//��������ʱ��(��λ��0.1ms)
		virtual int  GetRespCycleTime() = 0;
		//����������
		virtual float GetRespVolume() = 0;
		//���غ������ʣ������
		virtual float GetRespRemainVolume() = 0;
		//��������ʱ��CO2���½�ʱ��(��λ��0.1ms)
		virtual int  GetCO2Time_Inspiration() = 0;
		//���غ���ʱ��CO2������ʱ��(��λ��0.1ms)
		virtual int  GetCO2Time_Exhale() = 0;
		//�����޺���ʱ��ʣ������
		virtual float GetApneaRemainVolume() = 0;
		//���غ�������
		virtual int GetRespRate() = 0;
	public:
		//��������ˢ�·�ΧΪû�ı�
		virtual void SetRefurbishDataRangeToNoChange() = 0;
		//��������ˢ�·�Χ
		virtual _eRefurbishDataRange Get_eRefurbishDataRange() = 0;
	};
}}}