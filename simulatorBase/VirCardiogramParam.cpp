#include <boost/lexical_cast.hpp>
#include ".\VirCardiogramParam.h"

#include "..\common\EncodeConv.h"

namespace jysoft { namespace simulator { 

	CVirCardiogramParam::CVirCardiogramParam(void)
	{
		m_eRefurbishDataRange = RD_LoadConfigFile;
		m_eQRS = QRS_None;
		m_eRhythm = BR_Sinus;
		m_eExtrasys = ES_None;
		m_uHR     = 0;
		//------------------------------------------------------------
        m_pStorages = NULL;
	}

	CVirCardiogramParam::~CVirCardiogramParam(void)
	{
        if(m_pStorages != NULL)
        {
            m_pStorages->Release();
        }
	}

	bool CVirCardiogramParam::GetParamValue(const std::string &strKey, std::string &strValue)
	{
		boost::unordered_map<std::string, std::string>::iterator iter;
		iter = m_setParams.find( strKey );
		if( iter != m_setParams.end() )
		{
			strValue = iter->second;
			return true;
		}
		return false;
	}

	int CVirCardiogramParam::GetCycleTime()
	{
		std::string strTime;
		if( GetParamValue("CycleTime", /*out*/strTime) )
		{
			return boost::lexical_cast<int>(strTime);
		}
		return 0;
	}

	//返回当前的心率次数/分钟
	int CVirCardiogramParam::GetRhythmHR()
	{
		boost::unordered_map<std::string, std::string>::iterator iter;
		iter = m_setParams.find( "HR" );
		if(  iter != m_setParams.end() )
		{
			return boost::lexical_cast<int>(iter->second);
		}
		return 0;
	}

	void CVirCardiogramParam::ReLoadCardiogramParam()
	{
		LoadCardiogramParam( m_eQRS, m_eRhythm, m_uHR);
	}

	//返回配置文件的流文件
    LPSTREAM CVirCardiogramParam::GetMakefileStream()
    {
        LPSTREAM lpStream = NULL;
        if( m_pStorages )
        {
            m_pStorages->OpenStream(L"MakeFile.txt",NULL,STGM_READ|STGM_SHARE_EXCLUSIVE,0,&lpStream);
        }
        return lpStream;
    }

	//返回流文件
    LPSTREAM CVirCardiogramParam::GetFileStream(const std::string &strFileName)
    {
        USES_CONVERSION;
        LPSTREAM lpStream = NULL;
        if( m_pStorages )
        {
            m_pStorages->OpenStream(s2w(strFileName).c_str(),NULL,STGM_READ|STGM_SHARE_EXCLUSIVE,0,&lpStream);
        }
        return lpStream;
    }

	//返回是否有心脏搏动信号
	bool  CVirCardiogramParam::isHaveHeartStartSign()
	{
		long   lBeginTime, lCycleTime;
		return GetSpO2BeginTimeToCardiogram(lBeginTime, lCycleTime) ;
	}

	//返回Q波到S波时间段的时间（单位：0.1毫秒）
	int CVirCardiogramParam::GetPhaseTimeFromQtoS()
	{
		std::string    strRZoomTime( "0" );
		GetParamValue( "R_ZoomTime", /*out*/strRZoomTime);
		std::string    strRExtendTime( "0" );
		GetParamValue( "R_ExtendTime" , /*out*/strRExtendTime);
		return boost::lexical_cast<int>(strRZoomTime)/2 + boost::lexical_cast<int>(strRExtendTime);
	}

	//返回S波到T波时间段的时间（单位：0.1毫秒）
	int CVirCardiogramParam::GetPhaseTimeFromStoT()
	{	
		std::string    strTZoomTime( "0" );
		GetParamValue( "T_ZoomTime" , /*out*/strTZoomTime);
		return boost::lexical_cast<int>(strTZoomTime);
	}

}}
