#pragma once
#include <list>

#include "..\common\criticalmutex.h"


namespace jysoft { namespace simulator { 

	class CSpO2SignBuildInterface
	{
	protected:
		struct _SpO2SignStruct
		{
			int        m_nSpO2BeginTime;
			int        m_nCycleTime;
		public:
			_SpO2SignStruct()
			{
				m_nSpO2BeginTime = -1;
				m_nCycleTime     = -1;
			};
		};
	public:
		CSpO2SignBuildInterface(void);
		virtual ~CSpO2SignBuildInterface(void);
	protected:
		//Ѫ������ʱ������
		std::list<_SpO2SignStruct *>       m_lstSpO2BeginTime; 
		utility::CCriticalMutex            m_cHandleSpO2SignMap;
	public:
		//����ʱ������
		void ResetSpO2TimeSignList();
		//�Ƴ�ʱ����ڵ�����Ѫ��������
		void RemoveSpO2TimeSigns(const int nMilliterTime);
		//���Ѫ�������㣬���ؼ���������ʱ���
		void AddSpO2SignTime(const long lSpO2BeginTime, const long lCycleTime);
		void AddSpO2SignTimeToExtrasyst(long lSpO2BeginTime, long lPreSpO2BeginTime, long lCycleTime);
		/*******************************************************************************/
		// �������ƣ� JudgeSpO2Sign
		// ���ܣ� �������ಫ��������жϼ�����Ѫ�����źź����������������ź�
		// ������ int  iMilliTime:        ʱ�䣨0.1���룩
		//        int &nRtnMilliTime:     
		// ����ֵ:  0:���źţ�1:��������������2:Ѫ�����ź�����
		int  JudgeSpO2Sign(int  iMilliTime, int &nRtnMilliTime, int &nCycleMilliTime);
	};

}}