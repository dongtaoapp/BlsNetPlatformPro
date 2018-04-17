#include ".\wcd.h"

namespace jysoft { namespace simulator {

	CWCD::CWCD(void)
	{
		m_fScale = 1.0f;
		m_fx = 1.0f;
		m_fy = 1.0f;
	}

	CWCD::~CWCD(void)
	{
	}

	// 函数名称： InitializeWCD
	// 功能说明： 初始化世界指标系
    // 返回值：
    // 参数： ：fx,fy:
    // 参数： float fScale
    void CWCD::InitializeWCD(float fx, float fy, float fScale/*=1.0f*/)
	{//注：1(logical value) = 0.01mm
        //int iHorzSize = ::GetDeviceCaps(hDC,HORZSIZE); //Width, in millimeters, of the physical screen.
        //int iVertSize = ::GetDeviceCaps(hDC,VERTSIZE); //Height, in millimeters, of the physical screen.
        //int iHorzRes  = ::GetDeviceCaps(hDC,HORZRES);  //Width, in pixels, of the screen.
        //int iVertRes  = ::GetDeviceCaps(hDC,VERTRES);  //Height, in raster lines, of the screen
        m_fx = /*GetWdcMultiple()**/1.0f*fx/100;
        m_fy = /*GetWdcMultiple()**/1.0f*fy/100;
		Set_Scale(fScale);
	}

	void CWCD::TransformPointsToD(PointF * pts, int iCount)
	{
		m_cLtoD.TransformPoints(pts,iCount);
	}

	void CWCD::TransformPointsToL(PointF * pts, int iCount)
	{
		m_cDtoL.TransformPoints(pts,iCount);
	}

	void CWCD::Set_Scale(float fScale)
	{
		m_fScale = fScale;
		//由逻辑坐标得到对应的设备坐标
		m_cLtoD.SetElements(1.0f,0.0f,0.0f,1.0f,0.0f,0.0f);
		m_cLtoD.Multiply(&Matrix(fScale,0.0f,0.0f,fScale,0.0f,0.0f),MatrixOrderAppend);
		m_cLtoD.Multiply(&Matrix(m_fx,0.0f,0.0f,m_fy,0.0f,0.0f),MatrixOrderAppend);
		m_cLtoD.Multiply(&Matrix(1.0f,0.0f,0.0f,-1.0f,0.0f,0.0f),MatrixOrderAppend);

		//由设备坐标得到对应的逻辑坐标
		m_cDtoL.SetElements(1.0f,0.0f,0.0f,1.0f,0.0f,0.0f);
		m_cDtoL.Multiply(&Matrix(1.0f,0.0f,0.0f,-1.0f,0.0f,0.0f),MatrixOrderAppend);
		m_cDtoL.Multiply(&Matrix(1.0f/m_fx,0.0f,0.0f,1.0f/m_fy,0.0f,0.0f),MatrixOrderAppend);
		m_cDtoL.Multiply(&Matrix(1.0f/fScale,0.0f,0.0f,1.0f/fScale,0.0f,0.0f),MatrixOrderAppend);
	}

	//移动原点坐标
    void CWCD::TranslateOrigin(PointF ptDvOrigin)
	{
		//由逻辑坐标得到对应的设备坐标
		m_cLtoD.SetElements(1.0f,0.0f,0.0f,1.0f,0.0f,0.0f);
		m_cLtoD.Multiply(&Matrix(m_fScale,0.0f,0.0f,m_fScale,0.0f,0.0f),MatrixOrderAppend);
		m_cLtoD.Multiply(&Matrix(m_fx,0.0f,0.0f,m_fy,0.0f,0.0f),MatrixOrderAppend);
        m_cLtoD.Multiply(&Matrix(1.0f,0.0f,0.0f,-1.0f,1.0f*ptDvOrigin.X,1.0f*ptDvOrigin.Y),MatrixOrderAppend);

		//由设备坐标得到对应的逻辑坐标
		m_cDtoL.SetElements(1.0f,0.0f,0.0f,1.0f,0.0f,0.0f);
        m_cDtoL.Multiply(&Matrix(1.0f,0.0f,0.0f,1.0f,-ptDvOrigin.X,-1.0f*ptDvOrigin.Y),MatrixOrderAppend);
		m_cDtoL.Multiply(&Matrix(1.0f,0.0f,0.0f,-1.0f,0.0f,0.0f),MatrixOrderAppend);
		m_cDtoL.Multiply(&Matrix(1.0f/m_fx,0.0f,0.0f,1.0f/m_fy,0.0f,0.0f),MatrixOrderAppend);
		m_cDtoL.Multiply(&Matrix(1.0f/m_fScale,0.0f,0.0f,1.0f/m_fScale,0.0f,0.0f),MatrixOrderAppend);
	}

}}
