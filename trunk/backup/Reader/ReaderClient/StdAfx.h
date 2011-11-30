// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__666F1723_8D0A_4BB5_882A_D2015EC309E8__INCLUDED_)
#define AFX_STDAFX_H__666F1723_8D0A_4BB5_882A_D2015EC309E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afx.h>
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <iostream>

// TODO: reference additional headers your program requires here

#include <WINSOCK2.H> // win socket
#include <conio.h> // 
#include <winbase.h>
#include <string.h>

#pragma comment(lib, "WS2_32")

#include "..\SimpleLog.h" // 日志头文件

#define  READER_COUNT (4)
#define CLIENT_COUNT (16) // the number of simulated clients


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__666F1723_8D0A_4BB5_882A_D2015EC309E8__INCLUDED_)
