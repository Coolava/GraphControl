#pragma once
#include <afxwin.h>
#include <gdiplus.h>
#include <vector>
#include <memory>
#include "CPlot.h"
#include "CCirclePlot.h"
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
	bool addPlot(vector<unique_ptr<CPlot>>::iterator& it);

	unique_ptr<CPlot>& getPlot(size_t index);

	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();

private:
	ULONG_PTR gdiplusToken;
	Gdiplus::Status gdiplusStatus = Gdiplus::Status::Ok;
	Gdiplus::Status InitializeGdiplus();

	GraphType graphType = GraphType::Default;
	void InitializeDefault();

	vector<unique_ptr<CPlot>> plotContainer;
};
