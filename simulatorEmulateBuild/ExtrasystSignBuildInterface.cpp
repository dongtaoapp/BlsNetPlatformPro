#include <ctime>
#include <boost/random.hpp>
#include ".\extrasystsignbuildinterface.h"


using namespace boost::random;
namespace jysoft { namespace simulator { namespace ecg {

	CExtrasystSignBuildInterface::CExtrasystSignBuildInterface(void)
	{
		for(int i =0; i< 60; ++i)
			m_nSigns[i] = 0;
		m_nCurrentTime = 0;
		m_nExtrasystRate = 0;
	}

	CExtrasystSignBuildInterface::~CExtrasystSignBuildInterface(void)
	{
	}

	//修改早搏产生的数率
	void  CExtrasystSignBuildInterface::ModifyExtrasystRate(int  nExtrasystRate)
	{
		if( nExtrasystRate >= 20 )
		{
			nExtrasystRate = 20;
		}
		else if( nExtrasystRate <= 0)
		{
			nExtrasystRate = 0;
		}
		m_cMutex.Lock();
		m_nExtrasystRate = nExtrasystRate;
		m_nCurrentTime   = 0;
		m_cMutex.Unlock();
		RandonExtrasystSignBuildTime( nExtrasystRate );
	}

	//返回是否要产生早搏（单位：0.1毫秒）
	bool  CExtrasystSignBuildInterface::AddMilliterTime( int iMilliTime )
	{
		bool bHave = false;
		m_nCurrentTime += iMilliTime;
		int nCurrItem = m_nCurrentTime/10000;
		if( nCurrItem > 59 )
		{
			RandonExtrasystSignBuildTime(m_nExtrasystRate);
			m_nCurrentTime = 0;
		}
		else
		{
			if( m_nSigns[nCurrItem] > 0 )
			{
				m_nSigns[nCurrItem] = 0;
				bHave = true;
			}
		}
		return bHave;
	}

	void CExtrasystSignBuildInterface::RandonExtrasystSignBuildTime(int nExtrasystRate)
	{
		m_cMutex.Lock();
		for(int i =0; i< 60; ++i)
			m_nSigns[i] = 0;
		if( nExtrasystRate != 0)
		{
			variate_generator<mt19937, uniform_smallint<>> gen(mt19937((int32_t)std::time(0)), uniform_smallint<>(0,60));
			srand( (unsigned)time( NULL ) );
			for(; nExtrasystRate > 0; --nExtrasystRate)
			{
				int nSel = gen();
				if( nSel != 60 && m_nSigns[nSel] == 0 )
				{
					m_nSigns[nSel] = 1;
					break;
				}
			}
		}
		m_cMutex.Unlock();
	}
}}}
