#include <boost/lexical_cast.hpp>
#include ".\CardiogramPaceParam_I12.h"


namespace jysoft { namespace simulator { namespace ecg {

	CCardiogramPaceParam_I12::CCardiogramPaceParam_I12( IStorage *pRootStorage )
						: CVirCardiogramParam()
	{
		m_pStorages  = pRootStorage;
	}

	CCardiogramPaceParam_I12::~CCardiogramPaceParam_I12(void)
	{
	}

	//加载参数值
    void CCardiogramPaceParam_I12::LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm,int uHR, short sConduct/*=0*/, short sExtendParam/*=0*/)
	{
		//段名称；时间
		static std::string strParams[][5] = {
            {"Pacing.txt","pulse.txt","4900"},
			{}
		};
		std::string *pAimPtr = strParams[0];
		//设置刷新数据的范围
		if(m_eQRS == QRS_None)
		{
			m_setParams.clear();//移除所有的参数
			m_eRefurbishDataRange = RD_LoadConfigFile;
			m_setParams["ConfigFileName"] = "MakeFile.txt";
		}
		else if( m_uHR != uHR )
		{
			m_eRefurbishDataRange = RD_OpSegmentData;
		}

		if( m_uHR != uHR || m_eQRS != eQRS )
		{
			m_setParams["HR"] = boost::lexical_cast<std::string>(60*10000/uHR);
		}
	
		m_setParams["Pacing_FileName"] = pAimPtr[0];
		m_setParams["Pulse_FileName"] = pAimPtr[1];
		m_setParams["Pacing_ZoomTime"] = pAimPtr[2];
		int nPaceExtendTime = uHR - 200 - 300 - 2500;
		if(nPaceExtendTime < 0)
			nPaceExtendTime = 0;
		m_setParams["Pacing_ExtendTime"] = boost::lexical_cast<std::string>(nPaceExtendTime);
		m_setParams["CycleTime"] = boost::lexical_cast<std::string>(uHR);

		m_eQRS = QRS_A;
		m_eRhythm = eRhythm;
		m_uHR   = uHR;
	}

	//产生心电时，血氧的启动时间
	bool CCardiogramPaceParam_I12::GetSpO2BeginTimeToCardiogram(/*out*/long &lBeginTime, /*out*/long &lCycleTime)
	{
		lBeginTime = 2500;

		lCycleTime = (long)GetCycleTime();
		return true;
	}

	//返回Q波到S波时间段的时间（单位：0.1毫秒）
	int CCardiogramPaceParam_I12::GetPhaseTimeFromQtoS() 
	{ 
		return 1000; 
	}

	//返回S波到T波时间段的时间（单位：0.1毫秒）
	int CCardiogramPaceParam_I12::GetPhaseTimeFromStoT() 
	{ 
		return 3000; 
	}
}}}
