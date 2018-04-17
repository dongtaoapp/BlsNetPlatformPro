#pragma once
#include <string>
#include ".\simulatorsymptom_global.h"

namespace jysoft { namespace simulator {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     脚本元素基础类
	创建人：	 hjg
	创建时间：   2017/2/23
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORSYMPTOMSHARED_EXPORT CXVirtualComponent
	{
	public:
		CXVirtualComponent(void);
		virtual ~CXVirtualComponent(void);
	public:
		virtual bool isKindOf(const std::string &strClassName) = 0;
	};
}}
