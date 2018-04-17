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
		//�Ƴ�Map�ڵ�Ԫ��
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
		//�Ƴ�Map�ڵ�Ԫ��
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
			//���������ļ�
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
		//�Ƴ��ϴν���ʱ���ɵ�����
		xmlRoot.reset();
		pugi::xml_parse_result result = xmlRoot.load_buffer(pPtr, dwSize);
		//����������ı�
		if( result )
		{
			cycleNode = xmlRoot.first_element_by_path( "����/��������" );
			if( !cycleNode.empty() )
			{
				//���������ļ���������(�����ٶȷ��棬�������߳�)
				bRtn = ReCreateMainCycleData(pVirParam, pDstSample);
			}
		}
		return bRtn;
	}

	//�������ݶ�
	bool CCardiogramConfigHandle::ParseDataXMLSegment(CVirCardiogramParam *pVirParam)
	{
		for (pugi::xml_node_iterator it = cycleNode.begin(); it != cycleNode.end(); ++it)
		{
			std::string  cap = it->name();
			if( cap == "���ݶ�" )
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
		//���ɵ����ݲ����ζ��Ƴ�
		BOOST_FOREACH(auto pSample, m_lstDataOperatorSegment)
		{
			m_SampleDataMap.erase(pSample->GetSampleID());
			delete pSample;
		}
		m_lstDataOperatorSegment.clear();
		//end hjg
		for (pugi::xml_node_iterator it = cycleNode.begin(); it != cycleNode.end(); ++it)
		{
			if( std::string(it->name()) == "���ݲ�����" )
			{
				CSample *pNewSample = CreateSampleFromSegmentXML(*it, pVirParam);
				if(pNewSample == NULL)
					return false;
			}
		}
		return true;
	}

	//������϶�
	bool CCardiogramConfigHandle::ParseCombineXMLSegment(CVirCardiogramParam *pVirParam)
	{
		//���ɵ���϶ζ��Ƴ�
		BOOST_FOREACH(auto pSample, m_lstCombineSegment)
		{
			m_SampleDataMap.erase(pSample->GetSampleID());
			delete pSample;
		}
		m_lstCombineSegment.clear();
		//end hjg
		for (pugi::xml_node_iterator it = cycleNode.begin(); it != cycleNode.end(); ++it)
		{
			if( std::string(it->name()) == "��϶�" )
			{
				CSample *pNewSample = CreateSampleFromCombineXML(*it, pVirParam);
				if(pNewSample == NULL)
					return false;
			}
		}
		return true;
	}

	//���������ݶ�
	bool CCardiogramConfigHandle::ParseBasicSegmentData(CVirCardiogramParam *pVirParam, /*out*/CSample **pDstSample)
	{
		for (pugi::xml_node_iterator it = cycleNode.begin(); it != cycleNode.end(); ++it)
		{
			if( std::string(it->name()) == "�����ݶ�" )
			{
				*pDstSample= CreateBasicSegmentData(*it, pVirParam);
				if(*pDstSample == NULL)
					return false;
				return true;
			}
		}
		return false;
	}

	//��������
	bool CCardiogramConfigHandle::CreateMainCycleData(CVirCardiogramParam *pVirParam,/*out*/CSample *pDstSample)
	{
		pDstSample->ResetSample();
		std::list<CSample *> lstSamples;
		bool bRtn = false;
		//�ĵ����ڶ�
		pugi::xml_node ecgSegNode = cycleNode.first_element_by_path("./�ĵ����ڶ�");
		if( !ecgSegNode.empty() )
		{
			for (pugi::xml_node_iterator it = ecgSegNode.begin(); it != ecgSegNode.end(); ++it)
			{
				if( std::string(it->name()) == "���ݶ�")
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
		//�����ε�������������
		BOOST_FOREACH(auto pSamplePtr, lstSamples)
		{
			if(pDstSample->IsEmpty())
				pDstSample->Clone(pSamplePtr);
			else
				pDstSample->DirectLinkSampleData(pSamplePtr);
		}
		lstSamples.clear();
		int iCycleTime = pVirParam->GetCycleTime();
		//�����ڵ����ݴ����ʱ���Ƿ��������ʱ��
		int nSumTime = pDstSample->GetSampleSumTime();
		if( iCycleTime > nSumTime )
		{
			//�ӳ�
			pDstSample->AddSampleData(nSumTime, iCycleTime- nSumTime, 0.0f);
		}
		//---------------------------------------------------
		CSample *pBasicSegmentSample = NULL;//�����ݶ�
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
		//�Ƴ�Map�ڵ�Ԫ��
		auto p = m_SampleDataMap.begin();
		for (p; p != m_SampleDataMap.end(); ++p)
		{
			delete p->second;
		}
		m_SampleDataMap.clear();
		//�������ݶ�
		bool bRtn = ParseDataXMLSegment(pVirParam);
		//�������ݲ�����
		if(bRtn == true)
			bRtn = ParseDataOperatorXMLSegment(pVirParam);
		//������϶�
		if(bRtn == true)
			bRtn = ParseCombineXMLSegment(pVirParam);
		//��������
		if(bRtn == true)
			bRtn = CreateMainCycleData(pVirParam,pDstSample);
		return bRtn;
	}

	//�����粨������
	bool CCardiogramConfigHandle::CreateExtrasystData(int iCycleTime, Extrasys eExtrasyst, CVirCardiogramParam *pVirParam, /*in,out*/CSample *pDstSample)
	{	
		//�粨��
		pugi::xml_node extraSegNode = cycleNode.first_element_by_path("./�粨");
		if( !extraSegNode.empty() )
		{
			CSample *pExtrasystSample = CreateBasicExtrasystSample(eExtrasyst, extraSegNode, pVirParam);
			if(pExtrasystSample != NULL)
			{
				//���������ڶ�����
				if(eExtrasyst != PAC && eExtrasyst != PJC)
				{//�������������Ҫ�޸�
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

	//�����粨�Ĳ�ͬ���޸����ĵ�ͼ���ݶ�
	bool CCardiogramConfigHandle::ModifyMainCycleDataBaseExtrasyst(int iCycleTime , xml_node segmentNode, CVirCardiogramParam *pVirParam, /*in,out*/CSample *pDstSample)
	{
		int nSumTime = pVirParam->GetCycleTime();
		//nSumTime��iCycleTime�ı���
		//ASSERT(!(nSumTime%iCycleTime));
		for(int i = 1;i< int(1.0f*nSumTime/iCycleTime + 0.1);++i)
		{//ע����10%��������
			CSample *pPSample = NULL;
			boost::unordered_map<int, CSample *>::const_iterator pos = m_SampleDataMap.find(1);
			if( pos != m_SampleDataMap.end() )
			{//ע��P�������ݶε�ID��Ϊ1
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
		//���ز�������
		std::string   strFile;
		bool bParam = false;
		if(GetLoadSampleFileName(segmentNode, strFile, bParam))
		{
			if(bParam == true)
			{//�õ�ʵ�ʵ����ƣ����strFileΪ�գ���ʾΪ�������ĵ�ͼ����
				strFile = pVirParam->GetExtrasystFileName(eExtrasyst,strFile);
			}
			pNewSample = new CSample();
			//���ļ��м�������
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
				//�������ļ������Ĺ��̣���ԭʼ�������ݽ��д���
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

	//�������ݶε�ID�ţ��ҳ��˽�����
	xml_node CCardiogramConfigHandle::FindSegmentFromID(xml_node cycleNode, int iID)
	{
		for (pugi::xml_node_iterator it = cycleNode.begin(); it != cycleNode.end(); ++it)
		{
			std::string cap = it->name();
			if( cap == "���ݶ�" || cap == "��϶�" || cap == "���ݲ�����")
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

	//���ݶε����ã����ɲ�������
	CSample * CCardiogramConfigHandle::CreateSampleFromSegmentXML(pugi::xml_node segmentNode, CVirCardiogramParam *pVirParam)
	{
		CSample *pNewSample = NULL;
		//�õ����ݶε�ID��
		int dwID = 0;
		if(!GetSegmentID(segmentNode, dwID))
			return false;
		boost::unordered_map<int, CSample *>::const_iterator pos = m_SampleDataMap.find(dwID);
		if( pos == m_SampleDataMap.end() )
		{
			//���ز�������
			std::string  strFile;
			bool bParam = false;
			if(GetLoadSampleFileName(segmentNode, strFile, bParam))
			{
				if(bParam == true)
				{//�õ�ʵ�ʵ�����
					std::string strValue;
					if(!pVirParam->GetParamValue(strFile,strValue))
					{
                        BOOST_ASSERT(0);
						return false;
					}
					strFile = strValue;
				}
				pNewSample = new CSample(dwID);
				//���ļ��м�������
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
					{//��û����
						xml_node node = FindSegmentFromID(cycleNode,(int)dwOriginID);
						if( !node.empty() )
						{
							std::string cap = node.name();
							if(cap == "���ݶ�" || cap == "���ݲ�����")
								pOriginSample = CreateSampleFromSegmentXML(node, pVirParam);
							else if(cap == "��϶�")
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
				//�������ļ������Ĺ��̣���ԭʼ�������ݽ��д���
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
			if( std::string(segmentNode.name()) == "���ݲ�����")
			{//�����ݲ����ε����ݼ��뵽������
				std::list<CSample *>::const_iterator posFind = std::find(m_lstDataOperatorSegment.begin(), m_lstDataOperatorSegment.end(), pNewSample);
				if(posFind == m_lstDataOperatorSegment.end())
				{
					m_lstDataOperatorSegment.push_back(pNewSample);
				}
			}
		}
		return pNewSample;
	}
	//���������ݶ�
	CSample * CCardiogramConfigHandle::CreateBasicSegmentData(xml_node segmentNode, CVirCardiogramParam *pVirParam)
	{
		CSample *pNewSample = NULL;
		//�õ����ݶε�ID��
		int dwID = 0;
		if(!GetSegmentID(segmentNode, dwID))
			return false;
		//���ز�������
		std::string  strFile;
		bool bParam = false;
		if(GetLoadSampleFileName(segmentNode, strFile,bParam))
		{
			if(bParam == true)
			{//�õ�ʵ�ʵ�����
				std::string  strValue;
				if(!pVirParam->GetParamValue(strFile,strValue))
				{
                    BOOST_ASSERT(0);
					return false;
				}
				strFile = strValue;
			}
			pNewSample = new CSample(dwID);
			//���ļ��м�������
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
				{//��û����
					xml_node node = FindSegmentFromID(cycleNode,(int)dwOriginID);
					if( !node.empty() )
					{
						std::string cap = node.name();
						if( cap == "���ݶ�" || cap == "���ݲ�����")
							pOriginSample = CreateSampleFromSegmentXML(node, pVirParam);
						else if( cap == "��϶�")
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
			//�������ļ������Ĺ��̣���ԭʼ�������ݽ��д���
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
		//�õ����ݶε�ID��
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
			//����϶ε����ݼ��뵽������
			std::list<CSample *>::const_iterator posFind = std::find(m_lstCombineSegment.begin(), m_lstCombineSegment.end(), pNewSample);
			if(posFind == m_lstCombineSegment.end())
			{
				m_lstCombineSegment.push_back(pNewSample);
			}
		}
		return pNewSample;
	}

	//���ضε�ID��
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

	// �������ƣ� GetLoadSampleFileName
	// ����˵���� ���ض����ݵ���Դ���ļ����ƣ�
	// ����ֵ�� 
	// ������ CMessMemory *pSegmentMess��
	// ������ CString &strFileName�������ݵ���Դ����
	// ������ bool &bParam�����ص���Դ�����Ƿ�����������Ҫ�ö�Ӧ����ʵ��ֵ���
	bool CCardiogramConfigHandle::GetLoadSampleFileName(xml_node segmentNode, std::string &strFileName,bool &bParam)
	{
		for (pugi::xml_node_iterator it = segmentNode.begin(); it != segmentNode.end(); ++it)
		{
			if( std::string(it->name()) == "�ļ�����" )
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

	// �������ƣ� GetLoadSampleOriginID
	// ����˵���� ���ض����ݵ���Դ�����е�ID��
	// ����ֵ�� 
	// ������ CMessMemory *pSegmentMess��
	// ������ DWORD &dwID��
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

	//���Ų���������
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
			else if( it->type() == node_element && std::string(it->name()) == "������" )
			{
				//�õ�ʵ�ʵ���ֵ
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

	//�ظ����Ʋ���
	void  CCardiogramConfigHandle::CopySampleData(CSample *pSample, xml_node expressNode, CVirCardiogramParam *pVirParam)
	{
		int nSumNumber = 0;
		int iCycleTime = -1;
		std::string strKey;
		for (pugi::xml_node_iterator it = expressNode.begin(); it != expressNode.end(); ++it)
		{
			if( std::string(it->name()) == "���ʱ��" )
			{
				pugi::xml_node childNode = it->first_child();
				if( childNode.type() == node_pcdata )
				{
					iCycleTime = boost::lexical_cast<int>(childNode.value());
				}
				else if( childNode.type() == node_element && std::string(childNode.name()) == "������")
				{
					strKey = childNode.text().as_string();
				}
			}
			else if( std::string(it->name()) == "����" )
			{
				pugi::xml_node childNode = it->first_child();
				if( childNode.type() == node_pcdata )
				{
					nSumNumber = boost::lexical_cast<int>(childNode.value());
				}
				else if( childNode.type() == node_element && std::string(childNode.name()) == "������")
				{
					std::string strParam = childNode.text().as_string();
					//�õ�ʵ�ʵ���ֵ
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
		{//�������Ϊ0����ʾ����Ҫ��ӻ����ݶ�
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

	//�и����������
	void CCardiogramConfigHandle::CutSampleData(CSample *pSample, xml_node expressNode, CVirCardiogramParam *pVirParam)
	{
		bool bRmvPosition = true;//�Ƴ��Ĳ�λ(true:�ұߣ�false:���)
		int iTimePos = 0;
		for (pugi::xml_node_iterator it = expressNode.begin(); it != expressNode.end(); ++it)
		{
			std::string  cap = it->name();
			if( cap == "ȥ����λ" )
			{
				bRmvPosition = false;
			}
			else if( cap == "�и�ʱ���" )
			{
				pugi::xml_node childNode = it->first_child();
				if( childNode.type() == node_pcdata )
				{
					iTimePos = boost::lexical_cast<int>(childNode.value());
				}
				else if( childNode.type() == node_element && std::string(childNode.name()) == "������")
				{
					std::string strParam = childNode.text().as_string();
					//�õ�ʵ�ʵ���ֵ
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

	//����ָ���������������
	void CCardiogramConfigHandle::OverlapRegionSampleData(CSample *pSample, xml_node expressNode, CVirCardiogramParam *pVirParam)
	{
		bool bRmvPosition = true;//�Ƴ��Ĳ�λ(true:�ұߣ�false:���)
		int iTimePos = 0;
		for (pugi::xml_node_iterator it = expressNode.begin(); it != expressNode.end(); ++it)
		{
			std::string  cap( it->name() );
			if( cap == "ȥ����λ" )
			{
				bRmvPosition = false;
			}
			else if( cap == "ʱ���" )
			{
				pugi::xml_node childNode = it->first_child();
				if( childNode.type() == node_pcdata )
				{
					iTimePos = boost::lexical_cast<int>(childNode.value());
				}
				else if( childNode.type() == node_element && std::string(childNode.name()) == "������")
				{
					std::string strParam = childNode.text().as_string();
					//�õ�ʵ�ʵ���ֵ
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
	//ˮƽ����������
	void  CCardiogramConfigHandle::HoriExtendSampleData(CSample *pSample, xml_node expressNode, CVirCardiogramParam *pVirParam)
	{
		if(pSample->IsEmpty())
			return;
		bool bHorDirection = true; //TRUE���������죻FALSE����������
		float fValue = 0.0f;
		int   nExtendTime = 0;
		bool  bFindValue = false;
		for (pugi::xml_node_iterator it = expressNode.begin(); it != expressNode.end(); ++it)
		{
			std::string  cap(it->name());
			if( cap == "��ֵ" )
			{
				pugi::xml_node childNode = it->first_child();
				if( childNode.type() == node_pcdata )
				{
					fValue = boost::lexical_cast<float>(childNode.value());
				}
				else if( childNode.type() == node_element && std::string(childNode.name()) == "������")
				{
					std::string strParam = childNode.text().as_string();
					//�õ�ʵ�ʵ���ֵ
					std::string strValue;
					if(pVirParam->GetParamValue(strParam,strValue))
					{
						fValue = boost::lexical_cast<float>(strValue);
					}
					else
						BOOST_ASSERT(0);
				}
			}
			else if( cap == "ʱ��" )
			{
				pugi::xml_node childNode = it->first_child();
				if( childNode.type() == node_pcdata )
				{
					nExtendTime = boost::lexical_cast<int>(childNode.value());
				}
				else if( childNode.type() == node_element && std::string(childNode.name()) == "������")
				{
					std::string strParam = childNode.text().as_string();
					//�õ�ʵ�ʵ���ֵ
					std::string strValue;
					if(pVirParam->GetParamValue(strParam,strValue))
					{
						nExtendTime = boost::lexical_cast<int>(strValue);
						if(nExtendTime < 0)
						{//������ʾ������
							bHorDirection = false;
							nExtendTime = abs(nExtendTime);
						}
					}
					else
						BOOST_ASSERT(0);
				}
			}
			else if(cap == "����������")
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

	//ֱ�߼���������
	void  CCardiogramConfigHandle::LineExtendSampleData(CSample *pSample, xml_node expressNode, CVirCardiogramParam *pVirParam)
	{
		float fValue = 0.0f;
		int   nExtendTime = 0;
		for (pugi::xml_node_iterator it = expressNode.begin(); it != expressNode.end(); ++it)
		{
			std::string   cap( it->name() );
			if( cap == "��ֵ" )
			{
				pugi::xml_node childNode = it->first_child();
				if( childNode.type() == node_pcdata )
				{
					fValue = boost::lexical_cast<float>(childNode.value());
				}
				else if( childNode.type() == node_element && std::string(childNode.name()) == "������")
				{
					std::string strParam = childNode.text().as_string();
					//�õ�ʵ�ʵ���ֵ
					std::string strValue;
					if(pVirParam->GetParamValue(strParam,strValue))
					{
						fValue = boost::lexical_cast<float>(strValue);
					}
					else
						BOOST_ASSERT(0);
				}
			}
			else if( cap == "ʱ��" )
			{
				pugi::xml_node childNode = it->first_child();
				if( childNode.type() == node_pcdata )
				{
					nExtendTime = boost::lexical_cast<int>(childNode.value());
				}
				else if( childNode.type() == node_element && std::string(childNode.name()) == "������")
				{
					std::string strParam = childNode.text().as_string();
					//�õ�ʵ�ʵ���ֵ
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
			if( cap == "���ݶ�" )
			{
				int iID = it->text().as_int();
				boost::unordered_map<int, CSample *>::const_iterator pos = m_SampleDataMap.find(iID);
				if( pos == m_SampleDataMap.end() )
				{//��û�д����Ļ����ȴ���
					xml_node segNode = FindSegmentFromID(cycleNode, iID);
					if( !segNode.empty() )
					{
						std::string segCap( segNode.name() );
						if( segCap == "���ݶ�" || segCap == "���ݲ�����")
							pSrcSample[iStep] = CreateSampleFromSegmentXML(segNode, pVirParam);
						else if( segCap == "��϶�" )
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
			else if( cap == "��ֵ")
			{
				fValue = 0.0f;
				pugi::xml_node valueNode = it->first_child();
				if( valueNode.type() == node_pcdata )
				{
					fValue = boost::lexical_cast<float>(valueNode.value());
				}
				else if( valueNode.type() == node_element && std::string(valueNode.name()) == "������")
				{
					std::string strParam = valueNode.text().as_string();
					//�õ�ʵ�ʵ���ֵ
					std::string strValue;
					if(pVirParam->GetParamValue(strParam,strValue))
					{
						fValue = boost::lexical_cast<float>(strValue);
					}
				}
			}
			else if( cap == "ʱ��")
			{
				iIntervalTime = 0;
				pugi::xml_node valueNode = it->first_child();
				if( valueNode.type() == node_pcdata )
				{
					iIntervalTime = boost::lexical_cast<int>(valueNode.value());
				}
				else if( valueNode.type() == node_element && valueNode.name() == "������")
				{
					std::string strParam = valueNode.text().as_string();
					//�õ�ʵ�ʵ���ֵ
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
		if(expressCap == "ֱ�����Ӳ���")
		{
			pDstSample->DirectLinkSampleData(pSrcSample[1]);
		}
		else if(expressCap == "ˮƽ������Ӳ���")
		{
			pDstSample->HoriIntervalLinkSampleData(pSrcSample[1],iIntervalTime,fValue);
		}
		else if(expressCap == "ֱ�߼�����Ӳ���")
		{
			pDstSample->LineIntervalLinkSampleData(pSrcSample[1],iIntervalTime);
		}
		else if(expressCap == "������Ӳ���")
		{
			pDstSample->OverlapLinkSampleData(pSrcSample[1],iIntervalTime);
		}
		else if(expressCap == "��ʼλ�õ��Ӳ���")
		{
			pDstSample->DirectOverlapLinkSampleData(pSrcSample[1]);
		}
		else if(expressCap == "��ʼλ�ø��ǲ���")
		{
			pDstSample->DirectCoverLinkeSampleData(pSrcSample[1]);
		}
		return true;
	}

	void  CCardiogramConfigHandle::BasicOperatorSampleDataFormXML(/*in,out*/CSample *pDstSample, xml_node parentNode, CVirCardiogramParam *pVirParam)
	{
		//�������ļ������Ĺ��̣���ԭʼ�������ݽ��д���
		for (pugi::xml_node_iterator it = parentNode.begin(); it != parentNode.end(); ++it)
		{
			std::string  cap( it->name() );
			if(cap == "���Ų���")
			{
				ZoomSampleData(pDstSample,*it,pVirParam);
			}
			else if(cap == "�ظ����Ʋ���")
			{
				CopySampleData(pDstSample, *it, pVirParam);
			}
			else if(cap == "�и����")
			{
				CutSampleData(pDstSample, *it, pVirParam);
			}
			else if(cap == "ˮƽ����������")
			{
				HoriExtendSampleData(pDstSample, *it, pVirParam);
			}
			else if(cap == "ֱ�߼���������")
			{
				LineExtendSampleData(pDstSample, *it, pVirParam);
			}
			else if(cap == "�����������")
			{
				OverlapRegionSampleData(pDstSample, *it, pVirParam);
			}
		}
	}
}}}
