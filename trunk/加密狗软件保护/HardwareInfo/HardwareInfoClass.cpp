// HardwareInfo1.cpp: implementation of the CHardwareInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "io.h"
#include "HardwareInfoClass.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHardwareInfo::CHardwareInfo()
{
	// fill CPU info
	GetSystemInfo(&m_SysInfo);
	m_wProcessorArchitecture = m_SysInfo.wProcessorArchitecture;
	m_wProcessorLevel = m_SysInfo.wProcessorLevel;
	m_wProcessorRevision = m_SysInfo.wProcessorRevision;
	m_dwProcessorNumber = m_SysInfo.dwNumberOfProcessors;
	m_dwPageSize = m_SysInfo.dwPageSize;

	// fill memory info
	m_MemStatus.dwLength = sizeof(MEMORYSTATUS);
	GlobalMemoryStatus(&m_MemStatus);
	m_dwTotalPhysicalMemory = m_MemStatus.dwTotalPhys;
	m_dwAvailPhysicalMemory = m_MemStatus.dwAvailPhys;
	m_dwTotalVirtualMemory = m_MemStatus.dwTotalVirtual;
	m_dwAvailVirtualMemory = m_MemStatus.dwAvailVirtual;

	// get keyboard info
	m_nKeyboardType = ::GetKeyboardType(0);
	m_nKeyboardFuncKeyNumber = -1;
	switch (::GetKeyboardType(2))
	{
		case 1:
		case 3:
		case 5:
			m_nKeyboardFuncKeyNumber = 10;
			break;
		case 2:
		case 4:
			m_nKeyboardFuncKeyNumber = 12;
			break;
		case 6:
			m_nKeyboardFuncKeyNumber = 24;
			break;
	}

	// get drive info
	m_dwDrives = ::GetLogicalDrives();

}

CHardwareInfo::~CHardwareInfo()
{
}

WORD CHardwareInfo::GetProcessorArchitecture()
{
	return m_wProcessorArchitecture;
}

WORD CHardwareInfo::GetProcessorLevel()
{
	return m_wProcessorLevel;
}

WORD CHardwareInfo::GetProcessorRevision()
{
	return m_wProcessorRevision;
}

DWORD CHardwareInfo::GetPageSize()
{
	return m_dwPageSize;
}

DWORD CHardwareInfo::GetProcessorNumber()
{
	return m_dwProcessorNumber;
}

DWORD CHardwareInfo::GetTotalPhysicalMemory()
{
	return m_dwTotalPhysicalMemory;
}

DWORD CHardwareInfo::GetAvailPhysicalMemory()
{
	return m_dwAvailPhysicalMemory;
}

DWORD CHardwareInfo::GetTotalVirtualMemory()
{
	return m_dwTotalVirtualMemory;
}

DWORD CHardwareInfo::GetAvailVirtualMemory()
{
	return m_dwAvailVirtualMemory;
}

int CHardwareInfo::GetKeyboardType()
{
	return m_nKeyboardType;
}

int	CHardwareInfo::GetKeyboardFuncKeyNumber()
{
	return m_nKeyboardFuncKeyNumber;
}

int	CHardwareInfo::GetLogicalDrives(CStringList* pDriveList)
{
	// get drive info
	int nDriveNumber = 0;
	for(int i=0; i<26; ++i)
	{
		if (m_dwDrives & (1L<<i))
		{
			CString s;
			s.Format("%c:\\", i+'A');
			pDriveList->AddTail(s);

			nDriveNumber++;
		}
	}
	return nDriveNumber;
}

UINT CHardwareInfo::GetDriveType(LPCSTR pszDriveRootPath)
{
	return ::GetDriveType(pszDriveRootPath);
}

ULONGLONG CHardwareInfo::GetTotalDriveSpace(LPCSTR pszDriveRootPath)
{
	if (_access(pszDriveRootPath, 0) == -1)
		return -1;
	ULARGE_INTEGER FreeBytesAvailableToCaller, TotalNumberOfBytes, TotalNumberOfFreeBytes;
	GetDiskFreeSpaceEx( pszDriveRootPath,
						&FreeBytesAvailableToCaller,
						&TotalNumberOfBytes,
						&TotalNumberOfFreeBytes);
	// total space
	return TotalNumberOfBytes.QuadPart;
}

ULONGLONG CHardwareInfo::GetAvailDriveSpace(LPCSTR pszDriveRootPath)
{
	if (_access(pszDriveRootPath, 0) == -1)
		return -1;
	ULARGE_INTEGER FreeBytesAvailableToCaller, TotalNumberOfBytes, TotalNumberOfFreeBytes;
	GetDiskFreeSpaceEx( pszDriveRootPath,
						&FreeBytesAvailableToCaller,
						&TotalNumberOfBytes,
						&TotalNumberOfFreeBytes);
	// total space
	return TotalNumberOfFreeBytes.QuadPart;
}

