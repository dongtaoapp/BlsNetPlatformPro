#include ".\ParseCPRData_Singleton.h"

#include <boost/utility/binary.hpp>


namespace jysoft{  namespace cpr 
{
	//CPR����/����ָ���ж�
	bool CParseCPRData_Singleton::isCPROrder(const _CPRData &cprData) const
	{
		dynamic_bitset<>  db(_CPR_ORDER_L, BOOST_BINARY(01110000));
		dynamic_bitset<>  cprOder(_CPR_ORDER_L, cprData.get<3>());
		db &= cprOder;
		return db.any();
	}

	//CPR��ʼ/����ָ���ж�
	//bStartJudge: true:��ʼCPR��false:����CPR�� indeterminate:CPR��ʼ/����ָ��
	bool CParseCPRData_Singleton::judgeCPRStartOrStopOrder(const _CPRData &cprData, tribool bStartJudge/*=unknown*/) const
	{
		dynamic_bitset<>  db(_CPR_ORDER_L, cprData.get<3>());
		if( indeterminate(bStartJudge) )
		{
			db &= dynamic_bitset<>(_CPR_ORDER_L, BOOST_BINARY(1110000));
			return (db.to_ulong() == 0x70) ? true : false;
		}
		else if( bStartJudge )
		{
			return (db.to_ulong() == 0x7F) ? true : false;
		}
		else
		{
			return (db.to_ulong() == 0x70) ? true : false;
		}
		return false;
	}

	//CPR�׶α�ʶָ���ж�
	//bPhaseJudge�� true:��ѹ�׶Σ�false:�����׶Σ� indeterminate:�׶�ָ��
	//bStartJudge�� true: ��ʼ��false:������ indeterminate:��Ч
	bool CParseCPRData_Singleton::judgeCPRPhaseStartOrFinishOrder(const _CPRData &cprData, tribool bPhaseJudge, tribool bStartJudge/*=unknown*/) const
	{
		dynamic_bitset<>  db(_CPR_ORDER_L, cprData.get<3>());
		if( indeterminate(bPhaseJudge) )
		{
			db &= dynamic_bitset<>(_CPR_ORDER_L, BOOST_BINARY(1110000));
			return (db.to_ulong() == 0x10) ? true : false;
		}
		else if( indeterminate(bStartJudge) )
		{
			if( bPhaseJudge )
			{
				//��ѹ��ʼ������ж�
				db &= dynamic_bitset<>(_CPR_ORDER_L, BOOST_BINARY(1110100));
				return (db.to_ulong() == 0x14) ? true : false;
			}
			else
			{
				//������ʼ������ж�
				db &= dynamic_bitset<>(_CPR_ORDER_L, BOOST_BINARY(1111000));
				return (db.to_ulong() == 0x18) ? true : false;
			}
		}
		else if( bPhaseJudge )
		{
			//��ѹ��ʼ/�����ж�
			db &= dynamic_bitset<>(_CPR_ORDER_L, 0x7F);
			if( bStartJudge )
			{
				return (db.to_ulong() == 0x17) ? true : false;
			}
			else 
			{
				return (db.to_ulong() == 0x14) ? true : false;
			}
		}
		else
		{
			//������ʼ/�����ж�
			db &= dynamic_bitset<>(_CPR_ORDER_L, 0x7F);
			if( bStartJudge )
			{
				return (db.to_ulong() == 0x1B) ? true : false;
			}
			else 
			{
				return (db.to_ulong() == 0x18) ? true : false;
			}
		}
		return false;
	}

	//���������ж�
	//bScopeJudge�� true:��ѹ���ȣ�false:�������ȣ� unknown:����ָ��
	bool CParseCPRData_Singleton::isCPRScopeOrder(const _CPRData &cprData, tribool bScopeJudge/*=unknown*/) const
	{
		dynamic_bitset<>  db(_CPR_ORDER_L, cprData.get<3>());
		db &= dynamic_bitset<>(_CPR_ORDER_L, 0xF0);
		if( indeterminate(bScopeJudge) )
		{
			if( db.to_ulong() == 0x40 || db.to_ulong() == 0x20 )
			{
				return true;
			}
			return false;
		}
		else if( bScopeJudge )
		{
			//��ѹ����
			return ( db.to_ulong() == 0x20 ) ? true : false;
		}
		else
		{
			//��������
			return ( db.to_ulong() == 0x40 ) ? true : false;
		}
		return false;
	}

	//�����ʶָ���ж�
	bool CParseCPRData_Singleton::isErrorSignOrder(const _CPRData &cprData) const
	{
		dynamic_bitset<>  db(_CPR_ORDER_L, cprData.get<3>());
		db &= dynamic_bitset<>(_CPR_ORDER_L, BOOST_BINARY(11110000));
		return ( db.to_ulong() == 0x60 ) ? true : false;
	}

	//��ѹ���Ȳ�����ֵ
	//����ֵ����ѹ��ȡ���ѹλ�á��ͷ���ȷ
	tuple<int, dynamic_bitset<>, bool>  CParseCPRData_Singleton::getPressureScopeValue(const _CPRData &cprData) const
	{
		int   pressureDepth = 0;
		bool  bReleaseRight = true;
		dynamic_bitset<>  pressurePos(_CPR_ORDER_L, 0);
		//��ѹ���
		pressureDepth = cprData.get<2>();
		//��ѹλ��
		int pos = cprData.get<3>();
		pressurePos = dynamic_bitset<>(_CPR_ORDER_L, cprData.get<3>()) & dynamic_bitset<>(_CPR_ORDER_L, BOOST_BINARY(1111));
		//�ͷ���ȷ
		bReleaseRight = !cprData.get<5>();
		return make_tuple(pressureDepth, pressurePos, bReleaseRight);
	}

	//�������Ȳ���ֵ
	//����ֵ�����������Ƿ��θ
	tuple<int, bool> CParseCPRData_Singleton::getBreathScopeValue(const _CPRData &cprData) const
	{
		int  breathVolume = 0;
		bool bStomach = false;
		//�������Ȳ���ֵ
		breathVolume = cprData.get<0>();
		//�Ƿ��θ
		bStomach = cprData.get<5>();
		return make_tuple(breathVolume, bStomach);
	}

	//���ش����ʶֵ
	_eCPRErrorSign CParseCPRData_Singleton::geteErrorSignValue(const _CPRData &cprData) const
	{
		dynamic_bitset<> order(_CPR_ORDER_L, cprData.get<3>());
		order &= dynamic_bitset<>(_CPR_ORDER_L, BOOST_BINARY(01111));
		return (_eCPRErrorSign)order.to_ulong();
	}

	//Ƶ�������ж�
	//bScopeJudge�� true:��ѹƵ�ʣ�false:����Ƶ�ʣ� unknown:Ƶ��ָ��
	bool CParseCPRData_Singleton::isRateOrder(const _CPRData &cprData, tribool bScopeJudge/*=unknown*/) const
	{
		dynamic_bitset<>  db(_CPR_ORDER_L, cprData.get<3>());
		db &= dynamic_bitset<>(_CPR_ORDER_L, 0xF0);
		if( indeterminate(bScopeJudge) )
		{
			if( db.to_ulong() == 0xC0 || db.to_ulong() == 0xA0 )
			{
				return true;
			}
			return false;
		}
		else if( bScopeJudge )
		{
			//��ѹ����
			return ( db.to_ulong() == 0xA0 ) ? true : false;
		}
		else
		{
			//��������
			return ( db.to_ulong() == 0xC0 ) ? true : false;
		}
		return false;
	}

	//��ѹƵ��ֵ
	//���أ���ѹƵ�ʡ�ʱ���
	tuple<int, unsigned short> CParseCPRData_Singleton::getPressureRateValue(const _CPRData &cprData) const
	{
		int  nRate = 0;
		unsigned short  sTime = 0;
		//��ѹƵ��
		nRate = cprData.get<4>();
		//ʱ���
		sTime = cprData.get<6>();
		return make_tuple(nRate, sTime);
	}

	//����Ƶ��ֵ
	//���أ�ͨ��ʱ�䡢Ƶ�ʡ�ʱ���
	tuple<int, short, unsigned short> CParseCPRData_Singleton::getBreathRateValue(const _CPRData &cprData) const
	{
		int  nRate = 0;
		short  sBreathTime = 0;
		unsigned short  sTime = 0;
		//����Ƶ��
		nRate = cprData.get<4>();
		//ͨ��ʱ��
		sBreathTime = (short)cprData.get<1>();
		//ʱ���
		sTime = cprData.get<6>();
		return make_tuple(nRate, sBreathTime, sTime);
	}
	//-------------------------------------------------------------------------------------------------------------------
	//������ֵ�ж�
	//bRealTimeJudge�� true:��ѹ����ֵ��false:��������ֵ�� unknown:������ֵ����
	bool CParseCPRData_Singleton::isCPRRealTimeSampleData(const _CPRData &cprData, tribool bRealTimeJudge/*=unknown*/) const
	{
		dynamic_bitset<> db(_CPR_ORDER_L, cprData.get<3>());
		if( indeterminate(bRealTimeJudge) )
		{
			db &= dynamic_bitset<>(_CPR_ORDER_L, 0x70);
			return db.none();
		}
		else if( bRealTimeJudge )
		{
			//��ѹ����ֵ
			db &= dynamic_bitset<>(_CPR_ORDER_L, 0x74);
			return (db.to_ulong() == 0x04) ? true : false;
		}
		else 
		{
			//��������ֵ
			db &= dynamic_bitset<>(_CPR_ORDER_L, 0x78);
			return (db.to_ulong() == 0x08) ? true : false;
		}
		return false;
	}

	//��ѹ������ֵ
	//����ֵ����ѹ��ȣ��Ƿ��������ر�ʶ
	tuple<int, bool> CParseCPRData_Singleton::getPressureSample(const _CPRData &cprData) const
	{
		int  nPressureDepth = 0;
		bool bUpSign = false;
		//��ѹ���
		nPressureDepth = cprData.get<2>();
		//�ж��Ƿ������ر�ʶ
		dynamic_bitset<>  db(_CPR_ORDER_L, cprData.get<3>());
		if(db[0] && db[1])
		{
			bUpSign = true;
		}
		return make_tuple(nPressureDepth, bUpSign);
	}

	//���ش���������ֵ
	//����ֵ�����������Ƿ��������ر�ʶ
	tuple<int, bool> CParseCPRData_Singleton::getBreathSample(const _CPRData &cprData) const
	{
		int  nBreathVolume = 0;
		bool bUpSign = false;
		//������
		nBreathVolume = cprData.get<0>() + cprData.get<1>();
		//�ж��Ƿ������ر�ʶ
		dynamic_bitset<>  db(_CPR_ORDER_L, cprData.get<3>());
		if(db[0] && db[1])
		{
			bUpSign = true;
		}
		return make_tuple(nBreathVolume, bUpSign);
	}

	//����CPR������ʼ/������ʶָ��
	_CPRData CParseCPRData_Singleton::createCPRPhaseData(bool bCPRStart, unsigned short sTimestamp/*=0*/) const
	{
		unsigned char  cprOrder = bCPRStart ? 0x7F : 0x70;
		return make_tuple(0, 0, 0, cprOrder, 0, false, sTimestamp);
	}

	//������ѹ�׶α�ʶָ��
	_CPRData CParseCPRData_Singleton::createPressurePhaseData(bool bPhaseStart) const
	{
		unsigned char  cprOrder = bPhaseStart ? 0x17 : 0x14;
		return make_tuple(0, 0, 0, cprOrder, 0, false, 0);
	}

	//���������׶α�ʶָ��
	_CPRData CParseCPRData_Singleton::createBreathPhaseData(bool bPhaseStart) const
	{
		unsigned char  cprOrder = bPhaseStart ? 0x1B : 0x18;
		return make_tuple(0, 0, 0, cprOrder, 0, false, 0);
	}

	//������ѹ����ָ��
	//sDepth�� ��ѹ���   bReleaseError�� �Ƿ���ȷ  sPos: ��ѹλ��  sTimestamp: ʱ�������λ��100ms��
	_CPRData CParseCPRData_Singleton::createPressureDepthData(unsigned char sDepth, bool bReleaseError, unsigned char sPos, unsigned short sTimestamp) const
	{
		unsigned char  cprOrder = 0x20 + sPos;
		return make_tuple(0, 0, sDepth, cprOrder, 0, bReleaseError, sTimestamp);
	}

	//������������ָ��
	//sVolume: ������   bStomach����θ  sTimestamp: ʱ�������λ��100ms��
	_CPRData CParseCPRData_Singleton::createBreathVolumeData(unsigned char sVolume, bool bStomach, unsigned short sTimestamp) const
	{
		return make_tuple(sVolume, 0, 0, 0x40, 0, bStomach, sTimestamp);
	}

	//������ѹƵ��ָ��
	//sRate: ��ѹƵ��   sTimestamp: ʱ�������λ��100ms��
	_CPRData CParseCPRData_Singleton::createPressureRateData(unsigned char sRate, unsigned short sTimestamp) const
	{
		return make_tuple(0, 0, 0, 0xA0, sRate, false, sTimestamp);
	}

	//��������Ƶ��ָ��
	//sRate: ����Ƶ��   sRespTime�� ͨ��ʱ�䣨��λ��100ms��  sTimestamp: ʱ�������λ��100ms��
	_CPRData CParseCPRData_Singleton::createBreathRateData(unsigned char sRate, unsigned char sRespTime, unsigned short sTimestamp) const
	{
		return make_tuple(0, sRespTime, 0, 0xC0, sRate, false, sTimestamp);
	}

	//����Zeroʵʱ����
	//cDepth: ʵʱ����  bPressure: ��ѹ/����  bAscens�������ؿ�ʼ
	_CPRData CParseCPRData_Singleton::createRealTimeSampleData(unsigned char cDepth, bool bPressure, bool bAscens/*=false*/) const
	{
		if( bPressure )
		{
			return make_tuple(0, 0, cDepth, bAscens ? 0x05 : 0x04, 0, false, 0);
		}
		return make_tuple(cDepth, 0, 0, bAscens ? 0x0A : 0x08, 0, false, 0);
	}

	//���������ʶָ��
	_CPRData CParseCPRData_Singleton::createErrorSignData(_eCPRErrorSign eErrorSign) const
	{
		return make_tuple(0, 0, 0, 0x60+eErrorSign, 0, false, 0);
	}
}}
