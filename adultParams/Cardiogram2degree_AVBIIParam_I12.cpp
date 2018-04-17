#include <boost/lexical_cast.hpp>
#include <boost/assert.hpp>
#include <boost/format.hpp>
#include ".\Cardiogram2degree_AVBIIParam_I12.h"


using namespace std;
using namespace boost;
namespace jysoft { namespace simulator { namespace ecg {

	CCardiogram2degree_AVBIIParam_I12::CCardiogram2degree_AVBIIParam_I12( IStorage *pRootStorage )
										: CVirCardiogramParam()
	{
		m_nStepNum = 0;
		m_nSumStepNum = 0;
		m_bEmptQRS   = 0;
		m_pStorages  = pRootStorage;
	}

	CCardiogram2degree_AVBIIParam_I12::~CCardiogram2degree_AVBIIParam_I12(void)
	{
	}

	//加载参数值
    void CCardiogram2degree_AVBIIParam_I12::LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm,int uHR, short sConduct/*=0*/, short sExtendParam/*=0*/)
	{
		//设置范围内的心率值
		if( uHR < 50 )
		{
			uHR  = 50;
		}
		else if( uHR > 100 )
		{
			uHR  = 100;
		}
		if( sConduct == 0 )
			sConduct  = 3;
        BOOST_ASSERT( sConduct == 3 || sConduct == 4 || sConduct == 5 );
		if( sConduct != 0 )
		{
			m_nSumStepNum  = sConduct;
		}
		//各数值的含义：p段文件名；缩放时间；水平间隔延伸时间；R段文件名；缩放时间；水平间隔延伸时间；T段文件名；缩放时间；水平间隔延伸时间；周期时间
		string strParams[][10] = {
            {"P.txt","1200","300","A_R.txt","1000","900","A_T.txt","2200","6400","12000"}, //50HR
            {"P.txt","1200","300","A_R.txt","1000","900","A_T.txt","2200","4400","10000"}, //60HR
            {"P.txt","1200","300","A_R.txt","1000","900","A_T.txt","2200","1900","8600"}, //70HR
            {"P.txt","1200","300","A_R.txt","1000","900","A_T.txt","2200","950","7500"}, //80HR
            {"P.txt","1200","300","A_R.txt","1000","900","A_T.txt","2200","1000","6600"}, //90HR
            {"P.txt","1200","300","A_R.txt","1000","900","A_T.txt","2200","700","6300"}, //95HR
            {"P.txt","1200","300","A_R.txt","1000","900","A_T.txt","2200","100","6000"},  //100HR
            {"P.txt","1200","300","A_R.txt","1000","900","A_T.txt","2200","0","5700"},  //105HR
            {"P.txt","1200","300","A_R.txt","1000","900","A_T.txt","2200","0","5450"}    //110HR
		};
		int  iHRStep  = uHR/10 - 5;
		if( uHR > 90 )
		{
			iHRStep = ((uHR / 5) * 5 - 90)/5 + 4;
		}
		string *pAimPtr = strParams[iHRStep];
		if( (uHR <= 90 &&(uHR % 10) != 0) || (uHR > 90 && (uHR % 5) != 0) )
		{
			int nCycleTime = ((600000 / uHR) / 50) * 50;  //时间单位为0.1毫秒；周期时间为50的倍数
			int nExtendTime = lexical_cast<int>( pAimPtr[8] );
			nExtendTime    = nExtendTime - ( lexical_cast<int>( pAimPtr[9] ) - nCycleTime);
			pAimPtr[8] = lexical_cast<string>( nExtendTime );
			pAimPtr[9] = lexical_cast<string>( nCycleTime );
		}

		//设置刷新数据的范围
		if(m_eQRS == QRS_None)
		{
			m_nStepNum = 0;
			m_bEmptQRS = 0;
			m_setParams.clear();//移除所有的参数
			m_eRefurbishDataRange = RD_LoadConfigFile;
			m_setParams["ConfigFileName"] = "MakeFile.txt";
		}
		else if(m_eQRS != eQRS)
		{
			m_eRefurbishDataRange = RD_AllData;
			m_nStepNum = 0;
			m_eRefurbishDataRange = RD_AllData;
		}
		if(m_nStepNum == 0 && m_eRefurbishDataRange != RD_LoadConfigFile)
		{
			m_eRefurbishDataRange = RD_AllData;
		}
		if( m_uHR != uHR || m_eQRS != eQRS )
		{
            format  fmt("%d");
			fmt % uHR;
			m_setParams["HR"] = fmt.str();
		}
		int iCycleTime = lexical_cast<int>( pAimPtr[9] );
		if( m_nStepNum == (m_nSumStepNum -1) )
		{
			m_eRefurbishDataRange = RD_AllData;
			pAimPtr[3] = "Zero.txt";
			pAimPtr[4] = "1000";
			pAimPtr[5] = "0";
			pAimPtr[6] = "Zero.txt";
			pAimPtr[7] = "1000";
			pAimPtr[8] = "0";
			int iTExtendTime = iCycleTime-800-2000;
			pAimPtr[8] = lexical_cast<string>(iTExtendTime);
		}
		SetP_FileName(pAimPtr);
		SetP_ZoomTime(pAimPtr);
		SetP_ExtendTime(pAimPtr);
		SetR_FileName(pAimPtr);
		SetR_ZoomTime(pAimPtr);
		SetR_ExtendTime(pAimPtr);
		SetT_FileName(pAimPtr);
		SetT_ZoomTime(pAimPtr);
		SetT_ExtendTime(pAimPtr);
		Set_CycleTime(pAimPtr);

		m_eQRS = eQRS;
		m_eRhythm = eRhythm;
		m_uHR     = uHR;
		//end hjg 2006/3/29
		//--------------------------------------------------------------
		++m_nStepNum;
		m_nStepNum = m_nStepNum % m_nSumStepNum;
		if( m_eRefurbishDataRange == RD_NoChange )
		{
			m_eRefurbishDataRange = RD_MainSegmentData;
		}
	}

	//加载对应的早波的数据参数
	void CCardiogram2degree_AVBIIParam_I12::LoadExtrasystParam(Extrasys eExtrasyst)
	{
		string   strAimPtr[5];
		switch(eExtrasyst)
		{
		case ES_None:
		case Unifocal_PVC:  //单形性室性早搏
		case Multifocal_PVC://多形性室性早搏
			{
				//各数值的含义：早波段时间；向左延伸时间；向左延伸值；向右延伸时间；向右延伸值；周期时间
				static string strUnifocalPVC_Params[][5] = {
                    {"4500","7400","0","8100","20000"}, //60
                    {"4500","7400","0","7700","19600"}, //61
                    {"4500","7400","0","7400","19300"}, //62
                    {"4500","7400","0","7100","19000"}, //63
                    {"4500","7200","0","7000","18700"}, //64
                    {"4500","7200","0","6700","18400"}, //65
                    {"4500","7200","0","6500","18200"}, //66
                    {"4500","7200","0","6200","17900"}, //67
                    {"4500","6900","0","6200","17600"}, //68
                    {"4500","6900","0","6000","17400"}, //69
                    {"4500","6800","0","5800","17100"}, //70
                    {"4500","6800","0","5600","16900"}, //71
                    {"4500","6800","0","5300","16600"}, //72
                    {"4500","6800","0","5100","16400"}, //73
                    {"4500","6800","0","4900","16200"}, //74
                    {"4500","6800","0","4700","16000"}, //75
                    {"4500","6800","0","4500","15800"}, //76
                    {"4500","6800","0","4300","15600"}, //77
                    {"4500","6600","0","4300","15400"}, //78
                    {"4500","6400","0","4300","15200"}, //79
                    {"4500","6400","0","4100","15000"}, //80
                    {"4500","6400","0","3900","14800"}, //81
                    {"4500","6400","0","3700","14600"}, //82
                    {"4500","6400","0","3500","14400"}, //83
                    {"4500","6400","0","3400","14300"}, //84
                    {"4500","6400","0","3200","14100"}, //85
                    {"4500","6400","0","3100","14000"}, //86
                    {"4500","6400","0","2900","13800"}, //87
                    {"4500","6400","0","2700","13600"}, //88
                    {"4500","6400","0","2600","13500"}, //89
                    {"4500","6400","0","2300","13200"}, //90
                    {"4500","6400","0","1700","12600"}, //95
                    {"4500","6400","0","1100","12000"}  //100
				};
				if( m_uHR <= 90 )
				{
					for( int n = 0; n < 5; ++n )
					{
						strAimPtr[n] = strUnifocalPVC_Params[m_uHR-60][n];
					}
				}
				else
				{
					int iHRStep = ((m_uHR / 5) * 5 - 90)/5 + 30;
					for( int n = 0; n < 5; ++n )
					{
						strAimPtr[n] = strUnifocalPVC_Params[m_uHR-60][n];
					}
					if( (m_uHR%5) != 0 )
					{
						//时间单位为0.1毫秒；周期时间为50的倍数
						int nCycleTime = ((600000 / m_uHR) / 50) * 50;
						strAimPtr[4] = lexical_cast<string>(nCycleTime);
						int nRightExtendTime = nCycleTime - 4500 - 6400;
						if( nRightExtendTime < 0 )
							nRightExtendTime = 0;
						strAimPtr[3] = lexical_cast<string>(nRightExtendTime);
					}
				}
				break;
			}
		case PVC_RonT://室性早搏RonT
			{
				//各数值的含义：早波段时间；向左延伸时间；向左延伸值；向左延伸值；周期时间
				static string strPVC_RonT_Params[][5] = {
                    {"4800","4500","0","700","10000"}, //60
                    {"4800","4500","0","5700","15000"}, //70
                    {"4650","4500","0","3850","13000"}, //80
                    {"4500","4500","0","2000","11000"}, //90
                    {"4500","4500","0","1000","10000"}  //100
				};
				int iHRStep = ((m_uHR / 10) * 10 - 60)/10;
				for (int nStep = 0; nStep < 5; ++nStep)
				{
					strAimPtr[nStep] = strPVC_RonT_Params[iHRStep][nStep];
				}
				if( (m_uHR%10) != 0 )
				{
					//时间单位为0.1毫秒；周期时间为50的倍数
					int nCycleTime = ((600000 / m_uHR) / 50) * 50;
					strAimPtr[4] = lexical_cast<string>(nCycleTime);
					int nRightExtendTime = nCycleTime - 3200 - 3000;
					if( nRightExtendTime < 0 )
						nRightExtendTime = 0;
					strAimPtr[3] = lexical_cast<string>(nRightExtendTime);
				}
				break;
			}
		case Coupled_PVC://室性早搏显二联律
			{
				//各数值的含义：早波段时间；向左延伸时间；向左延伸值；向左延伸值；周期时间
				static string strCoupled_PVC_Params[][5] = {
                    {"9600","7500","0","2900","20000"}, //60
                    {"9600","7500","0","2500","19600"}, //61
                    {"9600","7500","0","2200","19300"}, //62
                    {"9600","7500","0","1900","19000"}, //63
                    {"9600","7500","0","1600","18700"}, //64
                    {"9600","7500","0","1400","18500"}, //65
                    {"9600","7500","0","1100","18200"}, //66
                    {"9600","7500","0","800","17900"}, //67
                    {"9600","7500","0","500","17600"}, //68
                    {"9600","7400","0","400","17400"}, //69
                    {"9600","7000","0","400","17000"}, //70
                    {"9600","7000","0","300","16900"}, //71
                    {"9600","7000","0","100","16700"}, //72
                    {"9600","5800","0","1000","16400"}, //73
                    {"9600","5800","0","800","16200"}, //74
                    {"9600","5600","0","800","16000"}, //75
                    {"9600","4600","0","1600","15800"}, //76
                    {"9600","4500","0","1500","15600"}, //77
                    {"9600","4500","0","1300","15400"}, //78
                    {"9600","4500","0","1100","15200"}, //79
                    {"9300","4300","0","1500","15100"}, //80
                    {"9300","4300","0","1200","14800"}, //81
                    {"9300","4300","0","1000","14600"}, //82
                    {"9300","4300","0","800","14400"}, //83
                    {"9300","4500","0","500","14300"}, //84
                    {"9300","4500","0","300","14100"}, //85
                    {"9000","5400","0","0","13900"}, //86
                    {"9000","5400","0","0","13800"}, //87
                    {"9000","5400","0","0","13600"}, //88
                    {"9000","5400","0","0","13500"}, //89
                    {"9000","5400","0","0","13200"}, //90
					//2013.5.30 add hjg
                    {"8700","5400","0","0","12600"}, //95
                    {"8700","5400","0","0","12000"} //100
				};
				if( m_uHR <= 90 )
				{
					for( int n = 0; n < 5; ++n )
					{
						strAimPtr[n] = strCoupled_PVC_Params[m_uHR-60][n];
					}
				}
				else
				{
					int iHRStep = ((m_uHR / 5) * 5 - 90)/5 + 30;
					for( int n = 0; n < 5; ++n )
					{
						strAimPtr[n] = strCoupled_PVC_Params[m_uHR-60][n];
					}
					if( (m_uHR%5) != 0 )
					{
						//时间单位为0.1毫秒；周期时间为50的倍数
						int nCycleTime = ((600000 / m_uHR) / 50) * 50;
						strAimPtr[4] = lexical_cast<string>(nCycleTime);
						int nRightExtendTime = nCycleTime - 4500 - 6400;
						if( nRightExtendTime < 0 )
							nRightExtendTime = 0;
						strAimPtr[3] = lexical_cast<string>(nRightExtendTime);
					}
				}
				break;
			}
		}
		m_setParams["ES_Time"] = strAimPtr[0];//早波段时间
		m_setParams["ES_LExtentTime"] = strAimPtr[1];//向左延伸时间
		m_setParams["ES_LExtentValue"] = strAimPtr[2];//向左延伸值
		m_setParams["ES_RExtentTime"] = strAimPtr[3];//向右延伸时间
		m_setParams["CycleTime"] = strAimPtr[4];//周期时间
		if(m_eRefurbishDataRange == RD_NoChange)
			m_eRefurbishDataRange = RD_MainSegmentData;
	}

	void CCardiogram2degree_AVBIIParam_I12::LoadExtrasystParamPre(Extrasys eExtrasyst)
	{
		switch(eExtrasyst)
		{
		case PAC:
			{
				m_eRefurbishDataRange = RD_AllData;//重新加载所有的数据
				m_setParams["T_ExtendTime"] = "0";//T段延伸值
				break;
			}
		case PJC:
			{
				m_eRefurbishDataRange = RD_AllData;//重新加载所有的数据
				m_setParams["T_ExtendTime"] = "0";
				break;
			}
		}
	}

	std::string CCardiogram2degree_AVBIIParam_I12::GetExtrasystFileName(Extrasys eExtrasyst, const std::string &strKey)
	{
		string strExtrasystFileName;
		switch(eExtrasyst)
		{
		case ES_None:
		case Unifocal_PVC:
		case PVC_RonT:
			{
				strExtrasystFileName = "Unifocal_PVC_A.txt";
				break;
			}
		case Coupled_PVC:
			{
				strExtrasystFileName = "Coupled_PVC_A.txt";
				break;
			}
		case Multifocal_PVC:
			{
				string strFileNames[3]; 

				strFileNames[0] = "Unifocal_PVC_A.txt";
				strFileNames[1] = "Unifocal_PVC_B.txt";
				strFileNames[2] = "Unifocal_PVC_E.txt";

				srand( (unsigned)time( NULL ) );
				int nMultiPVC_Step = rand() % 3;
				strExtrasystFileName = strFileNames[nMultiPVC_Step];
				break;
			}
		}
		return strExtrasystFileName;
	}

	void CCardiogram2degree_AVBIIParam_I12::ReLoadCardiogramParam()
	{
		LoadCardiogramParam(m_eQRS,m_eRhythm,m_uHR, m_nSumStepNum);
	}

	//---------------------------------------------------------------------------------------------------------------
	//产生心电时，血氧的启动时间
	bool CCardiogram2degree_AVBIIParam_I12::GetSpO2BeginTimeToCardiogram(/*out*/long &lBeginTime, /*out*/long &lCycleTime)
	{
		try
		{
			lBeginTime = 0;
			std::string strKey, strValue;
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
			//------------------------------------------------------------
			strKey = "T_FileName";
			if( GetParamValue(strKey, strValue) )
			{
				if( strValue == "Zero.txt" )
				{
					m_bEmptQRS   = 1;
					return true;
				}
			}
			if( m_bEmptQRS == 1 )
			{
				m_bEmptQRS  = 2;
				lBeginTime  += lCycleTime;
				return true;
			}
			else if( m_bEmptQRS == 2)
			{
				m_bEmptQRS = 0;
				return false;
			}
		}
        catch (std::exception* e)
		{
			return false;
		}
		return true;
	}

	//产生早博时，血氧的启动时间
	bool CCardiogram2degree_AVBIIParam_I12::GetSpO2BeginTimeToExtrasyst(/*out*/long &lBeginTime, /*out*/long &lPreSpO2BeginTime, /*out*/long &lCycleTime)
	{
		lBeginTime = 0;
		std::string strKey, strValue;
		strKey = "ES_Time";
		if( GetParamValue(strKey, /*out*/strValue) )
		{
			lBeginTime = lexical_cast<long>(strValue);
			lBeginTime = lBeginTime/3;
		}
		else
		{
            BOOST_ASSERT(0);
			return false;
		}
		strKey = "ES_LExtentTime";
		if( GetParamValue(strKey, /*out*/strValue) )
		{
			lBeginTime += lexical_cast<long>(strValue);
		}
		else
		{
            BOOST_ASSERT(0);
			return false;
		}
		return GetSpO2BeginTimeToCardiogram(/*out*/lPreSpO2BeginTime, /*out*/lCycleTime);
	}

}}}
