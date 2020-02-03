#pragma once
#include "CBackGround.h"
#include <memory>
#include <gdiplus.h>

using namespace std;
class CLinearBack :
	public CBackGround
{
public:
	CLinearBack(CRect rc, CWnd* pParent, UINT nID);

	CLinearBack(CBackGround&&);
	~CLinearBack();

private:
	unique_ptr<Gdiplus::Bitmap> bitmap;
	unique_ptr<Gdiplus::Graphics> graphics;
public:
	virtual Gdiplus::Bitmap* getBitmap();
};

