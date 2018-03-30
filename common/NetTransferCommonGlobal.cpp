#include ".\nettransfercommonglobal.h"

namespace jysoft {
namespace network {

DWORD _NET_SOCKET_OBJ::m_dwSerializeID = 1;


_TRANSFER_STRUCT_MESS::_TRANSFER_STRUCT_MESS()
{
	m_cFlage[0] = 'H';
	m_cFlage[1] = 'L';
	m_nBlockSum = 0;
	m_nSequence = 0;
	m_dwSerializeID = 0;
	m_uTranferSumData = 0;
	m_eIrpType   = eNone;
}

}}

