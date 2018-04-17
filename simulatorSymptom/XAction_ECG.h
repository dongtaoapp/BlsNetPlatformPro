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
	public: //���ຯ������
		virtual bool isKindOf(const std::string &strClassName);
		/*******************************************************************************/
		// �������ƣ� GetActionCaption
		// ���ܣ�   ����������ʶ��
		// ������   
		// ����ֵ: 
		virtual std::string getActionCaption() const;
		/*******************************************************************************/
		// �������ƣ� Parse_ActionFromXml
		// ���ܣ�   ����������������
		// ������   IXMLDOMNode *pXMLShapeNode:
		// ����ֵ: 
		virtual bool Parse_ActionFromXml(pugi::xml_node* pXMLShapeNode);
		/*******************************************************************************/
		// �������ƣ� CombineActionParam
		// ���ܣ�   �����������ò���
		// ������   CXActionVirtual *pDstActionVir:
		// ����ֵ: 
		virtual void CombineActionParam(CXActionVirtual *pDstActionVir);
		/*******************************************************************************/
		// �������ƣ� CloneAction
		// ���ܣ�   ������������
		// ������   
		// ����ֵ: 
		virtual CXActionVirtual * CloneAction();
	public:
		void Set_EcgActionParam( const CECGParams &cEcgParam );
		//���ؾ�������ֵ
		int  GetValue_AbsoluteHR( int nSrcHR );
	protected:
		void SetAction_Ecg(const std::string &strRhythm, const std::string &strHR, const std::string &strExtrasyst, const std::string &strExtrasystRate, int nArtifacts,short sEMD, short sConduct, short sExtendParam);
	public:
		//����QRS
		QRS GetValue_eQRS() { return QRS_A; };
		//����������
		BasicRhythm GetValue_eBasicRhythm();
		//�����粫��
		Extrasys    GetValue_eExtrasys();
		//�����粫����/����
		int         GetValue_ExtrasystRate();
		//������������/����
		int GetValue_HR();
		//���ظ���ѡ��
		Artifact    GetValue_eArtifact();
		//����EMD
		bool   GetValue_EMD();
		//���ش���ֵ
		short  GetValue_Conduct();
		//������չֵ
		short  GetValue_ExtendParam();
		inline unsigned long Get_FieldsFlag() { return m_dwFields; };
		inline void Set_FieldsFlag(unsigned long dwField) { m_dwFields = dwField; };
		inline void Set_bRelatePercent( bool bPercent ) { m_bRelatePercent = bPercent; };
		inline bool Get_bRelatePercent() { return m_bRelatePercent; };
	public:
		int             m_nArtifacts;          //-1:��ûѡ��0��Muscular��1:50/60HZ
		std::string     m_strExtrasystRate;    //�粫������
		std::string     m_strRhythm;
		std::string     m_strExtrasyst;
		std::string     m_strHR;
		int             m_sEMD;
		short           m_sConduct;            //����       PM_CONDUCT = 0x00000200
		short           m_sExtendParam;        //��չ����   PM_EXTEND  = 0x00000800
		bool            m_bRelatePercent;
	private:
		unsigned long           m_dwFields;  //����λָ����Щ�������޸ģ���Ҫ���¶�Ӧ�Ľ���
	};
}}
