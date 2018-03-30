#include <math.h>
#include <boost/lexical_cast.hpp>
#include <boost/assert.hpp>
#include ".\nettransfervir.h"
#include ".\VirTcpTransferOpGather.h"

namespace jysoft {
namespace network {
//--------------------------------------------------------------------------------------------------------------------------
//
// Function: CompletionThread
// 
// Description:
//    This is the completion thread which services our completion port. One of
//    these threads is created per processor on the system. The thread sits in 
//    an infinite loop calling GetQueuedCompletionStatus and handling socket
//    IO that completed.
//
unsigned long WINAPI CNetTransferVir::CompletionThread(LPVOID lpParam)
{
	NET_SOCKET_OBJ  *sockobj=NULL;          // Per socket object for completed I/O
	NET_BUFFER_OBJ  *bufobj=NULL;           // Per I/O object for completed I/O
	OVERLAPPED      *lpOverlapped=NULL;     // Pointer to overlapped structure for completed I/O
    unsigned long    BytesTransfered,       // Number of bytes transfered
		Flags;                 // Flags for completed I/O
	int             rc, 
		error;

	CNetTransferVir *pTcpTransferPtr = (CNetTransferVir *)lpParam;
	while (1)
	{
		error = NO_ERROR;
		rc = GetQueuedCompletionStatus(
			pTcpTransferPtr->GethCompletionPort(),
			&BytesTransfered,
			(PULONG_PTR)&sockobj,
			&lpOverlapped,
			INFINITE
			);

		if(BytesTransfered == -1) // 用户通知退出
		{
			::ExitThread(0);
		}

		bufobj = CONTAINING_RECORD(lpOverlapped, NET_BUFFER_OBJ, ol);

		if (rc == FALSE)
		{
			SOCKET s;
			if(sockobj != NULL)
				s = sockobj->s;
			else if(bufobj->operation == OP_ACCEPT)
				s = pTcpTransferPtr->Get_ListenHandle();
			else
				s = bufobj->sclient;
            unsigned long dwFlags = 0;
			if(!::WSAGetOverlappedResult(s, &bufobj->ol, &BytesTransfered, FALSE, &Flags))
			{
				error = ::WSAGetLastError();
			}
		}
		try
		{
			if(sockobj != NULL && bufobj )
			{//将套接字句柄复制给NET_BUFFER_OBJ对象，使其相互对应
				bufobj->sclient = sockobj->s;
			}
			// Handle the IO operation
			pTcpTransferPtr->HandleIo(sockobj, bufobj, pTcpTransferPtr->GethCompletionPort(), BytesTransfered, error);
		}
		catch(...)
		{
			;
		}
	}

	return 0;
}
//--------------------------------------------------------------------------------------------------------------------------
CNetTransferVir::CNetTransferVir(bool bSendHeadStruct/*=TRUE*/)
{
	m_bSendHeadStruct = bSendHeadStruct;
	m_nNetProtocol = IPPROTO_TCP;
	m_hCompletionPort = 0;

	m_pDataExchangeTmpBuf[0] = new char[TRANSFERDATAMAXLENGTH+sizeof(TRANSFER_STRUCT_MESS)]; 
	m_pDataExchangeTmpBuf[1] = new char[TRANSFERDATAMAXLENGTH+sizeof(TRANSFER_STRUCT_MESS)];

	::InitializeCriticalSection(&m_FreeBufferListLock);
	::InitializeCriticalSection(&m_NoIntactBufferListLock);
	m_pFreeBufferObjsPtr = NULL;
	m_pNoIntactBufferObjsPtr = NULL;

	// 初始化WS2_32.dll
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2, 2);
	::WSAStartup(sockVersion, &wsaData);

	m_hAllocHeapHandle  = ::HeapCreate(HEAP_NO_SERIALIZE, sizeof(TRANSFER_STRUCT_MESS), 0);
}

CNetTransferVir::~CNetTransferVir(void)
{
	::DeleteCriticalSection(&m_FreeBufferListLock);
	::DeleteCriticalSection(&m_NoIntactBufferListLock);

	//::HeapFree(m_hHeap, HEAP_ZERO_MEMORY, m_pDataExchangeTmpBuf[0]);
	//::HeapFree(m_hHeap, HEAP_ZERO_MEMORY, m_pDataExchangeTmpBuf[1]);
	delete [] m_pDataExchangeTmpBuf[0];
	delete [] m_pDataExchangeTmpBuf[1];

	::HeapDestroy( m_hAllocHeapHandle );

	while(m_pFreeBufferObjsPtr)
	{
		NET_BUFFER_OBJ *pNextBuf = m_pFreeBufferObjsPtr->next;
		::HeapFree(::GetProcessHeap(), 0 , m_pFreeBufferObjsPtr->m_cBuf);
		::HeapFree(::GetProcessHeap(), 0 , m_pFreeBufferObjsPtr);
		m_pFreeBufferObjsPtr = pNextBuf;
	}
	::WSACleanup();	
}

//得到主机的地址
bool CNetTransferVir::GetHostAddrInfo(const char *lpCompterName, DWORD dwPort, int nProtocol, /*out*/struct addrinfo **pptrInfo)
{
	struct addrinfo hints;
	memset(&hints,0,sizeof(hints));
	hints.ai_flags = AI_CANONNAME;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = nProtocol;

    if(getaddrinfo(lpCompterName, boost::lexical_cast<std::string>(dwPort).c_str(), &hints,pptrInfo)!= 0)
	{
		return false;
	}
	return true;
}

//
// Function: GetNewAllocBufferObj
// 
// Description:
//    Allocate a NET_BUFFER_OBJ. Each receive posted allocates one of these. 
//
NET_BUFFER_OBJ * CNetTransferVir::GetNewAllocBufferObj(int buflen)
{
	NET_BUFFER_OBJ *newobj=NULL;

	buflen = buflen > TRANSFERDATAMAXLENGTH ? buflen : TRANSFERDATAMAXLENGTH;
	// Allocate the object
	::EnterCriticalSection(&m_FreeBufferListLock);

	if(m_pFreeBufferObjsPtr != NULL)
	{
		NET_BUFFER_OBJ *pPtrBuff, *pPreBuff;
		pPtrBuff = m_pFreeBufferObjsPtr;
		pPreBuff = NULL;
		while( pPtrBuff )
		{//查找空闲块中分配的内存大于buflen的NET_BUFFER_OBJ
			if(pPtrBuff->m_nAllocBufLen >= buflen)
			{
				if(pPreBuff == NULL)
				{
					m_pFreeBufferObjsPtr = pPtrBuff->next;
				}
				else
				{
					pPreBuff->next = pPtrBuff->next;
				}
				newobj = pPtrBuff;
				break;
			}
			else
			{
				pPreBuff = pPtrBuff;
				pPtrBuff = pPtrBuff->next;
			}
		}
	}

	::LeaveCriticalSection(&m_FreeBufferListLock);

	for(int i =0; i < 3 && newobj == NULL; ++i)
	{
		newobj = (NET_BUFFER_OBJ *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(NET_BUFFER_OBJ));
		if (newobj != NULL)
		{
			// Allocate the buffer
			newobj->m_cBuf = (char *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(BYTE) *buflen);
			if(newobj->m_cBuf != NULL)
			{
				newobj->m_nAllocBufLen = buflen;

				newobj->addrlen = sizeof(newobj->addr);
			}
			else
			{
				::HeapFree(GetProcessHeap(), 0, newobj);
				newobj = NULL;
			}
		}
	}

	newobj->next = NULL;

	return newobj;
}

//
// Function: GetNewAllocBufferObj
// 
// Description:
//    Allocate a NET_BUFFER_OBJ. Each receive posted allocates one of these. 
//    outside allocated buffer
//
NET_BUFFER_OBJ * CNetTransferVir::GetNewAllocBufferObj(char *lpBuff, int nOffset, int nAllocLen, int nCurrDataLen )
{
	NET_BUFFER_OBJ *newobj=NULL;

	// Allocate the object
	newobj = (NET_BUFFER_OBJ *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(NET_BUFFER_OBJ));
	if (newobj != NULL)
	{
		// Allocate the buffer
		newobj->m_cBuf = lpBuff; 
		newobj->m_uOffset = nOffset; //从开始位置偏移多少才为数据的起点
		newobj->m_nAllocBufLen = nAllocLen;
		newobj->m_nCurrDataLen = nCurrDataLen;
		newobj->m_bOutsideAlloc = true;          //缓冲区数据由外部分配

		newobj->addrlen = sizeof(newobj->addr);
	}
	return newobj;
}

// Function: FreeBufferObj
// 
// Description:
//    Free the buffer object. To increase performance, a lookaside list should be
//    implemented to cache NET_BUFFER_OBJ when freed.
//
void CNetTransferVir::FreeBufferObj(NET_BUFFER_OBJ *obj)
{
	if(obj == NULL)
		return ;
	bool bLonginLoof = false;
	m_cMutex.Lock();
	if(obj->m_pIntervalCounterPtr != NULL && *obj->m_pIntervalCounterPtr > 0)
		--(*obj->m_pIntervalCounterPtr);
	if((obj->m_pIntervalCounterPtr != NULL && *obj->m_pIntervalCounterPtr == 0) 
		|| (obj->m_pIntervalCounterPtr == NULL && obj->m_bOutsideAlloc == false))
	{
		bLonginLoof = true;
		delete obj->m_pIntervalCounterPtr;
		obj->m_pIntervalCounterPtr = NULL;
	}
	m_cMutex.Unlock();
	if(obj->m_pStructMessPtr != NULL)
	{
		::HeapFree(m_hAllocHeapHandle, 0, obj->m_pStructMessPtr);
		obj->m_pStructMessPtr = NULL;
	}
	if(bLonginLoof == true)
	{
		::EnterCriticalSection(&m_FreeBufferListLock);
		int nFreeCount = 0;
		NET_BUFFER_OBJ *pBuffPtr = m_pFreeBufferObjsPtr;
		while( pBuffPtr )
		{
			++nFreeCount;
			if(pBuffPtr == obj)
			{
                BOOST_ASSERT(0);
				goto _abnormal;
			}
			pBuffPtr = pBuffPtr->next;
		}
		obj->next = NULL; //防止有回路
		if(nFreeCount <= MAXFREEBUFFERSSUM && obj->m_nAllocBufLen == TRANSFERDATAMAXLENGTH)
		{
			char *pTmpBuff     = obj->m_cBuf;
			int   nTmpAllocNum = obj->m_nAllocBufLen;
			::memset(obj, 0, sizeof(NET_BUFFER_OBJ));
			obj->m_cBuf = pTmpBuff;
			obj->m_nAllocBufLen = nTmpAllocNum;
			if(m_pFreeBufferObjsPtr == NULL)
			{
				m_pFreeBufferObjsPtr = obj;
			}
			else
			{
				obj->next = m_pFreeBufferObjsPtr->next;
				m_pFreeBufferObjsPtr->next = obj;
			}
		}
		else
		{
			::HeapFree(GetProcessHeap(),0,obj->m_cBuf);
			::HeapFree(GetProcessHeap(), 0, obj);
		}
_abnormal:
		::LeaveCriticalSection(&m_FreeBufferListLock);
	}
	else
	{
		HeapFree(GetProcessHeap(), 0, obj);
	}
}

//
// Function: GetNewAllocSockObj
//
// Description:
//    Allocate a socket object and initialize its members. A socket object is
//    allocated for each socket created (either by socket or accept).
//    Again, a lookaside list can be implemented to cache freed SOCKET_OBJ to
//    improve performance.
//
NET_SOCKET_OBJ * CNetTransferVir::GetNewAllocSockObj(SOCKET s, int af)
{
	NET_SOCKET_OBJ  *sockobj=NULL;

	sockobj = (NET_SOCKET_OBJ *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(NET_SOCKET_OBJ));
	if (sockobj != NULL)
	{
		// Initialize the members
		sockobj->s = s;
		sockobj->af = af;

		InitializeCriticalSection(&sockobj->SockCritSec);
	}

	return sockobj;
}

//
// Function: FreeSocketObj
//
// Description:
//    Frees a socket object. If there are outstanding operations, the object
//    is not freed. 
//
bool CNetTransferVir::FreeSocketObj(NET_SOCKET_OBJ *obj)
{
	if(obj == NULL)
		return  true;
	if (obj->OutstandingOps != 0)
	{
		// Still outstanding operations so just return
		return false;
	}
	// Close the socket if it hasn't already been closed
	if (obj->s != INVALID_SOCKET)
	{
		closesocket(obj->s);
		obj->s = INVALID_SOCKET;
	}
	DeleteCriticalSection(&obj->SockCritSec);

	HeapFree(GetProcessHeap(), 0, obj);
	return true;
}

int CNetTransferVir::PostRecv(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *recvobj)
{//注：每次接收数据都将收到一个额外的结构
	WSABUF  wbuf[2];
	DWORD   bytes,
		flags;
	int     rc;

	recvobj->operation = OP_READ;

	for(int i=1; i<=3; ++i)
	{
		wbuf[0].buf = (char *)::HeapAlloc(m_hAllocHeapHandle, HEAP_ZERO_MEMORY, sizeof(TRANSFER_STRUCT_MESS)*i);
		if( wbuf[0].buf != NULL )
		{
			break;
		}
	}
	wbuf[0].len = sizeof(TRANSFER_STRUCT_MESS);
	wbuf[1].buf = recvobj->m_cBuf + recvobj->m_uOffset;
	wbuf[1].len = recvobj->m_nAllocBufLen;

	recvobj->m_pStructMessPtr = (TRANSFER_STRUCT_MESS *)wbuf[0].buf;
    BOOST_ASSERT( recvobj->m_pStructMessPtr != NULL );
	flags = 0;

	EnterCriticalSection(&sock->SockCritSec);

	if (m_nNetProtocol == IPPROTO_TCP)
	{
		rc = WSARecv(
			sock->s,
			wbuf,
			2,
			&bytes,
			&flags,
			&recvobj->ol,
			NULL
			);
	}
	else
	{
		rc = WSARecvFrom(
			sock->s,
			wbuf,
			2,
			&bytes,
			&flags,
			(SOCKADDR *)&sock->m_cRemoteAddr,
			&sock->addrlen,
			&recvobj->ol,
			NULL
			);
	}

	LeaveCriticalSection(&sock->SockCritSec);

	if (rc == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			return SOCKET_ERROR;
		}
	}

	// Increment outstanding overlapped operations
	InterlockedIncrement(&sock->OutstandingOps);
	return NO_ERROR;
}

//
// Function: PostSend
// 
// Description:
//    Post an overlapped send operation on the socket.
//
int CNetTransferVir::PostSend(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *sendobj, TRANSFER_STRUCT_MESS &cAppendMess)
{
	WSABUF  wbuf[2];
	DWORD   bytes;
	int     rc;

	sendobj->operation = OP_WRITE;

	wbuf[0].buf = (char *)::HeapAlloc(m_hAllocHeapHandle,HEAP_ZERO_MEMORY,sizeof(TRANSFER_STRUCT_MESS));
	wbuf[0].len = sizeof(TRANSFER_STRUCT_MESS);
	//设置包含数据区和此结构的总和的大小
	cAppendMess.m_uTranferSumData = USHORT(wbuf[0].len + sendobj->m_nCurrDataLen);

	::memcpy((void *)wbuf[0].buf,(void *)&cAppendMess, wbuf[0].len);

	wbuf[1].buf = sendobj->m_cBuf+sendobj->m_uOffset;
	wbuf[1].len = sendobj->m_nCurrDataLen;

	EnterCriticalSection(&sock->SockCritSec);

	if (m_nNetProtocol == IPPROTO_TCP)
	{
		if( m_bSendHeadStruct == TRUE )
		{
			//发送数据传输时附带相关结构信息 hjg 2011.12 add
			rc = WSASend(
				sock->s,
				wbuf,
				2,
				&bytes,
				0,
				&sendobj->ol,
				NULL
				);
		}
		else
		{
			//发送数据传输时不附带相关结构信息
			rc = WSASend(
				sock->s,
				&wbuf[1],
				1,
				&bytes,
				0,
				&sendobj->ol,
				NULL
				);
		}
	}
	else
	{
		if( m_bSendHeadStruct == TRUE )
		{
			rc = WSASendTo(
				sock->s,
				wbuf,
				2,
				&bytes,
				0,
				(SOCKADDR *)&sock->m_cRemoteAddr,
				sock->addrlen,
				&sendobj->ol,
				NULL
				);
		}
		else
		{
			//发送数据传输时不附带相关结构信息
			rc = WSASendTo(
				sock->s,
				&wbuf[1],
				1,
				&bytes,
				0,
				(SOCKADDR *)&sock->m_cRemoteAddr,
				sock->addrlen,
				&sendobj->ol,
				NULL
				);
		}
	}

	LeaveCriticalSection(&sock->SockCritSec);

	if (rc == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			return SOCKET_ERROR;
		}
	}

	// Increment the outstanding operation count
	InterlockedIncrement(&sock->OutstandingOps);
	return NO_ERROR;
}

NET_BUFFER_OBJ *CNetTransferVir::LoadNoIntactBuff(NET_BUFFER_OBJ **ppRecvObj, /*in,out*/DWORD *pTransferedSumSize)
{//注：(*ppRecvObj)->m_nCurrDataLen的值在此函数中设定
	::EnterCriticalSection(&m_NoIntactBufferListLock);
	NET_BUFFER_OBJ *pPreBuff = NULL;
	NET_BUFFER_OBJ *pSrchBuff = m_pNoIntactBufferObjsPtr;
	while(pSrchBuff)
	{
		if(pSrchBuff->sclient == (*ppRecvObj)->sclient)
		{
			if(pPreBuff == NULL)
			{
				m_pNoIntactBufferObjsPtr = m_pNoIntactBufferObjsPtr->next;
			}
			else
			{
				pPreBuff->next = pSrchBuff->next;
			}
			break;
		}

		pPreBuff = pSrchBuff;
		pSrchBuff = pSrchBuff->next;
	}
	::LeaveCriticalSection(&m_NoIntactBufferListLock);
	//--------------------------------------------------------------------------------------------
	if(pSrchBuff == NULL)
	{
		//标头结构完整，m_nCurrDataLen表示收到的数据长度；否则为接收的数据包长度

		if( *pTransferedSumSize > (*ppRecvObj)->m_pStructMessPtr->m_uTranferSumData )
		{
			(*ppRecvObj)->m_nCurrDataLen = (*ppRecvObj)->m_pStructMessPtr->m_uTranferSumData - sizeof(TRANSFER_STRUCT_MESS);
		}
		else if( *pTransferedSumSize >= sizeof(TRANSFER_STRUCT_MESS) )
		{
			(*ppRecvObj)->m_nCurrDataLen = (*pTransferedSumSize) - sizeof(TRANSFER_STRUCT_MESS);
		}
		else
		{
			(*ppRecvObj)->m_nCurrDataLen = *pTransferedSumSize;
		}
	}
	else
	{
		pSrchBuff->next     = NULL;
		::memset(m_pDataExchangeTmpBuf[0], 0, TRANSFERDATAMAXLENGTH+sizeof(TRANSFER_STRUCT_MESS) );
		::memset(m_pDataExchangeTmpBuf[1], 0, TRANSFERDATAMAXLENGTH+sizeof(TRANSFER_STRUCT_MESS) );
		//----------------------------------------------------------------------------------------------------
		NET_BUFFER_OBJ *pNewBuff = GetNewAllocBufferObj();
		pNewBuff->sclient   =   pSrchBuff->sclient;
		pNewBuff->m_pStructMessPtr = (TRANSFER_STRUCT_MESS *)::HeapAlloc(m_hAllocHeapHandle, HEAP_ZERO_MEMORY, sizeof(TRANSFER_STRUCT_MESS));
		UINT uTmpBufPos[2];
		uTmpBufPos[0] = uTmpBufPos[1] = 0;
		//将两数据包中的所有数据都拷贝到临时缓冲区
		if( pSrchBuff->m_nCurrDataLen <= 0 )
		{
			*pTransferedSumSize = 0;
			*ppRecvObj = NULL;
			return NULL;
		}
		if(pSrchBuff->m_pStructMessPtr == NULL)
		{
			::memcpy(m_pDataExchangeTmpBuf[0],pSrchBuff->m_cBuf+pSrchBuff->m_uOffset,pSrchBuff->m_nCurrDataLen);
			uTmpBufPos[0] = pSrchBuff->m_nCurrDataLen;
		}
		else
		{
			uTmpBufPos[0] = sizeof(TRANSFER_STRUCT_MESS);
			::memcpy(m_pDataExchangeTmpBuf[0], pSrchBuff->m_pStructMessPtr, uTmpBufPos[0]);
			::memcpy(m_pDataExchangeTmpBuf[0]+uTmpBufPos[0], pSrchBuff->m_cBuf+pSrchBuff->m_uOffset, pSrchBuff->m_nCurrDataLen);
			uTmpBufPos[0] += pSrchBuff->m_nCurrDataLen;
		}

		uTmpBufPos[1] = *pTransferedSumSize <= sizeof(TRANSFER_STRUCT_MESS) ? *pTransferedSumSize : sizeof(TRANSFER_STRUCT_MESS);
		::memcpy(m_pDataExchangeTmpBuf[1],(*ppRecvObj)->m_pStructMessPtr,uTmpBufPos[1] );
		if( uTmpBufPos[1] < *pTransferedSumSize )
		{
			::memcpy(m_pDataExchangeTmpBuf[1] + uTmpBufPos[1],  (*ppRecvObj)->m_cBuf+(*ppRecvObj)->m_uOffset, int(*pTransferedSumSize)-int(sizeof(TRANSFER_STRUCT_MESS)) );
		}
		uTmpBufPos[1] = *pTransferedSumSize;
		//-----------------------------------------------------------------------------------------------------------
		UINT uTmpBufPos2 = 0;
		if( (uTmpBufPos[0] + uTmpBufPos[1]) >= sizeof(TRANSFER_STRUCT_MESS) )
		{
			//第二个数据包能满足组建标头格式长度
			if(uTmpBufPos[0] < sizeof(TRANSFER_STRUCT_MESS))
			{
				uTmpBufPos2 = sizeof(TRANSFER_STRUCT_MESS) - uTmpBufPos[0];
				::memcpy(m_pDataExchangeTmpBuf[0]+uTmpBufPos[0], m_pDataExchangeTmpBuf[1], uTmpBufPos2);
				uTmpBufPos[0] = sizeof(TRANSFER_STRUCT_MESS);
			}
			TRANSFER_STRUCT_MESS *pSrcStructMess = (TRANSFER_STRUCT_MESS *)m_pDataExchangeTmpBuf[0];
			if(pSrcStructMess->m_cFlage[0] != 'H' || pSrcStructMess->m_cFlage[1] != 'L')
			{
				*pTransferedSumSize = 0;
				*ppRecvObj = NULL;
				return NULL;
			}
			int nNeedSize = pSrcStructMess->m_uTranferSumData - uTmpBufPos[0];
			if( (*pTransferedSumSize-uTmpBufPos2) < nNeedSize )
			{
				nNeedSize = (*pTransferedSumSize - uTmpBufPos2 );
			}
			::memcpy(m_pDataExchangeTmpBuf[0]+uTmpBufPos[0], m_pDataExchangeTmpBuf[1]+uTmpBufPos2, nNeedSize);
			uTmpBufPos[0] += nNeedSize;
			uTmpBufPos2   += nNeedSize;
			//----------------------------------------------------------------------------------------------
			//修改各值
			::memcpy(pNewBuff->m_pStructMessPtr, m_pDataExchangeTmpBuf[0], sizeof(TRANSFER_STRUCT_MESS) );
			pNewBuff->m_nCurrDataLen = uTmpBufPos[0] - sizeof(TRANSFER_STRUCT_MESS);
			::memcpy(pNewBuff->m_cBuf, m_pDataExchangeTmpBuf[0]+sizeof(TRANSFER_STRUCT_MESS), pNewBuff->m_nCurrDataLen);
			*pTransferedSumSize -= uTmpBufPos2;
			if(*pTransferedSumSize >= sizeof(TRANSFER_STRUCT_MESS))
			{
				::memcpy((*ppRecvObj)->m_pStructMessPtr, m_pDataExchangeTmpBuf[1]+uTmpBufPos2, sizeof(TRANSFER_STRUCT_MESS));
				(*ppRecvObj)->m_nCurrDataLen = *pTransferedSumSize - sizeof(TRANSFER_STRUCT_MESS);
				::memcpy((*ppRecvObj)->m_cBuf, m_pDataExchangeTmpBuf[1]+uTmpBufPos2+sizeof(TRANSFER_STRUCT_MESS), (*ppRecvObj)->m_nCurrDataLen);
			}
			else if( (*pTransferedSumSize) != 0)
			{
				::HeapFree(m_hAllocHeapHandle,0,(*ppRecvObj)->m_pStructMessPtr);
				(*ppRecvObj)->m_pStructMessPtr = NULL;
				(*ppRecvObj)->m_nCurrDataLen = *pTransferedSumSize;
				::memcpy((*ppRecvObj)->m_cBuf,m_pDataExchangeTmpBuf[1]+uTmpBufPos2, (*ppRecvObj)->m_nCurrDataLen);

				::EnterCriticalSection(&m_NoIntactBufferListLock);	
				(*ppRecvObj)->next = m_pNoIntactBufferObjsPtr;
				m_pNoIntactBufferObjsPtr = (*ppRecvObj);
				::LeaveCriticalSection(&m_NoIntactBufferListLock);

				*ppRecvObj = NULL;
			}
			else 
			{
				*pTransferedSumSize = pNewBuff->m_nCurrDataLen + sizeof(TRANSFER_STRUCT_MESS);
				//判断是否是完整的数据包
				if( *pTransferedSumSize == pNewBuff->m_pStructMessPtr->m_uTranferSumData  )
				{
					FreeBufferObj( *ppRecvObj );
					*ppRecvObj = NULL;
				}
				else
				{
					//释放分配的结构
					FreeBufferObj( *ppRecvObj );
					*ppRecvObj = pNewBuff;
					pNewBuff   = NULL;
				}
			}
			//----------------------------------------------------------------------------------------------
			FreeBufferObj(pSrchBuff);
			return pNewBuff;
		}
		else
		{
			*pTransferedSumSize = uTmpBufPos[0]+uTmpBufPos[1];
			::memcpy( m_pDataExchangeTmpBuf[0]+uTmpBufPos[0],m_pDataExchangeTmpBuf[1],uTmpBufPos[1]);
			::memcpy( pNewBuff->m_pStructMessPtr, m_pDataExchangeTmpBuf[0], *pTransferedSumSize );
			pNewBuff->m_nCurrDataLen = *pTransferedSumSize;
			//释放新分配的结构
			FreeBufferObj( *ppRecvObj );
			*ppRecvObj = pNewBuff;
			FreeBufferObj( pSrchBuff );
		}
	}
	return NULL;
}

//divide receive package
//dwTransferedSum: 收到的数据的大小
NET_BUFFER_OBJ * CNetTransferVir::DivideRecvBuffer(NET_BUFFER_OBJ *recvObj, DWORD dwTransferedSum)
{
	NET_BUFFER_OBJ *pRtnBuff = LoadNoIntactBuff(&recvObj, &dwTransferedSum);
	if(pRtnBuff == NULL)
	{
		pRtnBuff = recvObj;
	}
	else
	{
		if(recvObj && recvObj->m_pStructMessPtr->m_uTranferSumData <= dwTransferedSum)
			pRtnBuff->next = recvObj;
	}
	if(recvObj == NULL || recvObj->m_pStructMessPtr == NULL || recvObj->m_pStructMessPtr->m_cFlage[0] != 'H' || recvObj->m_pStructMessPtr->m_cFlage[1] != 'L')
		return pRtnBuff;
	//“recvObj->m_pStructMessPtr->m_uTranferSumData != 0"的判断主要为了隔离标头格式都没传送完
	if(recvObj->m_pStructMessPtr->m_uTranferSumData != 0 && recvObj->m_pStructMessPtr->m_uTranferSumData < dwTransferedSum)
	{
		dwTransferedSum -= sizeof(TRANSFER_STRUCT_MESS);
		recvObj->m_pIntervalCounterPtr = new LONG(1);
		recvObj->m_nCurrDataLen = recvObj->m_pStructMessPtr->m_uTranferSumData - sizeof(TRANSFER_STRUCT_MESS);
		DWORD dwDivideSum  = recvObj->m_nCurrDataLen;
		while((dwDivideSum+sizeof(TRANSFER_STRUCT_MESS)) <= dwTransferedSum)
		{
			TRANSFER_STRUCT_MESS *pStructMess = (TRANSFER_STRUCT_MESS *)::HeapAlloc(m_hAllocHeapHandle, HEAP_ZERO_MEMORY, sizeof(TRANSFER_STRUCT_MESS));
            BOOST_ASSERT(pStructMess != NULL);
			::memcpy((void *)pStructMess, recvObj->m_cBuf+recvObj->m_uOffset+dwDivideSum, sizeof(TRANSFER_STRUCT_MESS));
			//数据完全脱离协议规定，丢弃整个包  hjg 2013\1\11
			if( pStructMess->m_cFlage[0] != 'H' || pStructMess->m_cFlage[1] != 'L' || pStructMess->m_uTranferSumData == 0 )
			{
				::HeapFree(m_hAllocHeapHandle, HEAP_ZERO_MEMORY, pStructMess);
				pStructMess  = NULL;
				return NULL;
			}
			//end hjg modify
			int nCurrDatLength = 0;
			if((pStructMess->m_uTranferSumData + dwDivideSum) > dwTransferedSum)
			{
				nCurrDatLength = (dwTransferedSum - dwDivideSum) - sizeof(TRANSFER_STRUCT_MESS);
			}
			else
			{
				nCurrDatLength = pStructMess->m_uTranferSumData - sizeof(TRANSFER_STRUCT_MESS);
			}
			NET_BUFFER_OBJ *pNextRecvObj = GetNewAllocBufferObj(recvObj->m_cBuf,
				int(dwDivideSum+recvObj->m_uOffset+sizeof(TRANSFER_STRUCT_MESS)),
				recvObj->m_nAllocBufLen,
				nCurrDatLength
				);
			pNextRecvObj->m_pIntervalCounterPtr = recvObj->m_pIntervalCounterPtr;
			pNextRecvObj->m_pStructMessPtr = pStructMess;
			pNextRecvObj->operation = recvObj->operation;
			pNextRecvObj->sclient = recvObj->sclient;
			++(*recvObj->m_pIntervalCounterPtr);
			//------------------------------------------------------------------------------------------------------------------
			if((pStructMess->m_uTranferSumData + dwDivideSum) <= dwTransferedSum)
			{
				NET_BUFFER_OBJ *pLastBuff = recvObj;
				while(pLastBuff->next != NULL)
				{
					pLastBuff = pLastBuff->next;
				}
				pLastBuff->next = pNextRecvObj;
				dwDivideSum += pStructMess->m_uTranferSumData;
			}
			else
			{//加入到非完整NET_BUFFER_OBJ链表
				::EnterCriticalSection(&m_NoIntactBufferListLock);	
				pNextRecvObj->next = m_pNoIntactBufferObjsPtr;
				m_pNoIntactBufferObjsPtr = pNextRecvObj;
				::LeaveCriticalSection(&m_NoIntactBufferListLock);
				break;
			}
		}
		if(dwDivideSum < dwTransferedSum && (dwDivideSum+sizeof(TRANSFER_STRUCT_MESS)) > dwTransferedSum)
		{//表头还没收完
			int nCurrDatLength = dwTransferedSum - dwDivideSum;
			NET_BUFFER_OBJ *pNewBuf = GetNewAllocBufferObj();
			//NET_BUFFER_OBJ *pNewBuf = GetNewAllocBufferObj(recvObj->m_cBuf,int(dwDivideSum+recvObj->m_uOffset),recvObj->m_nAllocBufLen,nCurrDatLength);
			::memcpy(pNewBuf->m_cBuf, recvObj->m_cBuf+(dwDivideSum+recvObj->m_uOffset),nCurrDatLength);
			pNewBuf->m_nCurrDataLen = nCurrDatLength;
			pNewBuf->m_pStructMessPtr = NULL;
			//++(*recvObj->m_pIntervalCounterPtr);
			//pNewBuf->m_pIntervalCounterPtr = recvObj->m_pIntervalCounterPtr;
			pNewBuf->operation = recvObj->operation;
			pNewBuf->sclient   = recvObj->sclient;
			//加入到非完整NET_BUFFER_OBJ链表
			::EnterCriticalSection(&m_NoIntactBufferListLock);	
			pNewBuf->next = m_pNoIntactBufferObjsPtr;
			m_pNoIntactBufferObjsPtr = pNewBuf;
			::LeaveCriticalSection(&m_NoIntactBufferListLock);
		}
	}
	else if(recvObj->m_pStructMessPtr->m_uTranferSumData == 0 || recvObj->m_pStructMessPtr->m_uTranferSumData > dwTransferedSum)
	{//加入到非完整NET_BUFFER_OBJ链表
		::EnterCriticalSection(&m_NoIntactBufferListLock);	
		recvObj->next = m_pNoIntactBufferObjsPtr;
		m_pNoIntactBufferObjsPtr = recvObj;
		::LeaveCriticalSection(&m_NoIntactBufferListLock);
		if( dwTransferedSum < sizeof(TRANSFER_STRUCT_MESS) )
		{
			::memcpy(recvObj->m_cBuf+recvObj->m_uOffset, recvObj->m_pStructMessPtr, dwTransferedSum);
			recvObj->m_pStructMessPtr = NULL;
		}
		//判断pRtnBuff是否为完整的包 hjg 2014.4.19 add
		if( !pRtnBuff->m_pStructMessPtr || pRtnBuff->m_pStructMessPtr->m_cFlage[0] != 'H' \
			|| pRtnBuff->m_pStructMessPtr->m_cFlage[1] != 'L' \
			|| pRtnBuff->m_pStructMessPtr->m_uTranferSumData != (pRtnBuff->m_nCurrDataLen+sizeof(TRANSFER_STRUCT_MESS)) \
			)
		{
			pRtnBuff  = NULL;
		}
	}
	return pRtnBuff;
}


NET_BUFFER_OBJ * CNetTransferVir::GetWholeReadBuffer(NET_BUFFER_OBJ *recvObj)
{
	NET_BUFFER_OBJ *pRtnBuffPtr = NULL;
    /*if(recvObj != NULL)
	{
		ASSERT( recvObj->m_pStructMessPtr );
		if(recvObj->m_pStructMessPtr->m_nBlockSum == 1)
		{
			pRtnBuffPtr = recvObj;
		}
		else
		{
			//检查是否所有的块都接收到了
			int  nSumBlocks = 0;
			NET_BUFFER_OBJ  *pRootBuff = NULL;
			if( m_cRecvDataBuffObjMap.Lookup((WORD)recvObj->sclient,(void *&)pRootBuff) && pRootBuff != NULL)
			{
				recvObj->next = pRootBuff->next;
				pRootBuff->next = recvObj;
				NET_BUFFER_OBJ *pNextBuff = pRootBuff;
				while( pNextBuff )
				{
					if(pNextBuff->m_pStructMessPtr != NULL && 
						pNextBuff->m_pStructMessPtr->m_dwSerializeID == recvObj->m_pStructMessPtr->m_dwSerializeID)
					{
						++nSumBlocks;
					}
					pNextBuff = pNextBuff->next;
				}
			}
			else
			{
				if( recvObj->m_pStructMessPtr->m_cFlage[0] == 'H' && recvObj->m_pStructMessPtr->m_cFlage[1] == 'L' )
				{
					m_cRecvDataBuffObjMap.SetAt((WORD)recvObj->sclient, recvObj);
				}	
				return NULL;//还有没收到的数据块
			}
			if(nSumBlocks == recvObj->m_pStructMessPtr->m_nBlockSum)
			{//数据块都已接收
				NET_BUFFER_OBJ **pBufferlst = (NET_BUFFER_OBJ **)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY, (sizeof(NET_BUFFER_OBJ *) * nSumBlocks)); 

				NET_BUFFER_OBJ *pNextBuff = pRootBuff;
				NET_BUFFER_OBJ *pPreBuff  = NULL;
				//从小到大排序
				while(pNextBuff)
				{
					if(pNextBuff->m_pStructMessPtr != NULL && pNextBuff->m_pStructMessPtr->m_dwSerializeID == recvObj->m_pStructMessPtr->m_dwSerializeID)
					{//从链表中移除此节点
						pBufferlst[pNextBuff->m_pStructMessPtr->m_nSequence-1] = pNextBuff;
						if(pRootBuff == pNextBuff)
						{
							pRootBuff = pNextBuff->next;
							pNextBuff = pNextBuff->next;
							continue;
						}
						pPreBuff->next = pNextBuff->next;
						pNextBuff      = pPreBuff->next;
					}
					else
					{
						pPreBuff = pNextBuff;
						pNextBuff = pNextBuff->next;
					}
				}
				if(pRootBuff == NULL)
					m_cRecvDataBuffObjMap.RemoveKey((WORD)recvObj->sclient);
				else
					m_cRecvDataBuffObjMap.SetAt((WORD)pRootBuff->sclient, pRootBuff);
				for(int i = 0; i < nSumBlocks && pBufferlst[i] != NULL; ++i)
				{
					if(i == (nSumBlocks -1))
						pBufferlst[i]->next = NULL;
					else
						pBufferlst[i]->next = pBufferlst[i+1];
				}
				pRtnBuffPtr = pBufferlst[0];
			}	
		}
    }*/
	return pRtnBuffPtr;
}

//free Buffer_Obj
void CNetTransferVir::FreeBufferObjs()
{
    /*POSITION pos = m_cRecvDataBuffObjMap.GetStartPosition();
	while(pos)
	{
		NET_BUFFER_OBJ *pBufferPtr = NULL;
		WORD rKey = 0;
		m_cRecvDataBuffObjMap.GetNextAssoc(pos,rKey, (void *&)pBufferPtr);
		FreeBufferObj(pBufferPtr);
	}
    m_cRecvDataBuffObjMap.RemoveAll();*/
}

void CNetTransferVir::DoSendData(void *lpDataPtr, DWORD dwSize, NET_SOCKET_OBJ *pDestSockObj, _eNetTransferObjType eNetType/*=NT_None*/, _IrpType eIrpType /*=eNone*/)
{
	m_cSendSegMutex.Lock();
	//分配的大小为TRANSFERDATAMAXLENGTH的倍数
	int nAllocSize = dwSize%TRANSFERDATAMAXLENGTH ? (dwSize/TRANSFERDATAMAXLENGTH+1)*TRANSFERDATAMAXLENGTH : dwSize;
	NET_BUFFER_OBJ *pSendBuf  = GetNewAllocBufferObj(nAllocSize);
	::memcpy(pSendBuf->m_cBuf, lpDataPtr, dwSize);
	if(dwSize > TRANSFERDATAMAXLENGTH)
	{//分块发送
		pSendBuf->m_pIntervalCounterPtr = new LONG(nAllocSize / TRANSFERDATAMAXLENGTH);
		pSendBuf->m_nCurrDataLen = TRANSFERDATAMAXLENGTH;
	}
	else
	{
		pSendBuf->m_nCurrDataLen    = (int)dwSize ;
	}
	TRANSFER_STRUCT_MESS cStructMess;
	cStructMess.m_dwSerializeID = (USHORT)++pDestSockObj->m_dwSerializeID;
	cStructMess.m_nBlockSum     = nAllocSize / TRANSFERDATAMAXLENGTH;
	cStructMess.m_nSequence     = 1;//第一块数据
	cStructMess.m_eNetType      = eNetType;
	cStructMess.m_eIrpType      = eIrpType;
	for(DWORD iStep = 1; iStep*TRANSFERDATAMAXLENGTH < dwSize; ++iStep)
	{
		int nCurrDataLength = (iStep + 1) *TRANSFERDATAMAXLENGTH > dwSize ? (dwSize - iStep*TRANSFERDATAMAXLENGTH) : TRANSFERDATAMAXLENGTH;
		NET_BUFFER_OBJ *pNextBuf = GetNewAllocBufferObj(pSendBuf->m_cBuf,iStep*TRANSFERDATAMAXLENGTH,nAllocSize,nCurrDataLength);
		if(pNextBuf == NULL)
		{
            BOOST_ASSERT(0);
		}
		pNextBuf->m_pIntervalCounterPtr = pSendBuf->m_pIntervalCounterPtr;
		NET_BUFFER_OBJ *pPreBuf = pSendBuf;
		while(pPreBuf->next != NULL)
		{
			pPreBuf = pPreBuf->next;
		}
		pPreBuf->next = pNextBuf;
	}
	while(pSendBuf != NULL)
	{
		NET_BUFFER_OBJ *pNextBuf = pSendBuf->next;//先保存，防止先调用FreeBufferObj释放空间
		if(PostSend(pDestSockObj, pSendBuf, cStructMess) == SOCKET_ERROR)
		{
            BOOST_ASSERT(0);
			break;
		}
		++cStructMess.m_nSequence;
		pSendBuf = pNextBuf;                                                                                                                                                                                                        
		if( pSendBuf != NULL )
		{
			//::Sleep(25);
		}
	}
	m_cSendSegMutex.Unlock();
}

//加入能接收数据的对象
void CNetTransferVir::AddRecvNetDataOp(CVirReceiveNetDataOp *pOp)
{
    /*m_cMutex.Lock();
	POSITION pos = m_lstRecvNetDataOps.Find(pOp);
	if(pos == NULL)
	{
		m_lstRecvNetDataOps.AddTail(pOp);
	}
    m_cMutex.Unlock();*/
}
//移除接收数据的对象
void CNetTransferVir::RemoveRecevNetDataOp(CVirReceiveNetDataOp *pOp)
{
    /*m_cMutex.Lock();
	POSITION pos = m_lstRecvNetDataOps.Find(pOp);
	if(pos != NULL)
	{
		m_lstRecvNetDataOps.RemoveAt(pos);
	}
    m_cMutex.Unlock();*/
}

// 一个连接上的读操作完成
void CNetTransferVir::OnReadCompleted(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *buf)
{
    /*m_cMutex.Lock();
	POSITION pos = m_lstRecvNetDataOps.GetHeadPosition();
	while(pos)
	{
		CVirReceiveNetDataOp *pReceiveData = m_lstRecvNetDataOps.GetNext(pos);
		if(pReceiveData->IsCanRecvNetDataOp(buf))
		{
			pReceiveData->OnReceiveNetDataOp(sock, buf);
		}
	}
    m_cMutex.Unlock();*/
}

}}
