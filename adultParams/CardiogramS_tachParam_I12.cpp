#include <boost/lexical_cast.hpp>
#include <boost/assert.hpp>
#include ".\CardiogramS_tachParam_I12.h"


using namespace std;
using namespace boost;
namespace jysoft { namespace simulator { namespace ecg {

	CCardiogramS_tachParam_I12::CCardiogramS_tachParam_I12( IStorage *pRootStorage )
						: CVirCardiogramParam()
	{
		m_pStorages  = pRootStorage;
	}

	CCardiogramS_tachParam_I12::~CCardiogramS_tachParam_I12(void)
	{
	}

	//加载参数值
    void CCardiogramS_tachParam_I12::LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm, int uHR, short sConduct/*=0*/, short sExtendParam/*=0*/)
	{
		if( uHR < 160 )
		{
			uHR = 160;
		}
		else if( uHR > 280 )
		{
			uHR  = 280;
		}
		//各数值的含义：p段文件名；缩放时间；与开始位置间隔时间；R段文件名；缩放时间；水平间隔延伸时间；与开始位置间隔时间；T段文件名；缩放时间；水平间隔延伸时间；与开始位置间隔时间；周期时间
		string strParams[][12] = {
            {"Empty_Data.txt","0","0","A_R.txt","1000","200","0","A_T.txt","1600","125","1200","3750"}, //160HR
            {"Empty_Data.txt","0","0","A_R.txt","1000","200","0","A_T.txt","1750","0","1200","3500"}, //170HR
            {"Empty_Data.txt","0","0","A_R.txt","1000","200","0","A_T.txt","1750","0","1200","3295"}, //180HR
            {"Empty_Data.txt","0","0","A_R.txt","1000","200","0","A_T.txt","1800","0","1200","3150"}, //190HR
            {"Empty_Data.txt","0","0","A_R.txt","1000","200","0","A_T.txt","1900","0","1200","3000"}, //200HR
            {"Empty_Data.txt","0","0","A_R.txt","1000","200","0","A_T.txt","1900","0","1200","2850"}, //210HR
            {"Empty_Data.txt","0","0","A_R.txt","1000","200","0","A_T.txt","1900","0","1200","2700"}, //220HR
            {"Empty_Data.txt","0","0","A_R.txt","1000","200","0","A_T.txt","1900","0","1200","2600"}, //230HR
            {"Empty_Data.txt","0","0","A_R.txt","1000","200","0","A_T.txt","1900","0","1200","2500"}, //240HR
            {"Empty_Data.txt","0","0","A_R.txt","1000","200","0","A_T.txt","1900","0","1200","2400"}, //250HR
            {"Empty_Data.txt","0","0","A_R.txt","1000","200","0","A_T.txt","1900","0","1200","2300"}, //260HR
            {"Empty_Data.txt","0","0","A_R.txt","1000","200","0","A_T.txt","1900","0","1200","2200"}, //270HR
            {"Empty_Data.txt","0","0","A_R.txt","1000","200","0","A_T.txt","1900","0","1200","2150"}  //280HR
		};
		int iHRStep = ((uHR / 10) * 10 - 160)/10;

		string *pAimPtr = strParams[iHRStep];
		//设置刷新数据的范围
		if(m_eQRS == QRS_None)
		{
			m_setParams.clear();//移除所有的参数
			m_eRefurbishDataRange = RD_LoadConfigFile;
			m_setParams["ConfigFileName"] = "MakeFile.txt";
		}
		else if(m_eQRS != eQRS || m_uHR != uHR)
		{
			m_eRefurbishDataRange = RD_AllData;
		}

		if( m_uHR != uHR || m_eQRS != eQRS )
		{
			m_setParams["HR"] = lexical_cast<string>(uHR);
		}

		SetP_FileName(pAimPtr);
		SetP_ZoomTime(pAimPtr);
		SetP_ExtendTime(pAimPtr);
		SetR_FileName(pAimPtr);
		SetR_ZoomTime(pAimPtr);
		SetR_ExtendTime(pAimPtr);
		SetR_LExtendTime(pAimPtr);
		SetT_FileName(pAimPtr);
		SetT_ZoomTime(pAimPtr);
		SetT_ExtendTime(pAimPtr);
		SetT_LExtendTime(pAimPtr);
		Set_CycleTime(pAimPtr);

		m_eQRS = eQRS;
		m_eRhythm = eRhythm;
		m_uHR     = uHR;
		//end hjg 2010/11/4
	}

	//返回Q波到S波时间段的时间（单位：0.1毫秒）
	int CCardiogramS_tachParam_I12::GetPhaseTimeFromQtoS()
	{
        string    strRZoomTime("0");
		GetParamValue("R_ZoomTime", /*out*/strRZoomTime);
        string    strRExtendTime("0");
		GetParamValue("R_ExtendTime", /*out*/strRExtendTime);
		int  nRtnTime = 0;
		if( m_uHR <= 200 )
		{
			nRtnTime = lexical_cast<int>(strRZoomTime)/2+lexical_cast<int>(strRExtendTime);
		}
		else
		{
			nRtnTime = lexical_cast<int>(strRZoomTime)/3 + lexical_cast<int>(strRExtendTime);
		}
		return nRtnTime;
	}

	//返回S波到T波时间段的时间（单位：0.1毫秒）
	int CCardiogramS_tachParam_I12::GetPhaseTimeFromStoT()
	{	
        string    strTZoomTime("0");
		GetParamValue("T_ZoomTime", /*out*/strTZoomTime);
		int  nRtnTime = lexical_cast<int>(strTZoomTime);
		if( m_uHR > 200 )
		{
			nRtnTime  = 1200;
		}
		return nRtnTime;
	}


	//产生心电时，血氧的启动时间
	bool CCardiogramS_tachParam_I12::GetSpO2BeginTimeToCardiogram(/*out*/long &lBeginTime, /*out*/long &lCycleTime)
	{
		lBeginTime = 0;
		std::string  strKey, strValue;
		strKey = "P_ZoomTime";
		if( GetParamValue(strKey, strValue) )
		{
			lBeginTime += lexical_cast<long>(strValue);
		}
		else
		{
            BOOST_ASSERT(0);
			return false;
		}
		strKey = "P_ExtendTime";
		if( GetParamValue(strKey, strValue) )
		{
			lBeginTime += lexical_cast<long>(strValue);
		}
		else
		{
            BOOST_ASSERT(0);
			return false;
		}
		strKey = "P_ExtendTime";
		if( GetParamValue(strKey, strValue) )
		{
			lBeginTime += lexical_cast<long>(strValue);
		}
		else
		{
            BOOST_ASSERT(0);
			return false;
		}
		strKey = "R_ZoomTime";
		if( GetParamValue(strKey, strValue) )
		{
			lBeginTime += lexical_cast<long>(strValue);
		}
		else
		{
            BOOST_ASSERT(0);
			return false;
		}
		lCycleTime = (long)GetCycleTime();
		return true;
	}

}}}
