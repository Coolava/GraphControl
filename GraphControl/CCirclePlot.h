#pragma once
#include "CPlot.h"
#include <memory>

using namespace std;
class CCirclePlot :
	public CPlot
{
public:
	CCirclePlot();
	CCirclePlot(CRect rc, CWnd* pParent, UINT nID);
	~CCirclePlot();
	CCirclePlot(CCirclePlot&&);

public:
	void setColor(Gdiplus::Color _color);
	void setValue(Gdiplus::REAL startAngle, Gdiplus::REAL sweepAngle);
	virtual Gdiplus::Bitmap* getBitmap();

private:
	Gdiplus::REAL startAngle = 0.0f;
	Gdiplus::REAL sweepAngle = 0.0f;


	unique_ptr<Gdiplus::Bitmap> bitmap;
	unique_ptr<Gdiplus::Graphics> graphics;

	Gdiplus::Color color = Gdiplus::Color::DodgerBlue;
};

