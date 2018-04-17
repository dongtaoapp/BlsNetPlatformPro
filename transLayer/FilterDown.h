#pragma once
#include <list>
#include <string>
#include <boost/thread.hpp>
#include ".\VirtualCommunicate.h"

#include "..\Common\VirtualIrp.h"

namespace jysoft { namespace transLayer 
{
	class CFilterDown
	{
	public:
		CFilterDown();
		virtual ~CFilterDown(void);
	public:
		void TransportIrp(CVirtualCommunicate *pSrcCommunicate, irp::CVirtualIrp * pIrp);
		//设置与CFilterDown连通的通信链路
		void SetFilterDownLinkCommunicates(CVirtualCommunicate *pDownCommunicates[], short uNumber, bool bRmvCurCommunicates = true);
		void RmvFilterDownLinkCommunicates(CVirtualCommunicate *pDownCommunicates[], short uNumber);
	protected:
		boost::mutex     muCommunicate;
		//向下位机通讯的列表
		std::list<CVirtualCommunicate *> m_lstCommunicates;
	};
}}