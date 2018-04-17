#include <boost/foreach.hpp>
#include ".\spo2signbuildinterface.h"


using namespace std;
using namespace boost;
namespace jysoft { namespace simulator { 

	CSpO2SignBuildInterface::CSpO2SignBuildInterface(void)
	{
	}

	CSpO2SignBuildInterface::~CSpO2SignBuildInterface(void)
	{
		BOOST_FOREACH(auto x, m_lstSpO2BeginTime)
		{
			delete x;
		}
		m_lstSpO2BeginTime.clear();
	}

	//重置时间链表
	void CSpO2SignBuildInterface::ResetSpO2TimeSignList()
	{
		m_cHandleSpO2SignMap.Lock();
		BOOST_FOREACH(auto x, m_lstSpO2BeginTime)
		{
			delete x;
		}
		m_lstSpO2BeginTime.clear();
		m_cHandleSpO2SignMap.Unlock();
	}

	//移除时间段内的所有血氧启动点
	void CSpO2SignBuildInterface::RemoveSpO2TimeSigns(const int nMilliterTime)
	{
		m_cHandleSpO2SignMap.Lock();
		list<_SpO2SignStruct *>::iterator  iter;
		iter = m_lstSpO2BeginTime.begin();
		while( iter != m_lstSpO2BeginTime.end() )
		{
			_SpO2SignStruct *pSpO2SignStruct = *iter;
			if( pSpO2SignStruct->m_nSpO2BeginTime < nMilliterTime )
			{
				pSpO2SignStruct->m_nSpO2BeginTime = -1;
				if(pSpO2SignStruct->m_nCycleTime <= nMilliterTime)
				{
					m_lstSpO2BeginTime.erase( iter++ );
					delete pSpO2SignStruct;
				}
			}
			else
				break;
		}
		m_cHandleSpO2SignMap.Unlock();
	}

	//添加血氧启动点
	void CSpO2SignBuildInterface::AddSpO2SignTime(const long lSpO2BeginTime, const long lCycleTime)
	{
		long nTime = lSpO2BeginTime;
		m_cHandleSpO2SignMap.Lock();
		_SpO2SignStruct *pNewSpO2Sign = new _SpO2SignStruct;
		pNewSpO2Sign->m_nCycleTime = (int)lCycleTime;
		pNewSpO2Sign->m_nSpO2BeginTime = (int)lSpO2BeginTime;
		//末尾启动点
		list<_SpO2SignStruct *>::reverse_iterator re_iter;
		re_iter = m_lstSpO2BeginTime.rbegin();
		if( re_iter != m_lstSpO2BeginTime.rend() )
		{
			_SpO2SignStruct *pSpO2SignStruct = *re_iter;
			if( pSpO2SignStruct->m_nCycleTime > 0 )
			{
				pNewSpO2Sign->m_nSpO2BeginTime += pSpO2SignStruct->m_nCycleTime;
				pNewSpO2Sign->m_nCycleTime     += pSpO2SignStruct->m_nCycleTime;
			}
		}
		m_lstSpO2BeginTime.push_back( pNewSpO2Sign );
		m_cHandleSpO2SignMap.Unlock();
	}

	void CSpO2SignBuildInterface::AddSpO2SignTimeToExtrasyst(long lSpO2BeginTime, long lPreSpO2BeginTime, long lCycleTime)
	{
		m_cHandleSpO2SignMap.Lock();
		_SpO2SignStruct *pNewSpO2Sign = new _SpO2SignStruct;
		pNewSpO2Sign->m_nCycleTime = (int)lCycleTime;
		pNewSpO2Sign->m_nSpO2BeginTime = (int)lSpO2BeginTime;
		if(m_lstSpO2BeginTime.size() > 0)
		{
			list<_SpO2SignStruct *>::reverse_iterator re_iter;
			re_iter = m_lstSpO2BeginTime.rbegin();
			_SpO2SignStruct *pPreSpO2Sign = *re_iter;
			pNewSpO2Sign->m_nSpO2BeginTime += (pPreSpO2Sign->m_nSpO2BeginTime - lPreSpO2BeginTime);
			pNewSpO2Sign->m_nCycleTime     += (pPreSpO2Sign->m_nSpO2BeginTime - lPreSpO2BeginTime);
		}
		m_lstSpO2BeginTime.push_back( pNewSpO2Sign );
		m_cHandleSpO2SignMap.Unlock();
	}   

	/*******************************************************************************/
	// 函数名称： JudgeSpO2Sign
	// 功能： 根据心脏搏动情况，判断及启动血氧的信号和心脏跳动启动的信号
	// 参数： int  iMilliTime:        时间（0.1豪秒）
	//        int &nRtnMilliTime:     
	// 返回值:  0:无信号；0x01:心脏跳动启动；0x02:血氧的信号启动；0x03:两者都启动
	int  CSpO2SignBuildInterface::JudgeSpO2Sign(int  iMilliTime, int &nRtnMilliTime, int &nCycleMilliTime)
	{
		int  nSignState    = 0;
		m_cHandleSpO2SignMap.Lock();
		int nCount = m_lstSpO2BeginTime.size();
		for(int i = 0; i < nCount; ++i)
		{
			list<_SpO2SignStruct *>::iterator  iter;
			iter = m_lstSpO2BeginTime.begin();
			_SpO2SignStruct *pSpO2SignPtr = *iter;
			if( pSpO2SignPtr->m_nSpO2BeginTime > 0 && (pSpO2SignPtr->m_nSpO2BeginTime<(iMilliTime*4/3) || pSpO2SignPtr->m_nSpO2BeginTime <= iMilliTime ))
			{
				//血氧信号启动
				nSignState = 0x02;   
				nRtnMilliTime = pSpO2SignPtr->m_nSpO2BeginTime;
				nCycleMilliTime = pSpO2SignPtr->m_nCycleTime;
			}
			pSpO2SignPtr->m_nSpO2BeginTime -= iMilliTime;
			pSpO2SignPtr->m_nCycleTime     -= iMilliTime;
			if( pSpO2SignPtr->m_nCycleTime <= 0 )
			{
				//心脏跳动启动
				delete pSpO2SignPtr;
				nSignState   |=  0x01;
			}
			else
			{
				m_lstSpO2BeginTime.push_back( pSpO2SignPtr );
			}
			m_lstSpO2BeginTime.erase( iter );
		}
		m_cHandleSpO2SignMap.Unlock();
		return nSignState;
	}
}}
