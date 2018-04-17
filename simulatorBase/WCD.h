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
		Matrix  m_cLtoD;//逻辑-->设备
		Matrix  m_cDtoL;//设备-->逻辑
		float   m_fScale;
		REAL    m_fx;
		REAL    m_fy;
	public:
		CWCD(void);
		virtual ~CWCD(void);
	public:
		// 初始化世界指标系
        void InitializeWCD(float fx, float fy, float fScale = 1.0f);
		//移动原点坐标
        void TranslateOrigin(PointF ptDvOrigin);
		void Set_Scale(float fScale);
		inline Matrix *GetLtoDMatrixPtr(){ return &m_cLtoD;};
		inline Matrix *GetDtoLMatrixPtr(){ return &m_cDtoL;};
		//毫米转换为逻辑值
		inline float MillimeterToLogicalUnit(float fLength) { return fLength * 100; };
	public:
		virtual void TransformPointsToD(PointF * pts, int iCount);
		virtual void TransformPointsToL(PointF * pts, int iCount);
		inline  float GetScale() { return m_fScale;};
		inline  float Get_fx() { return m_fx; };
		inline  float Get_fy() { return m_fy; };
	};

}}
