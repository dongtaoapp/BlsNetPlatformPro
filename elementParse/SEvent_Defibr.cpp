#include ".\SEvent_Defibr.h"

#include <sstream>
#include <boost/format.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>


using namespace boost::property_tree;
CSEvent_Defibr::CSEvent_Defibr(void)
{
}


CSEvent_Defibr::~CSEvent_Defibr(void)
{
}

bool CSEvent_Defibr::isEvent_Defibr(const std::string &caption)
{
	if( caption == getEvent_Defibr_Caption() )
		return true;
	return false;
}

// 将属性保存到字符窜中
std::string CSEvent_Defibr::saveParams(short sDefibrCount, short nDefibrEnergy, bool bSyncDefibr/*=false*/)
{
	boost::format  fmt;
	if( sDefibrCount <= 1 && nDefibrEnergy == 0 )
	{
		fmt.parse("<Event_Defibri isSync=\"%d\" />");
		fmt % (bSyncDefibr ? 1 : 0);
	}
	else if( sDefibrCount <= 1 )
	{
		fmt.parse("<Event_Defibri defibrEnergy=\"%d\" isSync=\"%d\" />");
		fmt % nDefibrEnergy % (bSyncDefibr ? 1 : 0);
	}
	else if( nDefibrEnergy == 0 )
	{
		fmt.parse("<Event_Defibri defibrCount=\"%d\" isSync=\"%d\" />");
		fmt % sDefibrCount % (bSyncDefibr ? 1 : 0);
	}
	else
	{
		fmt.parse("<Event_Defibri defibrEnergy=\"%d\" defibrCount=\"%d\" isSync=\"%d\" />");
		fmt % nDefibrEnergy % sDefibrCount % (bSyncDefibr ? 1 : 0);
	}
	return fmt.str();
}

void CSEvent_Defibr::saveParamsToXML(pugi::xml_node* pXMLDefibrChild, short sDefibrCount, short nDefibrEnergy, bool bSyncDefibr/*=false*/)
{
	if( sDefibrCount <= 1 && nDefibrEnergy == 0 )
	{
		pXMLDefibrChild->append_attribute("isSync").set_value(bSyncDefibr ? 1 : 0);
	}
	else if( sDefibrCount <= 1 )
	{
		//除颤能量
		pXMLDefibrChild->append_attribute("defibrEnergy").set_value(nDefibrEnergy);
		pXMLDefibrChild->append_attribute("isSync").set_value(bSyncDefibr ? 1 : 0);
	}
	else if( nDefibrEnergy == 0 )
	{
		//除颤次数
		pXMLDefibrChild->append_attribute("defibrCount").set_value(sDefibrCount);
		//同步/异步
		pXMLDefibrChild->append_attribute("isSync").set_value(bSyncDefibr ? 1 : 0);
	}
	else
	{
		//除颤能量
		pXMLDefibrChild->append_attribute("defibrEnergy").set_value(nDefibrEnergy);
		//除颤次数
		pXMLDefibrChild->append_attribute("defibrCount").set_value(sDefibrCount);
		//同步/异步
		pXMLDefibrChild->append_attribute("isSync").set_value(bSyncDefibr ? 1 : 0);
	}
}

bool CSEvent_Defibr::explainParamsFromXML(pugi::xml_node* pXMLDefibrChild, /*out*/short *sDefibrCount, /*out*/short *nDefibrEnergy, /*out*/bool *bSyncDefibr/*=NULL*/)
{
	//除颤能量
	*nDefibrEnergy = pXMLDefibrChild->attribute("defibrEnergy").as_int(0);
	//除颤次数
	*sDefibrCount = pXMLDefibrChild->attribute("defibrCount").as_int(1);
	//同步/异步
	int nSyncDefibr = pXMLDefibrChild->attribute("isSync").as_int(1);
	*bSyncDefibr = nSyncDefibr > 0 ? true : false;
	return true;
}

bool CSEvent_Defibr::explainSimulateTriggerDefibrEvent(const std::string &defibrTriggerXML, /*out*/short *sDefibrCount, /*out*/short *nDefibrEnergy, /*out*/bool *bSyncDefibr/*=NULL*/)
{
	std::istringstream  istr(defibrTriggerXML);
	try
	{
		ptree  pt;
		read_xml(istr, pt);
		//除颤次数
		*sDefibrCount = pt.get<short>("Event_Defibri.<xmlattr>.defibrCount", 1);
		//除颤能量
		*nDefibrEnergy =  pt.get<short>("Event_Defibri.<xmlattr>.defibrEnergy",0);
		//同步/异步
		if( bSyncDefibr != NULL )
		{
			*bSyncDefibr =  pt.get<short>("Event_Defibri.<xmlattr>.isSync",1) > 0 ? true : false;
		}
	}
	catch (...)
	{
		return false;
	}
	return true;
}
