#pragma once
#include ".\common_global.h"
#include <string>
#include <boost/locale.hpp> 
 
//wstring to string
#define w2s jysoft::utility::CEncodeConv::WStringToString    
//string to wstring
#define s2w jysoft::utility::CEncodeConv::StringToWString
//gdk to utf8
#define g2u jysoft::utility::CEncodeConv::gbktoutf8
//utf8 to gdk
#define u2g jysoft::utility::CEncodeConv::utf8togbk
//-----------------------------------------------------------------------------------
namespace jysoft { namespace utility {

	class AFX_EXT_CLASS CEncodeConv
	{
	public:
		CEncodeConv(void);
		virtual ~CEncodeConv(void);
	public:
		//s2ws
		static std::wstring StringToWString(const std::string &str);
		//ws2s
		static std::string WStringToString(const std::wstring &wstr);
	public:
		//封装 string between( string const &text,string const &to_encoding,  
		//string const &from_encoding,method_type how = default_method);   
		//直接处理gbk转utf8编码  
		static std::string gbktoutf8(std::string const &text);  
		//直接处理utf8转gbk  
		static std::string utf8togbk(std::string const &text);  
		//直接处理big5转utf8  
		static std::string big5toutf8(std::string const &text);  
		//直接处理utf8转big5  
		static std::string utf8tobig5(std::string const &text); 
	protected:
		//代码转换:从一种编码转为另一种编码    
        static int code_convert(const char* from_charset, const char* to_charset, const char* inbuf, int inlen, char* outbuf, int outlen);
	};

}}
