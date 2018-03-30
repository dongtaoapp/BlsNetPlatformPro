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

// ������һ���µ�����
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

//��ȡ�״�������Ҫ��������ݣ�ע������Ϊ��
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

// һ�����ӹر�
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

// ��һ�������Ϸ����˴���
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
