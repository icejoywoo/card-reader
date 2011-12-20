//////////////////////////////////////////////////////////////////////////
// FileName: SimpleLog.h
// Creator: icejoywoo
// Date: 2011.11.28
// $Revision: 17 $
// $LastChangedDate: 2011-11-30 16:16:17 +0800 (å‘¨ä¸‰, 30 åä¸€æœˆ 2011) $
// Comment: Ò»¸ö¼òµ¥µÄÈÕÖ¾Àà, ÈıµÈ¼¶ÈÕÖ¾: info, warn, error
//			Ä¬ÈÏ±£´æÂ·¾¶: ³ÌĞòÄ¿Â¼ÏÂµÄlog, ÎÄ¼şÃûÒÔÈÕÆÚÎªÃû×Ö
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
	// »ñÈ¡ÈÕÖ¾±£´æÂ·¾¶
	static char* GetlogFileLocation();
	// ¾¯¸æĞÅÏ¢
	static BOOL warn(char* logText);
	// ÆÕÍ¨ĞÅÏ¢
	static BOOL info(char* logText);
	// ´íÎóĞÅÏ¢
	static BOOL error(char* logText);

	static HANDLE getMutex() {return mutex;}

	static int getErrors() {return errors;}
	
	static int getWarns() {return warns;}
private:
	SimpleLog() {}
	virtual ~SimpleLog() {}
	// Ğ´ÈÕÖ¾µ½ÎÄ¼ş, ¸ñÊ½Îª Ê±¼ä(%Y-%m-%d %X) ÄÚÈİ
	static BOOL WriteLog(char* LogText);
	// »ñÈ¡ÈÕÖ¾ÎÄ¼şÃû³Æ
	static CString GetFileName();
	
	// »ñÈ¡Ó¦ÓÃ³ÌĞòËùÔÚÂ·¾¶
	static CString GetFilePath();
private:
	// ±£Ö¤Ö»ÓĞÒ»¸öÏß³ÌÔÚĞ´ÈÕÖ¾, ·ÀÖ¹ÈÕÖ¾Êä³ö»ìÂÒ
	static const HANDLE mutex;
	// ÊÇ·ñÒÑ¾­½¨Á¢ÈÕÖ¾ÎÄ¼ş
	static BOOL isLogFileCreated;
	// ÈÕÖ¾ÎÄ¼şÂ·¾¶
	static CString logFileLocation;
	// Í³¼ÆÊı¾İ
	static ULONG errors;
	static ULONG warns;
};

#endif // !defined(AFX_SIMPLELOG_H__6BCBB496_2156_4415_94F5_962D614E57D5__INCLUDED_)
