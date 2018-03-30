#pragma once
#include ".\RefLexical_cast.h"
#include ".\PatientRuleInterfaceGlobal.h"

using namespace jysoft::utility;

namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     成人生理体征参数
	创建人：	 hjg
	创建时间：   2016/2/29
	//-----------------------------------------------------------------------------------------------------------------*/
	class AFX_EXT_CLASS CAdultPatient : public IRhythmRule
		, public IRespRule
	{
	public:
		CAdultPatient(void);
		virtual ~CAdultPatient(void);
	protected:
		CRefLexical_cast       refLexical_cast;
	public:
		void initialPatient(const std::string &configuePath);
	public: //IRhythmRule接口函数重载
		//返回心律的显示名称
		virtual std::string GetRhythmDisplayTxt(const std::string &strRhythm);
		//返回早搏的显示名称
		virtual std::string GetExtrasysDisplayTxt(const std::string &strExtrasys);
		// 返回所有的基本节率名称
		virtual void GetBasicRhythm(std::list<std::string> & lstStrings);
		// 返回基本节率对应的心率值范围，并返回缺省的心率
		virtual short GetHRsForRhythm(BasicRhythm eRhythm, short &sMinValue, short &sMaxValue); 
		// 返回对应节率对应的所有早搏，并返回缺省值。如果没有返回false
		virtual bool GetExtraSystsToRhythm(BasicRhythm eRhythm, std::list<std::string> * plstExtras);
	public: //IRespRule接口函数重载
		//返回呼吸的模式类型
		virtual void GetRespModes(std::list<std::string> & lstStrings);
		//返回呼吸模式的缺省呼吸次数
		virtual long GetRespModeDefaultRate(eRespMode eMode);
		//返回呼吸模式显示名称
		virtual std::string GetRespModeDisplayTxt(const std::string  &strRespMode);
	};

}}