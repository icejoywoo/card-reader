// TransferingDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DataTransferTool.h"
#include "TransferingDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransferingDialog dialog


CTransferingDialog::CTransferingDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTransferingDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTransferingDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTransferingDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransferingDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTransferingDialog, CDialog)
	//{{AFX_MSG_MAP(CTransferingDialog)
	ON_BN_CLICKED(IDC_OK, OnOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransferingDialog message handlers

void CTransferingDialog::OnOk() 
{
	// TODO: Add your control notification handler code here
	
}
