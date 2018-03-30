#pragma once
#include ".\LayerGlobal.h"

#include "..\common\CommonGlobal.h"
#include "..\common\LoopBuffer.h"

#include "..\simulatorBase\SimulatorOrderIrp.h"
#include "..\simulatorBase\EventIrp_SimulateTrigger.h"


namespace jysoft { namespace transLayer 
{
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ģ���˴����¼���ʶ�ӿ���
	�����ˣ�	 hjg
	����ʱ�䣺   2017/5/4
	//-----------------------------------------------------------------------------------------------------------------*/
	class ISimulateTriggerJudge
	{
	public:
		ISimulateTriggerJudge(void);
		virtual ~ISimulateTriggerJudge(void);
	public:
		/*******************************************************************************/
		// �������ƣ� createEvent_SimulateTriggerIrp
		// ���ܣ� ����ģ���˴����¼�Irp
		// ������ 
		//        _VirDataStruct *pDataStruct: 
		// ����ֵ:  
		virtual irp::CEventIrp_SimulateTrigger * createEvent_SimulateTriggerIrp(_VirDataStruct *pDataStruct) = 0;
		/*******************************************************************************/
		// �������ƣ� judgeRealTimeDataType
		// ���ܣ�  �ж��Ƿ�ΪCPRʵʱ��������
		// ������ 
		// ����ֵ: 
		virtual bool judgeRealTimeDataType(_VirDataStruct *pDataStruct, /*out*/_CPRData *lptrCPRData) = 0;
	protected:
		//�����ױ�־
		virtual bool searchBeginSegmentFlag();
		//����β��־, �����������;-1��ʾû�ҵ�
		virtual int  searchEndSegmentFlag();
	public:
		//���ܴӴ����յ�������
		_VirDataStruct * getDataStructFromCommData(void);
		void writeCommunicateData(void *lpData, UINT uNumber);
	protected:
		utility::CLoopBuffer<unsigned char>      m_cDataTmpBuffer;
	};

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ģ���˴����¼���ʶ��(2.0�汾��Ӳ���豸ͨѶ��ʽ)
	�����ˣ�	 hjg
	����ʱ�䣺   2011/5/5
	//-----------------------------------------------------------------------------------------------------------------*/
    class TRANSLAYERSHARED_EXPORT CBlsTriggerJudgeVersion : public ISimulateTriggerJudge
	{
	public:
		CBlsTriggerJudgeVersion();
		virtual ~CBlsTriggerJudgeVersion();
	public:
		/*******************************************************************************/
		// �������ƣ� createEvent_SimulateTriggerIrp
		// ���ܣ� ����ģ���˴����¼�Irp
		// ������ 
		//        _VirDataStruct *pDataStruct: 
		// ����ֵ:  
		virtual irp::CEventIrp_SimulateTrigger * createEvent_SimulateTriggerIrp(_VirDataStruct *pDataStruct);
		/*******************************************************************************/
		// �������ƣ� judgeRealTimeDataType
		// ���ܣ�  �ж��Ƿ�ΪCPRʵʱ��������
		// ������ 
		// ����ֵ: 
		virtual bool judgeRealTimeDataType(_VirDataStruct *pDataStruct, /*out*/_CPRData *lptrCPRData);
	};
}}
