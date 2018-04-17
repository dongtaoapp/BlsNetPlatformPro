#pragma once
#include ".\iaclsflowstrategy.h"

#include "..\SimulatorBase\ITransportOrderIrpToSimulator.h"


namespace jysoft { namespace flowEngine 
{
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     �ű������׼���ԣ��Զ�ѡ�����ӵ��¸�������ת�Ʋ���
	�����ˣ�	 hjg
	����ʱ�䣺   2009/3/27
	//-----------------------------------------------------------------------------------------------------------------*/

	class CNormalAclsFlowStrategy : public IAclsFlowStrategy
	{
	public:
		CNormalAclsFlowStrategy(transLayer::ITransportOrderIrpToUp *pTransportUpInterface, pugi::xml_node *pxmlRootElement, IHandleIrpsCollect *pHandleIrpsCollect, IGetPhysiologyActionObj *pGetActionObj);
		virtual ~CNormalAclsFlowStrategy(void);
	public:
		/*******************************************************************************/
		//���ܣ����ݲ��ԣ���������
		//������
		//      IXMLDOMNode *pFrameElement��
		//      eEventSign eEvent:
		//����ֵ:  �������ٴ����¼���FALSE);
		virtual bool OnFlowStrategy(pugi::xml_node *pFrameElement, eEventSign eEvent=ES_Normal);
		//���ݲ���ѡ������ת���������¸�����
		virtual CXLineLinkScenarioObj * SelectNextScenarioFromStrategy();
	protected:
		transLayer::ITransportOrderIrpToUp*  m_pTransportUpInterface;
	};
}}
