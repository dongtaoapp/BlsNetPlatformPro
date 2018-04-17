#include ".\respapneacycledata.h"

#include "..\SimulatorBase\ICO2SimulateSign.h"

namespace jysoft { namespace simulator { namespace resp {

	CRespApneaCycleData::CRespApneaCycleData(CInspirationSegment *pInspirationSegment, CExhaleSegment *pExhaleSegment, int nRespRate, int nInspirationTime)
										: CRespCycleData(pInspirationSegment, pExhaleSegment, nRespRate, nInspirationTime)
	{
		m_nRespRate   = 0;
		m_iSampleSec  = 25;//每秒的采样率
	}

	CRespApneaCycleData::~CRespApneaCycleData(void)
	{
	}

	/*******************************************************************************/
	// 函数名称： JudgeIsRepeatCycleData
	// 功能： 判断是否同一周期的数据
	// 参数： int nRespRate:  呼吸次数
	//        int nMillitInspirationTime: 吸气时间(单位:0.1ms)
	//        float fCurrentRemainVolume: 当前残留的量(单位:ml)    
	//        float fSumVolume:           本周期的总气量
	//        float fRemainVolume:        本周期结束后的残留的量(单位:ml)
	// 返回值:  
	bool CRespApneaCycleData::JudgeIsRepeatCycleData(int nRespRate, int nMillitInspirationTime, float fCurrentRemainVolume, float fSumVolume, float fRemainVolume)
	{
		if( nRespRate != 0 )
		{
			return false;
		}
	#define  _INFINITE           0.0001
		if( int(m_fCurrentRemainVolume+_INFINITE) != int(m_fRemainVolume+_INFINITE) )
		{
			return false;
		}
		return true;
	}

	/*******************************************************************************/
	// 函数名称： ResetPrepareReadSampleData
	// 功能：  重置数据的读取准备
	// 参数： 
	// 返回值:  
	void CRespApneaCycleData::ResetPrepareReadSampleData()
	{
	#define  _INFINITE      0.0001
		m_cInspirationLungVolumes.ResetReadBeginPosPtr();
		m_cInspirationLungVolumes.Empty();
		m_cExhaleLungVolumes.ResetReadBeginPosPtr();
		m_cExhaleLungVolumes.Empty();
		//生成下降曲线
		if( int(m_fCurrentRemainVolume + _INFINITE) != int(m_fRemainVolume + _INFINITE) && m_pExhaleSegment != NULL )
		{
			m_pExhaleSegment->ZoomSegmentDataHandle( m_nInspirationTime );
			m_pExhaleSegment->ZoomRespVolumeHandle(m_fRemainVolume, m_fCurrentRemainVolume );
			float *fSamplePtr = m_pExhaleSegment->GetSamplePtr();
            for (short dwItem = 0; dwItem < m_pExhaleSegment->GetSampleSumNumber(); ++dwItem)
			{
				RespDataStruct  stcRespData;
				stcRespData.m_fLungVolumeValue_L = fSamplePtr[dwItem]/2;
				stcRespData.m_fLungVolumeValue_R = fSamplePtr[dwItem]/2;
				m_cExhaleLungVolumes.WriteData(&stcRespData, 1);
			}
		}
	}

	/*******************************************************************************
	//功能：获取时间区间内的呼吸数据
	//参数：int iMilliTime:          时间（0.1豪秒）
	//      float *pcBuffer:         返回的呼吸数据
	//返回值: 数据的长度
	*********************************************************************************/
    short CRespApneaCycleData::GetRespSimulateData(int iMilliTime, unsigned char byteAddress, /*out*/float *pcLeftBuffer /*= NULL*/, /*out*/float *pcRightBuffer /*= NULL*/)
	{
        short dwNum = short(iMilliTime * m_iSampleSec * 1e-4);
		if( pcLeftBuffer != NULL  && pcRightBuffer != NULL )
		{
			if( m_cExhaleLungVolumes.GetNoneReadedNum() == 0 )
			{
                for (short dwItem = 0; dwItem < dwNum; ++dwItem)
				{
					pcLeftBuffer[dwItem] = m_fRemainVolume/2;
					pcRightBuffer[dwItem] = m_fRemainVolume/2;
				}
			}
			else
			{
				//设置CO2的下降信号
				if( (m_cExhaleLungVolumes.GetCurrBufferNum() == m_cExhaleLungVolumes.GetNoneReadedNum()) && m_pCO2SimulateSignInteface)
				{
					if( m_pCO2SimulateSignInteface != NULL )
					{
						int nMilliOtherTime = m_nInspirationTime - m_nInspirationToCO2Time;
						m_pCO2SimulateSignInteface->OnCO2SimulateSignOp(TRUE, m_nInspirationToCO2Time, nMilliOtherTime);
					}
					//发送指令,控制模拟人的呼吸
					TransportOrderToSimulator( );
				}
				//end hjg 2008/7/29 添加; 8/18日修改i
				if( m_cExhaleLungVolumes.GetNoneReadedNum() >= dwNum )
				{
					RespDataStruct  stcRespData;
                    for (short dwItem = 0; dwItem < dwNum; ++dwItem)
					{
						m_cExhaleLungVolumes.ReadDataMovePtr(&stcRespData,1);
						pcLeftBuffer[dwItem] = stcRespData.m_fLungVolumeValue_L;
						pcRightBuffer[dwItem] = stcRespData.m_fLungVolumeValue_R;
					}
				}
				else
				{
                    for (short dwItem = 0; dwItem < dwNum; ++dwItem)
					{
						pcLeftBuffer[dwItem] = m_fRemainVolume/2;
						pcRightBuffer[dwItem] = m_fRemainVolume/2;
					}
				}
			}
		}
		return dwNum;
	}
}}}
