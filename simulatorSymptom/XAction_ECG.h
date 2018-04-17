#pragma once
#include "xactionvirtual.h"

#include "..\Common\ECGParams.h"
#include "..\Common\CommonGlobal.h"


namespace jysoft { namespace simulator {
    class SIMULATORSYMPTOMSHARED_EXPORT CXAction_ECG : public CXActionVirtual
	{
	public:
		CXAction_ECG(void);
		CXAction_ECG(const std::string &strRhythm, const std::string &strHR);
		virtual ~CXAction_ECG(void);
	public: //基类函数重载
		virtual bool isKindOf(const std::string &strClassName);
		/*******************************************************************************/
		// 函数名称： GetActionCaption
		// 功能：   返回体征标识名
		// 参数：   
		// 返回值: 
		virtual std::string getActionCaption() const;
		/*******************************************************************************/
		// 函数名称： Parse_ActionFromXml
		// 功能：   解析体征参数内容
		// 参数：   IXMLDOMNode *pXMLShapeNode:
		// 返回值: 
		virtual bool Parse_ActionFromXml(pugi::xml_node* pXMLShapeNode);
		/*******************************************************************************/
		// 函数名称： CombineActionParam
		// 功能：   整合体征设置参数
		// 参数：   CXActionVirtual *pDstActionVir:
		// 返回值: 
		virtual void CombineActionParam(CXActionVirtual *pDstActionVir);
		/*******************************************************************************/
		// 函数名称： CloneAction
		// 功能：   拷贝体征参数
		// 参数：   
		// 返回值: 
		virtual CXActionVirtual * CloneAction();
	public:
		void Set_EcgActionParam( const CECGParams &cEcgParam );
		//返回绝对心率值
		int  GetValue_AbsoluteHR( int nSrcHR );
	protected:
		void SetAction_Ecg(const std::string &strRhythm, const std::string &strHR, const std::string &strExtrasyst, const std::string &strExtrasystRate, int nArtifacts,short sEMD, short sConduct, short sExtendParam);
	public:
		//返回QRS
		QRS GetValue_eQRS() { return QRS_A; };
		//返回心律名
		BasicRhythm GetValue_eBasicRhythm();
		//返回早搏名
		Extrasys    GetValue_eExtrasys();
		//返回早搏测试/分钟
		int         GetValue_ExtrasystRate();
		//返回心跳次数/分钟
		int GetValue_HR();
		//返回干扰选项
		Artifact    GetValue_eArtifact();
		//返回EMD
		bool   GetValue_EMD();
		//返回传导值
		short  GetValue_Conduct();
		//返回扩展值
		short  GetValue_ExtendParam();
		inline unsigned long Get_FieldsFlag() { return m_dwFields; };
		inline void Set_FieldsFlag(unsigned long dwField) { m_dwFields = dwField; };
		inline void Set_bRelatePercent( bool bPercent ) { m_bRelatePercent = bPercent; };
		inline bool Get_bRelatePercent() { return m_bRelatePercent; };
	public:
		int             m_nArtifacts;          //-1:都没选；0：Muscular；1:50/60HZ
		std::string     m_strExtrasystRate;    //早搏发生率
		std::string     m_strRhythm;
		std::string     m_strExtrasyst;
		std::string     m_strHR;
		int             m_sEMD;
		short           m_sConduct;            //传导       PM_CONDUCT = 0x00000200
		short           m_sExtendParam;        //扩展参数   PM_EXTEND  = 0x00000800
		bool            m_bRelatePercent;
	private:
		unsigned long           m_dwFields;  //用项位指名那些参数被修改，需要更新对应的界面
	};
}}
