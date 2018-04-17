#pragma once
#include <list>
#include ".\XSceneActFrame.h"
#include ".\scriptflowengine_global.h"

#include "..\common\CommonGlobal.h"
#include "..\common\EventHandleClockIrpOp.h"
#include "..\common\EventHandleCustomIrpOp.h"

#include "..\SimulatorBase\ITransportOrderIrpToSimulator.h"

namespace jysoft { namespace flowEngine 
{
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     �龰�򼯺���
	�����ˣ�	 hjg
	����ʱ�䣺   2017/2/16
	//-----------------------------------------------------------------------------------------------------------------*/
    class SCRIPTFLOWENGINESHARED_EXPORT CSceneActsCollect : public irp::CEventHandleCustomIrpOp
											,public irp::CEventHandleClockIrpOp
	{
	public:
		CSceneActsCollect();
		virtual ~CSceneActsCollect(void);
	protected:
		std::list<CXSceneActFrame *>       m_lstSceneActFrames;
		//������龰���б�
		std::list<ISceneActRunOp *>        m_lstActiveSceneActs;
	private:
		transLayer::ITransportOrderIrpToUp *m_pTransOrderIrpToUp;
	public: //��������
		/*******************************************************************************/
		//���ܣ��������¼�IRP����
		//������
		//      CVirtualIrp *pCurrIrp��
		//����ֵ:  �������ٴ���FALSE);
		virtual bool doHandleCustomEventIrpOp(irp::CVirtualIrp *pCurrIrp);
		/*******************************************************************************/
		//���ܣ�����ʱ���¼�IRP����
		//������
		//      CVirtualIrp *pCurrIrp��
		//����ֵ:  �������ٴ���FALSE);
		virtual bool doHandleClockIrpOp(irp::CVirtualIrp *pCurrIrp);
	public:
		/*******************************************************************************/
		//���ܣ�����Ĭ�ϵ��龰��
		//������
		//      const CString &strUnzipCataloguePath����ѹ��Ŀ��·��
		//����ֵ:  
		void LoadDefaultSceneActsFile(const std::string &strUnzipCataloguePath);
		/*******************************************************************************/
		//���ܣ����ؽű��ڶ�����龰��
		//������
		//      pRootElement��
		//      pTransOrderIrpToUp:
		//����ֵ:
		void InitialScriptSceneActs(pugi::xml_node rootElement, IGetPhysiologyActionObj *pGetActionObj, transLayer::ITransportOrderIrpToUp *pTransOrderIrpToUp);
		/*******************************************************************************/
		//���ܣ�����ȫ���龰��
		//������
		//����ֵ: 
		void ActiveSceneActsRun();
		/*******************************************************************************/
		//���ܣ���������龰��
		//������
		//����ֵ: 
		void ClearSceneActs();
	public:
		CXSceneActFrame * SearchSceneActFramePtr(unsigned short dwSignID);
	};
}}
