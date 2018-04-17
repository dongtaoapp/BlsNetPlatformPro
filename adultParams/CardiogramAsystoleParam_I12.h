#pragma once

#include "..\simulatorbase\vircardiogramparam.h"


namespace jysoft { namespace simulator { namespace ecg {

	class CCardiogramAsystoleParam_I12 : public CVirCardiogramParam
	{
	public:
		CCardiogramAsystoleParam_I12( IStorage *pRootStorage );
		virtual ~CCardiogramAsystoleParam_I12(void);
	public:
		//加载参数值
        virtual void LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm,int uHR, short sConduct = 0, short sExtendParam = 0);
		//是否初始构建时发送两次心电图数据
		virtual bool IsInitialSendDoubleSampleData() { return false; };
	};
}}}
