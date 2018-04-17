#pragma once
#include ".\RespParamImplVir.h"

namespace jysoft { namespace simulator { namespace resp {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ��������ģ����
	�����ˣ�	 hjg
	����ʱ�䣺   2017/2/22
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
		//����ĳ�������ʵĲ���ֵ
		void LoadRespParams(int nIndex)
		{
			m_cRespParam.LoadRespParams( nIndex );
		};
	public:
		//����������ʱ��(��λ��0.1ms)
		int  GetInspriationTime()
		{
			return m_cRespParam.GetInspriationTime();
		};
	public:
		//���غ�����ʱ��(��λ��0.1ms)
		int  GetExhaleTime()
		{
			return m_cRespParam.GetExhaleTime();
		};
	public:
		//��������ʱ��(��λ��0.1ms)
		int  GetRespCycleTime()
		{
			return m_cRespParam.GetRespCycleTime();
		};
	public:
		//����������
		float GetRespVolume()
		{
			return m_cRespParam.GetRespVolume();
		};
	public:
		//���غ������ʣ������
		float GetRespRemainVolume()
		{
			return m_cRespParam.GetRespRemainVolume();
		};
	public:
		//��������ʱ��CO2���½�ʱ��(��λ��0.1ms)
		int  GetCO2Time_Inspiration()
		{
			return m_cRespParam.GetCO2Time_Inspiration();
		};
	public:
		//���غ���ʱ��CO2������ʱ��(��λ��0.1ms)
		int  GetCO2Time_Exhale()
		{
			return m_cRespParam.GetCO2Time_Exhale();
		};
	public:
		//�����޺���ʱ��ʣ������
		float GetApneaRemainVolume()
		{
			return m_cRespParam.GetApneaRemainVolume();
		};
	public:
		//���غ�������
		int GetRespRate()
		{
			return m_cRespParam.GetRespRate();
		};
	public:
		//��������ˢ�·�ΧΪû�ı�
		void SetRefurbishDataRangeToNoChange()
		{
			m_cRespParam.SetRefurbishDataRangeToNoChange();
		};
		//��������ˢ�·�Χ
		_eRefurbishDataRange Get_eRefurbishDataRange()
		{
			return m_cRespParam.Get_eRefurbishDataRange();
		};
	};

}}}