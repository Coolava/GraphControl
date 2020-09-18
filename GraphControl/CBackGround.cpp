//#include "pch.h"
#include "CBackGround.h"

CBackGround::CBackGround(CRect rc, std::shared_ptr<CAxisInfo> axis)
{
	rectBG = rc;

	axisInfo = axis;
	gridInfo = { 50,5 };
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

CBackGround::CBackGround(CBackGround&&) noexcept
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

		/*Pixel Value*/
		CResolution<double> gridResolution{
			gridInfo.x * rectPlot.Width() / axisInfo->Resolution.x ,
			gridInfo.y* rectPlot.Height() / axisInfo->Resolution.y
		};

		/*Draw Horizontal grid*/
		double offset_y = fmod(axisInfo->yAxis.begin, gridResolution.y);
		for (double i = gridResolution.y + offset_y; i < rectPlot.bottom; i += gridResolution.y)
		{
			if (i > 0)
			{
				graphics->DrawLine(&pen,
					Gdiplus::PointF(static_cast<Gdiplus::REAL>(rectPlot.left-5), static_cast<Gdiplus::REAL>(rectPlot.top+i)),
					Gdiplus::PointF(static_cast<Gdiplus::REAL>(rectPlot.left), static_cast<Gdiplus::REAL>(rectPlot.top+i)));
			}
		}


		graphics->DrawLine(&pen, 
			Gdiplus::PointF(static_cast<Gdiplus::REAL>(rectPlot.left), static_cast<Gdiplus::REAL>(rectPlot.top)),
			Gdiplus::PointF(static_cast<Gdiplus::REAL>(rectPlot.left), static_cast<Gdiplus::REAL>(rectPlot.bottom)));



		/*Draw Horizontal grid*/
		/*Plot will move.*/
		double offset_x = fmod(axisInfo->xAxis.begin, gridResolution.x);
		for (double i = gridResolution.x- offset_x; i < rectPlot.right; i += gridResolution.x)
		{
			if(i > 0)
			{
				graphics->DrawLine(&pen,
					Gdiplus::PointF(static_cast<Gdiplus::REAL>(rectPlot.left + i), static_cast<Gdiplus::REAL>(rectPlot.bottom + 5)),
					Gdiplus::PointF(static_cast<Gdiplus::REAL>(rectPlot.left + i), static_cast<Gdiplus::REAL>(rectPlot.bottom)));
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
