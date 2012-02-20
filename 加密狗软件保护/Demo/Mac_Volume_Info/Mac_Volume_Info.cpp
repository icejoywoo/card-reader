#include "stdafx.h"

#include < windows.h >
#include < wincon.h >
#include < stdlib.h >
#include < stdio.h >
#include < time.h >

// 因为是通过NetAPI来获取网卡信息，所以需要包含其题头文件nb30.h #include < nb30.h >
#include < nb30.h >
#pragma comment(lib,"Netapi32.lib")


typedef struct _ASTAT_
{
 ADAPTER_STATUS adapt;
 NAME_BUFFER NameBuff [30];
}ASTAT, * PASTAT;

ASTAT Adapter;

// 定义一个存放返回网卡信息的变量
// 输入参数：lana_num为网卡编号，一般地，从0开始，但在Windows 2000中并不一定是连续分配的

void getmac_one (int lana_num)
{
 NCB ncb;
 UCHAR uRetCode;
 
 memset( &ncb, 0, sizeof(ncb) );
 ncb.ncb_command = NCBRESET;
 ncb.ncb_lana_num = lana_num;
 // 指定网卡号
 
 // 首先对选定的网卡发送一个NCBRESET命令，以便进行初始化
 uRetCode = Netbios( &ncb );
 printf( "The NCBRESET return code is: 0x%x \n", uRetCode );
 
 memset( &ncb, 0, sizeof(ncb) );
 ncb.ncb_command = NCBASTAT;
 ncb.ncb_lana_num = lana_num; // 指定网卡号
 
 strcpy( (char *)ncb.ncb_callname, "* " );
 ncb.ncb_buffer = (unsigned char *) &Adapter;
 
 // 指定返回的信息存放的变量
 ncb.ncb_length = sizeof(Adapter);
 
 // 接着，可以发送NCBASTAT命令以获取网卡的信息
 uRetCode = Netbios( &ncb );
 printf( "The NCBASTAT return code is: 0x%x \n", uRetCode );
 if ( uRetCode == 0 )
 {
  // 把网卡MAC地址格式化成常用的16进制形式，如0010-A4E4-5802
  printf( "The Ethernet Number[%d] is: %02X-%02X-%02X-%02X-%02X-%02X\n",
   lana_num,
   Adapter.adapt.adapter_address[0],
   Adapter.adapt.adapter_address[1],
   Adapter.adapt.adapter_address[2],
   Adapter.adapt.adapter_address[3],
   Adapter.adapt.adapter_address[4],
   Adapter.adapt.adapter_address[5] );
 }
}

int main(int argc, char* argv[])
{
 NCB ncb;
 UCHAR uRetCode;
 LANA_ENUM lana_enum;
 
 memset( &ncb, 0, sizeof(ncb) );
 ncb.ncb_command = NCBENUM;
 
 ncb.ncb_buffer = (unsigned char *) &lana_enum;
 ncb.ncb_length = sizeof(lana_enum);
 
 // 向网卡发送NCBENUM命令，以获取当前机器的网卡信息，如有多少个网卡、每张网卡的编号等
 uRetCode = Netbios( &ncb );
 printf( "The NCBENUM return code is: 0x%x \n", uRetCode );
 if ( uRetCode == 0 )
 {
	 printf( "Ethernet Count is : %d\n\n", lana_enum.length);
	 
	 // 对每一张网卡，以其网卡编号为输入编号，获取其MAC地址
	 for ( int i=0; i< lana_enum.length; ++i)
	 {
		 printf("%d", lana_enum.lana[i]);
		 getmac_one( lana_enum.lana[i]);
	 }
 }
 return 0;
} 