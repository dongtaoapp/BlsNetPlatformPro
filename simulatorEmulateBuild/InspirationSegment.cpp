#include <boost/assert.hpp>
#include ".\inspirationsegment.h"


namespace jysoft { namespace simulator { namespace resp {

	CInspirationSegment::CInspirationSegment(void)
	{
	}

	CInspirationSegment::~CInspirationSegment(void)
	{
	}

	/*******************************************************************************/
	// �������ƣ� GetVolumeMessageFromSegmentData
	// ���ܣ� �ɲ������ݻ�ȡ��ǰ�Ĳ��������ͳ�����
	// ������ [out]float &fRemainVolume��������������λ��ml��
	//        [out]float &fSumVolume ��  ������� ����λ��ml��
	// ����ֵ:  
	void  CInspirationSegment::GetVolumeMessageFromSegmentData(float &fRemainVolume, float &fSumVolume)
	{
        BOOST_ASSERT(!m_bEmpty);
		fRemainVolume = m_pPtrData[0];
		fSumVolume  = m_pPtrData[m_dwSize-1] ;
	}

	bool CInspirationSegment::isKindOf(const std::string &className )
	{
		if( className == "CInspirationSegment" )
			return true;
		return false;
	}

}}}
