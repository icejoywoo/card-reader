//////////////////////////////////////////////////////////////////////////
// FileName: SimpleLog.h
// Creator: icejoywoo
// Date: 2011.11.28
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
	// ��ȡ��־�ļ�����
	static CString GetFileName();

	// ��ȡӦ�ó�������·��
	static CString GetFilePath();
	
	// ������Ϣ
	static BOOL warn(CString logText);
	// ��ͨ��Ϣ
	static BOOL info(CString logText);
	// ������Ϣ
	static BOOL error(CString logText);
	
private:
	SimpleLog() {}
	virtual ~SimpleLog() {}
	// д��־���ļ�, ��ʽΪ ʱ��(%Y-%m-%d %X) ����
	static BOOL WriteLog(CString LogText);
private:
	// ��ֻ֤��һ���߳���д��־, ��ֹ��־�������
	static const HANDLE mutex;
	// �Ƿ��Ѿ�������־�ļ�
	static BOOL isLogFileCreated;
	// ��־�ļ�·��
	static CString logFileLocation;
};

#endif // !defined(AFX_SIMPLELOG_H__6BCBB496_2156_4415_94F5_962D614E57D5__INCLUDED_)
