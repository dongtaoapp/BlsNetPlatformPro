#include ".\virtcptransferopgather.h"

namespace jysoft {
namespace network {
//-----------------------------------------------------------------------------------------------------------
//class CVirTcpServeStatOp
CVirTcpServeStatOp::CVirTcpServeStatOp(void)
{
}

CVirTcpServeStatOp::~CVirTcpServeStatOp(void)
{
}

//------------------------------------------------------------------------------------------------------------
//class CVirTcpClientStatOp
CVirTcpClientStatOp::CVirTcpClientStatOp()
{
}

CVirTcpClientStatOp::~CVirTcpClientStatOp()
{
}

bool CVirTcpClientStatOp::isKindOf(const std::string &className)
{
	if( className == "CVirTcpClientStatOp" )
	{
		return true;
	}
	return false;
}

// 建立了一个新的连接
void CVirTcpClientStatOp::OnConnectionEstablished(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *buf)
{
	IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
	while ( pInterfaceVir != NULL )
	{
		if( pInterfaceVir->isKindOf("CVirTcpClientStatOp") )
		{
			CVirTcpClientStatOp *pTcpClientStatOp = (CVirTcpClientStatOp *)pInterfaceVir;
			pTcpClientStatOp->TcpConnectionEstablished( sock, buf );
		}
		pInterfaceVir = pInterfaceVir->GetNextInterfacePtr();
	}
}

//获取首次连接需要传输的数据；注：不能为空
void CVirTcpClientStatOp::OnGetConnectData(char *lpDataPtr, int *lpSize)
{
	IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
	while ( pInterfaceVir != NULL )
	{
		if( pInterfaceVir->isKindOf("CVirTcpClientStatOp") )
		{
			CVirTcpClientStatOp *pTcpClientStatOp = (CVirTcpClientStatOp *)pInterfaceVir;
			pTcpClientStatOp->TcpGetConnectData( lpDataPtr, lpSize );
		}
		pInterfaceVir = pInterfaceVir->GetNextInterfacePtr();
	}
}

// 一个连接关闭
void CVirTcpClientStatOp::OnConnectionClosing()
{
	IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
	while ( pInterfaceVir != NULL )
	{
		if( pInterfaceVir->isKindOf("CVirTcpClientStatOp") )
		{
			CVirTcpClientStatOp *pTcpClientStatOp = (CVirTcpClientStatOp *)pInterfaceVir;
			pTcpClientStatOp->TcpConnectionClosing( );
		}
		pInterfaceVir = pInterfaceVir->GetNextInterfacePtr();
	}
}

// 在一个连接上发生了错误
void CVirTcpClientStatOp::OnConnectionError(NET_SOCKET_OBJ *sock, NET_BUFFER_OBJ *buf, int nError)
{
	IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
	while ( pInterfaceVir != NULL )
	{
		if( pInterfaceVir->isKindOf("CVirTcpClientStatOp") )
		{
			CVirTcpClientStatOp *pTcpClientStatOp = (CVirTcpClientStatOp *)pInterfaceVir;
			pTcpClientStatOp->TcpConnectionError( sock, buf, nError );
		}
		pInterfaceVir = pInterfaceVir->GetNextInterfacePtr();
	}
}

//-------------------------------------------------------------------------------------------------------------
//class CVirReceiveNetDataOp
CVirReceiveNetDataOp::CVirReceiveNetDataOp(void)
{
}

CVirReceiveNetDataOp::~CVirReceiveNetDataOp(void)
{
}

}}
