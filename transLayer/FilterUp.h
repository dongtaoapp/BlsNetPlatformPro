#pragma once
#include <list>
#include ".\VirtualCommunicate.h"

#include "..\Common\VirtualIrp.h"
#include "..\common\criticalmutex.h"


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
		//�ϴ�����Case����
		void TranslateUpIrpNoNetwork( irp::CVirtualIrp * pUpIrp );
	public:
		//������CFilterUp��ͨ��ͨ����·
        void SetFilterUpLinkCommunicates(CVirtualCommunicate *pUpCommunicates[], short uNumber, bool bRmvCurCommunicates = true);
		void RmvFilterUpLinkCommunicate(CVirtualCommunicate *pUpCommunicate);
	protected:
        utility::CCriticalMutex   m_cUpMutex;
        CFormatTransport*         m_pFormatTransport;
		//����λ��ͨѶ���б�
		std::list<CVirtualCommunicate *> m_lstUpCommunicates;
	};
}}
