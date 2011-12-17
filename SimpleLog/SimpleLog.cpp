//////////////////////////////////////////////////////////////////////////
// FileName: SimpleLog.cpp
// Creator: icejoywoo
// Date: 2011.11.28
// $Revision$
// $LastChangedDate$
// Comment: 一个简单的日志类的实现, 三等级日志: info, warn, error
//			默认保存路径: 程序目录下的log, 文件名以日期为名字
//////////////////////////////////////////////////////////////////////////
#include "SimpleLog.h"
#include <windows.h>
#include <stdio.h>
#include <stdarg.h>  

char* SimpleLog::GetlogFileLocation()
{
	if (isLogFileCreated == TRUE)
	{
		return (LPTSTR)(LPCTSTR)logFileLocation;
	}
	return "";
}

//获取文件名称
CString SimpleLog::GetFileName()
{
	CString m_sFileName;
	m_sFileName = CTime::GetCurrentTime().Format("%Y-%m-%d_%H_%M_%S") + ".log";
	return m_sFileName;
}
//获取应用程序所在路径
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

// 写日志到文件, 格式为 时间(%Y-%m-%d %X) 内容
BOOL SimpleLog::WriteLog(char* LogText)
{
	WaitForSingleObject(mutex, INFINITE);
	try
	{
		CStdioFile m_SFile;
		CFileFind m_FileFind;
		char m_sLogMessage[512]; // 存放日志消息的地方
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

		if (m_SFile.GetLength() >= 100000000) // 大于100M的日志文件100000000
		{
			isLogFileCreated = FALSE;
		}

		m_SFile.SeekToEnd(); 
		
		m_SFile.Write(m_sLogMessage,lstrlen(m_sLogMessage));   	
		m_SFile.Close();
		ReleaseMutex(mutex);
	}
	catch(CFileException fileException)
	{
		return false;
	}
	return true;
}

// BOOL SimpleLog::warn(char* logText)
// {
// 	char buf[512];
// 	sprintf(buf, " warn: %s", logText);
// 	return WriteLog(buf);
// }
// 
// BOOL SimpleLog::info(char* logText)
// {
// 	char buf[512];
// 	sprintf(buf, " info: %s", logText);
// 	return WriteLog(buf);
// }
// 
// BOOL SimpleLog::error(char* logText)
// {
// 	char buf[512];
// 	sprintf(buf, " error: %s", logText);
// 	return WriteLog(buf);
// }


BOOL SimpleLog::warn(char* format, ...)
{
	char myFormat[512];
	sprintf(myFormat, " warn: %s", format);
	TRACE(CString("myFormat") + myFormat + "\n");
	char buf[512];
	va_list arg_ptr;
	va_start(arg_ptr, myFormat);
	sprintf(buf, myFormat, arg_ptr);
	va_end(arg_ptr);
	return WriteLog(buf);
}

BOOL SimpleLog::info(char* format, ...)
{
	char myFormat[512];
	sprintf(myFormat, " info: %s", format);
	TRACE(CString("myFormat") + myFormat + "\n");
	char buf[512];
	va_list arg_ptr;
	va_start(arg_ptr, myFormat);
	sprintf(buf, myFormat, arg_ptr);
	va_end(arg_ptr);
	return WriteLog(buf);
}

BOOL SimpleLog::error(char* format, ...)
{
	char myFormat[512];
	sprintf(myFormat, " error: %s", format);
	TRACE(CString("myFormat") + myFormat + "\n");
	char buf[512];
	va_list arg_ptr;
	va_start(arg_ptr, myFormat);
	sprintf(buf, myFormat, arg_ptr);
	va_end(arg_ptr);
	return WriteLog(buf);
}

const HANDLE SimpleLog::mutex = CreateMutex(NULL, FALSE, NULL);

BOOL SimpleLog::isLogFileCreated = FALSE;

CString SimpleLog::logFileLocation = "";