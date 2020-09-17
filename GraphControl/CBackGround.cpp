//#include "pch.h"
#include "CBackGround.h"

CBackGround::CBackGround(CRect rc, std::shared_ptr<CAxisInfo> axis)
{
	rectBG = rc;

	axisInfo = axis;
	gridInfo = { 10,10 };
}

CBackGround::~CBackGround()
{
	if (bitmap)
	{
		bitmap.reset();
	}
	if (graphics)
	{
		graphics.reset();
	}
}

CBackGround::CBackGround(CBackGround&&)
{
}

bool CBackGround::updateAxis()
{
	if(axisInfo->isUpdated())
	{
		CRect rectPlot = CRect(rectBG.left + 20, rectBG.top, rectBG.right, rectBG.bottom - 20);
		bitmap.reset(new Gdiplus::Bitmap(rectBG.Width(), rectBG.Height(), PixelFormat32bppARGB));
		graphics.reset(Gdiplus::Graphics::FromImage(bitmap.get()));
		graphics->SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);

		Gdiplus::Pen pen(Gdiplus::Color::Black);
		graphics->DrawLine(&pen, 
			Gdiplus::PointF(rectPlot.left, rectPlot.top ),
			Gdiplus::PointF(rectPlot.left, rectPlot.bottom));


		auto pixel = gridInfo.x * rectPlot.Height() / axisInfo->Resolution.y;
		for (double i = pixel-axisInfo->xAxis.begin; i < rectBG.right; i += pixel)
		{
			if(i > 0)
			{
				graphics->DrawLine(&pen,
					Gdiplus::PointF(rectPlot.left + i, rectPlot.bottom + 5),
					Gdiplus::PointF(rectPlot.left + i, rectPlot.bottom));
			}
		}

		graphics->DrawLine(&pen, 
			Gdiplus::PointF(rectPlot.right, rectPlot.bottom),
			Gdiplus::PointF(rectPlot.left , rectPlot.bottom ));
		

	}

	

	return false;
}

Gdiplus::Bitmap* CBackGround::getBitmap()
{
	return bitmap.get();
}
