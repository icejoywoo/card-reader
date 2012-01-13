#include "StdAfx.h"
#include "Utils.h"
#include "DataTransfer.h"
#include "DataTransferToolDlg.h"

UINT DataTransferThread(LPVOID pParam)
{
	CString* target = (CString*) pParam;

	CString m_FilePath;
	GetModuleFileName(NULL,m_FilePath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	m_FilePath.ReleaseBuffer();
	int m_iPosIndex;
	m_iPosIndex = m_FilePath.ReverseFind('\\'); 
	CString currentPath = m_FilePath.Left(m_iPosIndex);

	CString dbfile;
	dbfile.Format("%s\\data.db", currentPath);
	DataTransfer transfer(dbfile);
	dbfile.ReleaseBuffer();

	transfer.load("Test");
	transfer.Handle(*target);
	
	AfxMessageBox("数据转换完成!");
	return 0;
}