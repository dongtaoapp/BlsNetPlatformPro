#pragma once

#include "..\Common\CommonGlobal.h"

#include "..\SimulatorBase\VirEventIrp.h"
#include "..\SimulatorBase\EventIrp_ClockTime.h"


namespace jysoft { namespace flowEngine 
{
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     �龰�����ӿ���
	�����ˣ�	 hjg
	����ʱ�䣺   2013/11/17
	//-----------------------------------------------------------------------------------------------------------------*/
	class  ISceneActRunOp
	{
	public:
		ISceneActRunOp(void);
		virtual ~ISceneActRunOp(void);
	protected:
		short                         m_sActTime;    //����ʱ�䣨-1��δ���
	public:
		/*******************************************************************************/
		//���ܣ������¼�IRP�����麯��
		//������
		//      CVirEventIrp *pCurrEventIrp��
		//      /*out*/_ScheduleSceneState &eSceneState:    
		//����ֵ:  �����¼��Ƿ�����(TURE:���㣻FALSE:������)
		virtual bool DoHandleEventIrp(irp::CVirEventIrp *pCurrEventIrp, /*out*/_ScheduleSceneState &eSceneState) = 0;
		/*******************************************************************************/
		//���ܣ�����ʱ���¼�IRP����
		//������
		//      CEventIrp_ClockTime *pCurrClockTimeIrp��
		//����ֵ:  �������ٴ���FALSE);
		virtual bool DoHandleClockIrpOp(irp::CEventIrp_ClockTime *pCurrClockTimeIrp, /*out*/_ScheduleSceneState &eSceneState) = 0;
		/*******************************************************************************/
		//���ܣ������龰��Ĵ���״̬
		//������   
		//      BOOL bReactive:     �Ƿ����¼���
		//����ֵ: 
		virtual void DoStateActiveSceneFrame(bool bReactive) = 0;
	public:
		//�����龰���IDֵ
		virtual unsigned short Get_SceneActFrameId() = 0;
	};
}}