#pragma once
#include <pugixml.hpp>
#include ".\xscenario.h"
#include ".\XEventVirtual.h"
#include ".\ISceneActRunOp.h"

#include "..\common\CommonGlobal.h"

namespace jysoft { namespace flowEngine 
{
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     �龰�������
	�����ˣ�	 hjg
	����ʱ�䣺   2017/2/16
	//-----------------------------------------------------------------------------------------------------------------*/
	class CXSceneActFrame : public CXScenario
						  , public ISceneActRunOp
	{
	public:
		CXSceneActFrame(unsigned short dwFrameID);
		virtual ~CXSceneActFrame(void);
	protected:
		CXEventVirtual *               m_pActEvent;       //������¼�
		_SceneActHandleType            m_eActHandleType;  //�¼���������ö��
		short                          m_sDurationTime;   //����ʱ�����
		bool                           m_bExitFlow;       //�Ƿ��˳�����
	protected:
		unsigned short                    m_dwFrameID;
	public: //����������
		virtual bool isKindOf(const std::string &strClassName);
		//���ص�ǰ�������õ������б�
		virtual void GetScenarioActions(std::list<simulator::CXActionVirtual *>* plstActions);
	public: //�ӿ�ISceneActRunOp��������
		/*******************************************************************************/
		//���ܣ������¼�IRP�����麯��
		//������
		//      CVirEventIrp *pCurrEventIrp��
		//      /*out*/_ScheduleSceneState &eSceneState:    
		//����ֵ:  �����¼��Ƿ�����(TURE:���㣻FALSE:������)
		virtual bool DoHandleEventIrp(irp::CVirEventIrp *pCurrEventIrp, /*out*/_ScheduleSceneState &eSceneState);
		/*******************************************************************************/
		//���ܣ�����ʱ���¼�IRP����
		//������
		//      CEventIrp_ClockTime *pCurrClockTimeIrp��
		//����ֵ:  �������ٴ���FALSE);
		virtual bool DoHandleClockIrpOp(irp::CEventIrp_ClockTime *pCurrClockTimeIrp, /*out*/_ScheduleSceneState &eSceneState);
		/*******************************************************************************/
		//���ܣ������龰��Ĵ���״̬
		//������   
		//      BOOL bReactive:     �Ƿ����¼���
		//����ֵ: 
		virtual void DoStateActiveSceneFrame(bool bReactive);
		//�����龰���IDֵ
		virtual unsigned short Get_SceneActFrameId() { return m_dwFrameID; };
	public:
		//�����龰������������������Ϣ
		void ParseSceneActFrame(pugi::xml_node *pScenarioNode, IGetPhysiologyActionObj *pGetActionObj);
	protected:
		//���������������������������CXAction_FrameTime�hjg 2014.2.28 add
		virtual void ParseActions(pugi::xml_node *pScenarioNode);
		void LoadActEventFromXML(pugi::xml_node *pXMLActChild, IGetPhysiologyActionObj *pGetActionObj);
	};
}}
