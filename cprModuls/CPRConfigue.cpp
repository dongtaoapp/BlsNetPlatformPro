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
		//��С�����ͨ��ʱ��(��λ��100ms)
		lowerRespTime = 5;
		overRespTime  = 60;
		//-----------------------------------------------------------
		bOverPressureValidate = true;
		bSpecialityMemberOp  = true;
		cycleNumber         = 5;
		sumPressureNumber   = 150;
		//QCPRĬ�ϱ�׼
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
	//���ܣ������ķθ���������Ϣ
	//������
	//      const std::string &configueFile�� ���������ļ���Ϣ
	//����ֵ:  
	void CCPRConfigue::loadCPRConfigue(const std::string &configueFile)
	{
		ptree   pt;
		read_xml( configueFile, pt);
		//��ѹ��Χ
		lowerPressureDepth = pt.get<int>("QCPRConfig.CPRRule.parameters.pressureRule.depthRange.<xmlattr>.lower",50);
		overPressureDepth  = pt.get<int>("QCPRConfig.CPRRule.parameters.pressureRule.depthRange.<xmlattr>.over", 60);
		//������Χ
		lowerBreathVolume  = pt.get<int>("QCPRConfig.CPRRule.parameters.breathRule.volumeRange.<xmlattr>.lower", 50);
		overBreathVolume  = pt.get<int>("QCPRConfig.CPRRule.parameters.breathRule.volumeRange.<xmlattr>.over",1000);
		//ͨ��ʱ��
		lowerRespTime = pt.get<int>("QCPRConfig.CPRRule.parameters.breathRule.ventiTimeRange.<xmlattr>.lower", 500);
		overRespTime = pt.get<int>("QCPRConfig.CPRRule.parameters.breathRule.ventiTimeRange.<xmlattr>.over", 1500);
		//CPR����
		std::string ruleType = pt.get<std::string>("QCPRConfig.CPRRule.<xmlattr>.type");
		if( ruleType == "speciality" )
		{
			bSpecialityMemberOp = true;
			//ѭ������
			cycleNumber = pt.get<int>("QCPRConfig.CPRRule.cycleOpNumber.<xmlattr>.value");
		}
		else
		{
			bSpecialityMemberOp = false;
			//��ѹ����
			sumPressureNumber = pt.get<int>("QCPRConfig.CPRRule.pressureNumber.<xmlattr>.value");
		}
		//-----------------------QCPR��׼-----------------------------------------------------------------------------
		//�ű�����ʱ��
		scriptTime = make_optional(pt.get<std::string>("QCPRConfig.scriptTime.<xmlattr>.enable", "true") == "true", pt.get<short>("QCPRConfig.scriptTime", 150));
		//�ж�ʱ��
		interruptTime = make_optional(pt.get<std::string>("QCPRConfig.interruptTime.<xmlattr>.enable", "true") == "true", pt.get<short>("QCPRConfig.interruptTime", 20));
		//��ѹռ��
		CCF = make_optional(pt.get<std::string>("QCPRConfig.CCF.<xmlattr>.enable", "true") == "true", pt.get<short>("QCPRConfig.CCF", 60));
		//��ѹ��ȷռ��
		rightPPce = make_optional(pt.get<std::string>("QCPRConfig.PRightPce.<xmlattr>.enable", "true") == "true", pt.get<short>("QCPRConfig.PRightPce", 70));
		//������ȷռ��
		rightBPce = make_optional(pt.get<std::string>("QCPRConfig.BRightPce.<xmlattr>.enable", "true") == "true", pt.get<short>("QCPRConfig.BRightPce", 70));
		//��ѹƵ����ȷռ��
		ratePPce = make_optional(pt.get<std::string>("QCPRConfig.PRatePce.<xmlattr>.enable", "true") == "true", pt.get<short>("QCPRConfig.PRatePce", 70));
	}

	//����
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
		//QCPR��׼
		scriptTime  = pCPRConfigue->getScriptSumTime();
		interruptTime  = pCPRConfigue->getInterruptTime();
		CCF  = pCPRConfigue->getCCFPecent();
		rightPPce  = pCPRConfigue->getPRightPecent();
		rightBPce  = pCPRConfigue->getBRightPecent();
		ratePPce  = pCPRConfigue->getPRatePecent();
	}

	/*******************************************************************************/
	//���ܣ�SaveCPRConfigueToFile
	//���ܣ� ����ʹ���ߵ�CPR������Ϣ������BLS�ű�������
	//������
	//����ֵ: 
	void CCPRConfigue::saveCPRConfigueToFile(const std::string &strUserConfigueFile, _CPRManageState eCPRMode)
	{
		boost::format  fmt("<?xml version=\"1.0\" encoding=\"utf-8\" ?>\n<QCPRConfig opMode=\"%s\"></QCPRConfig>");
		fmt % (eCPRMode == aCPRPractiseMode ? "practise" : "popular");
		//�����ı�
		std::istringstream   sstream(fmt.str());
		ptree     pt;
		read_xml( sstream, pt );
		//��ѹ��Χ
		pt.put("QCPRConfig.CPRRule.parameters.pressureRule.depthRange.<xmlattr>.lower", lowerPressureDepth);
		pt.put("QCPRConfig.CPRRule.parameters.pressureRule.depthRange.<xmlattr>.over", overPressureDepth);
		//������Χ
		pt.put("QCPRConfig.CPRRule.parameters.breathRule.volumeRange.<xmlattr>.lower", lowerBreathVolume);
		pt.put("QCPRConfig.CPRRule.parameters.breathRule.volumeRange.<xmlattr>.over", overBreathVolume);
		//ͨ��ʱ��
		pt.put("QCPRConfig.CPRRule.parameters.breathRule.ventiTimeRange.<xmlattr>.lower", lowerRespTime);
		pt.put("QCPRConfig.CPRRule.parameters.breathRule.ventiTimeRange.<xmlattr>.over", overRespTime);
		//CPR����
		if( bSpecialityMemberOp )
		{
			pt.put("QCPRConfig.CPRRule.<xmlattr>.type", "speciality");
			//ѭ������
			pt.put("QCPRConfig.CPRRule.cycleOpNumber.<xmlattr>.value", cycleNumber);
		}
		else
		{
			pt.put("QCPRConfig.CPRRule.<xmlattr>.type", "amateur");
			//��ѹ����
			pt.put("QCPRConfig.CPRRule.pressureNumber.<xmlattr>.value", sumPressureNumber);
		}
		//-----------------------QCPR��׼-----------------------------------------------------------------------------
		//�ű�����ʱ��
		pt.put("QCPRConfig.scriptTime.<xmlattr>.enable", !scriptTime ? "true" : "false");
		pt.put("QCPRConfig.scriptTime", scriptTime.get_value_or(150));
		//�ж�ʱ��
		pt.put("QCPRConfig.interruptTime.<xmlattr>.enable", !interruptTime ? "true" : "false");
		pt.put("QCPRConfig.interruptTime", interruptTime.get_value_or(20));
		//��ѹռ��
		pt.put("QCPRConfig.CCF.<xmlattr>.enable", !CCF ? "true" : "false");
		pt.put("QCPRConfig.CCF", CCF.get_value_or(60));
		//��ѹ��ȷռ��
		pt.put("QCPRConfig.PRightPce.<xmlattr>.enable", !rightPPce ? "true" : "false");
		pt.put("QCPRConfig.PRightPce", rightPPce.get_value_or(70));
		//������ȷռ��
		pt.put("QCPRConfig.BRightPce.<xmlattr>.enable", !rightBPce ? "true" : "false");
		pt.put("QCPRConfig.BRightPce", rightBPce.get_value_or(70));
		//��ѹƵ����ȷռ��
		pt.put("QCPRConfig.PRatePce.<xmlattr>.enable", !ratePPce ? "true" : "false");
		pt.put("QCPRConfig.PRatePce", ratePPce.get_value_or(70));

		write_xml(strUserConfigueFile, pt);
	}
	
	//��ѹ���ֵ
	int CCPRConfigue::getOverPressureDepth(bool bPresets/*=false*/)
	{
		int   nOverDepth = overPressureDepth;
		if( bPresets == false && bOverPressureValidate == false )
		{
			//�������ѹ���
			nOverDepth = 80;
		}
		return nOverDepth;
	}

	//����Ĭ�ϵĲ���ֵ
	void CCPRConfigue::setDefaultParams(_CPRManageState eMode)
	{
		eFiveCycleMode       = eMode;
		lowerPressureDepth  = 50;
		overPressureDepth   = 60;
		lowerBreathVolume   = 500;
		overBreathVolume    = 1000;
		//��С�����ͨ��ʱ��(��λ��ms)
		lowerRespTime = 500;
		overRespTime  = 1500;
		//-----------------------------------------------------------
		bOverPressureValidate = true;
		bSpecialityMemberOp  = true;
		cycleNumber          = 5;
		//QCPRĬ�ϱ�׼
		scriptTime = make_optional(150);
		interruptTime = make_optional(20);
		rightPPce = make_optional(70);
		rightBPce = make_optional(70);
		ratePPce = make_optional(70);
	}


}}
