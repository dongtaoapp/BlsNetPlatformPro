#include <locale.h>
#include <boost/format.hpp>
#include ".\RefLexical_laug_cast.h"
#include ".\EncodeConv.h"


#define  _LauguageFile              "\\laug\\LanguateTransform.xml"

using namespace boost;
namespace jysoft{  namespace utility 
{
	CRefLexical_laug_cast::CRefLexical_laug_cast(void)
	{
		pt = NULL;
		m_bReferInitial = false;
	}
	
	CRefLexical_laug_cast::~CRefLexical_laug_cast(void)
	{
		if( pt != NULL )
		{
			delete pt;
		}
		pt = NULL;
	}

	/*******************************************************************************/
	// �������ƣ� translateReferFile
	// ���ܣ� ��ʼ���ʵ������Ϣ
	// ������ 
	//       commonResourcePath:     Ŀ¼·��
	// ����ֵ:  
	bool CRefLexical_laug_cast::translateReferFile(const string &commonResourcePath)
	{
		if( pt != NULL )
		{
			delete pt;
		}
		m_bReferInitial = false;
		pt = new wptree;
		try
		{
			string  referFile = commonResourcePath + _LauguageFile;
			std::wifstream f(referFile);
			std::locale utf8Locale(std::locale(), new std::codecvt_utf8<wchar_t>);
			f.imbue(utf8Locale); //��ת��һ��
			read_xml(f, *pt);
		}
		catch (xml_parser_error* e)
		{
			string er = e->message();
            return false;
		}
		m_bReferInitial = true;
		return true;
	}

	//��ȡֵ��Ӧ����ʾ����
	string CRefLexical_laug_cast::doReferLexical_cast(const string &lexicalCode)
	{
		string  lexicalShowValue = lexicalCode;
        foreach(auto &x, pt->get_child(L"LanguateTransform"))
		{
            if( x.second.get<wstring>(L"<xmlattr>.sign") == s2w(lexicalCode) )
			{
                wstring strNameW = x.second.get<wstring>(L"<xmlattr>.transform");
				lexicalShowValue = w2s(strNameW);
				break;
			}
		}
		return lexicalShowValue;
	}
}}
