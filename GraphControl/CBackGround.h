#pragma once
#include <afxwin.h>
#include <gdiplus.h>
using namespace	 std;
class CBackGround :
	public CWnd
{
public:
public:
	virtual Gdiplus::Bitmap* getBitmap() = 0;
};

