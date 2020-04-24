#include "CGraphCtrl.h"
BEGIN_MESSAGE_MAP(CGraphCtrl, CWnd)
	ON_WM_PAINT()
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
	//plotContainer.
	plotContainer.getContainer().clear();
	//plotContainer.clear();
	Gdiplus::GdiplusShutdown(gdiplusToken);
}

bool CGraphCtrl::addPlot()
{
	CRect rc;
	GetClientRect(rc);
	int nID = GetDlgCtrlID();

	size_t size = plotContainer.getContainer().size();
	//it = plotContainer.getContainer().end();

	if (nID > 0)
	{
		try
		{
			if (graphType == GraphType::Circle)
			{
				plotContainer.AddPlot(unique_ptr<CPlot>(new CCirclePlot(rc)));
				//plotContainer.AddPlot(rc);
				//plotContainer.push_back(unique_ptr<CPlot>(new CCirclePlot(rc)));
				//it = (plotContainer.getContainer().end() - 1);
				//return true;
			}
			else if(graphType == GraphType::Linear)
			{
				plotContainer.AddPlot(unique_ptr<CPlot>(new CLinearPlot(rc)));
				//plotContainer.AddPlot(rc);
				//plotContainer.push_back(unique_ptr<CPlot>(new CCirclePlot(rc)));
				//it = (plotContainer.getContainer().end() - 1);
				//return true;
			}
		}
		catch (...) { return false; }
	}

	return true;
}

unique_ptr<CPlot>& CGraphCtrl::getPlot(size_t index)
{
	return plotContainer.getPlot(index);
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
	graphic_buffer.Clear(Gdiplus::Color::White);

	for (auto &plot : plotContainer.getContainer())
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
