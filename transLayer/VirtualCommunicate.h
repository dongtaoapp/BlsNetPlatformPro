#pragma once
#include ".\translayer_global.h"

#include "..\common\VirtualIrp.h"

namespace jysoft { namespace transLayer 
{
	class CFilterUp;
    class TRANSLAYERSHARED_EXPORT CVirtualCommunicate
	{
	public:
		CVirtualCommunicate(void);
		virtual ~CVirtualCommunicate(void);
	protected:
		CFilterUp        *m_pFilterUpPtr;
	public:
		inline void SetFilterUpPtr(CFilterUp *pFilterUp) { m_pFilterUpPtr = pFilterUp;};
		// ��ʼ��ͨ�Žӿڣ�ʹ�����������շ�����
		virtual bool InitializeCommunicate(void) = 0;
		//�����ݴ�����λ��
		virtual void TransDownData(irp::CVirtualIrp * pDownIrp) = 0;
		//���ݴ���������
        virtual void TransUpData(void *lpData, short uNumber) = 0 ;
	public:
		//����CPR����
		virtual void TransUpCPRDataFromBuffer(const _CPRData *ptrdwCPRData, int nLength) = 0;
		//�ϴ�CPR��ʼ����
		virtual void TransUpCPRStartOrder() = 0;
		//�ϴ�CPR��������
		virtual void TransUpCPRStopOrder() = 0; 
	};
}}
