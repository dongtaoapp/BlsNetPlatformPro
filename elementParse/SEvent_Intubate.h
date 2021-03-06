#pragma once
#include <string>
#include <pugixml.hpp>
#include ".\elementParse_global.h"


class AFX_EXT_CLASS CSEvent_Intubate
{
public:
	CSEvent_Intubate(void);
	virtual ~CSEvent_Intubate(void);
public:
	static bool isEvent_Intubate(const std::string &caption);
	static std::string getEvent_Intubate_Caption() { return "Event_Intubate"; };
	// 将属性保存到字符窜中
	static std::string saveParams(short sPosition, short sAct);
	/*******************************************************************************/
	// 功能： 
	// 参数： 
	//        /*out*/short *sPosition: 插管位置：气管(0x01)；右肺组织(0x02)
	//        /*out*/short *sAct:      插管动作：插入(0x00)；拔出(0x11)；
	// 返回值:  
	static void saveParamsToXML(pugi::xml_node* pXMLIntubateChild, short sPosition, short sAct);
	static bool explainParamsFromXML(pugi::xml_node* pXMLIntubateChild, /*out*/short *sPosition, /*out*/short *sAct); 
public:
	static bool explainSimulateTriggerIntubateEvent(const std::string &intubateTriggerXML, /*out*/short *sPosition, /*out*/short *sAct);
};

