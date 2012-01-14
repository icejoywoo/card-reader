// TemplateNameDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DataTransferTool.h"
#include "TemplateNameDialog.h"
#include "DataTransferToolDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTemplateNameDialog dialog


CTemplateNameDialog::CTemplateNameDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTemplateNameDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTemplateNameDialog)
	m_TemplateName = _T("");
	//}}AFX_DATA_INIT
}


void CTemplateNameDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTemplateNameDialog)
	DDX_Text(pDX, IDC_EDIT_TEMPLATE_NAME, m_TemplateName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTemplateNameDialog, CDialog)
	//{{AFX_MSG_MAP(CTemplateNameDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTemplateNameDialog message handlers

void CTemplateNameDialog::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	// 将模板名传给父窗口
	((CDataTransferToolDlg*)GetParent())->m_NewTemplateName = m_TemplateName;
	UpdateData(FALSE);
	CDialog::OnOK();
}
