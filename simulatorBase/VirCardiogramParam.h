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
		//���ز���ֵ
        virtual void LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm, int uHR, short sConduct = 0, short sExtendParam = 0) = 0;
		//�����ĵ�ʱ��Ѫ��������ʱ��
		virtual bool GetSpO2BeginTimeToCardiogram(/*out*/long &lBeginTime, /*out*/long &lCycleTime) { return false;};
		//�����粩ʱ��Ѫ��������ʱ��
		virtual bool GetSpO2BeginTimeToExtrasyst(/*out*/long &lBeginTime, /*out*/long &lPreSpO2BeginTime, /*out*/long &lCycleTime) { return false;};
		virtual void LoadExtrasystParamPre(Extrasys eExtrasyst) { };
		virtual void LoadExtrasystParam(Extrasys eExtrasyst) { };
		inline _eRefurbishDataRange GeteRefurbishDataRange() {return m_eRefurbishDataRange;};
		virtual void SeteRefurbishDataRange(_eRefurbishDataRange eRange) {m_eRefurbishDataRange = eRange;};
		virtual bool GetParamValue(const std::string &strKey, std::string &strValue);
		virtual bool GetParamValue(const std::string &strKey, const std::string &strParam, std::string &strValue) {return false; };
		virtual std::string GetExtrasystFileName(Extrasys eExtrasyst,const std::string &strKey) { return ""; };
		//�Ƿ���ȱʡ���粥
		virtual bool IsHaveDefalutExtrasyst() {return true;};
		//�Ƿ��ʼ����ʱ���������ĵ�ͼ����
		virtual bool IsInitialSendDoubleSampleData() { return true; };
		virtual void ReLoadCardiogramParam();
		//���������ļ������ļ�
        virtual LPSTREAM GetMakefileStream() ;
		//�������ļ�
        virtual LPSTREAM GetFileStream(const std::string &strFileName);
	public:
		//���������ļ�������
		std::string getConfigFileName() { return m_setParams["ConfigFileName"]; };
		//��������ʱ��
		int GetCycleTime();
		//����Q����S��ʱ��ε�ʱ�䣨��λ��0.1���룩
		virtual int GetPhaseTimeFromQtoS();
		//����S����T��ʱ��ε�ʱ�䣨��λ��0.1���룩
		virtual int GetPhaseTimeFromStoT();
		//���ص�ǰ�����ʴ���/����
		int GetRhythmHR();
		//���ص�ǰ����������
		inline BasicRhythm GetCurrentRhythm() { return m_eRhythm; };
		//�����Ƿ������ಫ���ź�
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
		_eRefurbishDataRange            m_eRefurbishDataRange;//�趨ˢ�����ݵĳ̶�
		QRS                             m_eQRS;
		BasicRhythm                     m_eRhythm;
		Extrasys                        m_eExtrasys;
        int                             m_uHR;
		//------------------------------------------------
        IStorage *                      m_pStorages;
	};

}}
