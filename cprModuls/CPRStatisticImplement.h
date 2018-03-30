#pragma once
#include <boost/optional.hpp>
#include <boost/logic/tribool.hpp>
#include ".\Collates.h"
#include ".\CPRConfigue.h"
#include ".\CPRCommonGlobal.h"
#include ".\CPRPhaseStatistic.h"

#include "..\SimulatorBase\OpLogInterface.h"
#include "..\SimulatorBase\CPRShowInterfacesAggregate.h"


namespace jysoft{  namespace cpr {
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     CPRͳ��ʵʩ��
	�����ˣ�	 hjg
	����ʱ�䣺   2017/5/21
	//-----------------------------------------------------------------------------------------------------------------*/
    class CPRMODULSSHARED_EXPORT CCPRStatisticImplement
	{
	public:
		CCPRStatisticImplement(CPressureCollate *pPressureCollate, CBreathCollate *pBreathCollate);
		virtual ~CCPRStatisticImplement(void);
	public:
		CPressurePhaseStatistic    pressurePhaseStat;  //��ѹ�׶��Բ���ͳ����
		CBreathPhaseStatistic      breathPhaseStat;    //�����׶��Բ���ͳ����
	public:
		HANDLE                                    m_hRun;    //����
		HANDLE                                    m_hPause;  //��ͣ
		HANDLE                                    m_hThrdOut;  //�߳��˳�
		HANDLE                                    m_hThrdFinish;//�߳̽���
	protected:
		bool                                      bCPROperatoring;       //CPR�����Ƿ������б�ʶ
		CPressureCollate*                         pressureCollate;
		CBreathCollate*                           breathCollate;
		CShowCPRStatisticUpdateInterface*         cprStatisticShowInterface;
		//--------------------------------------------------------------------------------------------------
		//CPRͳ�ƴ�������״̬
		//true: ��������; false: ����������; freezed: ����״̬
		boost::tribool                 cprResetStating;
		boost::optional<int>           cycleNum;
		//�������ڵİ�ѹ����������
		int      pressurePeriodNum;
		int      breathPeriodNum;
		//CPRѭ����ʱ������ʶʱ���
		time_duration                  cprCycleInitiateTime;
		//�ۼ�ʱ��(�룩
		time_duration                  accumulateSec;
		//-------------------------------------------------------------------------------------------------
		//CPR�ܼ�Чֵ%����ѹ��Чֵ%��������Чֵ%
		boost::optional<int>     cprGradePec;
		boost::optional<int>     interruptTime;
	public: 
		/*******************************************************************************/
		// �������ƣ� initialCPRStaticImpl
		// ���ܣ� ��ʼ�����ݣ�����ʱ���¼��߳�
		// ������   
		// ����ֵ:  
		void initialCPRStaticImpl(void);
		/*******************************************************************************/
		// �������ƣ� acceptAndStatisticImp
		// ���ܣ� ͨ�����յ��ķ�����ֵ�ж�CPR��������ȷ�Լ�����ԭ��
		// ������ DWORD  dwData: ��ѹ/�����ķ���ֵ
		// ����ֵ:  CPR����״̬��ʾ
		void acceptAndStatisticImp(const _CPRData &cprData, _eCPRErrorSign  eErrorSign, UINT uLackNum, _eCPRErrorSign ePractiseExtendSign, boost::optional<int> cycleNewNum, _CPRManageState eState, CCPRConfigue* pCPRConfigue);
		//��������
		void resetStatisticImpl(bool bUpdateStatistics = false);
		//�������¿�ʼͳ��
		void allowRestatisticImpl(const time_duration &scriptRunTime);
		//����ʱ��
		void freezedStatisticImpl();
		//����100����ʱ���¼�����
		void increaseMillisecTimeTick();
		//ʱ���¼�������λ��1�룩
		void doHandleSecondClockTick();
		//CPR��ʼ����
		void CPRStartHandle();
		//CPR��������
		void CPRStopHandle();
		/*******************************************************************************/
		// �������ƣ� StartLinkCPRShowInterfaces
		// ���ܣ� ��ʼ����CPR��ʾ�������ʾ�ӿ�
		// ������ CCPRShowInterfacesAggregate *pShowAggregate:        
		// ����ֵ:  
		void startLinkCPRShowInterfaces(CCPRShowInterfacesAggregate *pShowAggregate);
		/*******************************************************************************/
		// �������ƣ� UnLinkCPRShowInterfaces
		// ���ܣ� �Ͽ�CPR��ʾ�������ʾ�ӿ�
		// ������ CCPRShowInterfacesAggregate *pShowAggregate:        
		// ����ֵ:
		void unLinkCPRShowInterfaces(CCPRShowInterfacesAggregate *pShowAggregate);
		//���ý׶�CPRͳ����־�ӿ�
		void setPhaseCPRLogInterfacePtr(log::COpLogInterface *pLogInterface);
	protected:
		/*******************************************************************************/
		// �������ƣ� StatisticOtherCPRValues
		// ���ܣ� ͳ������������(ƽ�����ʡ�ƽ�����)
		// ������ DWORD  dwData:        ��ѹ/�����ķ���ֵ
		//        _eCPRErrorSign eSign: CPR����״̬��ʾ
		// ����ֵ:  
		void statisticOtherCPRValues(const _CPRData &cprData, _eCPRErrorSign eSign);
		//���㲢ͬ������ͳ����ֵ
		//bScopeJudge�� true:��ѹ���ȣ�false:�������ȣ� unknown:����ָ��
		void calcAndUpdateStatisticValues(CShowCPRStatisticUpdateInterface *pShowInterface, boost::tribool bScopeJudge);
	public:
		void loadCPRData(const _CPRData *lptrCPRData, int nLength);
		inline bool isCPROperatoring() { return bCPROperatoring; };
		inline boost::optional<int> getCPRCycleNum() { return cycleNum; };
	protected:
		//���㲢�����ܷ�ֵ(%)
		boost::optional<int>  calcCPRGradePecent(_CPRManageState eState, CCPRConfigue* pCPRConfigue);
		//���㲢���ذ�ѹ��ֵ(%)
		boost::optional<int>  calcPressureGradePecent();
		//���㲢���ش�����ֵ(%)
		boost::optional<int>  calcBreathGradePecent();
		//���㲢���ذ�ѹ�ͷ���ȷ��ֵ(%)
		boost::optional<int>  calcPressureReleaseGradePecent();
		//���㲢���ذ�ѹλ����ȷ��ֵ(%)
		boost::optional<int>  calcPressurePosGradePecent();
		//������ȷ��ѹ��Χ�ٷֱ�
		boost::optional<int>  calcPressureDepthRightPecent();
		//����ѭ��ͳ�ƣ���ѹ:������ѭ������
		void calcCPRCycleStatistic(const _CPRData &cprData, boost::optional<int> cycleNewNum);
	public:
		int GetPressureRate();
		//ƽ����ѹ����
		int GetPressureAverageCount(int nOpSumSecond);
		int GetPressureAverageDepth();
		int GetPressureSumRightNum();
		int GetPressureSumIncomplete();
		int GetPressureSumErrorsNum();
		int GetPressureOverNum();
		int GetPressureLackNum();
		int GetPressurePosErrorNum();
		//����
		int GetBreathAverageVol();
		int GetBreathAverageVolInMinute(int nOpSumSecond);
		int GetBreathAverageCountInMinute(int nOpSumSecond);
		int GetBreathSumRightNum();
		int GetBreathSumErrorsNum();
		int GetBreathOverNum();
		int GetBreathLackNum();
		int GetBreathInStomachNum();
		int GetBreathPipeCloseNum();
		int GetBreathOthersNum();
	public:
		static UINT ThrdCPRMicroSecondTimeFunc(LPVOID lpVoid);
	};
}}
