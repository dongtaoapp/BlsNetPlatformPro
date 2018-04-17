#pragma once
#include ".\wcd.h"


namespace jysoft { namespace simulator { namespace ecg {

    class SIMULATORBASESHARED_EXPORT CCardiogramUCD : public CWCD
	{
	protected:
		CWCD *m_pWorldCordinate;
	public:
		CCardiogramUCD(CWCD *pWorldCord, int iSampleSec, RectF rtRegion, bool bToRight = false);
		~CCardiogramUCD(void);
	public:
		void Set_Scale_X(float fScaleX);
		void Set_Scale_Y(float fScaleY);
		void TransformPointsToD(PointF * pts, int iCount);
		void TransformPointsToL(PointF * pts, int iCount);
	protected:
		void Initialize();
	protected:
		float    m_fScale_X;
		float    m_fScale_Y;
	private:
		RectF     m_rtRegion;
		bool     m_bToRight;
	};

}}}
