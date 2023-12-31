
// ProjMFCDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CProjMFCDlg dialog
class CProjMFCDlg : public CDialogEx
{
// Construction
public:
	CProjMFCDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_PROJMFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon,b_exit,b_about,b_home;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton m_about;
	CButton m_home;
	CButton m_exit;
	afx_msg void OnBnClickedAbout();
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedDashbord();
	CStatic m_image;
};
