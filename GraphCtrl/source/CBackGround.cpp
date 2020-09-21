//#include "pch.h"
#include "CBackGround.h"
#include <sstream>
CBackGround::CBackGround(CRect rc, std::shared_ptr<CAxisInfo> axis)
{
	rectBG = rc;

	axis->axisWidth = { 20,50 };
	axisInfo = axis;
	gridInfo = { 50,5 };

	//Gdiplus::Font font(_T("맑은 고딕"), 9, Gdiplus::FontStyle::FontStyleRegular, Gdiplus::Unit::UnitPixel));
	//stringFormat.reset(new Gdiplus::StringFormat());
}

CBackGround::~CBackGround()
{
	if (bitmap)	bitmap.reset();
	if (graphics) graphics.reset();

}

CBackGround::CBackGround(CBackGround&&) noexcept
{
}

bool CBackGround::updateAxis()
{
	if(axisInfo->isUpdated())
	{
		CRect rectPlot = CRect(rectBG.left + axisInfo->axisWidth.y, rectBG.top, rectBG.right, rectBG.bottom - axisInfo->axisWidth.x);
		bitmap.reset(new Gdiplus::Bitmap(rectBG.Width(), rectBG.Height(), PixelFormat32bppARGB));
		graphics.reset(Gdiplus::Graphics::FromImage(bitmap.get()));
		graphics->SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
		graphics->SetTextRenderingHint(Gdiplus::TextRenderingHint::TextRenderingHintAntiAlias);


		/*Pixel Value*/
		CResolution<double> gridResolution{
			gridInfo.x * rectPlot.Width() / axisInfo->Resolution.x ,
			gridInfo.y * rectPlot.Height() / axisInfo->Resolution.y
		};

		DrawVerticalGrid(gridResolution.y, rectPlot);
		DrawHorizontalGrid(gridResolution.x, rectPlot);
	}

	

	return false;
}

void CBackGround::DrawHorizontalGrid(double gridResolution, CRect& rectPlot)
{
	/*Draw Horizontal grid*/
	/*Plot will move.*/
	int gridCount = 1;
	double offset = fmod(axisInfo->xAxis.begin, gridResolution);
	double prev = 0;

	Gdiplus::Pen axisPen(Gdiplus::Color::Black);
	Gdiplus::SolidBrush stringBrush(Gdiplus::Color::Black);
	Gdiplus::Font font(_T("맑은 고딕"), 9, Gdiplus::FontStyle::FontStyleRegular, Gdiplus::Unit::UnitPixel);
	Gdiplus::StringFormat stringFormat;
	stringFormat.SetAlignment(Gdiplus::StringAlignment::StringAlignmentFar);
	for (double i = gridResolution - offset; i < rectPlot.right; i += gridResolution)
	{
		if (i > 0)
		{
			if( (i - prev ) > gridInfo.x)
			{
				prev = i;
				graphics->DrawLine(&axisPen,
					Gdiplus::PointF(static_cast<Gdiplus::REAL>(rectPlot.left + i), static_cast<Gdiplus::REAL>(rectPlot.bottom + 5)),
					Gdiplus::PointF(static_cast<Gdiplus::REAL>(rectPlot.left + i), static_cast<Gdiplus::REAL>(rectPlot.bottom)));

				std::wostringstream out;
				out.precision(1);

				auto value = axisInfo->xAxis.minimum - (gridInfo.x * gridCount);
				out << std::fixed << value;

				std::wstring wstr(out.str());
				graphics->DrawString(wstr.c_str(), wstr.length(), &font, Gdiplus::PointF(rectPlot.left + i, rectPlot.bottom + 5), &stringFormat, &stringBrush);
			}
			gridCount++;
		}
	}




	graphics->DrawLine(&axisPen,
		Gdiplus::PointF(rectPlot.right, rectPlot.bottom),
		Gdiplus::PointF(rectPlot.left, rectPlot.bottom));

}

void CBackGround::DrawVerticalGrid(double gridResolution, CRect& rectPlot)
{
	/*Draw Vertical grid*/
	int gridCount = 1;
	double offset = fmod(axisInfo->yAxis.begin, gridResolution);
	Gdiplus::Pen axisPen(Gdiplus::Color::Black);
	Gdiplus::Font font(_T("맑은 고딕"), 9, Gdiplus::FontStyle::FontStyleRegular, Gdiplus::Unit::UnitPixel);
	Gdiplus::SolidBrush stringBrush(Gdiplus::Color::Black);
	Gdiplus::StringFormat stringFormat;
	stringFormat.SetAlignment(Gdiplus::StringAlignment::StringAlignmentFar);
	for (double i = gridResolution + offset; i < rectPlot.bottom; i += gridResolution)
	{
		if (i > 0)
		{
			/*maximum value first*/
			graphics->DrawLine(&axisPen,
				Gdiplus::PointF(static_cast<Gdiplus::REAL>(rectPlot.left - 5), static_cast<Gdiplus::REAL>(rectPlot.top + i)),
				Gdiplus::PointF(static_cast<Gdiplus::REAL>(rectPlot.left), static_cast<Gdiplus::REAL>(rectPlot.top + i)));

			std::wostringstream out;
			out.precision(1);

			auto value = axisInfo->yAxis.maximum - (gridInfo.y * gridCount++);
			out << std::fixed << value;

			std::wstring wstr(out.str());
			graphics->DrawString(wstr.c_str(), wstr.length(), &font, Gdiplus::PointF(rectPlot.left - 5, rectPlot.top + i), &stringFormat, &stringBrush);
		}
	}


	graphics->DrawLine(&axisPen,
		Gdiplus::PointF(static_cast<Gdiplus::REAL>(rectPlot.left), static_cast<Gdiplus::REAL>(rectPlot.top)),
		Gdiplus::PointF(static_cast<Gdiplus::REAL>(rectPlot.left), static_cast<Gdiplus::REAL>(rectPlot.bottom)));
}

Gdiplus::Bitmap* CBackGround::getBitmap()
{
	return bitmap.get();
}
