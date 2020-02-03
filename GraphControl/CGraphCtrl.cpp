#include "pch.h"
#include "CGraphCtrl.h"
BEGIN_MESSAGE_MAP(CGraphCtrl, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



CGraphCtrl::CGraphCtrl()
{
	InitializeDefault();
}

CGraphCtrl::CGraphCtrl(CWnd* pParent, UINT nID)
{
	CWnd::Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 100, 100), pParent, nID);

	InitializeDefault();

}

CGraphCtrl::~CGraphCtrl()
{
	plotContainer.clear();
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
			plotContainer.push_back(unique_ptr<CPlot>(new CCirclePlot(rc, this, nID + size + 10000)));
			it = (plotContainer.end() - 1);

			return true;
		}
	}

	return false;
}

unique_ptr<CPlot>& CGraphCtrl::getPlot(size_t index)
{
	return plotContainer.at(index);
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
	graphic_buffer.Clear(Gdiplus::Color::White);

	for (auto &plot : plotContainer)
	{
		graphic_buffer.DrawImage(plot->getBitmap(),0,0);
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
