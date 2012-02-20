#define RC_OPEN_FIRST_IN_LOCAL			1
#define RC_OPEN_NEXT_IN_LOCAL			2
#define RC_OPEN_IN_LAN					3
#define RC_OPEN_LOCAL_FIRST				4
#define RC_OPEN_LAN_FIRST				5

#define RC_PASSWORDTYPE_USER			1
#define RC_PASSWORDTYPE_DEVELOPER		2

#define RC_DOGTYPE_LOCAL				1
#define RC_DOGTYPE_NET					2

#define RC_TYPEFILE_DATA				1
#define RC_TYPEFILE_LICENSE				2
#define RC_TYPEFILE_ALGORITHMS			3
#define RC_TYPEFILE_DIR					4

#define RC_KEY_AES						1
#define RC_KEY_SIGN						2

#ifndef ULONG
#define ULONG	unsigned long
#endif
#ifndef CHAR
#define CHAR	char
#endif
#ifndef HRESULT
#define HRESULT	unsigned long
#endif


/////////////////////////////////////////////////////////////////
// structure definitoin
#pragma pack(1)

typedef struct _RC_HARDWARE_INFO
{
	ULONG 	ulSerialNumber;			//The Serial Number
	ULONG 	ulCurrentNumber;   		//The Hardware Current Number
	UCHAR 	ucDogType;        		//Hardware Dog Type, NetDog or LocalDog
	UCHAR	ucDogModel[4];			//UGRA or PGRA, at this version ,it is equal to UGRA
}RC_HARDWARE_INFO,*PRC_HARDWARE_INFO;

typedef struct _RC_PRODUCT_INFO
{
	CHAR	szProductName[16];       //Product Name
	ULONG 	ulProductCurNumber;   	 //The Developer Current Number
}RC_PRODUCT_INFO,*PRC_PRODUCT_INFO;

#pragma pack()

typedef HRESULT (WINAPI *RC_OPENDOG)(ULONG ulFlag, CHAR * pszProductName, ULONG * pDogHandle);
typedef HRESULT (WINAPI *RC_CLOSEDOG)(ULONG DogHandle);
typedef HRESULT (WINAPI *RC_CHECKDOG)(ULONG DogHandle);
typedef HRESULT (WINAPI *RC_GETDOGINFO)(ULONG DogHandle, RC_HARDWARE_INFO * pHardwareInfo, ULONG * pulLen);
typedef HRESULT (WINAPI *RC_GETPRODUCTCURRENTNO)(ULONG DogHandle, ULONG * pulProductCurrentNo);
typedef HRESULT (WINAPI *RC_VERIFYPASSWORD)(ULONG DogHandle, UCHAR ucPasswordType, CHAR * pszPassword,  UCHAR * pucDegree);
typedef HRESULT (WINAPI *RC_CHANGEPASSWORD)(ULONG DogHandle, UCHAR ucPasswordType, CHAR * pszPassword);
typedef HRESULT (WINAPI *RC_UPGRADE)(ULONG DogHandle, UCHAR * pucUpgrade, ULONG ulLen);
typedef HRESULT (WINAPI *RC_GETRANDOM)(ULONG DogHandle, UCHAR * pucRandom, UCHAR ucLen);
typedef HRESULT (WINAPI *RC_ENCRYPTDATA)(ULONG DogHandle, UCHAR * pucIn, ULONG ulInLen, UCHAR * pucOut, ULONG * pulOutLen);
typedef HRESULT (WINAPI *RC_DECRYPTDATA)(ULONG DogHandle, UCHAR * pucIn, ULONG ulInLen, UCHAR * pucOut, ULONG * pulOutLen);
typedef HRESULT (WINAPI *RC_CONVERTDATA)(ULONG DogHandle, UCHAR * pucIn, ULONG ulLen, ULONG * pulRet);
typedef HRESULT (WINAPI *RC_SETKEY)(ULONG DogHandle, UCHAR ucKeyType, UCHAR * pucIn, ULONG ulLen);
typedef HRESULT (WINAPI *RC_SIGNDATA)(ULONG DogHandle, UCHAR * pucIn, ULONG ulLen, UCHAR * pucOut, ULONG * pulOutLen);
typedef HRESULT (WINAPI *RC_EXECUTEFILE)(ULONG DogHandle, USHORT usDirID, USHORT usFileID, UCHAR * pucDataIn,
							  ULONG ulInLen, UCHAR * pucDataOut, ULONG * pulOutLen);				
typedef HRESULT (WINAPI *RC_WRITEFILE)(ULONG DogHandle, USHORT usDirID, USHORT usFileID, ULONG ulPos, ULONG ulLen, UCHAR * pucbuf);
typedef HRESULT (WINAPI *RC_VISITLICENSEFILE)(ULONG DogHandle, USHORT usDirID, USHORT usFileID, ULONG ulReserved);
typedef HRESULT (WINAPI *RC_CREATEFILE)(ULONG DogHandle, USHORT usDirID, USHORT usFileID, UCHAR ucFileType, ULONG ulFileLen);
typedef HRESULT (WINAPI *RC_DELETEFILE)(ULONG DogHandle, USHORT usDirID, USHORT usFileID);
typedef HRESULT (WINAPI *RC_CREATEDIR)(ULONG DogHandle, USHORT usDirID, ULONG ulSize);
typedef HRESULT (WINAPI *RC_DELETEDIR)(ULONG DogHandle, USHORT usDirID);
typedef HRESULT (WINAPI *RC_DEFRAGFILESYSTEM)(ULONG DogHandle, USHORT usDirID);
typedef HRESULT (WINAPI *RC_READFILE)(ULONG DogHandle, USHORT usDirID, USHORT usFileID, ULONG ulPos, ULONG ulLen, UCHAR * pucbuf);
typedef HRESULT (WINAPI *RC_GETUPGRADEREQUESTSTRING)(ULONG DogHandle, UCHAR * pucBuf, ULONG * pulLen);	
typedef HRESULT (WINAPI *RC_GETLICENSEINFO)(ULONG DogHandle, USHORT usDirID, USHORT usFileID, USHORT * pusLimit, ULONG * pulCount, ULONG * pulRuntime,  USHORT * pusBeginYear, UCHAR * pucBeginMonth, UCHAR * pucBeginDay, UCHAR * pucBeginHour, UCHAR * pucBeginMinute, UCHAR * pucBeginSecond, USHORT * pusEndYear, UCHAR * pucEndMonth, UCHAR * pucEndDay, UCHAR * pucEndHour, UCHAR * pucEndMinute, UCHAR * pucEndSecond);

