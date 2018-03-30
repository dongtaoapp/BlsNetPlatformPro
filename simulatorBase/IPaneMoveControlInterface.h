#pragma once
#include ".\simulatorbase_global.h"

#include "..\Common\IBedirecteLinksVir.h"

namespace jysoft{  namespace utility {

    class SIMULATORBASESHARED_EXPORT IPaneMoveControlInterface  : public IBedirecteLinksVir
	{
	public:
		IPaneMoveControlInterface(void);
		virtual ~IPaneMoveControlInterface(void);
	public:
		virtual bool isKindOf(const std::string &className);
	public:
		//移动快滑动操作
		void OnPaneMoveOp();
		// 开始绘心电图
		void OnStart(bool bClear);
	protected:
		//移动快滑动操作
		virtual void PaneMoveOp() = 0;
		// 开始绘心电图
		virtual void Start(bool bClear) = 0;
	};

}}
