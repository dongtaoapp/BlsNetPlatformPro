#pragma once
#include ".\simulatorbase_global.h"

#include "..\common\iupdateshowvir.h"
#include "..\common\CommonGlobal.h"

namespace jysoft{  namespace cpr {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     CPR����������ʾ�ӿ�
	�����ˣ�	 hjg
	����ʱ�䣺   2017/2/25
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT CCPRRealTimeUpdateInterface : public IUpdateShowVir
	{
	public:
		CCPRRealTimeUpdateInterface(void);
		virtual ~CCPRRealTimeUpdateInterface(void);
	public://�ӿں�������
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
		virtual bool isKindOf(const std::string &className);
	public:
		//�õ�CPR������
		void OnLoadCPRSample(const _CPRData *ptrCPRDatas, int nLength);
		// ��������־
		void OnAddCPRErrorSign(_eCPRErrorSign eErrorSign);
	protected:
		//�Խ���ʾ��֪ͨ
		virtual void doLinkCPRRealTimeUpdateShow() { };
		//�Ͽ���ʾ��֪ͨ
		virtual void cutLinkCPRRealTimeUpdateShow() { };
		//�õ�CPR������
		virtual void LoadCPRSample(const _CPRData *ptrCPRDatas, int nLength) = 0;
		//��������־
		virtual void AddCPRErrorSign(_eCPRErrorSign eErrorSign) = 0;
	};

}}
