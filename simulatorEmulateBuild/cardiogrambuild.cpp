#include ".\CardiogramBuild.h"

#include "..\Common\CommonGlobal.h"

#include "..\Common\LineBuffer.h"
#include "..\Common\VirtualIrp.h"
#include "..\Common\DecodeUtil.h"
#include "..\Common\PatientRuleInterfaceGlobal.h"

#include "..\SimulatorBase\Sample.h"
#include "..\SimulatorBase\ShowECGUpdateInterface.h"
#include "..\SimulatorBase\IPnPFacility.h"

#include "..\ElementParse\SAction_ECG.h"

#include "..\AdultParams\AdultCardiogramParamFactory.h"


using namespace jysoft::irp;
using namespace jysoft::transLayer;
namespace jysoft { namespace simulator { namespace ecg {

	CCardiogramBuild::CCardiogramBuild()
	{
		m_bInitialed             = false;//ĩ��ʼ��

		m_uArtifactNum           = 0;
		m_pPtrTransportLayer     = NULL;
		m_pPhysiologyStartSignPtr = NULL;
		m_eNextCycleState        = NC_Rhythm;
		m_iCycleTime             = 0;

		m_bCardiogramModifyed[0] = m_bCardiogramModifyed[1] = true;

		m_pParamFactory         = NULL;
		m_pHeartStartSignAgg    = NULL;
		m_bClearWatchLink       = true; //�����ĵ����Ӽ��
		m_bLinkWatchEcg         = false;
	}

	CCardiogramBuild::~CCardiogramBuild(void)
	{
		if( m_pParamFactory )
		{
			delete m_pParamFactory;
			m_pParamFactory = NULL;
		}
	}

	//�ر��ĵ�ͼ������
	void CCardiogramBuild::CloseCardiogramBuild()
	{
		if( m_pParamFactory != NULL )
		{
			delete m_pParamFactory;
			m_pParamFactory = NULL;
		}
		m_bInitialed             = false;//ĩ��ʼ��

		m_uArtifactNum           = 0;
		m_pPtrTransportLayer     = NULL;
		m_pPhysiologyStartSignPtr = NULL;
		m_eNextCycleState        = NC_Rhythm;
		m_iCycleTime             = 0;
		m_bCardiogramModifyed[0] = m_bCardiogramModifyed[1] = true;
	}

	/*******************************************************************************/
	// �������ƣ� SetEcgBuildRelateInterfacesPtr
	// ���ܣ� �����ĵ�ͼ�������ָ��
	// ������ 
	//        ITransportOrderIrpToSimulator *pPtrTransportLayer:
	//        IPhysiologyStartSign *pSpO2SignPtr:  
	//        SimulatePatientType ePateintType:    ģ�������
	// ����ֵ: 
	void CCardiogramBuild::SetEcgBuildRelateInterfacesPtr(IPhysiologyStartSign *pSpO2SignPtr, const std::string &resPath, ITransportOrderIrpToSimulator *pPtrTransportLayer, SimulatePatientType ePateintType)
	{
		m_pPhysiologyStartSignPtr = pSpO2SignPtr;
		m_pPtrTransportLayer      = pPtrTransportLayer;
		if( m_pParamFactory != NULL )
		{
			delete m_pParamFactory;
			m_pParamFactory = NULL;
		}
		switch(ePateintType)
		{
		case SPT_Adult:
			{
				m_pParamFactory = new CAdultCardiogramParamFactory( resPath );
				break;
			}
		}
	}

	bool CCardiogramBuild::InitializeBuild(const CECGParams &cECGParams)
	{
		if(cECGParams.m_dwField & PM_EXTRASYS)
		{
			m_cParams.m_dwField |= PM_EXTRASYS;
			m_cParams.m_eExtrasys = cECGParams.m_eExtrasys;
		}
		if(cECGParams.m_dwField & PM_EXTRASYSRATE)
		{
			m_cParams.m_dwField |= PM_EXTRASYSRATE;
			m_cParams.m_iExtrasysRate = cECGParams.m_iExtrasysRate;
			m_cExtrasystSignInterface.ModifyExtrasystRate( m_cParams.m_iExtrasysRate );
		}
		short   sConduct = 0;     //��������
		if( cECGParams.m_dwField & PM_CONDUCT)
		{
			m_cParams.m_dwField |= PM_CONDUCT;
			sConduct = m_cParams.m_sConduct  = cECGParams.m_sConduct;

		}
		short   sExtendParam = 0;  //��չ����ֵ
		if( cECGParams.m_dwField & PM_EXTEND )
		{
			m_cParams.m_dwField |= PM_EXTEND;
			sExtendParam = m_cParams.m_sExtendParam = cECGParams.m_sExtendParam;
		}
		//--------------------------------------------------------------------------------------------------------
		m_pHeartStartSignAgg  = NULL;
		//�Ƴ�Ѫ������ʱ����
		m_cSpO2SignBuildInterface.ResetSpO2TimeSignList();
		//end hjg 2007/3/18 ���
		m_uArtifactNum = 0;
		m_eNextCycleState = NC_Rhythm;

		ICardiogramLeads *pVirEcgLeads = m_pParamFactory->CreateCardiogramLeadsInstance( &cECGParams );
		bool bRtn = CreateCardiogram( pVirEcgLeads, /*out*/&m_cLeadsSampleBuff[0]);
		if( bRtn )
		{
			m_iCycleTime = pVirEcgLeads->GetCycleTime();
			pVirEcgLeads->SeteRefurbishDataRange(RD_MainSegmentData);
		}
		m_DataBuffer.InitializeBuff( m_cLeadsSampleBuff[0].GetSampleNum(20*10000));

		m_bCardiogramModifyed[0] = true;
		m_bCardiogramModifyed[1] = pVirEcgLeads->IsInitialSendDoubleSampleData();
		m_bInitialed = true; //�ѳ�ʼ��

		return bRtn;
	}

	//���س�������ĵ�������ʱ��
	int CCardiogramBuild::GetDefibrillateActDelayTime()
	{
		if(m_cParams.m_eBasicRm == BR_AFib)
			return 30800; //3.08��
		return 35800;     //3.58��
	}

	//ֱ���޸��ĵ�ͼ���� 2006/11/2 hjg ���
	void CCardiogramBuild::DirectModifyCardiogram(const CECGParams * ptrParam)
	{
		//�Ƴ�Ѫ������ʱ����
		m_cSpO2SignBuildInterface.ResetSpO2TimeSignList();
		//end hjg 2007/3/18 ���
		m_uArtifactNum = 0;
		m_eNextCycleState = NC_Rhythm;
		m_DataBuffer.Empty();

		ICardiogramLeads *pVirEcgLeads = m_pParamFactory->CreateCardiogramLeadsInstance( ptrParam );
		bool bRtn = CreateCardiogram( pVirEcgLeads, /*out*/&m_cLeadsSampleBuff[0]);
		if( bRtn )
		{
			m_iCycleTime = pVirEcgLeads->GetCycleTime();
			pVirEcgLeads->SeteRefurbishDataRange(RD_MainSegmentData);	
		}
		//�Ƴ��粫����
		m_cExtrasystSignInterface.ModifyExtrasystRate( 0 );
	}

	//���ڳ�����������ĵ�ͼ�����޸�
	void CCardiogramBuild::DirectModifyCardiogramInDefibrState(const CECGParams * ptrParam)
	{
		//�Ƴ��粫����
		m_cExtrasystSignInterface.ModifyExtrasystRate( 0 );
		//���س�������ĵ�������ʱ��
		int nTime = GetDefibrillateActDelayTime();
		//end
		short nDataSize = m_cLeadsSampleBuff[0].GetSampleNum(nTime);
		I12LeadSample *pData = new I12LeadSample[nDataSize];
		::memset(pData, 0, sizeof(I12LeadSample)*nDataSize	);

		{
			boost::mutex::scoped_lock  lock(muSwapMutex);
			m_DataBuffer.WriteDataFromCurrReadPos(pData, nDataSize, NULL);
			//����Ŀǰ�������л�û�б��������ݴ�С
			m_DataBuffer.SetCurrNoneReadedNum(nDataSize);
		}
		delete [] pData;
		//�Ƴ���������ʱ���ڵ�����Ѫ��������
		m_cSpO2SignBuildInterface.RemoveSpO2TimeSigns(nTime);
		//---------------------------ֱ���޸��ĵ�ͼ����----------------------------------------------
		m_uArtifactNum = 0;
		{
			boost::mutex::scoped_lock  lock( muDirectEcgModifyMutex );
		    ICardiogramLeads *pVirEcgLeads = m_pParamFactory->CreateCardiogramLeadsInstance( ptrParam );
			bool bRtn = CreateCardiogram( pVirEcgLeads, /*out*/&m_cLeadsSampleBuff[0]);
			if( bRtn )
			{
				m_iCycleTime = pVirEcgLeads->GetCycleTime();
				pVirEcgLeads->SeteRefurbishDataRange(RD_MainSegmentData);
			}
			m_bCardiogramModifyed[0] = true;
			m_bCardiogramModifyed[1] = pVirEcgLeads->IsInitialSendDoubleSampleData();
		}
		//��������ڵ�����
		CombinNextCycleCurveData(true);
	}

	//ʵʩ��һ�γ���
	void CCardiogramBuild::DefibrillateAct()
	{
		//���س�������ĵ�������ʱ��
		int nTime = GetDefibrillateActDelayTime();
		//end
		short nDataSize = m_cLeadsSampleBuff[0].GetSampleNum(nTime);
		I12LeadSample *pData = new I12LeadSample[nDataSize];
		::memset(pData, 0, sizeof(I12LeadSample)*nDataSize	);

		//�Ƴ���������ʱ���ڵ�����Ѫ��������
		m_cSpO2SignBuildInterface.RemoveSpO2TimeSigns(nTime);
		boost::mutex::scoped_lock  lock(muSwapMutex);
		m_DataBuffer.WriteDataFromCurrReadPos(pData, nDataSize, NULL);
		delete [] pData;
	}

	//�����¸����ڵ�����
	void CCardiogramBuild::BuildNextCycleCardiogram()
	{
		boost::mutex::scoped_lock  lock( muDirectEcgModifyMutex );
		ICardiogramLeads *pVirEcgLeads = m_pParamFactory->GetCurrCardiogramLeadsInstance();
		if(m_eNextCycleState == NC_Change)
		{
			pVirEcgLeads->ReLoadCardiogramParam();
		}
		CreateCardiogram( pVirEcgLeads, /*out*/&m_cLeadsSampleBuff[1] );
		//��������ʱ��
		m_iCycleTime = pVirEcgLeads->GetCycleTime();
		//�������������ص�
		m_cLeadsSampleBuff[0].DirectOverlapLinkSampleData( m_cLeadsSampleBuff[1] );
		m_bCardiogramModifyed[0] = m_bCardiogramModifyed[1];
	}

	/*******************************************************************************/
	// �������ƣ� OnInitializeBuild
	// ���ܣ� ��ʼ���ĵ�ͼ������
	// ������ CECGParams *pECGParams:       
	// ����ֵ:  
	bool CCardiogramBuild::OnInitializeBuild(const CECGParams &cECGParams)
	{
		return InitializeBuild( cECGParams );
	}

	/*******************************************************************************
	//���ܣ���������ڵ�����
	//����ֵ:  ���ݵĳ���
	*********************************************************************************/
	short CCardiogramBuild::CombinNextCycleCurveData(bool changeInDefibr/*=false*/)
	{
		short dwRtnSize = m_cLeadsSampleBuff[0].GetSampleNum(m_iCycleTime);

		//��� Musular �� 50/60HZ ��Artifact����
		m_uArtifactNum = m_cLeadsSampleBuff[0].CombineArtifactData(m_cParams.m_eArtifact, m_iCycleTime, m_uArtifactNum);
		{
			boost::mutex::scoped_lock  lock(muEcgData);
			//�������������������ݵ�������
			I12LeadSample *pI12LeadSample = m_cLeadsSampleBuff[0].CombineLeadSamples( m_iCycleTime );
			m_DataBuffer.WriteData(pI12LeadSample,dwRtnSize);
		}
		//������ʣ���������ǰ��
		m_cLeadsSampleBuff[0].ClearEcgLeadCycleData( m_iCycleTime );
		//�����¸����ڵ�����
		BuildNextCycleCardiogram();
		return dwRtnSize;
	}


	// �������ƣ� CreateCardiogram
	// ����˵���� ����CECGParams�������ݣ�
	// ����ֵ�� 
	// ������ const CECGParams *ptrParam��
	// ������ CSample *pDestSample��
	bool CCardiogramBuild::CreateCardiogram(const CECGParams *ptrParam, /*out*/CEcgLeadSamples *pDestLeadsSample)
	{
		ICardiogramLeads * pVirEcgLeads = NULL;
		boost::mutex::scoped_lock  lock(muCardiogramParamMutex);
		if( ptrParam != NULL )
		{
			pVirEcgLeads = m_pParamFactory->CreateCardiogramLeadsInstance( ptrParam );
		}
		else
		{
			pVirEcgLeads = m_pParamFactory->GetCurrCardiogramLeadsInstance();
		}
		return CreateCardiogram( pVirEcgLeads, /*out*/pDestLeadsSample );
	}

	bool CCardiogramBuild::CreateCardiogram(ICardiogramLeads *pVirEcgLeads, /*out*/CEcgLeadSamples *pDestLeadsSample)
	{
		bool bScuccess = false;
		_eRefurbishDataRange eRange = pVirEcgLeads->GeteRefurbishDataRange();
		bScuccess = m_cCycleLeadsBuild.CreateCycleLeadsData( pVirEcgLeads, /*out*/pDestLeadsSample);
		//����ͬ����ʶ�������������ڵ���������Э��
		pVirEcgLeads->ResetSyncFlag();

		if(eRange != RD_NoChange)
			m_bCardiogramModifyed[1] = true;
		else
			m_bCardiogramModifyed[1] = false;
		pVirEcgLeads->SeteRefurbishDataRange(RD_NoChange);

		//����Ѫ��������ʱ��
		long lSpO2BeginTime = 0;
		long lCycleTime  = 0;
		if( pVirEcgLeads->GetSpO2BeginTimeToCardiogram( /*out*/ lSpO2BeginTime, /*out*/lCycleTime ) )
		{
			m_cSpO2SignBuildInterface.AddSpO2SignTime( lSpO2BeginTime, lCycleTime);
		}
		//end set SpO2 Begine Time
		return bScuccess ;
	}

	bool CCardiogramBuild::CreateExtrasyst(Extrasys eExtrasyst, /*out*/CEcgLeadSamples *pDestLeadsSample)
	{
		ICardiogramLeads *pVirEcgLeads = m_pParamFactory->GetCurrCardiogramLeadsInstance();
		int iCycleTime = pVirEcgLeads->GetCycleTime();
		bool bRtn = m_cCycleLeadsBuild.CreateExtrasystData(iCycleTime,eExtrasyst, pVirEcgLeads, /*out*/pDestLeadsSample);
		//����Ѫ��������ʱ��
		long lSpO2BeginTime = 0;
		long lPreSpO2SignTime = 0;
		long lCycleTime = 0;
		if( pVirEcgLeads->GetSpO2BeginTimeToExtrasyst(/*out*/lSpO2BeginTime, /*out*/lPreSpO2SignTime, /*out*/lCycleTime) )
		{
			m_cSpO2SignBuildInterface.AddSpO2SignTimeToExtrasyst( lSpO2BeginTime, lPreSpO2SignTime, lCycleTime);
		}
		//end set SpO2 Begine Time
		return bRtn;
	}

	// ��������ˢ�µ��ٶȣ��������ƶ����ٶȣ���λ������/�룩
	int CCardiogramBuild::GetMoveSpeed(void)
	{
		if(m_cParams.m_eSpeed == HS_Normal)
			return 25; //��׼����25����/��
		else if(m_cParams.m_eSpeed == HS_FAST)
			return 50; 
        BOOST_ASSERT(0);
		return 25;
	}

	//��Ӽ�����50/60HZʱ������
	void CCardiogramBuild::CombineArtifactData(Artifact eArtiface, float *fptrBegin, float *fptrEnd)
	{
	#define  PI    3.1415926
		switch(eArtiface)
		{
		case AF_None:
			{
				break;
			}
		case AF_Muscular: //�������
			{
				unsigned int uCycleNum = 0;
				float *fValuePtr = GetTriangleCycleData(30,uCycleNum);
				for(; fptrBegin < fptrEnd; ++fptrBegin)
				{
					float df = 0.0f;
					*fptrBegin += 0.07f * fValuePtr[m_uArtifactNum%uCycleNum] * (1+sin(2.0f*PI*13*m_uArtifactNum*0.0025f));
					++m_uArtifactNum;
				}
				break;
			}
		case AF_Frequent: //50/60���ȵĸ���
			{
				for(; fptrBegin < fptrEnd; ++fptrBegin)
				{
					*fptrBegin += 0.15f * (1+sin(2.0f*PI*50*m_uArtifactNum*0.0025f));
					++m_uArtifactNum;
				}
				break;
			}
		}
	}

	float* CCardiogramBuild::GetTriangleCycleData(int nFrequent, unsigned int &uCycleNum)
	{
	#define  PI    3.1415926
		static float fValue[100];
		uCycleNum = 400/nFrequent;//���ڵĵ���
		bool bBeforeHalf = true;
		for(int i=1; i<= uCycleNum; ++i)
		{
			if(bBeforeHalf == true)
				fValue[i-1] = 2.0f*nFrequent*i*0.0025f;
			if(bBeforeHalf && fValue[i-1] > 1.0f)
			{
				bBeforeHalf = false;
			}
			if(bBeforeHalf == false)
			{//��һ�εĺ�������
				fValue[i-1] = 2.0f*nFrequent*(1.0f/nFrequent - i*0.0025f);
			}
		}
		return fValue;
	}

	//�жϼ�����Ѫ�����ź�; int iMilliTime:   ʱ�䣨0.1���룩
	void  CCardiogramBuild::JudgeSpO2Sign(ICardiogramLeads  *pVirEcgLeads, int  iMilliTime)
	{
		CVirCardiogramParam *pVirParam = pVirEcgLeads->GetEcgLeadParam( Lead_II );
		int nDifferMilliTime = 0; //���ʱ��
		int nCycleMilliTime  = 0; //����ʱ��
		int nSignState = m_cSpO2SignBuildInterface.JudgeSpO2Sign( iMilliTime, /*out*/nDifferMilliTime, /*out*/nCycleMilliTime );
		if( (nSignState & 0x02) )
		{
			//S����T����ʱ��
			int  nMilliTimeFromQtoS = pVirParam->GetPhaseTimeFromQtoS();
			int  nMilliTimeFromStoT = pVirParam->GetPhaseTimeFromStoT();
			nCycleMilliTime = pVirParam->GetCycleTime();
			if( (nMilliTimeFromQtoS + nMilliTimeFromStoT) < nCycleMilliTime && m_pPhysiologyStartSignPtr)
			{
				m_pPhysiologyStartSignPtr->OnStartPhysiologySimpleLoad(nDifferMilliTime, nMilliTimeFromQtoS, nMilliTimeFromStoT, nCycleMilliTime);
			}
		}
		bool   bHaveHeartSign = pVirParam->isHaveHeartStartSign();
		if( (nSignState & 0x01) ||  !bHaveHeartSign)
		{
			//���������źŷ���
			SendHeartStartSign( bHaveHeartSign );
		}
	}

	/*******************************************************************************/
	//���ܣ���ȡ���������ڵĸ�������������
	//������int iMilliTime:             ʱ�䣨0.1���룩
	//      I12LeadSample *pcBuffer:    ���صĸ�������������
	//����ֵ:  �������ݵĳ���
	unsigned long CCardiogramBuild::GetI12LeadEcgSimulateData(int iMilliTime, /*out*/I12LeadSample *pcBuffer/*=NULL*/)
	{
		unsigned long dwRtSize = m_cLeadsSampleBuff[0].GetSampleNum(iMilliTime);
		if(pcBuffer == NULL)
			return dwRtSize;

		boost::mutex::scoped_lock  lock(muSwapMutex);
		short dwRemainBuffNum = m_DataBuffer.GetNoneReadedNum();
		//�����ڵ����ݸ���
		unsigned long dwHalfCycleSize = m_cLeadsSampleBuff[0].GetSampleNum(m_iCycleTime/2);
		if( dwRemainBuffNum < 90 || (m_iCycleTime >= 7000 && dwRemainBuffNum < dwHalfCycleSize) ) 
		{
			//��������
			UpdateShowHR( m_pParamFactory->GetCurrCardiogramLeadsInstance() );
			//��Ҫ���������ڵ�����
			CombinNextCycleCurveData();
		}
		short dwActiveNum = 0;//ʵ�ʷ��ص�������
		m_DataBuffer.ReadDataMovePtr(pcBuffer,(short)dwRtSize,&dwActiveNum);
		if( !m_bClearWatchLink && !m_bLinkWatchEcg )
		{
			::memset( pcBuffer, 0, sizeof(I12LeadSample) * dwActiveNum );
		}
		BOOST_ASSERT(dwActiveNum == dwRtSize);
		if( m_pParamFactory != NULL )
		{
			boost::mutex::scoped_lock  lock(muCardiogramParamMutex);
			ICardiogramLeads  *pVirEcgLeads = m_pParamFactory->GetCurrCardiogramLeadsInstance();
			if( pVirEcgLeads != NULL )
			{
				//�жϼ�����Ѫ�����ź�
				JudgeSpO2Sign( pVirEcgLeads, iMilliTime);
				//end hjg 2007/3/18 ���
			}
		}
		return dwActiveNum;
	}

	/*******************************************************************************/
	// �������ƣ� DirectModifyECGHandle
	// ���ܣ� ֱ���޸��ĵ�ͼ
	// ������ CECGParams *pECGParams
	//ע�� ���ĵ�ͼBuild��ʼ������ʱҲ�ô˺���
	// ����ֵ:  
	void CCardiogramBuild::DirectModifyECGHandle(const CECGParams &cECGParams)
	{
		if( !m_bInitialed )
		{
			InitializeBuild( cECGParams );
		}
		else
		{
			DirectModifyCardiogram( &cECGParams );
		}
	}

	/*******************************************************************************/
	// �������ƣ� ModifyECGInDefibrEventHandle
	// ���ܣ� ��Ϊ�������޸Ĳ���
	// ������ CECGParams *pECGParams
	// ����ֵ:  
	void CCardiogramBuild::ModifyECGInDefibrEventHandle(const CECGParams *pECGParams)
	{
		int  nDelayTimeByDefibr = GetDefibrillateActDelayTime()/10;
		if( pECGParams == NULL )
		{
			//ʵʩ��һ�γ���
			DefibrillateAct();

			m_cInterfaceMutex.Lock();
			if( m_pShowECGUpdate != NULL )
			{
				int nHR  = m_pParamFactory->GetCurrCardiogramLeadsInstance()->Get_iRhythmHR();
				m_pShowECGUpdate->OnShowECGRateInDefib(nHR, nDelayTimeByDefibr);
			}
			m_cInterfaceMutex.Unlock();
		}
		else
		{
			//���ڳ�����������ĵ�ͼ�����޸ģ������ݴ˲������޸ĸ�����Ԫͼ�κ������ʽ
			DirectModifyCardiogramInDefibrState( pECGParams );
			if( m_pShowECGUpdate != NULL )
			{
				//int nHR  = m_pParamFactory->GetCurrCardiogramParamInstance()->GetRhythmHR();
				std::string  strRhythm = IRhythmRule::GetstrBasicRhythm(pECGParams->m_eBasicRm);
				std::string  strExtrasys ;
				if( pECGParams->m_dwField & PM_EXTRASYS )
				{
					strExtrasys = IRhythmRule::GetstrExtrasys( pECGParams->m_eExtrasys );
				}
				m_pShowECGUpdate->OnShowECGNameInDefib( strRhythm, strExtrasys, pECGParams->m_iHR, pECGParams->m_bEMD, nDelayTimeByDefibr);
			}
			m_cInterfaceMutex.Unlock();
		}
	}
	
	/*******************************************************************************/
	// �������ƣ� ModifyECGHandle
	// ���ܣ� �޸��ĵ�ͼ
	// ������ CECGParams *pECGParams:       
	// ����ֵ:  
	void CCardiogramBuild::ModifyECGHandle(const CECGParams &cECGParams)
	{
		boost::mutex::scoped_lock  lock( muDirectEcgModifyMutex );
		ICardiogramLeads *pVirEcgLeads = m_pParamFactory->CreateCardiogramLeadsInstance( &cECGParams );
		if( CreateCardiogram(pVirEcgLeads, /*out*/&m_cLeadsSampleBuff[0]) )
		{
			m_iCycleTime = pVirEcgLeads->GetCycleTime();
			pVirEcgLeads->SeteRefurbishDataRange( RD_MainSegmentData );
		}
		m_bCardiogramModifyed[0] = m_bCardiogramModifyed[1] = true;
		m_cParams = cECGParams;
	}

	//��������
	void CCardiogramBuild::UpdateShowHR(ICardiogramLeads  *pVirEcgLeads)
	{
		m_cInterfaceMutex.Lock();
		if( m_pShowECGUpdate != NULL && pVirEcgLeads )
		{
			CVirCardiogramParam *pVirParam = pVirEcgLeads->GetEcgLeadParam( Lead_II );
			m_pShowECGUpdate->OnShowECGRate( pVirParam->GetRhythmHR() );
		}
		m_cInterfaceMutex.Unlock();
	}

	//�����Ƿ�����ĵ����Ӽ��
	void CCardiogramBuild::Set_IsClearEcgWatchLink(bool bClear)
	{
		m_bClearWatchLink  = bClear;
		m_cInterfaceMutex.Lock();
		if( m_pShowECGUpdate != NULL )
		{
			if( IsShowEcgByLinkState() )
			{
				m_pShowECGUpdate->OnAllLinkUpdateShow();
			}
			else 
			{
				m_pShowECGUpdate->OnAllUnLinkUpdateShow();
			}
		}
		m_cInterfaceMutex.Unlock();
		{
			boost::mutex::scoped_lock  lock(muHeartStartSign);
			if( m_pHeartStartSignAgg != NULL )
			{
				m_pHeartStartSignAgg->OnWatchHeartStartSign( IsShowEcgByLinkState() );
			}
		}
	}

	//�����ĵ����Ӽ��״̬
	void CCardiogramBuild::Set_EcgWatchLinkState(bool bLinking)
	{
		if( m_bLinkWatchEcg != bLinking )
		{
			m_bLinkWatchEcg   = bLinking;
			m_cInterfaceMutex.Lock();
			if( m_pShowECGUpdate != NULL )
			{
				if( IsShowEcgByLinkState() )
				{
					m_pShowECGUpdate->OnAllLinkUpdateShow();
				}
				else 
				{
					m_pShowECGUpdate->OnAllUnLinkUpdateShow();
				}
			}
			m_cInterfaceMutex.Unlock();
			{
				boost::mutex::scoped_lock  lock(muHeartStartSign);
				if( m_pHeartStartSignAgg != NULL )
				{
					m_pHeartStartSignAgg->OnWatchHeartStartSign( IsShowEcgByLinkState() );
				}
			}
		}
	}

	//�����ĵ�����״̬�������Ƿ���ʾ�ĵ�����
	bool CCardiogramBuild::IsShowEcgByLinkState()
	{
		if( m_bClearWatchLink || m_bLinkWatchEcg )
		{
			return true;
		}
		return false;
	}

	//�������������źŽӿ�
	void CCardiogramBuild::InsertHeartStartSignPtr(IHeartStartSign  *pInterface)
	{
		boost::mutex::scoped_lock  lock(muHeartStartSign);
		if( m_pHeartStartSignAgg == NULL )
		{
			m_pHeartStartSignAgg  = pInterface;
		}
		else
		{
			m_pHeartStartSignAgg->SetNextInterfacePtr( pInterface );
		}
		if( pInterface != NULL )
		{
			pInterface->WatchHeartStartSign( true );
		}
	}

	void CCardiogramBuild::RemoveHeartStartSignPtr(IHeartStartSign  *pInterface)
	{
		boost::mutex::scoped_lock  lock(muHeartStartSign);
		if( m_pHeartStartSignAgg != NULL )
		{
			m_pHeartStartSignAgg = (IHeartStartSign *)IBedirecteLinksVir::RemoveInterfacePtr(m_pHeartStartSignAgg, pInterface);
		}
		if( pInterface != NULL )
		{
			pInterface->WatchHeartStartSign( false );
		}
	}

	//���������źŷ���
	void CCardiogramBuild::SendHeartStartSign( bool bHaveHeartSign )
	{
		boost::mutex::scoped_lock  lock(muHeartStartSign);
		if( m_pHeartStartSignAgg != NULL )
		{
			ICardiogramLeads  *pVirEcgLeads = m_pParamFactory->GetCurrCardiogramLeadsInstance();
			m_pHeartStartSignAgg->OnHeartStartSignHandle(pVirEcgLeads->Get_eCurrentRhythm(), pVirEcgLeads->GetCycleTime(), bHaveHeartSign);
		}
	}

}}}
