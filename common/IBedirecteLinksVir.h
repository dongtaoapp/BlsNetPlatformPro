#pragma once
#include <string>
#include ".\common_global.h"


namespace jysoft {
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     双向链接接口基类
	创建人：	 hjg
	创建时间：   2016/8/20
	功能：       包含双向链接的操作函数
	//-----------------------------------------------------------------------------------------------------------------*/
	class AFX_EXT_CLASS IBedirecteLinksVir
	{
	public:
		IBedirecteLinksVir(void);
		virtual ~IBedirecteLinksVir(void);
	protected:
		IBedirecteLinksVir            *m_pNextInterface;    //下个接口
		IBedirecteLinksVir            *m_pPreInterface;     //上个接口
	public:
		//设置下个界面显示控件接口
		void SetNextInterfacePtr(IBedirecteLinksVir *pNextInterface);
		//设置上个接口
		inline void SetPreviouInterfacePtr(IBedirecteLinksVir *pPreInterface) { m_pPreInterface = pPreInterface;};
		//返回下个接口
		inline IBedirecteLinksVir * GetNextInterfacePtr() { return m_pNextInterface;};
		//返回上个接口
		inline IBedirecteLinksVir * GetPreviouInterfacePtr() { return m_pPreInterface;};
	public:
		//返回接口联表的头
		IBedirecteLinksVir * GetHeaderInterfacePtr();
		//移除制定的接口
		static IBedirecteLinksVir * RemoveInterfacePtr(IBedirecteLinksVir *pOrgInterfacePtr, IBedirecteLinksVir *pRmvInterface);
	public:
		virtual bool isKindOf(const std::string &className) = 0;
	};
}
