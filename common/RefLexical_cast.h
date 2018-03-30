#pragma once
#include ".\common_global.h"
#include <vector>
#include <map>
#include <codecvt>
#include <locale>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>


using namespace std;
using namespace boost::property_tree;

namespace jysoft{  namespace utility {
/*-----------------------------------------------------------------------------------------------------------------
文件说明：     词典对照翻译表
创建人：	 hjg
创建时间：   2016/11/21
//-----------------------------------------------------------------------------------------------------------------*/
class AFX_EXT_CLASS CRefLexical_cast
{
public:
	CRefLexical_cast(void);
	virtual ~CRefLexical_cast(void);
public:
	/*******************************************************************************/
	// 函数名称： translateReferFile
	// 功能： 初始化词典对照信息
	// 参数： 
	//       const string &referFile:     
	// 返回值:  
	bool translateReferFile(const string &referFile);
	//获取目录对应的显示名称
	bool referSectionShowName(const string &propCode, /*out*/string *pstrName);
	//获取对应的值
	bool doReferLexical_cast(const string &lexicalCode, /*out*/string *lexicalShowValue);
	bool doReferLexical_cast(const string &propCode, const string &lexicalCode, /*out*/string *lexicalShowValue);
	//获取显示值的对应code
	bool revertReferLexical_cast(const string &propCode, const string &lexicalShowValue, /*out*/string *lexicalCode);
	//获取对应域内的所有值
	void referLexicalsIterator(const string &propCode, /*out*/map<string,string> *refValueMap, /*out*/vector<string> *lexicalCodes);
protected:
	wptree       *pt;
private:
	//typedef std::codecvt<wchar_t, char, std::mbstate_t>  code_type;
	//std::wstring_convert<code_type> m_conv;
};

}}
