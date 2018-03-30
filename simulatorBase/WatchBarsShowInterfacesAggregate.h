#pragma once
#include ".\ShowABPUpdateInterface.h"
#include ".\ShowSpO2UpdateInterface.h"
#include ".\ShowECGUpdateInterface.h"
#include ".\ShowEtCO2UpdateInterface.h"
#include ".\ShowRespRateUpdateInterface.h"
#include ".\IHeartStartSign.h"
#include ".\ShowGeneralNoRangeUpdateInterface.h"
#include ".\ShowTempUpdateInterface.h"
#include ".\ShowGeneralUpdateInterface.h"
#include ".\ShowNIBPUpdateInterface.h"

namespace jysoft { namespace simulator {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ģ�������ؼ���ʾ�ӿڼ���
	�����ˣ�	 hjg
	����ʱ�䣺   2016/8/15
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT CWatchBarsShowInterfacesAggregate
	{
	public:
		CWatchBarsShowInterfacesAggregate(void);
		virtual ~CWatchBarsShowInterfacesAggregate(void);
	protected:
		//�ĵ�ͼ��Ϣ��ʾ�ӿڣ������������ơ����ʴ���������������Χ����Ϣ
		base::CShowECGUpdateInterface              *m_pShowHRInterface;
		//Ѫ����Ϣ��ʾ�ӿ�
		base::CShowSpO2UpdateInterface             *m_pShowSpO2ValueInterface;
		//CO2Ũ����Ϣ��ʾ�ӿ�
		base::CShowEtCO2UpdateInterface            *m_pShowEtCO2ValueInterface;
		//�д�Ѫѹ��Ϣ��ʾ�ӿ�
		base::CShowABPUpdateInterface              *m_pShowABPValueInterface;
		//�޴�Ѫѹ��Ϣ��ʾ�ӿ�
		base::CShowNIBPUpdateInterface             *m_pShowNIBPValueInterface;
		//����������Ϣ��ʾ�ӿ�
		base::CShowRespRateUpdateInterface         *m_pShowRRInterface;
		//��Χ���£�ָ�����¡����º�Һ���¶ȣ�
		base::CShowTempUpdateInterface             *m_pShowPTempValueInterface;
		//ģ������塰���֡�����ʾ�����ź�
		IHeartStartSign                     *m_pHeartStartSignInterface;
	public:
		//�����ĵ�ͼ��Ϣ��ʾ�ӿ�
		inline base::CShowECGUpdateInterface * Get_ShowHRUpdateInterfacePtr() { return m_pShowHRInterface; };
		void Set_ShowHRUpdateInterfacePtr(base::CShowECGUpdateInterface *pEcgInterface, bool bRemove = false);
		//����Ѫ����Ϣ��ʾ�ӿ�
		inline base::CShowSpO2UpdateInterface * Get_ShowSpO2ValueUpdateInterfacePtr() { return m_pShowSpO2ValueInterface; };
		void Set_ShowSpO2ValueUpdateInterfacePtr(base::CShowSpO2UpdateInterface *pSpO2Interface, bool bRemove = false);
		//����CO2Ũ����Ϣ��ʾ�ӿ�
		inline base::CShowEtCO2UpdateInterface * Get_ShowEtCO2ValueUpdateInterfacePtr() { return m_pShowEtCO2ValueInterface; };
        void Set_ShowEtCO2ValueUpdateInterfacePtr(base::CShowEtCO2UpdateInterface *pEtCO2Interface, bool bRemove = false);
		//�����д�Ѫѹ��Ϣ��ʾ�ӿ�
		inline base::CShowABPUpdateInterface * Get_ShowABPValueUpdateInterfacePtr() { return m_pShowABPValueInterface; };
		void Set_ShowABPValueUpdateInterfacePtr(base::CShowABPUpdateInterface *pABPInterface, bool bRemove = false);
		//�����޴�Ѫѹ��Ϣ��ʾ�ӿ�
		inline base::CShowNIBPUpdateInterface * Get_ShowNIBPValueUpdateInterfacePtr() { return m_pShowNIBPValueInterface; };
		void Set_ShowNIBPValueUpdateInterfacePtr(base::CShowNIBPUpdateInterface *pNIBPInterface, bool bRemove = false);
		//���غ���������Ϣ��ʾ�ӿ�
		inline base::CShowRespRateUpdateInterface * Get_ShowRespRateUpdateInterfacePtr() { return m_pShowRRInterface; };
		void Set_ShowRespRateUpdateInterfacePtr(base::CShowRespRateUpdateInterface *pRRInterface, bool bRemove = false);
		//ģ������塰���֡�����ʾ�����ź�
		inline IHeartStartSign * Get_HeartStartSignInterface() { return m_pHeartStartSignInterface; };
		void Set_HeartStartSignInterface(IHeartStartSign *pHeartSignInterface, bool bRemove = false);
		//����
		inline base::CShowTempUpdateInterface * Get_ShowPTempValueInterfacePtr(){return m_pShowPTempValueInterface;};
		void Set_ShowPTempValueInterfacePtr(base::CShowTempUpdateInterface *pPTempInterface, bool bRemove = false);
	protected:
		/*******************************************************************************/
		// �������ƣ� InitialWatchBarsShowInterfacesAggregate
		// ���ܣ� ��ȡģ������������е���Ϣ��ʾ�ӿ�
		// ������ 
		// ����ֵ:  
		virtual void InitialWatchBarsShowInterfacesAggregate( ) = 0;

	};

}}
