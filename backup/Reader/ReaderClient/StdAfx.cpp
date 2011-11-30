// stdafx.cpp : source file that includes just the standard includes
//	ReaderClient.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
const HANDLE SimpleLog::mutex = CreateMutex(NULL, FALSE, NULL);
// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
