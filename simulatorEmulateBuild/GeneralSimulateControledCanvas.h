#pragma once
#include "..\common\criticalmutex.h"

#include "..\SimulatorBase\IPaneMoveControlInterface.h"


namespace jysoft { namespace simulator {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     �ܿ�ʵʱ���ݷַ���
	�����ˣ�	 hjg
	����ʱ�䣺   2008/8/19
	//-----------------------------------------------------------------------------------------------------------------*/

	class IGetPhysioloySimulateData;
	class IDistributeSimulateData;
	class CGeneralSimulateControledCanvas : public utility::IPaneMoveControlInterface
	{
	public:
		CGeneralSimulateControledCanvas(void);
		virtual ~CGeneralSimulateControledCanvas(void);
	protected:
		float                          m_fTempBuffer[100];    //��ʱ���ݶ�ȡ����
		IGetPhysioloySimulateData      *m_pGetSimulateData;   //�ĵ�ͼ���ݻ�ȡ�ӿ�
		IDistributeSimulateData        *m_pDistributeData;    //�ĵ�ͼ�����ɷ��ӿ�
	private:
		utility::CCriticalMutex        m_cMutex;
		int                            m_iMilliTime;      //��λ��0.1ms
		BOOL                           m_bStartDistribute;
	public:
		void InitialSimulate(IGetPhysioloySimulateData *pGetSimulateData, int iMilliTime = 400);
	protected:
		//�ƶ��컬������
		virtual void PaneMoveOp();
		// ��ʼ���ĵ�ͼ
		virtual void Start(bool bClear);
	public:
		//��ʼ����ʱʵ����
		void OnStartWatchPhyst(IDistributeSimulateData *pDistributeData);
		//�Ͽ���ʱʵ�ļ��
		void OnCutWatchPhyst(IDistributeSimulateData *pCutDistributeData);
	};
}}