#pragma once
#include ".\symptomvirtual.h"


namespace jysoft { namespace simulator {

    class SIMULATORSYMPTOMSHARED_EXPORT CSymptom_FrameTime : public CSymptomVirtual
	{
	public:
		CSymptom_FrameTime(void);
		virtual ~CSymptom_FrameTime(void);
	public: 
		/*******************************************************************************/
		// 函数名称： IsKindOf
		// 功能：   判断体征的类别
		// 参数：   const CString &strClassName
		// 返回值: 
		virtual  bool isKindOf( const std::string &strClassName );
		//根据标示名称判断体征参数
		virtual  bool isSymptomCaption(const std::string &strCaption);
		/*******************************************************************************/
		// 函数名称： InitialSymptomValue
		// 功能：   初始化体征值
		// 参数：   IModifiedSymptomsOp *pInterfacePtr
		// 返回值: 
		virtual  void InitialSymptomValue(IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType);
		/*******************************************************************************/
		// 函数名称： InitialSymptomValue
		// 功能：   初始化体征值
		// 参数：   
		//          tag_TrendValue *pDefaultTrendValue:  相应体征修改的值返回
		//          CXActionVirtual *pVirAction:         对应体征值
		//          short sTransTime:                    转换时间（单位：秒）
		// 返回值: 
		virtual  void InitialSymptomValue(CXActionVirtual *pVirAction, short sTransTime = 0);
	public:
		inline long  GetValue_FrameTime() { return m_lFrameTime; };
		//重置场景框时间为0
		void ResetFrameTimeToZero();
		//增加场景框持续时间
		void IncreaseFrameTime(long  lAddTime);
	protected:
		long                            m_lFrameTime;
	};
}}
