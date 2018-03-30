#pragma once
#include <string>
#include ".\IBedirecteLinksVir.h"

namespace jysoft {
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     逻辑操作接口基类
	创建人：	 hjg
	创建时间：   2008/8/5
	//-----------------------------------------------------------------------------------------------------------------*/

	class AFX_EXT_CLASS COpInterfaceVir : public IBedirecteLinksVir
	{
	public:
		COpInterfaceVir(void);
		virtual ~COpInterfaceVir(void);
	public:
		virtual bool isKindOf(const std::string &strClassName);
	};

}