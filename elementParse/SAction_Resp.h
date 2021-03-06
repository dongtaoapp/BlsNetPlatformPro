#pragma once
#include <string>
#include <pugixml.hpp>
#include ".\elementParse_global.h"


/*-----------------------------------------------------------------------------------------------------------------
类说明：     自主呼吸解析类 
创建人：	 hjg
创建时间：   
//-----------------------------------------------------------------------------------------------------------------*/
class AFX_EXT_CLASS CSAction_Resp
{
public:
	CSAction_Resp(void);
	virtual ~CSAction_Resp(void);
public:
	static bool isAction_Resp(const std::string &caption);
	static std::string getAction_Resp_Caption() { return "Action_Resp"; };
	// 将属性保存到字符窜中
	static std::string saveParams( const std::string &breathType, long lBreathValue);
	static void saveParamsToXML(pugi::xml_node* pXMLRespChild, const std::string &breathType, long lBreathnValue);
	static bool explainParamsFromXML(pugi::xml_node* pXMLRespChild, /*out*/std::string *pstrBreathType, /*out*/long *lBreathnValue); 
};

