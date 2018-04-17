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
		m_bInitialed             = false;//末初始化

		m_uArtifactNum           = 0;
		m_pPtrTransportLayer     = NULL;
		m_pPhysiologyStartSignPtr = NULL;
		m_eNextCycleState        = NC_Rhythm;
		m_iCycleTime             = 0;

		m_bCardiogramModifyed[0] = m_bCardiogramModifyed[1] = true;

		m_pParamFactory         = NULL;
		m_pHeartStartSignAgg    = NULL;
		m_bClearWatchLink       = true; //忽略心电链接检查
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

	//关闭心电图构造器
	void CCardiogramBuild::CloseCardiogramBuild()
	{
		if( m_pParamFactory != NULL )
		{
			delete m_pParamFactory;
			m_pParamFactory = NULL;
		}
		m_bInitialed             = false;//末初始化

		m_uArtifactNum           = 0;
		m_pPtrTransportLayer     = NULL;
		m_pPhysiologyStartSignPtr = NULL;
		m_eNextCycleState        = NC_Rhythm;
		m_iCycleTime             = 0;
		m_bCardiogramModifyed[0] = m_bCardiogramModifyed[1] = true;
	}

	/*******************************************************************************/
	// 函数名称： SetEcgBuildRelateInterfacesPtr
	// 功能： 设置心电图构造相关指针
	// 参数： 
	//        ITransportOrderIrpToSimulator *pPtrTransportLayer:
	//        IPhysiologyStartSign *pSpO2SignPtr:  
	//        SimulatePatientType ePateintType:    模拟人类别
	// 返回值: 
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
		short   sConduct = 0;     //传导设置
		if( cECGParams.m_dwField & PM_CONDUCT)
		{
			m_cParams.m_dwField |= PM_CONDUCT;
			sConduct = m_cParams.m_sConduct  = cECGParams.m_sConduct;

		}
		short   sExtendParam = 0;  //扩展参数值
		if( cECGParams.m_dwField & PM_EXTEND )
		{
			m_cParams.m_dwField |= PM_EXTEND;
			sExtendParam = m_cParams.m_sExtendParam = cECGParams.m_sExtendParam;
		}
		//--------------------------------------------------------------------------------------------------------
		m_pHeartStartSignAgg  = NULL;
		//移除血氧启动时间项
		m_cSpO2SignBuildInterface.ResetSpO2TimeSignList();
		//end hjg 2007/3/18 添加
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
		m_bInitialed = true; //已初始化

		return bRtn;
	}

	//返回除颤引起的电流饱和时间
	int CCardiogramBuild::GetDefibrillateActDelayTime()
	{
		if(m_cParams.m_eBasicRm == BR_AFib)
			return 30800; //3.08秒
		return 35800;     //3.58秒
	}

	//直接修改心电图参数 2006/11/2 hjg 添加
	void CCardiogramBuild::DirectModifyCardiogram(const CECGParams * ptrParam)
	{
		//移除血氧启动时间项
		m_cSpO2SignBuildInterface.ResetSpO2TimeSignList();
		//end hjg 2007/3/18 添加
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
		//移除早搏设置
		m_cExtrasystSignInterface.ModifyExtrasystRate( 0 );
	}

	//由于除颤而引起的心电图参数修改
	void CCardiogramBuild::DirectModifyCardiogramInDefibrState(const CECGParams * ptrParam)
	{
		//移除早搏设置
		m_cExtrasystSignInterface.ModifyExtrasystRate( 0 );
		//返回除颤引起的电流饱和时间
		int nTime = GetDefibrillateActDelayTime();
		//end
		short nDataSize = m_cLeadsSampleBuff[0].GetSampleNum(nTime);
		I12LeadSample *pData = new I12LeadSample[nDataSize];
		::memset(pData, 0, sizeof(I12LeadSample)*nDataSize	);

		{
			boost::mutex::scoped_lock  lock(muSwapMutex);
			m_DataBuffer.WriteDataFromCurrReadPos(pData, nDataSize, NULL);
			//设置目前缓冲区中还没有被读的数据大小
			m_DataBuffer.SetCurrNoneReadedNum(nDataSize);
		}
		delete [] pData;
		//移除电流饱和时间内的所有血氧启动点
		m_cSpO2SignBuildInterface.RemoveSpO2TimeSigns(nTime);
		//---------------------------直接修改心电图参数----------------------------------------------
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
		//组合下周期的数据
		CombinNextCycleCurveData(true);
	}

	//实施了一次除颤
	void CCardiogramBuild::DefibrillateAct()
	{
		//返回除颤引起的电流饱和时间
		int nTime = GetDefibrillateActDelayTime();
		//end
		short nDataSize = m_cLeadsSampleBuff[0].GetSampleNum(nTime);
		I12LeadSample *pData = new I12LeadSample[nDataSize];
		::memset(pData, 0, sizeof(I12LeadSample)*nDataSize	);

		//移除电流饱和时间内的所有血氧启动点
		m_cSpO2SignBuildInterface.RemoveSpO2TimeSigns(nTime);
		boost::mutex::scoped_lock  lock(muSwapMutex);
		m_DataBuffer.WriteDataFromCurrReadPos(pData, nDataSize, NULL);
		delete [] pData;
	}

	//创建下个周期的数据
	void CCardiogramBuild::BuildNextCycleCardiogram()
	{
		boost::mutex::scoped_lock  lock( muDirectEcgModifyMutex );
		ICardiogramLeads *pVirEcgLeads = m_pParamFactory->GetCurrCardiogramLeadsInstance();
		if(m_eNextCycleState == NC_Change)
		{
			pVirEcgLeads->ReLoadCardiogramParam();
		}
		CreateCardiogram( pVirEcgLeads, /*out*/&m_cLeadsSampleBuff[1] );
		//设置周期时间
		m_iCycleTime = pVirEcgLeads->GetCycleTime();
		//将两采样数据重叠
		m_cLeadsSampleBuff[0].DirectOverlapLinkSampleData( m_cLeadsSampleBuff[1] );
		m_bCardiogramModifyed[0] = m_bCardiogramModifyed[1];
	}

	/*******************************************************************************/
	// 函数名称： OnInitializeBuild
	// 功能： 初始化心电图构造器
	// 参数： CECGParams *pECGParams:       
	// 返回值:  
	bool CCardiogramBuild::OnInitializeBuild(const CECGParams &cECGParams)
	{
		return InitializeBuild( cECGParams );
	}

	/*******************************************************************************
	//功能：组合下周期的数据
	//返回值:  数据的长度
	*********************************************************************************/
	short CCardiogramBuild::CombinNextCycleCurveData(bool changeInDefibr/*=false*/)
	{
		short dwRtnSize = m_cLeadsSampleBuff[0].GetSampleNum(m_iCycleTime);

		//添加 Musular 或 50/60HZ 的Artifact数据
		m_uArtifactNum = m_cLeadsSampleBuff[0].CombineArtifactData(m_cParams.m_eArtifact, m_iCycleTime, m_uArtifactNum);
		{
			boost::mutex::scoped_lock  lock(muEcgData);
			//拷贝完整周期心律数据到缓冲区
			I12LeadSample *pI12LeadSample = m_cLeadsSampleBuff[0].CombineLeadSamples( m_iCycleTime );
			m_DataBuffer.WriteData(pI12LeadSample,dwRtnSize);
		}
		//将后面剩余的数据向前移
		m_cLeadsSampleBuff[0].ClearEcgLeadCycleData( m_iCycleTime );
		//创建下个周期的数据
		BuildNextCycleCardiogram();
		return dwRtnSize;
	}


	// 函数名称： CreateCardiogram
	// 功能说明： 根据CECGParams创建数据，
	// 返回值： 
	// 参数： const CECGParams *ptrParam：
	// 参数： CSample *pDestSample：
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
		//重置同步标识符，用于下周期导联构建的协调
		pVirEcgLeads->ResetSyncFlag();

		if(eRange != RD_NoChange)
			m_bCardiogramModifyed[1] = true;
		else
			m_bCardiogramModifyed[1] = false;
		pVirEcgLeads->SeteRefurbishDataRange(RD_NoChange);

		//设置血氧启动的时间
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
		//设置血氧启动的时间
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

	// 返回数据刷新的速度，即滑块移动的速度（单位：毫米/秒）
	int CCardiogramBuild::GetMoveSpeed(void)
	{
		if(m_cParams.m_eSpeed == HS_Normal)
			return 25; //标准的是25毫米/秒
		else if(m_cParams.m_eSpeed == HS_FAST)
			return 50; 
        BOOST_ASSERT(0);
		return 25;
	}

	//添加肌颤或50/60HZ时的数据
	void CCardiogramBuild::CombineArtifactData(Artifact eArtiface, float *fptrBegin, float *fptrEnd)
	{
	#define  PI    3.1415926
		switch(eArtiface)
		{
		case AF_None:
			{
				break;
			}
		case AF_Muscular: //肌肉颤动
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
		case AF_Frequent: //50/60赫兹的干扰
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
		uCycleNum = 400/nFrequent;//周期的点数
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
			{//用一段的函数计算
				fValue[i-1] = 2.0f*nFrequent*(1.0f/nFrequent - i*0.0025f);
			}
		}
		return fValue;
	}

	//判断及启动血氧的信号; int iMilliTime:   时间（0.1豪秒）
	void  CCardiogramBuild::JudgeSpO2Sign(ICardiogramLeads  *pVirEcgLeads, int  iMilliTime)
	{
		CVirCardiogramParam *pVirParam = pVirEcgLeads->GetEcgLeadParam( Lead_II );
		int nDifferMilliTime = 0; //相差时间
		int nCycleMilliTime  = 0; //周期时间
		int nSignState = m_cSpO2SignBuildInterface.JudgeSpO2Sign( iMilliTime, /*out*/nDifferMilliTime, /*out*/nCycleMilliTime );
		if( (nSignState & 0x02) )
		{
			//S波到T波的时间
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
			//心脏跳动信号发送
			SendHeartStartSign( bHaveHeartSign );
		}
	}

	/*******************************************************************************/
	//功能：获取滑块区域内的各导联曲线数据
	//参数：int iMilliTime:             时间（0.1豪秒）
	//      I12LeadSample *pcBuffer:    返回的各导联曲线数据
	//返回值:  曲线数据的长度
	unsigned long CCardiogramBuild::GetI12LeadEcgSimulateData(int iMilliTime, /*out*/I12LeadSample *pcBuffer/*=NULL*/)
	{
		unsigned long dwRtSize = m_cLeadsSampleBuff[0].GetSampleNum(iMilliTime);
		if(pcBuffer == NULL)
			return dwRtSize;

		boost::mutex::scoped_lock  lock(muSwapMutex);
		short dwRemainBuffNum = m_DataBuffer.GetNoneReadedNum();
		//半周期的数据个数
		unsigned long dwHalfCycleSize = m_cLeadsSampleBuff[0].GetSampleNum(m_iCycleTime/2);
		if( dwRemainBuffNum < 90 || (m_iCycleTime >= 7000 && dwRemainBuffNum < dwHalfCycleSize) ) 
		{
			//更新心率
			UpdateShowHR( m_pParamFactory->GetCurrCardiogramLeadsInstance() );
			//需要生成下周期的数据
			CombinNextCycleCurveData();
		}
		short dwActiveNum = 0;//实际返回的数据数
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
				//判断及启动血氧的信号
				JudgeSpO2Sign( pVirEcgLeads, iMilliTime);
				//end hjg 2007/3/18 添加
			}
		}
		return dwActiveNum;
	}

	/*******************************************************************************/
	// 函数名称： DirectModifyECGHandle
	// 功能： 直接修改心电图
	// 参数： CECGParams *pECGParams
	//注： 对心电图Build初始化构造时也用此函数
	// 返回值:  
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
	// 函数名称： ModifyECGInDefibrEventHandle
	// 功能： 因为除颤而修改波形
	// 参数： CECGParams *pECGParams
	// 返回值:  
	void CCardiogramBuild::ModifyECGInDefibrEventHandle(const CECGParams *pECGParams)
	{
		int  nDelayTimeByDefibr = GetDefibrillateActDelayTime()/10;
		if( pECGParams == NULL )
		{
			//实施了一次除颤
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
			//由于除颤而引起的心电图参数修改，并根据此参数，修改各个单元图形和组合形式
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
	// 函数名称： ModifyECGHandle
	// 功能： 修改心电图
	// 参数： CECGParams *pECGParams:       
	// 返回值:  
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

	//更新心率
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

	//设置是否忽略心电链接检查
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

	//设置心电链接检查状态
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

	//根据心电链接状态，返回是否显示心电数据
	bool CCardiogramBuild::IsShowEcgByLinkState()
	{
		if( m_bClearWatchLink || m_bLinkWatchEcg )
		{
			return true;
		}
		return false;
	}

	//插入心脏启动信号接口
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

	//心脏跳动信号发送
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
