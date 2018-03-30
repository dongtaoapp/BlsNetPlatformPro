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
		m_cUpMutex.Lock();
        foreach(CVirtualCommunicate * pVirComm, m_lstUpCommunicates)
		{
			pVirComm->TransDownData(pIrp);
		}
		m_cUpMutex.Unlock();
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
		m_cUpMutex.Lock();
		if(bRmvCurCommunicates == true)
		{
			m_lstUpCommunicates.clear();
		}
        for(short i=0;i<uNumber;++i)
		{
			m_lstUpCommunicates.push_back(pUpCommunicates[i]);
		}
		m_cUpMutex.Unlock();
	}

	void CFilterUp::RmvFilterUpLinkCommunicate(CVirtualCommunicate *pUpCommunicate)
	{
		m_cUpMutex.Lock();
		std::remove(m_lstUpCommunicates.begin(), m_lstUpCommunicates.end(), pUpCommunicate);
		m_cUpMutex.Unlock();
	}
}}
