#include "CGraphCtrl.h"
BEGIN_MESSAGE_MAP(CGraphCtrl, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
END_MESSAGE_MAP()



CGraphCtrl::CGraphCtrl()
{
	InitializeDefault();
}

//CGraphCtrl::CGraphCtrl(CWnd* pParent, UINT nID)
//{
//	CWnd::Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 100, 100), pParent, nID);
//
//	InitializeDefault();
//
//}

CGraphCtrl::~CGraphCtrl()
{
	plotContainer.clear();
	backGround.reset();
	Gdiplus::GdiplusShutdown(gdiplusToken);
}

bool CGraphCtrl::addPlot(vector<unique_ptr<CPlot>>::iterator& it)
{
	CRect rc;
	GetClientRect(rc);
	int nID = GetDlgCtrlID();
	size_t size = plotContainer.size();
	it = plotContainer.end();
	if (graphType == GraphType::Circle)
	{
		if (nID > 0)
		{
			try
			{
				plotContainer.push_back(unique_ptr<CPlot>(new CCirclePlot(rc, this, nID + size + (UINT)IDoffset::Plot)));
				it = (plotContainer.end() - 1);
				return true;
			}
			catch(...){/* return false */}
		}
	}

	return false;
}

CPlot* CGraphCtrl::getPlot(size_t index)
//unique_ptr<CPlot>& CGraphCtrl::getPlot(size_t index)
{
	return plotContainer.at(index).get();
}

void CGraphCtrl::OnPaint()
{
	CPaintDC dc(this); 

	Gdiplus::Graphics graphic(dc);
	CRect rc;
	GetClientRect(rc);

	/*buffer*/
	Gdiplus::Bitmap bitmap_buffer(rc.Width(), rc.Height(), PixelFormat32bppARGB);
	Gdiplus::Graphics graphic_buffer(&bitmap_buffer);

	/*Draw background*/
	/*
	If you draw nothing, you will see aliased graph. 
	Sol 1 : Fill background
	Sol 2 : Copy parent background
	*/

	graphic_buffer.DrawImage(backGround->getBitmap(),0,0);
	//graphic_buffer.Clear(Gdiplus::Color::White);

	for (auto &plot : plotContainer)
	{
		auto bitmap = plot->getBitmap();
		if (bitmap != nullptr)
		{
			graphic_buffer.DrawImage(bitmap, 0, 0);
		}
	}

	graphic.DrawImage(&bitmap_buffer, 0, 0);


}

Gdiplus::Status CGraphCtrl::InitializeGdiplus()
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;

	return Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}

void CGraphCtrl::InitializeDefault()
{
	gdiplusStatus = InitializeGdiplus();

}


int CGraphCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}


BOOL CGraphCtrl::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{

	if (nID > 0)
	{
		backGround = unique_ptr<CBackGround>(new CCircleBack(rect, this, nID + (UINT)IDoffset::Background));
	}


	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}
