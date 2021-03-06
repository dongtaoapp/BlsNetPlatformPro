#include ".\saction_ecg.h"

#include <boost/format.hpp>

CSAction_ECG::CSAction_ECG(void)
{
}

CSAction_ECG::~CSAction_ECG(void)
{
}

bool CSAction_ECG::isECG_Action(const std::string &caption)
{
	if( caption == getAction_ECG_Caption() )
		return true;
	return false;
}

std::string CSAction_ECG::saveParams(const std::string &strRhythm, const std::string &strHR, const std::string &strHRPercent, const std::string &strExtrasyst, const std::string &strExtrasystRate,int nArtifacts,short bEMD,short sConduct, short sExtendParam)
{
	std::string  xmlEcg, tmp;
	if( !strHR.empty() )
	{
		boost::format  fmt;
		if( strHRPercent.empty() )
		{
			fmt.parse("<Action_ECG><Rhythm>%s</Rhythm><HR>%s</HR>");
			fmt % strRhythm % strHR;
		}
		else
		{
			fmt.parse("<Action_ECG><Rhythm>%s</Rhythm><HR-per>%s</HR-per>");
			fmt % strRhythm % strHRPercent;
		}
		xmlEcg = fmt.str();
	}
	tmp = xmlEcg;
	if(!strExtrasyst.empty())
	{
		boost::format  fmt("%s<Extrasyst>%s</Extrasyst>");
		fmt % tmp % strExtrasyst;
		tmp = fmt.str();
	}
	switch( nArtifacts )
	{
	case 0:
		{
			boost::format  fmt("%s<Artifacts>%s</Artifacts>");
			fmt % tmp % "none";
			xmlEcg = fmt.str();
			break;
		}
	case 1:
		{
			boost::format  fmt("%s<Artifacts>%s</Artifacts>");
			fmt % tmp % "Muscular";
			xmlEcg = fmt.str();
			break;
		}
	case 2:
		{
			boost::format  fmt("%s<Artifacts>%s</Artifacts>");
			fmt % tmp % "50/60HZ";
			xmlEcg = fmt.str();
			break;
		}
	}
	tmp = xmlEcg;
	if(!strExtrasystRate.empty())
	{
		boost::format  fmt("%s<ExtrasystRate>%s</ExtrasystRate>");
		fmt % tmp % strExtrasystRate;
		tmp = fmt.str();
	}
	std::string   strEMD;
	switch ( bEMD )
	{
	case 0:
		strEMD = "No Change";
		break;
	case 1:
		strEMD = "No PEA";
		break;
	case 2:
		strEMD = "PEA";
		break;
	}
	boost::format fmt("%s<EMD>%s</EMD><Conduct>%d</Conduct>");
	fmt % tmp % strEMD % sConduct;
	tmp = fmt.str();
	if( sExtendParam != 0 )
	{
		boost::format  fmt("%s<ExtendValue>%d</ExtendValue>");
		fmt % tmp % sExtendParam;
		tmp = fmt.str();
	}
	boost::format fmt2("%s</Action_ECG>");
	fmt2 % tmp;
	return fmt2.str();
}

bool CSAction_ECG::explainParamsFromXML(pugi::xml_node* pParentMess, std::string &strRhythm, std::string &strHR, std::string &strHRPercent, std::string &strExtrasyst, std::string &strExtrasystRate, int &nArtifacts,short &bEMD,short &sConduct, short &sExtendParam)
{
	return false;
}

void CSAction_ECG::saveParamsToXML(pugi::xml_node* pParentMess,  const std::string &strRhythm, const std::string &strHR, const std::string &strHRPercent, const std::string &strExtrasyst, const std::string &strExtrasystRate,int nArtifacts,short bEMD,short sConduct, short sExtendParam)
{
	
}
