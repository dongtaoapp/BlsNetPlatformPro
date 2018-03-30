#pragma once
#include ".\common_global.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <mswsock.h>
#include ".\CommonGlobal.h"


namespace jysoft {
namespace network {
	//传输的数据表示的类型
	enum _eNetTransferObjType
	{
		NT_None = 0,           //末定义
		NT_Control,            //控制命令
		NT_Talk,               //语言对讲数据
		NT_ScenarioEvent,      //场景属性及事件
		NT_WatchFacilityParam, //监控设备参数
		NT_CPRRealTimeData,    //CPR实时数据
		NT_CourseDataPackage,  //过程数据包（包括:CPR数据；场景急救过程）
		NT_SimulateCommData,   //模拟人通讯数据
		NT_CommonFile,          //通用性文件
		NT_LogPackage			//日志包
	};
	//network transfer structs define
	// This is our per I/O buffer. It contains a WSAOVERLAPPED structure as well
	//    as other necessary information for handling an IO operation on a socket.
	//
	//传输时附带的结构信息
	typedef struct AFX_EXT_CLASS _TRANSFER_STRUCT_MESS
	{
		char                 m_cFlage[2];
		BYTE                 m_nBlockSum;      //总数块
		BYTE                 m_nSequence;      //顺序号
		USHORT               m_dwSerializeID;  //ID号
		USHORT               m_uTranferSumData; //数据包大小：包含数据区和此结构的总和的大小
		//-------------------------------------------------------------------------------
		_eNetTransferObjType m_eNetType;
		_IrpType             m_eIrpType;
	public:
		_TRANSFER_STRUCT_MESS();
	} TRANSFER_STRUCT_MESS;

	typedef struct _NET_BUFFER_OBJ
	{
		WSAOVERLAPPED           ol;

		SOCKET                  sclient;       // Used for AcceptEx client socket for server

		char                   *m_cBuf;           // Buffer for recv/send/AcceptEx
		int                     m_nCurrDataLen;   // 当前使用了的数据长度
		int                     m_nAllocBufLen;   // 分配的缓冲区长度, 发送时小于传输最大块
		UINT                    m_uOffset;        // 离m_cBuf多长开始
		bool                    m_bOutsideAlloc;  // 数据区由外部分配
		LONG                   *m_pIntervalCounterPtr;//内部计数器，0：表示缓冲区没别引用；n：表示缓冲区被n个别的地方引用  注：new出

		SOCKADDR_STORAGE        addr;
		int                     addrlen;

		int                     operation;     // Type of operation issued
#define OP_ACCEPT       0                   // AcceptEx
#define OP_READ         1                   // WSARecv/WSARecvFrom
#define OP_WRITE        2                   // WSASend/WSASendTo
#define OP_CONNECT      3                   // WSAConnect

		struct _NET_BUFFER_OBJ  *next;

		TRANSFER_STRUCT_MESS    *m_pStructMessPtr;

	} NET_BUFFER_OBJ;

	//
	// This is our per socket buffer. It contains information about the socket handle
	//    which is returned from each GetQueuedCompletionStatus call.
	//
	typedef struct AFX_EXT_CLASS  _NET_SOCKET_OBJ
	{
		SOCKET               s;              // Socket handle

		int                  af,             // Address family of socket (AF_INET, AF_INET6)
			bClosing;       // Is the socket closing?

		SOCKADDR_STORAGE     m_cRemoteAddr;
		int                  addrlen;

		volatile LONG         OutstandingOps; // Number of outstanding overlapped ops on socket

		static DWORD         m_dwSerializeID; //ID号

		CRITICAL_SECTION     SockCritSec;    // Protect access to this structure

	} NET_SOCKET_OBJ;
}}
