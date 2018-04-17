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
		//������CFilterDown��ͨ��ͨ����·
		void SetFilterDownLinkCommunicates(CVirtualCommunicate *pDownCommunicates[], short uNumber, bool bRmvCurCommunicates = true);
		void RmvFilterDownLinkCommunicates(CVirtualCommunicate *pDownCommunicates[], short uNumber);
	protected:
		boost::mutex     muCommunicate;
		//����λ��ͨѶ���б�
		std::list<CVirtualCommunicate *> m_lstCommunicates;
	};
}}