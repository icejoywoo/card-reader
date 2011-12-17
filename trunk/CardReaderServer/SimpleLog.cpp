//////////////////////////////////////////////////////////////////////////
// FileName: SimpleLog.cpp
// Creator: icejoywoo
// Date: 2011.11.28
// $Revision: 69 $
// $LastChangedDate: 2011-12-16 14:03:46 +0800 (周五, 16 十二月 2011) $
// Comment: һ���򵥵���־���ʵ��, ���ȼ���־: info, warn, error
//			Ĭ�ϱ���·��: ����Ŀ¼�µ�log, �ļ���������Ϊ����
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

//��ȡ�ļ�����
CString SimpleLog::GetFileName()
{
	CString m_sFileName;
	m_sFileName = CTime::GetCurrentTime().Format("%Y-%m-%d_%H_%M_%S") + ".log";
	return m_sFileName;
}
//��ȡӦ�ó�������·��
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

// д��־���ļ�, ��ʽΪ ʱ��(%Y-%m-%d %X) ����
BOOL SimpleLog::WriteLog(char* LogText)
{
	WaitForSingleObject(mutex, INFINITE);
	try
	{
		CStdioFile m_SFile;
		CFileFind m_FileFind;
		char m_sLogMessage[512];
		CString m_sFileName = GetFileName();
		CString m_sFilePath = GetFilePath();
		CString m_sCurrentTime = CTime::GetCurrentTime().Format("%Y-%m-%d %X");

		sprintf(m_sLogMessage, "[%s]%s\r\n", m_sCurrentTime, LogText);
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

		if (m_SFile.GetLength() > 100000000) // ����100M����־�ļ�100000000
		{
			isLogFileCreated = FALSE;
		}

		m_SFile.SeekToEnd(); 
		
		m_SFile.WriteString(m_sLogMessage);
		
		// TODO: ����־���뵽��������, ����Ժ�ǿ
		//EnterCriticalSection(&(Server::getInstance()->g_cs));
		Server::getInstance()->log += m_sLogMessage;
		//LeaveCriticalSection(&(Server::getInstance()->g_cs));

		m_SFile.Close();
		ReleaseMutex(mutex);
	}
	catch(CFileException fileException)
	{
		return false;
	}
	return true;
}

BOOL SimpleLog::warn(char* logText)
{
	char buf[512];
	sprintf(buf, " warn: %s", logText);
	return WriteLog(buf);
}

BOOL SimpleLog::info(char* logText)
{
	char buf[512];
	sprintf(buf, " info: %s", logText);
	return WriteLog(buf);
}

BOOL SimpleLog::error(char* logText)
{
	char buf[512];
	sprintf(buf, " error: %s", logText);
	return WriteLog(buf);
}

const HANDLE SimpleLog::mutex = CreateMutex(NULL, FALSE, NULL);

BOOL SimpleLog::isLogFileCreated = FALSE;

CString SimpleLog::logFileLocation = "";