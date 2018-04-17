#pragma once
#include <string>
#include ".\simulatorsymptom_global.h"

namespace jysoft { namespace simulator {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     �ű�Ԫ�ػ�����
	�����ˣ�	 hjg
	����ʱ�䣺   2017/2/23
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
