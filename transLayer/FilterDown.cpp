#include <algorithm>
#include <boost/foreach.hpp>
#include ".\filterdown.h"


using namespace jysoft::irp;
namespace jysoft { namespace transLayer 
{
	CFilterDown::CFilterDown()
	{
	}

	CFilterDown::~CFilterDown(void)
	{
		m_lstCommunicates.clear();
	}

	void CFilterDown::TransportIrp(CVirtualCommunicate *pSrcCommunicate, CVirtualIrp * pIrp)
	{
		boost::mutex::scoped_lock  lock(muCommunicate);
		BOOST_FOREACH(auto pVirCommunicate, m_lstCommunicates)
		{
			if(pVirCommunicate != pSrcCommunicate && pIrp != NULL)
				pVirCommunicate->TransDownData(pIrp);
		}
	}
	//设置与CFilterDown连通的通信链路
	void CFilterDown::SetFilterDownLinkCommunicates(CVirtualCommunicate *pDownCommunicates[], short uNumber, bool bRmvCurCommunicates /*= true*/)
	{
		boost::mutex::scoped_lock  lock(muCommunicate);
		if(bRmvCurCommunicates == true)
		{//移除现有的所有发送数据方式
			m_lstCommunicates.clear();
		}
		for(short i = 0;i<uNumber; ++i)
		{
			m_lstCommunicates.push_back(pDownCommunicates[i]);
		}
	}

	void CFilterDown::RmvFilterDownLinkCommunicates(CVirtualCommunicate *pDownCommunicates[], short uNumber)
	{
		boost::mutex::scoped_lock  lock(muCommunicate);
		for(short i = 0;i<uNumber; ++i)
		{
			std::list<CVirtualCommunicate *>::iterator pos = std::find(m_lstCommunicates.begin(), m_lstCommunicates.end(), pDownCommunicates[i]);
			if( pos != m_lstCommunicates.end() )
			{
				m_lstCommunicates.erase( pos );
			}
		}
	}
}}
