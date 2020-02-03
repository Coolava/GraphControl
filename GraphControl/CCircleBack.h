#pragma once
#include "CBackGround.h"
#include <memory>
#include <gdiplus.h>

using namespace std;
class CCircleBack :
	public CBackGround
{
public:
	CCircleBack(CRect rc, CWnd* pParent, UINT nID);

	CCircleBack(CBackGround&&);
	~CCircleBack();

private:
	unique_ptr<Gdiplus::Bitmap> bitmap;
	unique_ptr<Gdiplus::Graphics> graphics;
public:
	virtual Gdiplus::Bitmap* getBitmap();
};

