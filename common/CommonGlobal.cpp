#include <boost/assert.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>

#include ".\CommonGlobal.h"


using namespace  boost;

namespace jysoft {
	//------------------------------------------------------------------------------------------------------
	//struct I12LeadSample
	void I12LeadSample::ZeroI12LeadSample()
	{
		::memset(this, 0, sizeof(I12LeadSample));
	}

	// 返回特定导联的电压值
	float I12LeadSample::Get_fLeadSample( RhythmLead eRhythmLead )
	{
		float   fLeadSample = 0.0f;
		switch( eRhythmLead )
		{
		case Lead_I:
			{
				fLeadSample  = m_fSampleI;
				break;
			}
		case Lead_II:
			{
				fLeadSample  = m_fSampleII;
				break;
			}
		case Lead_III:
			{
				fLeadSample  = m_fSampleIII;
				break;
			}
		case Lead_aVR:
			{
				fLeadSample  = m_fSampleaVR;
				break;
			}
		case Lead_aVL:
			{
				fLeadSample  = m_fSampleaVL;
				break;
			}
		case Lead_aVF:
			{
				fLeadSample  = m_fSampleaVF;
				break;
			}
		case Lead_V1:
			{
				fLeadSample  = m_fSampleV1;
				break;
			}
		case Lead_V2:
			{
				fLeadSample  = m_fSampleV2;
				break;
			}
		case Lead_V3:
			{
				fLeadSample  = m_fSampleV3;
				break;
			}
		case Lead_V4:
			{
				fLeadSample  = m_fSampleV4;
				break;
			}
		case Lead_V5:
			{
				fLeadSample  = m_fSampleV5;
				break;
			}
		case Lead_V6:
			{
				fLeadSample  = m_fSampleV6;
				break;
			}
		}
		return fLeadSample;
	}

	//---------------------------------------------------------------------------------------------------------
	//结构  _CPRRule_DetailStruct
	_CPRRule_DetailStruct::_CPRRule_DetailStruct()
	{
		m_bBreath = false;  //按压
		m_nNumber = -1;
		nextDetailPtr = NULL;
	}

	_CPRRule_DetailStruct::_CPRRule_DetailStruct(bool bBreath, int nNumber)
	{
		m_bBreath = bBreath;
		m_nNumber = nNumber;
		nextDetailPtr = NULL;
	}

	void _CPRRule_DetailStruct::Copy(_CPRRule_DetailStruct *pDetail)
	{
		m_bBreath = pDetail->m_bBreath;
		m_nNumber = pDetail->m_nNumber;
	}

	//结构  _CPRRuleStruct
	_CPRRuleStruct::_CPRRuleStruct()
	{
		m_nCycle = 0;
		detailRules = NULL;
	}

	_CPRRuleStruct::~_CPRRuleStruct()
	{
		_CPRRule_DetailStruct *pPtr = detailRules;
		while( pPtr != NULL )
		{
			_CPRRule_DetailStruct *pTmp = pPtr->getNextDetailRule();
			delete pPtr;
			pPtr = pTmp;
		}
		detailRules = NULL;
	}

	void _CPRRuleStruct::addNewDetail(_CPRRule_DetailStruct *pDetail)
	{
		if( detailRules == NULL )
		{
			detailRules = pDetail;
		}
		else
		{
			//查到队尾后添加
			_CPRRule_DetailStruct *tmp = detailRules;
			while( tmp != NULL )
			{
				if( tmp->getNextDetailRule() == NULL )
				{
					tmp->setNextDetailRule(pDetail);
					break;
				}
				else
				{
					tmp = tmp->getNextDetailRule();
				}
			}
		}
	}

	void _CPRRuleStruct::setDefaultCPRRule(int nCycle/*=5*/)
	{
		setEmpty();
		//常规CPR
		m_eRuleType = eCPRGeneralType;
		//---周期性循环操作
		m_nCycle = nCycle;
		//按压次数
		_CPRRule_DetailStruct *pDetail = new _CPRRule_DetailStruct(false, 30);
		addNewDetail(pDetail);
		//---两口气
		_CPRRule_DetailStruct *pBreathDetail = new _CPRRule_DetailStruct(true, 2);
		addNewDetail(pBreathDetail);
	}

	//只按压
    void _CPRRuleStruct::setOnlyPressure(long lNumber)
	{
		setEmpty();
		//常规CPR
		m_eRuleType = eCPROnlyPressureType;
		//---周期性循环操作
		m_nCycle = -1;
		//吹气次数
		_CPRRule_DetailStruct *pDetail = new _CPRRule_DetailStruct(false, -1);
		addNewDetail(pDetail);
	}

	//只吹气
	void _CPRRuleStruct::setOnlyBreath()
	{
		setEmpty();
		//常规CPR
		m_eRuleType = eCPROnlyBreathType;
		//---周期性循环操作
		m_nCycle = -1;
		//吹气次数
		_CPRRule_DetailStruct *pDetail = new _CPRRule_DetailStruct(true, -1);
		addNewDetail(pDetail);
	}

	void _CPRRuleStruct::setEmpty()
	{
		m_nCycle = 0;
		_CPRRule_DetailStruct *pPtr = detailRules;
		while( pPtr != NULL )
		{
			_CPRRule_DetailStruct *pTmp = pPtr->getNextDetailRule();
			delete pPtr;
			pPtr = pTmp;
		}
		detailRules = NULL;
	}

	void _CPRRuleStruct::copy(_CPRRuleStruct *pRule)
	{
		setEmpty();

		m_eRuleType = pRule->m_eRuleType;
		m_nCycle    = pRule->m_nCycle;

		_CPRRule_DetailStruct *pDetailPtr = pRule->detailRules;
		while( pDetailPtr != NULL )
		{
			_CPRRule_DetailStruct *pNewDetail = new _CPRRule_DetailStruct;
			pNewDetail->Copy(pDetailPtr);
			//添加新项
			addNewDetail(pNewDetail);

			pDetailPtr = pDetailPtr->getNextDetailRule();
		}
	}

	//--------------------------------------------------------------------------------------------------
	_EventLog_struct::_EventLog_struct()
	{
		m_eEventSign  = ES_Normal;
	}
}
