#pragma once
#include <afxwin.h>
#include <gdiplus.h>

class CPlot :
	public CWnd
{

public:

	virtual Gdiplus::Bitmap* getBitmap() = 0;

};

