#include <algorithm>
#include <Windows.h>
#include <boost/foreach.hpp>
#include <boost/assert.hpp>
#include ".\filterdown.h"


using namespace jysoft::irp;
namespace jysoft { namespace transLayer 
{
	//=============================================================================================================================
	//线程函数
	UINT WINAPI ThrdFilterDownTransFunc(LPVOID lpVoid)
	{
		CFilterDown *pFilterDown = (CFilterDown *)lpVoid;
		HANDLE  phEvents[3];
		pFilterDown->GetThreadEventHandles(phEvents,3);
		::ResetEvent(phEvents[2]);
		while(1)
		{
            unsigned long dwRtn = ::WaitForMultipleObjects(2,phEvents,false,INFINITE);
			switch(dwRtn)
			{
			case WAIT_OBJECT_0:
				{
					CFilterDown::_TransDownDataStruct *pHandleData = pFilterDown->RmvHeadTransDownData();
					if( pHandleData != NULL && pHandleData->m_pIrpPtr != NULL)
					{
						pFilterDown->TransportIrp(pHandleData);
					}
					break;
				}
			case WAIT_OBJECT_0 + 1:
				{
					::SetEvent(phEvents[2]);
					return 0;
				}
			}
		}
		return 0;
	}

	//-----------------------------------------------------------------------------------------------------------------------------
	CFilterDown::_TransDownDataStruct::_TransDownDataStruct(CVirtualCommunicate *pSrcCommunicate, CVirtualIrp *pIrp)
	{
		m_pSrcCommunicate = pSrcCommunicate;
		m_pIrpPtr         = pIrp;
	}
	CFilterDown::_TransDownDataStruct::~_TransDownDataStruct()
	{
		delete m_pIrpPtr;
		m_pIrpPtr = NULL;
	}
	//---------------------------------------------------------------------------------------------------------------------------
	CFilterDown::CFilterDown()
	{
		m_hHaveTransIrp = ::CreateEvent(NULL,true,false,NULL);
		m_hThreadOut    = NULL;
		m_hLogout       = NULL;
	}

	CFilterDown::~CFilterDown(void)
	{
		if( m_hThreadOut != NULL && m_hLogout != NULL )
		{
			::SetEvent(m_hThreadOut);
			::WaitForSingleObject(m_hLogout,INFINITE);
			CloseHandle(m_hThreadOut);
			CloseHandle(m_hLogout);
		}
	
        ::CloseHandle(m_hHaveTransIrp);
		m_lstCommunicates.clear();
        foreach(auto x, m_lstTransDatas)
		{
			delete x;
		}
		m_lstTransDatas.clear();
	}

	void CFilterDown::StartFilterDownTransFuncThread()
	{
		m_hThreadOut    = ::CreateEvent(NULL,true,false,NULL);
		m_hLogout       = ::CreateEvent(NULL,true,false,NULL);
		//=======创建线程==============
		::AfxBeginThread((AFX_THREADPROC)ThrdFilterDownTransFunc,(LPVOID)this,THREAD_PRIORITY_ABOVE_NORMAL);
	}

	void CFilterDown::TransportIrp(CVirtualCommunicate *pSrcCommunicate, CVirtualIrp * pIrp)
	{
		AddNewTransDownData(pSrcCommunicate, pIrp);

	}
	//设置与CFilterDown连通的通信链路
    void CFilterDown::SetFilterDownLinkCommunicates(CVirtualCommunicate *pDownCommunicates[], short uNumber, bool bRmvCurCommunicates /*= true*/)
	{
		m_cDownMutex.Lock();
		if(bRmvCurCommunicates == true)
		{//移除现有的所有发送数据方式
			m_lstCommunicates.clear();
		}
		for(UINT i = 0;i<uNumber; ++i)
		{
			m_lstCommunicates.push_back(pDownCommunicates[i]);
		}
		m_cDownMutex.Unlock();
	}

    void CFilterDown::RmvFilterDownLinkCommunicates(CVirtualCommunicate *pDownCommunicates[], short uNumber)
	{
		m_cDownMutex.Lock();
		for(UINT i = 0;i<uNumber; ++i)
		{
			std::list<CVirtualCommunicate *>::iterator pos = std::find(m_lstCommunicates.begin(), m_lstCommunicates.end(), pDownCommunicates[i]);
			if( pos != m_lstCommunicates.end() )
			{
				m_lstCommunicates.erase( pos );
			}
		}
		m_cDownMutex.Unlock();
	}

	void CFilterDown::GetThreadEventHandles(HANDLE *lptrHandles, int nNum)
	{
        BOOST_ASSERT(nNum == 3);
		lptrHandles[0] = m_hHaveTransIrp;
		lptrHandles[1] = m_hThreadOut;
		lptrHandles[2] = m_hLogout;
	}

	void CFilterDown::AddNewTransDownData(CVirtualCommunicate *pSrcCommunicate, CVirtualIrp * pIrp)
	{
		_TransDownDataStruct *pNewStruct = new _TransDownDataStruct(pSrcCommunicate, pIrp);
		m_cTransMutex.Lock();
		m_lstTransDatas.push_back(pNewStruct);
		m_cTransMutex.Unlock();
		::SetEvent(m_hHaveTransIrp);
	}

	CFilterDown::_TransDownDataStruct * CFilterDown::RmvHeadTransDownData()
	{
		_TransDownDataStruct *pRtnData = NULL;
		m_cTransMutex.Lock();
		std::list<_TransDownDataStruct *>::iterator iter;
		iter = m_lstTransDatas.begin();
		if( iter == m_lstTransDatas.end() )
		{
			::ResetEvent(m_hHaveTransIrp);
		}
		else
		{
			pRtnData = *iter;
			m_lstTransDatas.pop_front();
			if(m_lstTransDatas.size() == 0)
			{
				::ResetEvent(m_hHaveTransIrp);
			}
		}
		m_cTransMutex.Unlock();
		return pRtnData;
	}

	void CFilterDown::TransportIrp(_TransDownDataStruct *pTransDownDataPtr)
	{
		m_cDownMutex.Lock();
        foreach(auto pVirCommunicate, m_lstCommunicates)
		{
			if(pVirCommunicate != pTransDownDataPtr->m_pSrcCommunicate)
				pVirCommunicate->TransDownData(pTransDownDataPtr->m_pIrpPtr);
		}
		m_cDownMutex.Unlock();
		delete pTransDownDataPtr;
	}
}}
