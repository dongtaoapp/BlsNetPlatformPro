#pragma once
#include ".\RefLexical_cast.h"
#include ".\PatientRuleInterfaceGlobal.h"

using namespace jysoft::utility;

namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ����������������
	�����ˣ�	 hjg
	����ʱ�䣺   2016/2/29
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
	public: //IRhythmRule�ӿں�������
		//�������ɵ���ʾ����
		virtual std::string GetRhythmDisplayTxt(const std::string &strRhythm);
		//�����粫����ʾ����
		virtual std::string GetExtrasysDisplayTxt(const std::string &strExtrasys);
		// �������еĻ�����������
		virtual void GetBasicRhythm(std::list<std::string> & lstStrings);
		// ���ػ������ʶ�Ӧ������ֵ��Χ��������ȱʡ������
		virtual short GetHRsForRhythm(BasicRhythm eRhythm, short &sMinValue, short &sMaxValue); 
		// ���ض�Ӧ���ʶ�Ӧ�������粫��������ȱʡֵ�����û�з���false
		virtual bool GetExtraSystsToRhythm(BasicRhythm eRhythm, std::list<std::string> * plstExtras);
	public: //IRespRule�ӿں�������
		//���غ�����ģʽ����
		virtual void GetRespModes(std::list<std::string> & lstStrings);
		//���غ���ģʽ��ȱʡ��������
		virtual long GetRespModeDefaultRate(eRespMode eMode);
		//���غ���ģʽ��ʾ����
		virtual std::string GetRespModeDisplayTxt(const std::string  &strRespMode);
	};

}}