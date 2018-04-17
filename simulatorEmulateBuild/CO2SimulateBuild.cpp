#include ".\co2simulatebuild.h"
#include ".\CO2SimulateIntubateState.h"

#include "..\SimulatorBase\ShowEtCO2UpdateInterface.h"


namespace jysoft { namespace simulator { namespace etCO2 {

	CCO2SimulateBuild::CCO2SimulateBuild(void)
	{
		//����EtCO2���Ӽ��
		m_bClearWatchLink  = true;
		m_bLinkWatchEtCO2  = false;

		m_nReflushCalculate  = 0;

		m_pIntubateState   = new CCO2SimulateIntubateState( );
		m_pCurrCO2SimulateState = NULL;
		m_pNextCO2SimulateState = NULL;
	}

	CCO2SimulateBuild::~CCO2SimulateBuild(void)
	{
		if( m_pIntubateState != NULL )
		{
			delete m_pIntubateState;
		}
		m_pIntubateState  = NULL;
	}

	/*********************************************************************************/
	//���ܣ���ʼ��ģ��CO2������
	//������
	//      int nCO2Per:             CO2%
	//����ֵ:  
	void CCO2SimulateBuild::InitializeBuild(int nCO2Per)
	{
		m_pCurrCO2SimulateState = NULL;
		m_pNextCO2SimulateState = NULL;
		//��ʼ�����״̬
		m_pIntubateState->InitialStartTimeThread( this );
		m_cAutoRespState.Set_EtCO2SimulateBuildPtr( this );
		//---------------------------------------------------------------------------------------------------
		if( nCO2Per > 70 )
		{
			nCO2Per = 70;
		}
		m_cAutoRespState.SetCO2PerValue( nCO2Per );
		m_cCO2CycleData.InitialCO2CycleData( m_strCO2ResourePath, nCO2Per );
	}

	//�޸�CO2%
	void CCO2SimulateBuild::ModifyCO2PercentValue( int nCO2Per )
	{
		if( nCO2Per > 70 )
		{
			nCO2Per = 70;
		}
		m_cAutoRespState.SetCO2PerValue( nCO2Per );
		//�������ܲ��ʱ��etCO2ֵ
		if( m_pCurrCO2SimulateState == m_pIntubateState || m_pNextCO2SimulateState == m_pIntubateState )
		{
			m_pIntubateState->SetCO2PerValue( nCO2Per );
		}
		nCO2Per   = -1;  //δָ��
		{
			boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
			if( m_pCurrCO2SimulateState != NULL )
			{
				nCO2Per  = m_pCurrCO2SimulateState->GetCO2PerValue();
			}
		}
		
		if( nCO2Per != -1 )
		{
			m_cCO2CycleData.ModifyCO2PerValue( nCO2Per );
		}
	}
	/*******************************************************************************/
	//���ܣ���ȡ���������ڵ���������
	//������int iMilliTime:          ʱ�䣨0.1���룩
	//      float *pcBuffer:         ���ص���������
	//����ֵ:  �������ݵĳ���
	unsigned long CCO2SimulateBuild::GetPhysioloySimulateData(int iMilliTime, /*out*/float *pcBuffer /*= NULL*/)
	{
		if( pcBuffer != NULL )
		{
			m_nReflushCalculate += iMilliTime;
			if( m_nReflushCalculate >= 0 )
			{
				//��ʾEtCO2����ֵ
				boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
				if( m_pShowEtCO2Update && m_pCurrCO2SimulateState)
				{
					int  nEtCO2Value = m_pCurrCO2SimulateState->GetCO2PerValue();
					m_pShowEtCO2Update->OnShowEtCO2Value( nEtCO2Value );
				}
				m_nReflushCalculate  = -100000;
			}
		}
		return m_cCO2CycleData.GetPhysioloySimulateData(iMilliTime, m_pCurrCO2SimulateState, pcBuffer);
	}

	/*******************************************************************************/
	// �������ƣ� OnCO2SimulateSignOp
	// ���ܣ� ����ʱ��������CO2��ģ���źŴ���
	// ������  BOOL bInspiration: ����(TRUE); ����(FALSE)
	//         int nMilliChangeTime: CO2������������ʱ�䣨0.1���룩
	//         int nMilliOtherTime:  �������������������ʱ�䣨0.1���룩
	// ����ֵ:  
	void CCO2SimulateBuild::OnCO2SimulateSignOp(bool bInspiration, int nMilliChangeTime, int nMilliOtherTime)
	{
		m_cCO2CycleData.CO2SimulateSignOp(bInspiration, nMilliChangeTime, nMilliOtherTime);
		//��ʾEtCO2��ֵ
		boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
		if( bInspiration == TRUE )
		{
			m_nReflushCalculate  = -(nMilliChangeTime+nMilliOtherTime);
		}
		if( m_pShowEtCO2Update && m_pCurrCO2SimulateState)
		{
			int  nEtCO2Value = m_pCurrCO2SimulateState->GetCO2PerValue();
			m_pShowEtCO2Update->OnShowEtCO2Value( nEtCO2Value );
		}
	}


	//����EtCO2����״̬�������Ƿ���ʾEtCO2����
	bool CCO2SimulateBuild::IsShowEtCO2LinkState()
	{
		if( m_bClearWatchLink || m_bLinkWatchEtCO2 )
		{
			return true;
		}
		return false;
	}

	//�����Ƿ����EtCO2���Ӽ��
	void CCO2SimulateBuild::Set_IsClearEtCO2WatchLink(bool bClear)
	{
		m_bClearWatchLink  = bClear;
		boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
		if( m_pShowEtCO2Update != NULL )
		{
			if( IsShowEtCO2LinkState() )
			{
				m_pShowEtCO2Update->OnAllLinkUpdateShow();
			}
			else 
			{
				m_pShowEtCO2Update->OnAllUnLinkUpdateShow();
			}
		}
	}

	//����EtCO2���Ӽ��״̬
	void CCO2SimulateBuild::Set_EtCO2WatchLinkState(bool bLinking)
	{	
		m_bLinkWatchEtCO2   = bLinking;
		boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
		if( m_pShowEtCO2Update != NULL )
		{
			if( IsShowEtCO2LinkState() )
			{
				m_pShowEtCO2Update->OnAllLinkUpdateShow();
			}
			else 
			{
				m_pShowEtCO2Update->OnAllUnLinkUpdateShow();
			}
		}
	}

	/*******************************************************************************/
	// �������ƣ� OnStartAutoRespOp
	// ���ܣ� ����/��ͣ��������
	// ������ 
	//         BOOL bAutoResp:
	// ����ֵ:  
	void CCO2SimulateBuild::OnStartAutoRespOp( bool bAutoResp )
	{
		boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
		if( bAutoResp )
		{
			//�����ǰΪ���״̬�������Ƶ���״̬
			if( m_pCurrCO2SimulateState != NULL && m_pCurrCO2SimulateState->isKindOf( "CCO2SimulateIntubateState" ) )
			{
				m_pNextCO2SimulateState = m_pIntubateState;
			}
			else if( m_pNextCO2SimulateState != NULL && !m_pNextCO2SimulateState->isKindOf( "CCO2SimulateIntubateState" ) )
			{
				m_pNextCO2SimulateState  = NULL;
			}
			//��ǰģʽΪ��������
			m_pCurrCO2SimulateState  = &m_cAutoRespState;
			m_cAutoRespState.Set_IsFirstAutoRespState( TRUE );
		}
		else
		{
			if( m_pNextCO2SimulateState != NULL )
			{
				//��ǰģʽΪ���
				m_pCurrCO2SimulateState  = m_pNextCO2SimulateState;
			}
			else if( m_pCurrCO2SimulateState == NULL || !m_pCurrCO2SimulateState->isKindOf( "CCO2SimulateIntubateState" ) )
			{
				//��ǰģʽΪ�޺���״̬
				m_pCurrCO2SimulateState = &m_cNoRespState;
			}
			m_pNextCO2SimulateState  = NULL;
		}
	}

	/*******************************************************************************/
	// �������ƣ� OnIntubateOp
	// ���ܣ� ��/����¼�
	// ������ 
	//         BOOL bIntubate:
	// ����ֵ:  
	void CCO2SimulateBuild::IntubateEventOp( bool bIntubate )
	{
		boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
		if( m_pCurrCO2SimulateState != NULL && m_pCurrCO2SimulateState->isKindOf( "CCO2SimulateAutoRespState" ) )
		{
			m_pNextCO2SimulateState = bIntubate ? m_pIntubateState : NULL;
		}
		else
		{
			m_pCurrCO2SimulateState = bIntubate ? m_pIntubateState : (ICO2SimulateState *)&m_cNoRespState;
			m_pNextCO2SimulateState = NULL;
		};
	}

	/*******************************************************************************/
	// �������ƣ� OnOnceBreathEventOp
	// ���ܣ� һ�δ����¼�
	// ������ 
	// ����ֵ:  
	void CCO2SimulateBuild::OnceBreathEventOp()
	{
		boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
		if( m_pCurrCO2SimulateState != NULL )
		{
			m_pCurrCO2SimulateState->DoOnceBreathEventHandle();
		}
		//��ʾEtCO2��ֵ
		m_nReflushCalculate  = -20000;
		if( m_pShowEtCO2Update && m_pCurrCO2SimulateState)
		{
			int  nEtCO2Value = m_pCurrCO2SimulateState->GetCO2PerValue();
			m_pShowEtCO2Update->OnShowEtCO2Value( nEtCO2Value );
		}
	}

	/*******************************************************************************/
	// �������ƣ� OnCPREventOp
	// ���ܣ� �׶���CPR�¼�
	// ������ 
	// ����ֵ:  
	void CCO2SimulateBuild::CPREventOp( bool bStop )
	{
		m_pIntubateState->DoCPREventHandle( bStop );
	}

	/*********************************************************************************/
	//���ܣ��޸Ĳ��״̬��EtCO2ֵ
	//������
	//      int nEtCO2Value:             CO2%
	//����ֵ:  
	void CCO2SimulateBuild::ModifyEtCO2ValueIntubationState(int nEtCO2Value)
	{
		if( m_pCurrCO2SimulateState != NULL && m_pCurrCO2SimulateState->isKindOf( "CCO2SimulateIntubateState" ) )
		{
			m_cCO2CycleData.ModifyCO2PerValue( nEtCO2Value );
		}
	}
}}}
