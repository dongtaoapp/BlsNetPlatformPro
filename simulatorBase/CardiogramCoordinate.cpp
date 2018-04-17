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

	// ��ĻX���ϵ�fX����ת��Ϊ�߼���ֵ
	double CCardiogramCoordinate::ScreenDvToLogic_X(float fX)
	{
		PointF DvPt(fX,0.0f);
		m_pUCD->TransformPointsToL(&DvPt,1);
		return (double)DvPt.X;
	}


	// ���ݲ����޸�����ϵ
	void CCardiogramCoordinate::Modify(CECGParams * pParams)
	{
		if(pParams->m_dwField & 0x00000040)
		{//�Ŵ�ߴ�
			m_pUCD->Set_Scale_Y(1.0f*pParams->m_uSize);
		}
		if(pParams->m_dwField & 0x00000080)
		{//�����ٶ�
			if(pParams->m_eSpeed == HS_Normal)
				m_pUCD->Set_Scale_X(1.0f);
			else
				m_pUCD->Set_Scale_X(2.0f);
		}
	}

	//�Ŵ�Y��
	void CCardiogramCoordinate::ZoomYScale(float fZoom_Y)
	{
		m_pUCD->Set_Scale_Y(fZoom_Y);
	}

	// ��Ϊȱʡ״̬�µ�����ϵ
	void CCardiogramCoordinate::Default(void)
	{
		m_pUCD->Set_Scale_X(1.0f);
		m_pUCD->Set_Scale_Y(1.0f);
	}

	// ����ת��Ϊ���׵�λ(������ϵ����)
	float CCardiogramCoordinate::PixelToMillimeterEx(int nPixel)
	{//ע��1(logical value) = 0.01mm
		PointF pt(1.0f*nPixel,0.0f);
		m_cWCD.TransformPointsToL(&pt,1);
		return pt.X/100;
	}

	// �����߼����ȣ����ף����õ��������ʱ��(0.1����)
	int CCardiogramCoordinate::GetTime(int nLogicL)
	{
		int iRtnTime = GetTimeEx(1.0f*nLogicL);
		return iRtnTime;
	}

	int CCardiogramCoordinate::GetTimeEx(float fLogicL)
	{//ע��1(logical value) = 0.01mm
		PointF pts(fLogicL*100,0.0f);
		m_pUCD->GetDtoLMatrixPtr()->TransformPoints(&pts,1);
		return int(pts.X + 0.001)*25;
	}

	// ����ת��Ϊ���ص�λ(������ϵ����)
	int CCardiogramCoordinate::MillimeterToPixelEx(float fLength)
	{//ע��1(logical value) = 0.01mm
		PointF pt(fLength*100,0.0f);
		m_cWCD.TransformPointsToD(&pt,1);
		return (int)(pt.X+DEFINITE);
	}

	int CCardiogramCoordinate::GetMillimeterToStep(float fLength)
	{//ע��1(logical value) = 0.01mm
		PointF pts(fLength*100,0.0f);
		m_pUCD->GetDtoLMatrixPtr()->TransformPoints(&pts,1);
		return int(pts.X + DEFINITE);
	}

	//�����Ŵ�
	void CCardiogramCoordinate::ZoomFixedCurve(float fZoom)
	{
		m_fScale = fZoom;
		m_cWCD.Set_Scale(fZoom);
	}

}}}
