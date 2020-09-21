#pragma once
#include <afxwin.h>
#include <gdiplus.h>
#include <memory>
#include <string>
#include "Define.h"

class CBackGround
{
public:
	CBackGround(CRect rc, std::shared_ptr<CAxisInfo> axis);
	virtual ~CBackGround();
	CBackGround(CBackGround&&) noexcept;


	bool updateAxis();
	void DrawHorizontalGrid(double gridResolution, CRect& rectPlot);
	void DrawVerticalGrid(double gridResolution, CRect& rectPlot);
	virtual Gdiplus::Bitmap* getBitmap();
private:
	CResolution<double> gridInfo;
	CRect rectBG;
	std::shared_ptr<CAxisInfo> axisInfo;


	std::unique_ptr<Gdiplus::Bitmap> bitmap;
	std::unique_ptr<Gdiplus::Graphics> graphics;

	//std::unique_ptr<Gdiplus::Font> font;
	//std::unique_ptr<Gdiplus::StringFormat> stringFormat;
	//Gdiplus::StringFormat stringFormat;
};

