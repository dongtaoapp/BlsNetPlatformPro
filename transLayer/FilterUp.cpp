#include <algorithm>
#include <boost/foreach.hpp>
#include ".\filterup.h"
#include ".\FormatTransport.h"


namespace jysoft { namespace transLayer {
	CFilterUp::CFilterUp(CFormatTransport *pFormatTransport)
	{
		m_pFormatTransport = pFormatTransport;
	}

	CFilterUp::~CFilterUp(void)
	{
	}

	void CFilterUp::TransportIrp(irp::CVirtualIrp * pIrp)
	{
		//�����ͨ����·��Ҳ����
		boost::mutex::scoped_lock  lock( muUpLink );
		BOOST_FOREACH(CVirtualCommunicate * pVirComm, m_lstUpCommunicates)
		{
			pVirComm->TransDownData(pIrp);
		}
		//���ϴ���IRP
		m_pFormatTransport->AddUpIrpToList(pIrp);
	}

	//�ϴ�����Case����
	void CFilterUp::TranslateUpIrpNoNetwork( irp::CVirtualIrp * pUpIrp )
	{
		//���ϴ���IRP
		m_pFormatTransport->AddUpIrpToList(pUpIrp);
	}

	//������CFilterUp��ͨ��ͨ����·
	void CFilterUp::SetFilterUpLinkCommunicates(CVirtualCommunicate *pUpCommunicates[], short uNumber, bool bRmvCurCommunicates /*= true*/)
	{
		boost::mutex::scoped_lock  lock( muUpLink );
		if(bRmvCurCommunicates == true)
		{
			m_lstUpCommunicates.clear();
		}
		for(short i=0;i<uNumber;++i)
		{
			m_lstUpCommunicates.push_back(pUpCommunicates[i]);
		}
	}

	void CFilterUp::RmvFilterUpLinkCommunicate(CVirtualCommunicate *pUpCommunicate)
	{
		boost::mutex::scoped_lock  lock( muUpLink );
		std::remove(m_lstUpCommunicates.begin(), m_lstUpCommunicates.end(), pUpCommunicate);
	}
}}
