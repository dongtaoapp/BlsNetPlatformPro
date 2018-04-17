#include <boost/assert.hpp>
#include ".\respcycledata.h"

#include "..\Common\DecodeUtil.h"


using namespace jysoft::irp;
using namespace jysoft::utility;
namespace jysoft { namespace simulator { namespace resp {

	CRespCycleData::CRespCycleData(CInspirationSegment *pInspirationSegment, CExhaleSegment *pExhaleSegment, int nRespRate, int nInspirationTime)
	{
		m_pInspirationSegment  = pInspirationSegment;
		m_pExhaleSegment       = pExhaleSegment;
		//��������
		m_nRespRate            = nRespRate;
		//����ʱ��(��λ:0.1ms)
		m_nInspirationTime     = nInspirationTime;
		//��ǰ��������       (��λ:ml) 
		//�����ڵĳ�����     (��λ:ml)
		if( pInspirationSegment )
		{
			m_fCurrentRemainVolume = pInspirationSegment->Get_RemainRespVolume();
			m_fSumVolume          = pInspirationSegment->Get_SumRespVolume();
		}
		else
		{
			m_fCurrentRemainVolume = 0.0f;
			m_fSumVolume          = 0.0f;
		}
		//�����ں�Ĳ������� (��λ:ml)
		if ( pExhaleSegment )
		{
			m_fRemainVolume = pExhaleSegment->Get_RemainRespVolume();
		}
		else
		{
			m_fRemainVolume = 0.0f;
		}

		m_nInspirationToCO2Time = 0;
		m_nExhaleToCO2Time      = 0;

		m_pCO2SimulateSignInteface = NULL;
		m_pTransportOrderInterface = NULL;
		//����������ݵĲ�������
        short   dwSumNumber = 0;
		if( pInspirationSegment )
		{
			dwSumNumber = pInspirationSegment->GetSampleSumNumber();
		}
		dwSumNumber = (dwSumNumber/1024+1)*1024;
		m_cInspirationLungVolumes.InitializeBuff( dwSumNumber );
		if( pExhaleSegment )
		{
			dwSumNumber = pExhaleSegment->GetSampleSumNumber();
		}
		else
		{
			dwSumNumber = 0;
		}
		dwSumNumber = (dwSumNumber/1024+1)*1024;
		m_cExhaleLungVolumes.InitializeBuff( dwSumNumber );

		m_pbSynchronizeSignSend = NULL;
	}

	CRespCycleData::~CRespCycleData(void)
	{
		if( m_pInspirationSegment )
		{
			delete m_pInspirationSegment;
		}
		if( m_pExhaleSegment )
		{
			delete m_pExhaleSegment;
		}
		m_pCO2SimulateSignInteface = NULL;
		m_pTransportOrderInterface = NULL;
	}

	/*******************************************************************************/
	// �������ƣ� JudgeIsRepeatCycleData
	// ���ܣ� �ж��Ƿ�ͬһ���ڵ�����
	// ������ int nRespRate:  ��������
	//        int nMillitInspirationTime: ����ʱ��(��λ:0.1ms)
	//        float fCurrentRemainVolume: ��ǰ��������(��λ:ml)    
	//        float fSumVolume:           �����ڵ�������(��λ:ml)
	//        float fRemainVolume:        �����ڽ�����Ĳ�������(��λ:ml)
	// ����ֵ:  
	bool CRespCycleData::JudgeIsRepeatCycleData(int nRespRate, int nMillitInspirationTime, float fCurrentRemainVolume, float fSumVolume, float fRemainVolume)
	{
		if( m_nRespRate != nRespRate || m_nInspirationTime != nMillitInspirationTime )
		{
			return false;
		}
	#define  _INFINITE           0.0001
		if( int(m_fCurrentRemainVolume+_INFINITE) != int(fCurrentRemainVolume+_INFINITE) )
		{
			return false;
		}
		if( int(m_fSumVolume+_INFINITE) != int(fSumVolume+_INFINITE) )
		{
			return false;
		}
		if( int(m_fRemainVolume+_INFINITE) != int(fRemainVolume+_INFINITE) )
		{
			return false;
		}
		return true;
	}

	/*******************************************************************************/
	// �������ƣ� ResetPrepareReadSampleData
	// ���ܣ�  �������ݵĶ�ȡ׼��
	// ������ 
	// ����ֵ:  
	void CRespCycleData::ResetPrepareReadSampleData()
	{
        BOOST_ASSERT(m_pInspirationSegment != NULL && m_pExhaleSegment != NULL);

		m_cInspirationLungVolumes.ResetReadBeginPosPtr();
		m_cInspirationLungVolumes.Empty();
		m_cExhaleLungVolumes.ResetReadBeginPosPtr();
		m_cExhaleLungVolumes.Empty();
		//�ָ����ҷεĲ�������
		float *fSamplePtr = m_pInspirationSegment->GetSamplePtr();
        for (short dwItem = 0; dwItem < m_pInspirationSegment->GetSampleSumNumber(); ++dwItem)
		{
			RespDataStruct  stcRespData;
			stcRespData.m_fLungVolumeValue_L = fSamplePtr[dwItem]/2;
			stcRespData.m_fLungVolumeValue_R = fSamplePtr[dwItem]/2;
			m_cInspirationLungVolumes.WriteData(&stcRespData, 1);
		}
		fSamplePtr = m_pExhaleSegment->GetSamplePtr();
        for (short dwItem = 0; dwItem < m_pExhaleSegment->GetSampleSumNumber(); ++dwItem)
		{
			RespDataStruct  stcRespData;
			stcRespData.m_fLungVolumeValue_L = fSamplePtr[dwItem]/2;
			stcRespData.m_fLungVolumeValue_R = fSamplePtr[dwItem]/2;
			m_cExhaleLungVolumes.WriteData(&stcRespData, 1);
		}
	}

	/*******************************************************************************
	//���ܣ���ȡʱ�������ڵĺ�������
	//������int iMilliTime:          ʱ�䣨0.1���룩
	//      float *pcBuffer:         ���صĺ�������
	//      BYTE byteAddress:        Ŀ���豸��ַ��
	//����ֵ: ���ݵĳ���
	*********************************************************************************/
    short CRespCycleData::GetRespSimulateData(int iMilliTime, unsigned char byteAddress, /*out*/float *pcLeftBuffer /*= NULL*/, /*out*/float *pcRightBuffer  /*= NULL*/)
	{
        short  dwNum = m_pInspirationSegment->GetSampleNum(iMilliTime);
		if( pcLeftBuffer != NULL && pcRightBuffer != NULL )
		{
			//����CO2���½��ź�
			if( m_cInspirationLungVolumes.GetNoneReadedNum() == m_cInspirationLungVolumes.GetCurrBufferNum() )
			{
				if( m_pCO2SimulateSignInteface )
				{
					int nMilliOtherTime = m_nInspirationTime - m_nInspirationToCO2Time;
					m_pCO2SimulateSignInteface->OnCO2SimulateSignOp(TRUE, m_nInspirationToCO2Time, nMilliOtherTime);
				}
				//����ָ��,����ģ���˵ĺ���
				TransportOrderToSimulator( );
			}
			if( m_cInspirationLungVolumes.GetNoneReadedNum() >= dwNum )
			{
                for (short dwItem = 0; dwItem < dwNum; ++dwItem)
				{
					RespDataStruct    stcRespData;
					m_cInspirationLungVolumes.ReadDataMovePtr(&stcRespData, 1, NULL);
					pcLeftBuffer[dwItem]  = stcRespData.m_fLungVolumeValue_L;
					pcRightBuffer[dwItem] = stcRespData.m_fLungVolumeValue_R;
				}
			}
			else if( m_cInspirationLungVolumes.GetNoneReadedNum() != 0 )
			{
                short  dwNoneReadNum = m_cInspirationLungVolumes.GetNoneReadedNum();
				RespDataStruct    stcRespData;
                for (short dwItem = 0; dwItem < dwNoneReadNum; ++dwItem)
				{
					m_cInspirationLungVolumes.ReadDataMovePtr(&stcRespData, 1, NULL);
					pcLeftBuffer[dwItem]  = stcRespData.m_fLungVolumeValue_L;
					pcRightBuffer[dwItem] = stcRespData.m_fLungVolumeValue_R;
				}
				for (; dwNoneReadNum < dwNum; ++dwNoneReadNum)
				{
					pcLeftBuffer[dwNoneReadNum]  = stcRespData.m_fLungVolumeValue_L;
					pcRightBuffer[dwNoneReadNum] = stcRespData.m_fLungVolumeValue_R;
				}
			}
			else
			{
				if(m_cExhaleLungVolumes.GetNoneReadedNum() == m_cExhaleLungVolumes.GetCurrBufferNum())
				{
					//����CO2�������ź�
					if( m_pCO2SimulateSignInteface )
					{
						//����ʱ�䣺����ʱ��-����ʱ��
						int nExhaleTime = m_nRespCycleTime - m_nInspirationTime;
						int nMilliOtherTime = nExhaleTime - m_nExhaleToCO2Time;
						m_pCO2SimulateSignInteface->OnCO2SimulateSignOp(FALSE, m_nExhaleToCO2Time, nMilliOtherTime);
					}
				}
				if( m_cExhaleLungVolumes.GetNoneReadedNum() >= dwNum )
				{
					RespDataStruct    stcRespData;
                    for (short dwItem = 0; dwItem < dwNum; ++dwItem)
					{
						m_cExhaleLungVolumes.ReadDataMovePtr(&stcRespData, 1, NULL);
						pcLeftBuffer[dwItem]  = stcRespData.m_fLungVolumeValue_L;
						pcRightBuffer[dwItem] = stcRespData.m_fLungVolumeValue_R;
					}
				}
				else if( m_cExhaleLungVolumes.GetNoneReadedNum() != 0 )
				{
                    short  dwNoneReadNum = m_cExhaleLungVolumes.GetNoneReadedNum();
					RespDataStruct    stcRespData;
                    for (short dwItem = 0; dwItem < dwNoneReadNum; ++dwItem)
					{
						m_cExhaleLungVolumes.ReadDataMovePtr(&stcRespData, 1, NULL);
						pcLeftBuffer[dwItem]  = stcRespData.m_fLungVolumeValue_L;
						pcRightBuffer[dwItem] = stcRespData.m_fLungVolumeValue_R;
					}
					for (; dwNoneReadNum < dwNum; ++dwNoneReadNum)
					{
						pcLeftBuffer[dwNoneReadNum]  = m_fRemainVolume/2;
						pcRightBuffer[dwNoneReadNum] = m_fRemainVolume/2;
					}
				}
				else
				{	
                    for (short index = 0; index < dwNum; ++index)
					{
						pcLeftBuffer[index]  = m_fRemainVolume/2;
						pcRightBuffer[index] = m_fRemainVolume/2;
					}
				}
			}
		}
		return dwNum;
	}

	void CRespCycleData::Set_CO2SimulateSignInteface(ICO2SimulateSign *pInterface)
	{
		m_pCO2SimulateSignInteface = pInterface;
	}

	void CRespCycleData::Set_TransportOrderIrpToSimulatorInteface(transLayer::ITransportOrderIrpToSimulator *pInterface, int *pIsSynSignSendFlag)
	{
		m_pTransportOrderInterface = pInterface;

		m_pbSynchronizeSignSend  = pIsSynSignSendFlag;
	}

	//����ָ��,����ģ���˵ĺ���
	void CRespCycleData::TransportOrderToSimulator()
	{
		if( m_pTransportOrderInterface && m_pbSynchronizeSignSend )
		{
			CSimulatorOrderIrp *pOrderIrp  = NULL;
			if( m_eRefurbishDataRange != RD_NoChange  )
			{
				if( (*m_pbSynchronizeSignSend) != 0 )
				{
					//������������ָ��
					pOrderIrp = TranslateRespIrp( false );
					*m_pbSynchronizeSignSend  = 2;      //ע��Ҳ�Ǳ�ʾTRUE������ָ�ѷ��ͺ�������ָ��
				}
				else
				{
					//������������ָ��ͬ��ָ��
					pOrderIrp = TranslateRespIrp( true );
					*m_pbSynchronizeSignSend = 1;
				}
			}
			else 
			{
				if( (*m_pbSynchronizeSignSend) > 0 )
				{
					//������������ָ��
					pOrderIrp = TranslateRespIrp( false );
				}
				*m_pbSynchronizeSignSend  = 2;
			}
			if( pOrderIrp )
			{
				m_pTransportOrderInterface->OnTransportDownOrderToSimulater( pOrderIrp );
			}

		}
	}

	//����ָ��Irp
	CSimulatorOrderIrp * CRespCycleData::TranslateRespIrp( bool bSynchronizeSignOrder )
	{
		/*CSimulatorOrderIrp  *pSimulatorOrderIrp = new CSimulatorOrderIrp(CT_BREATH_SET);
		byte    cLogicVoltData[18];
		::memset(cLogicVoltData, 0, 18);
		//������ʼλ
		cLogicVoltData[0] = 0xFF;
		cLogicVoltData[1] = 0x00;
		cLogicVoltData[2] = 0xFF;
		cLogicVoltData[3] = 0x00;
		cLogicVoltData[4] = 0xFF;
		//���ý���λ
		cLogicVoltData[17] = 0xFC;
		cLogicVoltData[16] = 0xFC;
		cLogicVoltData[15] = 0xFC;

		short   *psRespAddress = (short *)&cLogicVoltData[5];
		*psRespAddress = 0x820;    //4��ģ��(��·ģ��)��10��ģ�飨��������ӿڣ�
		//���ݰ����ȣ���ָ��
		cLogicVoltData[7]  = 7;
		//�趨���������Ĺ��ܺ�
		cLogicVoltData[8]  = 0x81;
		//��������
		cLogicVoltData[9]    =  (byte)m_nRespRate;
		if( m_nRespRate != 0 )
		{
			//����ʱ��(��ʽ����λ�ֽڣ���λ:0.1��)
			short   sInspirationTime = short(m_nInspirationTime/1000);
			BYTE *pDataPtr = (BYTE *)&sInspirationTime;
			cLogicVoltData[10] = pDataPtr[1];  //��λ
			cLogicVoltData[11] = pDataPtr[0];  //��λ
			//����ʱ��(��ʽ����λ�ֽڣ���λ:0.1��)
			int nExhaleTime = m_nRespCycleTime - m_nInspirationTime;
			short   sExhaleTime = short(nExhaleTime/1000);
			pDataPtr = (BYTE *)&sExhaleTime;
			cLogicVoltData[12] = pDataPtr[1];  //��λ
			cLogicVoltData[13] = pDataPtr[0];  //��λ
			//ͬ��ָ��
			cLogicVoltData[14] = bSynchronizeSignOrder ? 0x01 : 0x00;
		}
		//ת��Ϊ������ı�
		std::string  strRespOrderDecode = CDecodeUtil::byteArrayToHexstr(cLogicVoltData, 18);
		pSimulatorOrderIrp->addOrderDecode( strRespOrderDecode );
		return pSimulatorOrderIrp;*/
		return NULL;
	}
}}}
