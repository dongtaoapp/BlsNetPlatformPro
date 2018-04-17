#pragma once
#include ".\ICardiogramLeads.h"

#include "..\Common\ECGParams.h"

namespace jysoft { namespace simulator {

    class SIMULATORBASESHARED_EXPORT CVirCardiogramParaFactory
	{
	public:
		CVirCardiogramParaFactory(void);
		virtual ~CVirCardiogramParaFactory(void);
	public:
		//创建对应的参数类
		virtual ICardiogramLeads * CreateCardiogramLeadsInstance( const CECGParams *ptrParam ) = 0;
	public:
		inline ICardiogramLeads * GetCurrCardiogramLeadsInstance() {return m_pCurrCardiogramLeadsPtr;};
	protected:
		ICardiogramLeads *                m_pCurrCardiogramLeadsPtr;
	};

}}
