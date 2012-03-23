
extern "C"
{


//des slgorythm.
__int16 __stdcall   IC_Encrypt( char *key,char *ptrSource, unsigned __int16 msgLen, char *ptrDest);
__int16 __stdcall   IC_Decrypt( char *key,char *ptrSource, unsigned __int16 msgLen, char *ptrDest);
__int16 __stdcall   IC_Encrypt_Hex( char *key,char *ptrSource, unsigned __int16 msgLen, char *ptrDest);
__int16 __stdcall   IC_Decrypt_Hex( char *key,char *ptrSource, unsigned __int16 msgLen, char *ptrDest);
__int16 __stdcall   IC_Encrypt_Neu( char *key,char *ptrSource, unsigned __int16 msgLen, char *ptrDest);
__int16 __stdcall   IC_Decrypt_Neu( char *key,char *ptrSource, unsigned __int16 msgLen, char *ptrDest);
__int16 __stdcall   IC_Status_1(HANDLE idComDev);
//
HANDLE   __stdcall  IC_InitComm(__int16 port);
HANDLE   __stdcall  IC_InitCommAdvanced(__int16 port);
__int16  __stdcall  IC_ExitComm(HANDLE idComDev);
__int16  __stdcall  IC_Status(HANDLE idComDev);
__int16  __stdcall  IC_Down(HANDLE idComDev);

__int16 IC_Reset(HANDLE idComDev);

__int16  __stdcall  IC_ReadVer(HANDLE idComDev,unsigned char *Ver);
__int16  __stdcall  IC_DevBeep(HANDLE idComDev,unsigned char beeptime);
__int16  __stdcall  IC_Beep(HANDLE idComDev,unsigned char delaytime,unsigned char beeptime);
__int16 __stdcall   IC_ReadDevice(HANDLE idComDev,__int16 offset,__int16 len,unsigned char * databuffer);
__int16 __stdcall   IC_WriteDevice(HANDLE idComDev,__int16 offset,__int16 len,unsigned char * writebuffer);
__int16 __stdcall   IC_ReadDevice_Hex(HANDLE idComDev,__int16 offset,__int16 len,unsigned char * databuffer);
__int16 __stdcall   IC_WriteDevice_Hex(HANDLE idComDev,__int16 offset,__int16 len,unsigned char * writebuffer);

//
__int16  __stdcall  IC_CpuApduSourceEXT(HANDLE idComDev, __int16 slen, unsigned char * sendbuffer, __int16 *rlen, unsigned char * databuffer);
__int16  __stdcall  IC_CpuApduSourceEXT_Hex(HANDLE idComDev, __int16 slen, unsigned char * sendbuffer, __int16 *rlen, unsigned char * databuffer);
__int16  __stdcall  IC_CpuApduEXT(HANDLE idComDev,__int16 slen,unsigned char * sendbuffer,__int16 *rlen,unsigned char * databuffer);
__int16  __stdcall  IC_CpuApduEXT_Hex(HANDLE idComDev,__int16 slen,unsigned char * sendbuffer,__int16 *rlen,unsigned char * databuffer);

__int16  __stdcall  IC_CpuReset(HANDLE idComDev,unsigned char *rlen, unsigned char *databuffer);
__int16  __stdcall  IC_CpuApdu(HANDLE idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer);
__int16  __stdcall  IC_CpuApduSource(HANDLE idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer);
__int16  __stdcall  IC_CpuReset_Hex(HANDLE idComDev,unsigned char *rlen, unsigned char *databuffer);
__int16  __stdcall  IC_CpuApdu_Hex(HANDLE idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer);
__int16  __stdcall  IC_CpuApduSource_Hex(HANDLE idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer);
__int16  __stdcall  IC_CpuGetProtocol(HANDLE idComDev);
__int16  __stdcall  IC_CpuApduRespon(HANDLE idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer);
__int16  __stdcall  IC_CpuSetProtocol(HANDLE idComDev,unsigned char cardp);


//
__int16  __stdcall  IC_Pushout(HANDLE idComDev);
__int16  __stdcall  IC_InitType (HANDLE idComDev,__int16 type);
__int16  __stdcall  IC_Read(HANDLE idComDev,__int16 offset,__int16 len,unsigned char * databuffer);
__int16  __stdcall  IC_Read_Float(HANDLE idComDev,__int16 offset,float *fdata);
__int16  __stdcall  IC_Read_Int(HANDLE idComDev,__int16 offset,long *fdata);
__int16  __stdcall  IC_Write_Int(HANDLE idComDev,__int16 offset,long fdata);
__int16  __stdcall  IC_ReadProtection(HANDLE idComDev,__int16 offset,__int16 len,unsigned char* protbuffer);
__int16  __stdcall  IC_ReadProtection_Hex(HANDLE idComDev,__int16 offset,__int16 len,unsigned char* protbuffer);
__int16  __stdcall  IC_ReadWithProtection(HANDLE idComDev,__int16 offset,__int16 len,unsigned char* protbuffer);
__int16  __stdcall  IC_ReadWithProtection_Hex(HANDLE idComDev,__int16 offset,__int16 len,unsigned char* protbuffer);
__int16  __stdcall  IC_Write(HANDLE idComDev,__int16 offset,__int16 len,unsigned char *writebuffer);
__int16  __stdcall  IC_Write_Float(HANDLE idComDev,__int16 offset,float fdata);
__int16  __stdcall  IC_WriteProtection(HANDLE idComDev,__int16 offset,__int16 len,unsigned char *protbuffer);
__int16  __stdcall  IC_WriteWithProtection(HANDLE idComDev,__int16 offset,__int16 len,unsigned char *writebuffer);
__int16  __stdcall  IC_WriteProtection_Hex(HANDLE idComDev,__int16 offset,__int16 len,unsigned char *protbuffer);
__int16  __stdcall  IC_WriteWithProtection_Hex(HANDLE idComDev,__int16 offset,__int16 len,unsigned char * writebuffer);

__int16 __stdcall   IC_ReadPass_SLE4442(HANDLE idComDev,unsigned char*password);
__int16  __stdcall  IC_ReadCount_SLE4442(HANDLE idComDev);
__int16  __stdcall  IC_CheckPass_SLE4442(HANDLE idComDev,unsigned char* password);
__int16  __stdcall  IC_ChangePass_SLE4442(HANDLE idComDev,unsigned char*password);
//
__int16  __stdcall  IC_CheckPass_4442hex(HANDLE idComDev,unsigned char*password);
__int16  __stdcall  IC_ChangePass_4442hex(HANDLE idComDev,unsigned char*password);
__int16 __stdcall   IC_ReadPass_4442hex(HANDLE idComDev,unsigned char*password);
//
__int16  __stdcall  IC_ReadCount_SLE4428(HANDLE idComDev);
__int16  __stdcall  IC_CheckPass_SLE4428(HANDLE idComDev,unsigned char* password);
__int16  __stdcall  IC_ChangePass_SLE4428(HANDLE idComDev,unsigned char* password);
//
__int16  __stdcall  IC_CheckPass_4428hex(HANDLE idComDev,unsigned char* password);
__int16  __stdcall  IC_ChangePass_4428hex(HANDLE idComDev,unsigned char* password);
//
__int16  __stdcall  IC_Erase(HANDLE idComDev,__int16 offset,__int16 len);
__int16  __stdcall  IC_Erase_102(HANDLE idComDev,__int16 offset,__int16 len);
__int16  __stdcall  IC_Fuse_102(HANDLE idComDev);
__int16  __stdcall  IC_ReadCount_102(HANDLE idComDev);

__int16  __stdcall  IC_CheckPass_102(HANDLE idComDev,unsigned char*password);
__int16  __stdcall  IC_ChangePass_102(HANDLE idComDev,unsigned char*password);
__int16  __stdcall  IC_CheckAZPass_102(HANDLE idComDev,__int16 zone, unsigned char*password);
__int16  __stdcall  IC_ChangeAZPass_102(HANDLE idComDev,__int16 zone,unsigned char*password);
//
__int16  __stdcall  IC_CheckPass_102hex(HANDLE idComDev,unsigned char*password);
__int16  __stdcall  IC_ChangePass_102hex(HANDLE idComDev,unsigned char*password);
__int16  __stdcall  IC_CheckAZPass_102hex(HANDLE idComDev,__int16 zone, unsigned char*password);
__int16  __stdcall  IC_ChangeAZPass_102hex(HANDLE idComDev,__int16 zone,unsigned char*password);

__int16  __stdcall  IC_Fuse_1604(HANDLE idComDev);
__int16  __stdcall  IC_ReadCount_1604(HANDLE idComDev,__int16 area);
__int16  __stdcall  IC_CheckPass_1604(HANDLE idComDev,__int16 area,unsigned char*password);
__int16  __stdcall  IC_ChangePass_1604(HANDLE idComDev,__int16 area,unsigned char*password);
//
__int16  __stdcall  IC_CheckPass_1604hex(HANDLE idComDev,__int16 area,unsigned char*password);
__int16  __stdcall  IC_ChangePass_1604hex(HANDLE idComDev,__int16 area,unsigned char*password);
//4404
__int16  __stdcall  IC_Fuse_4404(HANDLE icdev);
__int16  __stdcall  IC_ReadCount_4404(HANDLE icdev);
__int16  __stdcall  IC_CheckPass_4404(HANDLE idComDev,unsigned char *password);
__int16  __stdcall  IC_ChangePass_4404(HANDLE idComDev,unsigned char *password);
__int16  __stdcall  IC_CheckAZPass_4404(HANDLE idComDev,unsigned char *password);
__int16  __stdcall  IC_ChangeAZPass_4404(HANDLE idComDev,unsigned char*password);
__int16  __stdcall  IC_CheckPass_4404hex(HANDLE idComDev,unsigned char *password);
__int16  __stdcall  IC_ChangePass_4404hex(HANDLE idComDev,unsigned char *password);
__int16  __stdcall  IC_CheckAZPass_4404hex(HANDLE idComDev,unsigned char *password);
__int16  __stdcall  IC_ChangeAZPass_4404hex(HANDLE idComDev,unsigned char*password);

//4406
__int16  __stdcall  IC_RValue(HANDLE idComDev);
__int16  __stdcall  IC_DEValue(HANDLE idComDev,__int16 num);
__int16  __stdcall  IC_Fuse_4406(HANDLE icdev, __int16 value);
__int16  __stdcall  IC_ReadCount_4406(HANDLE icdev);
__int16  __stdcall  IC_CheckPass_4406(HANDLE idComDev,unsigned char *password);

__int16  __stdcall  IC_Erase_4406(HANDLE idComDev,unsigned char offset);
__int16  __stdcall  IC_CheckPass_4406hex(HANDLE idComDev,unsigned char *password);
__int16  __stdcall  IC_CheckPass_4406userhex(HANDLE idComDev,unsigned char *password);
__int16  __stdcall  IC_CheckPass_4406user(HANDLE idComDev,unsigned char *password);

//
__int16  __stdcall  IC_Write24(HANDLE idComDev,__int16 offset,__int16 len,unsigned char *writebuffer);
__int16  __stdcall  IC_Write64(HANDLE idComDev,__int16 offset,__int16 len,unsigned char *writebuffer);
//hex read and write.
__int16  __stdcall  IC_Write_Hex(HANDLE idComDev,__int16 offset,__int16 len,unsigned char *writebuffer);
__int16  __stdcall  IC_Read_Hex(HANDLE idComDev,__int16 offset,__int16 len,unsigned char * databuffer);
__int16  __stdcall  IC_Write24_Hex(HANDLE idComDev,__int16 offset,__int16 len,unsigned char *writebuffer);
__int16  __stdcall  IC_Write64_Hex(HANDLE idComDev,__int16 offset,__int16 len,unsigned char *writebuffer);
//
__int16 __stdcall IC_DirectRead(HANDLE idComDev,__int16 page,__int16 offset,__int16 bytes,unsigned char *buff);
__int16 __stdcall IC_WriteByBuffer(HANDLE idComDev,__int16 page,__int16 offset,__int16 bytes,unsigned char *buff);
__int16 __stdcall IC_DirectWrite(HANDLE idComDev,__int16 page,__int16 offset,__int16 bytes,unsigned char *buff);
//
__int16 __stdcall IC_DirectRead_Hex(HANDLE idComDev,__int16 page,__int16 offset,__int16 bytes,unsigned char *buff);
__int16 __stdcall IC_DirectWrite_Hex(HANDLE idComDev,__int16 page,__int16 offset,__int16 bytes,unsigned char *writebuffer);
__int16 __stdcall IC_WriteBybuffer_Hex(HANDLE idComDev,__int16 page,__int16 offset,__int16 bytes,unsigned char *writebuffer);
//
__int16  __stdcall IC_Fuse_1604B(HANDLE idComDev);
__int16  __stdcall IC_ReadCount_1604B(HANDLE idComDev,__int16 area);
__int16  __stdcall IC_ChangePass_1604B(HANDLE idComDev,__int16 area,unsigned char*password);
__int16  __stdcall IC_CheckPass_1604B(HANDLE idComDev,__int16 area,unsigned char*password);
__int16  __stdcall IC_ChangePass_1604Bhex(HANDLE idComDev,__int16 area,unsigned char*password);
__int16  __stdcall IC_CheckPass_1604Bhex(HANDLE idComDev,__int16 area,unsigned char*password);
//
__int16 __stdcall IC_Read_1101(HANDLE idComDev,__int16 page,__int16 offset,__int16 bytes,unsigned char *buff);
__int16 __stdcall IC_Write_1101(HANDLE idComDev,__int16 page,__int16 offset,__int16 bytes,unsigned char *buff);
__int16 __stdcall IC_Read_1101hex(HANDLE idComDev,__int16 page,__int16 offset,__int16 bytes,unsigned char *buff);
__int16 __stdcall IC_Write_1101hex(HANDLE idComDev,__int16 page,__int16 offset,__int16 bytes,unsigned char *buff);

__int16  __stdcall  IC_GotoUpdate (HANDLE idComDev);       //for download function
//AT88SC1608 卡的专用函数

__int16  __stdcall IC_InitAuth_Hex(HANDLE idComDev,unsigned char *Q0);
__int16  __stdcall IC_CheckAuth_Hex(HANDLE idComDev,unsigned char *Q1);
__int16  __stdcall IC_InitAuth(HANDLE idComDev,unsigned char *Q0);
__int16  __stdcall IC_CheckAuth(HANDLE idComDev,unsigned char *Q1);
__int16  __stdcall IC_CheckRPassword_Hex(HANDLE idComDev,unsigned char zone,unsigned char *Pin);
__int16  __stdcall IC_CheckWPassword_Hex(HANDLE idComDev,unsigned char zone,unsigned char *Pin);
__int16  __stdcall IC_CheckRPassword(HANDLE idComDev,unsigned char zone,unsigned char *Pin);
__int16  __stdcall IC_CheckWPassword(HANDLE idComDev,unsigned char zone,unsigned char *Pin);
__int16  __stdcall IC_ChangeRPassword(HANDLE idComDev,unsigned char zone,unsigned char *Pin);
__int16  __stdcall IC_ChangeWPassword(HANDLE idComDev,unsigned char zone,unsigned char *Pin);
__int16  __stdcall IC_ChangeRPassword_Hex(HANDLE idComDev,unsigned char zone,unsigned char *Pin);
__int16  __stdcall IC_ChangeWPassword_Hex(HANDLE idComDev,unsigned char zone,unsigned char *Pin);
__int16  __stdcall IC_WriteFuse(HANDLE idComDev,unsigned char fusetype);
__int16  __stdcall IC_ReadFuse(HANDLE idComDev);
__int16  __stdcall IC_WriteConfigZone(HANDLE idComDev,__int16 Offset,__int16 len,unsigned char *WDataBuff);
__int16  __stdcall IC_WriteUserZone(HANDLE idComDev,__int16 Offset,__int16 len,unsigned char *WDataBuff);
__int16  __stdcall IC_ReadConfigZone(HANDLE idComDev,__int16 Offset,__int16 len,unsigned char *RDataBuff);
__int16  __stdcall IC_ReadUserZone(HANDLE idComDev,__int16 Offset,__int16 len,unsigned char *RDataBuff);
__int16 __stdcall  IC_ReadWPasswordCount(HANDLE idComDev,unsigned char zone);
__int16 __stdcall  IC_ReadRPasswordCount(HANDLE idComDev,unsigned char zone);

__int16 __stdcall IC_ReadAuthCount(HANDLE idComDev);
__int16 __stdcall IC_WriteConfigZone_Hex(HANDLE idComDev,__int16 Offset,__int16 len,unsigned char *WDataBuff);
__int16 __stdcall IC_WriteUserZone_Hex(HANDLE idComDev,__int16 Offset,__int16 len,unsigned char *WDataBuff);
__int16 __stdcall IC_ReadConfigZone_Hex(HANDLE idComDev,__int16 Offset,__int16 len,unsigned char *RDataBuff);
__int16 __stdcall IC_ReadUserZone_Hex(HANDLE idComDev,__int16 Offset,__int16 len,unsigned char *RDataBuff);

__int16 __stdcall IC_SetUserZone(HANDLE idComDev,unsigned char Zone);


//AT88SC1608的专用算法程序，资料中介绍为F2算法。
__int16 __stdcall SetInit(unsigned char *Ci, unsigned char *Gc,unsigned char *Q0);
__int16 __stdcall Authenticate(unsigned char *Q1,unsigned char *Q2);
//可以使用16进制的数据传输
__int16 __stdcall SetInit_Hex(unsigned char *Ci, unsigned char *Gc,unsigned char *Q0);
__int16 __stdcall Authenticate_Hex(unsigned char *Q1,unsigned char *Q2);

/*
认证的使用过程：
	1。产生Q0为一个随机数。
	2。使用IC_InitAuth（Q0）将Q0送入卡中。
	3。从卡中读出Ci用于下一步的密钥初始化。
	4。使用SetInit(Ci，Gc，Q0),其中Gc为用户密钥，由用于掌握，必须和卡中的Gc相同，Q0在第一步中已经产生。
	5。使用Authenticate（Q1，Q2）产生Q1，Q2，用于下一步的认证过程
	6。使用IC_CheckAuth（Q1）将Q1送入卡中认证。
	7。从卡中读出Ci和Q2比较，如果相同则认证通过。

    注意：在此过程中Gc为用户已知密钥
*/
//2个工具函数，用于字符串格式的转换
__int16 __stdcall   hex2asc(unsigned char *strhex,unsigned char *strasc,__int16 length);
__int16 __stdcall   asc2hex(unsigned char *strasc,unsigned char *strhex,__int16 length);

__int16  __stdcall  SendData(HANDLE idComDev,__int16 len,unsigned char * databuffer);
__int16  __stdcall  ReceiveData(HANDLE idComDev,__int16 len,unsigned char *databuffer);


unsigned __int16 __stdcall ICC_Internal_Auth(HANDLE idComDev,unsigned char kid,unsigned char *randifd,unsigned char retlen,unsigned char *encrand);
unsigned __int16 __stdcall ICC_External_Auth(HANDLE idComDev,unsigned char kid,unsigned char *encrand);
unsigned __int16 __stdcall ICC_Verify(HANDLE idComDev,unsigned char kid,unsigned char pin_len,unsigned char *pin);
unsigned __int16 __stdcall ICC_Write_Bin(HANDLE idComDev,unsigned __int16 offset,unsigned __int16 len,unsigned char *data);
unsigned __int16 __stdcall ICC_Read_Bin(HANDLE idComDev,unsigned __int16 offset,unsigned __int16 len,unsigned char *resp);
unsigned __int16 __stdcall ICC_Select_File(HANDLE idComDev,unsigned char sflag,unsigned __int16 fid);
unsigned __int16 __stdcall ICC_Get_Challenge(HANDLE idComDev,unsigned char len,unsigned char *rand);

__int16 __stdcall IC_ReadUsbSnr(HANDLE idComDev,unsigned char *snrdata);

//BOOL __stdcall RegisterCallback(LPRD102_CALLBACK_FUNC lpfnCallback);
__int16  __stdcall  IC_Control(HANDLE idComDev,unsigned char ctype,unsigned char delaytime);



__int16  __stdcall  IC_CheckCard(HANDLE idComDev);

__int16  __stdcall  IC_Check_4442(HANDLE idComDev);
__int16  __stdcall  IC_Check_4428(HANDLE idComDev);
__int16  __stdcall  IC_Check_102(HANDLE idComDev);
__int16  __stdcall  IC_Check_1604(HANDLE idComDev);
__int16  __stdcall  IC_Check_1604B(HANDLE idComDev);
__int16  __stdcall  IC_Check_24C01(HANDLE idComDev);
__int16  __stdcall  IC_Check_24C02(HANDLE idComDev);
__int16  __stdcall  IC_Check_24C04(HANDLE idComDev);
__int16  __stdcall  IC_Check_24C08(HANDLE idComDev);
__int16  __stdcall  IC_Check_24C16(HANDLE idComDev);
__int16  __stdcall  IC_Check_24C64(HANDLE idComDev);
__int16  __stdcall  IC_Check_45DB041(HANDLE idComDev);
__int16  __stdcall  IC_Check_1101(HANDLE idComDev);
__int16  __stdcall  IC_Check_CPU(HANDLE idComDev);
__int16  __stdcall  IC_Check_153(HANDLE idComDev);
__int16  __stdcall  IC_Check_1608(HANDLE idComDev);
__int16  __stdcall  IC_Check_4404(HANDLE idComDev);
__int16  __stdcall  IC_Check_4406(HANDLE idComDev);

HANDLE __stdcall IC_InitComm_Baud(__int16 port,unsigned long combaud);
__int16 __stdcall IC_SetCommTimeout(DWORD lTime_ms,DWORD sTime_ms);
__int16  __stdcall  IC_Write_102(HANDLE idComDev,__int16 offset,__int16 len,unsigned char *writebuffer);
__int16  __stdcall  IC_Write_102hex(HANDLE idComDev,__int16 offset,__int16 len,unsigned char *writebuffer);
__int16  __stdcall  IC_Write_1604(HANDLE idComDev,__int16 offset,__int16 len,unsigned char *writebuffer);
__int16  __stdcall  IC_Write_1604hex(HANDLE idComDev,__int16 offset,__int16 len,unsigned char *writebuffer);
HANDLE __stdcall IC_InitComm_Q(__int16 port,unsigned long combaud);
__int16  __stdcall  IC_SetCpuPara(HANDLE idComDev,unsigned char cputype,unsigned char cpupro,unsigned char cpuetu);
__int16  __stdcall  IC_CpuColdReset(HANDLE idComDev,unsigned char *rlen, unsigned char *databuffer);
__int16  __stdcall  IC_CpuColdReset_Hex(HANDLE idComDev,unsigned char *rlen, unsigned char *databuffer);
__int16  __stdcall  IC_CpuHotReset(HANDLE idComDev,unsigned char *rlen, unsigned char *databuffer);
__int16  __stdcall  IC_CpuHotReset_Hex(HANDLE idComDev,unsigned char *rlen, unsigned char *databuffer);

__int16  __stdcall  IC_SwitchPcsc(HANDLE idComDev,unsigned char flag);

}