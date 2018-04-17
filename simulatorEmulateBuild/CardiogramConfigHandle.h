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
		//生成早波段数据
		bool CreateExtrasystData(int iCycleTime, Extrasys eExtrasyst, CVirCardiogramParam *pVirParam, /*out*/CSample *pDstSample);
		//解析基数据段
		bool ParseBasicSegmentData(CVirCardiogramParam *pVirParam, /*out*/CSample **pDstSample);
	protected:
		//根据数据段的ID号，找出此解析段
		xml_node FindSegmentFromID(xml_node cycleNode, int iID);
		//根据段的配置，生成采样数据
		CSample * CreateSampleFromSegmentXML(xml_node segmentNode, CVirCardiogramParam *pVirParam);
		CSample * CreateSampleFromCombineXML(xml_node combineNode, CVirCardiogramParam *pVirParam);
		CSample * CreateBasicExtrasystSample(Extrasys eExtrasyst, xml_node segmentNode, CVirCardiogramParam *pVirParam);
		CSample * CreateBasicSegmentData(xml_node segmentNode, CVirCardiogramParam *pVirParam);
		bool ModifyMainCycleDataBaseExtrasyst(int iCycleTime ,xml_node segmentNode, CVirCardiogramParam *pVirParam, /*out*/CSample *pDstSample);
	protected:
		//返回段的ID号
		bool GetSegmentID(xml_node segmentNode, int &dwID);
		//返回段数据的来源（文件名称）
		bool  GetLoadSampleFileName(xml_node segmentNode, std::string &strFileName,bool &bParam);
		bool  GetLoadSampleOriginID(xml_node segmentNode, int &dwID);
		//加载采样数据文件
		bool  LoadSampleFromFile(CSample *pSample, const std::string &strFile,CVirCardiogramParam *pVirParam);
		//缩放操作处理函数
		void  ZoomSampleData(CSample *pSample, xml_node expressNode, CVirCardiogramParam *pVirParam);
		//切割操作处理函数
		void  CutSampleData(CSample *pSample, xml_node expressNode, CVirCardiogramParam *pVirParam);
		//重复复制操作
		void  CopySampleData(CSample *pSample, xml_node expressNode, CVirCardiogramParam *pVirParam);
		//覆盖指定区域操作处理函数
		void OverlapRegionSampleData(CSample *pSample, xml_node expressNode, CVirCardiogramParam *pVirParam);
		//水平间隔延伸操作
		void  HoriExtendSampleData(CSample *pSample, xml_node expressNode, CVirCardiogramParam *pVirParam);
		//直线间隔延伸操作
		void  LineExtendSampleData(CSample *pSample, xml_node expressNode, CVirCardiogramParam *pVirParam);
		//组合处理
		bool  CombineSampleDataHandle(CSample *pDstSample, xml_node expressNode, CVirCardiogramParam *pVirParam);
		void  BasicOperatorSampleDataFormXML(/*in,out*/CSample *pDstSample, xml_node parentNode, CVirCardiogramParam *pVirParam);
	protected://属性
		pugi::xml_document    xmlRoot;
		pugi::xml_node    cycleNode;
		boost::unordered_map<int, CSample *>  m_SampleDataMap;
		std::list<CSample *>  m_lstDataOperatorSegment;
		std::list<CSample *>  m_lstCombineSegment;
	};
}}}