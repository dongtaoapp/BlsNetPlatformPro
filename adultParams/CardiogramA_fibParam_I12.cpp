#include <boost/lexical_cast.hpp>
#include <boost/assert.hpp>
#include ".\CardiogramA_fib.h"
#include ".\CardiogramA_fibParam_I12.h"


using namespace std;
using namespace boost;
namespace jysoft { namespace simulator { namespace ecg {

	CCardiogramA_fibParam_I12::CCardiogramA_fibParam_I12(CCardiogramA_fib *pAFibEcg, IStorage *pRootStorage )
							: CVirCardiogramParam()
	{
		m_dwSumRunTime = 0;
		m_nSumBasicSegTime = 0;
		m_nBasicSeg_LExtentTime = 0;
		m_pStorages     = pRootStorage;
		m_pAFibEcg      = pAFibEcg;
	}

	CCardiogramA_fibParam_I12::~CCardiogramA_fibParam_I12(void)
	{
	}

    void CCardiogramA_fibParam_I12::GetNormalA_fibParams(/*out*/std::string *pParams, int uHR)
	{
		//各数值的含义：R段文件名；缩放时间；水平间隔延伸时间；T段文件名；缩放时间；水平间隔延伸时间,周期时间;
		string strNormalParams[][7] = {
            {"A_R.txt","1000","900","A_T.txt","2200","6400","12000"},//50HR
            {"A_R.txt","1000","900","A_T.txt","2200","4400","10000"},//60HR
            {"A_R.txt","1000","900","A_T.txt","2200","3000","8600"},//70HR
            {"A_R.txt","1000","900","A_T.txt","2200","1900","7500"},//80HR
            {"A_R.txt","1000","900","A_T.txt","2200","1000","6600"},//90HR
            {"A_R.txt","1000","900","A_T.txt","2200","400","6000"},//100HR
            {"A_R.txt","1000","900","A_T.txt","2200","100","5700"},//105HR
            {"A_R.txt","1000","825","A_T.txt","2200","0","5625"},  //110HR
            {"A_R.txt","1000","500","A_T.txt","2000","0","5375"},  //115HR
            {"A_R.txt","925","350","A_T.txt","1800","425","5050"}, //120HR
            {"A_R.txt","925","350","A_T.txt","1800","300","4825"}, //125HR
            {"A_R.txt","925","350","A_T.txt","1650","225","4600"}  //130HR
		};
		int  iHRStep  = uHR/10 - 5;
		if( uHR > 100 )
		{
			iHRStep = ((uHR / 5) * 5 - 100)/5 + 5;
		}
		for( int n = 0; n < 7; ++n )
		{
			pParams[n] = strNormalParams[iHRStep][n];
		}
		if( (uHR <= 100 && (uHR % 10) != 0) || (uHR > 100 && (uHR % 5) != 0) )
		{
			int nContrastCycleTime = lexical_cast<int>( pParams[6] );
			int nCycleTime = ((600000 / uHR) / 50) * 50;  //时间单位为0.1毫秒；周期时间为50的倍数
			int nExtendTime = lexical_cast<int>( pParams[5] );
			nExtendTime    = nExtendTime - ( nContrastCycleTime - nCycleTime);
			pParams[5] = lexical_cast<string>(nExtendTime);
		}
	}

    void CCardiogramA_fibParam_I12::GetFastA_fibParams(/*out*/string *pParams, int uHR)
	{
		//各数值的含义：R段文件名；缩放时间；水平间隔延伸时间；T段文件名；缩放时间；水平间隔延伸时间,周期时间;
		string strFastParams[][7] = {
            {"A_R.txt","925","350","A_T.txt","1650","225","4600"},//130HR
            {"A_R.txt","925","350","A_T.txt","1650","175","4450"},//135HR
            {"A_R.txt","925","350","A_T.txt","1650","125","4275"},//140HR
            {"A_R.txt","925","350","A_T.txt","1600","125","4150"},//145HR
            {"A_R.txt","925","275","A_T.txt","1550","125","4000"},//150HR
            {"A_R.txt","850","200","A_T.txt","1500","125","3900"},//155HR
            {"A_R.txt","850","150","A_T.txt","1500","125","3750"},//160HR
            {"A_R.txt","850","150","A_T.txt","1500","100","3600"},//165HR
            {"A_R.txt","800","200","A_T.txt","1600","0","3500"},//170HR
            {"A_R.txt","800","200","A_T.txt","1750","0","3425"},//175HR
            {"A_R.txt","800","200","A_T.txt","1750","0","3295"},//180HR
            {"A_R.txt","900","200","A_T.txt","1800","0","3225"},//185HR
            {"A_R.txt","900","200","A_T.txt","1850","0","3150"},//190HR
            {"A_R.txt","900","200","A_T.txt","1900","0","3075"},//195HR
            {"A_R.txt","900","200","A_T.txt","1900","0","3000"} //200HR
		};
		if( uHR <= 200 )
		{
			int  iHRStep  = ((uHR / 5) * 5 - 130)/5;
			for( int n = 0; n < 7; ++n )
			{
				pParams[n] = strFastParams[iHRStep][n];
			}
			if( (uHR <= 200 && (uHR % 5) != 0) )
			{
				int nContrastCycleTime = lexical_cast<int>( pParams[6] );
				int nCycleTime = ((600000 / uHR) / 50) * 50;     //时间单位为0.1毫秒；周期时间为50的倍数
				int nExtendTime = lexical_cast<int>( pParams[5] );
				nExtendTime    = nExtendTime - ( nContrastCycleTime - nCycleTime);
				if( nExtendTime < 0 )
				{
					nExtendTime = 0;
				}
				pParams[5] = lexical_cast<string>(nExtendTime);
			}
		}
		else
		{
			int iHRStep = ((uHR / 10) * 10 - 200)/10 + 14;
			for( int n = 0; n < 7; ++n )
			{
				pParams[n] = strFastParams[iHRStep][n];
			}
		}
	}

	//加载参数值
    void CCardiogramA_fibParam_I12::LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm, int uHR, short sConduct/*=0*/, short sExtendParam/*=0*/)
	{
		if( uHR < 50 )
			uHR = 50;
		if( uHR > 200 )
			uHR = 200;
		//-----------------------------------------------------------------------------------------------------------------
		string pAimPtr[7];
		if( uHR <= 130 )
		{
			GetNormalA_fibParams(pAimPtr, uHR);
		}
		else
		{
			GetFastA_fibParams(pAimPtr, uHR);
		}
		//设置刷新数据的范围
		if(m_eQRS == QRS_None)
		{
			m_eRefurbishDataRange = RD_LoadConfigFile;
			m_setParams.clear();//移除所有的参数
			m_setParams["ConfigFileName"] = "MakeFile.txt";
			m_dwSumRunTime = 0;//总运行时间设为0
			m_nSumBasicSegTime = 0;
		}
		else if(m_eQRS != eQRS)
		{
			m_eRefurbishDataRange = RD_AllData;
			m_dwSumRunTime = 0;//总运行时间设为0
			m_nSumBasicSegTime = 0;
		}
		else
		{//其它的情况都必须修改此范围的数据
			if(uHR != m_uHR && (uHR == 30 || m_uHR == 30))
				m_eRefurbishDataRange = RD_AllData;
			else
				m_eRefurbishDataRange = RD_OpSegmentData;
		};
		if( m_uHR != uHR || m_eQRS != eQRS )
		{
			m_setParams["HR"] = lexical_cast<string>(uHR);
		}
		//===================================================================
		m_eQRS = eQRS;
		m_eRhythm = eRhythm;
		m_uHR     = uHR;
		Set_CycleTime(NULL);//设定时间
		SetR_FileName(pAimPtr);
		SetR_ZoomTime(pAimPtr);
		SetR_RExtendTime(pAimPtr);
		SetT_FileName(pAimPtr);
		SetT_ZoomTime(pAimPtr);
		SetT_ExtendTime(pAimPtr);
		SetR_LExtendTime(NULL);
		m_setParams["Seg_FileName"] = "Basic_Seg.txt";

		//===================================================================
		m_dwSumRunTime += lexical_cast<long>(m_setParams["CycleTime"]);
		//end hjg 2006/4/6
	}

	//产生心电时，血氧的启动时间
	bool CCardiogramA_fibParam_I12::GetSpO2BeginTimeToCardiogram(/*out*/long &lBeginTime, /*out*/long &lCycleTime)
	{
		lBeginTime = 0;
		string strKey, strValue;

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
		strKey = "R_LExtentTime";
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

	bool CCardiogramA_fibParam_I12::GetParamValue(const std::string &strKey, const std::string &strParam, std::string &strValue)
	{
        if(strKey == "Seg_CopyIntervalTime")
		{
			switch(m_uHR)
			{
			case 50:
				{
					strValue = "100";
					break;
				}
			default:
				{
					strValue = "0";
					break;
				}
			}
		}
		return true;
	}

	bool CCardiogramA_fibParam_I12::GetParamValue(const std::string &strKey, std::string &strValue)
	{
        if(strKey == "Seg_CopyNum")
		{
			string strCycleTime;
            GetParamValue("CycleTime", strCycleTime);
			//当前的周期时间
			int iCurrCycleTime = lexical_cast<int>( strCycleTime );
			//设置基数据段向前延伸的时间
			m_nBasicSeg_LExtentTime = m_nSumBasicSegTime - (m_dwSumRunTime - iCurrCycleTime);
            BOOST_ASSERT(m_nBasicSeg_LExtentTime >= 0);
			string strIntervalTime;
			GetParamValue("Seg_CopyIntervalTime","",strIntervalTime);
			int iIntervalTime = lexical_cast<int>(strIntervalTime);
			int iCoyNum = 0;
			if(m_dwSumRunTime > m_nSumBasicSegTime)
			{
				if((m_dwSumRunTime - m_nSumBasicSegTime)%(iIntervalTime+14000) != 0)
					iCoyNum = (m_dwSumRunTime - m_nSumBasicSegTime)/(iIntervalTime+14000) + 1;
				else
					iCoyNum = (m_dwSumRunTime - m_nSumBasicSegTime)/(iIntervalTime+14000);
			}
			strValue = lexical_cast<string>(iCoyNum);
			m_nSumBasicSegTime += iCoyNum * (iIntervalTime+14000);
		}
        else if(strKey == "BasicSeg_LExtentTime")
		{
			strValue = lexical_cast<string>(m_nBasicSeg_LExtentTime);
		}
		else
		{
			CVirCardiogramParam::GetParamValue(strKey,strValue);
		}
		//2018.2.26 add hjg
		if( strValue.empty() )
		{
			strValue = "0";
		}
		return true;
	}

	void CCardiogramA_fibParam_I12::SetR_LExtendTime(const std::string *pStrParams)
	{
		std::string strCycleTime,strR_Time,strR_ExtendTime,strT_Time,strT_ExtendTime;
		strCycleTime = m_setParams["CycleTime"];
		strR_Time    = m_setParams["R_ZoomTime"];
		strR_ExtendTime = m_setParams["R_RExtendTime"];
		strT_Time    = m_setParams["T_ZoomTime"];
		strT_ExtendTime = m_setParams["T_ExtendTime"];
		int iT_RExtendTime = lexical_cast<int>(strR_ExtendTime);
		int iCycleTime = lexical_cast<int>(strCycleTime);
		int iTime = lexical_cast<int>(strR_Time);
		iTime += iT_RExtendTime;
		iTime += lexical_cast<int>(strT_Time);
		iTime += lexical_cast<int>(strT_ExtendTime);

		int iR_LExtendTime = iCycleTime - iTime;
		if(iR_LExtendTime <= 0)
			iR_LExtendTime = 1000;
		if(iR_LExtendTime > 9000)
		{
			iR_LExtendTime = iR_LExtendTime/2;
		}
		iTime += iR_LExtendTime;
		if(iTime >= iCycleTime)
			iTime = iT_RExtendTime;
		else
			iTime = iT_RExtendTime + (iCycleTime-iTime);
		strR_ExtendTime = lexical_cast<string>(iTime);
		m_setParams["R_RExtendTime"] = strR_ExtendTime;
		m_setParams["R_LExtentTime"] = lexical_cast<string>(iR_LExtendTime);
	}

	void CCardiogramA_fibParam_I12::Set_CycleTime(const std::string * pStrParams)
	{
		int  iCycleTime = m_pAFibEcg->GetCycleTime();
		m_setParams["CycleTime"] = lexical_cast<string>(iCycleTime);
		//设定心率次数
		m_setParams["HR"] = lexical_cast<string>(600000/iCycleTime);
	}

}}}
