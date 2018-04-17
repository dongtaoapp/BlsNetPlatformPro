#include <boost/lexical_cast.hpp>
#include <boost/assert.hpp>
#include ".\CardiogramJunctParam_I12.h"


using namespace std;
using namespace boost;
namespace jysoft { namespace simulator { namespace ecg {

	CCardiogramJunctParam_I12::CCardiogramJunctParam_I12(IStorage *pRootStorage )
							: CVirCardiogramParam()
	{
		m_pStorages  = pRootStorage;
	}

	CCardiogramJunctParam_I12::~CCardiogramJunctParam_I12(void)
	{
	}

	//加载参数值
    void CCardiogramJunctParam_I12::LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm,int uHR, short sConduct/*=0*/, short sExtendParam/*=0*/)
	{
		//各数值的含义：p段文件名；缩放时间；与开始位置间隔时间；R段文件名；缩放时间；水平间隔延伸时间；与开始位置间隔时间；T段文件名；缩放时间；水平间隔延伸时间；与开始位置间隔时间；周期时间
		string strParams[][12] = {
			//A 
            {"P.txt","1125","-1000","A_R.txt","1000","900","0","A_T.txt","2200","15900","1900","20000"},//30HR*
            {"P.txt","1125","-850","A_R.txt","1000","900","300","A_T.txt","2200","12600","2200","17000"},//35HR
            {"P.txt","1125","-700","A_R.txt","1000","900","600","A_T.txt","2200","10400","2400","15000"},//40HR
            {"P.txt","1125","-300","A_R.txt","1000","900","750","A_T.txt","2200","8200","2600","13000"},//45HR
            {"P.txt","1125","0","A_R.txt","1000","900","900","A_T.txt","2200","7000","2800","12000"}, //50HR*
            {"P.txt","1125","0","A_R.txt","1000","900","900","A_T.txt","2200","6000","2800","11000"}, //55HR
            {"Empty_Data.txt","0","0","A_R.txt","1000","900","0","A_T.txt","2200","5900","1900","10000"}, //60HR*
            {"Empty_Data.txt","0","0","A_R.txt","1000","900","0","A_T.txt","2200","5100","1900","9200"}, //65HR
            {"Empty_Data.txt","0","0","A_R.txt","1000","900","0","A_T.txt","2200","4500","1900","8600"}, //70HR*
            {"Empty_Data.txt","0","0","A_R.txt","1000","900","0","A_T.txt","2200","3900","1900","8000"}, //75HR
            {"Empty_Data.txt","0","0","A_R.txt","1000","900","0","A_T.txt","2200","3400","1900","7500"}, //80HR*
            {"Empty_Data.txt","0","0","A_R.txt","1000","900","0","A_T.txt","2200","2900","1900","7000"}, //85HR
            {"Empty_Data.txt","0","0","A_R.txt","1000","900","0","A_T.txt","2200","2500","1900","6600"}, //90HR
            {"Empty_Data.txt","0","0","A_R.txt","1000","900","0","A_T.txt","2200","1900","1900","6000"}, //100HR*
            {"P.txt","1125","-1000","A_R.txt","1000","900","0","A_T.txt","2200","1400","1900","5500"}, //110HR*
            {"P.txt","1125","-1000","A_R.txt","1000","900","0","A_T.txt","2200","1000","1900","5100"}, //120HR*
            {"P.txt","1125","-1000","A_R.txt","1000","900","0","A_T.txt","2200","500","1900","4600"}, //130HR
            {"P.txt","1125","-1000","A_R.txt","1000","900","0","A_T.txt","2200","200","1900","4300"}, //140HR*
            {"P.txt","1125","-1000","A_R.txt","1000","900","0","A_T.txt","2200","0","1900","4100"}, //150HR
            {"Empty_Data.txt","0","0","A_R.txt","1000","200","0","A_T.txt","1600","950","1200","3750"} //160HR*
		};
		int iHRStep = Get_HRStep(uHR);
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

		if(uHR == 50)
			m_setParams["P_FileName_50"] = "P.txt";
		else
			m_setParams["P_FileName_50"] = "Empty_Data.txt";
		m_eQRS = eQRS;
		m_eRhythm = eRhythm;
		m_uHR     = uHR;
		//end hjg 2006/3/29
	}

	//产生心电时，血氧的启动时间
	bool CCardiogramJunctParam_I12::GetSpO2BeginTimeToCardiogram(/*out*/long &lBeginTime, /*out*/long &lCycleTime)
	{
		lBeginTime = 0;
		string strKey, strValue;
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

    int CCardiogramJunctParam_I12::Get_HRStep(int uHR)
	{
		int iStep = 0;
		if(uHR < 90)
			iStep = uHR/5-6;
		else
			iStep = uHR/10-9+12;
		return iStep;
	}
}}}
