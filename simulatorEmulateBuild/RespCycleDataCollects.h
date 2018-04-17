#pragma once
#include <list>

#include "..\common\criticalmutex.h"

namespace jysoft { namespace simulator { namespace resp {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ����ģ��ʵʱ���ݰ�����������
	�����ˣ�	 hjg
	����ʱ�䣺   2017/2/24
	//-----------------------------------------------------------------------------------------------------------------*/

	class CRespCycleData;
	class CRespCycleDataCollects
	{
	public:
		CRespCycleDataCollects(void);
		virtual ~CRespCycleDataCollects(void);
	protected:
		std::list<CRespCycleData *>  m_lstRespSegments;
		utility::CCriticalMutex       m_cMutex;
	public:
		//���뵽����������
		void AddRespCycleDataPtr(CRespCycleData *pSegment);
		//�Ƴ��������ݰ�
		CRespCycleData * RemoveRespCycleData();
		//���ʵʱ���ݰ�
		void EmptyRespCycleDataCollects();
	};
}}}