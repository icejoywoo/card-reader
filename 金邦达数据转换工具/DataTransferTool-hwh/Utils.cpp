#include "StdAfx.h"
#include "Utils.h"
#include "DataTransfer.h"
#include "DataTransferToolDlg.h"

UINT DataTransferThread(LPVOID pParam)
{
	CDataTransferToolDlg* mainFrame = (CDataTransferToolDlg*) pParam;

// 	CString m_FilePath;
// 	GetModuleFileName(NULL,m_FilePath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
// 	m_FilePath.ReleaseBuffer();
// 	int m_iPosIndex;
// 	m_iPosIndex = m_FilePath.ReverseFind('\\'); 
// 	CString currentPath = m_FilePath.Left(m_iPosIndex);
// 	
// 	CString dbfile;
// 	dbfile.Format("%s\\data.db", currentPath);
//	::SetCurrentDirectory(currentPath);
//	DataTransfer transfer(Convert(dbfile, CP_ACP, CP_UTF8));
	DataTransfer transfer;
	
	transfer.load(mainFrame->m_CurrentTemplate);
	if (mainFrame->m_TargetFile.IsEmpty())
	{
		transfer.Handle(mainFrame->m_InputFile, mainFrame->m_SplitSize);
	}
	else
	{
		transfer.Handle(mainFrame->m_InputFile, mainFrame->m_SplitSize, mainFrame->m_TargetFile);
	}
	
	return 0;
}

CString Convert(CString str, int sourceCodepage, int targetCodepage) 
{ 
	int len=str.GetLength(); 
	
	int unicodeLen=MultiByteToWideChar(sourceCodepage,0,str,-1,NULL,0); 
	
	wchar_t * pUnicode; 
	pUnicode=new wchar_t[unicodeLen+1]; 
	
	memset(pUnicode,0,(unicodeLen+1)*sizeof(wchar_t)); 
	
	
	MultiByteToWideChar(sourceCodepage,0,str,-1,(LPWSTR)pUnicode,unicodeLen); 
	
	BYTE * pTargetData; 
	int targetLen=WideCharToMultiByte(targetCodepage,0,(LPWSTR)pUnicode,-1,(char *)pTargetData,0,NULL,NULL); 
	
	pTargetData=new BYTE[targetLen+1]; 
	memset(pTargetData,0,targetLen+1); 
	
	WideCharToMultiByte(targetCodepage,0,(LPWSTR)pUnicode,-1,(char *)pTargetData,targetLen,NULL,NULL); 
	
	CString rt; 
	rt.Format("%s",pTargetData); 
	
	delete []pUnicode; 
	delete []pTargetData; 
	return rt; 
	
 }