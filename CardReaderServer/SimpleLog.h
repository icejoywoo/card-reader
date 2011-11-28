//////////////////////////////////////////////////////////////////////////
// FileName: SimpleLog.h
// Creator: icejoywoo
// Date: 2011.11.28
// Comment: 一个简单的日志类, 三等级日志: info, warn, error
//			默认保存路径: 程序目录下的log, 文件名以日期为名字
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
	// 获取日志文件名称
	static CString GetFileName();

	// 获取应用程序所在路径
	static CString GetFilePath();
	
	// 警告信息
	static BOOL warn(CString logText);
	// 普通信息
	static BOOL info(CString logText);
	// 错误信息
	static BOOL error(CString logText);
	
private:
	SimpleLog() {}
	virtual ~SimpleLog() {}
	// 写日志到文件, 格式为 时间(%Y-%m-%d %X) 内容
	static BOOL WriteLog(CString LogText);
private:
	// 保证只有一个线程在写日志, 防止日志输出混乱
	static const HANDLE mutex;
	// 是否已经建立日志文件
	static BOOL isLogFileCreated;
	// 日志文件路径
	static CString logFileLocation;
};

#endif // !defined(AFX_SIMPLELOG_H__6BCBB496_2156_4415_94F5_962D614E57D5__INCLUDED_)
