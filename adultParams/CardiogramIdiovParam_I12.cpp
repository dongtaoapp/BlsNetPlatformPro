#include <boost/lexical_cast.hpp>
#include ".\CardiogramIdiovParam_I12.h"


using namespace std;
using namespace boost;
namespace jysoft { namespace simulator { namespace ecg {

	CCardiogramIdiovParam_I12::CCardiogramIdiovParam_I12(IStorage *pRootStorage )
						: CVirCardiogramParam()
	{
		m_pStorages  = pRootStorage;
	}

	CCardiogramIdiovParam_I12::~CCardiogramIdiovParam_I12(void)
	{
	}

	//加载参数值
    void CCardiogramIdiovParam_I12::LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm,int uHR, short sConduct/*=0*/, short sExtendParam/*=0*/)
	{
		if( uHR < 1 )
			uHR  = 1;
		else if( uHR > 100 )
			uHR  = 100;
		int iHRStep = uHR/10 ;
		//各数值的含义：段文件名；缩放时间；水平间隔延伸时间；周期时间
		string strParams[][4] = {
			//A
            {"Unifocal_PVC_A.txt","4800","595200","600000"},//1HR
            {"Unifocal_PVC_A.txt","4800","55200","60000"},//10HR
            {"Unifocal_PVC_A.txt","4800","25200","30000"},//20HR
            {"Unifocal_PVC_A.txt","4800","15200","20000"},//30HR
            {"Unifocal_PVC_A.txt","4800","10200","15000"},//40HR
            {"Unifocal_PVC_A.txt","4800","7200","12000"},//50HR
            {"Unifocal_PVC_A.txt","4800","5200","10000"}, //60HR
            {"Unifocal_PVC_A.txt","4800","3800","8600"}, //70HR
            {"Unifocal_PVC_A.txt","4800","2700","7500"}, //80HR
            {"Unifocal_PVC_A.txt","4800","1800","6600"}, //90HR
            {"Unifocal_PVC_A.txt","4800","1200","6000"} //100HR
		};
		string *pAimPtr = strParams[ iHRStep];
		if( (uHR % 10) != 0 )
		{
			int nCycleTime = ((600000 / uHR) / 50) * 50;
			int nExtendTime = lexical_cast<int>( pAimPtr[2] );
			nExtendTime    = nExtendTime - ( lexical_cast<int>( pAimPtr[3] ) - nCycleTime);
			pAimPtr[2] = lexical_cast<string>(nExtendTime);
			pAimPtr[3] = lexical_cast<string>(nCycleTime);
		}
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
			m_setParams["HR"]  = lexical_cast<string>(uHR);
		}

		m_setParams["Seg_FileName"] = pAimPtr[0];
		m_setParams["ZoomTime"] = pAimPtr[1];
		m_setParams["R_ExtendTime"] = pAimPtr[2];
		m_setParams["CycleTime"] = pAimPtr[3];

		m_eQRS = eQRS;
		m_eRhythm = eRhythm;
		m_uHR     = uHR;
		//end hjg 2006/3/29
	}

	//产生心电时，血氧的启动时间
	bool CCardiogramIdiovParam_I12::GetSpO2BeginTimeToCardiogram(/*out*/long &lBeginTime, /*out*/long &lCycleTime)
	{
		lBeginTime = 2500;

		lCycleTime = (long)GetCycleTime();
		return true;
	}

	//返回Q波到S波时间段的时间（单位：0.1毫秒）
	int CCardiogramIdiovParam_I12::GetPhaseTimeFromQtoS() 
	{ 
		return 1000; 
	}

	//返回S波到T波时间段的时间（单位：0.1毫秒）
	int CCardiogramIdiovParam_I12::GetPhaseTimeFromStoT() 
	{ 
		return 3000; 
	}
}}}
