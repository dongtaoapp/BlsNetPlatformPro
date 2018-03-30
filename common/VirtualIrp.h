#pragma once
#include <string>
#include ".\CommonGlobal.h"

namespace jysoft { namespace irp {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     虚拟Irp封装类
	创建人：	 hjg
	创建时间：   2009/4/8
	//-----------------------------------------------------------------------------------------------------------------*/
	class AFX_EXT_CLASS CVirtualIrp
	{
	public:
		CVirtualIrp(void);
		virtual ~CVirtualIrp(void);
	public:
		//返回Irp的类别
		virtual _IrpType Get_eIrpType() = 0;
		virtual bool isKindOf(const std::string &strClass) = 0;
	public:
		/*******************************************************************************/
		// 函数名称： doPackageIrp
		// 功能：  打包Irp的内容
		// 参数： 
		// 返回值: 
		virtual std::string doPackageIrp() = 0;
	};
}}

