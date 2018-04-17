#pragma once
#include <string>
#include <atlconv.h>
#include <objbase.h>
#include <boost/unordered_map.hpp>
#include ".\simulatorbase_global.h"

#include "..\Common\CommonGlobal.h"

namespace jysoft { namespace simulator { 

    class  SIMULATORBASESHARED_EXPORT CVirCardiogramParam
	{
	public:
		CVirCardiogramParam(void);
		virtual ~CVirCardiogramParam(void);
	public:
		//加载参数值
        virtual void LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm, int uHR, short sConduct = 0, short sExtendParam = 0) = 0;
		//产生心电时，血氧的启动时间
		virtual bool GetSpO2BeginTimeToCardiogram(/*out*/long &lBeginTime, /*out*/long &lCycleTime) { return false;};
		//产生早博时，血氧的启动时间
		virtual bool GetSpO2BeginTimeToExtrasyst(/*out*/long &lBeginTime, /*out*/long &lPreSpO2BeginTime, /*out*/long &lCycleTime) { return false;};
		virtual void LoadExtrasystParamPre(Extrasys eExtrasyst) { };
		virtual void LoadExtrasystParam(Extrasys eExtrasyst) { };
		inline _eRefurbishDataRange GeteRefurbishDataRange() {return m_eRefurbishDataRange;};
		virtual void SeteRefurbishDataRange(_eRefurbishDataRange eRange) {m_eRefurbishDataRange = eRange;};
		virtual bool GetParamValue(const std::string &strKey, std::string &strValue);
		virtual bool GetParamValue(const std::string &strKey, const std::string &strParam, std::string &strValue) {return false; };
		virtual std::string GetExtrasystFileName(Extrasys eExtrasyst,const std::string &strKey) { return ""; };
		//是否有缺省的早播
		virtual bool IsHaveDefalutExtrasyst() {return true;};
		//是否初始构建时发送两次心电图数据
		virtual bool IsInitialSendDoubleSampleData() { return true; };
		virtual void ReLoadCardiogramParam();
		//返回配置文件的流文件
        virtual LPSTREAM GetMakefileStream() ;
		//返回流文件
        virtual LPSTREAM GetFileStream(const std::string &strFileName);
	public:
		//返回配置文件的名称
		std::string getConfigFileName() { return m_setParams["ConfigFileName"]; };
		//返回周期时间
		int GetCycleTime();
		//返回Q波到S波时间段的时间（单位：0.1毫秒）
		virtual int GetPhaseTimeFromQtoS();
		//返回S波到T波时间段的时间（单位：0.1毫秒）
		virtual int GetPhaseTimeFromStoT();
		//返回当前的心率次数/分钟
		int GetRhythmHR();
		//返回当前的心律名称
		inline BasicRhythm GetCurrentRhythm() { return m_eRhythm; };
		//返回是否有心脏搏动信号
		virtual bool  isHaveHeartStartSign();
	protected:
		virtual void SetP_FileName( const std::string *  pStrParams) { m_setParams["P_FileName"] = pStrParams[0]; };
		virtual void SetP_ZoomTime( const std::string * pStrParams) { m_setParams["P_ZoomTime"] = pStrParams[1]; };
		virtual void SetP_ExtendTime(const std::string * pStrParams) { m_setParams["P_ExtendTime"] = pStrParams[2];};
		virtual void SetR_FileName( const std::string * pStrParams) { m_setParams["R_FileName"] = pStrParams[3];};
		virtual void SetR_ZoomTime( const std::string * pStrParams) { m_setParams["R_ZoomTime"]  = pStrParams[4];};
		virtual void SetR_ExtendTime(const std::string *pStrParams) { m_setParams["R_ExtendTime"] = pStrParams[5];};
		virtual void SetT_FileName( const std::string * pStrParams) { m_setParams["T_FileName"] = pStrParams[6];};
		virtual void SetT_ZoomTime( const std::string * pStrParams) { m_setParams["T_ZoomTime"] = pStrParams[7];};
		virtual void SetT_ExtendTime(const std::string * pStrParams) { m_setParams["T_ExtendTime"] = pStrParams[8];};
		virtual void Set_CycleTime(const std::string * pStrParams) { m_setParams["CycleTime"] = pStrParams[9]; };
		virtual void Set_HeartRate(const std::string * pStrParams) { m_setParams["HR"] = pStrParams[10]; };
	protected:
		boost::unordered_map<std::string, std::string>  m_setParams;
		_eRefurbishDataRange            m_eRefurbishDataRange;//设定刷新数据的程度
		QRS                             m_eQRS;
		BasicRhythm                     m_eRhythm;
		Extrasys                        m_eExtrasys;
        int                             m_uHR;
		//------------------------------------------------
        IStorage *                      m_pStorages;
	};

}}
