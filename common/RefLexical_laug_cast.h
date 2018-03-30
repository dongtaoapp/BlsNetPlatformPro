#pragma once
#include ".\common_global.h"
#include <string>
#include <codecvt>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>


using namespace std;
using namespace boost::property_tree;

namespace jysoft{  namespace utility 
{
	/*-----------------------------------------------------------------------------------------------------------------
	文件说明：    名称对照翻译
	创建人：	 hjg
	创建时间：   2017/5/1
	//-----------------------------------------------------------------------------------------------------------------*/
	class AFX_EXT_CLASS CRefLexical_laug_cast
	{
	public:
		CRefLexical_laug_cast(void);
		virtual ~CRefLexical_laug_cast(void);
	public:
		/*******************************************************************************/
		// 函数名称： translateReferFile
		// 功能： 初始化词典对照信息
		// 参数： 
		//       commonResourcePath:     目录路径
		// 返回值:  
		bool translateReferFile(const string &commonResourcePath);
		//获取值对应的显示名称
		string doReferLexical_cast(const string &lexicalCode);
	public:
		inline bool isInitialRefer() { return  m_bReferInitial; };
	private:
		wptree       *pt;
	private:
		//初始化词典对照信息
		bool         m_bReferInitial;
	};
}}

