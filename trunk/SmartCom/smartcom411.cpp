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

unsigned int crctab[256]=  //calc_crc16 ������
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

/************ calc_crc16 ���*************/
void crcupdata(unsigned char in,unsigned short *accum,unsigned int *crctab)
{
	*accum=(*accum<<8)^crctab[(*accum>>8)^in];
}
/*  len: У�����ݳ��� */
/*  in:  У�����ݰ��� */
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

//SVC_DSP_2_HEX��SVC_HEX_2_DSPΪʮ������������ASSCII����ת��������

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

///********���ڲ�������start********//
//******************************************/
/* Declare:��ʼ�����ڣ��򿪴���            */
/* Input :                                 */ 
/*    ComPort  ���ں�(1��2��3��4)          */
/*    BaudRate �����ʴ���			       */
/*        0-----19200                      */
/*        1-----9600                       */
/*        2-----4800                        */
/*        3-----2400                       */
/*        4-----1200                       */
/*        5-----28800	                   */			
/*	      6-----57600	                   */	
/*	      7-----115200                      */
/*	      Ĭ��--19200                      */
/* return:                                 */
/*   0�����ɹ�   -7 ---- ���ɹ�            */ 		
////////////////////////////////////////////
int  IniCom(int ComPort,int BaudRate)
{
	int		baud;
	DCB		dcb;
	char	InitTemp[80];
	char	CommName[10];
	COMMTIMEOUTS CommTimeOuts;

    //��׼ͨ�ſ�	
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

	//ͨ����׼ͨ�ſ�

		sprintf(CommName,"\\\\?\\COM%d",ComPort);
		hCommDev[ComPort]= CreateFile 
		(
		  CommName,
		  GENERIC_READ|GENERIC_WRITE, //dwDesiredAccess
		  0,     //dwShareModeΨһ����
		  NULL,  //lpSecurityAttributes
		  OPEN_EXISTING,	//��COM���Ѵ���,��ΪOPEN_EXISTING//dwCreationDistribution	  
		  //0,   //dwFlagsAndAttributes
		  FILE_ATTRIBUTE_NORMAL,//dwFlagsAndAttributes
		  NULL  //����ΪNULL
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
		PurgeComm(hCommDev[ComPort],PURGE_TXABORT);//������뻺����
		PurgeComm(hCommDev[ComPort],PURGE_RXABORT);//������������
		PurgeComm(hCommDev[ComPort],PURGE_TXCLEAR);//��������д����
		PurgeComm(hCommDev[ComPort],PURGE_RXCLEAR);//�������ж�����		

	return(0);
}
/**************************************************/
/*    Declare : �رմ���                           */
/*    Input :ComPort �������ں�                    */
/*    Output:                                     */
/*       0�����ɹ�                                 */
/*       -7��������                                */
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
/*    Declare : ����SmartCom411��ʽ�������ݰ�     */
/*    Input :								      */
/*       Machine: ����                            */
/*       Commandbyte�� ������                     */
/*       PacketBuffer����������ݰ�               */
/*       PacketLen����������ݰ�����              */
/*    Output:                                     */
/*       Targetbuffer��������õ����ݰ�           */
/*       ���������͵����ݰ��ĳ���		          */
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
/*    Declare : �򴮿����ָ�����ݳ��ȵ����ݰ�    */
/*    Input :								      */
/*       ComPort �������ں�                       */
/*       PacketBuffer����������ݰ�               */
/*       PacketLen����������ݰ�����              */
/*    Output:                                     */
/*       0�����ɹ�                                */
/*       -3�������ʹ���                           */
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
            return -1; //���Ͳ����������
		 }
		 else
		 {
			return 0;  //���Ͳ�������ɹ�
		 }
	}
	else
	{
		return -1; //���ڻ�û�д�
	}
}

/**************************************************/
/* Declare : ��Ⲧ�������Ƿ��ѽ��� 
��ڲ�����
ComPort: ����
MaxWaitTime����������ӵĵȴ�ʱ��

����ֵ��
�ɹ�������1
ʧ�ܣ�
-2:�������ݴ�
-6:�ն��޷�Ӧ
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

	return 1;  //�����ѽ���

}


/**************************************************/
/* Declare : �Ӵ��ڶ������SmartCom411��ʽ���ݰ� 
��ڲ�����
ComPort: ����
waitforstx2���ȴ�STX2��0xC2�����ص�ʱ��
_WaitTime���������ֽ�֮��ĵȴ�ʱ��
���ڲ�����
RecBuffer������������
����ֵ��
�ɹ������ض������ݰ�����
ʧ�ܣ�
-2:�������ݴ�
-4:�������ݳ�ʱ;
-6:�ն��޷�Ӧ
-9������У�����
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
		return(-9);    //����У��CRC����
	}

	return(PacketLen);
}
/*****************************************************
 Declare : ����ͨ�ſڶ������ݰ��Ƿ����SmartCom411��ʽ
��ڲ�����
SourceBuffer: ��������ݰ�

����ֵ��
�ɹ������ض������ݰ���ʵ����
ʧ�ܣ�
-2:�������ݴ�
-9������У�����
*****************************************************/
int	 CheckBytes (unsigned char *SourceBuffer)
{	
	unsigned short crc16;
	unsigned char Crc1,Crc2;	
	
	if (SourceBuffer[0]!=STX2) { //��ʼ������	
			return (-2);
	}

	int crc_len=SourceBuffer[3]+4;  //�μ�У������ݰ�����

	crc16=calc_crc16(crc_len,SourceBuffer);	
	Crc1=(unsigned char)(crc16>>8);	
	Crc2=(unsigned char)crc16;
   
	if((Crc1!=SourceBuffer[crc_len]) ||(Crc2!=SourceBuffer[crc_len+1])) 
    {
		return(-9);    //����У��CRC����
	}

	if (SourceBuffer[crc_len+2]!=ETX2) {	//����������	
		return(-2);
	}	
	return(SourceBuffer[3]+7);
}



/////����ΪTCP/IPͨ�Ż�������
//SOCKET	Sock;
//SOCKET is defined as unsigned int data type. 
/*
������StartWinSocketEnv()��
���ܣ�����WinSocket������
��ڲ������ޡ�
���ڲ������ޡ�
����ֵ��
	0			��WINSOCK��̬�⣬����WinSocket�����ɹ���
	-11			SMART_NOT_FIND_WINSOCK_DLL��û���ҵ����õ�WINSOCK��̬�⡣
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
������CloseWinSocketEnv()��
���ܣ��ر�WinSocket������
��ڲ������ޡ�
���ڲ������ޡ�
����ֵ��
	0			�ر�WinSocket�����ɹ���
	-12			SMART_CLOSE_WINSOCK_ENV_ERROR���ر�WinSocket��������
*/
int  CloseWinSocketEnv()
{
	if(WSACleanup()==SOCKET_ERROR)
		return(SMART_CLOSE_WINSOCK_ENV_ERROR);
	
	return(0);
}


/*
������EstablishConnect(char * IP_Address,int IP_Port,int TimeOut,unsigned int *Sock)
���ܣ�����WINSOCKET����
��ڲ�����
	1��IP_Address��IP��ַ����192.168.0.138
	2��IP_Port������SOCKET���ӵĶ˿ںţ���4001��
	3��TimeOut������SOCKET���ӵĳ�ʱʱ�䣬��λms��
���ڲ�����
	Sock���ɹ�����SOCKET���Ӻ󷵻ص�SOCKETֵ��
����ֵ��
	0		�ɹ�����SOCKET���ӡ�
	-7		SMART_ESTABLISH_CONNECT_TIMEOUT������SOCKET���ӳ�ʱ��
	-13		SMART_IP_ADDRESS_ERROR�������IP��ַ��
	-14		SMART_INITIAL_SOCKET_ERROR����ʼ��SOCKET��
*/
//��WINDOWS�С�SOCKET��������Ϊunsigned int��������. 
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
		return(SMART_IP_ADDRESS_ERROR);	//IP��ַ��
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
		return(SMART_ESTABLISH_CONNECT_TIMEOUT); //����WINSOCKET����
	}

	*Sock = CurSock;
	return(0);
}

/*
������CloseConnect(unsigned int Sock)��
���ܣ��ر�Socket���ӡ�
��ڲ������ޡ�
���ڲ������ޡ�
����ֵ��
	0		�ر�Socket���ӳɹ���
	-8		SMART_CLOSE_SOCKET_ERROR���ر�Socket���ӳ���
*/
int  CloseConnect(unsigned int Sock)
{

	shutdown(Sock, SD_BOTH);
	if(closesocket((unsigned int)Sock)==SOCKET_ERROR)
		return(SMART_CLOSE_SOCKET_ERROR);
	return(0);
}
/*
������SendData(unsigned int Sock,unsigned char *PacketBuffer,int PacketLen)��
���ܣ�ͨ�����ӵ�Socket�������ݡ�
��ڲ�����
	1��Sock��Ҫ�������ݵ�SOCKET��
	2��PacketBuffer��Ҫ���͵����ݡ�
	3��PacketLen���������ݵĳ��ȡ�
���ڲ������ޡ�
����ֵ��
	0		�������ݳɹ���
	-3		SMART_SEND_DATA_ERROR���������ݴ�
	-16		SMART_CONNECT_BROKEN��WINSOCK���Ӷ��ѻ����·�ѹرա�
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
������ReceiveData(unsigned int Sock,int WaitForSTX2Time,int NormalWaitTime,unsigned char *PacketBuffer)��
���ܣ�ͨ�����ӵ�Socket�������ݡ�
��ڲ�����
	1��Sock��Ҫ�������ݵ�SOCKET��
	2��WaitForSTX2Time������������ʼ����0xc2�ĳ�ʱʱ�䡣
	3��NormalWaitTime�������������ݵĳ�ʱʱ�䡣
	4��PacketBuffer��������յ����ݡ�
���ڲ������ޡ�
����ֵ��
	>0		�ɹ��������ݵĳ��ȡ�
	-2		RECEIVE_DATA_ERROR,�������ݴ�
	-4		SMART_RECEIVE_DATA_TIMEOUT���������ݳ�ʱ��
	-10		SMART_RECEIVE_DATA_PACKET_ERROR�������������ݰ���ʽ��
	-15		SMART_CONNECT_CLOSED��WINSOCK�����ѹرա�
	-16		SMART_CONNECT_BROKEN��WINSOCK���Ӷ��ѻ����·�ѹرա�
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

	//����Ƿ������ݿɽ���
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

	//��������
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
		/*�����ݳ�ʱ*/
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
		/*�����ݳ�ʱ*/
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
		/*�����ݳ�ʱ*/
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
		return(-9);    //����У��CRC����
	}
	
	//PacketBuffer[PacketLen-3]=Crc1;
	//PacketBuffer[PacketLen-2]=Crc2;
    
	return(PacketLen);
}

/*
������DirectReceiveData(unsigned int Sock,unsigned char *PacketBuffer)��
���ܣ�ͨ�����ӵ�Socket�������ݡ�
��ڲ�����
	1��Sock��Ҫ�������ݵ�SOCKET��
	2��PacketBuffer��������յ����ݡ�
���ڲ������ޡ�
����ֵ��
	>0		�ɹ��������ݵĳ��ȡ�
	-2		RECEIVE_DATA_ERROR,�������ݴ�
	-4		SMART_RECEIVE_DATA_TIMEOUT���������ݳ�ʱ��
	-10		SMART_RECEIVE_DATA_PACKET_ERROR�������������ݰ���ʽ��
	-15		SMART_CONNECT_CLOSED��WINSOCK�����ѹرա�
	-16		SMART_CONNECT_BROKEN��WINSOCK���Ӷ��ѻ����·�ѹرա�
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
		
		//��������
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
			return SMART_RECEIVE_DATA_TIMEOUT;  //�������ݳ�ʱ
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
������int BindPort(char* IP_Address,int IP_Port,unsigned int *Sock)
���ܣ���ָ��������˿�
��ڲ�����
1��IP_Address�����󶨵�IP��ַ����"192.168.5.29"
2��IP_Port��   ���󶨵Ķ˿ںţ���4001��
���ڲ�����
Sock���󶨳ɹ��󣬷��ص��׽���ֵ��
����ֵ��
0		�󶨳ɹ���
-13		SMART_IP_ADDRESS_ERROR�������IP��ַ��
-14		SMART_INITIAL_SOCKET_ERROR����ʼ��SOCKET��
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
         return(SMART_INITIAL_SOCKET_ERROR);  //��ʼ��SOCKET��
	}

    int retval;
	retval=bind(m_socket,(SOCKADDR*)&addrSock,sizeof(SOCKADDR));
	if(SOCKET_ERROR==retval)
	{
		int ErrorCode=WSAGetLastError();
		closesocket(m_socket);
	//	return(SMART_INITIAL_SOCKET_ERROR);  //��ʼ��SOCKET��
		return ErrorCode;
	}
    *Sock = m_socket;
	return 0;
}

/*
������SendUDPData(unsigned int Sock,const char* IP_Address,int IP_Port,unsigned char *PacketBuffer,int PacketLen)��
���ܣ�ͨ���󶨵�Socket����UDP���ݡ�
��ڲ�����
1��Sock�� Ҫ�������ݵ�SOCKET��
2��IP_Address�������͵�IP��ַ����"192.168.5.30"
3��IP_Port��   ���󶨵Ķ˿ںţ���4001��
4��PacketBuffer��Ҫ���͵����ݡ�
5��PacketLen���������ݵĳ��ȡ�
���ڲ������ޡ�
����ֵ��
0		�������ݳɹ���
-3		SMART_SEND_DATA_ERROR���������ݴ�
-13		SMART_IP_ADDRESS_ERROR�������IP��ַ��
*/
int  SendUDPData(unsigned int Sock,const char* IP_Address,int IP_Port,unsigned char *PacketBuffer,int PacketLen)
{

	int RetCode;
    SOCKADDR_IN addrTo;
	if(PacketLen <= 0 )
	{
		return 0;   //û������Ҫ����
	}

	addrTo.sin_family=AF_INET;
	addrTo.sin_port=htons(IP_Port); //ת���������ֽ���
	addrTo.sin_addr.S_un.S_addr=inet_addr(IP_Address); //ת���������ֽ���

	RetCode=sendto(Sock,(const char*)PacketBuffer,PacketLen,0,(SOCKADDR*)&addrTo,sizeof(SOCKADDR)); //����UDP���ݰ�


	if(RetCode>0)
		return 0; //�������ݳɹ�
	else
	    return SMART_SEND_DATA_ERROR; //�������ݴ�

}

//RecvUDPData

/*
������RecvUDPData(unsigned int Sock,int WaitForSTX2Time,int NormalWaitTime,unsigned char *PacketBuffer)��
���ܣ�ͨ�����ӵ�Socket�������ݡ�
��ڲ�����
	1��Sock��Ҫ�������ݵ�SOCKET��
	2��WaitForSTX2Time������������ʼ����0xc2�ĳ�ʱʱ�䡣
	3��WaitForSTX2Time�������������ݵĳ�ʱʱ�䡣
	4��PacketBuffer��������յ����ݡ�
���ڲ������ޡ�
����ֵ��
	>0		�ɹ��������ݵĳ��ȡ�
	-9		RECEIVE_DATA_ERROR,�������ݴ�
	-4		SMART_RECEIVE_DATA_TIMEOUT���������ݳ�ʱ��
	-10		SMART_RECEIVE_DATA_PACKET_ERROR�������������ݰ���ʽ��
*/
int  RecvUDPData(unsigned int Sock,int WaitForSTX2Time,int NormalWaitTime,unsigned char *PacketBuffer,int bufLen)
{

	unsigned short crc16;
	unsigned char Crc1,Crc2;
    SOCKADDR_IN addrFrom;
	int len = sizeof(SOCKADDR);

    //	���ó�ʱ
	int rcvtimeo = WaitForSTX2Time+NormalWaitTime ; 

	if( setsockopt( Sock , SOL_SOCKET , SO_RCVTIMEO , (const char *)&rcvtimeo , sizeof(rcvtimeo) ) == SOCKET_ERROR)
	{
		return SMART_RECEIVE_DATA_TIMEOUT;
	}

	int retval=recvfrom(Sock,(char*)PacketBuffer,bufLen,0,(SOCKADDR*)&addrFrom,&len);
	if(retval>0)
	{
        if(PacketBuffer[0]!=STX2)
			return(SMART_RECEIVE_DATA_PACKET_ERROR);  //���ݸ�ʽ����
	}
	int totalLen=retval;
	int packetLen=100000;	 
	//�жϽ��������Ƿ���������������������
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
        return SMART_RECEIVE_DATA_TIMEOUT;  //�������ݳ�ʱ
		
    }
    else //���ݽ��ճɹ�
	{
		if(PacketBuffer[0]!=STX2 || PacketBuffer[totalLen-1]!=ETX2)
		{
			return(SMART_RECEIVE_DATA_PACKET_ERROR);  //���ݸ�ʽ����
		}

		//CRCУ��
		crc16=calc_crc16(totalLen-3,PacketBuffer);
		
		Crc1=(unsigned char)(crc16>>8);	
		Crc2=(unsigned char)crc16;	
		
		if((Crc1!=PacketBuffer[totalLen-3]) ||(Crc2!=PacketBuffer[totalLen-2])) 
		{
			return(-9);    //����У��CRC����
		}
		
		return(totalLen);
		
	}

}



/*
������CloseUDPSocketEnv(unsigned int sock)
���ܣ��ر�Sock �� WinSocket������
��ڲ��������رյ�sock��������
���ڲ������ޡ�
����ֵ��
	0			�ر�Sock �� WinSocket������
	-12			SMART_CLOSE_WINSOCK_ENV_ERROR���ر�WinSocket��������
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
������GetOneLocalSocket(unsigned int * socket)
���ܣ����һ������������SOCK,���ڷ��ͺͽ���UDP��
��ڲ�����
���ڲ������µõ���Sock��
����ֵ��
	0        ִ�гɹ�	   
	<0 		 ִ��ʧ��
*/


int GetOneLocalSocket(unsigned int * socket,int srcPort)   
{
   
   //�ɹ�����true , ʧ�ܷ���false
     int port = srcPort;   
	 int ret = -1;
	 
	 char strIP[20];
	 strIP[0]=0;
     //�����������
     PIP_ADAPTER_INFO pInfo=NULL;
     ULONG ulSize=0;
      
     GetAdaptersInfo(pInfo,&ulSize);//��һ�ε��ã���ȡ��������С
	 if (ulSize == 0 ) {
		 return -3; //�������Ӳ�����
	 }
     pInfo=(PIP_ADAPTER_INFO)new(char[ulSize]);
     GetAdaptersInfo(pInfo,&ulSize);
     
     //����ÿһ������
     while(pInfo)
     {
		 if (pInfo->Type == MIB_IF_TYPE_ETHERNET) //�����PPP����
		 {
			 strcpy(strIP,pInfo->IpAddressList.IpAddress.String);//��ȡGPRS���ӵ�IP��ַ
			 break;
		 }
         //����ǰָ��������һ��
         pInfo=pInfo->Next;
     }
     if (0==strIP[0])
	 {  
		 socket=0;
		 return -1; //GPRS���Ӳ�����
	 }
	 
    ret=BindPort(strIP,port,socket); 
    if(ret<0)
	{
			 socket=0;
			 return -2;  //��ʧ��
	 }
	 
	 return 0;


}