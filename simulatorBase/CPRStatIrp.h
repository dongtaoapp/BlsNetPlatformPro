#pragma once
#include ".\simulatorbase_global.h"
#include ".\VirEventIrp.h"


namespace jysoft { namespace irp {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     CPR����״̬�¼�Irp
	�����ˣ�	 hjg
	����ʱ�䣺   2017/2/8
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORBASESHARED_EXPORT CCPRStatIrp : public CVirEventIrp
	{
	public:
		CCPRStatIrp(void);
		virtual ~CCPRStatIrp(void);
	public:
		virtual _IrpType Get_eIrpType() { return eCPR_Stat; };
		virtual bool isKindOf(const std::string &strClass);
		//�����¼���־
		virtual eEventSign Get_EventSign() { return ES_CPREvent; };
		/*******************************************************************************/
		// �������ƣ� doPackageIrp
		// ���ܣ�  ���Irp������
		// ������ 
		// ����ֵ: 
		virtual std::string doPackageIrp();
		/*******************************************************************************/
		// �������ƣ� UpdateEventSignShow
		// ���ܣ�  ��ʾ�¼�����
		// ������ 
		// ����ֵ: 
		virtual void UpdateEventSignShow(simulator::base::CShowEventSignUpdateInterface  *pInterface );
	public:
		/*******************************************************************************/
		// �������ƣ� CreateEvent_CPRIrp
		// ���ܣ� ����CPR�¼�Irp��
		// ������ 
		//       _CPRManageState eCPRMode: CPRģʽ
		//       int nStat:               ״̬
		// ����ֵ:  
		static CCPRStatIrp * CreateEvent_CPRIrp(_CPRManageState eCPRMode, int nStat);
		/*******************************************************************************/
		// �������ƣ� UnzipPackage
		// ���ܣ� ��ѹ�������Irp������
		// ������ 
		//        char *lpData��
		//        UINT uNumber��
		// ����ֵ:  
        static CCPRStatIrp * UnzipPackage(char *lpData, unsigned short uNumber);
	public:
		inline void Set_eCPRMode(_CPRManageState  eState) { m_eCPRMode = eState; };
		inline void Set_OperatorStat(int nStat) { m_nStat = nStat; };
		inline _CPRManageState Get_eCPRMode() { return m_eCPRMode; };
		inline int GetValue_Stat() { return m_nStat; };
	protected:
		_CPRManageState    m_eCPRMode;        //CPR����ģʽ
		//------------------------------------------------------------------------
		//0:    CPR��������
		//1:    CPR������ʼ
		//2:    �ڱ�׼ģʽ��ʵսģʽ�£����5��ѭ����CPR����
		int                m_nStat;          
	};

}}
