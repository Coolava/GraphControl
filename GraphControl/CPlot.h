#pragma once
#include <afxwin.h>
#include <gdiplus.h>
#include <memory>

class CPlot :
	public CWnd
{
private:
public:

	/*Plot area*/
	CRect rcPlot;

	/*Plot color*/
	Gdiplus::Color color = Gdiplus::Color::DodgerBlue;

	virtual Gdiplus::Bitmap* getBitmap() = 0;
	virtual void setColor(Gdiplus::Color color) = 0;

	/*In Circleplot inherite this function*/
	virtual void setValue(Gdiplus::REAL startAngle, Gdiplus::REAL sweepAngle);


	//virtual void AddPlot(std::unique_ptr<CPlot>) = 0;

	/*Return containers ref*/
	//virtual vector<unique_ptr<CPlot>>& getContainer() = 0;
	//
	//virtual unique_ptr<CPlot>& getPlot(size_t index) = 0;
	//virtual size_t AddPlot(unique_ptr<CPlot>&& plot) = 0;
	//

};

