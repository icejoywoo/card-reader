//////////////////////////////////////////////////////////////////////////
// FileName: SimpleLog.cpp
// Creator: icejoywoo
// Date: 2011.11.28
// $Revision: 69 $
// $LastChangedDate: 2011-12-16 14:03:46 +0800 (å‘¨äº”, 16 åäºŒæœˆ 2011) $
// Comment: Ò»¸ö¼òµ¥µÄÈÕÖ¾ÀàµÄÊµÏÖ, ÈıµÈ¼¶ÈÕÖ¾: info, warn, error
//			Ä¬ÈÏ±£´æÂ·¾¶: ³ÌĞòÄ¿Â¼ÏÂµÄlog, ÎÄ¼şÃûÒÔÈÕÆÚÎªÃû×Ö
//////////////////////////////////////////////////////////////////////////
#include "SimpleLog.h"
#include <windows.h>

char* SimpleLog::GetlogFileLocation()
{
	if (isLogFileCreated == TRUE)
	{
		return (LPTSTR)(LPCTSTR)logFileLocation;
	}
	return "";
}

//»ñÈ¡ÎÄ¼şÃû³Æ
CString SimpleLog::GetFileName()
{
	CString m_sFileName;
	m_sFileName = CTime::GetCurrentTime().Format("%Y-%m-%d_%H_%M_%S") + ".log";
	return m_sFileName;
}
//»ñÈ¡Ó¦ÓÃ³ÌĞòËùÔÚÂ·¾¶
CString SimpleLog::GetFilePath()
{   
	CString m_FilePath;
	GetModuleFileName(NULL,m_FilePath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	m_FilePath.ReleaseBuffer();
	int m_iPosIndex;
	m_iPosIndex = m_FilePath.ReverseFind('\\'); 
	m_FilePath = m_FilePath.Left(m_iPosIndex) + "\\Log";
	return m_FilePath;
}

// Ğ´ÈÕÖ¾µ½ÎÄ¼ş, ¸ñÊ½Îª Ê±¼ä(%Y-%m-%d %X) ÄÚÈİ
BOOL SimpleLog::WriteLog(CString LogText)
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
		if (!isLogFileCreated)
		{
			logFileLocation = m_sFilePath + "\\" +m_sFileName;
			if(!m_FileFind.FindFile(m_sFilePath))
			{
				CreateDirectory(m_sFilePath, NULL);
			}			
			if(!m_SFile.Open(logFileLocation, CFile::modeReadWrite))
			{
				m_SFile.Open(logFileLocation, CFile::modeCreate | CFile::modeReadWrite | CFile::typeText);
			}
			isLogFileCreated = TRUE;
		} else {
			if(!m_SFile.Open(logFileLocation, CFile::modeReadWrite))
			{
				m_SFile.Open(logFileLocation, CFile::modeCreate | CFile::modeReadWrite | CFile::typeText);
			}
		}

		if (m_SFile.GetLength() > 100000000) // ´óÓÚ100MµÄÈÕÖ¾ÎÄ¼ş100000000
		{
			isLogFileCreated = FALSE;
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

BOOL SimpleLog::warn(CString logText)
{
	return WriteLog(" warn: " + logText);
}

BOOL SimpleLog::info(CString logText)
{
	return WriteLog(" info: " + logText);
}

BOOL SimpleLog::error(CString logText)
{
	return WriteLog(" error: " + logText);
}

const HANDLE SimpleLog::mutex = CreateMutex(NULL, FALSE, NULL);

BOOL SimpleLog::isLogFileCreated = FALSE;

CString SimpleLog::logFileLocation = "";