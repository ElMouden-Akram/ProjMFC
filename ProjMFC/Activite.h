#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// Activite dialog

class Activite : public CDialogEx
{
	DECLARE_DYNAMIC(Activite)

public:
	Activite(CWnd* pParent = NULL);   // standard constructor
	virtual ~Activite();

// Dialog Data
	enum { IDD = IDD_ACTIVITE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list_activite;

	void Activite::ExtractDataFromDB(CString sequel);
	void Activite::ComboClicked();
	CComboBox combo1;
	CComboBox combo2;
	CComboBox combo3;
	CComboBox combo4;
	afx_msg void OnCbnSelchangeACombo();
};
