#include <boost/lexical_cast.hpp>
#include ".\CardiogramV_tachParam_I12.h"


namespace jysoft { namespace simulator { namespace ecg {

	CCardiogramV_tachParam_I12::CCardiogramV_tachParam_I12( IStorage *pRootStorage )
						: CVirCardiogramParam()
	{
		m_pStorages = pRootStorage;
	}

	CCardiogramV_tachParam_I12::~CCardiogramV_tachParam_I12(void)
	{
	}

	//加载参数值
    void CCardiogramV_tachParam_I12::LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm,int uHR, short sConduct/*=0*/, short sExtendParam/*=0*/)
	{
		int iHRStep = Get_HRStep(uHR);
		//各数值的含义：段文件名；缩放时间；切割时间点；直线间隔延伸时间；水平间隔延伸操作；周期时间
		std::string strParams[][6] = {
			//A
            {"Unifocal_PVC_A.txt","4800","0","0","200","5000"},//120HR
            {"Unifocal_PVC_A.txt","4800","4500","200","0","4700"},//130HR
            {"Unifocal_PVC_A.txt","4800","4300","200","0","4500"},//140HR
            {"Unifocal_PVC_A.txt","4800","3800","200","0","4000"},//150HR
            {"Unifocal_PVC_A.txt","4800","3600","200","0","3800"},//160HR
            {"Unifocal_PVC_A.txt","4800","3300","200","0","3500"},//170HR
            {"Unifocal_PVC_A.txt","3200","0","0","200","3400"},//180HR
            {"Unifocal_PVC_A.txt","3200","3000","200","0","3200"},//190HR
            {"Unifocal_PVC_A.txt","3200","2800","200","0","3000"},//200HR
            {"Unifocal_PVC_A.txt","3200","2700","200","0","2900"},//210HR
            {"Unifocal_PVC_A.txt","3200","2700","100","0","2700"},//220HR
            {"Unifocal_PVC_A.txt","3200","2600","100","0","2600"},//230HR
            {"Unifocal_PVC_A.txt","3200","2500","100","0","2500"} //240HR
		};
		std::string *pAimPtr = strParams[ iHRStep ];
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
			m_setParams["HR"] = boost::lexical_cast<std::string>(uHR);
		}

		m_setParams["Seg_FileName"] = pAimPtr[0];
		m_setParams["ZoomTime"] = pAimPtr[1];
		m_setParams["CutPositionTime"] = pAimPtr[2];
		m_setParams["LineExtendTime"] = pAimPtr[3];
		m_setParams["R_ExtendTime"] = pAimPtr[4];
		m_setParams["CycleTime"] = pAimPtr[5];

		m_eQRS = eQRS;
		m_eRhythm = eRhythm;
		m_uHR     = uHR;
		//end hjg 2006/3/29
	}

	//产生心电时，血氧的启动时间
	bool CCardiogramV_tachParam_I12::GetSpO2BeginTimeToCardiogram(/*out*/long &lBeginTime, /*out*/long &lCycleTime)
	{
		lBeginTime  = 0;
		std::string strKey, strValue;
		strKey = "ZoomTime";
		if( GetParamValue(strKey, strValue) )
		{
			lBeginTime += boost::lexical_cast<long>(strValue)/2;
		}
		else
		{
			return false;
		}
		lCycleTime = (long)GetCycleTime();
		return true;
	}

    int CCardiogramV_tachParam_I12::Get_HRStep(int uHR)
	{
		int iStep = 0;
		iStep = uHR/10-12;
		return iStep < 0 ? 0 : iStep;
	}
}}}
