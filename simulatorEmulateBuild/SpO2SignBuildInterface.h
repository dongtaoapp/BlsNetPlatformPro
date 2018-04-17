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
		//血氧启动时间连表
		std::list<_SpO2SignStruct *>       m_lstSpO2BeginTime; 
		utility::CCriticalMutex            m_cHandleSpO2SignMap;
	public:
		//重置时间链表
		void ResetSpO2TimeSignList();
		//移除时间段内的所有血氧启动点
		void RemoveSpO2TimeSigns(const int nMilliterTime);
		//添加血氧启动点，返回加入后的启动时间点
		void AddSpO2SignTime(const long lSpO2BeginTime, const long lCycleTime);
		void AddSpO2SignTimeToExtrasyst(long lSpO2BeginTime, long lPreSpO2BeginTime, long lCycleTime);
		/*******************************************************************************/
		// 函数名称： JudgeSpO2Sign
		// 功能： 根据心脏搏动情况，判断及启动血氧的信号和心脏跳动启动的信号
		// 参数： int  iMilliTime:        时间（0.1豪秒）
		//        int &nRtnMilliTime:     
		// 返回值:  0:无信号；1:心脏跳动启动；2:血氧的信号启动
		int  JudgeSpO2Sign(int  iMilliTime, int &nRtnMilliTime, int &nCycleMilliTime);
	};

}}