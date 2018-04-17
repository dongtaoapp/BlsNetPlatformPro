#include <algorithm>
#include <boost/foreach.hpp>
#include ".\imodifiedsymptomsop.h"
#include ".\SymptomVirtual.h"


namespace jysoft { namespace simulator 
{
	IModifiedSymptomsOp::IModifiedSymptomsOp(void)
	{
	}

	IModifiedSymptomsOp::~IModifiedSymptomsOp(void)
	{
		modifiedSymptoms.clear();
	}

	/*******************************************************************************/
	// 函数名称： AddNewModifiedSymptom
	// 功能：   添加被修改的体征，收集的体征需要保存唯一性
	// 参数：   CSymptomVirtual *pVirSymptom
	// 返回值:  
	void IModifiedSymptomsOp::AddNewModifiedSymptom(CSymptomVirtual *pVirSymptom)
	{
		m_cMutex.Lock();
		if( !findModifiedSymptom(pVirSymptom) )
		{
			modifiedSymptoms.push_back(pVirSymptom);
		}
		m_cMutex.Unlock();
	}

	/*******************************************************************************/
	// 函数名称： RemoveAllModifiedSymptoms
	// 功能：   移除所有收集的体征
	// 参数：   
	// 返回值:  
	void IModifiedSymptomsOp::RemoveAllModifiedSymptoms()
	{
		m_cMutex.Lock();
		modifiedSymptoms.clear();
		m_cMutex.Unlock();
	}

	bool IModifiedSymptomsOp::findModifiedSymptom(CSymptomVirtual *pVirSymptom)
	{
		std::list<CSymptomVirtual *>::iterator pos;
		pos = std::find(modifiedSymptoms.begin(), modifiedSymptoms.end(), pVirSymptom);
		if( pos == modifiedSymptoms.end() )
		{
			return false;
		}
		return true;
	}

	//清除被修改体征的标识
	void IModifiedSymptomsOp::emptyModifiedSymptomsFlag()
	{
        foreach(auto pVirSymptom, modifiedSymptoms)
		{
			pVirSymptom->ResetFlag();
		}
		modifiedSymptoms.clear();
	}
}}
