#pragma once
#include <string>
#include <atlconv.h>
#include <objbase.h>
#include ".\adultparams_global.h"

#include "..\SimulatorBase\VirCardiogramParaFactory.h"


namespace jysoft { namespace simulator { namespace ecg {

    class ADULTPARAMSSHARED_EXPORT CAdultCardiogramParamFactory : public CVirCardiogramParaFactory
	{
	public:
		CAdultCardiogramParamFactory(const std::string &ecgResourcePath);
		virtual ~CAdultCardiogramParamFactory(void);
	private:
		IStorage           *m_pStorages;
	public:
		//������Ӧ�Ĳ�����
		virtual ICardiogramLeads * CreateCardiogramLeadsInstance( const CECGParams *ptrParam );
	};
}}}
