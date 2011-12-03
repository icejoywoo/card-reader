// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__D36A68C9_50C2_4174_97A0_76AB9F4A438C__INCLUDED_)
#define AFX_STDAFX_H__D36A68C9_50C2_4174_97A0_76AB9F4A438C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

// my own header files
#include "SimpleLog.h"
#include <WINSOCK2.H> // win socket
#include <conio.h> // 
#include <winbase.h>

#pragma comment(lib, "WS2_32")
//#include "Reader.h"
#include "Server.h"
#include "ServerUtils.h"

#define DEFAULT_PORT (60000) // 服务器默认端口号

// 导入SmartCom
#include "SmartCom.h"
#pragma comment(lib, "SmartCom")

#include <map>  // 引入map
using namespace std;

#include "SplitStr.h" // 分割字符串的类

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__D36A68C9_50C2_4174_97A0_76AB9F4A438C__INCLUDED_)
