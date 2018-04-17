#include <boost/lexical_cast.hpp>
#include <boost/assert.hpp>
#include ".\Cardiogram3degree_AVBParam_I12.h"


using namespace std;
using namespace boost;
namespace jysoft { namespace simulator { namespace ecg {

	CCardiogram3degree_AVBParam_I12::CCardiogram3degree_AVBParam_I12(IStorage *pRootStorage )
								: CVirCardiogramParam()
	{
		m_dwSumRunTime          = 0;
		m_nSumBasicSegTime      = 0;
		m_nBasicSeg_LExtentTime = 0;
		m_pStorages  = pRootStorage;
	}

	CCardiogram3degree_AVBParam_I12::~CCardiogram3degree_AVBParam_I12(void)
	{
	}

	//加载参数值
    void CCardiogram3degree_AVBParam_I12::LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm,int uHR, short sConduct/*=0*/, short sExtendParam/*=0*/)
	{
		if( uHR < 10 )
		{
			uHR   = 10;
		}
		else if( uHR > 60 )
		{
			uHR   = 60;
		}
		int iHRStep = uHR/10 - 1;
		int iMove   = uHR%10;

		//各数值的含义： 
		std::string strParams[][4] = {
            {"A_Segment.txt","20000","BasicSeg_Name.txt","60000"},  //10
            {"A_Segment.txt","18000","BasicSeg_Name.txt","30000"},  //20
            {"A_Segment.txt","15200","BasicSeg_Name.txt","20000"},  //30
            {"A_Segment.txt","11200","BasicSeg_Name.txt","16000"},  //40
            {"A_Segment.txt","7200","BasicSeg_Name.txt","12000"},   //50
            {"A_Segment.txt","6950","BasicSeg_Name.txt","11750"},   //51
            {"A_Segment.txt","6700","BasicSeg_Name.txt","11500"},   //52
            {"A_Segment.txt","6500","BasicSeg_Name.txt","11300"},   //53
            {"A_Segment.txt","6300","BasicSeg_Name.txt","11100"},   //54
            {"A_Segment.txt","6250","BasicSeg_Name.txt","10900"},  //55
            {"A_Segment.txt","6200","BasicSeg_Name.txt","10700"},  //56
            {"A_Segment.txt","6150","BasicSeg_Name.txt","10500"},  //57
            {"A_Segment.txt","6100","BasicSeg_Name.txt","10350"},  //58
            {"A_Segment.txt","6050","BasicSeg_Name.txt","10150"},  //59
            {"A_Segment.txt","5975","BasicSeg_Name.txt","10000"}   //60
		};
		string *pAimPtr = NULL;
		if(uHR <= 50)
		{
			pAimPtr = strParams[(int(eQRS) - 1)*13 + iHRStep];
			if(iMove!=0)
			{
				int nCycleTime = ((600000 / uHR) / 50) * 50; 
				int nExtendTime = lexical_cast<int>( pAimPtr[1] );
				nExtendTime    = nExtendTime - ( lexical_cast<int>( pAimPtr[3] ) - nCycleTime);
				pAimPtr[1] = lexical_cast<string>(nExtendTime);
				pAimPtr[3] = lexical_cast<string>(nCycleTime);
			}
		}
		else
		{
			iHRStep = 2+(uHR-50);
			pAimPtr = strParams[(int(eQRS) - 1)*13 + iHRStep];
		}

		//设置刷新数据的范围
		if(m_eQRS == QRS_None)
		{
			m_eRefurbishDataRange = RD_LoadConfigFile;
			m_setParams.clear();//移除所有的参数
			m_setParams["ConfigFileName"] = "MakeFile.txt";
			m_dwSumRunTime = 0;//总运行时间设为0
			m_nSumBasicSegTime = 0;
			m_setParams["Seg_FileName"] = "Zero.txt";
		}
		else
		{//其它的情况都必须修改此范围的数据
			if(m_setParams["Seg_FileName"] != pAimPtr[0])
				m_eRefurbishDataRange = RD_AllData;
			else
				m_eRefurbishDataRange = RD_OpSegmentData;
			m_setParams["Seg_FileName"] = pAimPtr[0];
		};
		if( m_uHR != uHR || m_eQRS != eQRS )
		{
			m_setParams["HR"] = lexical_cast<string>(uHR);
		}
		//-----------------------------------------------------------
		m_setParams["ExtendTime"] = pAimPtr[1];
		m_setParams["BasicSeg_FileName"] = pAimPtr[2];
		m_setParams["CycleTime"] = pAimPtr[3];
		//------------------------------------------------------------
		m_eQRS = eQRS;
		m_eRhythm = eRhythm;
		m_uHR     = uHR;
		//============================================================
		m_dwSumRunTime += lexical_cast<int>(m_setParams["CycleTime"]);
	}

	bool CCardiogram3degree_AVBParam_I12::GetParamValue(const std::string &strKey, const std::string &strParam, std::string &strValue)
	{
        if(strKey == "Seg_CopyIntervalTime")
		{
			if( m_uHR >= 10 && m_uHR < 45)
			{
				strValue = "3500";
			}
			else if( m_uHR >= 45 && m_uHR < 58)
			{
				strValue = "2200";
			}
			else
			{
				strValue = "500";
			}
		}
		return true;	
	}

	bool CCardiogram3degree_AVBParam_I12::GetParamValue(const std::string &strKey, std::string &strValue)
	{
        if(strKey == "Seg_CopyNum")
		{
			string strCycleTime;
			GetParamValue("CycleTime",strCycleTime);
			int iCurrCycleTime = lexical_cast<int>(strCycleTime);//当前的周期时间
			//设置基数据段向前延伸的时间
			m_nBasicSeg_LExtentTime = m_nSumBasicSegTime - (m_dwSumRunTime - iCurrCycleTime);
            BOOST_ASSERT(m_nBasicSeg_LExtentTime >= 0);
			string strIntervalTime;
			GetParamValue( "Seg_CopyIntervalTime", "", strIntervalTime);
			int iIntervalTime = lexical_cast<int>(strIntervalTime);
			int iCoyNum = 0;
			if(m_dwSumRunTime > m_nSumBasicSegTime)
			{
				if((m_dwSumRunTime - m_nSumBasicSegTime)%(iIntervalTime+5000) != 0)
					iCoyNum = (m_dwSumRunTime - m_nSumBasicSegTime)/(iIntervalTime+5000) + 1;
				else
					iCoyNum = (m_dwSumRunTime - m_nSumBasicSegTime)/(iIntervalTime+5000);
			}
			strValue = lexical_cast<string>(iCoyNum);
			m_nSumBasicSegTime += iCoyNum * (iIntervalTime+5000);
		}
        else if(strKey == "BasicSeg_LExtentTime")
		{
			strValue = lexical_cast<string>(m_nBasicSeg_LExtentTime);
		}
		else
		{
			CVirCardiogramParam::GetParamValue(strKey,strValue);
		}
		return true;
	}

	//产生心电时，血氧的启动时间
	bool CCardiogram3degree_AVBParam_I12::GetSpO2BeginTimeToCardiogram(/*out*/long &lBeginTime, /*out*/long &lCycleTime)
	{
		lBeginTime = 0;
		string strKey, strValue;
		strKey = "Seg_FileName";
		if( GetParamValue(strKey, strValue) && strValue == "Zero.txt" )
		{
			return false;
		}
		else
		{
			lBeginTime = 4200;
		}
		lCycleTime = (long)GetCycleTime();
		return true;
	}

}}}
