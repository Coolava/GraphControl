
// Sample ApplicationDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Sample Application.h"
#include "Sample ApplicationDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSampleApplicationDlg dialog



CSampleApplicationDlg::CSampleApplicationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SAMPLEAPPLICATION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSampleApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_CIRCLE, sliderCircle);
	DDX_Control(pDX, IDC_SLIDER_LINEAR, sliderLinear);
	
}

BEGIN_MESSAGE_MAP(CSampleApplicationDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDOK, &CSampleApplicationDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDOK2, &CSampleApplicationDlg::OnBnClickedOk2)
END_MESSAGE_MAP()


// CSampleApplicationDlg message handlers

BOOL CSampleApplicationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	m_CtrlCircleGraph.Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 102, 102), this, 10001);

	bool ret = m_CtrlCircleGraph.addPlot();
	if (ret == true)
	{
		m_CtrlCircleGraph.getPlot(0)->setColor(Gdiplus::Color::OrangeRed);
		//((CCirclePlot*)m_CtrlCircleGraph.getPlot(0).get())->setColor(Gdiplus::Color::OrangeRed);

	}

	ret = m_CtrlCircleGraph.addPlot();

	sliderCircle.SetRange(0, 3600);
	

	m_CtrlLinearGraph.Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(104, 0, 500+104, 102), this, 10002);
	m_CtrlLinearGraph.setGraphType(GraphType::Linear);
	
	ret = m_CtrlLinearGraph.addPlot();
	if (ret == true)
	{
		m_CtrlLinearGraph.getPlot(0)->setColor(Gdiplus::Color::DodgerBlue);

		auto axis = m_CtrlLinearGraph.getAxisInfo();
		m_CtrlLinearGraph.setResolution({ axis->Resolution.x, 20});
		//((CLinearPlot*)plot1->get())->setColor(Gdiplus::Color::OrangeRed);
		//((CLinearPlot*)plot1->get())->setColor(Gdiplus::Color::OrangeRed);

	}

	ret = m_CtrlLinearGraph.addPlot();

	sliderCircle.SetRange(0, 3600);

	sliderLinear.SetRange(0, 3600);
	
	//if (ret == true)
	//{
	//	((CCirclePlot*)plot2->get())->setValue(45.0f, 360.0f-45.0f);
	//
	//}
	//((CCirclePlot*)(*plot1))->setValue(0.0f, 45.0f);


	SetBackgroundColor(RGB(255, 255, 255));
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSampleApplicationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSampleApplicationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSampleApplicationDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	if (IDC_SLIDER_CIRCLE == pScrollBar->GetDlgCtrlID())
	{
		int iPos = sliderCircle.GetPos();

		m_CtrlCircleGraph.getPlot(0)->setValue(0.0f, (Gdiplus::REAL)iPos / 10);
		m_CtrlCircleGraph.getPlot(1)->setValue((Gdiplus::REAL)iPos / 10, 360.0f - (Gdiplus::REAL)iPos / 10);


		//((CCirclePlot*)m_CtrlCircleGraph.getPlot(0).get())->setValue(0.0f, (Gdiplus::REAL)iPos / 10);
		//((CCirclePlot*)m_CtrlCircleGraph.getPlot(1).get())->setValue((Gdiplus::REAL)iPos / 10, 360.0f - (Gdiplus::REAL)iPos / 10);
		//((CCirclePlot*)plot1->get())->setValue(0.0f, (Gdiplus::REAL)iPos / 10);
		//((CCirclePlot*)plot2->get())->setValue((Gdiplus::REAL)iPos / 10, 360.0f - (Gdiplus::REAL)iPos / 10);
		m_CtrlCircleGraph.Invalidate(false);

	}
	else if (IDC_SLIDER_LINEAR == pScrollBar->GetDlgCtrlID())
	{

		int iPos = sliderLinear.GetPos();

		Gdiplus::REAL val = 10 * sin(2 * 3.14 / 3600 * (iPos));
		m_CtrlLinearGraph.getPlot(0)->addPoint(val);

		m_CtrlLinearGraph.Invalidate(false);


	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CSampleApplicationDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void CSampleApplicationDlg::OnBnClickedOk2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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


	Gdiplus::Pen pen(Gdiplus::Color::AliceBlue);

	graphic_buffer.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);

	//graphics->FillPie(&brush, ellipseRect, startAngle, sweepAngle );

	/*Test code*/
	Gdiplus::PointF points[100];

	for (int i = 0; i < 100; i++)
	{
		points[i] = Gdiplus::PointF(i, 10 * sin(2 * 3.14 / 100*i) + 20);
	}
	graphic_buffer.DrawBeziers(&pen, &points[0], 100);


	graphic.DrawImage(&bitmap_buffer, 0, 0);

	Invalidate(false);
}
