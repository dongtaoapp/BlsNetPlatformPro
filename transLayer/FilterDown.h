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
		{//向下传的数据结构
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
		//设置与CFilterDown连通的通信链路
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
		HANDLE        m_hHaveTransIrp;//有Irp需要传输句柄
		HANDLE        m_hThreadOut;   //要求退出线程
		HANDLE        m_hLogout;      //线程已退出句柄
        utility::CCriticalMutex        m_cDownMutex;
        utility::CCriticalMutex        m_cTransMutex;
		//向下位机通讯的列表
		std::list<CVirtualCommunicate *> m_lstCommunicates;
	};
}}
