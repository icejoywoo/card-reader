// HardwareInfo1.h: interface for the CHardwareInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HARDWAREINFO1_H__E3A8EFA1_C05C_11D3_BC14_0080C7249374__INCLUDED_)
#define AFX_HARDWAREINFO1_H__E3A8EFA1_C05C_11D3_BC14_0080C7249374__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHardwareInfo  
{
public:
	CHardwareInfo();
	virtual ~CHardwareInfo();

	// CPU
	WORD	GetProcessorArchitecture();
	WORD	GetProcessorLevel();
	WORD	GetProcessorRevision();
	DWORD	GetProcessorNumber();
	DWORD	GetPageSize();
	// Memory
	DWORD	GetTotalPhysicalMemory();
	DWORD	GetAvailPhysicalMemory();
	DWORD	GetTotalVirtualMemory();
	DWORD	GetAvailVirtualMemory();
	// Keyboard
	int		GetKeyboardType();
	int		GetKeyboardFuncKeyNumber();
	// Drives
	int		GetLogicalDrives(CStringList* pDriveList);
	UINT	GetDriveType(LPCSTR pszDriveRootPath);
	ULONGLONG	GetTotalDriveSpace(LPCSTR pszDriveRootPath);
	ULONGLONG	GetAvailDriveSpace(LPCSTR pszDriveRootPath);
	// All info
	SYSTEM_INFO		m_SysInfo;
	MEMORYSTATUS	m_MemStatus;
	DWORD			m_dwDrives;

protected:
	WORD	m_wProcessorArchitecture;
	WORD	m_wProcessorLevel;
	WORD	m_wProcessorRevision;
	DWORD	m_dwPageSize;
	DWORD	m_dwProcessorNumber;
	DWORD	m_dwTotalPhysicalMemory;
	DWORD	m_dwAvailPhysicalMemory;
	DWORD	m_dwTotalVirtualMemory;
	DWORD	m_dwAvailVirtualMemory;
	int		m_nKeyboardType;
	int		m_nKeyboardFuncKeyNumber;
};

#endif // !defined(AFX_HARDWAREINFO1_H__E3A8EFA1_C05C_11D3_BC14_0080C7249374__INCLUDED_)
