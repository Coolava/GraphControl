#pragma once
#include <afxwin.h>
#include <gdiplus.h>
#include <memory>

class CPlot 
{
public:
	virtual ~CPlot() {};
	/*Plot area*/
	CRect rcPlot;

	/*Plot color*/
	Gdiplus::Color color = Gdiplus::Color::DodgerBlue;

	virtual Gdiplus::Bitmap* getBitmap() = 0;
	virtual void setColor(Gdiplus::Color color) = 0;

	/*In Circleplot inherite this function*/
	virtual void setValue(Gdiplus::REAL startAngle, Gdiplus::REAL sweepAngle);

	/*In Linearplot inherite this function*/
	virtual void addPoint(Gdiplus::REAL value);


};

