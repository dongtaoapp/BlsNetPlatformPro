#pragma once
#include ".\CommonGlobal.h"

namespace jysoft { namespace simulator {
	
	class AFX_EXT_CLASS CECGParams
	{
	public:
		CECGParams(void);
		virtual ~CECGParams(void);
	public:
        unsigned long        m_dwField;        //用语指明哪些变量被赋值
		Artifact     m_eArtifact;      //PM_ARTIFACT = 0x00000001
		int          m_iExtrasysRate;  //早搏的比率 PM_EXTRASYSRATE = 0x00000002
		BasicRhythm  m_eBasicRm;       //基本心律   PM_BASICRHYTHM = 0x00000008
		Extrasys     m_eExtrasys;      //期外收缩（早搏） PM_EXTRASYS = 0x00000010
		int          m_iHR;            //心跳次数   PM_HR = 0x00000020
        bool         m_bHRPercent;     //心率改变比率  PM_HRPER = 0x00000400
        short         m_uSize;          //放大尺寸   PM_SIZE = 0x00000040
		HeartSpeak   m_eSpeed;         //心跳速度   PM_SPEED = 0x00000080
        bool         m_bEMD;           //           PM_EMD   = 0x00000100
		short        m_sConduct;       //传导       PM_CONDUCT = 0x00000200
		short        m_sExtendParam;   //扩展参数   PM_EXTEND  = 0x00000800
	public:
		/**
		*	赋值操作
		*/
		const CECGParams & operator = (const CECGParams & params);
		// 设为正常的心电图参数
		void  SetDefault(SimulatePatientType ePatientType);
		//清除心电图参数
		void  ClearEcgParams();
	};
	
}}
