#include "stdafx.h"
#include "D6touch.h"
#include <iostream>
using namespace std;



D6touch::D6touch()
{
	//hinstLib=NULL;
	// initDll();
	// my_ic_initcomm=NULL;
	// my_ic_status=NULL;  
	// my_ic_inittype=NULL;  
	// my_ic_exitcomm=NULL;
	// my_ic_checkcpu=NULL;

	// my_ic_setcpupara=NULL;
	// my_dc_setcpu=NULL;
	// my_dc_cpureset=NULL;
	// my_dc_cpuapdusource=NULL;
	// my_dc_cpuapdu=NULL;
	// my_dc_resethex=NULL;
	// my_dc_cpuapdusourcehex=NULL;
	// my_dc_cpuapduhex=NULL;
	// my_dc_cpuapdurespon=NULL;
	// my_dc_cpuapduresponhex=NULL;
	// my_dc_cpudown=NULL;
	//if(hinstLib != NULL){


	//	my_ic_initcomm = (myICInitComm)GetProcAddress(hinstLib, "IC_InitComm");
	//	my_ic_status = (myICStatus)GetProcAddress(hinstLib, "IC_Status");  
	//	my_ic_inittype = (myICInitType)GetProcAddress(hinstLib, "IC_InitType"); 
	//	my_ic_exitcomm = (myICExitComm)GetProcAddress(hinstLib, "IC_ExitComm"); 
	//	my_ic_checkcpu = (myICCheckCPU)GetProcAddress(hinstLib, "IC_Check_CPU"); 

	//	my_dc_setcpu = NULL;
	//	my_dc_cpureset = (myDcCupReset)GetProcAddress(hinstLib, "IC_CpuReset");
	//	my_dc_cpuapdusource = (myDcCpuApduSource)GetProcAddress(hinstLib, "IC_CpuApduSource");
	//	my_dc_cpuapdu = (myDcCpuApdu)GetProcAddress(hinstLib, "IC_CpuApdu");
	//	my_dc_resethex = (myDcReset_hex)GetProcAddress(hinstLib, "IC_CpuReset_Hex");
	//	my_dc_cpuapdusourcehex = (myDcCpuApduSource_hex)GetProcAddress(hinstLib, "IC_CpuApduSource_Hex");
	//	my_dc_cpuapduhex = (myDcCpuApdu_hex)GetProcAddress(hinstLib, "IC_CpuApdu_Hex");
	//	my_dc_cpuapdurespon = (myDcCpuApduRespon)GetProcAddress(hinstLib, "IC_CpuApduRespon");
	//	//my_dc_cpuapduresponhex = (myDcCpuApduRespon_hex)GetProcAddress(hinstLib, "IC_CpuApduSource");
	//	my_dc_cpuapduresponhex = NULL;
	//	my_dc_cpudown = NULL;
	//	my_ic_setcpupara = (myICSetCpuPara)GetProcAddress(hinstLib,"IC_SetCpuPara");
	//}
}



bool D6touch::initDll(){
	hinstLib = LoadLibrary("dcic32.dll"); 
	if (hinstLib != NULL) {
		return false;
	}
	return true;
}

D6touch::~D6touch(void)
{
	/*if (m_isClose >=0)
	{
	my_ic_exitcomm(m_commHandle);
	}*/
}

HANDLE  D6touch::dc_init6(__int16 port)
{
	/*m_commHandle =  my_ic_initcomm(port);
	return m_commHandle;*/
	m_commHandle = NULL;
	m_commHandle = IC_InitComm(port);
	if ((int)m_commHandle <= 0)
	{
     
		m_commHandle = IC_InitCommAdvanced(port);
		
	}
	return m_commHandle;

}

__int16 D6touch::dc_checkcpu6(HANDLE ICDev)
{

	/*return my_ic_checkcpu(ICDev);*/
	return IC_Check_CPU(ICDev);

}

__int16 D6touch::dc_InitType6(HANDLE ICDev,__int16 TypeNo)
{
	//return  my_ic_inittype(ICDev,TypeNo);
	return  IC_InitType(ICDev,TypeNo);
}


__int16 D6touch::dc_Status6(HANDLE ICDev)
{
	//return my_ic_status(ICDev);
	return IC_Status(ICDev);
}


bool D6touch::Exit()
{

	//闭串行口，在Windows系统中，同时只能有一个设备使用串行口， 
	//所以在退出系统时，请关闭串行口，以便于其它设备使用。
	//m_isClose = my_ic_exitcomm(m_commHandle);
	m_isClose = IC_ExitComm(m_commHandle);
	if(m_isClose < 0  )
	{
		return false;
	}
	else
	{
		return true;
	}
}

__int16 __stdcall  D6touch::dc_setcpu6(HANDLE icdev,unsigned char _Byte)
{
	return 0;
}

__int16 __stdcall  D6touch::dc_cpureset6(HANDLE icdev,unsigned char *rlen,unsigned char *databuffer)
{
	//return my_dc_cpureset(icdev,rlen,databuffer);
	return IC_CpuReset(icdev,rlen,databuffer);
}

__int16 __stdcall D6touch::dc_cpuapdusource6(HANDLE icdev,unsigned char slen,unsigned char * sendbuffer,
											 unsigned char *rlen,unsigned char * databuffer)
{
	/*return my_dc_cpuapdusource(icdev,slen,sendbuffer,rlen,databuffer);*/
	return IC_CpuApduSource(icdev,slen,sendbuffer,rlen,databuffer);
}

__int16 __stdcall D6touch::dc_cpuapdu6(HANDLE icdev,unsigned char slen,unsigned char * sendbuffer,
									   unsigned char *rlen,unsigned char * databuffer)
{
	//return my_dc_cpuapdu(icdev,slen,sendbuffer,rlen,databuffer);
	return IC_CpuApdu(icdev,slen,sendbuffer,rlen,databuffer);
}

__int16 __stdcall  D6touch::dc_cpuapdurespon6(HANDLE idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer)
{
	/*return my_dc_cpuapdurespon(idComDev,slen,sendbuffer,rlen,databuffer);*/
	return IC_CpuApduRespon(idComDev,slen,sendbuffer,rlen,databuffer);
}
__int16 __stdcall  D6touch::dc_cpuapdurespon_hex6(HANDLE idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer)
{

	return 0;; 

}

__int16  __stdcall D6touch::dc_cpuapdu_hex6(HANDLE icdev,unsigned char slen, char * sendbuffer,
											unsigned char *rlen, char * databuffer)
{
	//return my_dc_cpuapduhex(icdev,slen,sendbuffer,rlen,databuffer);
	return IC_CpuApdu_Hex(icdev,slen,(unsigned char *)sendbuffer,rlen,(unsigned char *)databuffer);
}

__int16 __stdcall  D6touch::dc_cpureset_hex6(HANDLE icdev,unsigned char *rlen, char *databuffer)
{

	//return my_dc_resethex(icdev,rlen,databuffer);
	return IC_CpuReset_Hex(icdev,rlen,(unsigned char *)databuffer);

}
//66
__int16  __stdcall D6touch::dc_cpuapdusource_hex6(HANDLE icdev,unsigned char slen, char * sendbuffer,
												  unsigned char *rlen, char * databuffer)
{
	//	return my_dc_cpuapdusourcehex(icdev,slen,sendbuffer,rlen,databuffer);
	return IC_CpuApduSource_Hex(icdev,slen,(unsigned char *)sendbuffer,rlen,(unsigned char *)databuffer);

}

__int16 __stdcall  D6touch::dc_cpudown6(HANDLE icdev)
{

	return 0;
}

__int16 __stdcall D6touch::dc_setcpupara6(HANDLE idComDev,unsigned char cputype,unsigned char cpupro,unsigned char cpuetu)
{
	//return my_ic_setcpupara(idComDev,cputype,cpupro,cpuetu);
	return  IC_SetCpuPara(idComDev,cputype,cpupro,cpuetu);
}


__int16  __stdcall  D6touch::dc_cpuapdusourceEXT6(HANDLE idComDev, __int16 slen, unsigned char * sendbuffer, __int16 *rlen, unsigned char * databuffer)
{
	return IC_CpuApduSourceEXT( idComDev, slen, sendbuffer, rlen,  databuffer);
}
__int16  __stdcall  D6touch::dc_cpuapdusourceEXT_hex6(HANDLE idComDev, __int16 slen,  char * sendbuffer, __int16 *rlen,  char * databuffer)
{
	return IC_CpuApduSourceEXT_Hex( idComDev,  slen, (unsigned char *)sendbuffer, rlen, (unsigned char *)databuffer);
}
__int16  __stdcall  D6touch::dc_cpuapduEXT6(HANDLE idComDev,__int16 slen,unsigned char * sendbuffer,__int16 *rlen,unsigned char * databuffer)
{
	return IC_CpuApduEXT( idComDev, slen,sendbuffer,rlen, databuffer);
}
__int16  __stdcall  D6touch::dc_cpuapduEXT_hex6(HANDLE idComDev,__int16 slen, char * sendbuffer,__int16 *rlen, char * databuffer)
{
	return IC_CpuApduEXT_Hex( idComDev,slen, (unsigned char * )sendbuffer,rlen,(unsigned char * ) databuffer);
}


__int16  __stdcall  D6touch::IC_Down6(HANDLE idComDev)
{
	return IC_Down(idComDev);
}