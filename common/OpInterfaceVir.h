#pragma once
#include <string>
#include ".\IBedirecteLinksVir.h"

namespace jysoft {
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     �߼������ӿڻ���
	�����ˣ�	 hjg
	����ʱ�䣺   2008/8/5
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