#include "CCirclePlot.h"

#include <vector>
CCirclePlot::CCirclePlot()
{
}

CCirclePlot::CCirclePlot(CRect rc)
{
	//CWnd::Create(NULL, NULL, WS_CHILD | WS_VISIBLE, rc, pParent, nID);
	rcPlot = rc;
}

CCirclePlot::~CCirclePlot()
{
	
	if (bitmap)
	{
		bitmap.reset();
		//Gdiplus::Bitmap* bmp = bitmap.release();
		//delete bmp;
	}
	if (graphics)
	{
		graphics.reset();
		//Gdiplus::Graphics* grp = graphics.release();
		//delete grp;
	}
}

CCirclePlot::CCirclePlot(CCirclePlot&&)
{
}


void CCirclePlot::setColor(Gdiplus::Color _color)
{
	color = _color;
}

void CCirclePlot::setValue(Gdiplus::REAL _startAngle, Gdiplus::REAL _sweepAngle)
{
	//CRect rc;
	//GetClientRect(rc);

	bitmap.reset(new Gdiplus::Bitmap(rcPlot.Width(), rcPlot.Height(), PixelFormat32bppARGB));
	graphics.reset(Gdiplus::Graphics::FromImage(bitmap.get()));

	Gdiplus::RectF ellipseRect(rcPlot.left + 1.0f, rcPlot.top + 1.0f, rcPlot.Width() - 2.0f, rcPlot.Height() - 2.0f);

	Gdiplus::SolidBrush brush(color);

	Gdiplus::Pen pen(color);
	startAngle = _startAngle;
	sweepAngle = _sweepAngle;
	graphics->SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);

	//graphics->FillPie(&brush, ellipseRect, startAngle, sweepAngle );

	/*Test code*/
	//Gdiplus::PointF points[100];
	std::vector<Gdiplus::PointF> points;
	for (int i = 0; i < 100; i++)
	{
		//points[i] = Gdiplus::PointF(i,10*sin(2 * 3.14 /100* (i+ _sweepAngle))+20);
		points.push_back(Gdiplus::PointF(i,10*sin(2 * 3.14 /100* (i+ _sweepAngle))+20));
	}
	graphics->DrawBeziers(&pen, &points[0], 100);
	/////////////////////////////////////////////////////////

	//graphics->FillPie(&brush, ellipseRect, startAngle, sweepAngle);

}

Gdiplus::Bitmap* CCirclePlot::getBitmap()
{
	return bitmap.get();
}
