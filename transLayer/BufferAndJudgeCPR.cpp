#include <algorithm>
#include <boost/foreach.hpp>
#include <boost/bind.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/utility/binary.hpp>
#include <boost/algorithm/string.hpp>
#include ".\BufferAndJudgeCPR.h"
#include ".\VirtualCommunicate.h"

#include "..\common\ParseCPRData_Singleton.h"


using namespace boost;
namespace jysoft { namespace transLayer 
{
	CBufferAndJudgeCPR::CBufferAndJudgeCPR(CVirtualCommunicate *pCommCommunicate)
	{
		m_pCommCommunicate = pCommCommunicate;
		m_iDelayTime = 0;
		m_uBuffTimeEvent = 0;
		m_uStartCPR  = 0;
		//-----------------------------------------------------------------------
		m_iEqualTime = 0;
	}

	CBufferAndJudgeCPR::~CBufferAndJudgeCPR(void)
	{
		BOOST_FOREACH( auto x, m_lstTimeEvents )
		{
			delete x;
		}
		m_lstTimeEvents.clear();
	}

	//加入新的CPR数据
	void  CBufferAndJudgeCPR::loadCPRNewData(const _CPRData &cprValue)
	{
		const cpr::CParseCPRData_Singleton &cCPRParse = cpr::CParseCPRData_Singleton::get_const_instance();
		if( cCPRParse.isCPRRealTimeSampleData( cprValue ) )
		{
			tuple<int, bool> tuData = cCPRParse.isCPRRealTimeSampleData(cprValue, true) ? cCPRParse.getPressureSample( cprValue ) : cCPRParse.getBreathSample( cprValue );
			if( tuData.get<0>() > 0 || tuData.get<1>() )
			{
				if(m_uBuffTimeEvent == 0 && m_uStartCPR == 0 && isEqualCPRData(m_dwCPRData, cprValue))
					return;
				m_iDelayTime = 0;
			}
			else if(m_uBuffTimeEvent == 0 && m_uStartCPR == 0)
			{
				return;
			}
			if(isEqualCPRData(m_dwCPRData, cprValue) )
			{
				++m_iEqualTime;
			}
			else
			{
				m_dwCPRData = cprValue;
				m_iEqualTime = 0;
			}
		}
		{
			boost::mutex::scoped_lock  lock(muBufferData);
			m_cLoopBuff.push_back(cprValue);
		}

		if(m_uStartCPR == 0 && m_uBuffTimeEvent == 0)
		{
			m_uBuffTimeEvent = setTimer(2,300);
		}
	}

	//过了nTime时间后触发此函数
	void  CBufferAndJudgeCPR::lapseTimerHandle(int nTime)
	{
		muTimeEvent.lock();
		BOOST_FOREACH( auto pTimeEvent, m_lstTimeEvents )
		{
			pTimeEvent->m_nRemainTime -= nTime;
		}
		muTimeEvent.unlock();
		std::list<_TimeEventStruct *>::iterator pos = m_lstTimeEvents.begin();
		for( ; pos != m_lstTimeEvents.end(); ++pos)
		{
			_TimeEventStruct *pTimeEvent = *pos;
			if(pTimeEvent->m_nRemainTime <= 0)
			{
				pTimeEvent->m_nRemainTime = pTimeEvent->m_nSrcTime;
				OnTimer(pTimeEvent->m_uIDEvent);
				break;
			}
		}
	}

	void  CBufferAndJudgeCPR::OnTimer(_short nIDEvent)
	{
		const cpr::CParseCPRData_Singleton &cCPRParse = cpr::CParseCPRData_Singleton::get_const_instance();
		if(nIDEvent == 1)
		{//缓冲数据小于6个，每次传一个数据；缓冲数据大于6个小于10个，每次传两个数据；缓冲数据大于10个，每次传三个数据
			++m_iDelayTime;
			int i = 1;
			if(m_cLoopBuff.size() > 12 || m_cLoopBuff.size() < 20)
				i = 2;
			else if(m_cLoopBuff.size() >= 20)
				i = 3;
			for(;i>0;--i)
			{
				while(1)
				{
					_CPRData cCPRData[2];;
					int dwActiveSize = 1;
					muBufferData.lock();
					if(m_cLoopBuff.size() == 0)
						dwActiveSize = 0;
					else
					{
						cCPRData[0] = *m_cLoopBuff.begin();
						m_cLoopBuff.pop_front();
						if(m_cLoopBuff.size() != 0)
						{
							cCPRData[1] = *m_cLoopBuff.begin();
							m_cLoopBuff.pop_front();
							dwActiveSize = 2;
						}
					}
					muBufferData.unlock();
					if((m_iDelayTime >= 70 || m_iEqualTime >= 70)&& m_uStartCPR != 0)
					{
						//CPR结束
						m_pCommCommunicate->TransUpCPRStopOrder();
						killTimer(m_uStartCPR);
						m_uStartCPR = 0;
						m_iEqualTime = 0; 
						//插入CPR结束
						cCPRData[0] = cCPRParse.createCPRPhaseData(false);
						dwActiveSize = 1;
					}
					if(dwActiveSize != 0)
					{
						//发送数据
						m_pCommCommunicate->TransUpCPRDataFromBuffer( cCPRData, dwActiveSize );
						break;
					}
					else
					{
						i = 0;
						break;
					}
				}
			}
		}
		if(nIDEvent == 2)
		{//缓冲计数器
			killTimer(m_uBuffTimeEvent);
			m_uBuffTimeEvent = 0;
			m_iDelayTime = 0;//设置Delay计数器为0
			m_uStartCPR = setTimer(1,100);
			//CPR开始
			m_pCommCommunicate->TransUpCPRStartOrder();
			_CPRData cCPRData[1];
			cCPRData[0] = cCPRParse.createCPRPhaseData(true);
			//开始发送
			m_pCommCommunicate->TransUpCPRDataFromBuffer(cCPRData, 1);
		}
	}

	_short  CBufferAndJudgeCPR::setTimer(_short uIDEvent, int nTime)
	{
		boost::mutex::scoped_lock  lock(muTimeEvent);
		_TimeEventStruct *pNewTimeEvent  = new _TimeEventStruct(uIDEvent, nTime);
		m_lstTimeEvents.push_back(pNewTimeEvent);
		return uIDEvent;
	}

	//删除时间事件
	void  CBufferAndJudgeCPR::killTimer(_short nIDEvent)
	{
		boost::mutex::scoped_lock  lock(muTimeEvent);
		std::list<_TimeEventStruct *>::iterator iter;
		iter = find_if(m_lstTimeEvents.begin(), m_lstTimeEvents.end(), bind(&_TimeEventStruct::m_uIDEvent, _1) == nIDEvent);
		if( iter != m_lstTimeEvents.end() )
		{
			delete (*iter);
			m_lstTimeEvents.erase( iter );
		}
	}	

	//重置
	void CBufferAndJudgeCPR::reset()
	{
		killTimer(m_uStartCPR);
		killTimer(m_uBuffTimeEvent);
		m_cLoopBuff.clear();
		m_iDelayTime = 0;
		m_uBuffTimeEvent = 0;
		m_uStartCPR  = 0;
		//-----------------------------------------------------------------------
		m_iEqualTime = 0;
	}

	bool CBufferAndJudgeCPR::isEqualCPRData(const _CPRData &srcCPRValue, const _CPRData &dstCPRValue ) const
	{
		const cpr::CParseCPRData_Singleton &cCPRParse = cpr::CParseCPRData_Singleton::get_const_instance();
		if( cCPRParse.isCPRRealTimeSampleData( dstCPRValue ) )
		{
			tuple<int, bool> tuData = cCPRParse.isCPRRealTimeSampleData(dstCPRValue, true) ? cCPRParse.getPressureSample( dstCPRValue ) : cCPRParse.getBreathSample( dstCPRValue );
			if( srcCPRValue.get<3>() == 0 && tuData.get<0>() == 0 )
			{
				return true;
			}
			else if( srcCPRValue.get<3>() == dstCPRValue.get<3>() )
			{
				if( cCPRParse.isCPRRealTimeSampleData(srcCPRValue, true) && srcCPRValue.get<2>() == tuData.get<0>() )
				{
					return true;
				}
				else if( cCPRParse.isCPRRealTimeSampleData(srcCPRValue, false) && srcCPRValue.get<0>() == tuData.get<0>() )
				{
					return true;
				}
			}
			return false;
		}
		return false;
	}
}}
