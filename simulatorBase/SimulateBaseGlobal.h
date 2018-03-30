#pragma once
#include <list>
#include ".\simulatorbase_global.h"

#include "..\Common\CommonGlobal.h"

enum _SIMULATECOMMANDTYPE
{
	CT_NONE = 0,
	CT_SIMULATE_LINK,      //ģ��������ָ��
	CT_CPR_DATA,            //CPR����
	CT_CPR_EVENT,          //CPR�¼�
	CT_CARDIOGRAM_DATA,    //�ĵ�ͼ����
	CT_AIRWAY_SET,         //��������
	CT_PACE_SET,           //������
	CT_BLOODPRESS_SET,     //Ѫѹ����
	CT_BREATH_SET,         //��������
	CT_ECGRATE_SET,        //��������
	CT_PUPIL_SET,          //ͫ������
	CT_SPILE_EVENT,        //����¼�
	CT_UNSPILE_EVENT,      //ȡ������¼�
	CT_SCENARIORESET_EVENT,   //�ű������¼�
	CT_CONTROL_EVENT,      //����ָ��
	CT_EVENT               //�¼�
};

//---------------------------------------------------------------------------------------------------
//�ķθ��ղ���ͳ�����ݽṹ
struct  SIMULATORBASESHARED_EXPORT _CPRStatisticCollectStruct
{
	//��ѹ
	int                     m_uPressureRate;
	int                     m_uPressureAverageCount; //ÿ���ӵĴ���
	int                     m_uPressureAverageDepth; //ƽ�����
	int                     m_uPressureRightNum;  //��ȷ����
	int                     m_uPressureErrSumNum;
	int                     m_uPressureOverNum;   //����
	int                     m_uPressureLackNum;   //����
	int                     m_uPressureIncompleteNum;    //��ѹʱ����ȫ�ͷ�
	int                     m_uPressurePositionErrorNum; //��ѹλ���ܴ���
	int                     m_uPressureOtherNum;   //����
	//����
	int                     m_uBreathAverageVol;            //ƽ��������[ml]
	int                     m_uBreathAverageVolInMinute;    //ÿ1���ӵĴ�����[ml]
	int                     m_uBreathAverageCountInMinute;  //ÿ���ӵĴ���
	int                     m_uBreathRightNum; //��ȷ����
	int                     m_uBreathErrSumNum;
	int                     m_uBreathOverNum;  //����
	int                     m_uBreathLackNum;  //����
	int                     m_uBreathStomachNum; //��θ
	int                     m_uBreathPipeCloseNum;//�����ر�
	int                     m_uBreathOtherNum; //����
public:
	_CPRStatisticCollectStruct();
};
