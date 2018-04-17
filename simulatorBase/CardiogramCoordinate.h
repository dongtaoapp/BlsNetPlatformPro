#pragma once
#include ".\WCD.h"

#include "..\Common\ECGParams.h"

namespace jysoft { namespace simulator { namespace ecg {

	/*心电图纸的参数：
			X轴：   1大格为0.1秒
					1大格为5毫米
			Y轴：   1大格为0.5毫伏
			速度：  25毫米/秒
	*/
	class CCardiogramUCD;
    class SIMULATORBASESHARED_EXPORT CCardiogramCoordinate
	{
	public:
		CCardiogramCoordinate();
		~CCardiogramCoordinate(void);
	public://重要函数CCardiogramCoordinate
		void Initialize(float fx, float fy, int iSampleSec, const RectF &rtClient,float fScale = 1.0f, bool bToRight=false);
		// 屏幕X轴上的fX长度转换为逻辑的值
		double ScreenDvToLogic_X(float fX);
		// 根据参数修改坐标系
		void Modify(CECGParams * pParams);
		// 设为缺省状态下的坐标系
		void Default(void);
		// 象素转换为毫米单位(由坐标系决定)
		float PixelToMillimeterEx(int nPixel);
		// 根据逻辑长度（毫米），得到所代表的时间(0.1毫秒)
		int GetTime(int nLogicL);
		int GetTimeEx(float fLogicL);
		// 毫米转换为象素单位(由坐标系决定)
		int MillimeterToPixelEx(float fLength);
		int GetMillimeterToStep(float fLength);
		//整个放大
		void ZoomFixedCurve(float fZoom);
		//放大Y轴
		void ZoomYScale(float fZoom_Y);
	public://属性
		inline CCardiogramUCD * GetUCDPtr() const {return m_pUCD;};
		inline CWCD * GetWCDPtr() {return &m_cWCD;};
	protected:
		CWCD                     m_cWCD;
		CCardiogramUCD *         m_pUCD;
		float                    m_fScale;
	};

}}}
