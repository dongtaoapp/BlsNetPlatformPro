#pragma once
#include ".\common_global.h"
#include ".\IBedirecteLinksVir.h"

namespace jysoft {
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     界面显示控件接口基类
	创建人：	 hjg
	创建时间：   2008/8/5
	//-----------------------------------------------------------------------------------------------------------------*/

	class AFX_EXT_CLASS IUpdateShowVir : public IBedirecteLinksVir
	{
	public:
		IUpdateShowVir(void);
		virtual ~IUpdateShowVir(void);
	public:
		void OnAllUnLinkUpdateShow();
		void OnAllLinkUpdateShow();
	public:
		virtual void UnLinkUpdateShow() = 0;
		virtual void LinkUpdateShow()   = 0;
	public:
		virtual bool isKindOf(const std::string &className);

	};
}
