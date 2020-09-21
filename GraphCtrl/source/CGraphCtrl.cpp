#include "CGraphCtrl.h"

BEGIN_MESSAGE_MAP(CGraphCtrl, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



CGraphCtrl::CGraphCtrl()
{
	InitializeDefault();
}



CGraphCtrl::~CGraphCtrl()
{
	plotContainer.getContainer().clear();
	Gdiplus::GdiplusShutdown(gdiplusToken);
}

bool CGraphCtrl::addPlot()
{
	CRect rc;

	GetClientRect(rc);
	int nID = GetDlgCtrlID();

	size_t size = plotContainer.getContainer().size();

	if (nID > 0)
	{
		try
		{
			if (graphType == GraphType::Circle)
			{
				plotContainer.AddPlot(unique_ptr<CPlot>(new CCirclePlot(rc)));
			}
			else if(graphType == GraphType::Linear)
			{
				plotContainer.AddPlot(unique_ptr<CPlot>(new CLinearPlot(plotArea,axisInfo)));
			}
		}
		catch (...) { return false; }
	}

	return true;
}

void CGraphCtrl::setGraphType(GraphType type)
{
	graphType = type;
}

unique_ptr<CPlot>& CGraphCtrl::getPlot(size_t index)
{
	return plotContainer.getPlot(index);
}


void CGraphCtrl::setAxisInfo(CAxisInfo info)
{
	axisInfo.reset(new CAxisInfo(info));
}

void CGraphCtrl::setResolution(CResolution<Gdiplus::REAL> resolution)
{
	axisInfo->Resolution = resolution;
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

	if (graphType == GraphType::Linear)
	{
		backGround->updateAxis();
		auto bg = backGround->getBitmap();

		graphic_buffer.DrawImage(bg, 0, 0);
	}

	for (auto &plot : plotContainer.getContainer())
	{
		auto bitmap = plot->getBitmap();
		if (bitmap != nullptr)
		{
			if (graphType == GraphType::Circle)
			{
				graphic_buffer.DrawImage(bitmap, 0,0);
			}
			else if (graphType == GraphType::Linear)
			{
				graphic_buffer.DrawImage(bitmap, axisInfo->axisWidth.y, plotArea.top);
			}
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


BOOL CGraphCtrl::PreCreateWindow(CREATESTRUCT& cs)
{
	CRect rc = CRect(0, 0,  cs.cx, cs.cy);
	plotArea = CRect(30, 0, cs.cx, cs.cy-20);
	axisInfo.reset(new CAxisInfo(plotArea));
	
	backGround.reset(new CBackGround(rc, axisInfo));
	return CWnd::PreCreateWindow(cs);
}
