#pragma once
#include "CPlot.h"
#include <memory>
#include <vector>

using namespace std;


template<typename T>
class Axis
{
public:
	Axis() {};
	Axis(T _begin, T _end) :begin(_begin), end(_end) {}
	T begin;
	T end;

	inline T size() { return (end - begin); }
};

template<typename T>
class CResolution
{
public:
	CResolution() {};
	CResolution(T _x, T _y) :x(_x), y(_y) {}
	T x;
	T y;
};
class CAxisInfo
{
public:
	CAxisInfo() {}

	CAxisInfo(CRect rc)
	{
		xAxis.begin = 0;
		xAxis.end = (Gdiplus::REAL)rc.Width();
		yAxis.begin = 0;
		yAxis.end = (Gdiplus::REAL)rc.Height();
		Resolution.x = (Gdiplus::REAL)rc.Width();
		Resolution.y = (Gdiplus::REAL)rc.Height();
	}
	CAxisInfo(Axis<Gdiplus::REAL> _xAxis, Axis<Gdiplus::REAL> _yAxis, CResolution<Gdiplus::REAL> _Resolution)
		: xAxis(_xAxis), yAxis(_yAxis), Resolution(_Resolution){}
	Axis<Gdiplus::REAL> xAxis = { 0,0 };
	Axis<Gdiplus::REAL> yAxis = { 0,0 };

	/*number of points*/
	CResolution< Gdiplus::REAL> Resolution = { 0,0 };
};

class CLinearPlot:
	public CPlot
{
public:
	CLinearPlot();
	CLinearPlot(CRect rc);
	~CLinearPlot();
	CLinearPlot(CLinearPlot&&) ;

public:
	virtual void setColor(Gdiplus::Color _color);

	/*Add value to end of array*/
	virtual void addPoint(Gdiplus::REAL value);

	virtual Gdiplus::Bitmap* getBitmap();
	//virtual void setPlotColor(Gdiplus::Color _color);

	void setAxisInfo(CAxisInfo info);
private:
	Gdiplus::REAL startAngle = 0.0f;
	Gdiplus::REAL sweepAngle = 0.0f;

	/*contain displayed point info*/
	//Axis< Gdiplus::REAL> pointInfo;
	Axis< size_t> pointInfo;

	/*Array of points*/
	vector<Gdiplus::PointF> points;

	CAxisInfo axisInfo;

	vector<Gdiplus::REAL> values;

	unique_ptr<Gdiplus::Bitmap> bitmap;
	unique_ptr<Gdiplus::Graphics> graphics;

	//Gdiplus::Color color = Gdiplus::Color::DodgerBlue;
};

