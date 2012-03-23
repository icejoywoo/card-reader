// d6_d8.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "d6_d8.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CD6_d8App

BEGIN_MESSAGE_MAP(CD6_d8App, CWinApp)
	//{{AFX_MSG_MAP(CD6_d8App)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD6_d8App construction

CD6_d8App::CD6_d8App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// CD6_D8App 初始化
BOOL CD6_d8App::InitInstance()
{
	CWinApp::InitInstance();
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CD6_d8App object

CD6_d8App theApp;
D6touch   reader_d6;     //定义一个D6读卡器的全局变量;D6读卡器只能进行接触操作。
D8Cap     reader_d8;    //定义一个D8读卡器的全局变量;D8读卡器可以进行接触和飞接触操作。
HANDLE    handle_d6=0;  //D6读卡器的一个全局句柄。
int       flag=0;       //flag==0表示混合使用D8跟D6的动态接口，即调用接触操作时用的是D8的接口，实际调用的是D6的实现
                       //flag==1表示只使用D8，即调用接触操作时，用的是D8的接口，实际调用的也是D8的实现。
CString strPath;

//辅助函数
void __stdcall GetDllPath()
{
	char Buffer[BUFSIZE];
    DWORD dwRet;
	//dwRet=GetCurrentDirectory(BUFSIZE,Buffer);
	dwRet=GetModuleFileName(NULL,Buffer,BUFSIZE);
	if(dwRet==0||dwRet>BUFSIZE)
	{
		return;
	}
    CString strPathTemp(Buffer);
	int index;
	index=strPathTemp.ReverseFind('\\');
	strPathTemp=strPathTemp.Left(index);
	strPath=strPathTemp;
    strPath+="\\READER_SETUP.ini";
	strPath.Replace("\\","\\\\");
}

void __stdcall write(erro_info errotype, int port)
{
	CString strCom;
	strCom.Format("%d",port+1); 
	CString strError("str_err_Com");
	strError+=strCom;
    CTime t = CTime::GetCurrentTime();
    CString m_timeStr = t.Format("%Y,%B,%d,%H,%M,%S");
	CString strErrorInfo;
	switch (errotype)
	{
	case Load_D8_dll_error:
        // strErrorInfo=" 加载D8读卡器dll出错，找不到文件";
		//m_timeStr+=strErrorInfo;
		//WritePrivateProfileString("ErrorInfo",strError,m_timeStr,strPath);
		break;
	case Can_not_find_ini_file:
        strErrorInfo=" 找不到READER_SETUP.ini文件";
		m_timeStr+=strErrorInfo;
		WritePrivateProfileString("ErrorInfo",strError,m_timeStr,strPath);
		break;
	case setup_ini_file_error:
		strErrorInfo=" 配置READER_SETUP.ini文件出错";
		m_timeStr+=strErrorInfo;
		WritePrivateProfileString("ErrorInfo",strError,m_timeStr,strPath);
		break;
	}
}
//基本函数
HANDLE  __stdcall  dc_init(__int16 port,long baud)
{
	//int mode;
	//mode=GetPrivateProfileInt("ReadersConfig","Mode",68,".\\READER_SETUP.ini");
	//if(68==mode)
	//{
	//	flag=0;
	//}
	//else
	//{
	//	flag=1;
	//}
	GetDllPath();
	int ReaderKind;
	CString strUSB="USB";
    if(100==port)
	{
		ReaderKind=GetPrivateProfileInt("ReadersConfig",strUSB,0,strPath);
	} 
	else
	{
		CString ComNum;
		CString strCom="Com";
		ComNum.Format("%d",port+1);
		strCom+=ComNum;
		ReaderKind=GetPrivateProfileInt("ReadersConfig",strCom,0,strPath);
	}
	if(ReaderKind==0)
	{
		write(Can_not_find_ini_file,port);
	}
	if(6==ReaderKind)
	{
		flag=0;
		reader_d6.dc_init6(port);
		handle_d6=reader_d6.m_commHandle;
		reader_d6.dc_InitType6(handle_d6);
		reader_d6.dc_Status6(handle_d6);
		return handle_d6;
	}
	else if(8==ReaderKind)
	{
		flag=1;
		reader_d8.Initial(port);
		return reader_d8.dc_init8(port,baud);
	}
	else 
	{
		write(setup_ini_file_error,port);
		return NULL;
		
	}
	
}

__int16 __stdcall dc_card(HANDLE icdev,unsigned char _Mode,unsigned long *_Snr)
{
	
	return reader_d8.dc_card8(icdev,_Mode,_Snr);
    

}

__int16  __stdcall dc_request(HANDLE icdev,unsigned char _Mode,unsigned __int16  *TagType)
{
	return reader_d8.dc_request8(icdev,_Mode,TagType);
}

__int16  __stdcall dc_select(HANDLE icdev,unsigned long _Snr,unsigned char *_Size)
{
   return reader_d8.dc_select8(icdev,_Snr,_Size);
}

__int16  __stdcall  dc_anticoll(HANDLE icdev,unsigned char _Bcnt,unsigned long *_Snr)
{
   return reader_d8.dc_anticoll8(icdev,_Bcnt,_Snr);
}

__int16  __stdcall dc_load_key(HANDLE icdev,unsigned char _Mode,unsigned char _SecNr,unsigned char *_NKey)
{
	return reader_d8.dc_load_key8(icdev,_Mode,_SecNr,_NKey);

}

__int16  __stdcall dc_authentication(HANDLE icdev,unsigned char _Mode,unsigned char _SecNr)
{
	return reader_d8.dc_authentication8(icdev,_Mode,_SecNr);
}


__int16  __stdcall dc_authentication_2(HANDLE icdev,unsigned char _Mode,unsigned char KeyNr,unsigned char Adr)
{
	return reader_d8.dc_authentication_28(icdev,_Mode,KeyNr,Adr);

}

__int16 __stdcall dc_authentication_pass(HANDLE icdev,unsigned char _Mode,unsigned char Addr,unsigned char *passbuff) 
{
	return reader_d8.dc_authentication_pass8(icdev,_Mode,Addr,passbuff);

}

__int16 __stdcall dc_read(HANDLE icdev,unsigned char _Adr,unsigned char *_Data)
{
	return reader_d8.dc_read8(icdev,_Adr,_Data);

}

__int16 __stdcall dc_write(HANDLE icdev,unsigned char _Adr,unsigned char *_Data)
{
	return reader_d8.dc_write8(icdev,_Adr,_Data);

}

__int16 __stdcall dc_halt(HANDLE icdev)
{
	return reader_d8.dc_halt8(icdev);
}

__int16  __stdcall dc_changeb3(HANDLE icdev,unsigned char _SecNr,unsigned char *_KeyA,unsigned char _B0,unsigned char _B1,unsigned char _B2,unsigned char _B3,unsigned char _Bk,unsigned char *_KeyB)
{
	return reader_d8.dc_changeb38(icdev,_SecNr,_KeyA,_B0,_B1,_B2,_B3,_Bk,_KeyB);

}

__int16 __stdcall dc_HL_authentication(HANDLE icdev,unsigned char reqmode,unsigned long snr,unsigned char authmode,unsigned char secnr)
{
	return reader_d8.dc_HL_authentication8(icdev,reqmode,snr,authmode,secnr);

}

__int16 __stdcall dc_HL_read(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,unsigned long _Snr,unsigned char *_Data, unsigned long *_NSnr)
{
	return reader_d8.dc_HL_read8(icdev,_Mode,_Adr,_Snr,_Data,_NSnr);

}

__int16 __stdcall dc_HL_write(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,unsigned long *_Snr,unsigned char *_Data)
{
	return reader_d8.dc_HL_write8(icdev,_Mode,_Adr,_Snr,_Data);

}

__int16 __stdcall dc_check_write(HANDLE icdev,unsigned long Snr,unsigned char authmode,unsigned char Adr,unsigned char *_data)
{
	return reader_d8.dc_check_write8(icdev,Snr,authmode,Adr,_data);

}

__int16 __stdcall dc_exit(HANDLE icdev)
{
	reader_d6.Exit();
	return reader_d8.dc_exit8(icdev);

}

//带Hex函数
__int16 __stdcall dc_card_hex (HANDLE icdev,unsigned char _Mode,unsigned char *snrstr)
{
	return reader_d8.dc_card_hex8(icdev,_Mode,snrstr);
}



__int16 __stdcall dc_load_key_hex(HANDLE icdev,unsigned char _Mode,unsigned char _SecNr,char *_NKey)
{
	return reader_d8.dc_load_key_hex8(icdev,_Mode,_SecNr,_NKey);

}

__int16 __stdcall dc_authentication_pass_hex(HANDLE icdev,unsigned char _Mode,unsigned char _Addr,unsigned char *passbuff)
{
	return reader_d8.dc_authentication_pass_hex8(icdev,_Mode,_Addr,passbuff);

}


__int16 __stdcall dc_read_hex(HANDLE icdev,unsigned char _Adr,char *_Data)
{
	return reader_d8.dc_read_hex8(icdev,_Adr,_Data);
}

__int16 __stdcall dc_write_hex(HANDLE icdev,unsigned char _Adr,char *_Data)
{
	return reader_d8.dc_write_hex8(icdev,_Adr,_Data);

}

__int16 __stdcall dc_srd_eepromhex(HANDLE icdev,int offset,int length,unsigned char *rec_buffer)
{
	return reader_d8.dc_srd_eepromhex8(icdev,offset,length,rec_buffer);

}

__int16 __stdcall dc_swr_eepromhex(HANDLE icdev,int offset,int length,unsigned char* buffer)
{
	return reader_d8.dc_swr_eepromhex8(icdev,offset,length,buffer);

}

__int16 __stdcall dc_cpuapdu_hex(HANDLE icdev,unsigned char slen, char * sendbuffer,unsigned char *rlen, char * rbuff)
{
	if(flag==1)
	{
		return reader_d8.dc_cpuapdu_hex8(icdev,slen,sendbuffer,rlen,rbuff);
	}
	return reader_d6.dc_cpuapdu_hex6(handle_d6,slen,sendbuffer,rlen,rbuff);

}

__int16 __stdcall dc_cpureset_hex(HANDLE icdev,unsigned char *rlen, char *databuffer) 
{
	if(flag==1)
	{
		return reader_d8.dc_cpureset_hex8(icdev,rlen,databuffer);
	}
	return reader_d6.dc_cpureset_hex6(handle_d6,rlen,databuffer);

}

//RFMA专用
__int16 __stdcall dc_gettime(HANDLE icdev,unsigned char *time)
{
	return reader_d8.dc_gettime8(icdev,time);

}

__int16 __stdcall dc_high_disp(HANDLE icdev,unsigned char offset,unsigned char disp_len,unsigned char *disp_str)
{
	return reader_d8.dc_high_disp8(icdev,offset,disp_len,disp_str);
}

__int16 __stdcall dc_disp_mode(HANDLE icdev,unsigned char mode)
{
	return reader_d8.dc_disp_mode8(icdev,mode);
}

__int16 __stdcall dc_setbright(HANDLE icdev,unsigned char bright)
{
	return reader_d8.dc_setbright8(icdev,bright);
}

__int16 __stdcall dc_disp_str(HANDLE icdev,char *digit)
{
	return reader_d8.dc_disp_str8(icdev,digit);
}

__int16 __stdcall dc_settime(HANDLE icdev,unsigned char *time)
{
	return reader_d8.dc_settime8(icdev,time);
}

//接触式界面CPU卡相关操作
__int16 __stdcall dc_cpuapdu(HANDLE ICDev,unsigned char slen,unsigned char * sbuff,unsigned char *rlen,unsigned char * rbuff)
{
	if(flag==1)
	{
		return reader_d8.dc_cpuapdu8(ICDev,slen,sbuff,rlen,rbuff);
	}
	return reader_d6.dc_cpuapdu6(handle_d6,slen,sbuff,rlen,rbuff);
}

__int16 __stdcall dc_cpuapdusource(HANDLE ICDev,unsigned char slen,unsigned char * sbuff,unsigned char *rlen,unsigned char * rbuff)
{
	if(flag==1)
	{
		return reader_d8.dc_cpuapdusource8(ICDev,slen,sbuff,rlen,rbuff);
	}
	return reader_d6.dc_cpuapdusource6(handle_d6,slen,sbuff,rlen,rbuff);
}

__int16 __stdcall dc_cpureset(HANDLE ICDev,unsigned char *rlen, unsigned char *rbuff)
{
	if(flag==1)
	{
		return reader_d8.dc_cpureset8(ICDev,rlen,rbuff);
	}
	return reader_d6.dc_cpureset6(handle_d6,rlen,rbuff);
}

__int16 __stdcall dc_setcpu(HANDLE ICDev,unsigned char SAMID)
{
	if(flag==1)
	{
		return reader_d8.dc_setcpu8(ICDev,SAMID);
	}
	return reader_d6.dc_setcpu6(handle_d6,SAMID);
}


__int16 __stdcall dc_setcpupara(HANDLE ICDev,unsigned char cputype,unsigned char cpupro,unsigned char cpuetu)
{
	if(flag==1)
	{
		return reader_d8.dc_setcpupara8(ICDev,cputype,cpupro,cpuetu);
	}
	return reader_d6.dc_setcpupara6(handle_d6,cputype,cpupro,cpuetu);
}


//added for long instruction
__int16 __stdcall  dc_getcpupara(HANDLE icdev,unsigned char cputype,unsigned char *cpupro,unsigned char *cpuetu)
{
	if(flag==1)
	{
		return reader_d8.dc_getcpupara8(icdev,cputype,cpupro,cpuetu);
	}
	return 0;


}
__int16 __stdcall  dc_cpuapdusourceEXT(HANDLE icdev,__int16 slen,unsigned char * sendbuffer,__int16 *rlen,unsigned char * databuffer)
{
	if(flag==1)
	{
		return reader_d8.dc_cpuapdusourceEXT8(icdev,slen,sendbuffer,rlen,databuffer);
	}
	return reader_d6.dc_cpuapdusourceEXT6(handle_d6,slen,sendbuffer,rlen,databuffer);

}


__int16 __stdcall  dc_cpuapdusourceEXT_hex(HANDLE icdev,__int16 slen, char * sendbuffer,__int16 *rlen, char * databuffer)
{
	if(flag==1)
	{
		return reader_d8.dc_cpuapdusourceEXT_hex8(icdev,slen,sendbuffer,rlen,databuffer);
	}
	return reader_d6.dc_cpuapdusourceEXT_hex6(handle_d6,slen,sendbuffer,rlen,databuffer);

}


__int16 __stdcall  dc_cpuapduEXT(HANDLE icdev,__int16 slen,unsigned char * sendbuffer,__int16 *rlen,unsigned char * databuffer)
{
	if(flag==1)
	{
		return reader_d8.dc_cpuapduEXT8(icdev,slen,sendbuffer,rlen,databuffer);
	}
	return reader_d6.dc_cpuapduEXT6(handle_d6,slen,sendbuffer,rlen,databuffer);

}


__int16 __stdcall  dc_cpuapduEXT_hex(HANDLE icdev,__int16 slen,char * sendbuffer,__int16 *rlen,char * databuffer)
{
	if(1==flag)
	{
		return reader_d8.dc_cpuapduEXT_hex8(icdev,slen,sendbuffer,rlen,databuffer);
	}
	return reader_d6.dc_cpuapduEXT_hex6(handle_d6,slen,sendbuffer,rlen,databuffer);

}


__int16 __stdcall  dc_pro_commandlinkEXT(HANDLE idComDev,unsigned int slen,
										 unsigned char * sendbuffer,unsigned int *rlen,
										 unsigned char * databuffer,unsigned char timeout,
										 unsigned char FG)
{
	if(1==flag)
	{
		return reader_d8.dc_pro_commandlinkEXT8(idComDev,slen,sendbuffer,rlen,databuffer,timeout,FG);
	}
	return 0;

}


__int16 __stdcall dc_pro_reset(HANDLE icdev,unsigned char *rlen,unsigned char *receive_data)
{
	return reader_d8.dc_pro_reset8(icdev,rlen,receive_data);

}


__int16 __stdcall dc_pro_command(HANDLE idComDev,unsigned char slen,
								 unsigned char * sendbuffer,unsigned char *rlen,
								 unsigned char * databuffer,unsigned char timeout)
{
	return reader_d8.dc_pro_command8(idComDev,slen,sendbuffer,rlen,databuffer,timeout);

}



//值操作
__int16  __stdcall dc_initval(HANDLE icdev,unsigned char _Adr,unsigned long _Value)
{
	return reader_d8.dc_initval8(icdev,_Adr,_Value);

}
__int16  __stdcall dc_readval(HANDLE icdev,unsigned char _Adr,unsigned long *_Value)
{
	return reader_d8.dc_readval8(icdev,_Adr,_Value);
}
__int16  __stdcall dc_increment(HANDLE icdev,unsigned char _Adr,unsigned long _Value)
{
	return reader_d8.dc_increment8(icdev,_Adr,_Value);
}
__int16  __stdcall dc_decrement(HANDLE icdev,unsigned char _Adr,unsigned long _Value)
{
	return reader_d8.dc_decrement8(icdev,_Adr,_Value);

}
__int16  __stdcall dc_restore(HANDLE icdev,unsigned char _Adr)
{
	return reader_d8.dc_restore8(icdev,_Adr);

}
__int16  __stdcall dc_transfer(HANDLE icdev,unsigned char _Adr)
{
	return reader_d8.dc_transfer8(icdev,_Adr);

}

__int16  __stdcall dc_des_hex(unsigned char *key,unsigned char *sour,unsigned char *dest,
							  __int16 m)
{
	return reader_d8.dc_des_hex8(key,sour,dest,m);
}



//设备函数
__int16  __stdcall dc_beep(HANDLE icdev,unsigned short _Msec)
{
	return reader_d8.dc_beep8(icdev,_Msec);

}
__int16 __stdcall dc_getver(HANDLE icdev,unsigned char *sver)
{
	return reader_d8.dc_getver8(icdev,sver);

}
__int16  __stdcall dc_srd_eeprom(HANDLE icdev,__int16   offset,__int16 lenth,
								 unsigned char *rec_buffer)
{
	return reader_d8.dc_srd_eeprom8(icdev,offset,lenth,rec_buffer);

}
__int16  __stdcall dc_swr_eeprom(HANDLE icdev,__int16   offset,__int16 lenth,
								 unsigned char* send_buffer)
{
	return reader_d8.dc_swreeprom8(icdev,offset,lenth,send_buffer);

}

__int16 __stdcall a_hex(unsigned char *a,unsigned char *hex,__int16 len)
{
	return reader_d8.a_hex8(a,hex,len);

}
__int16 __stdcall hex_a(unsigned char *hex,unsigned char *a,__int16 length)
{
	return reader_d8.hex_a8(hex,a,length);

}

__int16  __stdcall dc_reset(HANDLE icdev,unsigned __int16   _Msec)
{
	return reader_d8.dc_reset8(icdev,_Msec);

}


//added in 20110512
__int16 __stdcall dc_pro_halt(HANDLE icdev)
{
	return reader_d8.dc_pro_halt8(icdev);

}

__int16  __stdcall dc_config(HANDLE icdev,unsigned char _Mode,unsigned char _Baud)
{
	return  reader_d8.dc_config8(icdev,_Mode,_Baud);

}



//added in 20110527
__int16 __stdcall dc_card_double(HANDLE icdev,unsigned char _Mode,unsigned char *_Snr)
{
	return reader_d8.dc_card_double8(icdev,_Mode,_Snr);

}

__int16 __stdcall dc_card_double_hex(HANDLE icdev,unsigned char _Mode,unsigned char *_Snr)
{
	return reader_d8.dc_card_double_hex8(icdev,_Mode,_Snr);

}


//added in 20110627

__int16  __stdcall dc_gettimehex(HANDLE icdev,char *time)
{
	return reader_d8.dc_gettimehex8(icdev,time);

}

__int16  __stdcall dc_settimehex(HANDLE icdev,char *time)
{
	return reader_d8.dc_settimehex8(icdev,time);

}



__int16 __stdcall dc_readblock(HANDLE icdev,unsigned char flags,
							   unsigned char startblock,unsigned char blocknum, 
							   unsigned char *UID, 
							   unsigned char *rlen,unsigned char *rbuffer)
{
	return reader_d8.dc_readblock8(icdev,flags,startblock,blocknum,UID,rlen,rbuffer);
}


__int16 __stdcall dc_readblock_hex(HANDLE icdev,unsigned char flags,
								   unsigned char startblock,unsigned char blocknum, 
								   unsigned char *UID, 
							   unsigned char *rlen,unsigned char *rbuffer)
{

	return reader_d8.dc_readblock_hex8(icdev,flags,startblock,blocknum,UID,rlen,rbuffer);
}


__int16 __stdcall dc_writeblock(HANDLE icdev,unsigned char flags,
								unsigned char startblock,unsigned char blocknum, 
								unsigned char *UID, 
								unsigned char wlen,unsigned char *rbuffer)
{
	return reader_d8.dc_writeblock8(icdev,flags,startblock,blocknum,UID,wlen,rbuffer);

}

__int16 __stdcall dc_writeblock_hex(HANDLE icdev,unsigned char flags,
									unsigned char startblock,unsigned char blocknum, 
									unsigned char *UID, 
								unsigned char wlen,unsigned char *rbuffer)
{
	return reader_d8.dc_writeblock_hex8(icdev,flags,startblock,blocknum,UID,wlen,rbuffer);
}


__int16 __stdcall  dc_cardAB(HANDLE icdev,unsigned char *rlen,unsigned char *rbuf,unsigned char *type)
{
	return reader_d8.dc_cardAB8(icdev,rlen,rbuf,type);
}

__int16 __stdcall dc_pro_commandsource(HANDLE idComDev,unsigned char slen,
									   unsigned char * sendbuffer,unsigned char *rlen,
									   unsigned char * databuffer,unsigned char timeout)
{
	return reader_d8.dc_pro_commandsource8(idComDev,slen,sendbuffer,rlen,databuffer,timeout);

}


__int16 __stdcall dc_pro_commandsourcehex(HANDLE idComDev,unsigned char slen, 
										  char * sendbuffer,unsigned char *rlen, 
									char * databuffer,unsigned char timeout)
{
	return reader_d8.dc_pro_commandsourcehex8(idComDev,slen,sendbuffer,rlen,databuffer,timeout);

}
/***********************************自动生成代码***added by chch 20110703****************************/
/***********************************自动生成代码***added by chch 20110703****************************/

__int16 __stdcall dc_write_TS(HANDLE icdev){
	return reader_d8.dc_write_TS8(icdev);
}
__int16 __stdcall dc_initval_ml(HANDLE icdev,unsigned __int16   _Value){
	return reader_d8.dc_initval_ml8(icdev,_Value);
}
__int16 __stdcall dc_readval_ml(HANDLE icdev,unsigned __int16   *_Value){
	return reader_d8.dc_readval_ml8(icdev,_Value);
}

__int16 __stdcall dc_anticoll2(HANDLE icdev,unsigned char _Bcnt,unsigned long *_Snr){
	return reader_d8.dc_anticoll28(icdev,_Bcnt,_Snr);
}
__int16 __stdcall dc_select2(HANDLE icdev,unsigned long _Snr,unsigned char *_Size){
	return reader_d8.dc_select28(icdev,_Snr,_Size);
}
__int16 __stdcall dc_HL_writehex(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,unsigned long *_Snr,unsigned char *_Data){
	return reader_d8.dc_HL_writehex8(icdev,_Mode,_Adr,_Snr,_Data);
}
__int16 __stdcall dc_HL_readhex(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,unsigned long _Snr,unsigned char *_Data,unsigned long *_NSnr){
	return reader_d8.dc_HL_readhex8(icdev,_Mode,_Adr,_Snr,_Data,_NSnr);
}
__int16 __stdcall dc_check_writehex(HANDLE icdev,unsigned long Snr,unsigned char authmode,unsigned char Adr,unsigned char * _data){
	return reader_d8.dc_check_writehex8(icdev,Snr,authmode,Adr,_data);
}
__int16 __stdcall dc_clr_control_bit(HANDLE icdev,unsigned char _b){
	return reader_d8.dc_clr_control_bit8(icdev,_b);
}
__int16 __stdcall dc_set_control_bit(HANDLE icdev,unsigned char _b){
	return reader_d8.dc_set_control_bit8(icdev,_b);
}

__int16 __stdcall swr_alleeprom(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char* snd_buffer){
	return reader_d8.swr_alleeprom8(icdev,offset,lenth,snd_buffer);
}
__int16 __stdcall srd_alleeprom(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char *receive_buffer){
	return reader_d8.srd_alleeprom8(icdev,offset,lenth,receive_buffer);
}
__int16 __stdcall dc_ctl_mode(HANDLE icdev,unsigned char mode){
	return reader_d8.dc_ctl_mode8(icdev,mode);
}
__int16 __stdcall dcdeshex(unsigned char *key,unsigned char *sour,unsigned char *dest,__int16 m){
	return reader_d8.dcdeshex8(key,sour,dest,m);
}
__int16 __stdcall dcdes(unsigned char *key,unsigned char *sour,unsigned char *dest,__int16 m){
	return reader_d8.dcdes8(key,sour,dest,m);
}
__int16 __stdcall dc_light(HANDLE icdev,unsigned short _OnOff){
	return reader_d8.dc_light8(icdev,_OnOff);
}


__int16 __stdcall dc_cpuapdusource_hex(HANDLE icdev,unsigned char slen, char * sendbuffer,unsigned char *rlen, char * databuffer){
	return reader_d8.dc_cpuapdusource_hex8(icdev,slen,sendbuffer,rlen,databuffer);
}
__int16 __stdcall dc_cpuapdurespon(HANDLE idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer){
	return reader_d8.dc_cpuapdurespon8(idComDev,slen,sendbuffer,rlen,databuffer);
}
__int16 __stdcall dc_cpuapdurespon_hex(HANDLE idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer){
	return reader_d8.dc_cpuapdurespon_hex8(idComDev,slen,sendbuffer,rlen,databuffer);
}
__int16 __stdcall dc_set_addr(unsigned char saddr){
	return reader_d8.dc_set_addr8(saddr);
}
HANDLE __stdcall dc_init_485(__int16 port,long baud){
	return reader_d8.dc_init_4858(port,baud);
}
__int16 __stdcall dc_changebaud_485(HANDLE icdev,long baud){
	return reader_d8.dc_changebaud_4858(icdev,baud);
}
__int16 __stdcall dc_change_addr(HANDLE icdev,unsigned char saddr){
	return reader_d8.dc_change_addr8(icdev,saddr);
}
__int16 __stdcall dc_pro_resethex(HANDLE icdev,unsigned char *rlen, char *receive_data){
	return reader_d8.dc_pro_resethex8(icdev,rlen,receive_data);
}
__int16 __stdcall dc_pro_commandhex(HANDLE idComDev,unsigned char slen,char * sendbuffer,unsigned char *rlen,char * databuffer,unsigned char timeout){
	return reader_d8.dc_pro_commandhex8(idComDev,slen,sendbuffer,rlen,databuffer,timeout);
}
__int16 __stdcall dc_request_shc1102(HANDLE icdev,unsigned char _Mode,unsigned __int16 *TagType){
	return reader_d8.dc_request_shc11028(icdev,_Mode,TagType);
}
__int16 __stdcall dc_auth_shc1102(HANDLE icdev,unsigned char *_Data){
	return reader_d8.dc_auth_shc11028(icdev,_Data);
}
__int16 __stdcall dc_read_shc1102(HANDLE icdev,unsigned char _Adr,unsigned char *_Data){
	return reader_d8.dc_read_shc11028(icdev,_Adr,_Data);
}
__int16 __stdcall dc_write_shc1102(HANDLE icdev,unsigned char _Adr,unsigned char *_Data){
	return reader_d8.dc_write_shc11028(icdev,_Adr,_Data);
}
__int16 __stdcall dc_halt_shc1102(HANDLE icdev){
	return reader_d8.dc_halt_shc11028(icdev);
}
__int16 __stdcall dc_config_card(HANDLE icdev,unsigned char cardtype){
	return reader_d8.dc_config_card8(icdev,cardtype);
}
__int16 __stdcall dc_request_b(HANDLE icdev,unsigned char _Mode,unsigned char AFI,unsigned char N,unsigned char *ATQB){
	return reader_d8.dc_request_b8(icdev,_Mode,AFI,N,ATQB);
}
__int16 __stdcall dc_slotmarker(HANDLE icdev,unsigned char N, unsigned char *ATQB){
	return reader_d8.dc_slotmarker8(icdev,N,ATQB);
}
__int16 __stdcall dc_attrib(HANDLE icdev,unsigned char *PUPI, unsigned char CID){
	return reader_d8.dc_attrib8(icdev,PUPI,CID);
}
__int16 __stdcall dc_open_door(HANDLE icdev,unsigned char cflag){
	return reader_d8.dc_open_door8(icdev,cflag);
}
__int16 __stdcall dc_open_timedoor(HANDLE icdev,unsigned __int16 utime){
	return reader_d8.dc_open_timedoor8(icdev,utime);
}
__int16 __stdcall dc_read_random(HANDLE icdev, unsigned char *data){
	return reader_d8.dc_read_random8(icdev,data);
}
__int16 __stdcall dc_write_random(HANDLE icdev,__int16 len, unsigned char *data){
	return reader_d8.dc_write_random8(icdev,len,data);
}
__int16 __stdcall dc_read_random_hex(HANDLE icdev, unsigned char *data){
	return reader_d8.dc_read_random_hex8(icdev,data);
}
__int16 __stdcall dc_write_random_hex(HANDLE icdev,__int16 len, unsigned char *data){
	return reader_d8.dc_write_random_hex8(icdev,len,data);
}
__int16 __stdcall dc_erase_random(HANDLE icdev,__int16 len){
	return reader_d8.dc_erase_random8(icdev,len);
}
__int16 __stdcall dc_mfdes_auth(HANDLE icdev,unsigned char keyno,unsigned char keylen,unsigned char *authkey,unsigned char *randAdata,unsigned char *randBdata){
	return reader_d8.dc_mfdes_auth8(icdev,keyno,keylen,authkey,randAdata,randBdata);
}
__int16 __stdcall dc_disp_neg(HANDLE icdev,char *dispstr){
	return reader_d8.dc_disp_neg8(icdev,dispstr);
}
__int16 __stdcall dc_pro_commandlink(HANDLE idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer,unsigned char timeout,unsigned char FG){
	return reader_d8.dc_pro_commandlink8(idComDev,slen,sendbuffer,rlen,databuffer,timeout,FG);
}
__int16 __stdcall dc_pro_commandlink_hex(HANDLE idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer,unsigned char timeout,unsigned char FG){
	return reader_d8.dc_pro_commandlink_hex8(idComDev,slen,sendbuffer,rlen,databuffer,timeout,FG);
}
__int16 __stdcall dc_read_idcard(HANDLE icdev,unsigned char times,unsigned char *_Data){
	return reader_d8.dc_read_idcard8(icdev,times,_Data);
}
__int16 __stdcall dc_read_idcard_hex(HANDLE icdev,unsigned char times,unsigned char *_Data){
	return reader_d8.dc_read_idcard_hex8(icdev,times,_Data);
}

__int16 __stdcall dc_command(HANDLE idComDev,unsigned char cmd,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer){
	return reader_d8.dc_command8(idComDev,cmd,slen,sendbuffer,rlen,databuffer);
}
__int16 __stdcall dc_command_hex(HANDLE idComDev,unsigned char cmd,unsigned char slen,char * sendbuffer,unsigned char *rlen,char * databuffer){
	return reader_d8.dc_command_hex8(idComDev,cmd,slen,sendbuffer,rlen,databuffer);
}
__int16 __stdcall dc_creat_mac(unsigned char KeyLen,unsigned char *Key,unsigned short DataLen,unsigned char *Data,unsigned char *InitData,unsigned char AutoFixFlag,unsigned char FixChar,unsigned char *MacData){
	return reader_d8.dc_creat_mac8(KeyLen,Key,DataLen,Data,InitData,AutoFixFlag,FixChar,MacData);
}
__int16 __stdcall dc_creat_mac_hex(unsigned char KeyLen,unsigned char *Key,unsigned short DataLen,unsigned char *Data,unsigned char *InitData,unsigned char AutoFixFlag,unsigned char FixChar,unsigned char *MacData){
	return reader_d8.dc_creat_mac_hex8(KeyLen,Key,DataLen,Data,InitData,AutoFixFlag,FixChar,MacData);
}
__int16 __stdcall dc_HL_write_hex(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,unsigned long *_Snr,unsigned char *_Data){
	return reader_d8.dc_HL_write_hex8(icdev,_Mode,_Adr,_Snr,_Data);
}
__int16 __stdcall dc_HL_read_hex(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,unsigned long _Snr,unsigned char *_Data,unsigned long *_NSnr){
	return reader_d8.dc_HL_read_hex8(icdev,_Mode,_Adr,_Snr,_Data,_NSnr);
}
__int16 __stdcall dc_check_write_hex(HANDLE icdev,unsigned long Snr,unsigned char authmode,unsigned char Adr,unsigned char * _data){
	return reader_d8.dc_check_write_hex8(icdev,Snr,authmode,Adr,_data);
}
__int16 __stdcall dc_srd_eeprom_hex(HANDLE icdev,__int16   offset,__int16   lenth,unsigned char *rec_buffer){
	return reader_d8.dc_srd_eeprom_hex8(icdev,offset,lenth,rec_buffer);
}
__int16 __stdcall dc_swr_eeprom_hex(HANDLE icdev,__int16   offset,__int16   lenth,unsigned char* send_buffer){
	return reader_d8.dc_swr_eeprom_hex8(icdev,offset,lenth,send_buffer);
}
__int16 __stdcall dc_gettime_hex(HANDLE icdev,char *time){
	return reader_d8.dc_gettime_hex8(icdev,time);
}
__int16 __stdcall dc_settime_hex(HANDLE icdev,char *time){
	return reader_d8.dc_settime_hex8(icdev,time);
}
__int16 __stdcall dc_des(unsigned char *key,unsigned char *sour,unsigned char *dest,__int16 m){
	return reader_d8.dc_des8(key,sour,dest,m);
}
__int16 __stdcall dc_pro_reset_hex(HANDLE icdev,unsigned char *rlen, char *receive_data){
	return reader_d8.dc_pro_reset_hex8(icdev,rlen,receive_data);
}
__int16 __stdcall dc_pro_command_hex(HANDLE idComDev,unsigned char slen,char * sendbuffer,unsigned char *rlen,char * databuffer,unsigned char timeout){
	return reader_d8.dc_pro_command_hex8(idComDev,slen,sendbuffer,rlen,databuffer,timeout);
}
__int16 __stdcall dc_pro_commandsource_hex(HANDLE idComDev,unsigned char slen,char * sendbuffer,unsigned char *rlen,char * databuffer,unsigned char timeout){
	return reader_d8.dc_pro_commandsource_hex8(idComDev,slen,sendbuffer,rlen,databuffer,timeout);
}
__int16 __stdcall dc_switch_unix(HANDLE icdev,long baud){
	return reader_d8.dc_switch_unix8(icdev,baud);
}
__int16 __stdcall dc_authentication_passaddr(HANDLE icdev,unsigned char _Mode,unsigned char _Addr,unsigned char *passbuff){
	return reader_d8.dc_authentication_passaddr8(icdev,_Mode,_Addr,passbuff);
}
__int16 __stdcall dc_authentication_passaddr_hex(HANDLE icdev,unsigned char _Mode,unsigned char _Addr,unsigned char *passbuff){
	return reader_d8.dc_authentication_passaddr_hex8(icdev,_Mode,_Addr,passbuff);
}
__int16 __stdcall dc_card_fm11rf005(HANDLE icdev,unsigned char _Mode,unsigned long *_Snr){
	return reader_d8.dc_card_fm11rf0058(icdev,_Mode,_Snr);
}
__int16 __stdcall dc_setusbtimeout(unsigned char ntimes){
	return reader_d8.dc_setusbtimeout8(ntimes);
}
__int16 __stdcall dc_mfdes_baud(HANDLE icdev,unsigned char _Mode,unsigned char para){
	return reader_d8.dc_mfdes_baud8(icdev,_Mode,para);
}
__int16 __stdcall dc_tripledes(unsigned char *key,unsigned char *src,unsigned char *dest,__int16 m){
	return reader_d8.dc_tripledes8(key,src,dest,m);
}
__int16 __stdcall dc_tripledes_hex(unsigned char *key,unsigned char *src,unsigned char *dest,__int16 m){
	return reader_d8.dc_tripledes_hex8(key,src,dest,m);
}
__int16 __stdcall dc_mfdes_auth_hex(HANDLE icdev,unsigned char keyno,unsigned char keylen,unsigned char *authkey,unsigned char *randAdata,unsigned char *randBdata){
	return reader_d8.dc_mfdes_auth_hex8(icdev,keyno,keylen,authkey,randAdata,randBdata);
}
__int16 __stdcall dc_pro_sendcommandsource(HANDLE idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char timeout){
	return reader_d8.dc_pro_sendcommandsource8(idComDev,slen,sendbuffer,timeout);
}
__int16 __stdcall dc_pro_receivecommandsource(HANDLE idComDev,unsigned char *rlen,unsigned char * databuffer){
	return reader_d8.dc_pro_receivecommandsource8(idComDev,rlen,databuffer);
}
__int16 __stdcall dc_inventory(HANDLE icdev,unsigned char flags,unsigned char AFI,unsigned char masklen,unsigned char *rlen,unsigned char *rbuffer){
	return reader_d8.dc_inventory8(icdev,flags,AFI,masklen,rlen,rbuffer);
}
__int16 __stdcall dc_inventory_hex(HANDLE icdev,unsigned char flags,unsigned char AFI,unsigned char masklen,unsigned char *rlen,unsigned char *rbuffer){
	return reader_d8.dc_inventory_hex8(icdev,flags,AFI,masklen,rlen,rbuffer);
}
__int16 __stdcall dc_stay_quiet(HANDLE icdev,unsigned char flags,unsigned char *UID){
	return reader_d8.dc_stay_quiet8(icdev,flags,UID);
}
__int16 __stdcall dc_stay_quiet_hex(HANDLE icdev,unsigned char flags,unsigned char *UID){
	return reader_d8.dc_stay_quiet_hex8(icdev,flags,UID);
}
__int16 __stdcall dc_select_uid(HANDLE icdev,unsigned char flags,unsigned char *UID){
	return reader_d8.dc_select_uid8(icdev,flags,UID);
}
__int16 __stdcall dc_select_uid_hex(HANDLE icdev,unsigned char flags,unsigned char *UID){
	return reader_d8.dc_select_uid_hex8(icdev,flags,UID);
}
__int16 __stdcall dc_reset_to_ready(HANDLE icdev,unsigned char flags,unsigned char *UID){
	return reader_d8.dc_reset_to_ready8(icdev,flags,UID);
}
__int16 __stdcall dc_reset_to_ready_hex(HANDLE icdev,unsigned char flags,unsigned char *UID){
	return reader_d8.dc_reset_to_ready_hex8(icdev,flags,UID);
}
__int16 __stdcall dc_lock_block(HANDLE icdev,unsigned char flags,unsigned char block,unsigned char *UID){
	return reader_d8.dc_lock_block8(icdev,flags,block,UID);
}
__int16 __stdcall dc_lock_block_hex(HANDLE icdev,unsigned char flags,unsigned char block,unsigned char *UID){
	return reader_d8.dc_lock_block_hex8(icdev,flags,block,UID);
}
__int16 __stdcall dc_write_afi(HANDLE icdev,unsigned char flags,unsigned char AFI,unsigned char *UID){
	return reader_d8.dc_write_afi8(icdev,flags,AFI,UID);
}
__int16 __stdcall dc_write_afi_hex(HANDLE icdev,unsigned char flags,unsigned char AFI,unsigned char *UID){
	return reader_d8.dc_write_afi_hex8(icdev,flags,AFI,UID);
}
__int16 __stdcall dc_lock_afi(HANDLE icdev,unsigned char flags,unsigned char AFI,unsigned char *UID){
	return reader_d8.dc_lock_afi8(icdev,flags,AFI,UID);
}
__int16 __stdcall dc_lock_afi_hex(HANDLE icdev,unsigned char flags,unsigned char AFI,unsigned char *UID){
	return reader_d8.dc_lock_afi_hex8(icdev,flags,AFI,UID);
}
__int16 __stdcall dc_write_dsfid(HANDLE icdev,unsigned char flags,unsigned char DSFID,unsigned char *UID){
	return reader_d8.dc_write_dsfid8(icdev,flags,DSFID,UID);
}
__int16 __stdcall dc_write_dsfid_hex(HANDLE icdev,unsigned char flags,unsigned char DSFID,unsigned char *UID){
	return reader_d8.dc_write_dsfid_hex8(icdev,flags,DSFID,UID);
}
__int16 __stdcall dc_lock_dsfid(HANDLE icdev,unsigned char flags,unsigned char DSFID,unsigned char *UID){
	return reader_d8.dc_lock_dsfid8(icdev,flags,DSFID,UID);
}
__int16 __stdcall dc_lock_dsfid_hex(HANDLE icdev,unsigned char flags,unsigned char DSFID,unsigned char *UID){
	return reader_d8.dc_lock_dsfid_hex8(icdev,flags,DSFID,UID);
}
__int16 __stdcall dc_get_systeminfo(HANDLE icdev,unsigned char flags,unsigned char *UID,unsigned char *rlen,unsigned char *rbuffer){
	return reader_d8.dc_get_systeminfo8(icdev,flags,UID,rlen,rbuffer);
}
__int16 __stdcall dc_get_systeminfo_hex(HANDLE icdev,unsigned char flags,unsigned char *UID,unsigned char *rlen,unsigned char *rbuffer){
	return reader_d8.dc_get_systeminfo_hex8(icdev,flags,UID,rlen,rbuffer);
}
__int16 __stdcall dc_get_securityinfo(HANDLE icdev,unsigned char flags,unsigned char startblock,unsigned char blocknum,unsigned char *UID,unsigned char *rlen,unsigned char *rbuffer){
	return reader_d8.dc_get_securityinfo8(icdev,flags,startblock,blocknum,UID,rlen,rbuffer);
}
__int16 __stdcall dc_get_securityinfo_hex(HANDLE icdev,unsigned char flags,unsigned char startblock,unsigned char blocknum,unsigned char *UID,unsigned char *rlen,unsigned char *rbuffer){
	return reader_d8.dc_get_securityinfo_hex8(icdev,flags,startblock,blocknum,UID,rlen,rbuffer);
}
__int16 __stdcall dc_getsnr_fm11rf005(HANDLE icdev,unsigned long *_Snr){
	return reader_d8.dc_getsnr_fm11rf0058(icdev,_Snr);
}
__int16 __stdcall dc_getsnr_fm11rf005_hex(HANDLE icdev,unsigned char *snrstr){
	return reader_d8.dc_getsnr_fm11rf005_hex8(icdev,snrstr);
}
__int16 __stdcall dc_write_fm11rf005(HANDLE icdev,unsigned char _Adr,unsigned char *_Data){
	return reader_d8.dc_write_fm11rf0058(icdev,_Adr,_Data);
}
__int16 __stdcall dc_read_fm11rf005(HANDLE icdev,unsigned char _Adr,unsigned char *_Data){
	return reader_d8.dc_read_fm11rf0058(icdev,_Adr,_Data);
}
__int16 __stdcall dc_read_fm11rf005_hex(HANDLE icdev,unsigned char _Adr,char *_Data){
	return reader_d8.dc_read_fm11rf005_hex8(icdev,_Adr,_Data);
}
__int16 __stdcall dc_write_fm11rf005_hex(HANDLE icdev,unsigned char _Adr,char *_Data){
	return reader_d8.dc_write_fm11rf005_hex8(icdev,_Adr,_Data);
}
__int16 __stdcall DCDEV_CommandMcu(HANDLE idComDev,unsigned char ctimeout,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer){
	return reader_d8.DCDEV_CommandMcu8(idComDev,ctimeout,slen,sendbuffer,rlen,databuffer);
}
__int16 __stdcall DCDEV_CommandMcu_Hex(HANDLE idComDev,unsigned char ctimeout,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer){
	return reader_d8.DCDEV_CommandMcu_Hex8(idComDev,ctimeout,slen,sendbuffer,rlen,databuffer);
}
__int16 __stdcall dc_displcd(HANDLE idComDev,unsigned char flag){
	return reader_d8.dc_displcd8(idComDev,flag);
}
__int16 __stdcall dc_getinputpass(HANDLE idComDev,unsigned char ctime,unsigned char *rlen,unsigned char * cpass){
	return reader_d8.dc_getinputpass8(idComDev,ctime,rlen,cpass);
}
__int16 __stdcall dc_readmagcard(HANDLE idComDev, unsigned char ctime, unsigned char *pTrack2Data, unsigned long *pTrack2Len, unsigned char *pTrack3Data, unsigned long *pTrack3Len){
	return reader_d8.dc_readmagcard8(idComDev,ctime,pTrack2Data,pTrack2Len,pTrack3Data,pTrack3Len);
}
__int16 __stdcall dc_testdevicecomm(HANDLE idComDev){
	return reader_d8.dc_testdevicecomm8(idComDev);
}
__int16 __stdcall dc_dispmainmenu(HANDLE idComDev){
	return reader_d8.dc_dispmainmenu8(idComDev);
}
__int16 __stdcall dc_setdevicetime(HANDLE idComDev,unsigned char year,unsigned char month,unsigned char date,unsigned char hour,unsigned char minute,unsigned char second){
	return reader_d8.dc_setdevicetime8(idComDev,year,month,date,hour,minute,second);
}
__int16 __stdcall dc_getdevicetime(HANDLE idComDev,unsigned char *year,unsigned char *month,unsigned char *date,unsigned char *hour,unsigned char *minute,unsigned char *second){
	return reader_d8.dc_getdevicetime8(idComDev,year,month,date,hour,minute,second);
}
__int16 __stdcall dc_dispinfo(HANDLE idComDev,unsigned char line,unsigned char offset,char *data){
	return reader_d8.dc_dispinfo8(idComDev,line,offset,data);
}
__int16 __stdcall dc_dispmaininfo(HANDLE idComDev,unsigned char offset,char *data){
	return reader_d8.dc_dispmaininfo8(idComDev,offset,data);
}
__int16 __stdcall dc_posbeep(HANDLE idComDev,unsigned char beeptime){
	return reader_d8.dc_posbeep8(idComDev,beeptime);
}
__int16 __stdcall dc_ctlbacklight(HANDLE idComDev, unsigned char cOpenFlag){
	return reader_d8.dc_ctlbacklight8(idComDev,cOpenFlag);
}
__int16 __stdcall dc_ctlled(HANDLE idComDev, unsigned char cLed, unsigned char cOpenFlag){
	return reader_d8.dc_ctlled8(idComDev,cLed,cOpenFlag);
}
__int16 __stdcall dc_lcdclrscrn(HANDLE idComDev, unsigned char cLine){
	return reader_d8.dc_lcdclrscrn8(idComDev,cLine);
}
__int16 __stdcall dc_passin(HANDLE idComDev,unsigned char ctime){
	return reader_d8.dc_passin8(idComDev,ctime);
}
__int16 __stdcall dc_passget(HANDLE idComDev,unsigned char *rlen,unsigned char * cpass){
	return reader_d8.dc_passget8(idComDev,rlen,cpass);
}
__int16 __stdcall dc_passcancel(HANDLE idComDev){
	return reader_d8.dc_passcancel8(idComDev);
}
__int16 __stdcall dc_getinputkey(HANDLE idComDev,unsigned char disptype,unsigned char line,unsigned char ctime,unsigned char *rlen,unsigned char * ckeydata){
	return reader_d8.dc_getinputkey8(idComDev,disptype,line,ctime,rlen,ckeydata);
}
__int16 __stdcall dc_displcd_ext(HANDLE idComDev,unsigned char flag,unsigned char row,unsigned char offset){
	return reader_d8.dc_displcd_ext8(idComDev,flag,row,offset);
}
__int16 __stdcall dc_readmagcardall(HANDLE idComDev, unsigned char ctime, unsigned char *pTrack1Data, unsigned long *pTrack1Len,unsigned char *pTrack2Data, unsigned long *pTrack2Len, unsigned char *pTrack3Data, unsigned long *pTrack3Len){
	return reader_d8.dc_readmagcardall8(idComDev,ctime,pTrack1Data,pTrack1Len,pTrack2Data,pTrack2Len,pTrack3Data,pTrack3Len);
}
__int16 __stdcall dc_readdevsnr(HANDLE idComDev,unsigned char *snr){
	return reader_d8.dc_readdevsnr8(idComDev,snr);
}
__int16 __stdcall dc_readreadersnr(HANDLE idComDev,unsigned char *snr){
	return reader_d8.dc_readreadersnr8(idComDev,snr);
}
__int16 __stdcall dc_resetdevice(HANDLE idComDev){
	return reader_d8.dc_resetdevice8(idComDev);
}
__int16 __stdcall dc_read_4442(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * buffer){
	return reader_d8.dc_read_44428(icdev,offset,lenth,buffer);
}
__int16 __stdcall dc_read_4442_hex(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char* buffer){
	return reader_d8.dc_read_4442_hex8(icdev,offset,lenth,buffer);
}
__int16 __stdcall dc_write_4442(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * buffer){
	return reader_d8.dc_write_44428(icdev,offset,lenth,buffer);
}
__int16 __stdcall dc_write_4442_hex(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char* buffer){
	return reader_d8.dc_write_4442_hex8(icdev,offset,lenth,buffer);
}
__int16 __stdcall dc_verifypin_4442(HANDLE icdev,unsigned char *passwd){
	return reader_d8.dc_verifypin_44428(icdev,passwd);
}
__int16 __stdcall dc_verifypin_4442_hex(HANDLE icdev,unsigned char *passwd){
	return reader_d8.dc_verifypin_4442_hex8(icdev,passwd);
}
__int16 __stdcall dc_readpin_4442(HANDLE icdev,unsigned char *passwd){
	return reader_d8.dc_readpin_44428(icdev,passwd);
}
__int16 __stdcall dc_readpin_4442_hex(HANDLE icdev,unsigned char *passwd){
	return reader_d8.dc_readpin_4442_hex8(icdev,passwd);
}
__int16 __stdcall dc_readpincount_4442(HANDLE icdev){
	return reader_d8.dc_readpincount_44428(icdev);
}
__int16 __stdcall dc_changepin_4442(HANDLE icdev,unsigned char *passwd){
	return reader_d8.dc_changepin_44428(icdev,passwd);
}
__int16 __stdcall dc_changepin_4442_hex(HANDLE icdev,unsigned char *passwd){
	return reader_d8.dc_changepin_4442_hex8(icdev,passwd);
}
__int16 __stdcall dc_readwrotect_4442(HANDLE icdev,__int16 offset,__int16 leng,unsigned char *buffer){
	return reader_d8.dc_readwrotect_44428(icdev,offset,leng,buffer);
}
__int16 __stdcall dc_readwrotect_4442_hex(HANDLE icdev,__int16 offset,__int16 leng,unsigned char *buffer){
	return reader_d8.dc_readwrotect_4442_hex8(icdev,offset,leng,buffer);
}
__int16 __stdcall dc_writeprotect_4442(HANDLE icdev,__int16 offset,__int16 leng,unsigned char *buffer){
	return reader_d8.dc_writeprotect_44428(icdev,offset,leng,buffer);
}
__int16 __stdcall dc_writeprotect_4442_hex(HANDLE icdev,__int16 offset,__int16 leng,unsigned char *buffer){
	return reader_d8.dc_writeprotect_4442_hex8(icdev,offset,leng,buffer);
}
__int16 __stdcall dc_write_24c(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * snd_buffer){
	return reader_d8.dc_write_24c8(icdev,offset,lenth,snd_buffer);
}
__int16 __stdcall dc_write_24c_hex(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * snd_buffer){
	return reader_d8.dc_write_24c_hex8(icdev,offset,lenth,snd_buffer);
}
__int16 __stdcall dc_write_24c64(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * snd_buffer){
	return reader_d8.dc_write_24c648(icdev,offset,lenth,snd_buffer);
}
__int16 __stdcall dc_write_24c64_hex(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * snd_buffer){
	return reader_d8.dc_write_24c64_hex8(icdev,offset,lenth,snd_buffer);
}
__int16 __stdcall dc_read_24c(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * receive_buffer){
	return reader_d8.dc_read_24c8(icdev,offset,lenth,receive_buffer);
}
__int16 __stdcall dc_read_24c_hex(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * receive_buffer){
	return reader_d8.dc_read_24c_hex8(icdev,offset,lenth,receive_buffer);
}
__int16 __stdcall dc_read_24c64(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * receive_buffer){
	return reader_d8.dc_read_24c648(icdev,offset,lenth,receive_buffer);
}
__int16 __stdcall dc_read_24c64_hex(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * receive_buffer){
	return reader_d8.dc_read_24c64_hex8(icdev,offset,lenth,receive_buffer);
}
__int16 __stdcall dc_read_4428(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * buffer){
	return reader_d8.dc_read_44288(icdev,offset,lenth,buffer);
}
__int16 __stdcall dc_read_4428_hex(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char* buffer){
	return reader_d8.dc_read_4428_hex8(icdev,offset,lenth,buffer);
}
__int16 __stdcall dc_write_4428(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * buffer){
	return reader_d8.dc_write_44288(icdev,offset,lenth,buffer);
}
__int16 __stdcall dc_write_4428_hex(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char* buffer){
	return reader_d8.dc_write_4428_hex8(icdev,offset,lenth,buffer);
}
__int16 __stdcall dc_verifypin_4428(HANDLE icdev,unsigned char *passwd){
	return reader_d8.dc_verifypin_44288(icdev,passwd);
}
__int16 __stdcall dc_verifypin_4428_hex(HANDLE icdev,unsigned char *passwd){
	return reader_d8.dc_verifypin_4428_hex8(icdev,passwd);
}
__int16 __stdcall dc_readpin_4428(HANDLE icdev,unsigned char *passwd){
	return reader_d8.dc_readpin_44288(icdev,passwd);
}
__int16 __stdcall dc_readpin_4428_hex(HANDLE icdev,unsigned char *passwd){
	return reader_d8.dc_readpin_4428_hex8(icdev,passwd);
}
__int16 __stdcall dc_readpincount_4428(HANDLE icdev){
	return reader_d8.dc_readpincount_44288(icdev);
}
__int16 __stdcall dc_changepin_4428(HANDLE icdev,unsigned char *passwd){
	return reader_d8.dc_changepin_44288(icdev,passwd);
}
__int16 __stdcall dc_changepin_4428_hex(HANDLE icdev,unsigned char *passwd){
	return reader_d8.dc_changepin_4428_hex8(icdev,passwd);
}
__int16 __stdcall dc_Check_4442(HANDLE icdev){
	return reader_d8.dc_Check_44428(icdev);
}
__int16 __stdcall dc_Check_4428(HANDLE icdev){
	return reader_d8.dc_Check_44288(icdev);
}
__int16 __stdcall dc_Check_24C01(HANDLE icdev){
	return reader_d8.dc_Check_24C018(icdev);
}
__int16 __stdcall dc_Check_24C02(HANDLE icdev){
	return reader_d8.dc_Check_24C028(icdev);
}
__int16 __stdcall dc_Check_24C04(HANDLE icdev){
	return reader_d8.dc_Check_24C048(icdev);
}
__int16 __stdcall dc_Check_24C08(HANDLE icdev){
	return reader_d8.dc_Check_24C088(icdev);
}
__int16 __stdcall dc_Check_24C16(HANDLE icdev){
	return reader_d8.dc_Check_24C168(icdev);
}
__int16 __stdcall dc_Check_24C64(HANDLE icdev){
	return reader_d8.dc_Check_24C648(icdev);
}
__int16 __stdcall dc_Check_CPU(HANDLE icdev){
	return reader_d8.dc_Check_CPU8(icdev);
}
__int16 __stdcall dc_CheckCard(HANDLE icdev){
	return reader_d8.dc_CheckCard8(icdev);
}
__int16 __stdcall dc_getrcinfo(HANDLE icdev,unsigned char *info){
	return reader_d8.dc_getrcinfo8(icdev,info);
}
__int16 __stdcall dc_getrcinfo_hex(HANDLE icdev,unsigned char *info){
	return reader_d8.dc_getrcinfo_hex8(icdev,info);
}
__int16 __stdcall dc_getlongver(HANDLE icdev,unsigned char *sver){
	return reader_d8.dc_getlongver8(icdev,sver);
}
__int16 __stdcall dc_cardstr(HANDLE icdev,unsigned char _Mode,char * Strsnr){
	return reader_d8.dc_cardstr8(icdev,_Mode,Strsnr);
}
__int16 __stdcall dc_card_b(HANDLE icdev,unsigned char *rbuf){
	return reader_d8.dc_card_b8(icdev,rbuf);
}
__int16 __stdcall dc_card_b_hex(HANDLE icdev,char *rbuf){
	return reader_d8.dc_card_b_hex8(icdev,rbuf);
}
__int16 __stdcall dc_dispinfo_T8(HANDLE idComDev,unsigned char line,unsigned char offset,char *data){
	return reader_d8.dc_dispinfo_T88(idComDev,line,offset,data);
}
__int16 __stdcall dc_dispinfo_pro_T8(HANDLE idComDev,unsigned char offset,char *data){
	return reader_d8.dc_dispinfo_pro_T88(idComDev,offset,data);
}
__int16 __stdcall dc_clearlcd_T8(HANDLE icdev,unsigned char line){
	return reader_d8.dc_clearlcd_T88(icdev,line);
}
__int16 __stdcall dc_led_T8(HANDLE icdev,unsigned char cled,unsigned char cflag){
	return reader_d8.dc_led_T88(icdev,cled,cflag);
}
__int16 __stdcall dc_MFPL0_writeperso(HANDLE icdev,unsigned int BNr,unsigned char * dataperso){
	return reader_d8.dc_MFPL0_writeperso8(icdev,BNr,dataperso);
}
__int16 __stdcall dc_MFPL0_writeperso_hex(HANDLE icdev,unsigned int BNr,unsigned char * dataperso){
	return reader_d8.dc_MFPL0_writeperso_hex8(icdev,BNr,dataperso);
}
__int16 __stdcall dc_MFPL0_commitperso(HANDLE icdev){
	return reader_d8.dc_MFPL0_commitperso8(icdev);
}
__int16 __stdcall dc_MFPL1_authl1key(HANDLE icdev,unsigned char *authkey){
	return reader_d8.dc_MFPL1_authl1key8(icdev,authkey);
}
__int16 __stdcall dc_MFPL1_authl1key_hex(HANDLE icdev,unsigned char *authkey){
	return reader_d8.dc_MFPL1_authl1key_hex8(icdev,authkey);
}
__int16 __stdcall dc_MFPL1_switchtol2(HANDLE icdev,unsigned char *authkey){
	return reader_d8.dc_MFPL1_switchtol28(icdev,authkey);
}
__int16 __stdcall dc_MFPL1_switchtol3(HANDLE icdev,unsigned char *authkey){
	return reader_d8.dc_MFPL1_switchtol38(icdev,authkey);
}
__int16 __stdcall dc_MFPL2_switchtol3(HANDLE icdev,unsigned char *authkey){
	return reader_d8.dc_MFPL2_switchtol38(icdev,authkey);
}
__int16 __stdcall dc_MFPL3_authl3key(HANDLE icdev,unsigned int keyBNr,unsigned char *authkey){
	return reader_d8.dc_MFPL3_authl3key8(icdev,keyBNr,authkey);
}
__int16 __stdcall dc_MFPL3_authl3key_hex(HANDLE icdev,unsigned int keyBNr,unsigned char *authkey){
	return reader_d8.dc_MFPL3_authl3key_hex8(icdev,keyBNr,authkey);
}
__int16 __stdcall dc_MFPL3_authl3sectorkey(HANDLE icdev,unsigned char mode,unsigned int sectorBNr,unsigned char *authkey){
	return reader_d8.dc_MFPL3_authl3sectorkey8(icdev,mode,sectorBNr,authkey);
}
__int16 __stdcall dc_MFPL3_authl3sectorkey_hex(HANDLE icdev,unsigned char mode,unsigned int sectorBNr,unsigned char *authkey){
	return reader_d8.dc_MFPL3_authl3sectorkey_hex8(icdev,mode,sectorBNr,authkey);
}
__int16 __stdcall dc_MFPL3_readinplain(HANDLE icdev,unsigned int BNr,unsigned char Numblock, unsigned char *readdata){
	return reader_d8.dc_MFPL3_readinplain8(icdev,BNr,Numblock,readdata);
}
__int16 __stdcall dc_MFPL3_readinplain_hex(HANDLE icdev,unsigned int BNr,unsigned char Numblock, unsigned char *readdata){
	return reader_d8.dc_MFPL3_readinplain_hex8(icdev,BNr,Numblock,readdata);
}
__int16 __stdcall dc_MFPL3_readencrypted(HANDLE icdev,unsigned int BNr,unsigned char Numblock, unsigned char *readdata, unsigned char flag){
	return reader_d8.dc_MFPL3_readencrypted8(icdev,BNr,Numblock,readdata,flag);
}
__int16 __stdcall dc_MFPL3_readencrypted_hex(HANDLE icdev,unsigned int BNr,unsigned char Numblock, unsigned char *readdata, unsigned char flag){
	return reader_d8.dc_MFPL3_readencrypted_hex8(icdev,BNr,Numblock,readdata,flag);
}
__int16 __stdcall dc_MFPL3_writeinplain(HANDLE icdev,unsigned int BNr,unsigned char Numblock,unsigned char *writedata){
	return reader_d8.dc_MFPL3_writeinplain8(icdev,BNr,Numblock,writedata);
}
__int16 __stdcall dc_MFPL3_writeinplain_hex(HANDLE icdev,unsigned int BNr,unsigned char Numblock,unsigned char *writedata){
	return reader_d8.dc_MFPL3_writeinplain_hex8(icdev,BNr,Numblock,writedata);
}
__int16 __stdcall dc_MFPL3_writeencrypted(HANDLE icdev,unsigned int BNr,unsigned char Numblock,unsigned char *writedata, unsigned char flag){
	return reader_d8.dc_MFPL3_writeencrypted8(icdev,BNr,Numblock,writedata,flag);
}
__int16 __stdcall dc_MFPL3_writeencrypted_hex(HANDLE icdev,unsigned int BNr,unsigned char Numblock,unsigned char *writedata, unsigned char flag){
	return reader_d8.dc_MFPL3_writeencrypted_hex8(icdev,BNr,Numblock,writedata,flag);
}
__int16 __stdcall dc_auth_ulc(HANDLE icdev, unsigned char * key){
	return reader_d8.dc_auth_ulc8(icdev,key);
}
__int16 __stdcall dc_auth_ulc_hex(HANDLE icdev, unsigned char * key){
	return reader_d8.dc_auth_ulc_hex8(icdev,key);
}
__int16 __stdcall dc_changekey_ulc(HANDLE icdev,unsigned char *newkey){
	return reader_d8.dc_changekey_ulc8(icdev,newkey);
}
__int16 __stdcall dc_changekey_ulc_hex(HANDLE icdev,unsigned char *newkey){
	return reader_d8.dc_changekey_ulc_hex8(icdev,newkey);
}
__int16 __stdcall dc_pro_commandlinkEXT_hex(HANDLE idComDev,unsigned int slen,unsigned char * sendbuffer,unsigned int *rlen,unsigned char * databuffer,unsigned char timeout,unsigned char FG){
	return reader_d8.dc_pro_commandlinkEXT_hex8(idComDev,slen,sendbuffer,rlen,databuffer,timeout,FG);
}

/***********************************自动生成代码***added by chch 20110703****************************/
/***********************************自动生成代码***added by chch 20110703****************************/
//CPU下电
__int16 __stdcall dc_cpudown(HANDLE icdev)
{
	if(1==flag)
	{
		return reader_d8.dc_cpudown8(icdev);
	}
	else
	{
		return reader_d6.IC_Down6(handle_d6);
	}
}












