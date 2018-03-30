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
	// �������ƣ� doPackageIrp
	// ���ܣ�  ���Irp������
	// ������ 
	// ����ֵ: 
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
	// �������ƣ� UnzipPackage
	// ���ܣ� ��ѹ�������Irp������
	// ������ 
	//        char *lpData��
	//        UINT uNumber��
	// ����ֵ:  
	CRealTimeDataIrp * CRealTimeDataIrp::UnzipPackage(const char *lpstrPackage, UINT uNumber)
	{
		/*CRealTimeDataIrp  *pRealTimeIrp = NULL;
		//���������Irp������
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
	// �������ƣ� CreateRealTimeData_CPRIrp
	// ���ܣ� ����CPRʵʱ����Irp��
	// ������ 
	//        const _CPRData *ptrCPRDatas��
	//        int nLength��
	// ����ֵ:    
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

	//����CPRʵʱ��������
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

	//��ȡCPRʵʱ��������
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