// CardReaderClientDll.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "CardReaderClientDll.h"

#define SMARTCOMSTRING_EXPORTS_MACRO

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}


// This is an example of an exported variable
// CARDREADERCLIENTDLL_API int nCardReaderClientDll=0;

// This is an example of an exported function.
// CARDREADERCLIENTDLL_API int fnCardReaderClientDll(void)
// {
// 	return 42;
// }

// This is the constructor of a class that has been exported.
// see CardReaderClientDll.h for the class definition
// CCardReaderClientDll::CCardReaderClientDll()
// { 
// 	return; 
// }

typedef struct _ClientParam
{
	char* serverIp;
	int serverPort;
} ClientParam;

ClientParam clientParam;


CARDREADERCLIENTDLL_API int initClient(char* serverIp, int serverPort)
{
	clientParam.serverIp = serverIp;
	clientParam.serverPort = serverPort;
	return 0;
}

CARDREADERCLIENTDLL_API int getReader(int cardId, char* userId)
{
	return 0;
}

CARDREADERCLIENTDLL_API int releaseReader(int cardId)
{
	return 0;
}

