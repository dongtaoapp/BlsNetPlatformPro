#include <boost/lexical_cast.hpp>
#include ".\Cardiogram1degree_AVBParam_I12.h"


namespace jysoft { namespace simulator { namespace ecg {

	CCardiogram1degree_AVBParam_I12::CCardiogram1degree_AVBParam_I12( IStorage *pRootStorage )
								: CVirCardiogramParam()
	{
		m_pStorages  = pRootStorage;
	}

	CCardiogram1degree_AVBParam_I12::~CCardiogram1degree_AVBParam_I12(void)
	{
	}

	//加载参数值
    void CCardiogram1degree_AVBParam_I12::LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm,int uHR, short sConduct/*=0*/, short sExtendParam/*=0*/)
	{
		//设置范围内的心率值
		if( uHR < 20 )
		{
			uHR  = 20;
		}
		else if( uHR > 160 )
		{
			uHR  = 160;
		}
		//各数值的含义：p段文件名；缩放时间；水平间隔延伸时间；R段文件名；缩放时间；水平间隔延伸时间；T段文件名；缩放时间；水平间隔延伸时间；周期时间
		std::string strParams[][10] = {
            {"P.txt","1200","2150","A_R.txt","1000","900","A_T.txt","2200","22550","30000"},//20HR
            {"P.txt","1200","2150","A_R.txt","1000","900","A_T.txt","2200","12550","20000"},//30HR
            {"P.txt","1200","2100","A_R.txt","1000","900","A_T.txt","2200","7600","15000"}, //40HR
            {"P.txt","1200","2000","A_R.txt","1000","900","A_T.txt","2200","4700","12000"}, //50HR
            {"P.txt","1200","1800","A_R.txt","1000","900","A_T.txt","2200","2900","10000"}, //60HR
            {"P.txt","1200","1700","A_R.txt","1000","900","A_T.txt","2200","1600","8600"}, //70HR
            {"P.txt","1200","1500","A_R.txt","1000","900","A_T.txt","2200","700","7500"}, //80HR
            {"P.txt","1200","1300","A_R.txt","1000","900","A_T.txt","2000","0","6600"}, //90H
            {"P.txt","1200","1300","A_R.txt","1000","900","A_T.txt","1900","0","6300"}, //95HR
            {"P.txt","1200","1200","A_R.txt","1000","700","A_T.txt","1900","0","6000"},  //100HR
            {"P.txt","1200","1200","A_R.txt","1000","600","A_T.txt","1900","0","5700"},  //105HR
            {"P.txt","1200","1000","A_R.txt","900","600","A_T.txt","1900","0","5625"},    //110HR
            {"P.txt","1200","1000","A_R.txt","925","500","A_T.txt","1900","0","5200"},    //115HR
            {"P.txt","1200","950","A_R.txt","925","350","A_T.txt","1700","0","5100"},   //120HR*
            {"P.txt","1150","950","A_R.txt","925","350","A_T.txt","1700","0","4800"},   //125HR
            {"P.txt","1150","900","A_R.txt","925","350","A_T.txt","1700","0","4600"},   //130HR
            {"P.txt","1150","900","A_R.txt","925","250","A_T.txt","1650","0","4450"},   //135HR
            {"P.txt","1150","900","A_R.txt","925","250","A_T.txt","1650","0","4275"},    //140HR*
            {"P.txt","1050","900","A_R.txt","900","250","A_T.txt","1600","0","4150"},    //145HR
            {"P.txt","1050","900","A_R.txt","900","250","A_T.txt","1600","0","4000"},    //150HR
            {"P.txt","1050","800","A_R.txt","900","200","A_T.txt","1500","0","3875"},    //155HR
            {"P.txt","1050","800","A_R.txt","900","200","A_T.txt","1500","0","3750"}     //160HR*
		};
		std::string *pAimPtr = NULL;
		if(uHR <= 90)
		{
			int iMove  = uHR%10;
			if( iMove == 0 )
			{
				int iHRStep = uHR/10 - 2;
				pAimPtr = strParams[ iHRStep ];
			}
			else
			{
				int iHRStep = uHR/10 - 1;
				pAimPtr     = strParams[ iHRStep ];
				int nCycleTime = ((600000 / uHR) / 50) * 50;
				int nExtendTime;
				nExtendTime = boost::lexical_cast<int>( pAimPtr[8] );
				nExtendTime    = nExtendTime+(nCycleTime-(boost::lexical_cast<int>( pAimPtr[9] )));
			}
		}
		else
		{
			int iHRStep = ((uHR / 5) * 5 - 90)/5 + 7;
			pAimPtr = strParams[ iHRStep ];
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
			if(m_eQRS != QRS_F)
				m_eRefurbishDataRange = RD_OpSegmentData;
			else
				m_eRefurbishDataRange = RD_AllData;
		}
		if( m_uHR != uHR || m_eQRS != eQRS )
		{
			std::string  strHR = boost::lexical_cast<std::string>(uHR);
			m_setParams["HR"] = strHR;
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
	}

	//加载对应的早波的数据参数
	void CCardiogram1degree_AVBParam_I12::LoadExtrasystParam(Extrasys eExtrasyst)
	{
		//设置下次创建周期数据时的操作范围
		m_eRefurbishDataRange = RD_MainSegmentData;
		std::string *pAimPtr = NULL;
		int iHRSum = 21;
		int iHRStep = m_uHR/10 - 2;
		int iMove = m_uHR%10;
		switch(eExtrasyst)
		{
		case ES_None:
		case Unifocal_PVC:  //单形性室性早搏
		case Multifocal_PVC://多形性室性早搏
			{
				//各数值的含义：早波段时间；向左延伸时间；向左延伸值；向右延伸时间；向右延伸值；周期时间
				static std::string strUnifocalPVC_Params[][6] = {
                    {"4800","13200","0","12000","0","30000"},//20
                    {"4800","11700","0","3500","0","20000"}, //30
                    {"4800","9700","0","500","0","15000"}, //40
                    {"4800","9100","0","0","0","12000"}, //50
                    {"4800","8600","0","6600","0","20000"}, //60
                    {"4500","8000","0","4700","0","17200"}, //70
                    {"4500","7100","0","3400","0","15000"}, //80
                    {"4500","6700","0","2000","0","13200"}, //90
                    {"4500","6500","0","1000","0","12000"}, //100
                    {"4500","6350","0","650","0","11500"}, //105
                    {"4500","6200","0","300","0","11000"}, //110
                    {"4500","5950","0","500","0","10550"}, //115
                    {"4500","5700","0","700","0","10100"}, //120
                    {"4500","5550","0","525","0","9725"}, //125
                    {"4500","5400","0","350","0","9350"}, //130
                    {"4500","5250","0","175","0","8975"}, //135
                    {"4500","5100","0","0","0","8600"}, //140
                    {"4175","5000","0","0","0","8375"}, //145
                    {"3850","4900","0","0","0","8150"}, //150
                    {"3525","4800","0","0","0","7925"}, //155
                    {"3200","4700","0","0","0","7700"}  //160
				};
				if(m_uHR <= 100)
				{
					pAimPtr = strUnifocalPVC_Params[iHRStep];
					if(iMove!=0)
					{
						int first,next;
						std::string *strTemp = strUnifocalPVC_Params[iHRStep+1];
						int p[4]={0,1,3,5};
						for(int i=0;i<4;i++)
						{
							int n=p[i];
							first = boost::lexical_cast<int>( pAimPtr[n] );
							next  = boost::lexical_cast<int>( strTemp[n] );
							if(first != next)
							{
								int temp;
								if(abs(next-first) < 250)
								{
									if(iMove>5)
									{
										temp = ((next-first)/2/25)*25;
										first += temp;
										pAimPtr[n] = boost::lexical_cast<std::string>(first);
									}

								}
								else
								{
									temp = ((next-first)/10/25)*25;
									first += temp*iMove;
									pAimPtr[n] = boost::lexical_cast<std::string>(first);
								}
							}
						}
					}
				}
				else
				{
					int iHRStep = ((m_uHR / 5) * 5 - 100)/5 + 8;
					pAimPtr = strUnifocalPVC_Params[iHRStep];
				}
				break;
			}
		case PVC_RonT://室性早搏RonT
			{
				//各数值的含义：早波段时间；向左延伸时间；向左延伸值；向右延伸时间；向右延伸值；周期时间
				static std::string strPVC_RonT_Params[][6] = {
                    {"4800","5250","0","19000","0","30000"},//20
                    {"4800","5250","0","12500","0","20000"}, //30
                    {"4800","5200","0","4000","0","15000"}, //40
                    {"4800","5100","0","1100","0","12000"}, //50
                    {"4800","4900","0","0","0","10000"}, //60
                    {"4500","4800","0","0","0","8500"}, //70
                    {"4500","4600","0","0","0","7500"}, //80
                    {"4500","4400","0","3500","0","13200"}, //90
                    {"4500","4400","0","2200","0","12000"}, //100
                    {"4500","4000","0","1750","0","11500"}, //105
                    {"4500","3700","0","1300","0","11000"}, //110
                    {"4500","3625","0","1150","0","10550"}, //115
                    {"4500","3425","0","1000","0","10100"}, //120
                    {"4275","3325","0","750","0","9725"}, //125
                    {"4050","3225","0","500","0","9350"}, //130
                    {"3825","3125","0","250","0","8975"}, //135
                    {"3600","3125","0","0","0","8600"}, //140
                    {"3500","3100","0","0","0","8375"}, //145
                    {"3400","3100","0","0","0","8150"}, //150
                    {"3300","3100","0","400","0","7925"}, //155
                    {"3200","3100","0","800","0","7700"}  //160
				};
				//pAimPtr = strPVC_RonT_Params[iHRStep];
				if(m_uHR <= 100)
				{
					pAimPtr = strPVC_RonT_Params[iHRStep];
					if(iMove!=0)
					{
						int first,next;
						std::string *strTemp = strPVC_RonT_Params[iHRStep+1];
						int p[4]={0,1,3,5};
						for(int i=0;i<4;i++)
						{
							int n=p[i];
							first = boost::lexical_cast<int>( pAimPtr[n] );
							next = boost::lexical_cast<int>( strTemp[n] );
							if(first != next)
							{
								int temp;
								if(abs(next-first)<250)
								{
									if(iMove>5)
									{
										temp = ((next-first)/2/25)*25;
										first += temp;
										pAimPtr[n] = boost::lexical_cast<std::string>(first);
									}

								}
								else
								{
									temp = ((next-first)/10/25)*25;
									first += temp*iMove;
									pAimPtr[n] = boost::lexical_cast<std::string>( first );
								}
							}
						}
					}
				}
				else
				{
					int iHRStep = ((m_uHR / 5) * 5 - 100)/5 + 8;
					pAimPtr = strPVC_RonT_Params[iHRStep];
				}
				break;
			}
		case Coupled_PVC://室性早搏显二联律
			{
				//各数值的含义：早波段时间；向左延伸时间；向左延伸值；向右延伸时间；向右延伸值；周期时间
				static std::string strCoupled_PVC_Params[][6] = {
                    {"9750","13200","0","7050","0","30000"},//20
                    {"9750","11600","0","0","0","20000"}, //30
                    {"9750","9700","0","2250","0","30000"}, //40
                    {"9750","9100","0","6750","0","24000"}, //50
                    {"9750","8600","0","3250","0","20000"}, //60
                    {"9750","7900","0","750","0","17000"}, //70
                    {"9000","7100","0","0","0","15100"}, //80
                    {"9000","6700","0","0","0","13200"}, //90
                    {"9000","6500","0","2500","0","18000"}, //100
                    {"9000","6350","0","1900","0","17250"}, //105
                    {"9000","6200","0","1300","0","16500"}, //110
                    {"9000","5975","0","850","0","15825"}, //115
                    {"9000","5750","0","400","0","15150"}, //120
                    {"9000","5575","0","300","0","14600"}, //125
                    {"9000","5375","0","200","0","14025"}, //130
                    {"9000","5200","0","100","0","13475"}, //135
                    {"9000","5000","0","0","0","12900"}, //140
                    {"8375","4950","0","75","0","12575"}, //145
                    {"7750","4875","0","150","0","12225"}, //150
                    {"7125","4825","0","225","0","11900"}, //155
                    {"6500","4750","0","300","0","11550"}  //160
				};
				//pAimPtr = strCoupled_PVC_Params[iHRStep];
				if(m_uHR <= 100)
				{
					pAimPtr = strCoupled_PVC_Params[iHRStep];
					if(iMove!=0)
					{
						int first,next;
						std::string *strTemp = strCoupled_PVC_Params[iHRStep+1];
						int p[4] = {0,1,3,5};
						for(int i=0;i<4;i++)
						{
							int n=p[i];
							first = boost::lexical_cast<int>( pAimPtr[n] );
							next = boost::lexical_cast<int>( strTemp[n] );
							if(first!=next)
							{
								int temp;
								if(abs(next-first)<250)
								{
									if(iMove>5)
									{
										temp = ((next-first)/2/25)*25;
										first += temp;
										pAimPtr[n] = boost::lexical_cast<std::string>( first );
									}
								}
								else
								{
									temp = ((next-first)/10/25)*25;
									first += temp*iMove;
									pAimPtr[n] = boost::lexical_cast<std::string>(first);
								}
							}
						}
					}
				}
				else
				{
					int iHRStep = ((m_uHR / 5) * 5 - 100)/5 + 8;
					pAimPtr = strCoupled_PVC_Params[iHRStep];
				}
				break;
			}
		case PAC://房性早搏
			{
				m_eRefurbishDataRange = RD_AllData;//重新加载所有的数据
				//各数值的含义：早波段时间；向左延伸时间；向左延伸值；向右延伸时间；向右延伸值；周期时间；
				static std::string strPAC_Params[][7] = {
                    {"5600","20000","0","27400","0","53000"},//20HR
                    {"5600","10000","0","16900","0","32500"},//30HR
                    {"5600","9000","0","11400","0","26000"},//40HR
                    {"5600","8000","0","8200","0","21800"},//50HR
                    {"5600","7000","0","6000","0","18600"},//60HR
                    {"5600","6000","0","4300","0","15900"},//70HR
                    {"5600","5000","0","3200","0","13800"},//80HR
                    {"5600","4500","0","2200","0","12300"},//90HR
                    {"5600","4000","0","1400","0","10000"},//100HR
                    {"5600","3850","0","1100","0","10050"},//105HR
                    {"5600","3700","0","800","0","10100"},//110HR
                    {"5150","3600","0","1000","0","9750"},//115HR
                    {"4700","3500","0","1200","0","9400"},//120HR
                    {"4625","3375","0","1025","0","9025"},//125HR
                    {"4550","3250","0","850","0","8650"},//130HR
                    {"4475","3125","0","675","0","8275"},//135HR
                    {"4400","3000","0","500","0","7900"},//140HR
                    {"4300","3000","0","475","0","7775"},//145HR
                    {"4200","3000","0","450","0","7650"},//150HR
                    {"4100","3000","0","425","0","7525"},//155HR
                    {"4000","3000","0","400","0","7400"} //160HR
				};
				//pAimPtr = strPAC_Params[iHRStep];
				if(m_uHR <= 100)
				{
					pAimPtr = strPAC_Params[iHRStep];
					if(iMove!=0)
					{
						int first,next;
						std::string *strTemp = strPAC_Params[iHRStep+1];
						int p[4]={0,1,3,5};
						for(int i=0;i<4;i++)
						{
							int n=p[i];
							first = boost::lexical_cast<int>( pAimPtr[n] );
							next = boost::lexical_cast<int>( strTemp[n] );
							if(first!=next)
							{
								int temp;
								if(abs(next-first)<250)
								{
									if(iMove>5)
									{
										temp = ((next-first)/2/25)*25;
										first += temp;
										pAimPtr[n] = boost::lexical_cast<std::string>( first );
									}

								}
								else
								{
									temp = ((next-first)/10/25)*25;
									first += temp*iMove;
									pAimPtr[n] = boost::lexical_cast<std::string>( first);
								}
							}
						}
					}
				}
				else
				{
					int iHRStep = ((m_uHR / 5) * 5 - 100)/5 + 8;
					pAimPtr = strPAC_Params[iHRStep];
				}
				m_setParams["P_FileName"] = "P_2.txt";
				break;
			}
		case PJC:
			{
				m_eRefurbishDataRange = RD_AllData;//重新加载所有的数据
				//各数值的含义：早波段时间；向左延伸时间；向左延伸值；向右延伸时间；向右延伸值；周期时间；
				static std::string strPAC_Params[][7] = {
                    {"-1","21500","0","27400","0","53000"},//20HR
                    {"-1","11500","0","16900","0","32500"},//30HR
                    {"-1","10500","0","11400","0","26000"},//40HR
                    {"-1","9500","0","8200","0","21800"},//50HR
                    {"-1","8500","0","6000","0","18600"},//60HR
                    {"-1","7500","0","4300","0","15900"},//70HR
                    {"-1","6500","0","3200","0","13800"},//80HR
                    {"-1","6000","0","2200","0","12300"},//90HR
                    {"-1","5500","0","1400","0","10000"},//100HR
                    {"-1","5350","0","1100","0","10050"},//105HR
                    {"-1","5200","0","800","0","10100"},//110HR
                    {"-1","5100","0","1000","0","9750"},//115HR
                    {"-1","5000","0","1200","0","9400"},//120HR
                    {"-1","4875","0","1000","0","9025"},//125HR
                    {"-1","4750","0","800","0","8650"},//130HR
                    {"-1","4625","0","600","0","8275"},//135HR
                    {"-1","4500","0","400","0","7900"},//140HR
                    {"-1","4425","0","400","0","7775"},//145HR
                    {"-1","4350","0","400","0","7650"},//150HR
                    {"-1","4275","0","400","0","7525"},//155HR
                    {"-1","4200","0","400","0","7400"} //160HR
				};
				//pAimPtr = strPAC_Params[iHRStep];
				if(m_uHR <= 100)
				{
					pAimPtr = strPAC_Params[iHRStep];
					if(iMove!=0)
					{
						int first,next;
						std::string *strTemp = strPAC_Params[iHRStep+1];
						int p[3]={1,3,5};
						for(int i=0;i<3;i++)
						{
							int n=p[i];
							first = boost::lexical_cast<int>( pAimPtr[n] );
							next = boost::lexical_cast<int>( strTemp[n] );
							if(first != next)
							{
								int temp;
								if(abs(next-first)<250)
								{
									if(iMove>5)
									{
										temp = ((next-first)/2/25)*25;
										first += temp;
										pAimPtr[n] = boost::lexical_cast<std::string>( first );
									}
								}
								else
								{
									temp = ((next-first)/10/25)*25;
									first += temp*iMove;
									pAimPtr[n] = boost::lexical_cast<std::string>( first );
								}
							}
						}
					}
				}
				else
				{
					int iHRStep = ((m_uHR / 5) * 5 - 100)/5 + 8;
					pAimPtr = strPAC_Params[iHRStep];
				}
				m_setParams["P_FileName"] = "Empty_Data.txt";
				m_setParams["P_ZoomTime"] = "0";
				m_setParams["P_ExtendTime"] = "0";
				break;
			}
		}
		m_setParams["ES_Time"] = pAimPtr[0];//早波段时间
		m_setParams["ES_LExtentTime"] = pAimPtr[1];//向左延伸时间
		m_setParams["ES_LExtentValue"] = pAimPtr[2];//向左延伸值
		m_setParams["ES_RExtentTime"] =  pAimPtr[3];//向右延伸时间
		m_setParams["ES_RExtentValue"] = pAimPtr[4];//向右延伸值
		m_setParams["ES_OverlapTime"] = "0";//覆盖区域时间点
		m_setParams["CycleTime"] = pAimPtr[5];//周期时间
	}

	void CCardiogram1degree_AVBParam_I12::LoadExtrasystParamPre(Extrasys eExtrasyst)
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

	std::string CCardiogram1degree_AVBParam_I12::GetExtrasystFileName(Extrasys eExtrasyst, const std::string &strKey)
	{
		std::string strExtrasystFileName;
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
				std::string strFileNames[3]; 
				strFileNames[0] = "Unifocal_PVC_A.txt";
				strFileNames[1] = "Unifocal_PVC_B.txt";
				strFileNames[2] = "Unifocal_PVC_E.txt";

				srand( (unsigned)time( NULL ) );
				int nMultiPVC_Step = rand() % 3;
				strExtrasystFileName = strFileNames[nMultiPVC_Step];
				break;
			}
		case PAC:
		case PJC:
			{
				break;
			}
		}
		return strExtrasystFileName;
	}

	//产生心电时，血氧的启动时间
	bool CCardiogram1degree_AVBParam_I12::GetSpO2BeginTimeToCardiogram(/*out*/long &lBeginTime, /*out*/long &lCycleTime)
	{
		lBeginTime = 0;
		std::string strKey, strValue;
		strKey = "P_ZoomTime";
		if( GetParamValue(strKey, strValue) )
		{
			lBeginTime += boost::lexical_cast<long>(strValue);
		}
		else
		{
            BOOST_ASSERT(0);
			return false;
		}
		strKey = "P_ExtendTime";
		if( GetParamValue(strKey, strValue) )
		{
			lBeginTime += boost::lexical_cast<long>(strValue);
		}
		else
		{
            BOOST_ASSERT(0);
			return false;
		}
        strKey = "R_ZoomTime";
		if( GetParamValue(strKey, strValue) )
		{
			lBeginTime += boost::lexical_cast<long>(strValue);
		}
		else
		{
            BOOST_ASSERT(0);
			return false;
		}
		lCycleTime = (long)GetCycleTime();
		return true;
	}

	//产生早博时，血氧的启动时间
	bool CCardiogram1degree_AVBParam_I12::GetSpO2BeginTimeToExtrasyst(/*out*/long &lBeginTime, /*out*/long &lPreSpO2BeginTime, /*out*/long &lCycleTime)
	{
		lBeginTime = 0;
		std::string strKey, strValue;
		strKey = "ES_Time";
		if( GetParamValue(strKey, /*out*/strValue) )
		{
			lBeginTime = boost::lexical_cast<long>(strValue);
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
			lBeginTime += boost::lexical_cast<long>(strValue);
		}
		else
		{
            BOOST_ASSERT(0);
			return false;
		}
		return GetSpO2BeginTimeToCardiogram(/*out*/lPreSpO2BeginTime, /*out*/lCycleTime);
	}

}}}
