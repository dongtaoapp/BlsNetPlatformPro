#pragma once
#include ".\transLayer_global.h"


#include "..\SimulatorBase\SimulateBaseGlobal.h"

struct TRANSLAYERSHARED_EXPORT _VirDataStruct
{
public:
	unsigned char*         m_pData;
	unsigned int           m_dwSize;
	_SIMULATECOMMANDTYPE   m_eCmdType;
	//--------------------------------------------------
	_VirDataStruct *m_pNextDataStructPtr;
public:
	_VirDataStruct()
	{
		m_pData = NULL;
		m_dwSize = 0;
		m_eCmdType = CT_NONE;
		m_pNextDataStructPtr = NULL;
	};
	virtual ~_VirDataStruct()
	{
		m_pData = NULL;
		if( m_pNextDataStructPtr != NULL )
		{
			delete m_pNextDataStructPtr;
		}
	}
};

struct TRANSLAYERSHARED_EXPORT _DataNewAllocStruct : public _VirDataStruct
{
public:
	_DataNewAllocStruct()
	{
	};
	virtual ~_DataNewAllocStruct()
	{
		delete [] m_pData;
	}
};
