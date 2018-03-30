#include "StdAfx.h"
#include ".\realtimedatairp.h"
#include <strstream>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/format.hpp>
#include <boost/foreach.hpp>
#include <boost/assert.hpp>
#include <boost/dynamic_bitset.hpp>


#define  _CPR_ORDER_L           8

using namespace boost;
using namespace boost::property_tree;
namespace jysoft { namespace irp {

	CRealTimeDataIrp::CRealTimeDataIrp(void)
	{
		m_ptrCPRDatas   = NULL;
		m_nLength       = 0;
	}

	CRealTimeDataIrp::~CRealTimeDataIrp(void)
	{
		if( m_nLength != 0 && m_ptrCPRDatas )
		{
			delete [] m_ptrCPRDatas;
		}
	}

	bool CRealTimeDataIrp::isKindOf(const std::string &strClass)
	{	
		if( strClass == "CRealTimeDataIrp" )
		{
			return true;
		}
		return false;
	}	

	/*******************************************************************************/
	// 函数名称： doPackageIrp
	// 功能：  打包Irp的内容
	// 参数： 
	// 返回值: 
	std::string CRealTimeDataIrp::doPackageIrp()
	{
		BOOST_ASSERT(0);
		std::string     strData;
		for (int nStep=0; nStep < m_nLength; ++nStep)
		{
			boost::format fmt("<CPRSample><lung value=\"%d\" /><pressure value=\"%d\" /><order value=\"%d\" /><pressureRate value=\"%d\" /><releaseError value=\"%d\" /></CPRSample>");
			fmt % int(m_ptrCPRDatas[nStep].get<0>()) \
				% int(m_ptrCPRDatas[nStep].get<2>()) \
				% m_ptrCPRDatas[nStep].get<3>() \
				% int(m_ptrCPRDatas[nStep].get<4>()) \
				% m_ptrCPRDatas[nStep].get<5>() \
				;
			strData   = strData + fmt.str();
		}
		boost::format fmt("<CPR_RealTimeData>%s</CPR_RealTimeData>");
		fmt % strData;
		return fmt.str();
	}

	/*******************************************************************************/
	// 函数名称： UnzipPackage
	// 功能： 解压缩打包的Irp的内容
	// 参数： 
	//        char *lpData：
	//        UINT uNumber：
	// 返回值:  
	CRealTimeDataIrp * CRealTimeDataIrp::UnzipPackage(const char *lpstrPackage, UINT uNumber)
	{
		/*CRealTimeDataIrp  *pRealTimeIrp = NULL;
		//解析打包的Irp的内容
		std::istrstream   sstream(lpstrPackage, uNumber);
		ptree     pt;
		read_xml( sstream, pt );
		ptree::assoc_iterator pos = pt.find("CPR_RealTimeData");
		int  count = pos->second.size();
		if( count > 0 )
		{
			pRealTimeIrp = new CRealTimeDataIrp();
			pRealTimeIrp->m_ptrCPRDatas = new _CPRData[count];
			pRealTimeIrp->m_nLength = count;
			int step = 0;
			BOOST_FOREACH(auto &x, pt.get_child("CPR_RealTimeData"))
			{
				unsigned char sLung, pressDepth, speed;
				unsigned char orderValue = 0;
				bool  releaseErr = false;
				sLung = x.second.get<unsigned char>("lung_L.<xmlattr>.value");
				pressDepth = x.second.get<unsigned char>("pressure.<xmlattr>.value");
				speed  = x.second.get<unsigned char>("pressureRate.<xmlattr>.value");
				orderValue = x.second.get<unsigned char>("order.<xmlattr>.value");
				releaseErr = x.second.get<unsigned char>("releaseError.<xmlattr>.value") ? true : false;
				//-------------------------------------------------------------------------------------------------------------
				pRealTimeIrp->m_ptrCPRDatas[step] = make_tuple(sLung, 0, pressDepth, orderValue, speed, releaseErr, 0);
				++step;
				if( step >= count )
				{
					break;
				}
			}
		}
		return pRealTimeIrp;*/
		return NULL;
	}

	/*******************************************************************************/
	// 函数名称： CreateRealTimeData_CPRIrp
	// 功能： 创建CPR实时数据Irp类
	// 参数： 
	//        const _CPRData *ptrCPRDatas：
	//        int nLength：
	// 返回值:    
	CRealTimeDataIrp * CRealTimeDataIrp::CreateRealTimeData_CPRIrp(const _CPRData *ptrCPRDatas, int nLength)
	{
		CRealTimeDataIrp  *pRealTimeDataIrp = NULL;
		if( nLength > 0 )
		{
			pRealTimeDataIrp = new CRealTimeDataIrp();
			pRealTimeDataIrp->SetCPR_RealTimeData(ptrCPRDatas, nLength);
		}
		return pRealTimeDataIrp;
	}

	//设置CPR实时采样数据
	void CRealTimeDataIrp::SetCPR_RealTimeData(/*in*/const _CPRData *ptrCPRDatas, int nLength)
	{
		if( nLength > 0 )
		{
			m_ptrCPRDatas = new _CPRData[nLength];
		}
		for (int index=0; index < nLength; ++index)
		{
			m_ptrCPRDatas[index] = ptrCPRDatas[index];
		}
		m_nLength = nLength;
	}

	//获取CPR实时采样数据
	int CRealTimeDataIrp::GetCPR_RealTimeData(/*out*/_CPRData *ptrCPRDatas)
	{
		if( ptrCPRDatas != NULL )
		{
			for (int index=0; index < m_nLength; ++index)
			{
				ptrCPRDatas[index] = m_ptrCPRDatas[index];
			}
		}
		return m_nLength;
	}

}}