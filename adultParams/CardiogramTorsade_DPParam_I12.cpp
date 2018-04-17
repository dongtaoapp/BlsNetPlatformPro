#include <boost/lexical_cast.hpp>
#include ".\CardiogramTorsade_DPParam_I12.h"


namespace jysoft { namespace simulator { namespace ecg {

	CCardiogramTorsade_DPParam_I12::CCardiogramTorsade_DPParam_I12(IStorage *pRootStorage )
							: CVirCardiogramParam()
	{
		m_pStorages = pRootStorage;
	}

	CCardiogramTorsade_DPParam_I12::~CCardiogramTorsade_DPParam_I12(void)
	{
	}

	//加载参数值
    void CCardiogramTorsade_DPParam_I12::LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm,int uHR, short sConduct/*=0*/, short sExtendParam/*=0*/)
	{
		//段名称；时间
		static std::string strParams[][2] = {
			//----------------------------------------------------------------------
            {"Torsade_DP.txt","39100"}
		};
		std::string *pAimPtr = strParams[0];
		//设置刷新数据的范围
		if(m_eQRS == QRS_None)
		{
			m_setParams.clear();//移除所有的参数
			m_eRefurbishDataRange = RD_LoadConfigFile;
			m_setParams["ConfigFileName"] = "MakeFile.txt";
		}
		m_setParams["HR"] = "0";

		m_setParams["Seg_FileName"] = pAimPtr[0];
		m_setParams["CycleTime"] = pAimPtr[1];
		m_setParams["ZoomTime"] = pAimPtr[1];
		m_eQRS = eQRS;
		m_eRhythm = eRhythm;
		m_uHR     = uHR;
		//end hjg 2006/3/29
	}
}}}
