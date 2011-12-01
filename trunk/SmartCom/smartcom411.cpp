#include "stdafx.h"
#include "stdio.h"
#include "smartcom411.h"
#include "CustomConsts.h"
#include "Winbase.h"
#include <winsock2.h>
#include "iphlpapi.h"
#include "windows.h"
#pragma comment(lib, "ws2_32.lib" )
#pragma comment(lib, "IPHlpApi.Lib" )

HANDLE  hCommDev[256]=
{INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE,
 INVALID_HANDLE_VALUE,INVALID_HANDLE_VALUE};

unsigned int crctab[256]=  //calc_crc16 常数表
{
 0x0000,0x1021,0x2042,0x3063,0x4084,0x50A5,0x60C6,0x70E7,
 0x8108,0x9129,0xA14A,0xB16B,0xC18C,0xD1AD,0xE1CE,0xF1EF,
 0x1231,0x0210,0x3273,0x2252,0x52B5,0x4294,0x72F7,0x62D6,
 0x9339,0x8318,0xB37B,0xA35A,0xD3BD,0xC39C,0xF3FF,0xE3DE,
 0x2462,0x3443,0x0420,0x1401,0x64E6,0x74C7,0x44A4,0x5485,
 0xA56A,0xB54B,0x8528,0x9509,0xE5EE,0xF5CF,0xC5AC,0xD58D,
 0x3653,0x2672,0x1611,0x0630,0x76D7,0x66F6,0x5695,0x46B4,
 0xB75B,0xA77A,0x9719,0x8738,0xF7DF,0xE7FE,0xD79D,0xC7BC,
 0x48C4,0x58E5,0x6886,0x78A7,0x0840,0x1861,0x2802,0x3823,
 0xC9CC,0xD9ED,0xE98E,0xF9AF,0x8948,0x9969,0xA90A,0xB92B,
 0x5AF5,0x4AD4,0x7AB7,0x6A96,0x1A71,0x0A50,0x3A33,0x2A12,
 0xDBFD,0xCBDC,0xFBBF,0xEB9E,0x9B79,0x8B58,0xBB3B,0xAB1A,
 0x6CA6,0x7C87,0x4CE4,0x5CC5,0x2C22,0x3C03,0x0C60,0x1C41,
 0xEDAE,0xFD8F,0xCDEC,0xDDCD,0xAD2A,0xBD0B,0x8D68,0x9D49,
 0x7E97,0x6EB6,0x5ED5,0x4EF4,0x3E13,0x2E32,0x1E51,0x0E70,
 0xFF9F,0xEFBE,0xDFDD,0xCFFC,0xBF1B,0xAF3A,0x9F59,0x8F78,
 0x9188,0x81A9,0xB1CA,0xA1EB,0xD10C,0xC12D,0xF14E,0xE16F,
 0x1080,0x00A1,0x30C2,0x20E3,0x5004,0x4025,0x7046,0x6067,
 0x83B9,0x9398,0xA3FB,0xB3DA,0xC33D,0xD31C,0xE37F,0xF35E,
 0x02B1,0x1290,0x22F3,0x32D2,0x4235,0x5214,0x6277,0x7256,
 0xB5EA,0xA5CB,0x95A8,0x8589,0xF56E,0xE54F,0xD52C,0xC50D,
 0x34E2,0x24C3,0x14A0,0x0481,0x7466,0x6447,0x5424,0x4405,
 0xA7DB,0xB7FA,0x8799,0x97B8,0xE75F,0xF77E,0xC71D,0xD73C,
 0x26D3,0x36F2,0x0691,0x16B0,0x6657,0x7676,0x4615,0x5634,
 0xD94C,0xC96D,0xF90E,0xE92F,0x99C8,0x89E9,0xB98A,0xA9AB,
 0x5844,0x4865,0x7806,0x6827,0x18C0,0x08E1,0x3882,0x28A3,
 0xCB7D,0xDB5C,0xEB3F,0xFB1E,0x8BF9,0x9BD8,0xABBB,0xBB9A,
 0x4A75,0x5A54,0x6A37,0x7A16,0x0AF1,0x1AD0,0x2AB3,0x3A92,
 0xFD2E,0xED0F,0xDD6C,0xCD4D,0xBDAA,0xAD8B,0x9DE8,0x8DC9,
 0x7C26,0x6C07,0x5C64,0x4C45,0x3CA2,0x2C83,0x1CE0,0x0CC1,
 0xEF1F,0xFF3E,0xCF5D,0xDF7C,0xAF9B,0xBFBA,0x8FD9,0x9FF8,
 0x6E17,0x7E36,0x4E55,0x5E74,0x2E93,0x3EB2,0x0ED1,0x1EF0
}; 

/************ calc_crc16 快表法*************/
void crcupdata(unsigned char in,unsigned short *accum,unsigned int *crctab)
{
	*accum=(*accum<<8)^crctab[(*accum>>8)^in];
}
/*  len: 校验数据长度 */
/*  in:  校验数据包体 */
unsigned short  calc_crc16(unsigned char len,unsigned char *in)
{

	unsigned char i;
	unsigned short crc;	
	int stat;
	stat=0;
	crc=0xc78c;
	for(i=0;i<len;in++,i++)
	{
		crcupdata(*in,&crc,crctab);
	}	    
	return(crc);
}

//SVC_DSP_2_HEX和SVC_HEX_2_DSP为十六进制数组与ASSCII数组转换函数。

/***************************************************************************
  SUPPOSE dsp CONTAINS THE ASSCII ARRAY "12345F" AND WE EXECUTE THIS FUNCTION
  THEN THE ARRAY  AT hex WILL CONTAIN 12H,34H, 5FH
     	ASC->Hex
****************************************************************************/

void  SVC_DSP_2_HEX(unsigned char *dsp,unsigned char *hex,int count)
{
	int i;
	unsigned char ch;
	
	for(i=0;i<count;i++)
	{
		ch = dsp[i*2];
		if(ch>='a')
			ch -= 0x20;
		hex[i]=((ch<=0x39)?ch-0x30:ch-0x41+10);
		hex[i]=hex[i]<<4;

		ch = dsp[i*2+1];
		if(ch>='a')
			ch -= 0x20;
		hex[i]+=(((ch<=0x39)?ch-0x30:ch-0x41+10)&0x0f);
	}
}


/***************************************************************************
 SUPPOSE HEX CONTAINS THREE BYTES:12H 34H, 5FH AND WE EXECUTE THIS FUNCTION
 THEN dsp WILL CONTAIN ASCII BYTES "12345F"(Input:hex,count;Ouput:dsp)
	Hex->ASC
 **************************************************************************/

void  SVC_HEX_2_DSP(unsigned char *hex,unsigned char *dsp,int count)
{
	int i;
	char ch;
	for(i=0;i<count;i++)
	{
		ch=(hex[i]&0xf0)>>4;
		dsp[i*2]=(ch>9)?ch+0x41-10:ch+0x30;
		ch=hex[i]&0x0f;
		dsp[i*2+1]=(ch>9)?ch+0x41-10:ch+0x30;
	}
}

///********串口操作函数start********//
//******************************************/
/* Declare:初始化串口，打开串口            */
/* Input :                                 */ 
/*    ComPort  串口号(1、2、3、4)          */
/*    BaudRate 波特率代码			       */
/*        0-----19200                      */
/*        1-----9600                       */
/*        2-----4800                        */
/*        3-----2400                       */
/*        4-----1200                       */
/*        5-----28800	                   */			
/*	      6-----57600	                   */	
/*	      7-----115200                      */
/*	      默认--19200                      */
/* return:                                 */
/*   0——成功   -7 ---- 不成功            */ 		
////////////////////////////////////////////
int  IniCom(int ComPort,int BaudRate)
{
	int		baud;
	DCB		dcb;
	char	InitTemp[80];
	char	CommName[10];
	COMMTIMEOUTS CommTimeOuts;

    //标准通信口	
	switch(BaudRate)
	{
	case 19200:
		baud=19200;
		break;
	case 9600:
		baud=9600;
		break;
	case 4800:
		baud=4800;
		break;
	case 2400:
		baud=2400;
		break;
	case 1200:
		baud=1200;
		break;
	case 28800:
		baud=28800;
		break;
	case 57600:
		baud=57600;
		break;
	case 115200:
		baud=115200;
		break;
	default:
		baud=19200;
		break;
	}	

	//通过标准通信口

		sprintf(CommName,"\\\\?\\COM%d",ComPort);
		hCommDev[ComPort]= CreateFile 
		(
		  CommName,
		  GENERIC_READ|GENERIC_WRITE, //dwDesiredAccess
		  0,     //dwShareMode唯一访问
		  NULL,  //lpSecurityAttributes
		  OPEN_EXISTING,	//如COM口已存在,则为OPEN_EXISTING//dwCreationDistribution	  
		  //0,   //dwFlagsAndAttributes
		  FILE_ATTRIBUTE_NORMAL,//dwFlagsAndAttributes
		  NULL  //必须为NULL
	    );
		
		if (hCommDev[ComPort] == (HANDLE)-1 )
		  return (-7);
		SetupComm(hCommDev[ComPort],1024,1024);
		GetCommState(hCommDev[ComPort],&dcb);
		sprintf(InitTemp,"baud=%d parity=N data=8 stop=1 ",baud);
		BuildCommDCB(InitTemp,&dcb);
		SetCommState(hCommDev[ComPort],&dcb);
		memset(&CommTimeOuts,0,sizeof(CommTimeOuts));
		CommTimeOuts.ReadIntervalTimeout=MAXDWORD;
		CommTimeOuts.WriteTotalTimeoutMultiplier = 5;
		CommTimeOuts.WriteTotalTimeoutConstant = 50;	  
		SetCommTimeouts(hCommDev[ComPort],&CommTimeOuts);
		PurgeComm(hCommDev[ComPort],PURGE_TXABORT);//清空输入缓冲区
		PurgeComm(hCommDev[ComPort],PURGE_RXABORT);//清空输出缓冲区
		PurgeComm(hCommDev[ComPort],PURGE_TXCLEAR);//结束所有写操做
		PurgeComm(hCommDev[ComPort],PURGE_RXCLEAR);//结束所有读操做		

	return(0);
}
/**************************************************/
/*    Declare : 关闭串口                           */
/*    Input :ComPort ——串口号                    */
/*    Output:                                     */
/*       0——成功                                 */
/*       -7——错误                                */
/**************************************************/
int  CloseCom(int ComPort)
{
	if(hCommDev[ComPort]!=INVALID_HANDLE_VALUE)
	{
		if(!CloseHandle(hCommDev[ComPort]))
			return -7;
	}	
	return 0;
}

/**************************************************/
/*    Declare : 按照SmartCom411格式整理数据包     */
/*    Input :								      */
/*       Machine: 机号                            */
/*       Commandbyte： 命令字                     */
/*       PacketBuffer：输出的数据包               */
/*       PacketLen：输出的数据包长度              */
/*    Output:                                     */
/*       Targetbuffer——整理好的数据包           */
/*       返回欲发送的数据包的长度		          */
/**************************************************/
int	 PrepareBytes(int Machine,unsigned char Commandbyte,unsigned char *SourceBuffer,int *len,unsigned char *Targetbuffer)
{
    int Slen;
	unsigned short crc16;
	
	if(*len>248 || *len <0)
		return(-1);
    	
	Targetbuffer[0]=STX1;
	Targetbuffer[1]=(unsigned char)Machine;
	Targetbuffer[2]=Commandbyte;
	Targetbuffer[3]=(unsigned char)(*len)%256;
	Slen=*len+4;

	if(*len>0)
	   memcpy(Targetbuffer+4,SourceBuffer,*len);

	crc16=calc_crc16(Slen,Targetbuffer);
	
	Targetbuffer[Slen]=(unsigned char)(crc16>>8);
	Slen++;
	Targetbuffer[Slen]=(unsigned char)crc16;
    Slen++;
	Targetbuffer[Slen]=ETX1;
	
	return(*len+7);
}
/**************************************************/
/*    Declare : 向串口输出指定数据长度的数据包    */
/*    Input :								      */
/*       ComPort ——串口号                       */
/*       PacketBuffer：输出的数据包               */
/*       PacketLen：输出的数据包长度              */
/*    Output:                                     */
/*       0——成功                                */
/*       -3——发送错误                           */
/**************************************************/
int	 SendBytes(int ComPort,unsigned char *PacketBuffer,int PacketLen)
{
	DWORD	BytesWritten=0;
	DWORD	WrittingLen,total_write_len;
	BOOL	bReturn;
	DWORD	dwEvent;
	unsigned char	*buffer;
	
			/*  Send text  */
			EscapeCommFunction(hCommDev[ComPort],SETDTR);
			SetCommMask(hCommDev[ComPort],EV_TXEMPTY);
			PurgeComm(hCommDev[ComPort],PURGE_TXCLEAR);//added by liyongdong
			PurgeComm(hCommDev[ComPort],PURGE_RXCLEAR);//added by liyongdong
			buffer = PacketBuffer;
			WrittingLen = PacketLen;
			total_write_len=0;
    		do{
		   		BytesWritten=0;
     			bReturn=WriteFile(hCommDev[ComPort],buffer,WrittingLen, &BytesWritten,NULL);
				if (!bReturn){
					return(-3);
				}
				else{
				total_write_len += BytesWritten;
				buffer += BytesWritten;
				WrittingLen -= BytesWritten;
				}
			} while (total_write_len<(DWORD)PacketLen);
			WaitCommEvent(hCommDev[ComPort],&dwEvent,NULL);	
			return(0);
}


int  ModemDial(int ComPort,unsigned char* DialString,int length)
{
	
	if(hCommDev[ComPort]!=INVALID_HANDLE_VALUE)
	{
//		 DWORD dwMask = EV_CTS;
//		 SetCommMask(hCommDev[ComPort],dwMask);
         EscapeCommFunction(hCommDev[ComPort],SETDTR);
         EscapeCommFunction(hCommDev[ComPort],SETRTS);
// WaitCommEvent(hCommDev[ComPort],&dwMask,NULL);
		 if (SendBytes(ComPort,DialString,length) != 0)
		 {
            return -1; //发送拨号命令出错
		 }
		 else
		 {
			return 0;  //发送拨号命令成功
		 }
	}
	else
	{
		return -1; //串口还没有打开
	}
}

/**************************************************/
/* Declare : 检测拨号连接是否已建立 
入口参数：
ComPort: 串口
MaxWaitTime：最大建立连接的等待时间

返回值：
成功：返回1
失败：
-2:接收数据错
-6:终端无反应
*****************************************************/

int  CheckModemLink(int ComPort,int MaxWaitTime)
{
	DWORD	StartTime,EndTime;
        DWORD	dwModemStat=0;
	int WaitTime;   
	
	StartTime = GetTickCount();
	do{

        GetCommModemStatus(hCommDev[ComPort],&dwModemStat);

		EndTime=GetTickCount();
		WaitTime = EndTime - StartTime;
		if(WaitTime > MaxWaitTime) 
		{	
			return (-6);
		}
		Sleep(100);

	}while(!(dwModemStat & MS_RLSD_ON));

	return 1;  //连接已建立

}


/**************************************************/
/* Declare : 从串口读入符合SmartCom411格式数据包 
入口参数：
ComPort: 串口
waitforstx2：等待STX2（0xC2）返回的时间
_WaitTime：连续两字节之间的等待时间
出口参数：
RecBuffer：读出的数据
返回值：
成功：返回读出数据包长度
失败：
-2:接收数据错
-4:接收数据超时;
-6:终端无反应
-9：数据校验错误
*****************************************************/

int	 ReceiveBytes (int ComPort,int waitforstx2,int _WaitTime,unsigned char *RecBuffer)
{	
	DWORD	StartTime;
	DWORD	EndTime;
	int	    WaitTime;
	unsigned char *buffer;
	unsigned short crc16;
	unsigned char Crc1,Crc2;
	// modified
	int     WaitForSTX2Time;	
	WaitForSTX2Time=waitforstx2;    
	int		pack_len,PacketLen;
	DWORD	BytesRead=0,nToRead=0;
	BOOL	bReturn;
    //  receive text 
	StartTime = GetTickCount();
	buffer = RecBuffer;
    buffer++;
	//OVERLAPPED ov;
    //wait for start of text flag -- STX 
	do{
		*RecBuffer = (char)NULL;
		bReturn = ReadFile(hCommDev[ComPort],RecBuffer,1,&BytesRead,NULL);
		if (bReturn == FALSE)
		{			
			return (-2);
		}
		EndTime=GetTickCount();
		WaitTime = EndTime - StartTime;
		if(WaitTime > WaitForSTX2Time) 
		{	
			return (-6);
		}
	}while(*RecBuffer!=STX2);   	
		
	StartTime = GetTickCount();
	pack_len = 3;		
    while (pack_len>0){
		  bReturn = ReadFile(hCommDev[ComPort],buffer,1,&BytesRead,NULL);
		  if(bReturn == FALSE)
		  {		
			return (-2);
		  }
   		  buffer += BytesRead;
    	  pack_len -= BytesRead;
  		  EndTime=GetTickCount();
		  WaitTime = EndTime - StartTime;
		  if(WaitTime > _WaitTime) 
		  {			
				return (-4);
		  }
	}
	buffer--;
    pack_len = *buffer;	
    buffer ++;
        
    pack_len += 3;
	StartTime = GetTickCount();
    while (pack_len>0) {
     	    bReturn = ReadFile(hCommDev[ComPort],buffer,1,&BytesRead,NULL);
			if(bReturn == FALSE)
			{
					return (-2);
			}
			buffer += BytesRead;
	        pack_len -= BytesRead;
		    EndTime=GetTickCount();
		    WaitTime = EndTime - StartTime;
		    if(WaitTime > _WaitTime) 
			{	
			  return (-4);
			}
	}
    *buffer-- = (char)NULL;
    
	if (*buffer!=ETX2) {		
			return(-2);
	}
	
	buffer++;   
	PacketLen = buffer-RecBuffer;
	
	crc16=calc_crc16(PacketLen-3,RecBuffer);
    
	Crc1=(unsigned char)(crc16>>8);	
	Crc2=(unsigned char)crc16;	
    

	if((Crc1!=RecBuffer[PacketLen-3]) ||(Crc2!=RecBuffer[PacketLen-2])) 
    {
		return(-9);    //数据校验CRC错误
	}

	return(PacketLen);
}
/*****************************************************
 Declare : 检查从通信口读入数据包是否符合SmartCom411格式
入口参数：
SourceBuffer: 欲检查数据包

返回值：
成功：返回读出数据包真实长度
失败：
-2:接收数据错
-9：数据校验错误
*****************************************************/
int	 CheckBytes (unsigned char *SourceBuffer)
{	
	unsigned short crc16;
	unsigned char Crc1,Crc2;	
	
	if (SourceBuffer[0]!=STX2) { //起始符错误	
			return (-2);
	}

	int crc_len=SourceBuffer[3]+4;  //参加校验的数据包长度

	crc16=calc_crc16(crc_len,SourceBuffer);	
	Crc1=(unsigned char)(crc16>>8);	
	Crc2=(unsigned char)crc16;
   
	if((Crc1!=SourceBuffer[crc_len]) ||(Crc2!=SourceBuffer[crc_len+1])) 
    {
		return(-9);    //数据校验CRC错误
	}

	if (SourceBuffer[crc_len+2]!=ETX2) {	//结束符错误	
		return(-2);
	}	
	return(SourceBuffer[3]+7);
}



/////下面为TCP/IP通信基本函数
//SOCKET	Sock;
//SOCKET is defined as unsigned int data type. 
/*
函数：StartWinSocketEnv()。
功能：启动WinSocket环境。
入口参数：无。
出口参数：无。
返回值：
	0			打开WINSOCK动态库，启动WinSocket环境成功。
	-11			SMART_NOT_FIND_WINSOCK_DLL，没有找到可用的WINSOCK动态库。
*/
int  StartWinSocketEnv()
{
	WORD wMajorVersion,wMinorVersion,VersionReqd;
    WSADATA      wsaData;
	wMajorVersion = 2;
	wMinorVersion = 0;
	VersionReqd = wMinorVersion * 256 + wMajorVersion;
//	lpmyWSAData = (LPWSADATA)malloc(sizeof(WSADATA));
	if(WSAStartup(VersionReqd,&wsaData) != 0){
		return(SMART_NOT_FIND_WINSOCK_DLL);
	}
	
	return(0);
}

/*
函数：CloseWinSocketEnv()。
功能：关闭WinSocket环境。
入口参数：无。
出口参数：无。
返回值：
	0			关闭WinSocket环境成功。
	-12			SMART_CLOSE_WINSOCK_ENV_ERROR，关闭WinSocket环境出错。
*/
int  CloseWinSocketEnv()
{
	if(WSACleanup()==SOCKET_ERROR)
		return(SMART_CLOSE_WINSOCK_ENV_ERROR);
	
	return(0);
}


/*
函数：EstablishConnect(char * IP_Address,int IP_Port,int TimeOut,unsigned int *Sock)
功能：建立WINSOCKET连接
入口参数：
	1、IP_Address，IP地址。如192.168.0.138
	2、IP_Port，建立SOCKET连接的端口号，如4001。
	3、TimeOut，建立SOCKET连接的超时时间，单位ms。
出口参数：
	Sock，成功建立SOCKET连接后返回的SOCKET值。
返回值：
	0		成功建立SOCKET连接。
	-7		SMART_ESTABLISH_CONNECT_TIMEOUT，建立SOCKET连接超时。
	-13		SMART_IP_ADDRESS_ERROR，错误的IP地址。
	-14		SMART_INITIAL_SOCKET_ERROR，初始化SOCKET错。
*/
//在WINDOWS中“SOCKET”被定义为unsigned int数据类型. 
int  EstablishConnect(const char * IP_Address,int IP_Port,int TimeOut,unsigned int *Sock)
{
	int			RetCode;
	struct		sockaddr_in	FAR SockAddr;
	unsigned long		TcpipAddress;
	int	TimeoutFlag = 0;
	int StartTime;
	int EndTime;
	int ConnectTime;
	SOCKET	CurSock;

	TcpipAddress = inet_addr(IP_Address);
	memset(&SockAddr,0,sizeof(struct sockaddr_in));
	if(TcpipAddress != INADDR_NONE)
	{
		memcpy(&SockAddr.sin_addr, (char*)&TcpipAddress, 4);
		SockAddr.sin_family = AF_INET;
		SockAddr.sin_port = htons(IP_Port);
	}
	else {
		return(SMART_IP_ADDRESS_ERROR);	//IP地址错
	}

	if((CurSock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==INVALID_SOCKET)
		return(SMART_INITIAL_SOCKET_ERROR);

	StartTime = GetTickCount();
	while ((RetCode=connect(CurSock, (struct sockaddr FAR *)&SockAddr, sizeof(SockAddr)) )< 0) {
		EndTime=GetTickCount();
		ConnectTime = EndTime - StartTime;
		if(ConnectTime > TimeOut) {
			TimeoutFlag = 1;
			break;
		}
		//closesocket(CurSock);
		//CurSock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	}

	if(TimeoutFlag){
		closesocket(CurSock);
		return(SMART_ESTABLISH_CONNECT_TIMEOUT); //建立WINSOCKET连接
	}

	*Sock = CurSock;
	return(0);
}

/*
函数：CloseConnect(unsigned int Sock)。
功能：关闭Socket连接。
入口参数：无。
出口参数：无。
返回值：
	0		关闭Socket连接成功。
	-8		SMART_CLOSE_SOCKET_ERROR，关闭Socket连接出错。
*/
int  CloseConnect(unsigned int Sock)
{

	shutdown(Sock, SD_BOTH);
	if(closesocket((unsigned int)Sock)==SOCKET_ERROR)
		return(SMART_CLOSE_SOCKET_ERROR);
	return(0);
}
/*
函数：SendData(unsigned int Sock,unsigned char *PacketBuffer,int PacketLen)。
功能：通过连接的Socket发送数据。
入口参数：
	1、Sock，要发送数据的SOCKET。
	2、PacketBuffer，要发送的数据。
	3、PacketLen，发送数据的长度。
出口参数：无。
返回值：
	0		发送数据成功。
	-3		SMART_SEND_DATA_ERROR，发送数据错。
	-16		SMART_CONNECT_BROKEN，WINSOCK连接断裂或虚电路已关闭。
*/
int  SendData(unsigned int Sock,unsigned char *PacketBuffer,int PacketLen)
{
	int	WrittingLen,total_write_len;
	int	BytesWritten=0;
	int RetCode;
	unsigned char	*buffer;

	buffer = PacketBuffer;
	total_write_len=0;

	buffer = PacketBuffer;
	WrittingLen = PacketLen;
	total_write_len=0;
    do{
   		BytesWritten = send(Sock, (char*)buffer, WrittingLen,0);
		if(BytesWritten == SOCKET_ERROR){
			RetCode = WSAGetLastError();
			if(RetCode == WSAENETDOWN || RetCode == WSAENETRESET ||
				RetCode == WSAESHUTDOWN ||RetCode == WSAECONNABORTED ||
				RetCode == WSAETIMEDOUT || RetCode == WSAECONNRESET)
				return (SMART_CONNECT_BROKEN);
			else
				break;
		}			

		total_write_len += BytesWritten;
		buffer += BytesWritten;
		WrittingLen -= BytesWritten;
	}while(total_write_len<PacketLen);

	if(BytesWritten == SOCKET_ERROR)
		return(SMART_SEND_DATA_ERROR);

	return 0;
}

/*
函数：ReceiveData(unsigned int Sock,int WaitForSTX2Time,int NormalWaitTime,unsigned char *PacketBuffer)。
功能：通过连接的Socket接收数据。
入口参数：
	1、Sock，要发送数据的SOCKET。
	2、WaitForSTX2Time，接收数据起始符—0xc2的超时时间。
	3、NormalWaitTime，接收正常数据的超时时间。
	4、PacketBuffer，保存接收的数据。
出口参数：无。
返回值：
	>0		成功接收数据的长度。
	-2		RECEIVE_DATA_ERROR,接收数据错。
	-4		SMART_RECEIVE_DATA_TIMEOUT，接收数据超时。
	-10		SMART_RECEIVE_DATA_PACKET_ERROR，接收数据数据包格式错。
	-15		SMART_CONNECT_CLOSED，WINSOCK连接已关闭。
	-16		SMART_CONNECT_BROKEN，WINSOCK连接断裂或虚电路已关闭。
*/
int  ReceiveData(unsigned int Sock,int WaitForSTX2Time,int NormalWaitTime,unsigned char *PacketBuffer)
{
	DWORD	WaitTime,StartTime,EndTime;
	unsigned char	*buffer;
    int		pack_len,PacketLen;
	int		BytesRead=0;
	int		RetCode,timeoutflag;
	unsigned short crc16;
	unsigned char Crc1,Crc2;
	unsigned long FAR ap = 1;

	/*  receive data  */
	*PacketBuffer = 0;
    buffer = PacketBuffer;
    buffer++;
	ioctlsocket(Sock,FIONBIO,&ap);
	timeoutflag = 0;
	StartTime = GetTickCount();

	//检查是否有数据可接收
	while(1)
	{
		RetCode = recvfrom(Sock,
			           (char*)PacketBuffer,
					   256,
					   MSG_PEEK,
					   (struct sockaddr FAR *)NULL,
					   (int*)NULL);
		if(RetCode>0)
			break;
		if (RetCode == 0)
			return(SMART_CONNECT_CLOSED);
		if (RetCode == SOCKET_ERROR){
			RetCode = WSAGetLastError();
			if(RetCode == WSAENETDOWN || RetCode == WSAENETRESET ||
				RetCode == WSAESHUTDOWN ||RetCode == WSAECONNABORTED ||
				RetCode == WSAETIMEDOUT || RetCode == WSAECONNRESET)
			return (SMART_CONNECT_BROKEN);
		}

		EndTime=GetTickCount();
		WaitTime = EndTime - StartTime;
		if((int)WaitTime > WaitForSTX2Time) 
		{
			timeoutflag=1;
			break;
		}
	}

	if(timeoutflag)
		return(SMART_TERMINAL_NO_RESPONSE);

	*PacketBuffer = 0;

	//接收数据
    /*  wait for start of text flag -- STX2  */	
	do{
		*PacketBuffer = (char)NULL;
		RetCode = recv(Sock,(char*)PacketBuffer,1,0);
		if (RetCode == 0)
			return(SMART_CONNECT_CLOSED);
		if (RetCode == SOCKET_ERROR){
			RetCode = WSAGetLastError();
			if(RetCode == WSAENETDOWN || RetCode == WSAENETRESET ||
				RetCode == WSAESHUTDOWN ||RetCode == WSAECONNABORTED ||
				RetCode == WSAETIMEDOUT || RetCode == WSAECONNRESET)
			return (SMART_CONNECT_BROKEN);
		}
	
		EndTime=GetTickCount();
		WaitTime = EndTime - StartTime;
		if((int)WaitTime > WaitForSTX2Time) 
		{
			timeoutflag=1;
			break;
		}

	}while(*PacketBuffer!=STX2); 

	if(timeoutflag)
		return(SMART_TERMINAL_NO_RESPONSE);
	
	
	if(*PacketBuffer!=STX2){
		/*读数据超时*/
		return(SMART_TERMINAL_NO_RESPONSE);
	}

	pack_len = 3;
	StartTime = GetTickCount();
    while (pack_len>0)
	{
		BytesRead = recv(Sock,(char*)buffer,pack_len,0);
		if (BytesRead == 0)
			return(SMART_CONNECT_CLOSED);
		if (BytesRead == SOCKET_ERROR){
			RetCode = WSAGetLastError();
			if(RetCode == WSAENETDOWN || RetCode == WSAENETRESET ||
				RetCode == WSAESHUTDOWN ||RetCode == WSAECONNABORTED ||
				RetCode == WSAETIMEDOUT || RetCode == WSAECONNRESET)
				return (SMART_CONNECT_BROKEN);
		}

		if(BytesRead>0){			
			buffer += BytesRead;
    		pack_len -= BytesRead;
		}
		if(pack_len==0)
			break;
  		EndTime=GetTickCount();
		WaitTime = EndTime - StartTime;
		if((int)WaitTime > NormalWaitTime) 
			break;
	}

	if((int)WaitTime > NormalWaitTime){
		/*读数据超时*/
		return(SMART_RECEIVE_DATA_TIMEOUT);
	}

	buffer--;
    pack_len = *buffer;
    buffer ++;
    /*  Add CRC1,CRC2 and ETX2 */
    pack_len += 3;
    while (pack_len>0)
	{
		BytesRead = recv(Sock,(char*)buffer,pack_len,0);
		if (BytesRead == 0)
			return(SMART_CONNECT_CLOSED);
		if (BytesRead == SOCKET_ERROR){
			RetCode = WSAGetLastError();
			if(RetCode == WSAENETDOWN || RetCode == WSAENETRESET ||
				RetCode == WSAESHUTDOWN ||RetCode == WSAECONNABORTED ||
				RetCode == WSAETIMEDOUT || RetCode == WSAECONNRESET)
				return (SMART_CONNECT_BROKEN);
		}

		if(BytesRead>0){			
			buffer += BytesRead;
    		pack_len -= BytesRead;
		}
		if(pack_len==0)
			break;

  		EndTime=GetTickCount();
		WaitTime = EndTime - StartTime;
		if((int)WaitTime > NormalWaitTime) 
				break;
	}

	if((int)WaitTime > NormalWaitTime){
		/*读数据超时*/
		return(SMART_RECEIVE_DATA_TIMEOUT);
	}

	*buffer-- = (char)NULL;
    if (*buffer!=ETX2)
	{
		return(SMART_RECEIVE_DATA_PACKET_ERROR);
    }

    buffer++;   
    PacketLen = buffer-PacketBuffer;
	
	
	crc16=calc_crc16(PacketLen-3,PacketBuffer);
    
	Crc1=(unsigned char)(crc16>>8);	
	Crc2=(unsigned char)crc16;	
    
	
	if((Crc1!=PacketBuffer[PacketLen-3]) ||(Crc2!=PacketBuffer[PacketLen-2])) 
    {
		return(-9);    //数据校验CRC错误
	}
	
	//PacketBuffer[PacketLen-3]=Crc1;
	//PacketBuffer[PacketLen-2]=Crc2;
    
	return(PacketLen);
}

/*
函数：DirectReceiveData(unsigned int Sock,unsigned char *PacketBuffer)。
功能：通过连接的Socket接收数据。
入口参数：
	1、Sock，要发送数据的SOCKET。
	2、PacketBuffer，保存接收的数据。
出口参数：无。
返回值：
	>0		成功接收数据的长度。
	-2		RECEIVE_DATA_ERROR,接收数据错。
	-4		SMART_RECEIVE_DATA_TIMEOUT，接收数据超时。
	-10		SMART_RECEIVE_DATA_PACKET_ERROR，接收数据数据包格式错。
	-15		SMART_CONNECT_CLOSED，WINSOCK连接已关闭。
	-16		SMART_CONNECT_BROKEN，WINSOCK连接断裂或虚电路已关闭。
*/
int  DirectReceiveData(unsigned int nCommPort,unsigned char *PacketBuffer,int nCommType)
{	
	unsigned char	*buffer;
    int		PacketLen;
	int		BytesRead=0;
	int		RetCode;	
	switch(nCommType) {
	case COMM_TCP:
		unsigned long FAR ap;
		ap=1;
		
		buffer = PacketBuffer;    
		ioctlsocket(nCommPort,FIONBIO,&ap);
		
		//接收数据
		BytesRead = 0;
		
		//BytesRead = recv(nCommPort,(char*)buffer,500,0);
		BytesRead = recv(nCommPort,(char*)buffer,512,0);		
		if (BytesRead == 0)
			return(SMART_CONNECT_CLOSED);
		if (BytesRead == SOCKET_ERROR){
			RetCode = WSAGetLastError();
			if(RetCode == WSAENETDOWN || RetCode == WSAENETRESET ||
				RetCode == WSAESHUTDOWN ||RetCode == WSAECONNABORTED ||
				RetCode == WSAETIMEDOUT || RetCode == WSAECONNRESET)
				return (SMART_CONNECT_BROKEN);
		}
		
		if(BytesRead>0){			
			buffer += BytesRead;
		}

		*buffer-- = (char)NULL;
		buffer++;
		PacketLen = buffer-PacketBuffer;
		break;
	case COMM_UDP:
		SOCKADDR_IN addrFrom;
		int len,retval;
		len = sizeof(SOCKADDR);
		
		//retval=recvfrom(nCommPort,(char*)PacketBuffer,500,0,(SOCKADDR*)&addrFrom,&len);
		retval=recvfrom(nCommPort,(char*)PacketBuffer,512,0,(SOCKADDR*)&addrFrom,&len);
		if(SOCKET_ERROR==retval)
		{
			return SMART_RECEIVE_DATA_TIMEOUT;  //接收数据超时
		}
		PacketLen = retval;
		break;
	case COMM_COM:
	case COMM_MODEM:
		DWORD	BytesRead=0;
		BOOL	bReturn;
		//bReturn = ReadFile(hCommDev[nCommPort],PacketBuffer,500,&BytesRead,NULL);
		bReturn = ReadFile(hCommDev[nCommPort],PacketBuffer,512,&BytesRead,NULL);
		if (bReturn == FALSE)
		{			
			return (-2);
		}
		PacketLen = BytesRead;
		break;	
	}
	return(PacketLen);
}


/*
函数：int BindPort(char* IP_Address,int IP_Port,unsigned int *Sock)
功能：绑定指定的网络端口
入口参数：
1、IP_Address，待绑定的IP地址。如"192.168.5.29"
2、IP_Port，   待绑定的端口号，如4001。
出口参数：
Sock，绑定成功后，返回的套接字值。
返回值：
0		绑定成功。
-13		SMART_IP_ADDRESS_ERROR，错误的IP地址。
-14		SMART_INITIAL_SOCKET_ERROR，初始化SOCKET错。
*/
int  BindPort(const char* IP_Address,int IP_Port,unsigned int *Sock)
{
	SOCKET	m_socket;
    SOCKADDR_IN addrSock;
    
	addrSock.sin_family=AF_INET;
	addrSock.sin_port=htons(IP_Port);
	addrSock.sin_addr.S_un.S_addr=inet_addr(IP_Address);

	m_socket=socket(AF_INET,SOCK_DGRAM,0);

	if(INVALID_SOCKET==m_socket)
	{
         return(SMART_INITIAL_SOCKET_ERROR);  //初始化SOCKET错
	}

    int retval;
	retval=bind(m_socket,(SOCKADDR*)&addrSock,sizeof(SOCKADDR));
	if(SOCKET_ERROR==retval)
	{
		int ErrorCode=WSAGetLastError();
		closesocket(m_socket);
	//	return(SMART_INITIAL_SOCKET_ERROR);  //初始化SOCKET错
		return ErrorCode;
	}
    *Sock = m_socket;
	return 0;
}

/*
函数：SendUDPData(unsigned int Sock,const char* IP_Address,int IP_Port,unsigned char *PacketBuffer,int PacketLen)。
功能：通过绑定的Socket发送UDP数据。
入口参数：
1、Sock， 要发送数据的SOCKET。
2、IP_Address，待发送的IP地址。如"192.168.5.30"
3、IP_Port，   待绑定的端口号，如4001。
4、PacketBuffer，要发送的数据。
5、PacketLen，发送数据的长度。
出口参数：无。
返回值：
0		发送数据成功。
-3		SMART_SEND_DATA_ERROR，发送数据错。
-13		SMART_IP_ADDRESS_ERROR，错误的IP地址。
*/
int  SendUDPData(unsigned int Sock,const char* IP_Address,int IP_Port,unsigned char *PacketBuffer,int PacketLen)
{

	int RetCode;
    SOCKADDR_IN addrTo;
	if(PacketLen <= 0 )
	{
		return 0;   //没有数据要发送
	}

	addrTo.sin_family=AF_INET;
	addrTo.sin_port=htons(IP_Port); //转化成网络字节序
	addrTo.sin_addr.S_un.S_addr=inet_addr(IP_Address); //转化成网络字节序

	RetCode=sendto(Sock,(const char*)PacketBuffer,PacketLen,0,(SOCKADDR*)&addrTo,sizeof(SOCKADDR)); //发送UDP数据包


	if(RetCode>0)
		return 0; //发送数据成功
	else
	    return SMART_SEND_DATA_ERROR; //发送数据错。

}

//RecvUDPData

/*
函数：RecvUDPData(unsigned int Sock,int WaitForSTX2Time,int NormalWaitTime,unsigned char *PacketBuffer)。
功能：通过连接的Socket接收数据。
入口参数：
	1、Sock，要发送数据的SOCKET。
	2、WaitForSTX2Time，接收数据起始符—0xc2的超时时间。
	3、WaitForSTX2Time，接收正常数据的超时时间。
	4、PacketBuffer，保存接收的数据。
出口参数：无。
返回值：
	>0		成功接收数据的长度。
	-9		RECEIVE_DATA_ERROR,接收数据错。
	-4		SMART_RECEIVE_DATA_TIMEOUT，接收数据超时。
	-10		SMART_RECEIVE_DATA_PACKET_ERROR，接收数据数据包格式错。
*/
int  RecvUDPData(unsigned int Sock,int WaitForSTX2Time,int NormalWaitTime,unsigned char *PacketBuffer,int bufLen)
{

	unsigned short crc16;
	unsigned char Crc1,Crc2;
    SOCKADDR_IN addrFrom;
	int len = sizeof(SOCKADDR);

    //	设置超时
	int rcvtimeo = WaitForSTX2Time+NormalWaitTime ; 

	if( setsockopt( Sock , SOL_SOCKET , SO_RCVTIMEO , (const char *)&rcvtimeo , sizeof(rcvtimeo) ) == SOCKET_ERROR)
	{
		return SMART_RECEIVE_DATA_TIMEOUT;
	}

	int retval=recvfrom(Sock,(char*)PacketBuffer,bufLen,0,(SOCKADDR*)&addrFrom,&len);
	if(retval>0)
	{
        if(PacketBuffer[0]!=STX2)
			return(SMART_RECEIVE_DATA_PACKET_ERROR);  //数据格式错误
	}
	int totalLen=retval;
	int packetLen=100000;	 
	//判断接收数据是否完整，不完整继续接收
	while(retval>0)
	{
        if(totalLen>=4)
		{
			packetLen=*(BYTE*)(PacketBuffer+3)+7;  	   
		}
	   if(totalLen>=packetLen)
		   break;
	   retval=recvfrom(Sock,(char*)(PacketBuffer+totalLen),bufLen-totalLen,0,(SOCKADDR*)&addrFrom,&len);
	   if(retval>0)
	        totalLen+=retval;
	}

	if(SOCKET_ERROR==retval||0==retval)
    {
		//	TRACE("WSAGetLastError=%d\n",WSAGetLastError());
        return SMART_RECEIVE_DATA_TIMEOUT;  //接收数据超时
		
    }
    else //数据接收成功
	{
		if(PacketBuffer[0]!=STX2 || PacketBuffer[totalLen-1]!=ETX2)
		{
			return(SMART_RECEIVE_DATA_PACKET_ERROR);  //数据格式错误
		}

		//CRC校验
		crc16=calc_crc16(totalLen-3,PacketBuffer);
		
		Crc1=(unsigned char)(crc16>>8);	
		Crc2=(unsigned char)crc16;	
		
		if((Crc1!=PacketBuffer[totalLen-3]) ||(Crc2!=PacketBuffer[totalLen-2])) 
		{
			return(-9);    //数据校验CRC错误
		}
		
		return(totalLen);
		
	}

}



/*
函数：CloseUDPSocketEnv(unsigned int sock)
功能：关闭Sock 和 WinSocket环境。
入口参数：待关闭的sock描述符。
出口参数：无。
返回值：
	0			关闭Sock 和 WinSocket环境。
	-12			SMART_CLOSE_WINSOCK_ENV_ERROR，关闭WinSocket环境出错。
*/

int  CloseUDPSocketEnv(unsigned int sock)
{
   
    if(sock)
	{
      if(SOCKET_ERROR==closesocket(sock))
	  {
		  return SMART_CLOSE_WINSOCK_ENV_ERROR;
	  }

	}
	if(WSACleanup()==SOCKET_ERROR)
		return(SMART_CLOSE_WINSOCK_ENV_ERROR);
	
	return(0);
}


int  CloseUDPSocket(unsigned int sock)
{
    if(sock)
	{
      if(SOCKET_ERROR==closesocket(sock))
	  {
		  return SMART_CLOSE_WINSOCK_ENV_ERROR;
	  }
 
	}
    return 0;
}

/*
函数：GetOneLocalSocket(unsigned int * socket)
功能：获得一个本地主机的SOCK,用于发送和接受UDP包
入口参数：
出口参数：新得到的Sock。
返回值：
	0        执行成功	   
	<0 		 执行失败
*/


int GetOneLocalSocket(unsigned int * socket,int srcPort)   
{
   
   //成功返回true , 失败返回false
     int port = srcPort;   
	 int ret = -1;
	 
	 char strIP[20];
	 strIP[0]=0;
     //获得网卡数据
     PIP_ADAPTER_INFO pInfo=NULL;
     ULONG ulSize=0;
      
     GetAdaptersInfo(pInfo,&ulSize);//第一次调用，获取缓冲区大小
	 if (ulSize == 0 ) {
		 return -3; //网络连接不存在
	 }
     pInfo=(PIP_ADAPTER_INFO)new(char[ulSize]);
     GetAdaptersInfo(pInfo,&ulSize);
     
     //遍历每一张网卡
     while(pInfo)
     {
		 if (pInfo->Type == MIB_IF_TYPE_ETHERNET) //如果是PPP类型
		 {
			 strcpy(strIP,pInfo->IpAddressList.IpAddress.String);//获取GPRS连接的IP地址
			 break;
		 }
         //将当前指针移向下一个
         pInfo=pInfo->Next;
     }
     if (0==strIP[0])
	 {  
		 socket=0;
		 return -1; //GPRS连接不存在
	 }
	 
    ret=BindPort(strIP,port,socket); 
    if(ret<0)
	{
			 socket=0;
			 return -2;  //绑定失败
	 }
	 
	 return 0;


}