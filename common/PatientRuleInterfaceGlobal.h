#pragma once
#include <list>
#include ".\CommonGlobal.h"
#include ".\common_global.h"

namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	文件说明：     不同类型的模拟人的生理体征参数接口类集合
	创建人：	 hjg
	创建时间：   2016/11/21
	//-----------------------------------------------------------------------------------------------------------------*/

	/****************************心律参数接口*********************************************************/
	class AFX_EXT_CLASS IRhythmRule
	{
	public:
		IRhythmRule();
		virtual ~IRhythmRule();
	public:
		//返回心律的显示名称
		virtual std::string GetRhythmDisplayTxt(const std::string &strRhythm) = 0;
		//返回早搏的显示名称
		virtual std::string GetExtrasysDisplayTxt(const std::string &strExtrasys) = 0;
	public:
		// 返回所有的基本节率名称
		virtual void GetBasicRhythm(std::list<std::string> & lstStrings) = 0;
		// 返回基本节率对应的心率值范围，并返回缺省的心率
		virtual short GetHRsForRhythm(BasicRhythm eRhythm, short &sMinValue, short &sMaxValue) = 0; 
		// 返回对应节率对应的所有早搏，并返回缺省值。如果没有返回false
		virtual bool GetExtraSystsToRhythm(BasicRhythm eRhythm, std::list<std::string> * plstExtras) = 0;

		//根据心律返回合适的心率
		virtual bool GetRightRateForRhythm(int nHeartRate, BasicRhythm eRhythm, int *pRightHeartRate);
	public:
		static std::string GetstrQRS(QRS eQRS);
		static std::string GetstrBasicRhythm(BasicRhythm eRhythm);
		static std::string GetstrExtrasys(Extrasys eExtrasys);
		//------------------------------------------------------------------------
		static QRS  Get_eQRS(const std::string &strQRS);
		static BasicRhythm Get_eRhythm(const std::string &strRhythm);
		static Extrasys Get_eExtrasys(const std::string &strExtrasys);
		//-1:都没选；0：Muscular；1:50/60HZ
		static Artifact Get_eArtifact(int iArtifact);
	};

	/****************************呼吸模式接口*********************************************************/
	class AFX_EXT_CLASS IRespRule
	{
	public:
		IRespRule();
		virtual ~IRespRule();
	public:
		//返回呼吸的模式类型
		virtual void GetRespModes(std::list<std::string> & lstStrings) = 0;
		//返回呼吸模式的缺省呼吸次数
		virtual long GetRespModeDefaultRate(eRespMode eMode) = 0;
		//返回呼吸模式显示名称
		virtual std::string GetRespModeDisplayTxt(const std::string  &strRespMode) = 0;
	public:
		static std::string   GetstrRespMode(eRespMode eMode);
		static eRespMode Get_eRespMode(const std::string &strRespMode);

	};

	/****************************体征范围接口*********************************************************/
	class AFX_EXT_CLASS ISignsRespRule
	{
	public:
		ISignsRespRule();
		virtual ~ISignsRespRule();
	public:
		//返回体征类型
		virtual void			GetSignsMold(std::list<std::string> & lstStrings) = 0;
		//返回体征显示名称
		virtual std::string			GetSignsModeDisplayTxt(const std::string  &strRespMode) = 0;
		//返回体征单位
		virtual std::string			GetSignsModeUnit(const std::string &strRespMode) = 0;
	public:
		static  float			GetSignsModeDefault( const std::string &strRespMode );
	};
}}
