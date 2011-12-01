
#if !defined(AFX_READERSERVER_H__8E614869_67C1_4DBD_BF18_5BBC4A42D1AA__INCLUDED_)
#define AFX_READERSERVER_H__8E614869_67C1_4DBD_BF18_5BBC4A42D1AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include <stdlib.h>

// ½«int×ª»»ÎªCString
CString i2str(int a)
{
	CString str;
	str.Format("%d", a);
	return str;
}

#endif // !defined(AFX_READERSERVER_H__8E614869_67C1_4DBD_BF18_5BBC4A42D1AA__INCLUDED_)
