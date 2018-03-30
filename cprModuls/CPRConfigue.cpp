#include ".\CPRConfigue.h"

#include <sstream>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/format.hpp>


using namespace boost::property_tree;
namespace jysoft{  namespace cpr 
{
	CCPRConfigue::CCPRConfigue(void)
	{
		eFiveCycleMode       = aCPRPractiseMode;
		lowerPressureDepth  = 50;
		overPressureDepth   = 60;
		lowerBreathVolume   = 500;
		overBreathVolume    = 1000;
		//最小、最大通气时间(单位：100ms)
		lowerRespTime = 5;
		overRespTime  = 60;
		//-----------------------------------------------------------
		bOverPressureValidate = true;
		bSpecialityMemberOp  = true;
		cycleNumber         = 5;
		sumPressureNumber   = 150;
		//QCPR默认标准
		scriptTime = make_optional(150);
		interruptTime = make_optional(20);
		rightPPce = make_optional(70);
		rightBPce = make_optional(70);
		ratePPce = make_optional(70);
	}

	CCPRConfigue::~CCPRConfigue(void)
	{
	}

	/*******************************************************************************/
	//功能：加载心肺复苏配置信息
	//参数：
	//      const std::string &configueFile： 个人配置文件信息
	//返回值:  
	void CCPRConfigue::loadCPRConfigue(const std::string &configueFile)
	{
		ptree   pt;
		read_xml( configueFile, pt);
		//按压范围
		lowerPressureDepth = pt.get<int>("QCPRConfig.CPRRule.parameters.pressureRule.depthRange.<xmlattr>.lower",50);
		overPressureDepth  = pt.get<int>("QCPRConfig.CPRRule.parameters.pressureRule.depthRange.<xmlattr>.over", 60);
		//吹气范围
		lowerBreathVolume  = pt.get<int>("QCPRConfig.CPRRule.parameters.breathRule.volumeRange.<xmlattr>.lower", 50);
		overBreathVolume  = pt.get<int>("QCPRConfig.CPRRule.parameters.breathRule.volumeRange.<xmlattr>.over",1000);
		//通气时间
		lowerRespTime = pt.get<int>("QCPRConfig.CPRRule.parameters.breathRule.ventiTimeRange.<xmlattr>.lower", 500);
		overRespTime = pt.get<int>("QCPRConfig.CPRRule.parameters.breathRule.ventiTimeRange.<xmlattr>.over", 1500);
		//CPR规则
		std::string ruleType = pt.get<std::string>("QCPRConfig.CPRRule.<xmlattr>.type");
		if( ruleType == "speciality" )
		{
			bSpecialityMemberOp = true;
			//循环次数
			cycleNumber = pt.get<int>("QCPRConfig.CPRRule.cycleOpNumber.<xmlattr>.value");
		}
		else
		{
			bSpecialityMemberOp = false;
			//按压次数
			sumPressureNumber = pt.get<int>("QCPRConfig.CPRRule.pressureNumber.<xmlattr>.value");
		}
		//-----------------------QCPR标准-----------------------------------------------------------------------------
		//脚本允许时间
		scriptTime = make_optional(pt.get<std::string>("QCPRConfig.scriptTime.<xmlattr>.enable", "true") == "true", pt.get<short>("QCPRConfig.scriptTime", 150));
		//中断时间
		interruptTime = make_optional(pt.get<std::string>("QCPRConfig.interruptTime.<xmlattr>.enable", "true") == "true", pt.get<short>("QCPRConfig.interruptTime", 20));
		//按压占比
		CCF = make_optional(pt.get<std::string>("QCPRConfig.CCF.<xmlattr>.enable", "true") == "true", pt.get<short>("QCPRConfig.CCF", 60));
		//按压正确占比
		rightPPce = make_optional(pt.get<std::string>("QCPRConfig.PRightPce.<xmlattr>.enable", "true") == "true", pt.get<short>("QCPRConfig.PRightPce", 70));
		//吹气正确占比
		rightBPce = make_optional(pt.get<std::string>("QCPRConfig.BRightPce.<xmlattr>.enable", "true") == "true", pt.get<short>("QCPRConfig.BRightPce", 70));
		//按压频率正确占比
		ratePPce = make_optional(pt.get<std::string>("QCPRConfig.PRatePce.<xmlattr>.enable", "true") == "true", pt.get<short>("QCPRConfig.PRatePce", 70));
	}

	//保存
	void CCPRConfigue::copyConfigue(CCPRConfigue  *pCPRConfigue)
	{
		lowerPressureDepth  = pCPRConfigue->getLowerPressureDepth();
		overPressureDepth   = pCPRConfigue->getOverPressureDepth();
		lowerBreathVolume   = pCPRConfigue->getLowerBreathVolume();
		overBreathVolume    = pCPRConfigue->getOverBreathVolume();
		lowerRespTime       = pCPRConfigue->getLowerRespTime();
		overRespTime        = pCPRConfigue->getOverRespTime();
		eFiveCycleMode       = pCPRConfigue->getFiveCycleMode();
		bSpecialityMemberOp  = pCPRConfigue->isSpecialityMemberOp();
		cycleNumber          = pCPRConfigue->isFiveCycleRule() ? 5 : 3;
		sumPressureNumber   = pCPRConfigue->getSumPressureNumber();
		bOverPressureValidate = pCPRConfigue->isOverPressureDepthValidate();
		//QCPR标准
		scriptTime  = pCPRConfigue->getScriptSumTime();
		interruptTime  = pCPRConfigue->getInterruptTime();
		CCF  = pCPRConfigue->getCCFPecent();
		rightPPce  = pCPRConfigue->getPRightPecent();
		rightBPce  = pCPRConfigue->getBRightPecent();
		ratePPce  = pCPRConfigue->getPRatePecent();
	}

	/*******************************************************************************/
	//功能：SaveCPRConfigueToFile
	//功能： 保存使用者的CPR配置信息（用于BLS脚本操作）
	//参数：
	//返回值: 
	void CCPRConfigue::saveCPRConfigueToFile(const std::string &strUserConfigueFile, _CPRManageState eCPRMode)
	{
		boost::format  fmt("<?xml version=\"1.0\" encoding=\"utf-8\" ?>\n<QCPRConfig opMode=\"%s\"></QCPRConfig>");
		fmt % (eCPRMode == aCPRPractiseMode ? "practise" : "popular");
		//解析文本
		std::istringstream   sstream(fmt.str());
		ptree     pt;
		read_xml( sstream, pt );
		//按压范围
		pt.put("QCPRConfig.CPRRule.parameters.pressureRule.depthRange.<xmlattr>.lower", lowerPressureDepth);
		pt.put("QCPRConfig.CPRRule.parameters.pressureRule.depthRange.<xmlattr>.over", overPressureDepth);
		//吹气范围
		pt.put("QCPRConfig.CPRRule.parameters.breathRule.volumeRange.<xmlattr>.lower", lowerBreathVolume);
		pt.put("QCPRConfig.CPRRule.parameters.breathRule.volumeRange.<xmlattr>.over", overBreathVolume);
		//通气时间
		pt.put("QCPRConfig.CPRRule.parameters.breathRule.ventiTimeRange.<xmlattr>.lower", lowerRespTime);
		pt.put("QCPRConfig.CPRRule.parameters.breathRule.ventiTimeRange.<xmlattr>.over", overRespTime);
		//CPR规则
		if( bSpecialityMemberOp )
		{
			pt.put("QCPRConfig.CPRRule.<xmlattr>.type", "speciality");
			//循环次数
			pt.put("QCPRConfig.CPRRule.cycleOpNumber.<xmlattr>.value", cycleNumber);
		}
		else
		{
			pt.put("QCPRConfig.CPRRule.<xmlattr>.type", "amateur");
			//按压次数
			pt.put("QCPRConfig.CPRRule.pressureNumber.<xmlattr>.value", sumPressureNumber);
		}
		//-----------------------QCPR标准-----------------------------------------------------------------------------
		//脚本允许时间
		pt.put("QCPRConfig.scriptTime.<xmlattr>.enable", !scriptTime ? "true" : "false");
		pt.put("QCPRConfig.scriptTime", scriptTime.get_value_or(150));
		//中断时间
		pt.put("QCPRConfig.interruptTime.<xmlattr>.enable", !interruptTime ? "true" : "false");
		pt.put("QCPRConfig.interruptTime", interruptTime.get_value_or(20));
		//按压占比
		pt.put("QCPRConfig.CCF.<xmlattr>.enable", !CCF ? "true" : "false");
		pt.put("QCPRConfig.CCF", CCF.get_value_or(60));
		//按压正确占比
		pt.put("QCPRConfig.PRightPce.<xmlattr>.enable", !rightPPce ? "true" : "false");
		pt.put("QCPRConfig.PRightPce", rightPPce.get_value_or(70));
		//吹气正确占比
		pt.put("QCPRConfig.BRightPce.<xmlattr>.enable", !rightBPce ? "true" : "false");
		pt.put("QCPRConfig.BRightPce", rightBPce.get_value_or(70));
		//按压频率正确占比
		pt.put("QCPRConfig.PRatePce.<xmlattr>.enable", !ratePPce ? "true" : "false");
		pt.put("QCPRConfig.PRatePce", ratePPce.get_value_or(70));

		write_xml(strUserConfigueFile, pt);
	}
	
	//按压最大值
	int CCPRConfigue::getOverPressureDepth(bool bPresets/*=false*/)
	{
		int   nOverDepth = overPressureDepth;
		if( bPresets == false && bOverPressureValidate == false )
		{
			//忽略最大按压深度
			nOverDepth = 80;
		}
		return nOverDepth;
	}

	//设置默认的参数值
	void CCPRConfigue::setDefaultParams(_CPRManageState eMode)
	{
		eFiveCycleMode       = eMode;
		lowerPressureDepth  = 50;
		overPressureDepth   = 60;
		lowerBreathVolume   = 500;
		overBreathVolume    = 1000;
		//最小、最大通气时间(单位：ms)
		lowerRespTime = 500;
		overRespTime  = 1500;
		//-----------------------------------------------------------
		bOverPressureValidate = true;
		bSpecialityMemberOp  = true;
		cycleNumber          = 5;
		//QCPR默认标准
		scriptTime = make_optional(150);
		interruptTime = make_optional(20);
		rightPPce = make_optional(70);
		rightBPce = make_optional(70);
		ratePPce = make_optional(70);
	}


}}
