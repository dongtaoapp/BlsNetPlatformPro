#pragma once
#include <string>
#include <pugixml.hpp>
#include ".\elementParse_global.h"

//电极片的位置
class AFX_EXT_CLASS CSAction_Electrode
{
public:
	CSAction_Electrode(void);
	virtual ~CSAction_Electrode(void);
public:
	static bool isAction_Electrode(const std::string &caption);
	static std::string getAction_Electrode_Caption() { return "Action_Electrode"; };
	// 将属性保存到字符窜中
	static std::string saveParams(bool bPosRight);
	static void saveParamsToXML(pugi::xml_node* pXMElectrodeChild, bool bPosRight);
	static bool explainParamsFromXML(pugi::xml_node* pXMElectrodeChild, /*out*/bool *bPosRight); 
};

