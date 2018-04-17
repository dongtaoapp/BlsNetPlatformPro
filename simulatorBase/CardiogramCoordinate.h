#pragma once
#include ".\WCD.h"

#include "..\Common\ECGParams.h"

namespace jysoft { namespace simulator { namespace ecg {

	/*�ĵ�ͼֽ�Ĳ�����
			X�᣺   1���Ϊ0.1��
					1���Ϊ5����
			Y�᣺   1���Ϊ0.5����
			�ٶȣ�  25����/��
	*/
	class CCardiogramUCD;
    class SIMULATORBASESHARED_EXPORT CCardiogramCoordinate
	{
	public:
		CCardiogramCoordinate();
		~CCardiogramCoordinate(void);
	public://��Ҫ����CCardiogramCoordinate
		void Initialize(float fx, float fy, int iSampleSec, const RectF &rtClient,float fScale = 1.0f, bool bToRight=false);
		// ��ĻX���ϵ�fX����ת��Ϊ�߼���ֵ
		double ScreenDvToLogic_X(float fX);
		// ���ݲ����޸�����ϵ
		void Modify(CECGParams * pParams);
		// ��Ϊȱʡ״̬�µ�����ϵ
		void Default(void);
		// ����ת��Ϊ���׵�λ(������ϵ����)
		float PixelToMillimeterEx(int nPixel);
		// �����߼����ȣ����ף����õ��������ʱ��(0.1����)
		int GetTime(int nLogicL);
		int GetTimeEx(float fLogicL);
		// ����ת��Ϊ���ص�λ(������ϵ����)
		int MillimeterToPixelEx(float fLength);
		int GetMillimeterToStep(float fLength);
		//�����Ŵ�
		void ZoomFixedCurve(float fZoom);
		//�Ŵ�Y��
		void ZoomYScale(float fZoom_Y);
	public://����
		inline CCardiogramUCD * GetUCDPtr() const {return m_pUCD;};
		inline CWCD * GetWCDPtr() {return &m_cWCD;};
	protected:
		CWCD                     m_cWCD;
		CCardiogramUCD *         m_pUCD;
		float                    m_fScale;
	};

}}}
