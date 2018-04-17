#pragma once
#include "Windows.h"
#include "gdiplus.h"
#include ".\simulatorbase_global.h"

/////////////////////////////////////modified hjg/////////////////////////////////////////////////////
///
using namespace Gdiplus;
namespace jysoft { namespace simulator {

    class SIMULATORBASESHARED_EXPORT CWCD
	{
	protected:
		Matrix  m_cLtoD;//�߼�-->�豸
		Matrix  m_cDtoL;//�豸-->�߼�
		float   m_fScale;
		REAL    m_fx;
		REAL    m_fy;
	public:
		CWCD(void);
		virtual ~CWCD(void);
	public:
		// ��ʼ������ָ��ϵ
        void InitializeWCD(float fx, float fy, float fScale = 1.0f);
		//�ƶ�ԭ������
        void TranslateOrigin(PointF ptDvOrigin);
		void Set_Scale(float fScale);
		inline Matrix *GetLtoDMatrixPtr(){ return &m_cLtoD;};
		inline Matrix *GetDtoLMatrixPtr(){ return &m_cDtoL;};
		//����ת��Ϊ�߼�ֵ
		inline float MillimeterToLogicalUnit(float fLength) { return fLength * 100; };
	public:
		virtual void TransformPointsToD(PointF * pts, int iCount);
		virtual void TransformPointsToL(PointF * pts, int iCount);
		inline  float GetScale() { return m_fScale;};
		inline  float Get_fx() { return m_fx; };
		inline  float Get_fy() { return m_fy; };
	};

}}
