#pragma once
#include <list>
#include ".\transLayer_global.h"

#include "..\common\CommonGlobal.h"
#include "..\common\criticalMutex.h"

#define _UINT     unsigned int

namespace jysoft { namespace transLayer 
{
	//缓冲CPR数据并判断CPR的开始和结束
	class CVirtualCommunicate;
    class TRANSLAYERSHARED_EXPORT CBufferAndJudgeCPR
	{
		struct _TimeEventStruct
		{
		public:
			int   m_nSrcTime;
			int   m_nRemainTime;
			_UINT   m_uIDEvent;
		private:
			bool  m_bValidateEvent;    //是否是有效的计算器
		public:
			_TimeEventStruct()
			{
				m_bValidateEvent = true;
				m_uIDEvent  = 0;
				m_nSrcTime = m_nRemainTime = -1;
			};
			_TimeEventStruct(UINT uIDEvent, int iTime)
			{
				m_bValidateEvent = true;
				m_uIDEvent = uIDEvent;
				m_nSrcTime = m_nRemainTime = iTime;
			};
		public:
			inline void SetInvalidateTimeEvent() { m_bValidateEvent = false; };
			inline bool IsValidateTimeEvent() { return m_bValidateEvent; };
		};
	public:
		CBufferAndJudgeCPR(CVirtualCommunicate *pCommCommunicate);
		virtual ~CBufferAndJudgeCPR(void);
	public://主要的函数
		//过了nTime时间后触发此函数
		void  lapseTimerHandle(int nTime);
		_UINT  setTimer(_UINT uIDEvent, int nTime);
		void  OnTimer(_UINT nIDEvent);
		//删除时间事件
		void  killTimer(_UINT nIDEvent);
		//加入新的CPR数据
		void  loadCPRNewData(const _CPRData &cprValue);
		//重置
		void  reset();
	protected:
		bool isEqualCPRData(const _CPRData &srcCPRValue, const _CPRData &dstCPRValue ) const;
	protected:
		std::list<_TimeEventStruct *> m_lstTimeEvents;
		int           m_iDelayTime;
		_UINT          m_uBuffTimeEvent;//缓冲时间
		_UINT          m_uStartCPR;     //是否开始CPR
		_CPRData      m_dwCPRData;
		int           m_iEqualTime;
		//-----------------------------------------------------------
		CVirtualCommunicate *m_pCommCommunicate;
		std::list<_CPRData>   m_cLoopBuff;
	protected:
        utility::CCriticalMutex        m_cMutex;
        utility::CCriticalMutex        m_cTimeEventMutex;
	};
}}

