
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the CARDREADERCLIENTDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// CARDREADERCLIENTDLL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef CARDREADERCLIENTDLL_EXPORTS
#define CARDREADERCLIENTDLL_API __declspec(dllexport)
#else
#define CARDREADERCLIENTDLL_API __declspec(dllimport)
#endif

// This class is exported from the CardReaderClientDll.dll
class CARDREADERCLIENTDLL_API CCardReaderClientDll {
public:
	CCardReaderClientDll(void);
	// TODO: add your methods here.
};

extern CARDREADERCLIENTDLL_API int nCardReaderClientDll;

CARDREADERCLIENTDLL_API int fnCardReaderClientDll(void);

