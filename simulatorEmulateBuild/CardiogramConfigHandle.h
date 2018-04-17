#pragma once
#include <list>
#include <pugixml.hpp>
#include <boost/unordered_map.hpp>

#include "..\Common\CommonGlobal.h"

#include "..\SimulatorBase\Sample.h"
#include "..\SimulatorBase\VirCardiogramParam.h"


using namespace pugi;
namespace jysoft { namespace simulator { namespace ecg {

	class  CCardiogramConfigHandle
	{
	public:
		CCardiogramConfigHandle(void);
		~CCardiogramConfigHandle(void);
	public:
		bool LoadConfigFile(CVirCardiogramParam *pVirParam, CSample *pDstSample);
		bool ParseConfigXML(char *pPtr,long dwSize,CVirCardiogramParam *pVirParam, CSample *pDstSample);
		bool ParseDataXMLSegment(CVirCardiogramParam *pVirParam);
		bool ParseDataOperatorXMLSegment(CVirCardiogramParam *pVirParam);
		bool ParseCombineXMLSegment(CVirCardiogramParam *pVirParam);
		bool CreateMainCycleData(CVirCardiogramParam *pVirParam,/*out*/CSample *pDstSample);
		bool ReCreateMainCycleData(CVirCardiogramParam *pVirParam,/*out*/CSample *pDstSample);
		//�����粨������
		bool CreateExtrasystData(int iCycleTime, Extrasys eExtrasyst, CVirCardiogramParam *pVirParam, /*out*/CSample *pDstSample);
		//���������ݶ�
		bool ParseBasicSegmentData(CVirCardiogramParam *pVirParam, /*out*/CSample **pDstSample);
	protected:
		//�������ݶε�ID�ţ��ҳ��˽�����
		xml_node FindSegmentFromID(xml_node cycleNode, int iID);
		//���ݶε����ã����ɲ�������
		CSample * CreateSampleFromSegmentXML(xml_node segmentNode, CVirCardiogramParam *pVirParam);
		CSample * CreateSampleFromCombineXML(xml_node combineNode, CVirCardiogramParam *pVirParam);
		CSample * CreateBasicExtrasystSample(Extrasys eExtrasyst, xml_node segmentNode, CVirCardiogramParam *pVirParam);
		CSample * CreateBasicSegmentData(xml_node segmentNode, CVirCardiogramParam *pVirParam);
		bool ModifyMainCycleDataBaseExtrasyst(int iCycleTime ,xml_node segmentNode, CVirCardiogramParam *pVirParam, /*out*/CSample *pDstSample);
	protected:
		//���ضε�ID��
		bool GetSegmentID(xml_node segmentNode, int &dwID);
		//���ض����ݵ���Դ���ļ����ƣ�
		bool  GetLoadSampleFileName(xml_node segmentNode, std::string &strFileName,bool &bParam);
		bool  GetLoadSampleOriginID(xml_node segmentNode, int &dwID);
		//���ز��������ļ�
		bool  LoadSampleFromFile(CSample *pSample, const std::string &strFile,CVirCardiogramParam *pVirParam);
		//���Ų���������
		void  ZoomSampleData(CSample *pSample, xml_node expressNode, CVirCardiogramParam *pVirParam);
		//�и����������
		void  CutSampleData(CSample *pSample, xml_node expressNode, CVirCardiogramParam *pVirParam);
		//�ظ����Ʋ���
		void  CopySampleData(CSample *pSample, xml_node expressNode, CVirCardiogramParam *pVirParam);
		//����ָ���������������
		void OverlapRegionSampleData(CSample *pSample, xml_node expressNode, CVirCardiogramParam *pVirParam);
		//ˮƽ����������
		void  HoriExtendSampleData(CSample *pSample, xml_node expressNode, CVirCardiogramParam *pVirParam);
		//ֱ�߼���������
		void  LineExtendSampleData(CSample *pSample, xml_node expressNode, CVirCardiogramParam *pVirParam);
		//��ϴ���
		bool  CombineSampleDataHandle(CSample *pDstSample, xml_node expressNode, CVirCardiogramParam *pVirParam);
		void  BasicOperatorSampleDataFormXML(/*in,out*/CSample *pDstSample, xml_node parentNode, CVirCardiogramParam *pVirParam);
	protected://����
		pugi::xml_document    xmlRoot;
		pugi::xml_node    cycleNode;
		boost::unordered_map<int, CSample *>  m_SampleDataMap;
		std::list<CSample *>  m_lstDataOperatorSegment;
		std::list<CSample *>  m_lstCombineSegment;
	};
}}}