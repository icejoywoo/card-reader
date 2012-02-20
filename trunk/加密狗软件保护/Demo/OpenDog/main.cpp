#include <windows.h>
#include <iostream.h>
#include <stdio.h>
#include <time.h>
#include "GrandDogofDll.h"

void PrintMessage(HRESULT, const char*);

int main(void)
{
	HINSTANCE mlib;
	char Message[100];
	// 加载dll
	mlib = LoadLibrary(TEXT("RCGrandDogW32.dll"));
	if(mlib != NULL)
	{
		RC_OpenDog = (RC_OPENDOG)GetProcAddress(mlib, "rc_OpenDog");
		RC_CloseDog = (RC_CLOSEDOG)GetProcAddress(mlib, "rc_CloseDog");
		RC_CheckDog = (RC_CHECKDOG)GetProcAddress(mlib, "rc_CheckDog");
		RC_GetDogInfo = (RC_GETDOGINFO)GetProcAddress(mlib, "rc_GetDogInfo");
		RC_GetProductCurrentNo = (RC_GETPRODUCTCURRENTNO)GetProcAddress(mlib, "rc_GetProductCurrentNo");
		RC_VerifyPassword = (RC_VERIFYPASSWORD)GetProcAddress(mlib, "rc_VerifyPassword");
		RC_ChangePassword = (RC_CHANGEPASSWORD)GetProcAddress(mlib, "rc_ChangePassword");
		RC_Upgrade = (RC_UPGRADE)GetProcAddress(mlib, "rc_Upgrade");
		RC_GetRandom = (RC_GETRANDOM)GetProcAddress(mlib, "rc_GetRandom");
		RC_EncryptData = (RC_ENCRYPTDATA)GetProcAddress(mlib, "rc_EncryptData");
		RC_DecryptData = (RC_DECRYPTDATA)GetProcAddress(mlib, "rc_DecryptData");
		RC_ConvertData = (RC_CONVERTDATA)GetProcAddress(mlib, "rc_ConvertData");
		RC_SetKey = (RC_SETKEY)GetProcAddress(mlib, "rc_SetKey");
		RC_SignData = (RC_SIGNDATA)GetProcAddress(mlib, "rc_SignData");
		RC_ExecuteFile = (RC_EXECUTEFILE)GetProcAddress(mlib, "rc_ExecuteFile");
		RC_WriteFile = (RC_WRITEFILE)GetProcAddress(mlib, "rc_WriteFile");
		RC_VisitLicenseFile = (RC_VISITLICENSEFILE)GetProcAddress(mlib, "rc_VisitLicenseFile");
		RC_CreateFile = (RC_CREATEFILE)GetProcAddress(mlib, "rc_CreateFile");
		RC_DeleteFile = (RC_DELETEFILE)GetProcAddress(mlib, "rc_DeleteFile");
		RC_CreateDir = (RC_CREATEDIR)GetProcAddress(mlib, "rc_CreateDir");
		RC_DeleteDir = (RC_DELETEDIR)GetProcAddress(mlib, "rc_DeleteDir");
		RC_DefragFileSystem = (RC_DEFRAGFILESYSTEM)GetProcAddress(mlib, "rc_DefragFileSystem");
		RC_ReadFile = (RC_READFILE)GetProcAddress(mlib, "rc_ReadFile");
		RC_GetUpgradeRequestString = (RC_GETUPGRADEREQUESTSTRING)GetProcAddress(mlib, "rc_GetUpgradeRequestString");
		RC_GetLicenseInfo = (RC_GETLICENSEINFO)GetProcAddress(mlib, "rc_GetLicenseInfo");
	}
	else
	{
		wsprintf (Message, "Load RCGrandDogW32.dll failed.");
		cout << Message << endl;
		exit(0);
	}

	char PRODUCT_NAME[] = {"GrandDog"};
	HRESULT result = S_OK;
	ULONG DogHandle;

	// 打开加密狗, 通过product_name来区分狗, RC_OPEN_NEXT_IN_LOCAL打开下一只狗
	result = RC_OpenDog(RC_OPEN_FIRST_IN_LOCAL, PRODUCT_NAME, &DogHandle);
	PrintMessage(result, "Open Dog");

	// 验证开发商密码
	char DEVELOPER_PASSWORD[] = {"abcdefgh"};
	UCHAR ucDegree = 0;
	result = RC_VerifyPassword(DogHandle, RC_PASSWORDTYPE_DEVELOPER, DEVELOPER_PASSWORD, &ucDegree);
	PrintMessage(result, "Verify Password");
	
	result = RC_CreateDir(DogHandle, 4, 256);
	PrintMessage(result, "Create Dir");

	result = RC_CreateFile(DogHandle, 4, 5, RC_TYPEFILE_DATA, 200);
	PrintMessage(result, "Create File");
	
	long current_time;
	time(&current_time);
	printf("%ld\n", current_time);
	char buf[64];
	memset(buf, 0, 64);
	memcpy(buf, &current_time, sizeof(long));
	memcpy(&buf[4], &current_time, sizeof(long));
	result = RC_WriteFile(DogHandle, 4, 5, 0l, 64l, (UCHAR*)buf);
	PrintMessage(result, "Write File");

	char buf1[200];
	result = RC_ReadFile(DogHandle, 4, 5, 0l, 200l, (UCHAR*)buf1);
	PrintMessage(result, "Read File");

	long time_data;
	memcpy(&time_data, buf1, sizeof(long));
	cout << time_data << endl;
	memcpy(&time_data, &buf1[4], sizeof(long));
	cout << time_data << endl;

	// 关闭加密狗
	result = RC_CloseDog(DogHandle);
	PrintMessage(result, "Close Dog");

	return 0;
}

void PrintMessage(HRESULT result, const char* msg)
{
	if (result != S_OK)
	{
		printf("%s failed. Error code: 0x%lX\n", msg, result);
	}
	else
	{
		printf("%s success.\n", msg);
	}
}