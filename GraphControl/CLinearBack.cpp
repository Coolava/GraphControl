#include "CLinearBack.h"


CLinearBack::CLinearBack(CRect rc, CWnd* pParent, UINT nID)
{
	CWnd::Create(NULL, NULL, WS_CHILD | WS_VISIBLE, rc, pParent, nID);

	bitmap = unique_ptr<Gdiplus::Bitmap>(new Gdiplus::Bitmap(rc.Width(), rc.Height(), PixelFormat32bppARGB));
	graphics = unique_ptr<Gdiplus::Graphics>(Gdiplus::Graphics::FromImage(bitmap.get()));
	graphics->Clear(Gdiplus::Color::White);
}

CLinearBack::CLinearBack(CBackGround&&)
{
}

CLinearBack::~CLinearBack()
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

Gdiplus::Bitmap* CLinearBack::getBitmap()
{
	return bitmap.get();
}
