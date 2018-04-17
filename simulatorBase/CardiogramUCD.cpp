#include ".\CardiogramUCD.h"
#include ".\Sample.h"
#include <boost/assert.hpp>


namespace jysoft { namespace simulator { namespace ecg {

	CCardiogramUCD::CCardiogramUCD(CWCD *pWorldCord, int iSampleSec, RectF rtRegion, bool bToRight/*= false*/)
	{
        BOOST_ASSERT(pWorldCord); //pWorldCord����Ϊ��
		m_pWorldCordinate = pWorldCord;
		//Y�᣺   1���Ϊ0.5����(����)
		//X�᣺   1���Ϊ5����
		/*���㹫ʽ���ĵ�ͼ���ٶ�ΪV=25����/�룻X��ĵ�λx=0.01���ף����ĳ��ȣ�L=5����
					V/x=ÿ��Ĳ�����*����
		*/
		m_cLtoD.SetElements(1.0f,0.0f,0.0f,1.0f,0.0f,0.0f);
		m_fx =(25/0.01)/iSampleSec ;//����
		m_fy = 10.0f;//( 4/0.01* 10000 ) /pSample->m_iSampleVolt;
		m_rtRegion = rtRegion;
		m_bToRight = bToRight;
		m_fScale_X = 1.0f;
		m_fScale_Y = 1.0f;
		Initialize();
	}

	CCardiogramUCD::~CCardiogramUCD(void)
	{
		m_pWorldCordinate = NULL;
	}

	void CCardiogramUCD::Initialize()
	{
		m_cLtoD.SetElements(1.0f,0.0f,0.0f,1.0f,0.0f,0.0f);
		m_cLtoD.Multiply(&Matrix(m_fScale_X*m_fx,0.0f,0.0f,m_fScale_Y*m_fy,0.0f,0.0f),MatrixOrderAppend);
		m_cLtoD.Multiply(&Matrix(1.0f,0.0f,0.0f,1.0f,m_rtRegion.X,(m_rtRegion.Y+m_rtRegion.Height/2)),MatrixOrderAppend);
		if(m_bToRight == false)
			m_cLtoD.Multiply(&Matrix(1.0f,0.0f,0.0f,1.0f,m_rtRegion.GetRight(),0),MatrixOrderAppend);

		m_cDtoL.SetElements(1.0f,0.0f,0.0f,1.0f,0.0f,0.0f);
		if(m_bToRight == false)
			m_cLtoD.Multiply(&Matrix(1.0f,0.0f,0.0f,1.0f,-m_rtRegion.GetRight(),0),MatrixOrderAppend);
		m_cDtoL.Multiply(&Matrix(1.0f,0.0f,0.0f,1.0f,-m_rtRegion.X,-(m_rtRegion.Y+m_rtRegion.Height/2)),MatrixOrderAppend);
		m_cDtoL.Multiply(&Matrix(1.0f/(m_fScale_X*m_fx),0.0f,0.0f,1.0f/(m_fScale_Y*m_fy),0.0f,0.0f),MatrixOrderAppend);
	}

	void CCardiogramUCD::Set_Scale_X(float fScaleX)
	{
		m_fScale_X = fScaleX;
		Initialize();
	}

	void CCardiogramUCD::Set_Scale_Y(float fScaleY)
	{
		m_fScale_Y = fScaleY;
		Initialize();
	}

	//��Ļ����
	void CCardiogramUCD::TransformPointsToD(PointF * pts, int iCount)
	{
		m_cLtoD.TransformPoints(pts,iCount);
		m_pWorldCordinate->TransformPointsToD(pts,iCount);
	}
	//UCD�ϵ��߼�����
	void CCardiogramUCD::TransformPointsToL(PointF * pts, int iCount)
	{
		m_pWorldCordinate->TransformPointsToL(pts,iCount);
		m_cDtoL.TransformPoints(pts,iCount);
	}

}}}
