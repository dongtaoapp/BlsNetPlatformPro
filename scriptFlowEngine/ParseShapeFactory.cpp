#include ".\parseshapefactory.h"

#include "..\SimulatorSymptom\XAction_ECG.h"
#include "..\SimulatorSymptom\XAction_ABP.h"
#include "..\simulatorSymptom\XAction_CellColumn.h"
#include "..\simulatorSymptom\XAction_ContactPatient.h"
#include "..\simulatorSymptom\XAction_Electrode.h"
#include "..\simulatorSymptom\XAction_Pace.h"
#include "..\SimulatorSymptom\XAction_Resp.h"
#include "..\SimulatorSymptom\XAction_Pupil.h"
#include "..\SimulatorSymptom\XAction_Defibri.h"
#include "..\SimulatorSymptom\XAction_Osat.h"
#include "..\SimulatorSymptom\XAction_etCO2.h"
#include "..\SimulatorSymptom\XAction_Temperature.h"
#include "..\simulatorSymptom\XAction_FrameTime.h"


#include "..\elementParse\SAction_ECG.h"
#include "..\elementParse\SAction_ABP.h"
#include "..\elementParse\SAction_CellColumn.h"
#include "..\elementParse\SAction_ContactPatient.h"
#include "..\elementParse\SAction_Electrode.h"
#include "..\elementParse\SAction_Resp.h"
#include "..\elementParse\SAction_Pupil.h"
#include "..\elementParse\SAction_Defibrillate.h"
#include "..\elementParse\SAction_Pace.h"
#include "..\elementParse\SAction_Osat.h"
#include "..\elementParse\SAction_etCO2.h"
#include "..\elementParse\SAction_FrameTime.h"
#include "..\elementParse\SAction_Temperature.h"

#include ".\XEvent_AED.h"
#include ".\XEvent_CPR.h"
#include ".\XEvent_Defibri.h"
#include ".\XEvent_Pulse.h"
#include ".\XEvent_Thump.h"
#include ".\XEvent_Time.h"

#include "..\elementParse\SEvent_AED.h"
#include "..\ElementParse\SEvent_CPR.h"
#include "..\ElementParse\SEvent_Defibr.h"
#include "..\elementParse\SEvent_Thump.h"
#include "..\elementParse\SEvent_Pulse.h"
#include "..\ElementParse\SEvent_Pace.h"
#include "..\ElementParse\SEvent_Time.h"
#include "..\ElementParse\SEvent_Intubate.h"


using namespace jysoft::simulator;
namespace jysoft { namespace flowEngine 
{
	CParseShapeFactory::CParseShapeFactory(void)
	{
	}

	CParseShapeFactory::~CParseShapeFactory(void)
	{
	}

	//生成体征对象
	CXActionVirtual * CParseShapeFactory::CreateActionObject(const std::string & strSignName) const
	{
		CXActionVirtual *pActionVir = NULL;
		if( CSAction_ECG::isECG_Action( strSignName ) )
		{
			pActionVir = new CXAction_ECG();
		}
		else if( CSAction_ABP::isAction_BP( strSignName ) )
		{
			pActionVir = new CXAction_ABP();
		}
		else if( CSAction_CellColumn::isAction_CellColumn( strSignName ) )
		{
			pActionVir = new CXAction_CellColumn();
		}
		else if( CSAction_ContactPatient::isAction_ContactPatient( strSignName ) )
		{
			pActionVir = new CXAction_ContactPatient();
		}
		else if( CSAction_Electrode::isAction_Electrode( strSignName ) )
		{
			pActionVir = new CXAction_Electrode();
		}
		else if( CSAction_Resp::isAction_Resp( strSignName ) )
		{
			pActionVir = new CXAction_Resp();
		}
		else if( CSAction_Pupil::isAction_Pupil( strSignName ) )
		{
			pActionVir = new CXAction_Pupil();
		}
		else if( CSAction_Defibrillate::isAction_Defibri( strSignName ) )
		{
			pActionVir = new CXAction_Defibri();
		}
		else if( CSAction_Pace::isAction_Pace( strSignName ) )
		{
			pActionVir = new CXAction_Pace();
		}
		else if( CSAction_Temperature::isAction_Temperature( strSignName ) )
		{
			pActionVir = new CXAction_Temperature();
		}
		else if( CSAction_FrameTime::isAction_FrameTime( strSignName ) )
		{
			pActionVir = new CXAction_FrameTime();
		}
		return pActionVir;
	}

	//生成其它体征对象
	CXActionVirtual * CParseShapeFactory::CreateActionOtherObj(const std::string & strSignName) const
	{
		CXActionVirtual *pVirAction = NULL;
		if( CSAction_Osat::isAction_Osat( strSignName ) )
		{
			pVirAction = new CXAction_Osat();
		}
		else if( CSAction_etCO2::isAction_etCO2( strSignName ) )
		{
			pVirAction = new CXAction_etCO2();
		}
		else if( CSAction_Temperature::isAction_Temperature( strSignName ) )
		{
			pVirAction = new CXAction_Temperature();
		}
		return pVirAction;
	}

	void CParseShapeFactory::ParseActionObject(pugi::xml_node *pXMLShapeNode, std::list<CXActionVirtual *> *plstNewActions) const
	{
		plstNewActions->clear();
		//---------------------------------------------------------------------------
		std::string nodeName( pXMLShapeNode->name() );
		
		CXActionVirtual *pActionVir = NULL;
		if( nodeName != "Action_Other" )
		{
			pActionVir = CreateActionObject( nodeName );
			//解释体征数值
			if( pActionVir && pActionVir->Parse_ActionFromXml( pXMLShapeNode ) )
			{
				plstNewActions->push_back( pActionVir );
			}
		}
		else
		{
			DoParseActionOthersObj(pXMLShapeNode, plstNewActions);
		}
	} 

	void CParseShapeFactory::DoParseActionOthersObj(pugi::xml_node *pXMLActonOthersNode, std::list<CXActionVirtual *> *plstNewActions) const
	{
		for (pugi::xml_node_iterator it = pXMLActonOthersNode->begin(); it != pXMLActonOthersNode->end(); ++it)
		{
			//节点名称
			std::string   childName(it->name());
			//生成Action对象
			CXActionVirtual *pVirAction  = CreateActionOtherObj( childName );
			//------------------------------------------------------------------------------------
			if( pVirAction && pVirAction->Parse_ActionFromXml( &(*it) ) )
			{
				plstNewActions->push_back( pVirAction );
			}
			else
			{
				delete pVirAction;
			}
		}
	}

	//解析事件框中的事件
	CXEventVirtual * CParseShapeFactory::ParseEventObject(pugi::xml_node *pXMLShapeNode) const
	{
		CXEventVirtual  *pVirEvent  = NULL;

		std::string   nodeName(pXMLShapeNode->name());

		if( CSEvent_AED::isEvent_AED( nodeName ) )
		{
			pVirEvent = new CXEvent_AED();
		}
		if( CSEvent_CPR::isEvent_CPR( nodeName ) )
		{
			pVirEvent  = new CXEvent_CPR();
		}
		else if( CSEvent_Defibr::isEvent_Defibr( nodeName ) )
		{
			pVirEvent  = new CXEvent_Defibri();
		}
		else if( CSEvent_Pulse::isEvent_Pulse( nodeName ) )
		{
			pVirEvent = new CXEvent_Pulse();
		}
		else if( CSEvent_Thump::isAction_Thump( nodeName ) )
		{
			pVirEvent = new CXEvent_Thump();
		}
		else if( CSEvent_Time::isEvent_Time( nodeName ) )
		{
			pVirEvent  = new CXEvent_Time();
		}
		return pVirEvent;
	}
}}
