#pragma once
#include ".\virtualrespsegment.h"
#include ".\ExhaleSegment.h"


namespace jysoft { namespace simulator { namespace etCO2 {
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ��������ʱ��CO2�½����������ڴ˶����ݲ�����
	�����ˣ�	 hjg
	����ʱ�䣺   2017/2/27
	//-----------------------------------------------------------------------------------------------------------------*/

	class CInspiratedCO2Segment : public resp::CVirtualRespSegment
	{
	public:
		CInspiratedCO2Segment(void);
		virtual ~CInspiratedCO2Segment(void);
	protected:
		resp::CExhaleSegment  m_cOriginCO2Segment;  //ԭʼCO2�½���
	public:
		virtual bool isKindOf(const std::string &className );
		/*******************************************************************************/
		//���ܣ� �����ļ��ڵĺ�������
		//������ const CString &strFilePath: �����ļ�·��
		//����ֵ:  
		virtual bool LoadOriginSegmentData(const std::string &strFilePath);
	protected:
		/*******************************************************************************/
		// �������ƣ� GetVolumeMessageFromSegmentData
		// ���ܣ� �ɲ������ݻ�ȡ��ǰ�Ĳ��������ͳ�����
		// ������ [out]float &fRemainVolume��������������λ��ml��
		//        [out]float &fSumVolume ��  �������  ����λ��ml��
		// ����ֵ:  
		virtual void GetVolumeMessageFromSegmentData(float &fRemainVolume, float &fSumVolume) { };
		//ֱ���������
		void  HoriIntervalLinkData(int nTime);
	public:
		/*******************************************************************************/
		// �������ƣ� InitilaCO2Segment
		// ���ܣ� ����ʱ��������CO2��ģ���źŴ���
		// ������  int nCO2Per:          CO2�ٷֱ�
		//         int nMilliChangeTime: CO2�轵��ʱ�䣨0.1���룩
		//         int nMilliOtherTime:  �轵���������ʱ�䣨0.1���룩
		// ����ֵ:  
		void InitilaCO2Segment(int nCO2Per, int nMilliChangeTime, int nMilliOtherTime);
	};
}}}