#pragma once
#include <list>
#include ".\CommonGlobal.h"
#include ".\common_global.h"

namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	�ļ�˵����     ��ͬ���͵�ģ���˵��������������ӿ��༯��
	�����ˣ�	 hjg
	����ʱ�䣺   2016/11/21
	//-----------------------------------------------------------------------------------------------------------------*/

	/****************************���ɲ����ӿ�*********************************************************/
	class AFX_EXT_CLASS IRhythmRule
	{
	public:
		IRhythmRule();
		virtual ~IRhythmRule();
	public:
		//�������ɵ���ʾ����
		virtual std::string GetRhythmDisplayTxt(const std::string &strRhythm) = 0;
		//�����粫����ʾ����
		virtual std::string GetExtrasysDisplayTxt(const std::string &strExtrasys) = 0;
	public:
		// �������еĻ�����������
		virtual void GetBasicRhythm(std::list<std::string> & lstStrings) = 0;
		// ���ػ������ʶ�Ӧ������ֵ��Χ��������ȱʡ������
		virtual short GetHRsForRhythm(BasicRhythm eRhythm, short &sMinValue, short &sMaxValue) = 0; 
		// ���ض�Ӧ���ʶ�Ӧ�������粫��������ȱʡֵ�����û�з���false
		virtual bool GetExtraSystsToRhythm(BasicRhythm eRhythm, std::list<std::string> * plstExtras) = 0;

		//�������ɷ��غ��ʵ�����
		virtual bool GetRightRateForRhythm(int nHeartRate, BasicRhythm eRhythm, int *pRightHeartRate);
	public:
		static std::string GetstrQRS(QRS eQRS);
		static std::string GetstrBasicRhythm(BasicRhythm eRhythm);
		static std::string GetstrExtrasys(Extrasys eExtrasys);
		//------------------------------------------------------------------------
		static QRS  Get_eQRS(const std::string &strQRS);
		static BasicRhythm Get_eRhythm(const std::string &strRhythm);
		static Extrasys Get_eExtrasys(const std::string &strExtrasys);
		//-1:��ûѡ��0��Muscular��1:50/60HZ
		static Artifact Get_eArtifact(int iArtifact);
	};

	/****************************����ģʽ�ӿ�*********************************************************/
	class AFX_EXT_CLASS IRespRule
	{
	public:
		IRespRule();
		virtual ~IRespRule();
	public:
		//���غ�����ģʽ����
		virtual void GetRespModes(std::list<std::string> & lstStrings) = 0;
		//���غ���ģʽ��ȱʡ��������
		virtual long GetRespModeDefaultRate(eRespMode eMode) = 0;
		//���غ���ģʽ��ʾ����
		virtual std::string GetRespModeDisplayTxt(const std::string  &strRespMode) = 0;
	public:
		static std::string   GetstrRespMode(eRespMode eMode);
		static eRespMode Get_eRespMode(const std::string &strRespMode);

	};

	/****************************������Χ�ӿ�*********************************************************/
	class AFX_EXT_CLASS ISignsRespRule
	{
	public:
		ISignsRespRule();
		virtual ~ISignsRespRule();
	public:
		//������������
		virtual void			GetSignsMold(std::list<std::string> & lstStrings) = 0;
		//����������ʾ����
		virtual std::string			GetSignsModeDisplayTxt(const std::string  &strRespMode) = 0;
		//����������λ
		virtual std::string			GetSignsModeUnit(const std::string &strRespMode) = 0;
	public:
		static  float			GetSignsModeDefault( const std::string &strRespMode );
	};
}}
