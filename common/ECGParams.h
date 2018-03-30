#pragma once
#include ".\CommonGlobal.h"

namespace jysoft { namespace simulator {
	
	class AFX_EXT_CLASS CECGParams
	{
	public:
		CECGParams(void);
		virtual ~CECGParams(void);
	public:
        unsigned long        m_dwField;        //����ָ����Щ��������ֵ
		Artifact     m_eArtifact;      //PM_ARTIFACT = 0x00000001
		int          m_iExtrasysRate;  //�粫�ı��� PM_EXTRASYSRATE = 0x00000002
		BasicRhythm  m_eBasicRm;       //��������   PM_BASICRHYTHM = 0x00000008
		Extrasys     m_eExtrasys;      //�����������粫�� PM_EXTRASYS = 0x00000010
		int          m_iHR;            //��������   PM_HR = 0x00000020
        bool         m_bHRPercent;     //���ʸı����  PM_HRPER = 0x00000400
        short         m_uSize;          //�Ŵ�ߴ�   PM_SIZE = 0x00000040
		HeartSpeak   m_eSpeed;         //�����ٶ�   PM_SPEED = 0x00000080
        bool         m_bEMD;           //           PM_EMD   = 0x00000100
		short        m_sConduct;       //����       PM_CONDUCT = 0x00000200
		short        m_sExtendParam;   //��չ����   PM_EXTEND  = 0x00000800
	public:
		/**
		*	��ֵ����
		*/
		const CECGParams & operator = (const CECGParams & params);
		// ��Ϊ�������ĵ�ͼ����
		void  SetDefault(SimulatePatientType ePatientType);
		//����ĵ�ͼ����
		void  ClearEcgParams();
	};
	
}}
