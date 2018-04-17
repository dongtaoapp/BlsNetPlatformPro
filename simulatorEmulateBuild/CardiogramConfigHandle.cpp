#include <boost/format.hpp>
#include <boost/foreach.hpp>
#include <boost/assert.hpp>
#include <boost/lexical_cast.hpp>
#include ".\CardiogramConfigHandle.h"


namespace jysoft { namespace simulator { namespace ecg {

	CCardiogramConfigHandle::CCardiogramConfigHandle(void)
	{
	}

	CCardiogramConfigHandle::~CCardiogramConfigHandle(void)
	{
		m_lstDataOperatorSegment.clear();
		m_lstCombineSegment.clear();
		//移除Map内的元素
		auto p = m_SampleDataMap.begin();
		for (p; p != m_SampleDataMap.end(); ++p)
		{
			delete p->second;
		}
		m_SampleDataMap.clear();
	}

	bool CCardiogramConfigHandle::LoadConfigFile(CVirCardiogramParam *pVirParam, CSample *pDstSample)
	{
		bool bRtn = false;
		m_lstDataOperatorSegment.clear();
		m_lstCombineSegment.clear();
		//移除Map内的元素
		auto p = m_SampleDataMap.begin();
		for (p; p != m_SampleDataMap.end(); ++p)
		{
			delete p->second;
		}
		m_SampleDataMap.clear();
		try
		{
			LPSTREAM lpStream = pVirParam->GetMakefileStream();
			if(lpStream == NULL)
				return false;
			static char cData[1024*6];
			ULONG uReadSize = 0;
			lpStream->Read(cData,1024*6,&uReadSize);
			BOOST_ASSERT(uReadSize <= 1024*6);
			lpStream->Release();
			//解析配置文件
			bRtn = ParseConfigXML(cData, uReadSize,pVirParam,pDstSample);
		}
		catch(...)
		{
			bRtn = false;
		}
		return bRtn;
	}

	bool CCardiogramConfigHandle::ParseConfigXML(char *pPtr, long dwSize, CVirCardiogramParam *pVirParam, CSample *pDstSample)
	{
		bool bRtn = false;
		//移除上次解析时生成的数据
		xmlRoot.reset();
		pugi::xml_parse_result result = xmlRoot.load_buffer(pPtr, dwSize);
		//解析传入的文本
		if( result )
		{
			cycleNode = xmlRoot.first_element_by_path( "配置/周期数据" );
			if( !cycleNode.empty() )
			{
				//根据配置文件创建数据(考虑速度方面，建议用线程)
				bRtn = ReCreateMainCycleData(pVirParam, pDstSample);
			}
		}
		return bRtn;
	}

	//解析数据段
	bool CCardiogramConfigHandle::ParseDataXMLSegment(CVirCardiogramParam *pVirParam)
	{
		for (pugi::xml_node_iterator it = cycleNode.begin(); it != cycleNode.end(); ++it)
		{
			std::string  cap = it->name();
			if( cap == "数据段" )
			{
				CSample *pNewSample = CreateSampleFromSegmentXML(*it, pVirParam);
				if(pNewSample == NULL)
				{
					return false;
				}
			}
		}
		return true;
	}

	bool CCardiogramConfigHandle::ParseDataOperatorXMLSegment(CVirCardiogramParam *pVirParam)
	{
		//将旧的数据操作段都移除
		BOOST_FOREACH(auto pSample, m_lstDataOperatorSegment)
		{
			m_SampleDataMap.erase(pSample->GetSampleID());
			delete pSample;
		}
		m_lstDataOperatorSegment.clear();
		//end hjg
		for (pugi::xml_node_iterator it = cycleNode.begin(); it != cycleNode.end(); ++it)
		{
			if( std::string(it->name()) == "数据操作段" )
			{
				CSample *pNewSample = CreateSampleFromSegmentXML(*it, pVirParam);
				if(pNewSample == NULL)
					return false;
			}
		}
		return true;
	}

	//解析组合段
	bool CCardiogramConfigHandle::ParseCombineXMLSegment(CVirCardiogramParam *pVirParam)
	{
		//将旧的组合段都移除
		BOOST_FOREACH(auto pSample, m_lstCombineSegment)
		{
			m_SampleDataMap.erase(pSample->GetSampleID());
			delete pSample;
		}
		m_lstCombineSegment.clear();
		//end hjg
		for (pugi::xml_node_iterator it = cycleNode.begin(); it != cycleNode.end(); ++it)
		{
			if( std::string(it->name()) == "组合段" )
			{
				CSample *pNewSample = CreateSampleFromCombineXML(*it, pVirParam);
				if(pNewSample == NULL)
					return false;
			}
		}
		return true;
	}

	//解析基数据段
	bool CCardiogramConfigHandle::ParseBasicSegmentData(CVirCardiogramParam *pVirParam, /*out*/CSample **pDstSample)
	{
		for (pugi::xml_node_iterator it = cycleNode.begin(); it != cycleNode.end(); ++it)
		{
			if( std::string(it->name()) == "基数据段" )
			{
				*pDstSample= CreateBasicSegmentData(*it, pVirParam);
				if(*pDstSample == NULL)
					return false;
				return true;
			}
		}
		return false;
	}

	//生成主段
	bool CCardiogramConfigHandle::CreateMainCycleData(CVirCardiogramParam *pVirParam,/*out*/CSample *pDstSample)
	{
		pDstSample->ResetSample();
		std::list<CSample *> lstSamples;
		bool bRtn = false;
		//心电周期段
		pugi::xml_node ecgSegNode = cycleNode.first_element_by_path("./心电周期段");
		if( !ecgSegNode.empty() )
		{
			for (pugi::xml_node_iterator it = ecgSegNode.begin(); it != ecgSegNode.end(); ++it)
			{
				if( std::string(it->name()) == "数据段")
				{
					CSample *pSample = NULL;
					boost::unordered_map<int, CSample *>::const_iterator pos = m_SampleDataMap.find(it->text().as_int());
					if( pos != m_SampleDataMap.end() )
					{
						pSample = pos->second;
					}
					else
					{
						return false;
					}
					lstSamples.push_back(pSample);
				}
			}
			bRtn = true;
		}
		//将各段的数据整合起来
		BOOST_FOREACH(auto pSamplePtr, lstSamples)
		{
			if(pDstSample->IsEmpty())
				pDstSample->Clone(pSamplePtr);
			else
				pDstSample->DirectLinkSampleData(pSamplePtr);
		}
		lstSamples.clear();
		int iCycleTime = pVirParam->GetCycleTime();
		//检查段内的数据代表的时间是否等于周期时间
		int nSumTime = pDstSample->GetSampleSumTime();
		if( iCycleTime > nSumTime )
		{
			//延长
			pDstSample->AddSampleData(nSumTime, iCycleTime- nSumTime, 0.0f);
		}
		//---------------------------------------------------
		CSample *pBasicSegmentSample = NULL;//基数据段
		if(ParseBasicSegmentData(pVirParam,&pBasicSegmentSample))
		{
			pDstSample->DirectOverlapLinkSampleData(pBasicSegmentSample);
			delete pBasicSegmentSample;
		}
		return bRtn;
	}

	bool CCardiogramConfigHandle::ReCreateMainCycleData(CVirCardiogramParam *pVirParam,/*out*/CSample *pDstSample)
	{
		m_lstDataOperatorSegment.clear();
		m_lstCombineSegment.clear();
		//移除Map内的元素
		auto p = m_SampleDataMap.begin();
		for (p; p != m_SampleDataMap.end(); ++p)
		{
			delete p->second;
		}
		m_SampleDataMap.clear();
		//解析数据段
		bool bRtn = ParseDataXMLSegment(pVirParam);
		//解析数据操作段
		if(bRtn == true)
			bRtn = ParseDataOperatorXMLSegment(pVirParam);
		//解析组合段
		if(bRtn == true)
			bRtn = ParseCombineXMLSegment(pVirParam);
		//生成主段
		if(bRtn == true)
			bRtn = CreateMainCycleData(pVirParam,pDstSample);
		return bRtn;
	}

	//生成早波段数据
	bool CCardiogramConfigHandle::CreateExtrasystData(int iCycleTime, Extrasys eExtrasyst, CVirCardiogramParam *pVirParam, /*in,out*/CSample *pDstSample)
	{	
		//早波段
		pugi::xml_node extraSegNode = cycleNode.first_element_by_path("./早波");
		if( !extraSegNode.empty() )
		{
			CSample *pExtrasystSample = CreateBasicExtrasystSample(eExtrasyst, extraSegNode, pVirParam);
			if(pExtrasystSample != NULL)
			{
				//加载主周期段数据
				if(eExtrasyst != PAC && eExtrasyst != PJC)
				{//此两种情况不需要修改
					ModifyMainCycleDataBaseExtrasyst(iCycleTime,extraSegNode,pVirParam,pDstSample);
				}
				pDstSample->DirectOverlapLinkSampleData(pExtrasystSample);
			}
			delete pExtrasystSample;
		}
		else
		{
			BOOST_ASSERT(0);
			return false;
		}
		if(pDstSample->GetSampleSumTime() < iCycleTime)
			pDstSample->AddSampleData(pDstSample->GetSampleSumTime(),iCycleTime-pDstSample->GetSampleSumTime(),0.0f);
		return true;
	}

	//根据早波的不同，修改主心电图数据段
	bool CCardiogramConfigHandle::ModifyMainCycleDataBaseExtrasyst(int iCycleTime , xml_node segmentNode, CVirCardiogramParam *pVirParam, /*in,out*/CSample *pDstSample)
	{
		int nSumTime = pVirParam->GetCycleTime();
		//nSumTime是iCycleTime的倍数
		//ASSERT(!(nSumTime%iCycleTime));
		for(int i = 1;i< int(1.0f*nSumTime/iCycleTime + 0.1);++i)
		{//注：有10%的误差存在
			CSample *pPSample = NULL;
			boost::unordered_map<int, CSample *>::const_iterator pos = m_SampleDataMap.find(1);
			if( pos != m_SampleDataMap.end() )
			{//注：P波的数据段的ID号为1
				pPSample = pos->second;
				CSample cTmpSample;
				cTmpSample.Clone(pPSample);	
				cTmpSample.HoriIntervalLinkSampleData(i*iCycleTime,0.0f,false);
				int nPSampleTime = cTmpSample.GetSampleSumTime();
				cTmpSample.AddSampleData(nPSampleTime,(i+1)*iCycleTime-nPSampleTime,0.0f);
				pDstSample->DirectOverlapLinkSampleData(&cTmpSample);
			}
		}
		return true;
	}

	CSample * CCardiogramConfigHandle::CreateBasicExtrasystSample(Extrasys eExtrasyst, pugi::xml_node segmentNode, CVirCardiogramParam *pVirParam)
	{
		CSample *pNewSample = NULL;
		//加载采样数据
		std::string   strFile;
		bool bParam = false;
		if(GetLoadSampleFileName(segmentNode, strFile, bParam))
		{
			if(bParam == true)
			{//得到实际的名称，如果strFile为空，表示为本来的心电图数据
				strFile = pVirParam->GetExtrasystFileName(eExtrasyst,strFile);
			}
			pNewSample = new CSample();
			//从文件中加载数据
			if(!LoadSampleFromFile(pNewSample,strFile,pVirParam) && !bParam)
			{
				delete pNewSample;
				pNewSample = NULL;
			}
		}
		else
            BOOST_ASSERT(0);
		if(pNewSample != NULL)
		{
			bool bRtn = true;
			if(pNewSample->IsEmpty())
			{
				bRtn = ReCreateMainCycleData(pVirParam, pNewSample);
			}
			if(bRtn)
			{
				//按配置文件描述的过程，对原始采样数据进行处理
				BasicOperatorSampleDataFormXML(pNewSample, segmentNode, pVirParam);
			}
			else
			{
				delete pNewSample;
				pNewSample = NULL;
			}
		}
		return pNewSample;
	}

	//根据数据段的ID号，找出此解析段
	xml_node CCardiogramConfigHandle::FindSegmentFromID(xml_node cycleNode, int iID)
	{
		for (pugi::xml_node_iterator it = cycleNode.begin(); it != cycleNode.end(); ++it)
		{
			std::string cap = it->name();
			if( cap == "数据段" || cap == "组合段" || cap == "数据操作段")
			{
				xml_node  node = it->first_element_by_path("./ID");
				if( !node.empty() )
				{
					if(node.text().as_int() == iID)
						return *it;
				}
			}
		}
		return xml_node();
	}

	//根据段的配置，生成采样数据
	CSample * CCardiogramConfigHandle::CreateSampleFromSegmentXML(pugi::xml_node segmentNode, CVirCardiogramParam *pVirParam)
	{
		CSample *pNewSample = NULL;
		//得到数据段的ID号
		int dwID = 0;
		if(!GetSegmentID(segmentNode, dwID))
			return false;
		boost::unordered_map<int, CSample *>::const_iterator pos = m_SampleDataMap.find(dwID);
		if( pos == m_SampleDataMap.end() )
		{
			//加载采样数据
			std::string  strFile;
			bool bParam = false;
			if(GetLoadSampleFileName(segmentNode, strFile, bParam))
			{
				if(bParam == true)
				{//得到实际的名称
					std::string strValue;
					if(!pVirParam->GetParamValue(strFile,strValue))
					{
                        BOOST_ASSERT(0);
						return false;
					}
					strFile = strValue;
				}
				pNewSample = new CSample(dwID);
				//从文件中加载数据
				if(!LoadSampleFromFile(pNewSample,strFile,pVirParam))
				{
					delete pNewSample;
					pNewSample = NULL;
				}
			}
			else 
			{
				int dwOriginID;
				if(GetLoadSampleOriginID(segmentNode, dwOriginID))
				{
					CSample *pOriginSample = NULL;
					pos = m_SampleDataMap.find(dwOriginID);
					if( pos != m_SampleDataMap.end() )
					{
						pOriginSample = pos->second;
					}
					if(pOriginSample == NULL)
					{//还没加载
						xml_node node = FindSegmentFromID(cycleNode,(int)dwOriginID);
						if( !node.empty() )
						{
							std::string cap = node.name();
							if(cap == "数据段" || cap == "数据操作段")
								pOriginSample = CreateSampleFromSegmentXML(node, pVirParam);
							else if(cap == "组合段")
								pOriginSample = CreateSampleFromCombineXML(node, pVirParam);
							else
								BOOST_ASSERT(0);
						}
					}
					if(pOriginSample != NULL)
					{
						pNewSample = new CSample(dwID);
						pNewSample->Clone(pOriginSample);
					}
				}
			}
			if(pNewSample != NULL)
			{
				//按配置文件描述的过程，对原始采样数据进行处理
				BasicOperatorSampleDataFormXML(pNewSample, segmentNode, pVirParam);
			}
		}
		else
		{
			pNewSample = pos->second;
		}
		if(pNewSample != NULL)
		{
			m_SampleDataMap[pNewSample->GetSampleID()] = pNewSample;
			if( std::string(segmentNode.name()) == "数据操作段")
			{//将数据操作段的数据加入到连表中
				std::list<CSample *>::const_iterator posFind = std::find(m_lstDataOperatorSegment.begin(), m_lstDataOperatorSegment.end(), pNewSample);
				if(posFind == m_lstDataOperatorSegment.end())
				{
					m_lstDataOperatorSegment.push_back(pNewSample);
				}
			}
		}
		return pNewSample;
	}
	//创建基数据段
	CSample * CCardiogramConfigHandle::CreateBasicSegmentData(xml_node segmentNode, CVirCardiogramParam *pVirParam)
	{
		CSample *pNewSample = NULL;
		//得到数据段的ID号
		int dwID = 0;
		if(!GetSegmentID(segmentNode, dwID))
			return false;
		//加载采样数据
		std::string  strFile;
		bool bParam = false;
		if(GetLoadSampleFileName(segmentNode, strFile,bParam))
		{
			if(bParam == true)
			{//得到实际的名称
				std::string  strValue;
				if(!pVirParam->GetParamValue(strFile,strValue))
				{
                    BOOST_ASSERT(0);
					return false;
				}
				strFile = strValue;
			}
			pNewSample = new CSample(dwID);
			//从文件中加载数据
			if(!LoadSampleFromFile(pNewSample,strFile,pVirParam))
			{
				delete pNewSample;
				pNewSample = NULL;
			}
		}
		else 
		{
			int dwOriginID;
			if(GetLoadSampleOriginID(segmentNode, dwOriginID))
			{
				CSample *pOriginSample = NULL;
				boost::unordered_map<int, CSample *>::const_iterator pos = m_SampleDataMap.find(dwOriginID);
				if( pos != m_SampleDataMap.end() )
				{
					pOriginSample = pos->second;
				}
				if(pOriginSample == NULL)
				{//还没加载
					xml_node node = FindSegmentFromID(cycleNode,(int)dwOriginID);
					if( !node.empty() )
					{
						std::string cap = node.name();
						if( cap == "数据段" || cap == "数据操作段")
							pOriginSample = CreateSampleFromSegmentXML(node, pVirParam);
						else if( cap == "组合段")
							pOriginSample = CreateSampleFromCombineXML(node, pVirParam);
						else
							BOOST_ASSERT(0);
					}
				}
				if(pOriginSample != NULL)
				{
					pNewSample = new CSample(dwID);
					pNewSample->Clone(pOriginSample);
				}
			}
		}
		if(pNewSample != NULL)
		{
			//按配置文件描述的过程，对原始采样数据进行处理
			BasicOperatorSampleDataFormXML(pNewSample, segmentNode, pVirParam);
			if(pNewSample->IsEmpty())
			{
				delete pNewSample;
				pNewSample = NULL;
			}
		}
		return pNewSample;
	}

	CSample * CCardiogramConfigHandle::CreateSampleFromCombineXML(pugi::xml_node combineNode, CVirCardiogramParam *pVirParam)
	{
		CSample *pNewSample = NULL;
		//得到数据段的ID号
		int dwID = 0;
		if(!GetSegmentID(combineNode, dwID))
			return false;
		boost::unordered_map<int, CSample *>::const_iterator pos = m_SampleDataMap.find(dwID);
		if( pos != m_SampleDataMap.end() )
		{
			pNewSample = pos->second;
		}
		else
		{
			for (pugi::xml_node_iterator it = combineNode.begin(); it != combineNode.end(); ++it)
			{
				if( std::string(it->name()) != "ID" )
				{
					if(!CombineSampleDataHandle(pNewSample,*it, pVirParam))
					{
						delete pNewSample;
						pNewSample = NULL;
					}
				}
			}
		}
		if(pNewSample != NULL)
		{
			m_SampleDataMap[pNewSample->GetSampleID()] = pNewSample;
			//将组合段的数据加入到连表中
			std::list<CSample *>::const_iterator posFind = std::find(m_lstCombineSegment.begin(), m_lstCombineSegment.end(), pNewSample);
			if(posFind == m_lstCombineSegment.end())
			{
				m_lstCombineSegment.push_back(pNewSample);
			}
		}
		return pNewSample;
	}

	//返回段的ID号
	bool CCardiogramConfigHandle::GetSegmentID(xml_node segmentNode, int &dwID)
	{
		for (pugi::xml_node_iterator it = segmentNode.begin(); it != segmentNode.end(); ++it)
		{
			if( std::string(it->name()) == "ID" )
			{
				dwID = it->text().as_int();
				return true;
			}
		}
		return false;
	}

	// 函数名称： GetLoadSampleFileName
	// 功能说明： 返回段数据的来源（文件名称）
	// 返回值： 
	// 参数： CMessMemory *pSegmentMess：
	// 参数： CString &strFileName：段数据的来源名称
	// 参数： bool &bParam：返回的来源名称是否代表变量，需要用对应的真实数值替代
	bool CCardiogramConfigHandle::GetLoadSampleFileName(xml_node segmentNode, std::string &strFileName,bool &bParam)
	{
		for (pugi::xml_node_iterator it = segmentNode.begin(); it != segmentNode.end(); ++it)
		{
			if( std::string(it->name()) == "文件名称" )
			{
				pugi::xml_node fileNode = it->first_child();
				if( fileNode.type() == node_pcdata )
				{
					strFileName = fileNode.value();
					bParam = false;
					return true;
				}
				else if( fileNode.type() == node_element )
				{
					strFileName = fileNode.text().as_string();
					bParam = true;
					return true;
				}
			}
		}
		return false;
	}

	// 函数名称： GetLoadSampleOriginID
	// 功能说明： 返回段数据的来源，现有的ID号
	// 返回值： 
	// 参数： CMessMemory *pSegmentMess：
	// 参数： DWORD &dwID：
	bool CCardiogramConfigHandle::GetLoadSampleOriginID(xml_node segmentNode, int &dwID)
	{
		xml_node originNode = segmentNode.first_element_by_path("./Origin_ID");
		if( !originNode.empty() )
		{
			dwID = originNode.text().as_int();
			return true;
		}
		return false;
	}

	bool CCardiogramConfigHandle::LoadSampleFromFile(CSample *pSample, const std::string &strFile, CVirCardiogramParam *pVirParam)
	{
		if(strFile.empty())
			return false;
		LPSTREAM lpStream = NULL;
		lpStream = pVirParam->GetFileStream(strFile);
		bool bRtn = pSample->LoadSampleDataFromStream(lpStream);
		if(lpStream != NULL)
			lpStream->Release();
		return bRtn;
	}

	//缩放操作处理函数
	void CCardiogramConfigHandle::ZoomSampleData(CSample *pSample, xml_node expressNode, CVirCardiogramParam *pVirParam)
	{
		int nChgedTime = -1;
		for (pugi::xml_node_iterator it = expressNode.begin(); it != expressNode.end(); ++it)
		{
			if( it->type() == node_pcdata )
			{
				std::string str(it->value());
				nChgedTime = boost::lexical_cast<int>(str);
			}
			else if( it->type() == node_element && std::string(it->name()) == "代参数" )
			{
				//得到实际的数值
				std::string strValue;
				if(pVirParam->GetParamValue(it->text().as_string(), strValue))
				{
					nChgedTime = boost::lexical_cast<int>(strValue);
				}
				else
					BOOST_ASSERT(0);
			}
		}
		if(nChgedTime != -1)
		{
			if(nChgedTime == 0) 
				pSample->m_dwSize = 0;
			else
				pSample->ZoomSampleDataHandle(nChgedTime);
		}
	}

	//重复复制操作
	void  CCardiogramConfigHandle::CopySampleData(CSample *pSample, xml_node expressNode, CVirCardiogramParam *pVirParam)
	{
		int nSumNumber = 0;
		int iCycleTime = -1;
		std::string strKey;
		for (pugi::xml_node_iterator it = expressNode.begin(); it != expressNode.end(); ++it)
		{
			if( std::string(it->name()) == "间隔时间" )
			{
				pugi::xml_node childNode = it->first_child();
				if( childNode.type() == node_pcdata )
				{
					iCycleTime = boost::lexical_cast<int>(childNode.value());
				}
				else if( childNode.type() == node_element && std::string(childNode.name()) == "代参数")
				{
					strKey = childNode.text().as_string();
				}
			}
			else if( std::string(it->name()) == "次数" )
			{
				pugi::xml_node childNode = it->first_child();
				if( childNode.type() == node_pcdata )
				{
					nSumNumber = boost::lexical_cast<int>(childNode.value());
				}
				else if( childNode.type() == node_element && std::string(childNode.name()) == "代参数")
				{
					std::string strParam = childNode.text().as_string();
					//得到实际的数值
					std::string strValue;
					if(pVirParam->GetParamValue(strParam,strValue))
					{
						nSumNumber = boost::lexical_cast<int>(strValue);
					}
					else
						BOOST_ASSERT(0);
				}
			}
		}
		if(nSumNumber == 0)
		{//如果次数为0，表示不需要添加基数据段
			pSample->ResetSample();
		}
		else if(nSumNumber > 1)
		{
			CSample cTmpSample;
			cTmpSample.Clone(pSample);
			for(int i=1;i<nSumNumber;++i)
			{
				std::string  strCycleTime, strParam;
				strParam = boost::lexical_cast<std::string>(i);
				if(!strKey.empty() && pVirParam->GetParamValue(strKey,strParam,strCycleTime))
				{
					iCycleTime = boost::lexical_cast<int>(strCycleTime);
				}
				if(iCycleTime <= 0)
				{
					pSample->OverlapLinkSampleData(&cTmpSample,abs(iCycleTime));
				}
				else
				{
					int iSumTime =pSample->GetSampleSumTime();
					float fValue = *(pSample->GetSamplePtr(iSumTime)-1);
					pSample->AddSampleData(iSumTime,iCycleTime,fValue);
					pSample->OverlapLinkSampleData(&cTmpSample,0);
				}
			}
		}
	}

	//切割操作处理函数
	void CCardiogramConfigHandle::CutSampleData(CSample *pSample, xml_node expressNode, CVirCardiogramParam *pVirParam)
	{
		bool bRmvPosition = true;//移除的部位(true:右边；false:左边)
		int iTimePos = 0;
		for (pugi::xml_node_iterator it = expressNode.begin(); it != expressNode.end(); ++it)
		{
			std::string  cap = it->name();
			if( cap == "去除左位" )
			{
				bRmvPosition = false;
			}
			else if( cap == "切割时间点" )
			{
				pugi::xml_node childNode = it->first_child();
				if( childNode.type() == node_pcdata )
				{
					iTimePos = boost::lexical_cast<int>(childNode.value());
				}
				else if( childNode.type() == node_element && std::string(childNode.name()) == "代参数")
				{
					std::string strParam = childNode.text().as_string();
					//得到实际的数值
					std::string strValue;
					if(pVirParam->GetParamValue(strParam,strValue))
					{
						iTimePos = boost::lexical_cast<int>(strValue);
					}
					else
						BOOST_ASSERT(0);
				}
			}
		}
		if(iTimePos > 0)
		{
			pSample->CutSampleDataHandle(iTimePos,bRmvPosition);
		}
	}

	//覆盖指定区域操作处理函数
	void CCardiogramConfigHandle::OverlapRegionSampleData(CSample *pSample, xml_node expressNode, CVirCardiogramParam *pVirParam)
	{
		bool bRmvPosition = true;//移除的部位(true:右边；false:左边)
		int iTimePos = 0;
		for (pugi::xml_node_iterator it = expressNode.begin(); it != expressNode.end(); ++it)
		{
			std::string  cap( it->name() );
			if( cap == "去除左位" )
			{
				bRmvPosition = false;
			}
			else if( cap == "时间点" )
			{
				pugi::xml_node childNode = it->first_child();
				if( childNode.type() == node_pcdata )
				{
					iTimePos = boost::lexical_cast<int>(childNode.value());
				}
				else if( childNode.type() == node_element && std::string(childNode.name()) == "代参数")
				{
					std::string strParam = childNode.text().as_string();
					//得到实际的数值
					std::string strValue;
					if(pVirParam->GetParamValue(strParam,strValue))
					{
						iTimePos = boost::lexical_cast<int>(strValue);
					}
					else
						BOOST_ASSERT(0);
				}
			}
		}
		if(iTimePos > 0)
		{
			int nSumTime = pSample->GetSampleSumTime();
			pSample->CutSampleDataHandle(iTimePos,bRmvPosition);
			if(bRmvPosition == true)
			{
				iTimePos = nSumTime - iTimePos;
			}
			pSample->HoriIntervalLinkSampleData(iTimePos,0.0f,bRmvPosition);
		}
	}
	//水平间隔延伸操作
	void  CCardiogramConfigHandle::HoriExtendSampleData(CSample *pSample, xml_node expressNode, CVirCardiogramParam *pVirParam)
	{
		if(pSample->IsEmpty())
			return;
		bool bHorDirection = true; //TRUE：向右延伸；FALSE：向左延伸
		float fValue = 0.0f;
		int   nExtendTime = 0;
		bool  bFindValue = false;
		for (pugi::xml_node_iterator it = expressNode.begin(); it != expressNode.end(); ++it)
		{
			std::string  cap(it->name());
			if( cap == "数值" )
			{
				pugi::xml_node childNode = it->first_child();
				if( childNode.type() == node_pcdata )
				{
					fValue = boost::lexical_cast<float>(childNode.value());
				}
				else if( childNode.type() == node_element && std::string(childNode.name()) == "代参数")
				{
					std::string strParam = childNode.text().as_string();
					//得到实际的数值
					std::string strValue;
					if(pVirParam->GetParamValue(strParam,strValue))
					{
						fValue = boost::lexical_cast<float>(strValue);
					}
					else
						BOOST_ASSERT(0);
				}
			}
			else if( cap == "时间" )
			{
				pugi::xml_node childNode = it->first_child();
				if( childNode.type() == node_pcdata )
				{
					nExtendTime = boost::lexical_cast<int>(childNode.value());
				}
				else if( childNode.type() == node_element && std::string(childNode.name()) == "代参数")
				{
					std::string strParam = childNode.text().as_string();
					//得到实际的数值
					std::string strValue;
					if(pVirParam->GetParamValue(strParam,strValue))
					{
						nExtendTime = boost::lexical_cast<int>(strValue);
						if(nExtendTime < 0)
						{//负数表示负方向
							bHorDirection = false;
							nExtendTime = abs(nExtendTime);
						}
					}
					else
						BOOST_ASSERT(0);
				}
			}
			else if(cap == "负方向延伸")
			{
				bHorDirection = false;
			}
		}
		if(bFindValue == false)
		{
			if(bHorDirection)
				fValue = *(pSample->GetSamplePtr(pSample->GetSampleSumTime()) -1);
			else
				fValue = *pSample->GetSamplePtr(0);
		}
		if(nExtendTime > 0)
		{
			pSample->HoriIntervalLinkSampleData(nExtendTime,fValue,bHorDirection);
		}
	}

	//直线间隔延伸操作
	void  CCardiogramConfigHandle::LineExtendSampleData(CSample *pSample, xml_node expressNode, CVirCardiogramParam *pVirParam)
	{
		float fValue = 0.0f;
		int   nExtendTime = 0;
		for (pugi::xml_node_iterator it = expressNode.begin(); it != expressNode.end(); ++it)
		{
			std::string   cap( it->name() );
			if( cap == "数值" )
			{
				pugi::xml_node childNode = it->first_child();
				if( childNode.type() == node_pcdata )
				{
					fValue = boost::lexical_cast<float>(childNode.value());
				}
				else if( childNode.type() == node_element && std::string(childNode.name()) == "代参数")
				{
					std::string strParam = childNode.text().as_string();
					//得到实际的数值
					std::string strValue;
					if(pVirParam->GetParamValue(strParam,strValue))
					{
						fValue = boost::lexical_cast<float>(strValue);
					}
					else
						BOOST_ASSERT(0);
				}
			}
			else if( cap == "时间" )
			{
				pugi::xml_node childNode = it->first_child();
				if( childNode.type() == node_pcdata )
				{
					nExtendTime = boost::lexical_cast<int>(childNode.value());
				}
				else if( childNode.type() == node_element && std::string(childNode.name()) == "代参数")
				{
					std::string strParam = childNode.text().as_string();
					//得到实际的数值
					std::string strValue;
					if(pVirParam->GetParamValue(strParam,strValue))
					{
						nExtendTime = boost::lexical_cast<int>(strValue);
					}
					else
						BOOST_ASSERT(0);
				}
			}
		}
		if(nExtendTime > 0)
		{
			pSample->AddSampleData(pSample->GetSampleSumTime(),nExtendTime,pSample->m_pPtrData[pSample->m_dwSize-1],fValue);
		}
	}

	bool  CCardiogramConfigHandle::CombineSampleDataHandle(CSample *pDstSample, xml_node expressNode, CVirCardiogramParam *pVirParam)
	{
		CSample *pSrcSample[2];
		pSrcSample[0] = pSrcSample[1] = NULL;
		float fValue = 0.0f;
		int   iIntervalTime = 0;
		int iStep = 0;
		for (pugi::xml_node_iterator it = expressNode.begin(); it != expressNode.end(); ++it)
		{
			std::string cap(it->name());
			if( cap == "数据段" )
			{
				int iID = it->text().as_int();
				boost::unordered_map<int, CSample *>::const_iterator pos = m_SampleDataMap.find(iID);
				if( pos == m_SampleDataMap.end() )
				{//还没有创建的话，先创建
					xml_node segNode = FindSegmentFromID(cycleNode, iID);
					if( !segNode.empty() )
					{
						std::string segCap( segNode.name() );
						if( segCap == "数据段" || segCap == "数据操作段")
							pSrcSample[iStep] = CreateSampleFromSegmentXML(segNode, pVirParam);
						else if( segCap == "组合段" )
							pSrcSample[iStep] = CreateSampleFromCombineXML(segNode, pVirParam);
						else
							BOOST_ASSERT(0);
					}
				}
				else
				{
					pSrcSample[iStep] = pos->second;
				}
				if( pSrcSample[iStep] == NULL)
					return NULL;
				else
					++iStep;
			}
			else if( cap == "数值")
			{
				fValue = 0.0f;
				pugi::xml_node valueNode = it->first_child();
				if( valueNode.type() == node_pcdata )
				{
					fValue = boost::lexical_cast<float>(valueNode.value());
				}
				else if( valueNode.type() == node_element && std::string(valueNode.name()) == "代参数")
				{
					std::string strParam = valueNode.text().as_string();
					//得到实际的数值
					std::string strValue;
					if(pVirParam->GetParamValue(strParam,strValue))
					{
						fValue = boost::lexical_cast<float>(strValue);
					}
				}
			}
			else if( cap == "时间")
			{
				iIntervalTime = 0;
				pugi::xml_node valueNode = it->first_child();
				if( valueNode.type() == node_pcdata )
				{
					iIntervalTime = boost::lexical_cast<int>(valueNode.value());
				}
				else if( valueNode.type() == node_element && valueNode.name() == "代参数")
				{
					std::string strParam = valueNode.text().as_string();
					//得到实际的数值
					std::string strValue;
					if(pVirParam->GetParamValue(strParam,strValue))
					{
						iIntervalTime = boost::lexical_cast<int>(strValue);
					}
				}
			}
		}
		std::string  expressCap(expressNode.name());
		pDstSample->Clone(pSrcSample[0]);
		if(expressCap == "直接连接操作")
		{
			pDstSample->DirectLinkSampleData(pSrcSample[1]);
		}
		else if(expressCap == "水平间隔连接操作")
		{
			pDstSample->HoriIntervalLinkSampleData(pSrcSample[1],iIntervalTime,fValue);
		}
		else if(expressCap == "直线间隔连接操作")
		{
			pDstSample->LineIntervalLinkSampleData(pSrcSample[1],iIntervalTime);
		}
		else if(expressCap == "区域叠加操作")
		{
			pDstSample->OverlapLinkSampleData(pSrcSample[1],iIntervalTime);
		}
		else if(expressCap == "起始位置叠加操作")
		{
			pDstSample->DirectOverlapLinkSampleData(pSrcSample[1]);
		}
		else if(expressCap == "起始位置覆盖操作")
		{
			pDstSample->DirectCoverLinkeSampleData(pSrcSample[1]);
		}
		return true;
	}

	void  CCardiogramConfigHandle::BasicOperatorSampleDataFormXML(/*in,out*/CSample *pDstSample, xml_node parentNode, CVirCardiogramParam *pVirParam)
	{
		//按配置文件描述的过程，对原始采样数据进行处理
		for (pugi::xml_node_iterator it = parentNode.begin(); it != parentNode.end(); ++it)
		{
			std::string  cap( it->name() );
			if(cap == "缩放操作")
			{
				ZoomSampleData(pDstSample,*it,pVirParam);
			}
			else if(cap == "重复复制操作")
			{
				CopySampleData(pDstSample, *it, pVirParam);
			}
			else if(cap == "切割操作")
			{
				CutSampleData(pDstSample, *it, pVirParam);
			}
			else if(cap == "水平间隔延伸操作")
			{
				HoriExtendSampleData(pDstSample, *it, pVirParam);
			}
			else if(cap == "直线间隔延伸操作")
			{
				LineExtendSampleData(pDstSample, *it, pVirParam);
			}
			else if(cap == "覆盖区域操作")
			{
				OverlapRegionSampleData(pDstSample, *it, pVirParam);
			}
		}
	}
}}}
