#pragma once
#include ".\common_global.h"
#include ".\IBedirecteLinksVir.h"
#include ".\NetTransferCommonGlobal.h"

namespace jysoft {
namespace network {

//------------------------------------------------------------------------------------------------------------
//�๦�ܣ����ش�������ദ����������¼�
//------------------------------------------------------------------------------------------------------------
class AFX_EXT_CLASS CVirTcpServeStatOp
{
public:
	CVirTcpServeStatOp(void);
	virtual ~CVirTcpServeStatOp(void);
public:
	// ������һ���µ�����
	virtual void OnConnectionEstablished(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *buf) = 0;
	// һ�����ӹر�
	virtual void OnConnectionClosing(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *buf) = 0;
	// ��һ�������Ϸ����˴���
	virtual void OnConnectionError(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *buf, int nError) = 0;
};


//------------------------------------------------------------------------------------------------------------
//�๦�ܣ����ش�������ദ��ͻ������¼�
//------------------------------------------------------------------------------------------------------------
class AFX_EXT_CLASS CVirTcpClientStatOp : public IBedirecteLinksVir
{
public:
	CVirTcpClientStatOp();
	virtual ~CVirTcpClientStatOp();
public:
	virtual bool isKindOf(const std::string &className);
public:
	// ������һ���µ�����
	virtual void OnConnectionEstablished(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *buf);
	//��ȡ�״�������Ҫ��������ݣ�ע������Ϊ��
	virtual void OnGetConnectData(char *lpDataPtr, int *lpSize);
	// һ�����ӹر�
	virtual void OnConnectionClosing();
	// ��һ�������Ϸ����˴���
	virtual void OnConnectionError(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *buf, int nError);
protected:
	// ������һ���µ�����
	virtual void TcpConnectionEstablished(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *buf) { };
	//��ȡ�״�������Ҫ��������ݣ�ע������Ϊ��
	virtual void TcpGetConnectData(char *lpDataPtr, int *lpSize) { };
	// һ�����ӹر�
	virtual void TcpConnectionClosing() { };
	// ��һ�������Ϸ����˴���
	virtual void TcpConnectionError(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *buf, int nError) {  };
};

//------------------------------------------------------------------------------------------
//�๦�ܣ����ش����������Խ��յ����紫����������
//------------------------------------------------------------------------------------------

class AFX_EXT_CLASS  CVirReceiveNetDataOp
{
protected:
	CVirReceiveNetDataOp(void);
	virtual ~CVirReceiveNetDataOp(void);
public:
	virtual bool IsCanRecvNetDataOp(NET_BUFFER_OBJ *buf) = 0;
	//������յ�������
	virtual void OnReceiveNetDataOp(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *buf) = 0;
};

class AFX_EXT_CLASS CVirReceiveNoneNetDataOp : public CVirReceiveNetDataOp
{
protected:
	CVirReceiveNoneNetDataOp() { };
	~CVirReceiveNoneNetDataOp() { };
public:
	bool IsCanRecvNetDataOp(NET_BUFFER_OBJ *buf)
	{
		if(buf->m_pStructMessPtr->m_eNetType == NT_None)
			return true;
		return false;
	};
	//������յ�������
	virtual void OnReceiveNetDataOp(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *buf) = 0;
};

class AFX_EXT_CLASS CVirReceiveWatchFacilityParamNetDataOp : public CVirReceiveNetDataOp
{
protected:
	CVirReceiveWatchFacilityParamNetDataOp() { };
	~CVirReceiveWatchFacilityParamNetDataOp() { };
public:
	bool IsCanRecvNetDataOp(NET_BUFFER_OBJ *buf)
	{
		if(buf->m_pStructMessPtr->m_eNetType == NT_WatchFacilityParam)
			return true;
		return false;
	};
	//������յ�������
	virtual void OnReceiveNetDataOp(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *buf) = 0;
};

class AFX_EXT_CLASS CVirReceiveControlNetDataOp : public CVirReceiveNetDataOp
{
protected:
	CVirReceiveControlNetDataOp() { };
	~CVirReceiveControlNetDataOp() { };
public:
	bool IsCanRecvNetDataOp(NET_BUFFER_OBJ *buf)
	{
		if(buf->m_pStructMessPtr->m_eNetType == NT_Control)
			return true;
		return false;
	};
	//������յ�������
	virtual void OnReceiveNetDataOp(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *buf) = 0;
};

class AFX_EXT_CLASS CVirReceiveTalkNetDataOp : public CVirReceiveNetDataOp
{
protected:
	CVirReceiveTalkNetDataOp() { };
	~CVirReceiveTalkNetDataOp() { };
public:
	bool IsCanRecvNetDataOp(NET_BUFFER_OBJ *buf)
	{
		if(buf->m_pStructMessPtr->m_eNetType == NT_Talk)
			return true;
		return false;
	};
	//������յ�������
	virtual void OnReceiveNetDataOp(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *buf) = 0;
};

class AFX_EXT_CLASS CVirReceiveScenarioNetDataOP : public CVirReceiveNetDataOp
{
protected:
	CVirReceiveScenarioNetDataOP() { };
	~CVirReceiveScenarioNetDataOP() { };
public:
	bool IsCanRecvNetDataOp(NET_BUFFER_OBJ *buf)
	{
		if(buf->m_pStructMessPtr->m_eNetType == NT_ScenarioEvent)
			return true;
		return false;
	};
	//������յ�������
	virtual void OnReceiveNetDataOp(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *buf) = 0;
};
//CPRʵʱ�������紫����սӿ�
class AFX_EXT_CLASS CVirReceiveCPRRealTimeNetDataOp : public CVirReceiveNetDataOp
{
protected:
	CVirReceiveCPRRealTimeNetDataOp() { };
	~CVirReceiveCPRRealTimeNetDataOp() {};
public:
	bool IsCanRecvNetDataOp(NET_BUFFER_OBJ *buf)
	{
		if(buf->m_pStructMessPtr->m_eNetType == NT_CPRRealTimeData)
			return true;
		return false;
	};
	//������յ�������
	virtual void OnReceiveNetDataOp(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *buf) = 0;
};

//�������ݰ�������:CPR���ݣ��������ȹ��̣�
class AFX_EXT_CLASS CVirReceiveCoursePackageNetDataOp : public CVirReceiveNetDataOp
{
protected:
	CVirReceiveCoursePackageNetDataOp() { };
	~CVirReceiveCoursePackageNetDataOp() {};
public:
	bool IsCanRecvNetDataOp(NET_BUFFER_OBJ *buf)
	{
		if(buf->m_pStructMessPtr->m_eNetType == NT_CourseDataPackage)
			return true;
		return false;
	};
	//������յ�������
	virtual void OnReceiveNetDataOp(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *buf) = 0;
};

//ģ����WifiͨѶ���ݰ�
class AFX_EXT_CLASS CVirReceiveSimulateCommNetDataOp : public CVirReceiveNetDataOp
{
protected:
	CVirReceiveSimulateCommNetDataOp() { };
	~CVirReceiveSimulateCommNetDataOp() {};
public:
	bool IsCanRecvNetDataOp(NET_BUFFER_OBJ *buf)
	{
		if(buf->m_pStructMessPtr->m_eNetType == NT_SimulateCommData)
			return true;
		return false;
	};
	//������յ�������
	virtual void OnReceiveNetDataOp(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *buf) = 0;
};

//ͨ�����ļ�������սӿ�
class AFX_EXT_CLASS CVirReceiveFilePackageNetDataOp : public CVirReceiveNetDataOp
{
protected:
	CVirReceiveFilePackageNetDataOp() { };
	~CVirReceiveFilePackageNetDataOp() {};
public:
	bool IsCanRecvNetDataOp(NET_BUFFER_OBJ *buf)
	{
		if(buf->m_pStructMessPtr->m_eNetType == NT_CommonFile)
			return true;
		return false;
	};
	//������յ�������
	virtual void OnReceiveNetDataOp(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *buf) = 0;
};
}}
