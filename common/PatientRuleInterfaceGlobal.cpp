#include ".\PatientRuleInterfaceGlobal.h"

namespace jysoft { namespace simulator {
	//-----------------------------------------------------------------------------------------------------------
	//class IRhythmRule
	IRhythmRule::IRhythmRule()
	{
	}

	IRhythmRule::~IRhythmRule()
	{
	}

	QRS  IRhythmRule::Get_eQRS(const std::string &strQRS)
	{
		if(strQRS == "A")
		{
			return QRS_A;
		}
		if(strQRS == "B")
		{
			return QRS_B;
		}
		if(strQRS == "C")
		{
			return QRS_C;
		}
		if(strQRS == "D")
		{
			return QRS_D;
		}
		if(strQRS == "E")
		{
			return QRS_E;
		}
		if(strQRS == "F")
		{
			return QRS_F;
		}
		if(strQRS == "G")
		{
			return QRS_G;
		}
		return QRS_None;
	}

	std::string IRhythmRule::GetstrQRS(QRS eQRS)
	{
		switch(eQRS)
		{
		case QRS_A:
			return "A";
		case QRS_B:
			return "B";
		case QRS_C:
			return "C";
		case QRS_D:
			return "D";
		case QRS_E:
			return "E";
		case QRS_F:
			return "F";
		case QRS_G:
			return "G";
		}
		return "";
	}

	BasicRhythm IRhythmRule::Get_eRhythm(const std::string &strRhythm)
	{
		if(strRhythm.empty())
		{
			return BR_None;
		}
		if(strRhythm == "Sinus" || strRhythm == "Sinus  Unifocal PVC" || strRhythm == "Sinus  Coupled PVC" \
			|| strRhythm == "Sinus  PAC" || strRhythm == "Sinus  PJC" )
		{
			return BR_Sinus;
		}
		//伴有心肌缺血的窦性心律
		if( strRhythm == "Sinus Ischemia" )
		{
			return BR_Sinus_Ischemia;
		}
		//伴有损伤性心肌缺血的窦性心律
		if( strRhythm == "Sinus InjureIschemia" )
		{
			return BR_Sinus_InjureIschemia;
		}
		//有下急性心肌梗死的窦律，ST抬高
		if( strRhythm == "Sinus InferiorAMI ST" )
		{
			return BR_Sinus_InferiorAMI_ST;
		}
		//有前壁急性心肌梗死的窦律，ST抬高
		if( strRhythm == "Sinus AnteriorAMI ST" )
		{
			return BR_Sinus_AnteriorAMI_ST;
		}
		//有前壁急性心肌梗死的窦律，后期
		if( strRhythm == "Sinus AnteriorAMI Late" )
		{
			return BR_Sinus_AnteriorAMI_Late;
		}
		//伴有左束支阻滞的窦性心律
		if( strRhythm == "LBBB" )
		{
			return BR_Sinus_LBBB;
		}
		//伴有右束支阻滞的窦性心律
		if( strRhythm == "RBBB" )
		{
			return BR_Sinus_RBBB;
		}
		//左心室肥大的窦性心律
		if( strRhythm == "Left Ventricular Hypertrophy" )
		{
			return BR_Sinus_LeftHypertrophy;
		}
		//右心室肥大的窦性心律
		if( strRhythm == "Right Ventricular Hypertrophy" )
		{
			return BR_Sinus_RightHypertrophy;
		}
		//双心室肥大的窦性心律
		if( strRhythm == "Ventricular Hypertrophy" )
		{
			return BR_Sinus_Hypertrophy;
		}
		//高血钾的窦性心律
		if( strRhythm == "Hyperkalemia" )
		{
			return BR_Sinus_Hyperkalemia;
		}
		//WPW预激综合征
        if( strRhythm == "WPW" )
		{
			return BR_Sinus_WPW;
		}
		//心电轴左偏
		if( strRhythm == "Left Axis Deviation" )
		{
			return BR_Sinus_LeftAxis_Deviation;
		}
		//心电轴右偏
		if( strRhythm == "Right Axis Deviation" )
		{
			return BR_Sinus_RightAxis_Deviation;
		}
		//QT间期延长
		if( strRhythm == "Prolonged QT" )
		{
			return BR_Sinus_Prolonged_QT;
		}
		//洋地黄效应
		if( strRhythm == "Digitalis Effect" )
		{
			return BR_DigitalisEffect;
		}
		//一度房室传导阻滞
		if( strRhythm == "1 degree AVB" )
		{
			return BR_1degree_AVB;
		}
		//二度Ⅰ型房室传导阻滞
		if( strRhythm == "2 degree AVB Type-1" )
		{
			return BR_2degree_AVB_I;
		}
		//二度Ⅱ型房室传导阻滞
		if( strRhythm == "2 degree AVB Type-2" )
		{
			return BR_2degree_AVB_II;
		}
		//三度房室传导阻滞
		if( strRhythm == "3 degree AVB" )
		{
			return BR_3degree_AVB;
		}
		//心室停顿(Ventricular Standstill)
		if( strRhythm == "Ventr.standstill" )
		{
			return BR_Ventr_Standstill;
		}
		//室上性心动过速（SVT）
		if( strRhythm == "P.tach" )
		{
			return BR_ParoxysmalTach;
		}
		//心房扑动（A.flutt）
		if( strRhythm == "A.flutt." )
		{
			return BR_AFlutt;
		}
		//心房颤动（Afib）
		if( strRhythm == "A.fib." )
		{
			return BR_AFib;
		}
		//交界性心律(Junct.)
		if( strRhythm == "Junct." )
		{
			return BR_Junct;
		}
		//心室扑动
		if( strRhythm == "V.flutt." )
		{
			return BR_VFlutt;
		}
		//室性逸搏心律Idioventricular
		if( strRhythm == "Idiov." )
		{
			return BR_Idiov;
		}
		//室性心动过速（V.tach）
		if( strRhythm == "V.tach" )
		{
			return BR_VTach;
		}
		//尖端扭转型室性心动过速Torsade.de Pointes
		if( strRhythm == "Torsade.de Pointes" )
		{
			return BR_Torsade_DP;
		}
		//心室颤动（VF）
		if( strRhythm == "V.fibr" )
		{
			return BR_VFibr;
		}
		//临死前心律
		if( strRhythm == "Asystole" )
		{
			return BR_Asystole;
		}
		if( strRhythm == "Agonal rhythm" )
		{
			return BR_AgonalRhythm;
		}
		//房室顺序起搏(Pacem.AV-seq.)
		if( strRhythm == "Pacem.Attr" )
		{
			return BR_PacemakerAtr;
		}
		if( strRhythm == "Pacem.AV-seq." )
		{
			return BR_PacemakerAV_Seq;
		}
		//起搏器失去夺获
		if( strRhythm == "Pacem.LOC" )
		{
			return BR_PacemakerLoc;
		}
		if( strRhythm == "Die" )
		{
			return BR_Die;
		}
		return BR_None;
	}

	std::string IRhythmRule::GetstrBasicRhythm(BasicRhythm eRhythm)
	{
		switch(eRhythm)
		{
		case BR_Sinus:
			return "Sinus";
		case BR_Sinus_Ischemia:
			return "Sinus Ischemia";
		case BR_Sinus_InjureIschemia:
			return "Sinus InjureIschemia";
		case BR_Sinus_InferiorAMI_ST:
			return "Sinus InferiorAMI ST";
		case BR_Sinus_AnteriorAMI_ST:
			return "Sinus AnteriorAMI ST";
		case BR_Sinus_AnteriorAMI_Late:
			return "Sinus AnteriorAMI Late";
		case BR_Sinus_LBBB:
			return "LBBB";
		case BR_Sinus_RBBB:
			return "RBBB";
		case BR_Sinus_LeftHypertrophy:
			return "Left Ventricular Hypertrophy";
		case BR_Sinus_RightHypertrophy:
			return "Right Ventricular Hypertrophy";
		case BR_Sinus_Hypertrophy:
			return "Ventricular Hypertrophy";
		case BR_Sinus_Hyperkalemia:
			return "Hyperkalemia";
		case BR_Sinus_WPW:
			return "WPW";
		case BR_Sinus_LeftAxis_Deviation:
			return "Left Axis Deviation";
		case BR_Sinus_RightAxis_Deviation:
			return "Right Axis Deviation";
		case BR_Sinus_Prolonged_QT:
			return "Prolonged QT";
		case BR_DigitalisEffect:
			return "Digitalis Effect";
		case BR_1degree_AVB:
			return "1 degree AVB";
		case BR_2degree_AVB_I:
			return "2 degree AVB Type-1";
		case BR_2degree_AVB_II:
			return "2 degree AVB Type-2";
		case BR_3degree_AVB:
			return "3 degree AVB";
		case BR_Ventr_Standstill:
			return "Ventr.standstill";
		case BR_ParoxysmalTach:
			return "P.tach";
		case BR_AFlutt:
			return "A.flutt.";
		case BR_AFib:
			return "A.fib.";
		case BR_Junct:
			return "Junct.";
		case BR_VFlutt:
			return "V.flutt.";
		case BR_Idiov:
			return "Idiov.";
		case BR_VTach:
			return "V.tach";
		case BR_Torsade_DP:
			return "Torsade.de Pointes";
		case BR_VFibr:
			return "V.fibr";
		case BR_Asystole:
			return "Asystole";
		case BR_AgonalRhythm:
			return "Agonal rhythm";
		case BR_PacemakerAtr:
			return "Pacem.Attr";
		case BR_PacemakerAV_Seq:
			return "Pacem.AV-seq.";
		case BR_PacemakerLoc:
			return "Pacem.LOC";
		case BR_Die:
			return "Die";
		}
		return "";
	}

	Extrasys IRhythmRule::Get_eExtrasys(const std::string &strExtrasys)
	{
		if(strExtrasys == "Unifocal PVC")
		{
			return Unifocal_PVC;
		}
		if(strExtrasys == "PVC RonT")
		{
			return PVC_RonT;
		}
		if(strExtrasys == "Coupled PVC")
		{
			return Coupled_PVC;
		}
		if(strExtrasys == "Multifocal PVC")
		{
			return Multifocal_PVC;
		}
		if(strExtrasys == "PJC")
		{
			return PJC;
		}
		if(strExtrasys == "PAC")
		{
			return PAC;
		}
		return ES_None; //无
	}

	std::string IRhythmRule::GetstrExtrasys(Extrasys eExtrasys)
	{
		switch(eExtrasys)
		{
		case Unifocal_PVC:
			return "Unifocal PVC";
		case PVC_RonT:
			return "PVC RonT";
		case Coupled_PVC:
			return "Coupled PVC";
		case Multifocal_PVC:
			return "Multifocal PVC";
		case PJC:
			return "PJC";
		case PAC:
			return "PAC";
		}
		return "";
	}

	//-1:都没选；0：Muscular；1:50/60HZ
	Artifact IRhythmRule::Get_eArtifact(int iArtifact)
	{
		switch(iArtifact)
		{
		case -1:
			return AF_None;
		case 0:
			return AF_Muscular;
		case 1:
			return AF_Frequent;
		}
		return AF_None;
	}


	//根据心律返回合适的心率
	bool IRhythmRule::GetRightRateForRhythm(int nHeartRate, BasicRhythm eRhythm, int *pRightHeartRate)
	{
		return false;
	}

	//--------------------------------------------------------------------------------------------------------------------------
	//class IRespRule
	IRespRule::IRespRule()
	{

	}

	IRespRule::~IRespRule()
	{

	}

	eRespMode IRespRule::Get_eRespMode(const std::string &strRespMode)
	{
		eRespMode  eMode = RM_Normal;
		if( strRespMode == "Normal" )
		{
			eMode = RM_Normal;
		}
		else if( strRespMode == "Stokes" )
		{
			eMode = RM_Stokes;
		}
		else if( strRespMode == "Biots" )
		{
			eMode = RM_Biots;
		}
		else if( strRespMode == "Apneustic" )
		{
			eMode = RM_Apneustic;
		}
		else if( strRespMode == "Apnea" )
		{
			eMode = RM_Apnea;
		}
		else if( strRespMode == "Sign" )
		{
			eMode = RM_Sign;
		}
		else if( strRespMode == "IrregularGasp" )
		{
			eMode = RM_IrregularGasp;
		}
		return eMode;
	}

	std::string IRespRule::GetstrRespMode(eRespMode eMode)
	{
		std::string  strRespMode;
		switch( eMode )
		{
		case RM_Normal:
			{
				strRespMode = "Normal";
				break;
			}
		case RM_Stokes:
			{
				strRespMode = "Stokes";
				break;
			}
		case RM_Biots:
			{
				strRespMode = "Biots";
				break;
			}
		case RM_Apneustic:
			{
				strRespMode = "Apneustic";
				break;
			}
		case RM_Apnea:
			{
				strRespMode = "Apnea";
				break;
			}
		case RM_Sign:    //叹气样呼吸
			{
				strRespMode = "Sign";
				break;
			}
		case RM_IrregularGasp:  //不规则喘息
			{
				strRespMode  = "IrregularGasp";
				break;
			}
		}
		return strRespMode;
	}

	//---------------------------------------------------------------------------------------------------------------------------
	ISignsRespRule::ISignsRespRule()
	{

	}

	ISignsRespRule::~ISignsRespRule()
	{

	}

	float ISignsRespRule::GetSignsModeDefault( const std::string &strRespMode )
	{
		float  lRespRate = 0.0f;
		if( strRespMode == "RepirtoryRate" )
		{
			lRespRate = 12.0f;
		}
		else if( strRespMode == "Spo2" )
		{
			lRespRate  = 90.0f;
		}
		else if( strRespMode == "HearRate" )
		{
			lRespRate  = 80.0f;
		}
		else if( strRespMode == "BloodSystolic" )
		{
			lRespRate  = 120.0f;
		}
		else if( strRespMode == "BloodDiastolic" )
		{
			lRespRate  = 80.0f;
		}
		else if( strRespMode == "TemperatureBlood" )
		{
			lRespRate  = 37.0f;
		}
		else if( strRespMode == "TemperaturePeripheral" )
		{
			lRespRate  = 36.0f;
		}
		else if( strRespMode == "EtCO2" )
		{
			lRespRate  = 34.0f;
		}
		return lRespRate;
	}
}}
