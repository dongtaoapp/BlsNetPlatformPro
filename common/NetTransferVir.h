#pragma once
#include <list>
#include ".\NetTransferCommonGlobal.h"
#include ".\criticalmutex.h"
#include <boost/unordered_map.hpp>


namespace jysoft {
namespace network {

#define TRANSFERDATAMAXLENGTH                (8*1024)     //�������ݵ�����
#define MAXFREEBUFFERSSUM                    50         //���Ŀ��� NET_BUFFER_OBJ �������

//network�����
class CVirReceiveNetDataOp;
class  AFX_EXT_CLASS CNetTransferVir
{
public:
    CNetTransferVir( bool bSendHeadStruct =true );
	virtual ~CNetTransferVir(void);
protected:
	int                                      m_nNetProtocol;       //����Э��
	HANDLE                                   m_hCompletionPort;    //Completion port handle
    boost::unordered_map<WORD, void *>       m_cRecvDataBuffObjMap;//û����ȫ���յ����ݿ����SOCKET����MAP��
protected:
    utility::CCriticalMutex                  m_cMutex;
    utility::CCriticalMutex                  m_cMutex2;
    utility::CCriticalMutex                  m_cSendSegMutex;       //���ݱ��Ͱ�ͬ��
	CRITICAL_SECTION                         m_FreeBufferListLock;
	NET_BUFFER_OBJ                          *m_pFreeBufferObjsPtr;      //���е� NET_BUFFER_OBJ ����
	CRITICAL_SECTION                         m_NoIntactBufferListLock;  //������������ʱ��ŵ�Lock
	NET_BUFFER_OBJ                           *m_pNoIntactBufferObjsPtr; //������NET_BUFFER_OBJ����
    std::list<CVirReceiveNetDataOp *>      m_lstRecvNetDataOps;
private:
	char                                     *m_pDataExchangeTmpBuf[2]; //��HeapAlloc����
	//�Ƿ��ͱ�ͷ��ʽ  hjg 2011.12.26 add��ע���ޱ�ͷ��ʽ����ֻ���ں�ģ���˵�ָ��ͣ�
    bool                                      m_bSendHeadStruct;
	//TRANSFER_STRUCT_MESS�ṹ������ hjg 2012.5.14 add
	HANDLE                                    m_hAllocHeapHandle;
public://���Բ�������
	inline HANDLE GethCompletionPort() { return m_hCompletionPort;};
	virtual SOCKET Get_ListenHandle()  { return INVALID_SOCKET;};
	//�õ������ĵ�ַ
	bool GetHostAddrInfo(const char *lpCompterName, DWORD dwPort, int nProtocol, /*out*/struct addrinfo **pptrInfo);
	//�����ܽ������ݵĶ���
	void AddRecvNetDataOp(CVirReceiveNetDataOp *pOp);
	void RemoveRecevNetDataOp(CVirReceiveNetDataOp *pOp);
public:
	//��ʼ���������ӣ�ʹ����������������
	virtual bool InitializeNet(const char * lpStr,DWORD nPort) = 0;
	/* Function: HandleIo
	//
	// Description:
	//    This function handles the IO on a socket. In the event of a receive, the 
	//    completed receive is posted again. For completed accepts, another AcceptEx
	//    is posted. For completed sends, the buffer is freed.
	//*/
	virtual void HandleIo(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *buf, HANDLE hCompPort, DWORD BytesTransfered, DWORD error) = 0;
	// һ�������ϵĶ��������
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
