#include "pch.h"
#include "CCirclePlot.h"

CCirclePlot::CCirclePlot()
{
}

CCirclePlot::CCirclePlot(CRect rc, CWnd* pParent, UINT nID)
{
	CWnd::Create(NULL, NULL, WS_CHILD | WS_VISIBLE, rc, pParent, nID);

	CPaintDC dc(this);

	tempBitmap = unique_ptr<Gdiplus::Bitmap>(new Gdiplus::Bitmap(rc.Width(), rc.Height(), PixelFormat32bppARGB));
	tempGraphics = unique_ptr<Gdiplus::Graphics>(Gdiplus::Graphics::FromImage(tempBitmap.get()));

	bitmap = unique_ptr<Gdiplus::Bitmap>(new Gdiplus::Bitmap(rc.Width(), rc.Height(), PixelFormat32bppARGB));
	graphics = unique_ptr<Gdiplus::Graphics>(Gdiplus::Graphics::FromImage(bitmap.get()));
	//graphics = unique_ptr<Gdiplus::Graphics>(Gdiplus::Graphics::FromHDC(dc));
}

CCirclePlot::~CCirclePlot()
{
	tempBitmap.release();
	tempGraphics.release();
	bitmap.release();
	graphics.release();
}

CCirclePlot::CCirclePlot(CCirclePlot&&)
{
}


void CCirclePlot::setColor(Gdiplus::Color _color)
{
	color = _color;
}

void CCirclePlot::setValue(Gdiplus::REAL _startAngle, Gdiplus::REAL _sweepAngle)
{
	//tempGraphics->SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);

	graphics->Clear(Gdiplus::Color(0, 255, 0));
	tempGraphics->Clear(Gdiplus::Color(0,255,0));

	Gdiplus::SolidBrush brush(color);

	CRect rc;
	GetClientRect(rc);
	Gdiplus::Rect ellipseRect(rc.left+1,rc.top+1,rc.Width()-2,rc.Height()-2);
	
	startAngle = _startAngle;
	sweepAngle = _sweepAngle;
	tempGraphics->FillPie(&brush, ellipseRect, startAngle, sweepAngle );

	//brush.SetColor(Gdiplus::Color::White);
	//tempGraphics->FillPie(&brush, ellipseRect, sweepAngle, 360.0f + startAngle);
	
	//graphics->DrawImage(tempBitmap.get(), 0, 0);

	////graphics->Clear(Gdiplus::Color::White);
	Gdiplus::ImageAttributes imageAttr;
	//
	imageAttr.SetColorKey(Gdiplus::Color(0,255,0), Gdiplus::Color(0, 255, 0));
	graphics->DrawImage(tempBitmap.get(), Gdiplus::Rect(rc.left, rc.top, rc.Width(), rc.Height())
		, 0, 0, ellipseRect.Width, ellipseRect.Height, Gdiplus::Unit::UnitPixel, &imageAttr);

}

Gdiplus::Bitmap* CCirclePlot::getBitmap()
{
	return bitmap.get();
}
