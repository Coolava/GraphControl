
// Sample ApplicationDlg.h : header file
//

#pragma once
#include "CGraphCtrl.h"

// CSampleApplicationDlg dialog
class CSampleApplicationDlg : public CDialogEx
{
// Construction
public:
	CSampleApplicationDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SAMPLEAPPLICATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();

	CGraphCtrl m_CtrlCircle;
	vector<unique_ptr<CPlot>>::iterator plot1;
	vector<unique_ptr<CPlot>>::iterator plot2;

	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl sliderCircle;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
