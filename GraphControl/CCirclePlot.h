#pragma once
#include "CPlot.h"
#include <memory>

using namespace std;
class CCirclePlot :
	public CPlot
{
public:
	CCirclePlot();
	CCirclePlot(CRect rc);
	~CCirclePlot();
	CCirclePlot(CCirclePlot&&);

public:
	virtual void setColor(Gdiplus::Color _color);
	virtual void setValue(Gdiplus::REAL startAngle, Gdiplus::REAL sweepAngle);
	virtual Gdiplus::Bitmap* getBitmap();

	//virtual void setPlotColor(Gdiplus::Color _color);
private:
	Gdiplus::REAL startAngle = 0.0f;
	Gdiplus::REAL sweepAngle = 0.0f;


	unique_ptr<Gdiplus::Bitmap> bitmap;
	unique_ptr<Gdiplus::Graphics> graphics;

	//Gdiplus::Color color = Gdiplus::Color::DodgerBlue;
};

