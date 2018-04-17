#include <boost/lexical_cast.hpp>
#include <boost/assert.hpp>
#include ".\CardiogramV_fluttParam_I12.h"


namespace jysoft { namespace simulator { namespace ecg {

	CCardiogramV_fluttParam_I12::CCardiogramV_fluttParam_I12( IStorage *pRootStorage )
						: CVirCardiogramParam()
	{
		m_pStorages  = pRootStorage;
	}

	CCardiogramV_fluttParam_I12::~CCardiogramV_fluttParam_I12(void)
	{
	}

	//加载参数值
    void CCardiogramV_fluttParam_I12::LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm,int uHR, short sConduct/*=0*/, short sExtendParam/*=0*/)
	{
		int iHRStep = Get_HRStep(uHR);
		//段名称；时间
		static std::string strParams[][2] = {
			//--------------
            {"V_flutt.txt","3000"},  //200HR
            {"V_flutt.txt","2900"},  //210HR
            {"V_flutt.txt","2700"},  //220HR
            {"V_flutt.txt","2600"},  //230HR
            {"V_flutt.txt","2500"},  //240HR
            {"V_flutt.txt","2400"},  //250HR
            {"V_flutt.txt","2300"},  //260HR
            {"V_flutt.txt","2200"},  //270HR
            {"V_flutt.txt","2150"},  //280HR
            {"V_flutt.txt","2050"},  //290HR
            {"V_flutt.txt","2000"}   //300HR
		};
		std::string *pAimPtr = strParams[iHRStep];
		//设置刷新数据的范围
		if(m_eQRS == QRS_None)
		{
			m_setParams.clear();//移除所有的参数
			m_eRefurbishDataRange = RD_LoadConfigFile;
			m_setParams["ConfigFileName"] = "MakeFile.txt";
		}

		if( m_uHR != uHR || m_eQRS != eQRS )
		{
			m_setParams["HR"] = boost::lexical_cast<std::string>(uHR);

			if( m_eRefurbishDataRange != RD_LoadConfigFile )
			{
				m_eRefurbishDataRange = RD_AllData;
			}
		}

		m_setParams["Seg_FileName"] = pAimPtr[0];
		m_setParams["CycleTime"] = pAimPtr[1];
		m_setParams["ZoomTime"] = pAimPtr[1];
		m_eQRS = eQRS;
		m_eRhythm = eRhythm;
		m_uHR     = uHR;
		//end hjg 2006/3/29
	}

	//产生心电时，血氧的启动时间
	bool CCardiogramV_fluttParam_I12::GetSpO2BeginTimeToCardiogram(/*out*/long &lBeginTime, /*out*/long &lCycleTime)
	{
		lBeginTime = 0;
		std::string  strKey, strValue;
		strKey = "ZoomTime";
		if( GetParamValue(strKey, strValue) )
		{
			lBeginTime += boost::lexical_cast<long>(strValue);
		}
		else
		{
            BOOST_ASSERT(0);
			return false;
		}
		lCycleTime = (long)GetCycleTime();
		return true;
	}

    int CCardiogramV_fluttParam_I12::Get_HRStep(int uHR)
	{
		if( uHR < 200 )
			uHR = 200;
		if( uHR > 300 )
			uHR = 300;
		int iStep = uHR/10-20;
		return iStep < 0 ? 0 : iStep;
	}
}}}
