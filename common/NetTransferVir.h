#pragma once
#include <list>
#include ".\NetTransferCommonGlobal.h"
#include ".\criticalmutex.h"
#include <boost/unordered_map.hpp>


namespace jysoft {
namespace network {

#define TRANSFERDATAMAXLENGTH                (8*1024)     //传输数据的最大块
#define MAXFREEBUFFERSSUM                    50         //最大的空闲 NET_BUFFER_OBJ 块的数量

//network类基类
class CVirReceiveNetDataOp;
class  AFX_EXT_CLASS CNetTransferVir
{
public:
    CNetTransferVir( bool bSendHeadStruct =true );
	virtual ~CNetTransferVir(void);
protected:
	int                                      m_nNetProtocol;       //网络协议
	HANDLE                                   m_hCompletionPort;    //Completion port handle
    boost::unordered_map<WORD, void *>       m_cRecvDataBuffObjMap;//没有完全接收的数据块根据SOCKET放入MAP中
protected:
    utility::CCriticalMutex                  m_cMutex;
    utility::CCriticalMutex                  m_cMutex2;
    utility::CCriticalMutex                  m_cSendSegMutex;       //数据报送包同步
	CRITICAL_SECTION                         m_FreeBufferListLock;
	NET_BUFFER_OBJ                          *m_pFreeBufferObjsPtr;      //空闲的 NET_BUFFER_OBJ 链表
	CRITICAL_SECTION                         m_NoIntactBufferListLock;  //非完整包的临时存放点Lock
	NET_BUFFER_OBJ                           *m_pNoIntactBufferObjsPtr; //非完整NET_BUFFER_OBJ链表
    std::list<CVirReceiveNetDataOp *>      m_lstRecvNetDataOps;
private:
	char                                     *m_pDataExchangeTmpBuf[2]; //由HeapAlloc分配
	//是否发送表头格式  hjg 2011.12.26 add（注：无表头格式发送只用于和模拟人的指令发送）
    bool                                      m_bSendHeadStruct;
	//TRANSFER_STRUCT_MESS结构分配句柄 hjg 2012.5.14 add
	HANDLE                                    m_hAllocHeapHandle;
public://属性操作函数
	inline HANDLE GethCompletionPort() { return m_hCompletionPort;};
	virtual SOCKET Get_ListenHandle()  { return INVALID_SOCKET;};
	//得到主机的地址
	bool GetHostAddrInfo(const char *lpCompterName, DWORD dwPort, int nProtocol, /*out*/struct addrinfo **pptrInfo);
	//加入能接收数据的对象
	void AddRecvNetDataOp(CVirReceiveNetDataOp *pOp);
	void RemoveRecevNetDataOp(CVirReceiveNetDataOp *pOp);
public:
	//初始化网络连接，使其能正常接收数据
	virtual bool InitializeNet(const char * lpStr,DWORD nPort) = 0;
	/* Function: HandleIo
	//
	// Description:
	//    This function handles the IO on a socket. In the event of a receive, the 
	//    completed receive is posted again. For completed accepts, another AcceptEx
	//    is posted. For completed sends, the buffer is freed.
	//*/
	virtual void HandleIo(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *buf, HANDLE hCompPort, DWORD BytesTransfered, DWORD error) = 0;
	// 一个连接上的读操作完成
	void OnReadCompleted(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *buf);
	virtual void ShutDown() = 0;
	virtual void DoSendData(void *lpDataPtr, DWORD dwSize, _eNetTransferObjType eNetType = NT_None, _IrpType eIrpType = eNone) = 0;
protected:
	void DoSendData(void *lpDataPtr, DWORD dwSize, NET_SOCKET_OBJ *pDestSockObj, _eNetTransferObjType eNetType = NT_None, _IrpType eIrpType = eNone);
	//allocate a buffer object
	NET_BUFFER_OBJ *GetNewAllocBufferObj(int buflen = TRANSFERDATAMAXLENGTH);
	NET_BUFFER_OBJ *GetNewAllocBufferObj(char *lpBuff,  int nOffset, int nAllocLen, int nCurrDataLen);
	//Free the buffer object
	void FreeBufferObj(NET_BUFFER_OBJ *obj);
	//allocate a SocketObj 
	NET_SOCKET_OBJ *GetNewAllocSockObj(SOCKET s, int af);
	//Frees a socket object
	bool FreeSocketObj(NET_SOCKET_OBJ *obj);
	//-------------------------------------------------------------------------------------------------------------
	//Post an overlapped receive operation on the socket.
	int PostRecv(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *recvobj);
	//Post an overlapped send operation on the socket.
	int PostSend(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *sendobj, TRANSFER_STRUCT_MESS &cAppendMess);
	NET_BUFFER_OBJ *GetWholeReadBuffer(NET_BUFFER_OBJ *recvObj);
	//divide receive package
	NET_BUFFER_OBJ *DivideRecvBuffer(NET_BUFFER_OBJ *recvObj, DWORD dwTransferedSum);
	NET_BUFFER_OBJ *LoadNoIntactBuff(NET_BUFFER_OBJ **ppRecvObj, DWORD *pTransferedSumSize);
	//free Buffer_Obj
	void FreeBufferObjs();
protected:
    static unsigned long WINAPI CompletionThread(LPVOID lpParam);
};

}}
