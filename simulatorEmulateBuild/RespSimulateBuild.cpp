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
		//忽略RR链接检查
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
		//启动/暂停自主呼吸
		m_pCO2SimulateSignInterface->OnStartAutoRespOp( eMode == RM_Apnea ? false : true );
	}


	/*******************************************************************************
	//功能：获取滑块区域内的曲线数据
	//参数：int iMilliTime:          时间（0.1豪秒）
	//      float *pcBuffer:         返回的曲线数据
	//返回值:  曲线数据的长度
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
				//当前的呼吸次数
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
	//功能：初始化模拟呼吸构造器
	//参数：eRespMode eMode:  模式类型
	//      int nBreathRate:             呼吸次数
	//返回值:  
	*********************************************************************************/
	void CRespSimulateBuild::InitializeBuild(eRespMode eMode,  int nBreathRate)
	{
		m_bSynchronizeSignSend  = 0;
		ModifyRespBuildType(eMode,nBreathRate);
		m_cRespDeletedCollects.AddRespCycleDataPtr( m_pCurrentRespData[0] );
		//当前的肺内气体残留量
		float fVolume = m_pRespBuildState->GetApneaRemainVolume();
		m_pCurrentRespData[0] = m_pRespBuildState->OnCombineNextRespCycleData( fVolume, &m_cRespDeletedCollects );
		m_nRemainTime         = m_pCurrentRespData[0]->Get_RespCycleTime();
		m_pCurrentRespData[1] = NULL;
		//当前的呼吸次数
		m_nRespRate = m_pCurrentRespData[0]->GetCurrentRespRate();
		//设置CO2的启动接口
		m_pCurrentRespData[0]->Set_CO2SimulateSignInteface( m_pCO2SimulateSignInterface );
		//设置Resp与模拟人同步命令发送接口
		m_pCurrentRespData[0]->Set_TransportOrderIrpToSimulatorInteface( m_pTransportOrderToSimulatorInterface, &m_bSynchronizeSignSend);
	}

	/*******************************************************************************/
	// 函数名称： OnModifyPnPFacility
	// 功能： 改变热插拔设备
	// 参数： 
	//         CSyncPnpFacilities *pSyncPnPFacilities:
	// 返回值:  
	void CRespSimulateBuild::OnModifyPnPFacility(pnp::CSyncPnpFacilities *pSyncPnPFacilities)
	{
		unsigned char  byteAddress[2];
		byteAddress[0] = byteAddress[1] = 0;
		//ModifyTransmitAddress( /*out*/byteAddress[0] );
		COpRespBuildInterface::OnModifyPnPFacility( pSyncPnPFacilities );
		//ModifyTransmitAddress( /*out*/byteAddress[1] );
		if( m_pRespBuildState != NULL )
		{
			//设定下周期发送指令
			eRespMode  eMode = m_pRespBuildState->Get_RespMode();
			if( eMode != RM_Stokes && eMode != RM_Sign && eMode != RM_IrregularGasp && eMode != RM_Apnea )
			{
				int  nRespRate = m_pRespBuildState->Get_nRespRate();
				m_pRespBuildState->OnModifyRespRate( nRespRate );
			}
		}
	}

	/*******************************************************************************/
	// 函数名称： SetRespBuildRelateInterfacesPtr
	// 功能： 设置呼吸构造相关指针
	// 参数： 
	//        ICO2SimulateSign *pInterface:
	//        ITransportOrderIrpToSimulator *pTransportInterface:  
	//        SimulatePatientType ePateintType:    模拟人类别
	// 返回值: 
	void CRespSimulateBuild::SetRespBuildRelateInterfacesPtr(ICO2SimulateSign *pInterface, const std::string &resPath, ITransportOrderIrpToSimulator *pTransportInterface /*= NULL*/, SimulatePatientType eType /*= SPT_Adult*/)
	{
		respResourcePath = resPath + "\\RespSimulateData";
		m_pCO2SimulateSignInterface  = pInterface;
		m_ePatientType     = eType; 
		m_pTransportOrderToSimulatorInterface = pTransportInterface;
	}

	/*******************************************************************************
	//功能：组织下周期的呼吸数据
	//参数：
	//返回值:  
	*********************************************************************************/
	void CRespSimulateBuild::CombineNextCycleSimulateData()
	{
		float fRemainVolume = m_pCurrentRespData[0]->Get_RemainRespVolume();
		if( m_pRespBuildState != NULL )
		{
			m_pCurrentRespData[1] = m_pRespBuildState->OnCombineNextRespCycleData(fRemainVolume, &m_cRespDeletedCollects);
			//设置CO2的启动接口
			m_pCurrentRespData[1]->Set_CO2SimulateSignInteface( m_pCO2SimulateSignInterface );
			//设置Resp与模拟人同步命令发送接口
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
	//功能： 修改影响呼吸的行为
	//参数：
	//返回值:  
	void CRespSimulateBuild::ModifyInfluentRespBehaviors()
	{

	}

	//关闭呼吸构造器
	void CRespSimulateBuild::CloseRespSimulateBuild()
	{
		m_cRespDeletedCollects.AddRespCycleDataPtr( m_pCurrentRespData[0] );
		//清空
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

	//根据RR链接状态，返回是否显示Resp数据
	bool CRespSimulateBuild::IsShowRespLinkState()
	{
		if( m_bClearWatchLink || m_bLinkWatchResp )
		{
			return true;
		}
		return false;
	}

	//设置是否忽略RR链接检查
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

	//设置RR链接检查状态
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
