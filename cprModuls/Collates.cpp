#include ".\Collates.h"

#include "..\Common\ParseCPRData_Singleton.h"


namespace jysoft{  namespace cpr 
{
	CVirCollate::CVirCollate(void)
	{
		m_nMaxValue = m_nMinValue = 0;
	}

	CVirCollate::~CVirCollate(void)
	{
	}

	void CVirCollate::changeJudgeRange(int nMaxValue, int nMinValue)
	{
		m_nMaxValue = nMaxValue;
		m_nMinValue = nMinValue;
	}


	//�����Ƿ������ȷ
    bool CVirCollate::judgeIsDepthRight(const _CPRData &cprData, short vVersion/*=0*/) const
	{
		if( judgeIsOver(cprData, vVersion) || judgeIsLower(cprData, vVersion) )
		{
			return false;
		}
		return true;
	}
	//----------------------------------------------------------------------------------------------
	//��ѹ���ձ���
	CPressureCollate::CPressureCollate()
	{
		m_nMaxValue = 60; //��λ:mm
		m_nMinValue = 50; //��λ:mm
	}

	CPressureCollate::~CPressureCollate()
	{

	}

	//�ж��Ƿ񳬳�
    bool CPressureCollate::judgeIsOver(const _CPRData &cprData, short vVersion/*=0*/) const
	{
		if( getLogicalValue(cprData, vVersion) > m_nMaxValue )
		{
			return true;
		}
		return false;
	}

	//�ж��Ƿ����
    bool CPressureCollate::judgeIsLower(const _CPRData &cprData, short vVersion/*=0*/) const
	{
		if( getLogicalValue(cprData, vVersion) < m_nMinValue )
		{
			return true;
		}
		return false;
	}

	//�����߼�ֵ
    int  CPressureCollate::getLogicalValue(const _CPRData &cprData, short vVersion/*=0*/) const
	{
		int     nPressureDepth, cData;
		tie(cData, tuples::ignore) = CParseCPRData_Singleton::get_const_instance().getPressureSample(cprData);
		float   k[4];
		k[0] = 30.0/35.0f;             //ע�� 0~30mm
		k[1] = (50-30.0f)/(68-35.0f);  //ע��30~50mm
		k[2] = (58-50.0f)/(90-68.0f); //ע��50~58mm
		k[3] = k[2]*3/4;
		//��ͬ�������ò�ͬ��б��
		if( cData <= 35 )
		{
			nPressureDepth = k[0] * cData;
		}
		else if( cData > 35 && cData < 68 )
		{
			nPressureDepth = k[1] * (cData - 35) + 30;
		}
		else if( cData >= 68 && cData < 90 )
		{
			nPressureDepth = k[2] *(cData - 68) + 50;
		}
		else
		{
			nPressureDepth = k[3] * (cData - 90) + 58;
		}
		return nPressureDepth * 1.08;
	}

	//�жϰ�ѹλ�ô���
	bool  CPressureCollate::isPressurePositionError(const _CPRData &cprData) const
	{
		dynamic_bitset<>  pos(_CPR_ORDER_L, 0x00);
		tie(tuples::ignore, pos, tuples::ignore) = CParseCPRData_Singleton::get_const_instance().getPressureScopeValue(cprData);
		return pos.none() ? false : true;
	}

	//�жϰ�ѹ�ͷŲ���
	bool  CPressureCollate::isIncompleteError(const _CPRData &cprData) const
	{
		bool completeRight = true;
		tie(tuples::ignore, tuples::ignore, completeRight) = CParseCPRData_Singleton::get_const_instance().getPressureScopeValue(cprData);
		return completeRight ? false : true;
	}

	//�ж��Ƿ�ѹƵ�ʴ���(Ƶ�ʷ�Χ��100 ~ 120)
	bool  CPressureCollate::isPressureRateError(const _CPRData &cprData) const
	{
		int  rate = 0;
		tie(rate, tuples::ignore) = CParseCPRData_Singleton::get_const_instance().getPressureRateValue(cprData);
		if( rate == 0 || (rate >= 100 && rate <= 120) )
		{
			return true;
		}
		return false;
	}
	//----------------------------------------------------------------------------------------------
	//�������ձ���
	CBreathCollate::CBreathCollate()
	{
		m_nMaxValue = 1000; //��λ:ml
		m_nMinValue = 500;  //��λ:ml
		//ͨ��ʱ�䷶Χ(��λ��100ms)
		lowerRespTime = 5;
		overRespTime  = 60;
	}

	CBreathCollate::~CBreathCollate()
	{

	}

	//�ж��Ƿ񳬳�
    bool CBreathCollate::judgeIsOver(const _CPRData &cprData, short vVersion/*=0*/) const
	{
		if( getLogicalValue( cprData, vVersion ) > m_nMaxValue )
		{
			return true;
		}
		return false;
	}

	//�ж��Ƿ����
    bool CBreathCollate::judgeIsLower(const _CPRData &cprData, short vVersion/*=0*/) const
	{
		if( getLogicalValue( cprData, vVersion ) < m_nMinValue )
		{
			return true;
		}
		return false;
	}

	//�����߼�ֵ
    int  CBreathCollate::getLogicalValue(const _CPRData &cprData, short vVersion/*=0*/) const
	{
		int   nBreathVolume, cData;
		tie(cData, tuples::ignore) = CParseCPRData_Singleton::get_const_instance().getBreathSample(cprData);
		if( cData <= 12 )
			nBreathVolume = cData * 150 / 12;
		else if( cData <= 18 )
			nBreathVolume = (cData-12)*(500-150)/(18-12) + 150;
		else if( cData <= 35 )
			nBreathVolume = (cData-18)*(1000-500)/(35-18) + 500;
		else
			nBreathVolume = cData * 1500 / 35;
		return nBreathVolume;
	}

	//�ж��Ƿ��θ
	bool CBreathCollate::isToStomach( const _CPRData &cprData ) const
	{
		bool  bToStomach = false;
		tie(tuples::ignore, bToStomach) = CParseCPRData_Singleton::get_const_instance().getBreathScopeValue(cprData);
		return bToStomach;
	}

	//�ж�ͨ��ʱ���Ƿ񳬳�
    bool CBreathCollate::judgeIsRespTimeOver(const _CPRData &cprData, short vVersion/*=0*/) const
	{
		int   sRespTime = 0;
		tie(sRespTime, tuples::ignore, tuples::ignore)  = CParseCPRData_Singleton::get_const_instance().getBreathRateValue(cprData);
		if( sRespTime > overRespTime )
		{
			return true;
		}
		return false;
	}

	//�ж�ͨ��ʱ���Ƿ����
    bool CBreathCollate::judgeIsRespTimeLower(const _CPRData &cprData, short vVersion/*=0*/) const
	{
		int   sRespTime = 0;
		tie(sRespTime, tuples::ignore, tuples::ignore) = CParseCPRData_Singleton::get_const_instance().getBreathRateValue(cprData);
		if( sRespTime < lowerRespTime )
		{
			return true;
		}
		return false;
	}

}}
