#include "iconv.h"
#include ".\EncodeConv.h"
#include <boost/lexical_cast.hpp>


#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "iconv.lib")


using namespace std;
using namespace boost::locale::conv;

namespace jysoft { namespace utility {

	CEncodeConv::CEncodeConv(void)
	{
	}


	CEncodeConv::~CEncodeConv(void)
	{
	}

	//直接处理gbk转utf8编码  
	std::string CEncodeConv::gbktoutf8(std::string const &text)
	{
		//"UTF-8", "GBK"  
		std::string const &to_encoding("UTF-8");  
		std::string const &from_encoding("GBK");  
		method_type how = default_method;  
		return boost::locale::conv::between(text.c_str(), text.c_str() + text.size(), to_encoding, from_encoding, how);

		/*std::string   utf8Txt;
		int nOutLen = 2 * text.length() - 1;  
		if( nOutLen > 0 )
		{
			char* szOut = (char*)malloc(nOutLen);
			if (-1 == code_convert("gb2312","utf-8",text.c_str(),text.length(),szOut,nOutLen))  
			{    
				szOut = NULL;  
			}
			else
			{
				utf8Txt = std::string(szOut, nOutLen);
			}
			free(szOut);
		}
		return utf8Txt;*/
	}

	//直接处理utf8转gbk  
	std::string CEncodeConv::utf8togbk(std::string const &text)
	{
		std::string   gbkTxt;
		int nOutLen = 2 * text.length() - 1;  
		if( nOutLen > 0 )
		{
			char* szOut = (char*)malloc(nOutLen);  

			if (-1 == code_convert("utf-8","gb2312",text.c_str(),text.length(),szOut,nOutLen))  
			{   
				szOut = NULL;  
			}  
			else
			{
				gbkTxt = std::string(szOut, nOutLen);
			}
			free(szOut);
		}
		return gbkTxt;  
		/*std::string const &to_encoding("GBK");  
		std::string const &from_encoding("UTF-8");  
		method_type how = default_method;  
		return boost::locale::conv::between(text.c_str(), text.c_str() + text.size(), to_encoding, from_encoding, how);*/ 
	}

	//直接处理big5转utf8  
	std::string CEncodeConv::big5toutf8(std::string const &text)
	{
		std::string const &to_encoding("UTF-8");  
		std::string const &from_encoding("BIG5");  
		method_type how = default_method;  
		return boost::locale::conv::between(text.c_str(), text.c_str() + text.size(), to_encoding, from_encoding, how); 
	}

	//直接处理utf8转big5  
	std::string CEncodeConv::utf8tobig5(std::string const &text)
	{
		std::string const &to_encoding("BIG5");  
		std::string const &from_encoding("UTF-8");  
		method_type how = default_method;  
		return boost::locale::conv::between(text.c_str(), text.c_str() + text.size(), to_encoding, from_encoding, how);
	}

	std::wstring CEncodeConv::StringToWString(const std::string &str)
	{    
		setlocale(LC_ALL, "chs");  

		const char* _Source = str.c_str();  
		size_t _Dsize = str.size() + 1;  
		wchar_t *_Dest = new wchar_t[_Dsize];  
		wmemset(_Dest, 0, _Dsize);  
		mbstowcs(_Dest,_Source, _Dsize);  
		wstring result = _Dest;  
		delete []_Dest;  

		setlocale(LC_ALL, "C");  

		return result;  
		//方式二：
/*#ifdef WIN32  
		static std::string codepage;   
		if ( codepage.empty() ) {  
			// 获得系统当前的代码页。对于中文Windows,   
			CPINFOEX  cpinfo;  
			GetCPInfoEx( CP_ACP, 0, &cpinfo );  
			cpinfo.CodePageName;  
			codepage = "CP" + boost::lexical_cast<std::string>(cpinfo.CodePage);  
		}  

		std::wstring dst = boost::locale::conv::to_utf<wchar_t>( src, codepage.c_str() );  
#else  
		std::locale loc = boost::locale::generator().generate("");  
		std::wstring dst = boost::locale::conv::to_utf<wchar_t>( src, loc );  
#endif  
		return dst*/
	}

	//wstring高字节不为0，返回FALSE
	std::string CEncodeConv::WStringToString(const std::wstring &wstr)
	{    
		string curLocale = setlocale(LC_ALL, NULL); // curLocale = "C";  

		setlocale(LC_ALL, "chs");  

		const wchar_t* _Source = wstr.c_str();  
		size_t _Dsize = 2 * wstr.size() + 1;  
		char *_Dest = new char[_Dsize];  
		memset(_Dest,0,_Dsize);  
		wcstombs(_Dest,_Source,_Dsize);  
		string result = _Dest;  
		delete []_Dest;  

		setlocale(LC_ALL, curLocale.c_str());  

		return result;  
	}

	//代码转换:从一种编码转为另一种编码    
    int CEncodeConv::code_convert(const char* from_charset, const char* to_charset, const char* inbuf, int inlen, char* outbuf, int outlen)
	{  
		iconv_t cd;  

		const char** pin = &inbuf;    

		char** pout = &outbuf;  

		cd = iconv_open(to_charset,from_charset);    

		if(cd == 0)  
			return -1;  

		memset(outbuf,0,outlen);    

        if(iconv(cd,(const char**)pin,(unsigned int *)&inlen,pout,(unsigned int*)&outlen)  == -1)
        {
            return -1;
        }
		iconv_close(cd);  

		return 0;    
	}  
}}
