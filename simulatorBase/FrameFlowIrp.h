#pragma once
#include ".\simulatorbase_global.h"
#include <pugixml.hpp>

#include "..\Common\VirtualIrp.h"
#include "..\Common\CommonGlobal.h"


/////////////////////////////////////modified hjg/////////////////////////////////////////////////////
namespace jysoft { namespace irp {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ������ı��¼�Irp
	�����ˣ�	 hjg
	����ʱ�䣺   2009/4/8
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORBASESHARED_EXPORT CFrameFlowIrp : public CVirtualIrp
	{
	public:
		CFrameFlowIrp(void);
		virtual ~CFrameFlowIrp(void);
	public:
		virtual _IrpType Get_eIrpType() { return eFrameModify_Event; };
		virtual bool isKindOf(const std::string &strClass);
		/*******************************************************************************/
		// �������ƣ� DoPackageIrp
		// ���ܣ�  ���Irp������
		// ������ 
		// ����ֵ: 
		virtual std::string doPackageIrp();
		/*******************************************************************************/
		// �������ƣ� UnzipPackage
		// ���ܣ� ��ѹ�������Irp������
		// ������ 
		//        char *lpData��
		//        UINT uNumber��
		// ����ֵ:  
        static CFrameFlowIrp * UnzipPackage(char *lpData, unsigned short uNumber);
	public:
		eEventSign                   m_eEvent;
		unsigned short               m_dwFrameId;
		_ScheduleSceneState          m_eSceneAct;             //�龰/�����ݻ��������
	public:
		/*******************************************************************************/
		//���ܣ�����������ı��¼�Irp
		//������
		//      IXMLDOMNode *pFrameNode:
		//      eEventSign eEvent:
		//����ֵ:  
		static CFrameFlowIrp *CreateEventIrp_FrameFlow(pugi::xml_node *pFrameNode, eEventSign eEvent);
		/*******************************************************************************/
		//���ܣ������龰����Irp
		//������
		//      IXMLDOMNode *pSceneActNode:
		//      _ScheduleSceneState eSceneAct:
		//      eEventSign eEvent:
		//����ֵ:  
		static CFrameFlowIrp *CreateEventIrp_SceneActFlow(pugi::xml_node *pSceneActNode, _ScheduleSceneState eSceneAct, eEventSign eEvent);
		/*******************************************************************************/
		//���ܣ������龰����Irp
		//������
		//      DWORD dwFrameId:
		//      _ScheduleSceneState eSceneAct:
		//      eEventSign eEvent:
		//����ֵ:  
		static CFrameFlowIrp *CreateEventIrp_SceneActFlow(unsigned short dwFrameId, _ScheduleSceneState eSceneAct, eEventSign eEvent);
	};

}}
