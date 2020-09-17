#pragma once
#include <afxwin.h>
#include <gdiplus.h>
#include <vector>
#include <memory>

#include "CBackGround.h"
#include "CPlotContainer.h"
#include "CCirclePlot.h"
#include "CLinearPlot.h"
#include "Define.h"
#pragma comment (lib,"Gdiplus.lib")


using namespace std;
/*Working on Visual studio 2019 16.4.4*/
class CGraphCtrl :
	public CWnd
{
public:
	/*If you use this constructor, You have to call CWnd::Create*/
	CGraphCtrl();

	/*This function call CWnd::Create*/
	//CGraphCtrl(CWnd* pParent, UINT nID);

	~CGraphCtrl();


	/*
	Add new plot
	it : plot ref
	*/
	bool addPlot();

	/*Set GraphType
	Default - Circle*/
	void setGraphType(GraphType type);

	unique_ptr<CPlot>& getPlot(size_t index);

	auto& getBackground() { return backGround; }

	auto getAxisInfo() { return axisInfo; }
	void setAxisInfo(CAxisInfo info);
	void setResolution(CResolution<Gdiplus::REAL> resolution);

	std::shared_ptr<CAxisInfo> axisInfo;

	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();

private:
	ULONG_PTR gdiplusToken;
	Gdiplus::Status gdiplusStatus = Gdiplus::Status::Ok;
	Gdiplus::Status InitializeGdiplus();

	GraphType graphType = GraphType::Default;

	void InitializeDefault();

	unique_ptr<CBackGround> backGround;
	CPlotContainer plotContainer;

	CRect plotArea;
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};
