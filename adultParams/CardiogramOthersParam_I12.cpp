#include <boost/lexical_cast.hpp>
#include ".\CardiogramOthersParam_I12.h"


using namespace std;
using namespace boost;
namespace jysoft { namespace simulator { namespace ecg {

	CCardiogramOthersParam_I12::CCardiogramOthersParam_I12( IStorage *pRootStorage )
						: CVirCardiogramParam()
	{
		m_pStorages  = pRootStorage;
	}

	CCardiogramOthersParam_I12::~CCardiogramOthersParam_I12(void)
	{
	}

	//加载参数值
    void CCardiogramOthersParam_I12::LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm,int uHR, short sConduct/*=0*/, short sExtendParam/*=0*/)
	{
		int iStep = 0;
		switch(eRhythm)
		{
		case BR_Ventr_Standstill:
			iStep = 0;
			break;
		case BR_Die:
			iStep = 1;
			break;
		}
		//段名称；时间
		string strParams[][2] = {
            {"Ventr_Standstill.txt","7600"},
            {"Die.txt","7600"}
		};
		string *pAimPtr = strParams[iStep];
		//设置刷新数据的范围
		if(m_eQRS == QRS_None)
		{
			m_setParams.clear();//移除所有的参数
			m_eRefurbishDataRange = RD_LoadConfigFile;
			m_setParams["ConfigFileName"] = "MakeFile.txt";
		}
		else if(m_eRhythm != eRhythm || m_eQRS != eQRS)
		{
			if(!(m_eRhythm == eRhythm && (eRhythm == BR_AgonalRhythm || eRhythm == BR_Ventr_Standstill )))
				m_eRefurbishDataRange = RD_AllData;
		}

		if( m_uHR != uHR || m_eQRS != eQRS )
		{
			m_setParams["HR"] = lexical_cast<string>(0);
		}

		m_setParams["Seg_FileName"] = pAimPtr[0];
		m_setParams["CycleTime"] = pAimPtr[1];
		m_setParams["ZoomTime"] = pAimPtr[1];
		m_eQRS = eQRS;
		m_eRhythm = eRhythm;
		m_uHR     = uHR;
		//end hjg 2006/3/29
	}
}}}
