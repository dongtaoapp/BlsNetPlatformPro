#pragma once
#include <string>
#include <pugixml.hpp>
#include ".\elementParse_global.h"

class AFX_EXT_CLASS CSAction_ECG
{
public:
	CSAction_ECG(void);
	~CSAction_ECG(void);
public:
	static bool isECG_Action(const std::string &caption);
	inline static std::string getAction_ECG_Caption() { return "Action_ECG"; };
	// 将属性保存到字符窜中
	static std::string saveParams(const std::string &strRhythm, const std::string &strHR, const std::string &strHRPercent, const std::string &strExtrasyst, const std::string &strExtrasystRate,int nArtifacts,short bEMD,short sConduct, short sExtendParam);
	static void saveParamsToXML(pugi::xml_node* pParentMess,  const std::string &strRhythm, const std::string &strHR, const std::string &strHRPercent, const std::string &strExtrasyst, const std::string &strExtrasystRate,int nArtifacts,short bEMD,short sConduct, short sExtendParam);
	static bool explainParamsFromXML(pugi::xml_node* pParentMess, std::string &strRhythm, std::string &strHR, std::string &strHRPercent, std::string &strExtrasyst, std::string &strExtrasystRate, int &nArtifacts,short &bEMD,short &sConduct, short &sExtendParam);
};
