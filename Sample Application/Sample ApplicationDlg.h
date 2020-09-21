
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

	CGraphCtrl m_CtrlCircleGraph;
	CGraphCtrl m_CtrlLinearGraph;

	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl sliderCircle;
	CSliderCtrl sliderLinear;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedOk2();
};
