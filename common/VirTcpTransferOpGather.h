#pragma once
#include ".\common_global.h"
#include ".\IBedirecteLinksVir.h"
#include ".\NetTransferCommonGlobal.h"

namespace jysoft {
namespace network {

//------------------------------------------------------------------------------------------------------------
//类功能：重载此类的子类处理服务器的事件
//------------------------------------------------------------------------------------------------------------
class AFX_EXT_CLASS CVirTcpServeStatOp
{
public:
	CVirTcpServeStatOp(void);
	virtual ~CVirTcpServeStatOp(void);
public:
	// 建立了一个新的连接
	virtual void OnConnectionEstablished(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *buf) = 0;
	// 一个连接关闭
	virtual void OnConnectionClosing(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *buf) = 0;
	// 在一个连接上发生了错误
	virtual void OnConnectionError(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *buf, int nError) = 0;
};


//------------------------------------------------------------------------------------------------------------
//类功能：重载此类的子类处理客户器的事件
//------------------------------------------------------------------------------------------------------------
class AFX_EXT_CLASS CVirTcpClientStatOp : public IBedirecteLinksVir
{
public:
	CVirTcpClientStatOp();
	virtual ~CVirTcpClientStatOp();
public:
	virtual bool isKindOf(const std::string &className);
public:
	// 建立了一个新的连接
	virtual void OnConnectionEstablished(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *buf);
	//获取首次连接需要传输的数据；注：不能为空
	virtual void OnGetConnectData(char *lpDataPtr, int *lpSize);
	// 一个连接关闭
	virtual void OnConnectionClosing();
	// 在一个连接上发生了错误
	virtual void OnConnectionError(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *buf, int nError);
protected:
	// 建立了一个新的连接
	virtual void TcpConnectionEstablished(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *buf) { };
	//获取首次连接需要传输的数据；注：不能为空
	virtual void TcpGetConnectData(char *lpDataPtr, int *lpSize) { };
	// 一个连接关闭
	virtual void TcpConnectionClosing() { };
	// 在一个连接上发生了错误
	virtual void TcpConnectionError(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *buf, int nError) {  };
};

//------------------------------------------------------------------------------------------
//类功能：重载此类的子类可以接收到网络传输来的数据
//------------------------------------------------------------------------------------------

class AFX_EXT_CLASS  CVirReceiveNetDataOp
{
protected:
	CVirReceiveNetDataOp(void);
	virtual ~CVirReceiveNetDataOp(void);
public:
	virtual bool IsCanRecvNetDataOp(NET_BUFFER_OBJ *buf) = 0;
	//处理接收到的数据
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
	//处理接收到的数据
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
	//处理接收到的数据
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
	//处理接收到的数据
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
	//处理接收到的数据
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
	//处理接收到的数据
	virtual void OnReceiveNetDataOp(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *buf) = 0;
};
//CPR实时数据网络传输接收接口
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
	//处理接收到的数据
	virtual void OnReceiveNetDataOp(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *buf) = 0;
};

//过程数据包（包括:CPR数据；场景急救过程）
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
	//处理接收到的数据
	virtual void OnReceiveNetDataOp(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *buf) = 0;
};

//模拟人Wifi通讯数据包
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
	//处理接收到的数据
	virtual void OnReceiveNetDataOp(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *buf) = 0;
};

//通用性文件传输接收接口
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
	//处理接收到的数据
	virtual void OnReceiveNetDataOp(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *buf) = 0;
};
}}
