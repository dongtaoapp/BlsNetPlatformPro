#pragma once
#include ".\simulatorbase_global.h"

#include <boost/optional.hpp>
#include "..\Common\CommonGlobal.h"
#include "..\Common\IUpdateShowVir.h"


namespace jysoft{  namespace cpr {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     CPR����ͳ����ʾ�ӿ���ʾ�ӿ�
	�����ˣ�	 hjg
	����ʱ�䣺   2017/2/25
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT CShowCPRStatisticUpdateInterface : public IUpdateShowVir
	{
	public:
		CShowCPRStatisticUpdateInterface(void);
		virtual ~CShowCPRStatisticUpdateInterface(void);
	public:
		virtual bool isKindOf(const std::string &className);
	public://�ӿں�������
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	protected:
		//�Խ���ʾ��֪ͨ
		virtual void doLinkCPRStatisticUpdateShow() { };
		//�Ͽ���ʾ��֪ͨ
		virtual void cutLinkCPRStatisticUpdateShow() { };
		//����ͳ��
		virtual void ResetCPRStatistic(_CPRManageState  eState) = 0;
		//����ͳ�ƴ���
		virtual void UpdateCPRStatistic(boost::optional<int> calcGradePec, int nPressureSumNum, int nPressureRightNum, int nBreathSumNum, int nBreathRightNum) = 0;
		//����ʱ�䡢��ѹ�ж�ʱ��֪ͨ����ѹʱ��ռ��
		virtual void UpdateCPRTimeStatic(int cprPeriodTime, boost::optional<int> interruptTime,  boost::optional<int> pressureTimePercent) = 0;
		//ѭ��ͳ�ƣ���ѹ:������ѭ������
		virtual void UpdateCPRCycle(int pressureNum, int breathNum, boost::optional<int> cycleNum) = 0;
		//��ѹλ��ͳ��(������θ)��
		virtual void UpdatePositionStatic(short pos_low, short pos_high, short pos_left, short pos_Right) = 0;
		//��θͳ��
		virtual void UpdateInStomachNumber( short sInStomachNum) = 0;
		//��ѹͳ�ƣ���ȷ�ٷֱȡ��ж�ʱ�䡢ƽ����ȡ�ƽ��Ƶ�ʡ�λ����ȷ�ٷֱȡ��ͷ���ȷ�ٷֱȡ���ѹ���󡢰�ѹ��С
		virtual void UpdatePressureStatic(int calcGradePec, int interruptTime, int nAvergeDepth, int nAvergeRate, int sumNum, int posRightPec, int releasRightPec, int depthOverNum, int depthLowerNum) = 0;
		//����ͳ�ƣ���ȷ�ٷֱȡ�ƽ����������ƽ������Ƶ�ʡ��ܴ����������󡢹�С��ͨ���೤��ͨ�����
		virtual void UpdateBreathStatic(int calGradePec, int nAvergeVolume, int nAvergeRate, int sumNum, int volumeOverNum, int volumeLowerNum, int ventiOverTimeNum, int ventiLowerTimeNum) = 0;
	public:
		//����ͳ��
		virtual void OnResetCPRStatistic(_CPRManageState  eState);
		//����ͳ�ƴ���
		void OnUpdateStatistic(boost::optional<int> calcGradePec, int nPressureSumNum, int nPressureRightNum, int nBreathSumNum, int nBreathRightNum);
		//����ʱ�䡢��ѹ�ж�ʱ��֪ͨ����ѹʱ��ռ��
		virtual void OnUpdateCPRTimeStatic(int cprPeriodTime, boost::optional<int> interruptTime,  boost::optional<int> pressureTimePercent);
		//ѭ��ͳ�ƣ���ѹ:������ѭ������
		virtual void OnUpdateCPRCycle(int pressureNum, int breathNum, boost::optional<int> cycleNum);
		//��ѹλ��ͳ��
		virtual void OnUpdatePositionStatic(short pos_low, short pos_high, short pos_left, short pos_Right);
		//��θͳ��
		virtual void OnUpdateInStomachNumber( short sInStomachNum);
		//��ѹͳ�ƣ���ȷ�ٷֱȡ��ж�ʱ�䡢ƽ����ȡ�ƽ��Ƶ�ʡ�λ����ȷ�ٷֱȡ��ͷ���ȷ�ٷֱȡ���ѹ���󡢰�ѹ��С
		virtual void OnUpdatePressureStatic(int calcGradePec, int interruptTime, int nAvergeDepth, int nAvergeRate, int sumNum, int posRightPec, int releasRightPec, int depthOverNum, int depthLowerNum);
		//����ͳ�ƣ���ȷ�ٷֱȡ�ƽ����������ƽ������Ƶ�ʡ��ܴ����������󡢹�С��ͨ���೤��ͨ�����
		virtual void OnUpdateBreathStatic(int calGradePec, int nAvergeVolume, int nAvergeRate, int sumNum, int volumeOverNum, int volumeLowerNum, int ventiOverTimeNum, int ventiLowerTimeNum);
	};

}}
