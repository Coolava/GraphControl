#include "CLinearPlot.h"
CLinearPlot::CLinearPlot()
{
}

CLinearPlot::CLinearPlot(CRect rc,std::shared_ptr<CAxisInfo> axis)
{
	//CWnd::Create(NULL, NULL, WS_CHILD | WS_VISIBLE, rc, pParent, nID);
	rcPlot = rc;

	axisInfo = axis;
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

	Gdiplus::RectF ellipseRect(rcPlot.left + 1.0f, rcPlot.top + 1.0f, rcPlot.Width() - 2.0f, rcPlot.Height() - 2.0f);
	
	bitmap.reset(new Gdiplus::Bitmap(rcPlot.Width(), rcPlot.Height(), PixelFormat32bppARGB));
	graphics.reset(Gdiplus::Graphics::FromImage(bitmap.get()));
	graphics->SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);

	Gdiplus::Pen pen(color);

	/*Save values
	Will be used for slides
	*/
	values.push_back(value);

	/*
	Calculate X axis range to be displayed
	*/

	int pointCount = 0;
	if (axisInfo->xAxis.size() < values.size())
	{
		axisInfo->xAxis.begin = values.size() - (size_t)axisInfo->xAxis.size();
		axisInfo->xAxis.end = values.size();
		pointCount = axisInfo->xAxis.size();
	}
	else
	{
		pointCount = values.size();
		//axisInfo->xAxis.begin = 0;
		//axisInfo->xAxis.end = values.size();
	}
	
	/*Draw center lines*/
	Gdiplus::REAL y_center = (axisInfo->yAxis.size()) / 2 + axisInfo->yAxis.begin;

	/*Draw plot*/
	if (axisInfo->xAxis.size() > 0)
	{
		Gdiplus::REAL minimum = values[axisInfo->xAxis.begin], maximum = values[axisInfo->xAxis.begin];

		/*move to center*/
		auto minmax = std::minmax_element(values.begin() + axisInfo->xAxis.begin, values.end());
		minimum = *minmax.first;
		maximum = *minmax.second;

		Gdiplus::REAL centerValue = (minimum + maximum) / 2;

		vector<Gdiplus::PointF> points;
		for (size_t i = 0; i < pointCount; i++)
		{
			size_t pos = i + axisInfo->xAxis.begin;
			auto pixel = axisInfo->yAxis.size() / axisInfo->Resolution.y;
			points.push_back(Gdiplus::PointF(i, (values[pos] * pixel + (y_center- centerValue))));

		}

		graphics->DrawLines(&pen, &points[0], pointCount);
	}

}

Gdiplus::Bitmap* CLinearPlot::getBitmap()
{
	return bitmap.get();
}
