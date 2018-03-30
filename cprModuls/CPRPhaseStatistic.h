#pragma once
#include <list>
#include ".\Collates.h"
#include ".\CPRCommonGlobal.h"

#include "..\Common\CommonGlobal.h"
#include "..\Common\LoopBuffer.h"

#include "..\SimulatorBase\OpLogInterface.h"
#include "..\SimulatorBase\ShowCPRActUpdateInterface.h"

#include <boost/date_time/posix_time/posix_time.hpp>


using namespace boost::posix_time;
namespace jysoft{  namespace cpr {
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     CPR�׶��Բ���ͳ�ƽӿ���
	�����ˣ�	 hjg
	����ʱ�䣺   2017/4/9
	//-----------------------------------------------------------------------------------------------------------------*/
	class ICPRPhaseStatistic
	{
	public:
		ICPRPhaseStatistic(void);
		virtual ~ICPRPhaseStatistic(void);
	protected:
		std::list<_StatDataSeg *>       phaseStatSegs;
	protected:
		int                             delayTime;
		//���100����Ĵ���ʱ��
		UINT                            transEvent;
		UINT                            buffTimeEvent;//����ʱ��
		utility::CLoopBuffer<_CPRData>  loopBuff;
	protected:
		//��־�¼��ӿ�
		log::COpLogInterface*          m_pEventLogInterface;  
		CShowCPRActUpdateInterface*    actCPRDetailShowInterface;
	public:
		/*******************************************************************************/
		// �������ƣ� intervalTicktimeHandle
		// ���ܣ� ���100����ʱ�䴦����
		// ������ 
		//        
		// ����ֵ:  
		virtual void intervalTicktimeHandle(const CPressureCollate *pPressureColl, const CBreathCollate *pBreathColl) = 0;
		/*******************************************************************************/
		// �������ƣ� increaseSecondTickNotify
		// ���ܣ� ÿһ��ʱ���¼�֪ͨ
		// ������ 
		//        scriptRunTime:   ��������ʱ��
		// ����ֵ:
		virtual void increaseSecondTickNotify(const time_duration &scriptRunTime) = 0;
		/*******************************************************************************/
		// �������ƣ� cprPhaseStatisticHandle
		// ���ܣ� CPR�׶��Բ���ͳ�ƴ����� 
		// ������ 
		//       cprData:
		// ����ֵ:  
        virtual void cprPhaseStatisticHandle(const _CPRData &cprData, _eCPRErrorSign  eErrorSign, short uLackNum, _eCPRErrorSign ePractiseExtendSign, _CPRManageState eState) = 0;
	public:
		//��������
		virtual void resetPhaseStatistic();
		//������ʾ�ӿ�
		void setShowCPRDetailActInterfacePtr(CShowCPRActUpdateInterface *pInterface);
		//������־�ӿ�
		void setLogInterfacePtr(log::COpLogInterface *pLogInterface) { m_pEventLogInterface = pLogInterface; };
	};

	//��ѹ�׶���
	class CPressurePhaseStatistic : public ICPRPhaseStatistic
	{
	public:
		CPressurePhaseStatistic();
		virtual ~CPressurePhaseStatistic();
	public:
		//�ж�ʱ�䣨��λ���룩
		time_duration  interruptTime;
	protected:
		//��ǰ��ѹ�׶ε�ͳ��
		_StatPressueSeg   currentSegStat;
		//�ж��ۻ�ʱ�䣨��λ���룩
		int     accumInterruptTime;
	public:
		/*******************************************************************************/
		// �������ƣ� cprPressureRealTimeDataHandle
		// ���ܣ� CPR�������ݴ����� 
		// ������ 
		// ����ֵ:  
		void cprPressureRealTimeDataHandle(const _CPRData *lptrCPRDatas, int nLength, const CPressureCollate *pPressureColl);
		/*******************************************************************************/
		// �������ƣ� intervalTicktimeHandle
		// ���ܣ� ���100����ʱ�䴦����
		// ������ 
		//        
		// ����ֵ:  
		virtual void intervalTicktimeHandle(const CPressureCollate *pPressureColl, const CBreathCollate *pBreathColl);
		/*******************************************************************************/
		// �������ƣ� increaseSecondTickNotify
		// ���ܣ� ÿһ��ʱ���¼�֪ͨ
		// ������ 
		//        scriptRunTime:   ��������ʱ��
		// ����ֵ:
		virtual void increaseSecondTickNotify(const time_duration &scriptRunTime);
		/*******************************************************************************/
		// �������ƣ� cprPhaseStatisticHandle
		// ���ܣ� CPR�׶��Բ���ͳ�ƴ����� 
		// ������ 
		//       cprData:
		// ����ֵ:  
        virtual void cprPhaseStatisticHandle(const _CPRData &cprData, _eCPRErrorSign  eErrorSign, short uLackNum, _eCPRErrorSign ePractiseExtendSign, _CPRManageState eState);
	protected:
		/*******************************************************************************/
		// �������ƣ� OnCPRRealTimePhaseStatisticHandle
		// ���ܣ� CPR�׶��Բ���ͳ�ƴ����� 
		// ������ 
		//       _CPRData cCPRData:
		// ����ֵ:  
		void cprRealTimePhaseStatisticHandle(const _CPRData &cCPRData, const CPressureCollate *pPressureColl);
	private:
		void logPressurePhaseStatistic(const _StatPressueSeg *pPressureSeg, log::COpLogInterface* pLogInterface);
	public:
		//��������
		virtual void resetPhaseStatistic();
	public:
		short  getPressureSumNum();  //��ѹ�ܴ���
		short  getPressureSumRightNum(); //��ѹ��ȷ����
		short  getPressureSumErrorsNum(); //��ѹ�������
		short  getPressureSumIncomplete(); //��ѹ�ͷŲ�������
		short  getPressurePosErrorNum(short *pos_low = NULL, short *pos_high = NULL, short *pos_left = NULL, short *pos_Right = NULL); //��ѹλ�ô������
		short  getPressureOverNum();  //��ѹ����
		short  getPressureLackNum();  //��ѹ��С
		//��ѹ�����ȷ
		short  getPressureDepthRightNum();
		//����ƽ����ѹ���
		short  getAverageDepth();
		//����ƽ��Ƶ��
		short  getAverageRate();
	};

	//�����׶���
	class CBreathPhaseStatistic : public ICPRPhaseStatistic
	{
	public:
		CBreathPhaseStatistic();
		virtual ~CBreathPhaseStatistic();
	protected:
		//��ǰ�����׶ε�ͳ��
		_StatBreathSeg     currentSegStat;
	public:
		/*******************************************************************************/
		// �������ƣ� cprBreathRealTimeDataHandle
		// ���ܣ� �����������ݴ����� 
		// ������ 
		// ����ֵ:  
		void cprBreathRealTimeDataHandle(const _CPRData *lptrCPRDatas, int nLength, const CBreathCollate *pBreathColl);
		/*******************************************************************************/
		// �������ƣ� intervalTicktimeHandle
		// ���ܣ� ���100����ʱ�䴦����
		// ������ 
		//        
		// ����ֵ:  
		virtual void intervalTicktimeHandle(const CPressureCollate *pPressureColl, const CBreathCollate *pBreathColl);
		/*******************************************************************************/
		// �������ƣ� increaseSecondTickNotify
		// ���ܣ� ÿһ��ʱ���¼�֪ͨ
		// ������ 
		//        scriptRunTime:   ��������ʱ��
		// ����ֵ:
		virtual void increaseSecondTickNotify(const time_duration &scriptRunTime);
		/*******************************************************************************/
		// �������ƣ� cprPhaseStatisticHandle
		// ���ܣ� CPR�׶��Բ���ͳ�ƴ����� 
		// ������ 
		//       cprData:
		// ����ֵ:  
        virtual void cprPhaseStatisticHandle(const _CPRData &cprData, _eCPRErrorSign  eErrorSign, short uLackNum, _eCPRErrorSign ePractiseExtendSign, _CPRManageState eState);
	protected:
		/*******************************************************************************/
		// �������ƣ� OnCPRRealTimePhaseStatisticHandle
		// ���ܣ� CPR�׶��Բ���ͳ�ƴ����� 
		// ������ 
		//        _CPRData cCPRData:
		// ����ֵ:  
		virtual void cprRealTimePhaseStatisticHandle(const _CPRData &cCPRData, const CBreathCollate *pBreathColl);
	private:
		//ͳ�ƴ����׶��Բ���������
		void logBreathPhaseStatistic(const _StatBreathSeg *pBreathSeg,  log::COpLogInterface* pLogInterface);
	public:
		//��������
		virtual void resetPhaseStatistic();
	public:
		short  getBreathSumNum();  //�����ܴ���
		short  getBreathSumRightNum(); //������ȷ����
		short  getBreathSumErrorsNum(); //�����������
		short  getBreathOverNum();
		short  getBreathLackNum();
		short  getBreathInStomachNum();
		short  getBreathPipeCloseNum();
		//ͨ��ʱ�����
		short  getVentiOverTimeNum();
		//ͨ��ʱ�����
		short  getVentiLowerTimeNum();
		//����ƽ��������
		short  getAverageVolume();
	};
}}
