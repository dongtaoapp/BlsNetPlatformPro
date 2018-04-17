#pragma once
#include <list>
#include <boost/thread.hpp>
#include ".\VirtualCommunicate.h"

#include "..\Common\VirtualIrp.h"


namespace jysoft { namespace transLayer 
{
	class CFormatTransport;
	class  CFilterUp
	{
	public:
		CFilterUp(CFormatTransport *pFormatTransport);
		virtual ~CFilterUp(void);
	public:
		void TransportIrp(irp::CVirtualIrp * pIrp);
		//上传本地Case处理
		void TranslateUpIrpNoNetwork( irp::CVirtualIrp * pUpIrp );
	public:
		//设置与CFilterUp连通的通信链路
		void SetFilterUpLinkCommunicates(CVirtualCommunicate *pUpCommunicates[], short uNumber, bool bRmvCurCommunicates = true);
		void RmvFilterUpLinkCommunicate(CVirtualCommunicate *pUpCommunicate);
	protected:
		boost::mutex   muUpLink;
		CFormatTransport  *m_pFormatTransport;
		//向上位机通讯的列表
		std::list<CVirtualCommunicate *> m_lstUpCommunicates;
	};
}}