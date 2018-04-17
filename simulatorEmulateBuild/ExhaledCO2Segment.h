#pragma once

#include ".\virtualrespsegment.h"
#include ".\InspirationSegment.h"

namespace jysoft { namespace simulator { namespace etCO2 {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ��������ʱ��CO2�������������ڴ˶����ݲ�����
	�����ˣ�	 hjg
	����ʱ�䣺   2017/2/27
	//-----------------------------------------------------------------------------------------------------------------*/

	class CExhaledCO2Segment : public resp::CVirtualRespSegment
	{
	public:
		CExhaledCO2Segment(void);
		virtual ~CExhaledCO2Segment(void);
	protected:
		resp::CInspirationSegment     m_cOriginCO2Segment;
		int                     m_nCO2Percent;           //������̼�İٷֱ�
	private:
		int                     m_nCurrentCO2Per;        //��ǰ�Ķ�����̼�İٷֱ�
	public:
		bool isKindOf(const std::string &className );
		/*******************************************************************************/
		//���ܣ� �����ļ��ڵ�CO2����
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
		void  LineIntervalLinkSampleData(float fValue, int nIntervalTime);
	public:
		/*******************************************************************************/
		// �������ƣ� InitilaCO2Segment
		// ���ܣ� ��������ʱ��������CO2��ģ���źŴ���
		// ������  
		//         int nMilliChangeTime: CO2������ʱ�䣨0.1���룩
		//         int nMilliOtherTime:  �������������ʱ�䣨0.1���룩
		// ����ֵ:  
		void InitilaCO2Segment(int nMilliChangeTime, int nMilliOtherTime);
	public:
		void Set_CO2Percent(int nValue);
		inline int Get_CurrentCO2Percent() { return m_nCurrentCO2Per; };
	};
}}}