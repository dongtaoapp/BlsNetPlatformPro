#include ".\Sample.h"
#include ".\CardiogramUCD.h"
#include ".\CardiogramCoordinate.h"

namespace jysoft { namespace simulator { namespace ecg {

	CCardiogramCoordinate::CCardiogramCoordinate()
	{
		m_pUCD = NULL;
		m_fScale = 1.0f;
	}

	CCardiogramCoordinate::~CCardiogramCoordinate(void)
	{
		delete m_pUCD;
	}


	void CCardiogramCoordinate::Initialize(float fx, float fy, int iSampleSec, const RectF &rtClient,float fScale /*= 1.0f*/, bool bToRight/*=false*/)
	{
		m_fScale = fScale;
		m_cWCD.InitializeWCD(fx, fy, fScale);
		PointF ptPos[2];
		ptPos[0] = PointF(rtClient.GetLeft(),rtClient.GetTop());
		ptPos[1] = PointF(rtClient.GetRight(),rtClient.GetBottom());
		m_cWCD.TransformPointsToL(ptPos,2);
		PointF ptBegin;
		ptBegin.X = ptPos[0].X > ptPos[1].X ? ptPos[1].X : ptPos[0].X;
		ptBegin.Y = ptPos[0].Y > ptPos[1].Y ? ptPos[1].Y : ptPos[0].Y;
		RectF rtRegion(ptBegin,SizeF(::fabs(ptPos[0].X-ptPos[1].X),::fabs(ptPos[0].Y-ptPos[1].Y)));
		m_pUCD = new CCardiogramUCD(&m_cWCD, iSampleSec, rtRegion, bToRight);
	}

	// 屏幕X轴上的fX长度转换为逻辑的值
	double CCardiogramCoordinate::ScreenDvToLogic_X(float fX)
	{
		PointF DvPt(fX,0.0f);
		m_pUCD->TransformPointsToL(&DvPt,1);
		return (double)DvPt.X;
	}


	// 根据参数修改坐标系
	void CCardiogramCoordinate::Modify(CECGParams * pParams)
	{
		if(pParams->m_dwField & 0x00000040)
		{//放大尺寸
			m_pUCD->Set_Scale_Y(1.0f*pParams->m_uSize);
		}
		if(pParams->m_dwField & 0x00000080)
		{//心跳速度
			if(pParams->m_eSpeed == HS_Normal)
				m_pUCD->Set_Scale_X(1.0f);
			else
				m_pUCD->Set_Scale_X(2.0f);
		}
	}

	//放大Y轴
	void CCardiogramCoordinate::ZoomYScale(float fZoom_Y)
	{
		m_pUCD->Set_Scale_Y(fZoom_Y);
	}

	// 设为缺省状态下的坐标系
	void CCardiogramCoordinate::Default(void)
	{
		m_pUCD->Set_Scale_X(1.0f);
		m_pUCD->Set_Scale_Y(1.0f);
	}

	// 象素转换为毫米单位(由坐标系决定)
	float CCardiogramCoordinate::PixelToMillimeterEx(int nPixel)
	{//注：1(logical value) = 0.01mm
		PointF pt(1.0f*nPixel,0.0f);
		m_cWCD.TransformPointsToL(&pt,1);
		return pt.X/100;
	}

	// 根据逻辑长度（毫米），得到所代表的时间(0.1毫秒)
	int CCardiogramCoordinate::GetTime(int nLogicL)
	{
		int iRtnTime = GetTimeEx(1.0f*nLogicL);
		return iRtnTime;
	}

	int CCardiogramCoordinate::GetTimeEx(float fLogicL)
	{//注：1(logical value) = 0.01mm
		PointF pts(fLogicL*100,0.0f);
		m_pUCD->GetDtoLMatrixPtr()->TransformPoints(&pts,1);
		return int(pts.X + 0.001)*25;
	}

	// 毫米转换为象素单位(由坐标系决定)
	int CCardiogramCoordinate::MillimeterToPixelEx(float fLength)
	{//注：1(logical value) = 0.01mm
		PointF pt(fLength*100,0.0f);
		m_cWCD.TransformPointsToD(&pt,1);
		return (int)(pt.X+DEFINITE);
	}

	int CCardiogramCoordinate::GetMillimeterToStep(float fLength)
	{//注：1(logical value) = 0.01mm
		PointF pts(fLength*100,0.0f);
		m_pUCD->GetDtoLMatrixPtr()->TransformPoints(&pts,1);
		return int(pts.X + DEFINITE);
	}

	//整个放大
	void CCardiogramCoordinate::ZoomFixedCurve(float fZoom)
	{
		m_fScale = fZoom;
		m_cWCD.Set_Scale(fZoom);
	}

}}}
