#include ".\saction_abp.h"

#include <boost/format.hpp>

CSAction_ABP::CSAction_ABP(void)
{
}

CSAction_ABP::~CSAction_ABP(void)
{
}

bool CSAction_ABP::isAction_BP(const std::string &caption)
{
	if( caption == getAction_BP_Caption() )
	{
		return true;
	}
	return false;
}

// �����Ա��浽�ַ�����
std::string CSAction_ABP::saveParams(long lShrinkValue, long lStretchValue)
{
	boost::format   xmlBP;
	xmlBP.parse("<Action_BP><Shrink value=\"%d\" /><Stretch value=\"%d\" /></Action_BP>");
	xmlBP % lShrinkValue % lStretchValue;
	return xmlBP.str();
}

void CSAction_ABP::saveParamsToXML(pugi::xml_node* pXMLABPChild, long lShrinkValue, long lStretchValue)
{
	//����ѹ
	pugi::xml_node shrinkNode = pXMLABPChild->append_child("Shrink");
	shrinkNode.append_attribute("value").set_value( lShrinkValue );
	//����ѹ
	pugi::xml_node stretchNode = pXMLABPChild->append_child("Stretch");
	stretchNode.append_attribute("value").set_value( lStretchValue );
}

bool CSAction_ABP::explainParamsFromXML(pugi::xml_node* pXMLABPChild, long *lShrinkValue, /*out*/long *lStretchValue)
{
	//����ѹ
	*lShrinkValue = pXMLABPChild->child("Shrink").attribute("value").as_int(120);
	//����ѹ
	*lStretchValue = pXMLABPChild->child("Stretch").attribute("value").as_int(80);
	return true;
}
