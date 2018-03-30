#pragma once
#include ".\simulatorbase_global.h"

#include "..\Common\IBedirecteLinksVir.h"

namespace jysoft{  namespace utility {

    class SIMULATORBASESHARED_EXPORT IPaneMoveControlInterface  : public IBedirecteLinksVir
	{
	public:
		IPaneMoveControlInterface(void);
		virtual ~IPaneMoveControlInterface(void);
	public:
		virtual bool isKindOf(const std::string &className);
	public:
		//�ƶ��컬������
		void OnPaneMoveOp();
		// ��ʼ���ĵ�ͼ
		void OnStart(bool bClear);
	protected:
		//�ƶ��컬������
		virtual void PaneMoveOp() = 0;
		// ��ʼ���ĵ�ͼ
		virtual void Start(bool bClear) = 0;
	};

}}
