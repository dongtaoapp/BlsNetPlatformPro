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
	�ļ�˵����    ���ƶ��շ���
	�����ˣ�	 hjg
	����ʱ�䣺   2017/5/1
	//-----------------------------------------------------------------------------------------------------------------*/
	class AFX_EXT_CLASS CRefLexical_laug_cast
	{
	public:
		CRefLexical_laug_cast(void);
		virtual ~CRefLexical_laug_cast(void);
	public:
		/*******************************************************************************/
		// �������ƣ� translateReferFile
		// ���ܣ� ��ʼ���ʵ������Ϣ
		// ������ 
		//       commonResourcePath:     Ŀ¼·��
		// ����ֵ:  
		bool translateReferFile(const string &commonResourcePath);
		//��ȡֵ��Ӧ����ʾ����
		string doReferLexical_cast(const string &lexicalCode);
	public:
		inline bool isInitialRefer() { return  m_bReferInitial; };
	private:
		wptree       *pt;
	private:
		//��ʼ���ʵ������Ϣ
		bool         m_bReferInitial;
	};
}}

