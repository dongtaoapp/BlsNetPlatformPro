#pragma once
#include ".\VirtualRespSegment.h"

namespace jysoft { namespace simulator { namespace resp {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     �������ڷ�Ϊ�����κͺ����Σ������������������ݲ�����
	�����ˣ�	 hjg
	����ʱ�䣺   2017/2/22
	//-----------------------------------------------------------------------------------------------------------------*/

	class CInspirationSegment : public CVirtualRespSegment
	{
	public:
		CInspirationSegment(void);
		virtual ~CInspirationSegment(void);
	protected: //���ຯ������
		/*******************************************************************************/
		// �������ƣ� GetVolumeMessageFromSegmentData
		// ���ܣ� �ɲ������ݻ�ȡ��ǰ�Ĳ��������ͳ�����
		// ������ [out]float &fRemainVolume��������������λ��ml��
		//        [out]float &fSumVolume ��  �������  ����λ��ml��
		// ����ֵ:  
		void GetVolumeMessageFromSegmentData(float &fRemainVolume, float &fSumVolume);
	public:
		bool isKindOf(const std::string &className );
	};
}}}