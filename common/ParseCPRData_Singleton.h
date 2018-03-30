#pragma once

#include ".\CommonGlobal.h"

#include <boost/logic/tribool.hpp>
#include <boost/serialization/singleton.hpp>

#define  _CPR_ORDER_L           8

using namespace boost;
//BOOST_TRIBOOL_THIRD_STATE(unknown)

namespace jysoft{  namespace cpr {
	   /*-----------------------------------------------------------------------------------------------------------------
		��˵����     CPR���ݽ����ࣨ������
		�����ˣ�	 hjg
		����ʱ�䣺   2017/4/9      �޸�ʱ�䣺2018.2.27
		//****************************************************************************************************/
		//CPRָ���ʽ˵����
	    //    CPR��ʼ����ָ�0x7F:CPR��ʼ, 0x70:CPR����
	    //                     ʱ�����<��Ч>
	    //    CPR�׶α�ʶָ�
	    //                    0x1B:������ʼ, 0x18:��������
	    //                    0x17:��ѹ��ʼ, 0x14:��ѹ����
	    //    CPR����ָ��:
	    //                    ��������: 0x4X, ��ѹ����:0x2X
	    //                    ��ѹλ�ã�0~3λ�ֱ��ʾ���ҡ��ϡ��´���λ��; ��Ϊ0��ʾ��ȷ����Ϊ1��ʾ��ȷ�������λ��
	    //                    ʱ����� <��Ч>
	    //    CPRƵ��ָ�
	    //                    ����Ƶ��: 0xCX, ��ѹƵ��:0xAX
	    //                    ʱ����� <��Ч>
	    //    �����ʶֵ��
	    //                    ��ʶֵ:  0x60
	    //                    ʱ����� <��Ч?>
	    //    CPR��������:
	    //                    �������ݣ���3λΪ1����1λ�����������ؿ�ʼ
	    //                    ��ѹ���ݣ���2λΪ1����0λ����ѹ�����ؿ�ʼ
		//-----------------------------------------------------------------------------------------------------------------*/
	class  CParseCPRData_Singleton : public serialization::singleton<CParseCPRData_Singleton>
	{
	public:
		//CPR����/����ָ���ж�
		BOOST_DLLEXPORT bool isCPROrder(const _CPRData &cprData) const;
		//CPR��ʼ/����ָ���ж�
		//bStartJudge: true:��ʼCPR��false:����CPR�� indeterminate:CPR��ʼ/����ָ��
		BOOST_DLLEXPORT bool judgeCPRStartOrStopOrder(const _CPRData &cprData, tribool bStartJudge = indeterminate) const;
		//CPR�׶α�ʶָ���ж�
		//bPhaseJudge�� true:��ѹ�׶Σ�false:�����׶Σ� indeterminate:�׶�ָ��
		//bStartJudge�� true: ��ʼ��false:������ indeterminate:��Ч
		BOOST_DLLEXPORT bool judgeCPRPhaseStartOrFinishOrder(const _CPRData &cprData, tribool bPhaseJudge, tribool bStartJudge = indeterminate) const;
		//���������ж�
		//bScopeJudge�� true:��ѹ���ȣ�false:�������ȣ� unknown:����ָ��
		BOOST_DLLEXPORT bool isCPRScopeOrder(const _CPRData &cprData, tribool bScopeJudge = indeterminate) const;
		//�����ʶָ���ж�
		BOOST_DLLEXPORT bool isErrorSignOrder(const _CPRData &cprData) const;
		//��ѹ���Ȳ�����ֵ
		//����ֵ����ѹ��ȡ���ѹλ�á��ͷ���ȷ
		BOOST_DLLEXPORT tuple<int, dynamic_bitset<>, bool>  getPressureScopeValue(const _CPRData &cprData) const;
		//�������Ȳ���ֵ
		//����ֵ�����������Ƿ��θ
		BOOST_DLLEXPORT tuple<int, bool> getBreathScopeValue(const _CPRData &cprData) const;
		//Ƶ�������ж�
		//bScopeJudge�� true:��ѹƵ�ʣ�false:����Ƶ�ʣ� unknown:Ƶ��ָ��
		BOOST_DLLEXPORT bool isRateOrder(const _CPRData &cprData, tribool bScopeJudge = indeterminate) const;
		//��ѹƵ��ֵ
		//���أ���ѹƵ�ʡ�ʱ���
		BOOST_DLLEXPORT tuple<int, unsigned short> getPressureRateValue(const _CPRData &cprData) const;
		//����Ƶ��ֵ
		//���أ�ͨ��ʱ�䡢Ƶ�ʡ�ʱ���
		BOOST_DLLEXPORT tuple<int, short, unsigned short> getBreathRateValue(const _CPRData &cprData) const;
		//���ش����ʶֵ
		BOOST_DLLEXPORT _eCPRErrorSign geteErrorSignValue(const _CPRData &cprData) const;
		//-------------------------------------------------------------------------------------------------------------------
		//������ֵ�ж�
		//bRealTimeJudge�� true:��ѹ����ֵ��false:��������ֵ�� unknown:������ֵ����
		BOOST_DLLEXPORT bool isCPRRealTimeSampleData(const _CPRData &cprData, tribool bRealTimeJudge = indeterminate) const;
		//��ѹ������ֵ
		//����ֵ����ѹ��ȣ��Ƿ��������ر�ʶ
		BOOST_DLLEXPORT tuple<int, bool> getPressureSample(const _CPRData &cprData) const;
		//���ش���������ֵ
		//����ֵ�����������Ƿ��������ر�ʶ
		BOOST_DLLEXPORT tuple<int, bool> getBreathSample(const _CPRData &cprData) const;
		//--------------------------------------------------------------------------------------------------------------------
		//����CPR������ʼ/������ʶָ��
		BOOST_DLLEXPORT _CPRData createCPRPhaseData(bool bCPRStart, unsigned short sTimestamp = 0) const;
		//������ѹ�׶α�ʶָ��
		BOOST_DLLEXPORT _CPRData createPressurePhaseData(bool bPhaseStart) const;
		//���������׶α�ʶָ��
		BOOST_DLLEXPORT _CPRData createBreathPhaseData(bool bPhaseStart) const;
		//������ѹ����ָ��
		//sDepth�� ��ѹ���   bReleaseError�� �ͷŴ���  sPos: ��ѹλ��  sTimestamp: ʱ�������λ��100ms��
		BOOST_DLLEXPORT _CPRData createPressureDepthData(unsigned char sDepth, bool bReleaseError, unsigned char sPos, unsigned short sTimestamp) const;
		//������������ָ��
		//sVolume: ������   bStomach����θ  sTimestamp: ʱ�������λ��100ms��
		BOOST_DLLEXPORT _CPRData createBreathVolumeData(unsigned char sVolume, bool bStomach, unsigned short sTimestamp) const;
		//������ѹƵ��ָ��
		//sRate: ��ѹƵ��   sTimestamp: ʱ�������λ��100ms��
		BOOST_DLLEXPORT _CPRData createPressureRateData(unsigned char sRate, unsigned short sTimestamp) const;
		//��������Ƶ��ָ��
		//sRate: ����Ƶ��   sRespTime�� ͨ��ʱ�䣨��λ��100ms��  sTimestamp: ʱ�������λ��100ms��
		BOOST_DLLEXPORT _CPRData createBreathRateData(unsigned char sRate, unsigned char sRespTime, unsigned short sTimestamp) const;
		//����Zeroʵʱ����
		//cDepth: ʵʱ����  bPressure: ��ѹ/����  bAscens�������ؿ�ʼ
		BOOST_DLLEXPORT _CPRData createRealTimeSampleData(unsigned char cDepth, bool bPressure, bool bAscens=false) const;
		//���������ʶָ��
		BOOST_DLLEXPORT _CPRData createErrorSignData(_eCPRErrorSign eErrorSign) const;
	};
}}
