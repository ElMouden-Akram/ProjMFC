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
	, m_nomAct(_T(""))
	, m_nomPay(_T(""))
	, m_nomVil(_T(""))
	, m_nomCon(_T(""))
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
	DDX_Text(pDX, IDC_nomActEdit, m_nomAct);
	DDX_Text(pDX, IDC_nomVilEdit, m_nomVil);
	DDX_Text(pDX, IDC_nomPayEdit, m_nomPay);
	DDX_Text(pDX, IDC_nomConEdit, m_nomCon);
}


BEGIN_MESSAGE_MAP(Activite, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &Activite::OnCbnSelchangeACombo)
	ON_CBN_SELCHANGE(IDC_COMBO2, &Activite::OnCbnSelchangeACombo)
	ON_CBN_SELCHANGE(IDC_COMBO3, &Activite::OnCbnSelchangeACombo)
	ON_CBN_SELCHANGE(IDC_COMBO4, &Activite::OnCbnSelchangeACombo)
	ON_BN_CLICKED(IDC_ACTIV_ACTUALISER, &Activite::OnBnClickedActivActualiser)
	ON_NOTIFY(NM_CLICK, IDC_LIST3, &Activite::SelectItemOnList) //created manually not using ClassWizard
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
	
	CString sequel = L"SELECT Activites.NomActivite,Villages.nomVillage,Pays.nomPays,Continents.nomContinent FROM Activites, proposer, Villages, Pays, Continents WHERE Activites.idActivite = proposer.idActivite AND proposer.codeVillage = Villages.codeVillage AND Villages.codePays = Pays.codePays AND Pays.codeContinent = Continents.codeContinent;";
	ExtractDataFromDB(sequel);

	return TRUE;
}

void Activite::ExtractDataFromDB(CString sequel){
	CDaoDatabase db; //déclaration de variable base de donnée db : represents a connection to a database.
	CDaoRecordset recset(&db); //the varaible "recset" used to represent a 'set of records' from a database table.

	COleVariant var;//start Variables
	var.ChangeType(VT_BSTR,NULL);

	m_list_activite.DeleteAllItems();//♻ clear list
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



void Activite::OnCbnSelchangeACombo()
{
	// TODO: Add your control notification handler code here

	//🚩this fonction serve as 'message' for all the combo boxes, rather than being specific to just one of them ( not for only 1 of them)
	ComboClicked();	
}

void Activite::ComboClicked(){
	// for all the combo boxes : ses variables vont contenir la "chaine" selectionner pour l'utiliser dans la requet de tri.
	CString selectedTextCombo1 ;
	CString selectedTextCombo2 ;
	CString selectedTextCombo3 ;
	CString selectedTextCombo4 ;

	int ind1 = combo1.GetCurSel();  //Il retourne le numero de la ligne selectionné (commencant de 0 et non pas 1) , pour recuperer apres la chaine voulu .
	int ind2 = combo2.GetCurSel();
	int ind3 = combo3.GetCurSel();
	int ind4 = combo4.GetCurSel();
	CString temp; // ou mettre les valeur string selectionner 

	if ( ind1 != CB_ERR ){          //equivalent de dire "if "combo1" selected". By default, CB_ERR is a varaible that equals to -1 , CB_ERR = -1  .
		
		combo1.GetLBText(ind1,temp);  //then take its string.
		selectedTextCombo1 = CString(" AND Activites.nomActivite =\"")+temp+CString("\"");
		temp.Empty(); //vider la varaible
	}
	if ( ind2 != CB_ERR ){
		combo2.GetLBText(ind2,temp);
		selectedTextCombo2 = CString(" AND Villages.nomVillage =\"")+temp+CString("\"");
		temp.Empty();
	}
	if ( ind3 != CB_ERR ){
		combo3.GetLBText(ind3,temp);
		selectedTextCombo3 = CString(" AND Pays.nomPays =\"")+temp+CString("\"");
		temp.Empty();
	}
	if ( ind4 != CB_ERR ){
		combo4.GetLBText(ind4,temp);
		selectedTextCombo4 = CString(" AND Continents.nomContinent =\"")+temp+CString("\"");
		temp.Empty();
	}

	//now the request : 
	CString sequel = L"SELECT Activites.NomActivite,Villages.nomVillage,Pays.nomPays,Continents.nomContinent" 
		+ CString(L" FROM Activites, proposer, Villages, Pays, Continents")
		+ CString(L" WHERE Activites.idActivite = proposer.idActivite ")+selectedTextCombo1
		+ CString(L" AND")
		+ CString(L" proposer.codeVillage = Villages.codeVillage")+selectedTextCombo2
		+ CString(L" AND ")
		+ CString(L" Villages.codePays = Pays.codePays AND Pays.nomPays")+selectedTextCombo3
		+ CString(L" AND ")
		+ CString(L" Pays.codeContinent = Continents.codeContinent AND Continents.nomContinent ")+selectedTextCombo4;
	ExtractDataFromDB(sequel);

}




void Activite::OnBnClickedActivActualiser()
{
	// TODO: Add your control notification handler code here
	CString sequel = L"SELECT Activites.NomActivite,Villages.nomVillage,Pays.nomPays,Continents.nomContinent FROM Activites, proposer, Villages, Pays, Continents WHERE Activites.idActivite = proposer.idActivite AND proposer.codeVillage = Villages.codeVillage AND Villages.codePays = Pays.codePays AND Pays.codeContinent = Continents.codeContinent;";
	ExtractDataFromDB(sequel);
}

void Activite::SelectItemOnList(NMHDR *pNMHDR, LRESULT *pResult){
	//This fonction is a message when you double click on list , it put the selected thing in the dialogues :

	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	NMHDR x(*pNMHDR);
	
	// TODO: Add your control notification handler code here
	*pResult = 0;

	int id_item_list = pNMLV->iItem; //id selected item
	//CString id_champ = m_list.GetItemText(p,0); //id⚡⚡⚡💀💀 (so gdmn good thing! use it later)
	m_nomAct = m_list_activite.GetItemText(id_item_list,1);
	m_nomVil = m_list_activite.GetItemText(id_item_list,2);
	//GetDlgItemText = m_list.GetItemText(id_item_list,3);
	SetDlgItemText(IDC_nomActEdit ,m_list_activite.GetItemText(id_item_list,0));
	SetDlgItemText(IDC_nomVilEdit ,m_list_activite.GetItemText(id_item_list,1));
	SetDlgItemText(IDC_nomPayEdit ,m_list_activite.GetItemText(id_item_list,2));
	SetDlgItemText(IDC_nomConEdit ,m_list_activite.GetItemText(id_item_list,3));
	//AfxMessageBox(m_localite);
}
