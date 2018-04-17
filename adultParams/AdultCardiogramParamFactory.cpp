#include <boost/format.hpp>
#include <boost/assert.hpp>
#include ".\adultcardiogramparamfactory.h"

#include ".\CardiogramSinus.h"
#include ".\Cardiogram1degree_AVB.h"
#include ".\Cardiogram2degree_AVBI.h"
#include ".\Cardiogram2degree_AVBII.h"
#include ".\Cardiogram3degree_AVB.h"
#include ".\CardiogramIdiov.h"
#include ".\CardiogramA_flutt.h"
#include ".\CardiogramVFibr.h"
#include ".\CardiogramA_fib.h"
#include ".\CardiogramJunct.h"
#include ".\CardiogramV_tach.h"
#include ".\CardiogramV_flutt.h"
#include ".\CardiogramOthers.h"
#include ".\CardiogramTorsade_DP.h"
#include ".\CardiogramAsystole.h"
#include ".\CardiogramAgonale.h"
#include ".\CardiogramS_tach.h"
#include ".\CardiogramPace.h"

#include "..\common\EncodeConv.h"


namespace jysoft { namespace simulator { namespace ecg {

	CAdultCardiogramParamFactory::CAdultCardiogramParamFactory(const std::string &ecgResourcePath)
	{
		USES_CONVERSION;
		boost::format  fmt("%s\\cardiogram\\cardiogramDB.hlo");
		fmt % ecgResourcePath;
        StgOpenStorage(s2w(fmt.str()).c_str(),NULL,STGM_DIRECT_SWMR | STGM_READ | STGM_SHARE_DENY_NONE,0,0,&m_pStorages);

		m_pCurrCardiogramLeadsPtr  = NULL;
	}

	CAdultCardiogramParamFactory::~CAdultCardiogramParamFactory(void)
	{
		if( m_pStorages )
		{
			m_pStorages->Release();
		}
	}

	//创建对应的参数类
	ICardiogramLeads * CAdultCardiogramParamFactory::CreateCardiogramLeadsInstance( const CECGParams *ptrParam )
	{
		if(m_pCurrCardiogramLeadsPtr != NULL && ptrParam && (ptrParam->m_dwField & PM_BASICRHYTHM))
		{
			bool bExpress = m_pCurrCardiogramLeadsPtr->IsCanExpressCardiogramParam( ptrParam->m_eBasicRm, ptrParam->m_iHR );
			if(bExpress == true)
			{//能用原来的类表达
				short   sConduct = 0;     //传导设置
				if( ptrParam->m_dwField & PM_CONDUCT)
				{
					sConduct = ptrParam->m_sConduct;
				}
				short   sExtendParam = 0;  //扩展参数值
				if( ptrParam->m_dwField & PM_EXTEND )
				{
					sExtendParam = ptrParam->m_sExtendParam;
				}
				m_pCurrCardiogramLeadsPtr->LoadCardiogramLeadsParam(ptrParam->m_eBasicRm, ptrParam->m_iHR, sConduct, sExtendParam);
			}
			else
			{
				delete m_pCurrCardiogramLeadsPtr;
				m_pCurrCardiogramLeadsPtr = NULL;
			}
		}
		if(m_pCurrCardiogramLeadsPtr == NULL && ptrParam && (ptrParam->m_dwField & PM_BASICRHYTHM))
		{//找到能得到对应参数的类
			if(CCardiogramSinus::IsCanParamExpress(ptrParam->m_eBasicRm, ptrParam->m_iHR))
			{
				m_pCurrCardiogramLeadsPtr = new CCardiogramSinus( m_pStorages );
			}
			else if(CCardiogram1degree_AVB::IsCanParamExpress(ptrParam->m_eBasicRm, ptrParam->m_iHR))
			{
				m_pCurrCardiogramLeadsPtr = new CCardiogram1degree_AVB( m_pStorages );
			}
			else if(CCardiogram2degree_AVBI::IsCanParamExpress(ptrParam->m_eBasicRm, ptrParam->m_iHR))
			{
				m_pCurrCardiogramLeadsPtr = new CCardiogram2degree_AVBI( m_pStorages );
			}
			else if(CCardiogram2degree_AVBII::IsCanParamExpress(ptrParam->m_eBasicRm, ptrParam->m_iHR))
			{
				m_pCurrCardiogramLeadsPtr = new CCardiogram2degree_AVBII( m_pStorages );
			}
			else if( CCardiogram3degree_AVB::IsCanParamExpress(ptrParam->m_eBasicRm, ptrParam->m_iHR) )
			{
				m_pCurrCardiogramLeadsPtr = new CCardiogram3degree_AVB( m_pStorages );
			}
			else if(CCardiogramA_flutt::IsCanParamExpress(ptrParam->m_eBasicRm, ptrParam->m_iHR))
			{
				m_pCurrCardiogramLeadsPtr = new CCardiogramA_flutt( m_pStorages );
			}
			else if(CCardiogramA_fib::IsCanParamExpress(ptrParam->m_eBasicRm, ptrParam->m_iHR))
			{
				m_pCurrCardiogramLeadsPtr = new CCardiogramA_fib( m_pStorages );
			}
			else if(CCardiogramJunct::IsCanParamExpress(ptrParam->m_eBasicRm, ptrParam->m_iHR))
			{
				m_pCurrCardiogramLeadsPtr = new CCardiogramJunct( m_pStorages );
			}
			else if(CCardiogramOthers::IsCanParamExpress(ptrParam->m_eBasicRm, ptrParam->m_iHR))
			{
				m_pCurrCardiogramLeadsPtr = new CCardiogramOthers( m_pStorages );
			}
			else if( CCardiogramTorsade_DP::IsCanParamExpress(ptrParam->m_eBasicRm, ptrParam->m_iHR))
			{
				m_pCurrCardiogramLeadsPtr = new CCardiogramTorsade_DP( m_pStorages );
			}
			else if( CCardiogramAsystole::IsCanParamExpress(ptrParam->m_eBasicRm, ptrParam->m_iHR))
			{
				m_pCurrCardiogramLeadsPtr = new CCardiogramAsystole( m_pStorages );
			}
			else if(CCardiogramV_tach::IsCanParamExpress(ptrParam->m_eBasicRm, ptrParam->m_iHR))
			{
				m_pCurrCardiogramLeadsPtr = new CCardiogramV_tach( m_pStorages );
			}
			else if( CCardiogramV_flutt::IsCanParamExpress(ptrParam->m_eBasicRm, ptrParam->m_iHR))
			{
				m_pCurrCardiogramLeadsPtr = new CCardiogramV_flutt( m_pStorages );
			}
			else if( CCardiogramVFibr::IsCanParamExpress(ptrParam->m_eBasicRm, ptrParam->m_iHR))
			{
				m_pCurrCardiogramLeadsPtr = new CCardiogramVFibr( m_pStorages );
			}
			else if( CCardiogramS_tach::IsCanParamExpress(ptrParam->m_eBasicRm, ptrParam->m_iHR))
			{
				m_pCurrCardiogramLeadsPtr = new CCardiogramS_tach( m_pStorages );
			}
			else if(CCardiogramIdiov::IsCanParamExpress(ptrParam->m_eBasicRm, ptrParam->m_iHR) )
			{
				m_pCurrCardiogramLeadsPtr = new CCardiogramIdiov( m_pStorages );
			}
			else if(CCardiogramAgonale::IsCanParamExpress(ptrParam->m_eBasicRm, ptrParam->m_iHR) )
			{
				m_pCurrCardiogramLeadsPtr = new CCardiogramAgonale( m_pStorages );
			}
			else if(CCardiogramPace::IsCanParamExpress(ptrParam->m_eBasicRm, ptrParam->m_iHR) )
			{
				m_pCurrCardiogramLeadsPtr = new CCardiogramPace( m_pStorages );
			}

			short   sConduct = 0;     //传导设置
			if( ptrParam->m_dwField & PM_CONDUCT)
			{
				sConduct = ptrParam->m_sConduct;
			}
			short   sExtendParam = 0;  //扩展参数值
			if( ptrParam->m_dwField & PM_EXTEND )
			{
				sExtendParam = ptrParam->m_sExtendParam;
			}
			//以下添加的错误处理    hjg  2013.9.16 add
			if( !m_pCurrCardiogramLeadsPtr->LoadCardiogramLeadsParam(ptrParam->m_eBasicRm, ptrParam->m_iHR, sConduct, sExtendParam) )
			{
                BOOST_ASSERT( 0 );
				delete m_pCurrCardiogramLeadsPtr;
				m_pCurrCardiogramLeadsPtr = NULL;
			}
		}
		return m_pCurrCardiogramLeadsPtr;
	}
}}}
