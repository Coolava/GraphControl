#pragma once
#include "CPlot.h"
#include "Define.h"
#include <memory>

#include <vector>
#include <algorithm>
using namespace std;


class CLinearPlot:
	public CPlot
{
public:
	CLinearPlot();
	CLinearPlot(CRect rc, std::shared_ptr<CAxisInfo> axis);
	virtual ~CLinearPlot();
	CLinearPlot(CLinearPlot&&) noexcept;

public:
	virtual void setColor(Gdiplus::Color _color);

	/*Add value to end of array*/
	virtual void addPoint(Gdiplus::REAL value);

	virtual Gdiplus::Bitmap* getBitmap();
	//virtual void setPlotColor(Gdiplus::Color _color);

private:
	Gdiplus::REAL startAngle = 0.0f;
	Gdiplus::REAL sweepAngle = 0.0f;

	/*contain displayed point info*/
	Axis< size_t> pointInfo;

	std::shared_ptr<CAxisInfo> axisInfo;

	/*Array of points*/
	vector<Gdiplus::PointF> points;

	/*actual value*/
	vector<Gdiplus::REAL> values;

	unique_ptr<Gdiplus::Bitmap> bitmap;
	unique_ptr<Gdiplus::Graphics> graphics;

	//Gdiplus::Color color = Gdiplus::Color::DodgerBlue;
};

