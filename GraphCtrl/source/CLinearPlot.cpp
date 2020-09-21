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

	//if (bitmap)
	//{
	//	bitmap.reset();
	//	//Gdiplus::Bitmap* bmp = bitmap.release();
	//	//delete bmp;
	//}
	//if (graphics)
	//{
	//	graphics.reset();
	//	//Gdiplus::Graphics* grp = graphics.release();
	//	//delete grp;
	//}
}

CLinearPlot::CLinearPlot(CLinearPlot&&) noexcept
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

	//size_t pointCount = 0;
	//if (axisInfo->xAxis.size() < values.size())
	//{
	//	axisInfo->xAxis.begin = values.size() - (size_t)axisInfo->xAxis.size();
	//	axisInfo->xAxis.end = values.size();
	//	pointCount = static_cast<size_t>(axisInfo->xAxis.size());
	//}
	//else
	//{
	//	pointCount = values.size();
	//	//axisInfo->xAxis.begin = 0;
	//	//axisInfo->xAxis.end = values.size();
	//}
	//
	//axisInfo->xAxis.minimum = axisInfo->xAxis.begin;
	//axisInfo->xAxis.maximum = pointCount;


	/*Draw plot*/
	if (axisInfo->xAxis.size() > 0)
	{
		Gdiplus::REAL minimum = values[axisInfo->xAxis.begin], maximum = values[axisInfo->xAxis.begin];

		/*get minmax value*/
		auto minmax = std::minmax_element(values.begin() + axisInfo->xAxis.begin, values.end());
		axisInfo->yAxis.minimum = minimum = *minmax.first;
		axisInfo->yAxis.maximum = maximum = *minmax.second;

		axisInfo->xAxis.minimum = axisInfo->xAxis.begin;
		axisInfo->xAxis.maximum = values.size();

		/*move to center*/
		Gdiplus::REAL centerValue = (minimum + maximum) / 2;

		/*adjust y resolution*/
		axisInfo->Resolution.y = maximum - minimum;
		axisInfo->Resolution.x = axisInfo->xAxis.maximum - axisInfo->xAxis.minimum;

		vector<Gdiplus::PointF> points;
		for (size_t i = 0; i < axisInfo->xAxis.maximum; i++)
		{
			size_t pos = i + static_cast<size_t>(axisInfo->xAxis.begin);
			auto pixel_y = axisInfo->yAxis.size() / axisInfo->Resolution.y;
			auto pixel_x = axisInfo->xAxis.size() / axisInfo->Resolution.x;
			points.push_back(Gdiplus::PointF(i* pixel_x, ( (maximum - values[pos]) * pixel_y /* + (y_center- centerValue)*/)));

		}

		graphics->DrawLines(&pen, &points[0], axisInfo->xAxis.maximum);
	}

}

Gdiplus::Bitmap* CLinearPlot::getBitmap()
{
	return bitmap.get();
}
