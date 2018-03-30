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
�ļ�˵����     �ʵ���շ����
�����ˣ�	 hjg
����ʱ�䣺   2016/11/21
//-----------------------------------------------------------------------------------------------------------------*/
class AFX_EXT_CLASS CRefLexical_cast
{
public:
	CRefLexical_cast(void);
	virtual ~CRefLexical_cast(void);
public:
	/*******************************************************************************/
	// �������ƣ� translateReferFile
	// ���ܣ� ��ʼ���ʵ������Ϣ
	// ������ 
	//       const string &referFile:     
	// ����ֵ:  
	bool translateReferFile(const string &referFile);
	//��ȡĿ¼��Ӧ����ʾ����
	bool referSectionShowName(const string &propCode, /*out*/string *pstrName);
	//��ȡ��Ӧ��ֵ
	bool doReferLexical_cast(const string &lexicalCode, /*out*/string *lexicalShowValue);
	bool doReferLexical_cast(const string &propCode, const string &lexicalCode, /*out*/string *lexicalShowValue);
	//��ȡ��ʾֵ�Ķ�Ӧcode
	bool revertReferLexical_cast(const string &propCode, const string &lexicalShowValue, /*out*/string *lexicalCode);
	//��ȡ��Ӧ���ڵ�����ֵ
	void referLexicalsIterator(const string &propCode, /*out*/map<string,string> *refValueMap, /*out*/vector<string> *lexicalCodes);
protected:
	wptree       *pt;
private:
	//typedef std::codecvt<wchar_t, char, std::mbstate_t>  code_type;
	//std::wstring_convert<code_type> m_conv;
};

}}
