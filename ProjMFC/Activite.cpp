// Activite.cpp : implementation file
//

#include "stdafx.h"
#include "ProjMFC.h"
#include "Activite.h"
#include "afxdialogex.h"
#include <afxdao.h>

// Activite dialog

IMPLEMENT_DYNAMIC(Activite, CDialogEx)

Activite::Activite(CWnd* pParent /*=NULL*/)
	: CDialogEx(Activite::IDD, pParent)
{
	Create(IDD_DIALOG1, pParent);
}

Activite::~Activite()
{
}

void Activite::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, m_list_activite);
	DDX_Control(pDX, IDC_COMBO1, combo1);
	DDX_Control(pDX, IDC_COMBO2, combo2);
	DDX_Control(pDX, IDC_COMBO3, combo3);
	DDX_Control(pDX, IDC_COMBO4, combo4);
}


BEGIN_MESSAGE_MAP(Activite, CDialogEx)
END_MESSAGE_MAP()


// Activite message handlers
BOOL Activite::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRect rc;
	m_list_activite.GetClientRect(rc);
	m_list_activite.InsertColumn(0,L"Activite",0,rc.Width()/4);
	m_list_activite.InsertColumn(0,L"Village",0,rc.Width()/4);
	m_list_activite.InsertColumn(0,L"Pays",0,rc.Width()/4);
	m_list_activite.InsertColumn(0,L"Continent",0,rc.Width()/4);
	//🔥🔥🔥The 3 line code below is for selecting entire row instead of selecting only the ID(one colonne) :
	m_list_activite.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_list_activite.SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	m_list_activite.SetFocus();

	//init les combos par un texte descriptif :
	combo1.SetWindowTextW(L"Par activite");
	combo2.SetWindowTextW(L"Par village");
	combo3.SetWindowTextW(L"Par pays");
	combo4.SetWindowTextW(L"Par continent");
	
	//int premier = m_list_activite.InsertItem(0 ,L"Asia" ,0 );
	//m_list_activite.SetItemText(premier,2,L"dsa");

	ExtractDataFromDB();

	return TRUE;
}

void Activite::ExtractDataFromDB(){
	CDaoDatabase db; //déclaration de variable base de donnée db : represents a connection to a database.
	CDaoRecordset recset(&db); //the varaible "recset" used to represent a 'set of records' from a database table.
	CString sequel = L"SELECT Activites.NomActivite,Villages.nomVillage,Pays.nomPays,Continents.nomContinent FROM Activites, proposer, Villages, Pays, Continents WHERE Activites.idActivite = proposer.idActivite AND proposer.codeVillage = Villages.codeVillage AND Villages.codePays = Pays.codePays AND Pays.codeContinent = Continents.codeContinent;";

	COleVariant var;//start Variables
	var.ChangeType(VT_BSTR,NULL);

	m_list_activite.DeleteAllItems();//clear list
	db.Open(L"GestionActivite.mdb");
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,sequel,NULL);//to retrieve the records for the recordset

	CString nomActivite,nomVillage,Pays,Continent;
	int i=0;

	while(!recset.IsEOF())
	{
		//this part of the code should fill up the list + the 3 combo list !
		recset.GetFieldValue(L"nomActivite",var);
		nomActivite=(LPCWSTR)var.pbstrVal;
		m_list_activite.InsertItem(i ,nomActivite ,0 );
		if(combo1.FindStringExact(0,nomActivite)==CB_ERR){ 
			combo1.AddString(nomActivite);
		}

		recset.GetFieldValue(L"nomVillage",var);
		nomVillage=(LPCWSTR)var.pbstrVal;
		m_list_activite.SetItemText(i,1,nomVillage);
		if(combo2.FindStringExact(0,nomVillage)==CB_ERR){ 
			combo2.AddString(nomVillage);
		}

		recset.GetFieldValue(L"nomPays",var); //🚩Error here
		Pays=(LPCWSTR)var.pbstrVal;
		m_list_activite.SetItemText(i,2,Pays);
		if(combo3.FindStringExact(0,Pays)==CB_ERR){ //🚩 pour n'avoir pas 2 fois meme chaine dans la combo.
			combo3.AddString(Pays);
		}
		

		recset.GetFieldValue(L"nomContinent",var);
		Continent=(LPCWSTR)var.pbstrVal;
		m_list_activite.SetItemText(i,3,Continent);
		if(combo4.FindStringExact(0,Continent)==CB_ERR){ 
			combo4.AddString(Continent);
		}

		i=i++;
		recset.MoveNext(); 
	}
	recset.Close();
	db.Close();
}

