#pragma once
#include <list>
#include <boost/thread.hpp>
#include ".\translayer_global.h"

#include "..\common\CommonGlobal.h"

#define _short     unsigned int

namespace jysoft { namespace transLayer 
{
	//����CPR���ݲ��ж�CPR�Ŀ�ʼ�ͽ���
	class CVirtualCommunicate;
    class TRANSLAYERSHARED_EXPORT CBufferAndJudgeCPR
	{
		struct _TimeEventStruct
		{
		public:
			int   m_nSrcTime;
			int   m_nRemainTime;
			_short   m_uIDEvent;
		private:
			bool  m_bValidateEvent;    //�Ƿ�����Ч�ļ�����
		public:
			_TimeEventStruct()
			{
				m_bValidateEvent = true;
				m_uIDEvent  = 0;
				m_nSrcTime = m_nRemainTime = -1;
			};
			_TimeEventStruct(short uIDEvent, int iTime)
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
	public://��Ҫ�ĺ���
		//����nTimeʱ��󴥷��˺���
		void  lapseTimerHandle(int nTime);
		_short  setTimer(_short uIDEvent, int nTime);
		void  OnTimer(_short nIDEvent);
		//ɾ��ʱ���¼�
		void  killTimer(_short nIDEvent);
		//�����µ�CPR����
		void  loadCPRNewData(const _CPRData &cprValue);
		//����
		void  reset();
	protected:
		bool isEqualCPRData(const _CPRData &srcCPRValue, const _CPRData &dstCPRValue ) const;
	protected:
		std::list<_TimeEventStruct *> m_lstTimeEvents;
		int           m_iDelayTime;
		_short          m_uBuffTimeEvent;//����ʱ��
		_short          m_uStartCPR;     //�Ƿ�ʼCPR
		_CPRData      m_dwCPRData;
		int           m_iEqualTime;
		//-----------------------------------------------------------
		CVirtualCommunicate *m_pCommCommunicate;
		std::list<_CPRData>   m_cLoopBuff;
	protected:
		boost::mutex   muBufferData;
		boost::mutex   muTimeEvent;
	};
}}

