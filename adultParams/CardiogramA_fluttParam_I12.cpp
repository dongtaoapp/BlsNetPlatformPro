#include <boost/lexical_cast.hpp>
#include <boost/assert.hpp>
#include ".\CardiogramA_fluttParam_I12.h"


using namespace std;
using namespace boost;
namespace jysoft { namespace simulator { namespace ecg {

	CCardiogramA_fluttParam_I12::CCardiogramA_fluttParam_I12(IStorage *pRootStorage )
						: CVirCardiogramParam()
	{
		m_pStorages  = pRootStorage;
	}

	CCardiogramA_fluttParam_I12::~CCardiogramA_fluttParam_I12(void)
	{
	}

	//加载参数值
    void CCardiogramA_fluttParam_I12::LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm, int uHR, short sConduct/*=0*/, short sExtendParam/*=0*/)
	{
		int iHRStep = 0;
		switch( sConduct )
		{
		case 5: //60\5:1
			{
				uHR  = 60;
				iHRStep  = 0;
				break;
			}
		case 4: //75\4:1
			{
				uHR  = 75;
				iHRStep  = 1;
				break;
			}
		case 3: //100\3:1
			{
				uHR  = 100;
				iHRStep  = 2;
				break;
			}
		case 2: //150\2:1
			{
				uHR  = 150;
				iHRStep  = 3;
				break;
			}
		default:
			{
				if( uHR <= 60 || uHR <= 70 ) 
				{ //60\5:1
					uHR     = 60;
					iHRStep = 0;
				}
				else if ( uHR > 70 && uHR <= 90 ) 
				{// 75\4:1
					uHR     = 75;
					iHRStep = 1;
				}
				else if ( uHR > 90 && uHR <= 120 ) 
				{//100\3:1
					uHR     = 100;
					iHRStep = 2;
				}
				else 
				{//150\2:1
					uHR     = 150;
					iHRStep = 3;
				}
				break;
			}
		}

		//各数值的含义：R段文件名；缩放时间；负方向水平间隔延伸时间；水平间隔延伸时间；T段文件名；缩放时间；水平间隔延伸时间；基数据段名称；基数据段重复复制次数；周期时间
		std::string strParams[][10] = {
            {"A_R.txt","1000","1900","900","A_T.txt","2200","4000","BasicSeg.txt","5","10000"},//60HR
            {"A_R.txt","1000","1900","900","A_T.txt","2200","2000","BasicSeg.txt","4","8000"},//75HR
            {"A_R.txt","1000","1900","900","A_T.txt","2200","700","BasicSeg.txt","3","6000"},//100HR
            {"A_R.txt","1000","1900","350","A_T.txt","1800","0","BasicSeg.txt","2","4000"}//150HR
		};
		string *pAimPtr = strParams[iHRStep];

		//设置刷新数据的范围
		if(m_eQRS == QRS_None)
		{
			m_setParams.clear();//移除所有的参数
			m_eRefurbishDataRange = RD_LoadConfigFile;
			m_setParams["ConfigFileName"] = "MakeFile.txt";
		}
		else if(m_eQRS != eQRS)
		{
			m_eRefurbishDataRange = RD_AllData;
		}
		else if(m_uHR != uHR)
		{
			m_eRefurbishDataRange = RD_OpSegmentData;
		}

		if( m_uHR != uHR || m_eQRS != eQRS )
		{
            m_setParams["HR"] = lexical_cast<std::string>(uHR);
		}

		SetR_FileName(pAimPtr);
		SetR_ZoomTime(pAimPtr);
		SetR_LExtendTime(pAimPtr);
		SetR_RExtendTime(pAimPtr);
		SetT_FileName(pAimPtr);
		SetT_ZoomTime(pAimPtr);
		SetT_ExtendTime(pAimPtr);
		Set_CycleTime(pAimPtr);
		m_setParams["Seg_FileName"] = pAimPtr[7];
		m_setParams["Seg_CopyNum"] = pAimPtr[8];

		m_eQRS = eQRS;
		m_eRhythm = eRhythm;
		m_uHR     = uHR;
		//end hjg 2006/4/6
	}

	bool CCardiogramA_fluttParam_I12::GetParamValue(const std::string &strKey, const std::string &strParam, std::string &strValue)
	{
        if(strKey == "Seg_CopyIntervalTime")
		{
            if(strParam == "1" || strParam == "2" || strParam == "5" || strParam == "6")
				strValue = "-200";
			else
				strValue = "0";
		}
		return true;
	}

	//产生心电时，血氧的启动时间
	bool CCardiogramA_fluttParam_I12::GetSpO2BeginTimeToCardiogram(/*out*/long &lBeginTime, /*out*/long &lCycleTime)
	{
		lBeginTime = 0;
		string  strKey, strValue;
		strKey = "R_ZoomTime";
		if( CVirCardiogramParam::GetParamValue(strKey, strValue) )
		{
			lBeginTime += lexical_cast<long>(strValue);
		}
		else
		{
            BOOST_ASSERT(0);
			return false;
		}
        strKey = "R_LExtentTime";
		if( CVirCardiogramParam::GetParamValue(strKey, strValue) )
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
