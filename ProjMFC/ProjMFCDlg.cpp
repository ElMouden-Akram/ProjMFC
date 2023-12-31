
// ProjMFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProjMFC.h"
#include "ProjMFCDlg.h"
#include "afxdialogex.h"
#include "Activite.h"
#include <afxdao.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CProjMFCDlg dialog




CProjMFCDlg::CProjMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProjMFCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON11);
	b_exit = AfxGetApp()->LoadIcon(IDI_ICON5);
	b_about = AfxGetApp()->LoadIcon(IDI_ICON10);
	b_home = AfxGetApp()->LoadIcon(IDI_ICON4);
	
	}

void CProjMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_About, m_about);
	DDX_Control(pDX, IDC_Home, m_home);
	DDX_Control(pDX, IDC_Exit, m_exit);
	DDX_Control(pDX, IDC_POPO, m_image);
}

BEGIN_MESSAGE_MAP(CProjMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_About, &CProjMFCDlg::OnBnClickedAbout)
	ON_BN_CLICKED(IDC_Exit, &CProjMFCDlg::OnBnClickedExit)
	ON_BN_CLICKED(IDC_Dashbord, &CProjMFCDlg::OnBnClickedDashbord)
END_MESSAGE_MAP()


// CProjMFCDlg message handlers

BOOL CProjMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.
	m_exit.SetIcon(b_exit);
	m_home.SetIcon(b_home);
	m_about.SetIcon(b_about);
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	//🚩Creation de Base de donnée s'il n'existe pas :
	CFileFind finder; //pour chercher si le fichier DB existe .
	CString lpszFile =L"GestionActivite.mdb";

	BOOL bWorking = finder.FindFile(lpszFile);

	if(!bWorking){
		//If the file isn't there, then create one :)
		CDaoDatabase db;
		CDaoRecordset recset;

		db.Create(lpszFile);
		CString creation_table_Continent=L"CREATE TABLE CLIENTS(no_Client AUTOINCREMENT PRIMARY KEY, Nom VARCHAR(30), Prenom VARCHAR(30), Localite VARCHAR(30));";
		
		db.Execute(creation_table_Continent);
		db.Close();  //and close the database!
	}else{

	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CProjMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CProjMFCDlg::OnPaint()
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
HCURSOR CProjMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CProjMFCDlg::OnBnClickedAbout()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
	// TODO: Add your control notification handler code here
}


void CProjMFCDlg::OnBnClickedExit()
{ 
	OnOK();
	// TODO: Add your control notification handler code here
}


void CProjMFCDlg::OnBnClickedDashbord()
{
	// TODO: Add your control notification handler code here
	CRect rc;
	GetDlgItem(IDC_POPO)->GetWindowRect(rc);
	ScreenToClient(&rc);
	Activite* ActiviteDlg = new Activite(this);
	ActiviteDlg->MoveWindow(rc);

}


