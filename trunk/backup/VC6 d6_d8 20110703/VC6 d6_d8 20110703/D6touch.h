#pragma once
#include "dcic32.h"
#include <windows.h> 
#include <stdio.h> 
#pragma comment(lib,"dcic32.lib")
class D6touch
{
public:
	D6touch();
	~D6touch(void);
    HANDLE  dc_init6(__int16 port);	//初始化端口	
    __int16 dc_checkcpu6(HANDLE ICDev);
    __int16 dc_InitType6(HANDLE ICDev,__int16 TypeNo = 0x0c);
    __int16 dc_Status6(HANDLE ICDev);
	bool Exit();
	bool initDll();
	bool freeDll(); 
    
	__int16 __stdcall  dc_setcpu6(HANDLE icdev,unsigned char _Byte);
	__int16 __stdcall  dc_cpureset6(HANDLE icdev,unsigned char *rlen,unsigned char *databuffer);
	__int16 __stdcall  dc_cpuapdusource6(HANDLE icdev,unsigned char slen,unsigned char * sendbuffer,
		unsigned char *rlen,unsigned char * databuffer);

	__int16 __stdcall  dc_cpuapdu6(HANDLE icdev,unsigned char slen,unsigned char * sendbuffer,
		unsigned char *rlen,unsigned char * databuffer);

	__int16 __stdcall  dc_cpuapdurespon6(HANDLE idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer);
	
	__int16 __stdcall  dc_cpudown6(HANDLE icdev);
    __int16 __stdcall  dc_setcpupara6(HANDLE idComDev,unsigned char cputype,unsigned char cpupro,unsigned char cpuetu);

//hex
	__int16 __stdcall  dc_cpuapdusource_hex6(HANDLE icdev,unsigned char slen, char * sendbuffer,
		unsigned char *rlen, char * databuffer);
	__int16 __stdcall  dc_cpureset_hex6(HANDLE icdev,unsigned char *rlen, char *databuffer);
	__int16 __stdcall  dc_cpuapdu_hex6(HANDLE icdev,unsigned char slen, char * sendbuffer,
		unsigned char *rlen, char * databuffer);
    __int16 __stdcall  dc_cpuapdurespon_hex6(HANDLE idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer);

	//长指令
	__int16  __stdcall  dc_cpuapdusourceEXT6(HANDLE idComDev, __int16 slen, unsigned char * sendbuffer, __int16 *rlen, unsigned char * databuffer);
__int16  __stdcall  dc_cpuapdusourceEXT_hex6(HANDLE idComDev, __int16 slen,  char * sendbuffer, __int16 *rlen,  char * databuffer);
__int16  __stdcall  dc_cpuapduEXT6(HANDLE idComDev,__int16 slen,unsigned char * sendbuffer,__int16 *rlen,unsigned char * databuffer);
__int16  __stdcall  dc_cpuapduEXT_hex6(HANDLE idComDev,__int16 slen, char * sendbuffer,__int16 *rlen, char * databuffer);


__int16  __stdcall  IC_Down6(HANDLE idComDev);

	HINSTANCE hinstLib;
	//myICInitComm my_ic_initcomm;
	//myICStatus    my_ic_status;  
	//myICInitType my_ic_inittype;  
 //   myICExitComm my_ic_exitcomm;
 //   myICCheckCPU my_ic_checkcpu;

	//myICSetCpuPara my_ic_setcpupara;
	//myDcSetCpu my_dc_setcpu;
	//myDcCupReset my_dc_cpureset;
	//myDcCpuApduSource my_dc_cpuapdusource;
	//myDcCpuApdu my_dc_cpuapdu;
	//myDcReset_hex my_dc_resethex;
	//myDcCpuApduSource_hex my_dc_cpuapdusourcehex;
	//myDcCpuApdu_hex my_dc_cpuapduhex;
	//myDcCpuApduRespon my_dc_cpuapdurespon;

	//myDcCpuApduRespon_hex my_dc_cpuapduresponhex;
	//myDcCpuDown my_dc_cpudown;

	HANDLE m_commHandle;          //返回串口标识符
	__int16 m_isClose;
};


