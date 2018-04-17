#include <boost/lexical_cast.hpp>
#include <boost/assert.hpp>
#include ".\CardiogramAgonaleParam_I12.h"


using namespace std;
using namespace boost;
namespace jysoft { namespace simulator { namespace ecg {

	CCardiogramAgonaleParam_I12::CCardiogramAgonaleParam_I12( IStorage *pRootStorage )
							: CVirCardiogramParam()
	{
		m_dwSumRunTime = 0;
		m_nSumBasicSegTime = 0;
		m_nBasicSeg_LExtentTime = 0;
		//----------------------------------------------------------------------------------------------
		m_pStorages     = pRootStorage;
	}

	CCardiogramAgonaleParam_I12::~CCardiogramAgonaleParam_I12(void)
	{
	}

	//加载参数值
    void CCardiogramAgonaleParam_I12::LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm,int uHR, short sConduct/*=0*/, short sExtendParam/*=0*/)
	{
		if( uHR < 1 )
			uHR  = 1;
		else if( uHR > 40 )
			uHR  = 40;
		//各数值的含义：主波段文件名；缩放时间；水平间隔延伸时间；基数据段文件名；重复复制间隔时间；周期时间;
		string strParams[][6] = {
            {"Agonal_Rhythm.txt","3500","591250","Base_Seg.txt","100","600000"},//1HR
            {"Agonal_Rhythm.txt","3500","51250","Base_Seg.txt","100","60000"},//10HR
            {"Agonal_Rhythm.txt","3500","21250","Base_Seg.txt","100","30000"},//20HR
            {"Agonal_Rhythm.txt","3500","11250","Base_Seg.txt","100","20000"},//30HR
            {"Agonal_Rhythm.txt","3500","6250","Base_Seg.txt","100","15000"} //40HR
		};
		string *pParams = strParams[uHR/10];
		//---------------------------------------------------------------------------------------------------
		int nContrastCycleTime = lexical_cast<int>( pParams[5] );
		int nCycleTime = ((600000 / uHR) / 50) * 50;  //时间单位为0.1毫秒；周期时间为50的倍数
		int nExtendTime = lexical_cast<int>( pParams[2] );
		nExtendTime    = nExtendTime - ( nContrastCycleTime - nCycleTime);
		pParams[2] = lexical_cast<string>(nExtendTime);
		pParams[5] = lexical_cast<string>(nCycleTime);
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
			if(uHR != m_uHR )
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
	
		m_setParams["E_FileName"] =  pParams[0];
		m_setParams["E_ZoomTime"] = pParams[1];
		m_setParams["E_ExtendTime"] = pParams[2];
		m_setParams["Seg_FileName"] = pParams[3];
		m_setParams["Seg_CopyIntervalTime"] = pParams[4];
		m_setParams["CycleTime"] = pParams[5];
		//===================================================================
		m_dwSumRunTime += lexical_cast<int>(pParams[5]);
		//end hjg 2013/7/24
	}

	//产生心电时，血氧的启动时间
	bool CCardiogramAgonaleParam_I12::GetSpO2BeginTimeToCardiogram(/*out*/long &lBeginTime, /*out*/long &lCycleTime)
	{
		lBeginTime = 2500;

		lCycleTime = (long)GetCycleTime();
		return true;
	}

	bool CCardiogramAgonaleParam_I12::GetParamValue(const string &strKey, string &strValue)
	{
        if(strKey == "Seg_CopyNum")
		{
			string strCycleTime;
			GetParamValue("CycleTime",strCycleTime);
			//当前的周期时间
			int iCurrCycleTime = lexical_cast<int>(strCycleTime);
			//设置基数据段向前延伸的时间
			m_nBasicSeg_LExtentTime = m_nSumBasicSegTime - (m_dwSumRunTime - iCurrCycleTime);
            BOOST_ASSERT(m_nBasicSeg_LExtentTime >= 0);
			string strIntervalTime;
			GetParamValue("Seg_CopyIntervalTime", strIntervalTime);
			int iIntervalTime = lexical_cast<int>(strIntervalTime);
			int iCoyNum = 0;
			if(m_dwSumRunTime > m_nSumBasicSegTime)
			{
				if((m_dwSumRunTime - m_nSumBasicSegTime)%(iIntervalTime+29600) != 0)
					iCoyNum = (m_dwSumRunTime - m_nSumBasicSegTime)/(iIntervalTime+29600) + 1;
				else
					iCoyNum = (m_dwSumRunTime - m_nSumBasicSegTime)/(iIntervalTime+29600);
			}
			strValue = lexical_cast<string>(iCoyNum);
			m_nSumBasicSegTime += iCoyNum * (iIntervalTime+29600);
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
}}}
