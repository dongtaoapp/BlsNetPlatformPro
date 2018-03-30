#pragma once
#include ".\simulatorbase_global.h"

#include "..\Common\ibedirectelinksvir.h"
#include "..\Common\CommonGlobal.h"


namespace jysoft { namespace simulator {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ���������źŽӿ�
	�����ˣ�	 hjg
	����ʱ�䣺   2008/8/22
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT IHeartStartSign :  public IBedirecteLinksVir
	{
	public:
		IHeartStartSign(void);
		virtual ~IHeartStartSign(void);
	public:
		virtual bool isKindOf(const std::string &className);
	public:
		//���࿪ʼ����һ�����ڵ��������ź�
		virtual void HeartStartSignHandle(BasicRhythm eRhythm, int  nCycleTime, bool bHaveHeartSign) = 0;
        virtual void WatchHeartStartSign(bool bWatching) = 0;
	public:
		/*******************************************************************************/
		// �������ƣ� OnHeartStartSignHandle
		// ���ܣ�   ���࿪ʼ����һ�����ڵ��������ź�
		// ������
		//        BasicRhythm eRhythm:  ��������
		//        int  nCycleTime:      ��������ʱ�䣨��λ��0.1���룩
		// ����ֵ:  
		void OnHeartStartSignHandle(BasicRhythm eRhythm, int  nCycleTime, bool bHaveHeartSign);
		/*******************************************************************************/
		// �������ƣ� OnWatchHeartStartSign
		// ���ܣ�   
		// ������
		//        BOOL bWatching:  
		// ����ֵ:  
		void OnWatchHeartStartSign(bool bWatching);
	};

}}
