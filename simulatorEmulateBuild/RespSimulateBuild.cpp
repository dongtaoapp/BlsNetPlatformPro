#include ".\respsimulatebuild.h"
#include ".\IRespBuildTypeState.h"
#include ".\RespCycleData.h"
#include ".\RespApneaCycleData.h"
#include ".\RespNormalTypeState.h"
#include ".\RespBiotTypeState.h"
#include ".\RespApneusticTypeState.h"
#include ".\RespApneaTypeState.h"
#include ".\RespSignTypeState.h"


using namespace jysoft::transLayer;
namespace jysoft { namespace simulator { namespace resp {

	CRespSimulateBuild::CRespSimulateBuild( )
	{
		m_pCO2SimulateSignInterface  = NULL;
		m_pRespBuildState = NULL;
		m_nRespRate        = 0;
		m_pCurrentRespData[0] = new CRespApneaCycleData(NULL, NULL,0,0);
		((CRespApneaCycleData *)m_pCurrentRespData[0])->Set_RemainVolume(300.0f);
		m_pCurrentRespData[1] = NULL;
		m_nRemainTime      = m_pCurrentRespData[0]->Get_RespCycleTime();
		m_ePatientType     = SPT_Adult; 
		m_pTransportOrderToSimulatorInterface = NULL;
		//����RR���Ӽ��
		m_bClearWatchLink   = true;
		m_bLinkWatchResp    = false;

		m_bSynchronizeSignSend  = 0;
	}

	CRespSimulateBuild::~CRespSimulateBuild(void)
	{
		if( m_pRespBuildState )
		{
			delete m_pRespBuildState;
			m_pRespBuildState = NULL;
		}
		if( m_pCurrentRespData[0] != NULL )
		{
			delete m_pCurrentRespData[0];
			m_pCurrentRespData[0] = NULL;
		}
		if( m_pCurrentRespData[1] != NULL )
		{
			delete m_pCurrentRespData[1];
			m_pCurrentRespData[1] = NULL;
		}
	}

	void CRespSimulateBuild::ModifyRespBuildType(eRespMode eMode, int nBreathRate)
	{
		switch( eMode )
		{
		case RM_Normal:
			{
				if( m_pRespBuildState == NULL || !m_pRespBuildState->isKindOf("CRespNormalTypeState") )
				{
					IRespBuildTypeState *pNewType = new CRespNormalTypeState(m_ePatientType);
					pNewType->InitialLoadOriginSimulateData( respResourcePath, nBreathRate );
					delete m_pRespBuildState;
					m_pRespBuildState = pNewType;
				}
				else
				{
					m_pRespBuildState->OnModifyRespRate( nBreathRate );
				}
				break;
			}
		case RM_Biots:
			{
				if( m_pRespBuildState == NULL || !m_pRespBuildState->isKindOf("CRespBiotTypeState") )
				{
					IRespBuildTypeState *pNewType = new CRespBiotTypeState(m_ePatientType);
					pNewType->InitialLoadOriginSimulateData( respResourcePath, nBreathRate );
					delete m_pRespBuildState;
					m_pRespBuildState = pNewType;
				}
				else
				{
					m_pRespBuildState->OnModifyRespRate( nBreathRate );
				}
				break;
			}
		case RM_Apneustic:
			{
				if( m_pRespBuildState == NULL || !m_pRespBuildState->isKindOf("CRespApneusticTypeState") )
				{
					IRespBuildTypeState *pNewType = new CRespApneusticTypeState(m_ePatientType);
					pNewType->InitialLoadOriginSimulateData( respResourcePath, nBreathRate );
					delete m_pRespBuildState;
					m_pRespBuildState = pNewType;
				}
				break;
			}
		case RM_Apnea:
			{
				if( m_pRespBuildState == NULL || !m_pRespBuildState->isKindOf("CRespApneaTypeState") )
				{
					IRespBuildTypeState *pNewType = new CRespApneaTypeState(m_ePatientType);
					pNewType->InitialLoadOriginSimulateData( respResourcePath, nBreathRate );
					delete m_pRespBuildState;
					m_pRespBuildState = pNewType;
				}
				break;
			}
		case RM_Sign:
			{
				if( m_pRespBuildState == NULL || !m_pRespBuildState->isKindOf("CRespSignTypeState") )
				{
					IRespBuildTypeState *pNewType = new CRespSignTypeState(m_ePatientType);
					pNewType->InitialLoadOriginSimulateData( respResourcePath, nBreathRate );
					delete m_pRespBuildState;
					m_pRespBuildState = pNewType;
				}
				break;
			}
		}
		//����/��ͣ��������
		m_pCO2SimulateSignInterface->OnStartAutoRespOp( eMode == RM_Apnea ? false : true );
	}


	/*******************************************************************************
	//���ܣ���ȡ���������ڵ���������
	//������int iMilliTime:          ʱ�䣨0.1���룩
	//      float *pcBuffer:         ���ص���������
	//����ֵ:  �������ݵĳ���
	*********************************************************************************/
	unsigned long CRespSimulateBuild::GetRespSimulateData(int iMilliTime, /*out*/float *pcLeftBuffer /*= NULL*/, /*out*/float *pcRightBuffer /*= NULL*/)
	{
		unsigned char   byteAddress = 0;
		//ModifyTransmitAddress( /*out*/byteAddress );
		unsigned long dwNum = m_pCurrentRespData[0]->GetRespSimulateData(iMilliTime, byteAddress, pcLeftBuffer, pcRightBuffer);
		if( pcLeftBuffer != NULL &&  pcRightBuffer != NULL )
		{
			m_nRemainTime -= iMilliTime;
			if(m_nRemainTime <= 0)
			{
				CombineNextCycleSimulateData();
				m_cRespDeletedCollects.AddRespCycleDataPtr( m_pCurrentRespData[0] );
				m_pCurrentRespData[0] = m_pCurrentRespData[1];
				m_pCurrentRespData[1] = NULL;
				m_nRemainTime = m_pCurrentRespData[0]->Get_RespCycleTime();
				//��ǰ�ĺ�������
				m_nRespRate = m_pCurrentRespData[0]->GetCurrentRespRate();
				//if( m_pCurrentRespData[0]->m_eRefurbishDataRange != RD_NoChange )
				//{
				//	m_pCurrentRespData[0]->TransportOrderRateToSimulator( m_nRespRate );
				//}
				boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
				if( m_pShowRespUpdate )
				{
					eRespMode   enumMode = m_pRespBuildState->Get_RespMode();
					m_pShowRespUpdate->OnShowRespRate( enumMode, m_nRespRate );
				}
			}
		}
		return dwNum;
	}

	/*******************************************************************************
	//���ܣ���ʼ��ģ�����������
	//������eRespMode eMode:  ģʽ����
	//      int nBreathRate:             ��������
	//����ֵ:  
	*********************************************************************************/
	void CRespSimulateBuild::InitializeBuild(eRespMode eMode,  int nBreathRate)
	{
		m_bSynchronizeSignSend  = 0;
		ModifyRespBuildType(eMode,nBreathRate);
		m_cRespDeletedCollects.AddRespCycleDataPtr( m_pCurrentRespData[0] );
		//��ǰ�ķ������������
		float fVolume = m_pRespBuildState->GetApneaRemainVolume();
		m_pCurrentRespData[0] = m_pRespBuildState->OnCombineNextRespCycleData( fVolume, &m_cRespDeletedCollects );
		m_nRemainTime         = m_pCurrentRespData[0]->Get_RespCycleTime();
		m_pCurrentRespData[1] = NULL;
		//��ǰ�ĺ�������
		m_nRespRate = m_pCurrentRespData[0]->GetCurrentRespRate();
		//����CO2�������ӿ�
		m_pCurrentRespData[0]->Set_CO2SimulateSignInteface( m_pCO2SimulateSignInterface );
		//����Resp��ģ����ͬ������ͽӿ�
		m_pCurrentRespData[0]->Set_TransportOrderIrpToSimulatorInteface( m_pTransportOrderToSimulatorInterface, &m_bSynchronizeSignSend);
	}

	/*******************************************************************************/
	// �������ƣ� OnModifyPnPFacility
	// ���ܣ� �ı��Ȳ���豸
	// ������ 
	//         CSyncPnpFacilities *pSyncPnPFacilities:
	// ����ֵ:  
	void CRespSimulateBuild::OnModifyPnPFacility(pnp::CSyncPnpFacilities *pSyncPnPFacilities)
	{
		unsigned char  byteAddress[2];
		byteAddress[0] = byteAddress[1] = 0;
		//ModifyTransmitAddress( /*out*/byteAddress[0] );
		COpRespBuildInterface::OnModifyPnPFacility( pSyncPnPFacilities );
		//ModifyTransmitAddress( /*out*/byteAddress[1] );
		if( m_pRespBuildState != NULL )
		{
			//�趨�����ڷ���ָ��
			eRespMode  eMode = m_pRespBuildState->Get_RespMode();
			if( eMode != RM_Stokes && eMode != RM_Sign && eMode != RM_IrregularGasp && eMode != RM_Apnea )
			{
				int  nRespRate = m_pRespBuildState->Get_nRespRate();
				m_pRespBuildState->OnModifyRespRate( nRespRate );
			}
		}
	}

	/*******************************************************************************/
	// �������ƣ� SetRespBuildRelateInterfacesPtr
	// ���ܣ� ���ú����������ָ��
	// ������ 
	//        ICO2SimulateSign *pInterface:
	//        ITransportOrderIrpToSimulator *pTransportInterface:  
	//        SimulatePatientType ePateintType:    ģ�������
	// ����ֵ: 
	void CRespSimulateBuild::SetRespBuildRelateInterfacesPtr(ICO2SimulateSign *pInterface, const std::string &resPath, ITransportOrderIrpToSimulator *pTransportInterface /*= NULL*/, SimulatePatientType eType /*= SPT_Adult*/)
	{
		respResourcePath = resPath + "\\RespSimulateData";
		m_pCO2SimulateSignInterface  = pInterface;
		m_ePatientType     = eType; 
		m_pTransportOrderToSimulatorInterface = pTransportInterface;
	}

	/*******************************************************************************
	//���ܣ���֯�����ڵĺ�������
	//������
	//����ֵ:  
	*********************************************************************************/
	void CRespSimulateBuild::CombineNextCycleSimulateData()
	{
		float fRemainVolume = m_pCurrentRespData[0]->Get_RemainRespVolume();
		if( m_pRespBuildState != NULL )
		{
			m_pCurrentRespData[1] = m_pRespBuildState->OnCombineNextRespCycleData(fRemainVolume, &m_cRespDeletedCollects);
			//����CO2�������ӿ�
			m_pCurrentRespData[1]->Set_CO2SimulateSignInteface( m_pCO2SimulateSignInterface );
			//����Resp��ģ����ͬ������ͽӿ�
			m_pCurrentRespData[1]->Set_TransportOrderIrpToSimulatorInteface( m_pTransportOrderToSimulatorInterface, &m_bSynchronizeSignSend );
		}
	}


	void CRespSimulateBuild::ModifyRespRate(int nBreathRate)
	{
		if( m_pRespBuildState )
		{
			m_pRespBuildState->OnModifyRespRate( nBreathRate );
		}
	}

	/*********************************************************************************/
	//���ܣ� �޸�Ӱ���������Ϊ
	//������
	//����ֵ:  
	void CRespSimulateBuild::ModifyInfluentRespBehaviors()
	{

	}

	//�رպ���������
	void CRespSimulateBuild::CloseRespSimulateBuild()
	{
		m_cRespDeletedCollects.AddRespCycleDataPtr( m_pCurrentRespData[0] );
		//���
		m_cRespDeletedCollects.EmptyRespCycleDataCollects();
		if( m_pRespBuildState )
		{
			delete m_pRespBuildState;
			m_pRespBuildState = NULL;
		}
		m_pCO2SimulateSignInterface  = NULL;
		m_nRespRate        = 0;
		m_pCurrentRespData[0] = new CRespApneaCycleData(NULL, NULL,0,0);
		((CRespApneaCycleData *)m_pCurrentRespData[0])->Set_RemainVolume(1500.0f);
		m_pCurrentRespData[1] = NULL;
		m_nRemainTime      = m_pCurrentRespData[0]->Get_RespCycleTime();
		m_ePatientType     = SPT_Adult; 
		m_pTransportOrderToSimulatorInterface = NULL;
	}

	//����RR����״̬�������Ƿ���ʾResp����
	bool CRespSimulateBuild::IsShowRespLinkState()
	{
		if( m_bClearWatchLink || m_bLinkWatchResp )
		{
			return true;
		}
		return false;
	}

	//�����Ƿ����RR���Ӽ��
	void CRespSimulateBuild::Set_IsClearRespWatchLink(bool bClear)
	{
		m_bClearWatchLink  = bClear;
		boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
		if( m_pShowRespUpdate != NULL )
		{
			if( IsShowRespLinkState() )
			{
				m_pShowRespUpdate->OnAllLinkUpdateShow();
			}
			else 
			{
				m_pShowRespUpdate->OnAllUnLinkUpdateShow();
			}
		}
	}

	//����RR���Ӽ��״̬
	void CRespSimulateBuild::Set_RespWatchLinkState(bool bLinking)
	{
		m_bLinkWatchResp   = bLinking;
		boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
		if( m_pShowRespUpdate != NULL )
		{
			if( IsShowRespLinkState() )
			{
				m_pShowRespUpdate->OnAllLinkUpdateShow();
			}
			else 
			{
				m_pShowRespUpdate->OnAllUnLinkUpdateShow();
			}
		}
	}
}}}
