// SimpleLog.h: interface for the CLogFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMPLELOG_H__288388CA_9A3E_4F3D_A2B8_F1078E1F6A6B__INCLUDED_)
#define AFX_SIMPLELOG_H__288388CA_9A3E_4F3D_A2B8_F1078E1F6A6B__INCLUDED_

#include "stdafx.h"

class SimpleLog  
{
public:
	SimpleLog() {}
	virtual ~SimpleLog() {}
	//获取文件名称
	static CString GetFileName()
	{
		CString m_sFileName;
		m_sFileName = CTime::GetCurrentTime().Format("%Y-%m-%d") + ".log";
		return m_sFileName;
	}
	//获取应用程序所在路径
	static CString GetFilePath()
	{   
		CString m_FilePath;
		GetModuleFileName(NULL,m_FilePath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
		m_FilePath.ReleaseBuffer();
		int m_iPosIndex;
		m_iPosIndex = m_FilePath.ReverseFind('\\'); 
		m_FilePath = m_FilePath.Left(m_iPosIndex) + "\\Log";
		return m_FilePath;
	}
	
	static BOOL warn(CString logText)
	{
		return WriteLog(" warn: " + logText);
	}

	static BOOL info(CString logText)
	{
		return WriteLog(" info: " + logText);
	}

	static BOOL error(CString logText)
	{
		return WriteLog(" error: " + logText);
	}

private:
	// 写日志到文件, 格式为 时间(%Y-%m-%d %X) 内容
	static BOOL WriteLog(CString LogText)
	{
		WaitForSingleObject(mutex, INFINITE);
		try
		{
			CStdioFile m_SFile;
			CFileFind m_FileFind;
			CString m_sErrorMessage;
			CString m_sFileName = GetFileName();
			CString m_sFilePath = GetFilePath();
			CString m_sCurrentTime = CTime::GetCurrentTime().Format("%Y-%m-%d %X");
			
			m_sErrorMessage = "[" + m_sCurrentTime + "]" + LogText + "\r\n";
			
			if(!m_FileFind.FindFile(m_sFilePath))
			{
				CreateDirectory(m_sFilePath, NULL);
			}			
			if(!m_SFile.Open(m_sFilePath + "\\" +m_sFileName,CFile::modeReadWrite))
			{
				m_SFile.Open(m_sFilePath + "\\" + m_sFileName,CFile::modeCreate | CFile::modeReadWrite | CFile::typeText);
			}			
			m_SFile.SeekToEnd(); 			
			char* m_szMessage;			
			m_szMessage=(LPTSTR)(LPCTSTR)m_sErrorMessage;
			m_SFile.Write(m_szMessage,lstrlen(m_szMessage));   	
			m_SFile.Close();
			ReleaseMutex(mutex);
		}
		catch(CFileException fileException)
		{
			return false;
		}
		return true;
	}
private:
	static const HANDLE mutex;
};

#endif // !defined(AFX_SIMPLELOG_H__288388CA_9A3E_4F3D_A2B8_F1078E1F6A6B__INCLUDED_)
