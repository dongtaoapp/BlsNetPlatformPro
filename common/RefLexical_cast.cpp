#include <locale.h>
#include <boost/format.hpp>
#include ".\RefLexical_cast.h"
#include ".\EncodeConv.h"


using namespace std;

namespace jysoft{
namespace utility {

	using namespace boost;

	CRefLexical_cast::CRefLexical_cast(void)/*: m_conv(new code_type('chs'))*/
	{
		pt = NULL;
	}


	CRefLexical_cast::~CRefLexical_cast(void)
	{
		if( pt != NULL )
		{
			delete pt;
		}
		pt = NULL;
	}

	/*******************************************************************************/
	// 函数名称： translateReferFile
	// 功能： 初始化词典对照信息
	// 参数： 
	//       const string &referFile:     
	// 返回值:  
	bool CRefLexical_cast::translateReferFile(const string &referFile)
	{
		if( pt != NULL )
		{
			delete pt;
		}
		pt = new wptree;
		try
		{
			std::wifstream f(referFile);
			std::locale utf8Locale(std::locale(), new std::codecvt_utf8<wchar_t>);
			f.imbue(utf8Locale); //先转换一下
			read_xml(f, *pt);
		}
		catch (xml_parser_error* e)
		{
			string er = e->message();
			return false;
		}
		return true;
	}

	//获取目录对应的显示名称
	bool CRefLexical_cast::referSectionShowName(const string &propCode, /*out*/string *pstrName)
	{
        foreach(auto &x, pt->get_child(L"reference_data"))
		{
			if( x.second.get<wstring>(L"<xmlattr>.prop_code") == s2w(propCode) )
			{
				wstring strNameW = x.second.get<wstring>(L"<xmlattr>.prop_name");
				*pstrName = w2s(strNameW);
				return true;
			}
		}
		return false;
	}

	//获取对应的值
	bool CRefLexical_cast::doReferLexical_cast(const string &lexicalCode, /*out*/string *lexicalShowValue)
	{
        foreach(auto &x, pt->get_child(L"reference_data"))
		{
            for (wptree::const_iterator itr = x.second.begin(); itr != x.second.end(); ++itr)
			{
				if( itr->second.get_optional<wstring>(L"<xmlattr>.code") )
				{
					if( itr->second.get<wstring>(L"<xmlattr>.code") == s2w(lexicalCode) )
					{
						wstring lexicalShowValueW = itr->second.get<wstring>(L"<xmlattr>.value");
						*lexicalShowValue = w2s(lexicalShowValueW);
						return true;
					}
				}
			}
		}
		return false;
	}

	bool CRefLexical_cast::doReferLexical_cast(const string &propCode, const string &lexicalCode, /*out*/string *lexicalShowValue)
	{
        foreach(auto &x, pt->get_child(L"reference_data"))
		{
			if( x.second.get<wstring>(L"<xmlattr>.prop_code") == s2w(propCode) )
			{
                for (wptree::const_iterator itr = x.second.begin(); itr != x.second.end(); ++itr)
				{
					if( itr->second.get_optional<wstring>(L"<xmlattr>.code") )
					{
						if( itr->second.get<wstring>(L"<xmlattr>.code") == s2w(lexicalCode) )
						{
							 wstring lexicalShowValueW = itr->second.get<wstring>(L"<xmlattr>.value");
							 *lexicalShowValue = w2s(lexicalShowValueW);
							return true;
						}
					}
				}
			}
		}
		return false;
	}

	//获取显示值的对应code
	bool CRefLexical_cast::revertReferLexical_cast(const string &propCode, const string &lexicalShowValue, /*out*/string *lexicalCode)
	{
        foreach(auto &x, pt->get_child(L"reference_data"))
		{
			if( x.second.get<wstring>(L"<xmlattr>.prop_code") == s2w(propCode) )
			{
                for (wptree::const_iterator itr = x.second.begin(); itr != x.second.end(); ++itr)
				{
					if( itr->second.get_optional<wstring>(L"<xmlattr>.code") )
					{
						if( itr->second.get<wstring>(L"<xmlattr>.value") == s2w(lexicalShowValue) )
						{
							 wstring lexicalCodeW = itr->second.get<wstring>(L"<xmlattr>.code");
							 *lexicalCode = w2s(lexicalCodeW); 
							return true;
						}
					}
				}
			}
		}
		return false;
	}

	//获取对应域内的所有值
	void CRefLexical_cast::referLexicalsIterator(const string &propCode, /*out*/map<string,string> *refValueMap, /*out*/vector<string> *lexicalCodes)
	{
        foreach(auto &x, pt->get_child(L"reference_data"))
		{
			if( x.second.get<wstring>(L"<xmlattr>.prop_code") == s2w(propCode) )
			{
                for (wptree::const_iterator itr = x.second.begin(); itr != x.second.end(); ++itr)
				{
					if( itr->second.get_optional<wstring>(L"<xmlattr>.code") )
					{
						wstring lexicalShowNameW, lexicalCodeW;
						lexicalShowNameW = itr->second.get<wstring>(L"<xmlattr>.value");
						lexicalCodeW = itr->second.get<wstring>(L"<xmlattr>.code");
						string  lexicalShowName, lexicalCode;
						lexicalShowName = w2s(lexicalShowNameW);
						lexicalCode  = w2s(lexicalCodeW);
						(*refValueMap)[lexicalCode] = lexicalShowName;
						if( lexicalCodes != NULL )
						{
							lexicalCodes->insert( lexicalCodes->end(), lexicalCode );
						}
					}
				}
			}
		}
	}

	
}}
