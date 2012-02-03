// FieldConfigDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DataTransferTool.h"
#include "FieldConfigDialog.h"
#include "DataTransfer.h"
#include "DataTransferToolDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFieldConfigDialog dialog


CFieldConfigDialog::CFieldConfigDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CFieldConfigDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFieldConfigDialog)
	m_EndType = _T("");
	m_StartType = _T("");
	m_EndData = _T("");
	m_StartData = _T("");
	m_Tag = _T("");
	//}}AFX_DATA_INIT
}


void CFieldConfigDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFieldConfigDialog)
	DDX_CBString(pDX, IDC_COMBO_END_TYPE, m_EndType);
	DDX_CBString(pDX, IDC_COMBO_START_TYPE, m_StartType);
	DDX_Text(pDX, IDC_EDIT_END_DATA, m_EndData);
	DDX_Text(pDX, IDC_EDIT_START_DATA, m_StartData);
	DDX_Text(pDX, IDC_EDIT_TAG, m_Tag);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFieldConfigDialog, CDialog)
	//{{AFX_MSG_MAP(CFieldConfigDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFieldConfigDialog message handlers

void CFieldConfigDialog::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	if (m_StartType.IsEmpty() && m_StartData.IsEmpty() && m_EndType.IsEmpty() && m_EndData.IsEmpty() && m_Tag.IsEmpty())
	{
		AfxMessageBox("输入不正确，不可以全部为空！");
	} 
	else
	{
		//  判断输入有效性
		CDataTransferToolDlg* parent = ((CDataTransferToolDlg*)GetParent());
		TransferRule rule;
		rule.SetStart(m_StartType, m_StartData);
		rule.SetEnd(m_EndType, m_EndData);
		rule.SetTag(m_Tag);
		parent->m_TempRule = rule;
		UpdateData(FALSE);
		CDialog::OnOK();
	}
}

void CFieldConfigDialog::OnCancel() 
{
	CDialog::OnCancel();
}
