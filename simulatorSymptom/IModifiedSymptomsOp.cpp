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
	// �������ƣ� AddNewModifiedSymptom
	// ���ܣ�   ��ӱ��޸ĵ��������ռ���������Ҫ����Ψһ��
	// ������   CSymptomVirtual *pVirSymptom
	// ����ֵ:  
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
	// �������ƣ� RemoveAllModifiedSymptoms
	// ���ܣ�   �Ƴ������ռ�������
	// ������   
	// ����ֵ:  
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

	//������޸������ı�ʶ
	void IModifiedSymptomsOp::emptyModifiedSymptomsFlag()
	{
        foreach(auto pVirSymptom, modifiedSymptoms)
		{
			pVirSymptom->ResetFlag();
		}
		modifiedSymptoms.clear();
	}
}}
