#include <boost/foreach.hpp>
#include ".\respcycledatacollects.h"
#include ".\RespCycleData.h"

namespace jysoft { namespace simulator { namespace resp {

	CRespCycleDataCollects::CRespCycleDataCollects(void)
	{
	}

	CRespCycleDataCollects::~CRespCycleDataCollects(void)
	{
		BOOST_FOREACH(auto x, m_lstRespSegments)
		{
			delete x;
		}
		m_lstRespSegments.clear();
	}

	//���뵽����������
	void CRespCycleDataCollects::AddRespCycleDataPtr(CRespCycleData *pSegment)
	{
		m_cMutex.Lock();
		m_lstRespSegments.push_back( pSegment );
		m_cMutex.Unlock();
	}

	//�Ƴ��������ݰ�
	CRespCycleData * CRespCycleDataCollects::RemoveRespCycleData()
	{
		CRespCycleData *pPtr = NULL;
		m_cMutex.Lock();
		if( m_lstRespSegments.size() > 0 )
		{
			pPtr = *m_lstRespSegments.begin();
			m_lstRespSegments.pop_front();
		}
		m_cMutex.Unlock();
		return pPtr;
	}

	//���ʵʱ���ݰ�
	void CRespCycleDataCollects::EmptyRespCycleDataCollects()
	{
		m_cMutex.Lock();
		BOOST_FOREACH(auto x, m_lstRespSegments)
		{
			delete x;
		}
		m_lstRespSegments.clear();
		m_cMutex.Unlock();
	}
}}}
