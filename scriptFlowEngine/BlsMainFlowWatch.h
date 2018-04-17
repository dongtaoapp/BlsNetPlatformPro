#pragma once
#include ".\blsmainflowvirtual.h"


namespace jysoft { namespace flowEngine 
{
	class CBlsMainFlowWatch : public CBlsMainFlowVirtual
	{
	public:
		CBlsMainFlowWatch(CBlsSimulateCase  *pSimulateCase, transLayer::CFormatTransport* pTransport);
		virtual ~CBlsMainFlowWatch(void);
	public: //��������
		/*******************************************************************************/
		// �������ƣ� CreateScenario
		// ���ܣ� ���ݳ����ű��ļ�����ʼ��ACLS���̴�������
		// ������ 
		//       pugi::xml_node *pRootElement: 
		// ����ֵ:  
		virtual pugi::xml_node  CreateScenario( pugi::xml_node rootElement );
	protected: //��������
		/*******************************************************************************/
		// �������ƣ� ExecInitialFramework
		// ���ܣ� ��ʼ��ִ�е�ǰ�Ľ���Actions
		// ������ 
		//   
		// ����ֵ:  
		virtual void ExecInitialFramework(SimulatePatientType ePatientType);
	};
}}
