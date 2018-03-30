#pragma once
#include <list>
#include <string>
#include ".\VirtualCommunicate.h"

#include "..\common\VirtualIrp.h"
#include "..\common\criticalmutex.h"

namespace jysoft { namespace transLayer 
{
	class CFilterDown
	{
	public:
		struct _TransDownDataStruct
		{//���´������ݽṹ
		public:
			CVirtualCommunicate *m_pSrcCommunicate;
			irp::CVirtualIrp         *m_pIrpPtr;
		public:
			_TransDownDataStruct(CVirtualCommunicate *pSrcCommunicate, irp::CVirtualIrp *pIrp);
			~_TransDownDataStruct();
		};
	public:
		CFilterDown();
		virtual ~CFilterDown(void);
	public:
		void StartFilterDownTransFuncThread();
		void TransportIrp(CVirtualCommunicate *pSrcCommunicate, irp::CVirtualIrp * pIrp);
		//������CFilterDown��ͨ��ͨ����·
        void SetFilterDownLinkCommunicates(CVirtualCommunicate *pDownCommunicates[], short uNumber, bool bRmvCurCommunicates = true);
        void RmvFilterDownLinkCommunicates(CVirtualCommunicate *pDownCommunicates[], short uNumber);
		void GetThreadEventHandles(HANDLE *lptrHandles, int nNum);
	protected:
		std::list<_TransDownDataStruct *> m_lstTransDatas;
	public:
		void AddNewTransDownData(CVirtualCommunicate *pSrcCommunicate, irp::CVirtualIrp * pIrp);
		_TransDownDataStruct * RmvHeadTransDownData();
		void TransportIrp(_TransDownDataStruct *pTransDownDataPtr);
	protected:
		HANDLE        m_hHaveTransIrp;//��Irp��Ҫ������
		HANDLE        m_hThreadOut;   //Ҫ���˳��߳�
		HANDLE        m_hLogout;      //�߳����˳����
        utility::CCriticalMutex        m_cDownMutex;
        utility::CCriticalMutex        m_cTransMutex;
		//����λ��ͨѶ���б�
		std::list<CVirtualCommunicate *> m_lstCommunicates;
	};
}}
