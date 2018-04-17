#include <boost/assert.hpp>
#include ".\exhalesegment.h"

namespace jysoft { namespace simulator { namespace resp {

	CExhaleSegment::CExhaleSegment(void)
	{
	}

	CExhaleSegment::~CExhaleSegment(void)
	{
	}

	/*******************************************************************************/
	// �������ƣ� GetVolumeMessageFromSegmentData
	// ���ܣ� �ɲ������ݻ�ȡ��ǰ�Ĳ��������ͳ�����
	// ������ [out]float &fRemainVolume��������������λ��ml��
	//        [out]float &fSumVolume ���������  ����λ��ml��
	// ����ֵ:  
	void  CExhaleSegment::GetVolumeMessageFromSegmentData(float &fRemainVolume, float &fSumVolume)
	{
        BOOST_ASSERT(!m_bEmpty);
		fRemainVolume = m_pPtrData[m_dwSize-1];
		fSumVolume  = m_pPtrData[0] ;
	}


	bool CExhaleSegment::isKindOf(const std::string &className )
	{
		if( className == "CExhaleSegment" )
			return true;
		return false;
	}
}}}
