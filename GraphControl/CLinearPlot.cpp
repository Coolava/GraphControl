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
	bitmap.reset(new Gdiplus::Bitmap(rcPlot.Width(), rcPlot.Height(), PixelFormat32bppARGB));
	graphics.reset(Gdiplus::Graphics::FromImage(bitmap.get()));

	Gdiplus::RectF ellipseRect(rcPlot.left + 1.0f, rcPlot.top + 1.0f, rcPlot.Width() - 2.0f, rcPlot.Height() - 2.0f);

	graphics->SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);

	Gdiplus::Pen pen(color);

	/*Save values
	Will be used for slides
	*/
	values.push_back(value);

	axisInfo.xAxis.size();

	/*
	Calculate range to be displayed
	*/
	if (axisInfo.xAxis.size() < values.size())
	{
		pointInfo.begin = values.size() - (size_t)axisInfo.xAxis.size();
		pointInfo.end = values.size();
	}
	else
	{
		pointInfo.begin = 0;
		pointInfo.end = values.size();
	}


	if (pointInfo.size() > 0)
	{
		vector<Gdiplus::PointF> points;

		for (size_t i = 0; i < pointInfo.size(); i++)
		{
			size_t pos = i + pointInfo.begin;
			points.push_back(Gdiplus::PointF(i, values[pos]));
		}

		graphics->DrawLines(&pen, &points[0], pointInfo.size());
	}

}

Gdiplus::Bitmap* CLinearPlot::getBitmap()
{
	return bitmap.get();
}

void CLinearPlot::setAxisInfo(CAxisInfo info)
{
	axisInfo = info;
}
