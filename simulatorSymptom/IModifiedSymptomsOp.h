#pragma once
#include <list>
#include ".\simulatorsymptom_global.h"

#include "..\common\criticalmutex.h"

#include "..\SimulatorBase\ITransportOrderIrpToSimulator.h"

namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     标识、收集被修改的体征的接口类
	创建人：	 hjg
	创建时间：   2008/10/20
	//-----------------------------------------------------------------------------------------------------------------*/
	class CSymptomVirtual;
    class SIMULATORSYMPTOMSHARED_EXPORT IModifiedSymptomsOp
	{
	public:
		IModifiedSymptomsOp(void);
		virtual ~IModifiedSymptomsOp(void);
	public:
		/*******************************************************************************/
		// 函数名称： AddNewModifiedSymptom
		// 功能：   添加被修改的体征，收集的体征需要保存唯一性
		// 参数：   CSymptomVirtual *pVirSymptom
		// 返回值:  
		virtual void AddNewModifiedSymptom(CSymptomVirtual *pVirSymptom);
		/*******************************************************************************/
		// 函数名称： RemoveAllModifiedSymptoms
		// 功能：   移除所有收集的体征
		// 参数：   
		// 返回值:  
		virtual void RemoveAllModifiedSymptoms();
		/*******************************************************************************/
		// 函数名称： TransmitSimulatorOrders
		// 功能： 传输模拟人体征通信指令
		// 参数：        
		// 返回值:
		virtual void TransmitSimulatorOrders() = 0;
		/*******************************************************************************/
		// 函数名称： ModifiedSymptomsUpdateShow
		// 功能： 被修改的参数更新显示
		// 参数： 
		//        bool bClearModifiedFlag:      是否清除修改标识   
		// 返回值:
		virtual void ModifiedSymptomsUpdateShow( bool bClearModifiedFlag ) = 0;
	public:
		bool findModifiedSymptom(CSymptomVirtual *pVirSymptom);
		//清除被修改体征的标识
		void emptyModifiedSymptomsFlag();
	protected:
		utility::CCriticalMutex               m_cMutex;
		std::list<CSymptomVirtual *>          modifiedSymptoms;
	};
}}
