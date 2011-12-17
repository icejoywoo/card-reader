//////////////////////////////////////////////////////////////////////////
// FileName: SimpleLog.h
// Creator: icejoywoo
// Date: 2011.11.28
// $Revision$
// $LastChangedDate$
// Comment: һ���򵥵���־��, ���ȼ���־: info, warn, error
//			Ĭ�ϱ���·��: ����Ŀ¼�µ�log, �ļ���������Ϊ����
//////////////////////////////////////////////////////////////////////////
#if !defined(AFX_SIMPLELOG_H__6BCBB496_2156_4415_94F5_962D614E57D5__INCLUDED_)
#define AFX_SIMPLELOG_H__6BCBB496_2156_4415_94F5_962D614E57D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include "StdAfx.h"

/**
 * @author: icejoywoo
 * @date: 2011.11.28
 * @version: 0.1
 */
class SimpleLog  
{
public:
	// ��ȡ��־����·��
	static char* GetlogFileLocation();
// 	// ������Ϣ
// 	static BOOL warn(char* logText);
// 	// ��ͨ��Ϣ
// 	static BOOL info(char* logText);
// 	// ������Ϣ
// 	static BOOL error(char* logText);

	// ������Ϣ
	static BOOL warn(char* format, ...);
	// ��ͨ��Ϣ
	static BOOL info(char* format, ...);
	// ������Ϣ
	static BOOL error(char* format, ...);
	
private:
	SimpleLog() {}
	virtual ~SimpleLog() {}
	// д��־���ļ�, ��ʽΪ ʱ��(%Y-%m-%d %X) ����
	static BOOL WriteLog(char* LogText);
	// ��ȡ��־�ļ�����
	static CString GetFileName();
	
	// ��ȡӦ�ó�������·��
	static CString GetFilePath();
private:
	// ��ֻ֤��һ���߳���д��־, ��ֹ��־�������
	static const HANDLE mutex;
	// �Ƿ��Ѿ�������־�ļ�
	static BOOL isLogFileCreated;
	// ��־�ļ�·��
	static CString logFileLocation;
};

#endif // !defined(AFX_SIMPLELOG_H__6BCBB496_2156_4415_94F5_962D614E57D5__INCLUDED_)
