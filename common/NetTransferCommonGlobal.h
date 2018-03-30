#pragma once
#include ".\common_global.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <mswsock.h>
#include ".\CommonGlobal.h"


namespace jysoft {
namespace network {
	//��������ݱ�ʾ������
	enum _eNetTransferObjType
	{
		NT_None = 0,           //ĩ����
		NT_Control,            //��������
		NT_Talk,               //���ԶԽ�����
		NT_ScenarioEvent,      //�������Լ��¼�
		NT_WatchFacilityParam, //����豸����
		NT_CPRRealTimeData,    //CPRʵʱ����
		NT_CourseDataPackage,  //�������ݰ�������:CPR���ݣ��������ȹ��̣�
		NT_SimulateCommData,   //ģ����ͨѶ����
		NT_CommonFile,          //ͨ�����ļ�
		NT_LogPackage			//��־��
	};
	//network transfer structs define
	// This is our per I/O buffer. It contains a WSAOVERLAPPED structure as well
	//    as other necessary information for handling an IO operation on a socket.
	//
	//����ʱ�����Ľṹ��Ϣ
	typedef struct AFX_EXT_CLASS _TRANSFER_STRUCT_MESS
	{
		char                 m_cFlage[2];
		BYTE                 m_nBlockSum;      //������
		BYTE                 m_nSequence;      //˳���
		USHORT               m_dwSerializeID;  //ID��
		USHORT               m_uTranferSumData; //���ݰ���С�������������ʹ˽ṹ���ܺ͵Ĵ�С
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
		int                     m_nCurrDataLen;   // ��ǰʹ���˵����ݳ���
		int                     m_nAllocBufLen;   // ����Ļ���������, ����ʱС�ڴ�������
		UINT                    m_uOffset;        // ��m_cBuf�೤��ʼ
		bool                    m_bOutsideAlloc;  // ���������ⲿ����
		LONG                   *m_pIntervalCounterPtr;//�ڲ���������0����ʾ������û�����ã�n����ʾ��������n����ĵط�����  ע��new��

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

		static DWORD         m_dwSerializeID; //ID��

		CRITICAL_SECTION     SockCritSec;    // Protect access to this structure

	} NET_SOCKET_OBJ;
}}
