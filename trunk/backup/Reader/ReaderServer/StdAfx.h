// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__40C01AF4_541F_40CF_92E4_3BDE97064DAF__INCLUDED_)
#define AFX_STDAFX_H__40C01AF4_541F_40CF_92E4_3BDE97064DAF__INCLUDED_

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

#define READER_COUNT (4)

#include "..\SimpleLog.h" // 日志头文件

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__40C01AF4_541F_40CF_92E4_3BDE97064DAF__INCLUDED_)
