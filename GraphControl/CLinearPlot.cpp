#include "CLinearPlot.h"

CLinearPlot::CLinearPlot()
{
}

CLinearPlot::CLinearPlot(CRect rc)
{
	//CWnd::Create(NULL, NULL, WS_CHILD | WS_VISIBLE, rc, pParent, nID);
	rcPlot = rc;

	axisInfo = CAxisInfo(rc);

}

CLinearPlot::~CLinearPlot()
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

CLinearPlot::CLinearPlot(CLinearPlot&&)
{
}


void CLinearPlot::setColor(Gdiplus::Color _color)
{
	color = _color;
}



void CLinearPlot::addPoint(Gdiplus::REAL value)
{
	values.push_back(value);
	axisInfo.xAxis.size();


	bitmap.reset(new Gdiplus::Bitmap(rcPlot.Width(), rcPlot.Height(), PixelFormat32bppARGB));
	graphics.reset(Gdiplus::Graphics::FromImage(bitmap.get()));

	Gdiplus::RectF ellipseRect(rcPlot.left + 1.0f, rcPlot.top + 1.0f, rcPlot.Width() - 2.0f, rcPlot.Height() - 2.0f);

	Gdiplus::SolidBrush brush(color);


	graphics->SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);

	Gdiplus::Pen pen(color);

	pointInfo.end = values.size();

	if (pointInfo.end > 0)
	{

		if ((axisInfo.xAxis.end - values.size()) > 0)
		{
			pointInfo.begin = 0;
		}
		else
		{
			pointInfo.begin = values.size() - axisInfo.xAxis.size();
		}

		points.clear();
		for (size_t i = pointInfo.begin; i < pointInfo.end; i++)
		{
			points.push_back(Gdiplus::PointF(i - pointInfo.begin, value));
		}

		graphics->DrawBeziers(&pen, &points[pointInfo.begin], (INT)(pointInfo.end - pointInfo.begin));
	}
	
	// (INT)(pointInfo.end - pointInfo.begin));
	//graphics->DrawBeziers(&pen, &points[pointInfo.begin], (INT)(pointInfo.end - pointInfo.begin));
	//;graphics->FillPie(&brush, ellipseRect, startAngle, sweepAngle);

}

Gdiplus::Bitmap* CLinearPlot::getBitmap()
{
	return bitmap.get();
}

void CLinearPlot::setAxisInfo(CAxisInfo info)
{
	axisInfo = info;
}
