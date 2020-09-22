
#include "CBackGround.h"
#include <sstream>
CBackGround::CBackGround(CRect rc, std::shared_ptr<CAxisInfo> axis)
{
	rectBG = rc;

	axis->axisWidth = { 20,50 };
	axisInfo = axis;
	gridInfo = { 50,5 };

	Pen.reset(new Gdiplus::Pen(Gdiplus::Color::Black));
	stringBrush.reset(new Gdiplus::SolidBrush(Gdiplus::Color::Black));
	font.reset(new Gdiplus::Font(_T("Calibri"), 9, Gdiplus::FontStyle::FontStyleRegular, Gdiplus::Unit::UnitPixel));
	stringFormat.reset(new Gdiplus::StringFormat()); 
}

CBackGround::~CBackGround()
{

	if (Pen)	Pen.release();
	if (stringBrush)	stringBrush.release();
	if (font)	font.release();
	if (stringFormat)	stringFormat.release();

}

CBackGround::CBackGround(CBackGround&&) noexcept
{
}

bool CBackGround::updateAxis()
{
	if(axisInfo->isUpdated())
	{
		CRect rectPlot = CRect(rectBG.left + axisInfo->axisWidth.y, rectBG.top, rectBG.right, rectBG.bottom - axisInfo->axisWidth.x);
		clearBitmap(rectBG);


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

void CBackGround::clearBitmap(CRect rc)
{
	bitmap.reset(new Gdiplus::Bitmap(rc.Width(), rc.Height(), PixelFormat32bppARGB));
	graphics.reset(Gdiplus::Graphics::FromImage(bitmap.get()));
	graphics->SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
	graphics->SetTextRenderingHint(Gdiplus::TextRenderingHint::TextRenderingHintAntiAlias);
}

void CBackGround::DrawHorizontalGrid(double gridResolution, CRect& rectPlot)
{

	stringFormat->SetAlignment(Gdiplus::StringAlignment::StringAlignmentCenter);
	stringFormat->SetLineAlignment(Gdiplus::StringAlignment::StringAlignmentCenter);

	/*Draw Horizontal grid*/
	/*Plot will move.*/
	int gridCount = 1;
	double offset = fmod(axisInfo->xAxis.begin, gridResolution);
	double prev = 0;
	double half = gridResolution / 2;

	for (double i = gridResolution - offset; i < rectPlot.right; i += gridResolution)
	{
		if (i > 0)
		{
			if( (i - prev ) > gridInfo.x)
			{
				prev = i;
				graphics->DrawLine(Pen.get(),
					Gdiplus::PointF(static_cast<Gdiplus::REAL>(rectPlot.left + i), static_cast<Gdiplus::REAL>(rectPlot.bottom + 5)),
					Gdiplus::PointF(static_cast<Gdiplus::REAL>(rectPlot.left + i), static_cast<Gdiplus::REAL>(rectPlot.bottom)));

				auto value = axisInfo->xAxis.minimum - (gridInfo.x * gridCount);

				std::wstring wstr(to_Fixedwstring(value));

				graphics->DrawString(wstr.c_str(), static_cast<INT>(wstr.length()), font.get(),
					Gdiplus::RectF(static_cast<Gdiplus::REAL>(rectPlot.left + i- gridResolution), static_cast<Gdiplus::REAL>(rectPlot.bottom + 5), static_cast<Gdiplus::REAL>(gridResolution*2), static_cast<Gdiplus::REAL>(axisInfo->axisWidth.x - 5)), stringFormat.get(), stringBrush.get());
			}
			gridCount++;
		}
	}




	graphics->DrawLine(Pen.get(),
		Gdiplus::PointF(static_cast<Gdiplus::REAL>(rectPlot.right), static_cast<Gdiplus::REAL>(rectPlot.bottom)),
		Gdiplus::PointF(static_cast<Gdiplus::REAL>(rectPlot.left),  static_cast<Gdiplus::REAL>(rectPlot.bottom)));

}

void CBackGround::DrawVerticalGrid(double gridResolution, CRect& rectPlot)
{
	stringFormat->SetAlignment(Gdiplus::StringAlignment::StringAlignmentFar);
	stringFormat->SetLineAlignment(Gdiplus::StringAlignment::StringAlignmentCenter);

	/*Draw Vertical grid*/
	int gridCount = 1;
	double offset = fmod(axisInfo->yAxis.begin, gridResolution);
	double half = gridResolution / 2;
	for (double i = gridResolution + offset; i < rectPlot.bottom; i += gridResolution)
	{
		if (i > 0)
		{
			/*maximum value first*/
			graphics->DrawLine(Pen.get(),
				Gdiplus::PointF(static_cast<Gdiplus::REAL>(rectPlot.left - 5), static_cast<Gdiplus::REAL>(rectPlot.top + i)),
				Gdiplus::PointF(static_cast<Gdiplus::REAL>(rectPlot.left), static_cast<Gdiplus::REAL>(rectPlot.top + i)));


			auto value = axisInfo->yAxis.maximum - (gridInfo.y * gridCount++);

			std::wstring wstr(to_Fixedwstring(value));
			
			graphics->DrawString(wstr.c_str(), static_cast<INT>(wstr.length()), font.get(),
				Gdiplus::RectF(0, static_cast<Gdiplus::REAL>(rectPlot.top + i-half), static_cast<Gdiplus::REAL>(axisInfo->axisWidth.y-5), static_cast<Gdiplus::REAL>(gridResolution)),
				stringFormat.get(), stringBrush.get());
		}
	}


	graphics->DrawLine(Pen.get(),
		Gdiplus::PointF(static_cast<Gdiplus::REAL>(rectPlot.left), static_cast<Gdiplus::REAL>(rectPlot.top)),
		Gdiplus::PointF(static_cast<Gdiplus::REAL>(rectPlot.left), static_cast<Gdiplus::REAL>(rectPlot.bottom)));
}

Gdiplus::Bitmap* CBackGround::getBitmap()
{
	return bitmap.get();
}

std::wstring CBackGround::to_Fixedwstring(double value, int fixed)
{
	std::wostringstream out;
	out.precision(fixed);

	out << std::fixed << value;
	return out.str();
}
