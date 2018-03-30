#include <vector>
#include <boost/assign.hpp>
#include ".\simulatororderirp.h"

#include "..\Common\DecodeUtil.h"


using namespace std;
using namespace boost::assign;
using namespace jysoft::utility;
namespace jysoft { namespace irp {

	CSimulatorOrderIrp::CSimulatorOrderIrp(_SIMULATECOMMANDTYPE  eCmdType)
	{
		m_eCommandType  = eCmdType;
	}

	CSimulatorOrderIrp::~CSimulatorOrderIrp(void)
	{
		m_lstOrderDecodes.clear();
	}

	bool CSimulatorOrderIrp::isKindOf(const std::string &strClass)
	{
		if( strClass == "CSimulatorOrderIrp" )
		{
			return true;
		}
		return false;
	}

	void CSimulatorOrderIrp::addOrderDecode(const std::string &orderDecode)
	{
		m_lstOrderDecodes.push_back( orderDecode );
	}

	//开始解码
	std::list<std::string>::iterator CSimulatorOrderIrp::StartUnDecode()
	{
		return m_lstOrderDecodes.begin();
	}

	//解码下个指令
	long CSimulatorOrderIrp::NextUnDecode(std::list<std::string>::iterator &pos, byte *lpbyteData)
	{
		if( pos != m_lstOrderDecodes.end() )
		{
			long  length = CDecodeUtil::hexstrToByteArray(*pos, lpbyteData);
			if( lpbyteData != NULL )
			{
				++pos;
			}
			return length;
		}
		return 0;
	}

	/*******************************************************************************/
	// 函数名称： createSimulatorOrderIrp
	// 功能： 创建模拟人指令Irp
	// 参数：      
	// 返回值:  
	CSimulatorOrderIrp * CSimulatorOrderIrp::createSimulatorOrderIrp(byte param1, byte param2)
	{
		CSimulatorOrderIrp *pNewOrderIrp = new CSimulatorOrderIrp(CT_NONE);
		std::vector<byte>  vt;
		//心率指令
		vt = (list_of(0xFF), param1, param2, 0xFC);
		std::string  orderDecode = CDecodeUtil::byteArrayToHexstr(vt.begin(), vt.end());
		pNewOrderIrp->addOrderDecode( orderDecode );
		return pNewOrderIrp;
	}
}}
