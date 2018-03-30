#pragma once
#include ".\simulatorbase_global.h"
#include <list>
#include <string>
#include <boost/assert.hpp>
#include ".\SimulateBaseGlobal.h"

#include "..\Common\VirtualIrp.h"

namespace jysoft { namespace irp {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     模拟人指令包
	创建人：	 hjg
	创建时间：   2017/2/9
	注：  修改成支持for_each按次序查询(末完成)
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORBASESHARED_EXPORT CSimulatorOrderIrp : public CVirtualIrp
	{
	public:
		CSimulatorOrderIrp(_SIMULATECOMMANDTYPE  eCmdType);
		virtual ~CSimulatorOrderIrp(void);
	public:
		/*******************************************************************************/
		// 函数名称： createSimulatorOrderIrp
		// 功能： 创建模拟人指令Irp
		// 参数：      
		// 返回值:  
		static CSimulatorOrderIrp * createSimulatorOrderIrp(byte param1, byte param2);
	public:
		//返回Irp的类别
		virtual _IrpType Get_eIrpType() { return eSimulateOrder; };
		virtual bool isKindOf(const std::string &strClass);
		/*******************************************************************************/
		// 函数名称： doPackageIrp
		// 功能：  打包Irp的内容
		// 参数： 
		// 返回值: 
		virtual std::string doPackageIrp() { BOOST_ASSERT( 0 ); return ""; };
	public:
		inline _SIMULATECOMMANDTYPE Get_eSimulateCommandType() { return m_eCommandType; };
	protected:
		std::list<std::string>         m_lstOrderDecodes;        //编码的通信指令列表
		_SIMULATECOMMANDTYPE           m_eCommandType;
	public:
		void addOrderDecode(const std::string &orderDecode);
		void clearOrderDecode() { m_lstOrderDecodes.clear(); };
	public:
		//开始解码
		std::list<std::string>::iterator StartUnDecode();
		//解码下个指令
		long NextUnDecode(std::list<std::string>::iterator &pos, byte *lpbyteData);
	};

}}
