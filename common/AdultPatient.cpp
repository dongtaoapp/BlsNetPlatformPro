#include ".\AdultPatient.h"

#include <boost/format.hpp>

namespace jysoft { namespace simulator {

	CAdultPatient::CAdultPatient(void)
	{
	}


	CAdultPatient::~CAdultPatient(void)
	{
	}

	void CAdultPatient::initialPatient(const std::string &configuePath)
	{
		boost::format fm("%s\\laug\\parameter.xml");
		fm % configuePath;
		refLexical_cast.translateReferFile( fm.str() );
	}
	//-------------------------------------------------------------------------------------------------
	//接口IRhythmRule重载函数
	//返回心律的显示名称
	std::string CAdultPatient::GetRhythmDisplayTxt(const std::string &strRhythm)
	{
		std::string   rhythmDisplayTxt;
        const  std::string  propCode = "ecg_name";
		return refLexical_cast.doReferLexical_cast(propCode, strRhythm, &rhythmDisplayTxt) ? rhythmDisplayTxt : strRhythm;
	}

	//返回早搏的显示名称
	std::string CAdultPatient::GetExtrasysDisplayTxt(const std::string &strExtrasys)
	{
		std::string  extrasysDisplayTxt;
        const  std::string  propCode = "ecg_name";
		return refLexical_cast.doReferLexical_cast(propCode, strExtrasys, &extrasysDisplayTxt) ? extrasysDisplayTxt : strExtrasys;
	}

	// 返回所有的基本节率名称
	void CAdultPatient::GetBasicRhythm(std::list<std::string> & lstStrings)
	{
		//窦性心律
		lstStrings.push_back("Sinus");    
		//伴有心肌缺血的窦性心律
		lstStrings.push_back("Sinus Ischemia");    
		//伴有损伤性心肌缺血的窦性心律
		lstStrings.push_back("Sinus InjureIschemia");    
		//有下急性心肌梗死的窦律，ST抬高
		lstStrings.push_back("Sinus InferiorAMI ST");
		//有前壁急性心肌梗死的窦律，ST抬高
		lstStrings.push_back("Sinus AnteriorAMI ST");
		//有前壁急性心肌梗死的窦律，后期
		//lstStrings.AddTail(_T("Sinus AnteriorAMI Late"));
		//伴有左束支阻滞的窦性心律
		lstStrings.push_back("LBBB");
		//伴有右束支阻滞的窦性心律
		lstStrings.push_back("RBBB");
		//左心室肥大的窦性心律
		lstStrings.push_back("Left Ventricular Hypertrophy");
		//右心室肥大的窦性心律
		lstStrings.push_back("Right Ventricular Hypertrophy");
		//双心室肥大的窦性心律
		lstStrings.push_back("Ventricular Hypertrophy");
		//高血钾的窦性心律
		lstStrings.push_back("Hyperkalemia");
		//WPW预激综合征
		lstStrings.push_back("WPW");
		//心电轴左偏
		lstStrings.push_back("Left Axis Deviation");
		//心电轴右偏
		lstStrings.push_back("Right Axis Deviation");
		//QT间期延长
		//lstStrings.AddTail(_T("Prolonged QT"));
		//洋地黄效应
		lstStrings.push_back("Digitalis Effect");
		//一度房室传导阻滞
		lstStrings.push_back("1 degree AVB"); 
		//二度Ⅰ型房室传导阻滞
		lstStrings.push_back("2 degree AVB Type-1");
		//二度Ⅱ型房室传导阻滞
		lstStrings.push_back("2 degree AVB Type-2");
		//三度房室传导阻滞
		lstStrings.push_back("3 degree AVB");
		//心室停顿(Ventricular Standstill)
		lstStrings.push_back("Ventr.standstill");
		//室上性心动过速（SVT）
		lstStrings.push_back("P.tach"); 
		//心房扑动（A.flutt）
		lstStrings.push_back("A.flutt.");
		//心房颤动（Afib）
		lstStrings.push_back("A.fib.");
		//交界性心律(Junct.)
		lstStrings.push_back("Junct."); 
		//心室扑动
		lstStrings.push_back("V.flutt.");
		//室性逸搏心律Idioventricular
		lstStrings.push_back("Idiov.");
		//室性心动过速（V.tach）
		lstStrings.push_back("V.tach");
		//尖端扭转型室性心动过速Torsade.de Pointes
		lstStrings.push_back("Torsade.de Pointes"); 
		//心室颤动（VF）
		lstStrings.push_back("V.fibr");
		//临死前心律
		lstStrings.push_back("Asystole");
		//lstStrings.AddTail(_T("Agonal rhythm"));
		//房室顺序起搏(Pacem.AV-seq.)
		lstStrings.push_back("Pacem.Attr");
		lstStrings.push_back("Pacem.AV-seq.");
		//起搏器失去夺获
		lstStrings.push_back("Pacem.LOC");
		lstStrings.push_back("Die");
	}

	// 返回基本节率对应的心率值范围，并返回缺省的心率
	short CAdultPatient::GetHRsForRhythm(BasicRhythm eRhythm, short &sMinValue, short &sMaxValue)
	{
		short  sDefaultHR = 0;
		switch (eRhythm)
		{
		case BR_Sinus:
		case BR_Sinus_Doubt:
		case BR_Sinus_NoPulse:
		case BR_Sinus_Ischemia:
		case BR_Sinus_InjureIschemia:
		case BR_Sinus_InferiorAMI_ST:
		case BR_Sinus_AnteriorAMI_ST:
		case BR_Sinus_AnteriorAMI_Late:
		case BR_Sinus_LBBB:
		case BR_Sinus_RBBB:
		case BR_Sinus_LeftHypertrophy:
		case BR_Sinus_RightHypertrophy:
		case BR_Sinus_Hypertrophy:
		case BR_Sinus_Hyperkalemia:
		case BR_Sinus_WPW:
		case BR_Sinus_LeftAxis_Deviation:
		case BR_Sinus_RightAxis_Deviation:
			{
				sMinValue  = 20;
				sMaxValue  = 200;
				sDefaultHR = 80;
				break;
			}
		case BR_Sinus_Prolonged_QT:  //QT间期延长
			{
				sMinValue  = 20;
				sMaxValue  = 200;
				sDefaultHR = 80;
				break;
			}
		case BR_DigitalisEffect:
			{
				sMinValue  = 20;
				sMaxValue  = 120;
				sDefaultHR = 80;
				break;
			}
		case BR_1degree_AVB:
			{
				sMinValue  = 20;
				sMaxValue  = 150;
				sDefaultHR = 70;
				break;
			}
		case BR_2degree_AVB_I:
			{
				sMinValue  = 50;
				sMaxValue  = 75;
				sDefaultHR = 60;
				break;
			}
		case BR_2degree_AVB_II:
			{
				sMinValue  = 50;
				sMaxValue  = 90;
				sDefaultHR = 60;
				break;
			}
		case BR_3degree_AVB:
			{
				sMinValue  = 30;
				sMaxValue  = 60;
				sDefaultHR = 30;
				break;
			}
		case BR_Asystole:
		case BR_Ventr_Standstill:
			{
				sMinValue  = 0;
				sMaxValue  = 0;
				sDefaultHR = 0;
				break;
			}
		case BR_ParoxysmalTach: //阵发性室上性心动过速
			{
				sMinValue  = 160;
				sMaxValue  = 280;
				sDefaultHR = 230;
				break;
			}
		case BR_PSVtach:
			{
				sMinValue  = 150;
				sMaxValue  = 250;
				sDefaultHR = 180;
				break;
			}
		case BR_AFlutt:
			{
				sMinValue  = 60;
				sMaxValue  = 150;
				sDefaultHR = 150;
				break;
			}
		case BR_Junct:          //交界性心律
			{
				sMinValue  = 30;
				sMaxValue  = 150;
				sDefaultHR = 50;
				break;
			}
		case BR_AFib:       //房颤
			{
				sMinValue  = 50;
				sMaxValue  = 200;
				sDefaultHR = 160;
				break;
			}
		case BR_Idiov:
			{
				sMinValue  = 20;
				sMaxValue  = 100;
				sDefaultHR = 70;
				break;
			}
		case BR_VTach: //室性心动过速
			{
				sMinValue  = 150;
				sMaxValue  = 240;
				sDefaultHR = 180;
				break;
			}
		case BR_Torsade_DP:
			{
				sMinValue = sMaxValue = 200;
				sDefaultHR = 200;
				break;
			}
		case BR_VFibr:
		case BR_Die:
			{
				sMinValue = sMaxValue = 0;
				sDefaultHR = 0;
				break;
			}
		case BR_AgonalRhythm:
			{
				sMinValue  = 1;
				sMaxValue  = 40;
				sDefaultHR = 8;
				break;
			}
		case BR_VFlutt:           //室扑
			{
				sMinValue  = 150;
				sMaxValue  = 300;
				sDefaultHR = 150;
				break;
			}
		case BR_PacemakerAtr:
		case BR_PacemakerAV_Seq:
		case BR_PacemakerLoc:
			{
				sMinValue  = 50;
				sMaxValue  = 100;
				sDefaultHR = 70;
				break;
			}
		}
		return sDefaultHR;
	}

	// 返回对应节率对应的所有早搏，并返回缺省值。如果没有返回false
	bool CAdultPatient::GetExtraSystsToRhythm(BasicRhythm eRhythm, std::list<std::string> * plstExtras)
	{
		if(eRhythm == BR_None)
			return false;
		switch (eRhythm)
		{
		case BR_Sinus:
		case BR_Sinus_Doubt:
		case BR_Sinus_NoPulse:
		case BR_Sinus_Ischemia:
		case BR_Sinus_InjureIschemia:
		case BR_Sinus_InferiorAMI_ST:
		case BR_Sinus_AnteriorAMI_ST:
		case BR_Sinus_AnteriorAMI_Late:
		case BR_Sinus_LBBB:
		case BR_Sinus_RBBB:
		case BR_Sinus_LeftHypertrophy:
		case BR_Sinus_RightHypertrophy:
		case BR_Sinus_Hypertrophy:
		case BR_Sinus_Hyperkalemia:
		case BR_Sinus_WPW:
			//case BR_Sinus_LeftAxis_Deviation:
			//case BR_Sinus_RightAxis_Deviation:
		case BR_1degree_AVB:
			{
				if(plstExtras != NULL)
				{
					plstExtras->push_back("Unifocal PVC");
					plstExtras->push_back("PVC RonT");
					plstExtras->push_back("Coupled PVC");
					plstExtras->push_back("PJC");
					plstExtras->push_back("PAC");
				}
				break;
			}
		case BR_AFlutt:
		case BR_AFib:
		case BR_2degree_AVB_I:
		case BR_2degree_AVB_II:
		case BR_3degree_AVB:
			{
				if(plstExtras != NULL)
				{
					plstExtras->push_back("Unifocal PVC");
					plstExtras->push_back("PVC RonT");
					plstExtras->push_back("Coupled PVC");
				}
				break;
			}
		}
		return true;
	}

	//返回呼吸的模式类型
	void CAdultPatient::GetRespModes(std::list<std::string> & lstStrings)
	{
		lstStrings.clear();
		lstStrings.push_back( "Normal" );           //正常呼吸
		lstStrings.push_back("Kussmaul" );         //库斯莫尔呼吸
		lstStrings.push_back("Stokes" );           //陈施呼吸/潮式呼吸模式
		lstStrings.push_back("Biots" );
		lstStrings.push_back("Sign" );             //叹气样呼吸
		lstStrings.push_back("Apnea" );
	}

	//返回呼吸模式的缺省呼吸次数
	long CAdultPatient::GetRespModeDefaultRate(eRespMode eMode)
	{
		long  lRespRate = 0;
		switch( eMode )
		{
		case RM_Normal: 
			{
				lRespRate = 14;
				break;
			}
		case RM_Stokes:
			{
				lRespRate  = 0;
				break;
			}
		case RM_Biots:
			{
				lRespRate = 15;
				break;
			}
		case RM_Sign:
			{
				lRespRate  = 20;
				break;
			}
		case RM_Apnea:
			{
				lRespRate = 0;
				break;
			}
		}
		return lRespRate;
	}

	//返回呼吸模式显示名称
	std::string CAdultPatient::GetRespModeDisplayTxt(const std::string  &strRespMode)
	{
		std::string  respModeDisplayTxt;
		const std::string   propCode = "resp_name";
		return refLexical_cast.doReferLexical_cast(propCode, strRespMode, &respModeDisplayTxt) ? respModeDisplayTxt : strRespMode;
	}
}}
