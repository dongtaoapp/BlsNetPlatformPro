#include ".\vircardiogramparafactory.h"

namespace jysoft { namespace simulator {

	CVirCardiogramParaFactory::CVirCardiogramParaFactory(void)
	{
		m_pCurrCardiogramLeadsPtr = NULL;
	}

	CVirCardiogramParaFactory::~CVirCardiogramParaFactory(void)
	{
		if(m_pCurrCardiogramLeadsPtr != NULL)
		{
			delete m_pCurrCardiogramLeadsPtr;
		}
		m_pCurrCardiogramLeadsPtr = NULL;
	}

}}
