#include <boost/lexical_cast.hpp>
#include <boost/assert.hpp>
#include ".\Cardiogram2degree_AVBIParam_I12.h"

using namespace std;
using namespace boost;
namespace jysoft { namespace simulator { namespace ecg {

	CCardiogram2degree_AVBIParam_I12::CCardiogram2degree_AVBIParam_I12(IStorage *pRootStorage)
								: CVirCardiogramParam()
	{
		m_nStepNum = 0;
		m_nSumStepNum = 0;
		m_bEmptQRS   = 0;
		m_pStorages  = pRootStorage;
	}

	CCardiogram2degree_AVBIParam_I12::~CCardiogram2degree_AVBIParam_I12(void)
	{
	}

	//加载参数值
    void CCardiogram2degree_AVBIParam_I12::LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm,int uHR, short sConduct, short sExtendParam )
	{
		if( uHR < 50 )
		{
			uHR  = 50;
		}
		else if( uHR > 100 )
		{
			uHR  = 100;
		}
        BOOST_ASSERT( sConduct == 3 || sConduct == 4 || sConduct == 5 );
		if( sConduct != 0 )
		{
			m_nSumStepNum  = sConduct;
		}

		//各数值的含义：p段文件名；缩放时间；R段文件名；缩放时间；水平间隔延伸时间；T段文件名；缩放时间；周期时间
		string strParams[][8] = {
            {"P.txt","1200","A_R.txt","1000","900","A_T.txt","2200","12000"}, //50HR
            {"P.txt","1200","A_R.txt","1000","900","A_T.txt","2200","10900"}, //55HR
            {"P.txt","1200","A_R.txt","1000","900","A_T.txt","2200","10000"}, //60HR
            {"P.txt","1200","A_R.txt","1000","900","A_T.txt","2200","9200"}, //65HR
            {"P.txt","1200","A_R.txt","1000","900","A_T.txt","2200","8600"}, //70HR
            {"P.txt","1200","A_R.txt","1000","900","A_T.txt","2200","8000"}, //75HR
            {"P.txt","1200","A_R.txt","1000","900","A_T.txt","2200","7500"}, //80HR
            {"P.txt","1200","A_R.txt","1000","900","A_T.txt","2200","7050"}, //85HR
            {"P.txt","1200","A_R.txt","1000","900","A_T.txt","2200","6600"}, //90HR
            {"P.txt","1200","A_R.txt","1000","900","A_T.txt","2200","6300"}, //95HR
            {"P.txt","1200","A_R.txt","1000","900","A_T.txt","2200","6000"}  //100HR
		};
		int iHRStep = ((uHR / 5) * 5 - 50)/5 ;
		string *pAimPtr = strParams[ iHRStep ];
		//修改周期时间
		if( (uHR%5) != 0 )
		{
			int nCycleTime = ((600000 / uHR) / 50) * 50;  //时间单位为0.1毫秒；周期时间为50的倍数
			pAimPtr[7] = lexical_cast<int>(nCycleTime);
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
		}
		else
		{
			m_eRefurbishDataRange = RD_OpSegmentData;
		}
		if(m_nStepNum == 0 && m_eRefurbishDataRange != RD_LoadConfigFile)
		{
			m_eRefurbishDataRange = RD_AllData;
		}
		if( m_uHR != uHR || m_eQRS != eQRS )
		{
			string  strHR = lexical_cast<string>(uHR);
			m_setParams["HR"] = strHR;
		}

		int iCycleTime = lexical_cast<int>(pAimPtr[7]);
		int iPExtendTime = 0;
		int iTExtendTime = 0;
		if( m_nStepNum == (m_nSumStepNum -1) )
		{
			m_eRefurbishDataRange = RD_AllData;
			pAimPtr[2] = "Zero.txt";
			pAimPtr[3] = "800";
			pAimPtr[4] = "0";
			pAimPtr[5] = "Zero.txt";
			pAimPtr[6] = "1000";
			iPExtendTime = iCycleTime-600-1800;
			iTExtendTime = 0;
		} 
		else
		{
			static int iP_ExtendTime[][4] = {
				{400,2200,3400,4200},    //50
				{400,1600,3000,3800},    //55
				{300,1400,2800,3500},    //60
				{300,1300,2300,3200},    //65
				{300,1000,1800,2500},    //70
				{200,900,1600,2100},     //75
				{200,900,1300,1800},     //80
				{200,500,1000,1300},     //85
				{200,400,700,1000},     //90
				{100,300,500,700},      //95
				{100,300,500,700},      //100
				{50,200,400,600},      //105
				{50,100,200,500}       //110
			};
			//end
			int  iHRStep  = ((uHR / 5) * 5 - 50)/5;
			iPExtendTime = iP_ExtendTime[iHRStep][m_nStepNum];
			iTExtendTime = iCycleTime - lexical_cast<int>(pAimPtr[1]) - lexical_cast<int>(pAimPtr[3]) \
							 - lexical_cast<int>(pAimPtr[4]) - lexical_cast<int>(pAimPtr[6]) - iPExtendTime;
			if(iTExtendTime < 0)
				iTExtendTime = 0;
		}
		SetP_FileName(pAimPtr);
		SetP_ZoomTime(pAimPtr);
		//设置P波的延伸段时间
		m_setParams["P_ExtendTime"] = lexical_cast<string>(iPExtendTime);
		SetR_FileName(pAimPtr);
		SetR_ZoomTime(pAimPtr);
		SetR_ExtendTime(pAimPtr);
		SetT_FileName(pAimPtr);
		SetT_ZoomTime(pAimPtr);
		//设置T波的延伸段时间
		m_setParams["T_ExtendTime"] = lexical_cast<string>(iTExtendTime);
		Set_CycleTime(pAimPtr);

		m_eQRS = eQRS;
		m_eRhythm = eRhythm;
		m_uHR     = uHR;
		//--------------------------------------------------------------
		++m_nStepNum;
		m_nStepNum = m_nStepNum % m_nSumStepNum;
		if( m_eRefurbishDataRange == RD_NoChange )
		{
			m_eRefurbishDataRange = RD_MainSegmentData;
		}
	}

	//加载对应的早波的数据参数
	void CCardiogram2degree_AVBIParam_I12::LoadExtrasystParamPre(Extrasys eExtrasyst)
	{
		bool   bAddStepNum = true;
		if(m_nStepNum == 0)
		{
			LoadCardiogramParam(m_eQRS,m_eRhythm,m_uHR,m_nSumStepNum);
			//不增加m_nStepNum
			bAddStepNum  = false;
		}

		string   strAimPtr[4];
		switch(eExtrasyst)
		{
		case ES_None:
		case Unifocal_PVC:  //单形性室性早搏
		case Multifocal_PVC://多形性室性早搏
			{
				//各数值的含义：早波段时间；相对向左延伸时间；向左延伸值；周期时间
				static string strUnifocalPVC_Params[][4] = {
                    {"4500","5400","0","12000"}, //50:400
                    {"4500","7500","0","24000"}, //50:2400
                    {"4500","8600","0","24000"}, //50:3900
                    {"4500","9700","0","24000"}, //50:5200

                    {"4500","5500","0","10900"}, //55:400
                    {"4500","6700","0","21800"}, //55:1800
                    {"4500","7500","0","21800"}, //55:2800
                    {"4500","8200","0","21800"}, //55:3800

                    {"4800","5150","0","10000"}, //60:300
                    {"4800","6200","0","20000"}, //60:1600
                    {"4800","7000","0","20000"}, //60:2500
                    {"4800","8200","0","20000"}, //60:4000

                    {"4800","4900","0","9200"}, //65:300
                    {"4800","5800","0","18400"}, //65:1400
                    {"4800","6400","0","18400"}, //65:2000
                    {"4800","8000","0","18400"}, //65:4000

                    {"4500","4500","0","8570"}, //70:300
                    {"4500","5200","0","17150"}, //70:1100
                    {"4500","5900","0","17150"}, //70:1800
                    {"4500","6500","0","17150"}, //70:2400

                    {"4500","4400","0","8000"}, //75:200
                    {"4500","5100","0","16000"}, //75:900
                    {"4500","5700","0","16000"}, //75:1500
                    {"4500","6200","0","16000"},  //75:2000
					//hjg 2013.5.30 add
                    {"4500","4400","0","15000"}, //80:200
                    {"4500","5100","0","15000"}, //80:900
                    {"4500","5500","0","15000"}, //80:1300
                    {"4500","6100","0","15000"},  //80:1800

                    {"4500","4400","0","14100"}, //85:200
                    {"4500","4700","0","14100"}, //85:500
                    {"4500","5200","0","14100"}, //85:1000
                    {"4500","5500","0","14100"},  //85:1300

                    {"4500","4400","0","13200"}, //90:200
                    {"4500","4600","0","13200"}, //90:400
                    {"4500","4900","0","13200"}, //90:700
                    {"4500","5200","0","13200"},  //90:1000

                    {"4500","4300","0","12600"}, //95:100
                    {"4500","4500","0","12600"}, //95:300
                    {"4500","4700","0","12600"}, //95:500
                    {"4500","4900","0","12600"},  //95:700

                    {"4500","4300","0","12000"}, //100:100
                    {"4500","4500","0","12000"}, //100:300
                    {"4500","4700","0","12000"}, //100:500
                    {"4500","4900","0","12000"}   //100:700
				};
				int  iHRStep = ( (m_uHR / 5) * 5 - 50 )/5;
				for (int nStep = 0; nStep < 4; ++nStep)
				{
					strAimPtr[nStep] = strUnifocalPVC_Params[iHRStep*4+m_nStepNum][nStep];
				}
				if( (m_uHR % 5) != 0 )
				{
					int nCycleTime = (1200000 / m_uHR ) / 50 * 50;
					if( m_nStepNum == 0 )
					{
						nCycleTime = (600000 / m_uHR ) / 50 * 50;
					}
					strAimPtr[3] = lexical_cast<int>(nCycleTime);
				}
				break;
			}
		case PVC_RonT://室性早搏RonT
			{
				//各数值的含义：早波段时间；相对向左延伸时间；向左延伸值；周期时间
				static string strPVC_RonT_Params[][4] = {
                    {"4800","3000","0","10000"}, //50
                    {"4800","3000","0","10900"}, //55
                    {"4800","3000","0","10000"}, //60
                    {"4700","3000","0","9200"}, //65
                    {"4600","3000","0","8000"}, //70
                    {"4500","3000","0","8550"}, //75
					// hjg 2013.5.30 add
                    {"4500","3000","0","7500"}, //80
                    {"4500","3000","0","7050"}, //85
                    {"4500","3000","0","6650"}, //90
                    {"4500","3000","0","6300"}, //95
                    {"4500","3000","0","6000"} //100
				};
				int  iHRStep = ( (m_uHR / 5) * 5 - 50 )/5;
				for (int nStep = 0; nStep < 4; ++nStep)
				{
					strAimPtr[nStep] = strPVC_RonT_Params[iHRStep][nStep];
				}
				if( (m_uHR % 5) != 0 )
				{
					int nCycleTime = (600000 / m_uHR ) / 50 * 50;
					strAimPtr[3] = lexical_cast<int>(nCycleTime);
				}
				int iPExtendTime = lexical_cast<int>(m_setParams["P_ExtendTime"]);
				int iExtendLTime = iPExtendTime + 2800;
				strAimPtr[1] = lexical_cast<string>(iExtendLTime);
				break;
			}
		case Coupled_PVC://室性早搏显二联律
			{
				//各数值的含义：早波段时间；相对向左延伸时间；向左延伸值；周期时间
				static string strCoupled_PVC_Params[][4] = {
                    {"9600","5900","0","24000"}, //50:400
                    {"9600","7900","0","24000"}, //50:2400
                    {"9600","9000","0","24000"}, //50:3900
                    {"9600","10100","0","24000"}, //50:5200

                    {"9600","5100","0","21800"}, //55:400
                    {"9600","6300","0","21800"}, //55:1800
                    {"9600","7100","0","21800"}, //55:2800
                    {"9600","7900","0","21800"}, //55:3800

                    {"9600","5100","0","20000"}, //60:300
                    {"9600","6300","0","20000"}, //60:1600
                    {"9600","7100","0","20000"}, //60:2500
                    {"9600","7900","0","20000"}, //60:4000

                    {"9400","4300","0","18400"}, //65:300
                    {"9400","5300","0","18400"}, //65:1400
                    {"9400","6000","0","18400"}, //65:2000
                    {"9400","7500","0","18400"}, //65:4000

                    {"9200","4200","0","17150"}, //70:300
                    {"9200","4900","0","17150"}, //70:1100
                    {"9200","5400","0","17150"}, //70:1800
                    {"9200","6000","0","17150"}, //70:2400

                    {"9000","4100","0","16000"}, //75:200
                    {"9000","4800","0","16000"}, //75:900
                    {"9000","5400","0","16000"}, //75:1500
                    {"9000","5900","0","16000"},  //75:2000

					//hjg 2013.5.30 add
                    {"9000","4400","0","15000"}, //80:200
                    {"9000","5100","0","15000"}, //80:900
                    {"9000","5500","0","15000"}, //80:1300
                    {"9000","6100","0","15000"},  //80:1800

                    {"9000","4400","0","14100"}, //85:200
                    {"9000","4700","0","14100"}, //85:500
                    {"9000","5200","0","14100"}, //85:1000
                    {"9000","5500","0","14100"},  //85:1300

                    {"9000","4400","0","13200"}, //90:200
                    {"9000","4600","0","13200"}, //90:400
                    {"9000","4900","0","13200"}, //90:700
                    {"9000","5200","0","13200"},  //90:1000

                    {"9000","4300","0","12600"}, //95:100
                    {"9000","4500","0","12600"}, //95:300
                    {"9000","4700","0","12600"}, //95:500
                    {"9000","4900","0","12600"},  //95:700

                    {"9000","4300","0","12000"}, //100:100
                    {"9000","4500","0","12000"}, //100:300
                    {"9000","4700","0","12000"}, //100:500
                    {"9000","4900","0","12000"}   //100:700
				};
				int  iHRStep = ( (m_uHR / 5) * 5 - 50 )/5;
				for (int nStep = 0; nStep < 4; ++nStep)
				{
					strAimPtr[nStep] = strCoupled_PVC_Params[iHRStep*4+m_nStepNum][nStep];
				}
				if( (m_uHR % 5) != 0 )
				{
					int nCycleTime = (1200000 / m_uHR ) / 50 * 50;
					strAimPtr[3] = lexical_cast<string>(nCycleTime);
				}
				break;
			}
		}
		m_setParams["ES_Time"] = strAimPtr[0];//早波段时间
		int iES_LExtendTime = lexical_cast<int>(strAimPtr[1]);
		m_setParams["ES_LExtentTime"] = strAimPtr[1];//向左延伸时间
		m_setParams["ES_LExtentValue"] = strAimPtr[2];//向左延伸值

		int iES_RExtendTime = lexical_cast<int>(strAimPtr[3])-iES_LExtendTime - lexical_cast<int>(strAimPtr[0]);
		if(iES_RExtendTime < 0) 
			iES_RExtendTime = 0;
		m_setParams["ES_RExtentTime"] = lexical_cast<string>(iES_RExtendTime);
		
		m_setParams["CycleTime"] = strAimPtr[3];//周期时间
		//设置下次创建周期数据时的操作范围
		m_eRefurbishDataRange = RD_AllData;
	
		if( bAddStepNum == TRUE )
		{
			++m_nStepNum;
			m_nStepNum = m_nStepNum % m_nSumStepNum;
		}
	}

	string CCardiogram2degree_AVBIParam_I12::GetExtrasystFileName(Extrasys eExtrasyst, const string &strKey)
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

	//产生心电时，血氧的启动时间
	bool CCardiogram2degree_AVBIParam_I12::GetSpO2BeginTimeToCardiogram(/*out*/long &lBeginTime, /*out*/long &lCycleTime)
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
		if( m_bEmptQRS  )
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
		return true;
	}

	//产生早博时，血氧的启动时间
	bool CCardiogram2degree_AVBIParam_I12::GetSpO2BeginTimeToExtrasyst(/*out*/long &lBeginTime, /*out*/long &lPreSpO2BeginTime, /*out*/long &lCycleTime)
	{
		lBeginTime = 0;
		string strKey, strValue;
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

	//是否有缺省的早播
	bool CCardiogram2degree_AVBIParam_I12::IsHaveDefalutExtrasyst()
	{
		return m_nStepNum == (m_nSumStepNum -1) ? false : true;
	}

	void CCardiogram2degree_AVBIParam_I12::ReLoadCardiogramParam()
	{
		LoadCardiogramParam(m_eQRS,m_eRhythm,m_uHR, m_nSumStepNum);
	}

}}}
