#include "stdafx.h"

#include < windows.h >
#include < wincon.h >
#include < stdlib.h >
#include < stdio.h >
#include < time.h >

// ��Ϊ��ͨ��NetAPI����ȡ������Ϣ��������Ҫ��������ͷ�ļ�nb30.h #include < nb30.h >
#include < nb30.h >
#pragma comment(lib,"Netapi32.lib")


typedef struct _ASTAT_
{
 ADAPTER_STATUS adapt;
 NAME_BUFFER NameBuff [30];
}ASTAT, * PASTAT;

ASTAT Adapter;

// ����һ����ŷ���������Ϣ�ı���
// ���������lana_numΪ������ţ�һ��أ���0��ʼ������Windows 2000�в���һ�������������

void getmac_one (int lana_num)
{
 NCB ncb;
 UCHAR uRetCode;
 
 memset( &ncb, 0, sizeof(ncb) );
 ncb.ncb_command = NCBRESET;
 ncb.ncb_lana_num = lana_num;
 // ָ��������
 
 // ���ȶ�ѡ������������һ��NCBRESET����Ա���г�ʼ��
 uRetCode = Netbios( &ncb );
 printf( "The NCBRESET return code is: 0x%x \n", uRetCode );
 
 memset( &ncb, 0, sizeof(ncb) );
 ncb.ncb_command = NCBASTAT;
 ncb.ncb_lana_num = lana_num; // ָ��������
 
 strcpy( (char *)ncb.ncb_callname, "* " );
 ncb.ncb_buffer = (unsigned char *) &Adapter;
 
 // ָ�����ص���Ϣ��ŵı���
 ncb.ncb_length = sizeof(Adapter);
 
 // ���ţ����Է���NCBASTAT�����Ի�ȡ��������Ϣ
 uRetCode = Netbios( &ncb );
 printf( "The NCBASTAT return code is: 0x%x \n", uRetCode );
 if ( uRetCode == 0 )
 {
  // ������MAC��ַ��ʽ���ɳ��õ�16������ʽ����0010-A4E4-5802
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
 
 // ����������NCBENUM����Ի�ȡ��ǰ������������Ϣ�����ж��ٸ�������ÿ�������ı�ŵ�
 uRetCode = Netbios( &ncb );
 printf( "The NCBENUM return code is: 0x%x \n", uRetCode );
 if ( uRetCode == 0 )
 {
	 printf( "Ethernet Count is : %d\n\n", lana_enum.length);
	 
	 // ��ÿһ�������������������Ϊ�����ţ���ȡ��MAC��ַ
	 for ( int i=0; i< lana_enum.length; ++i)
	 {
		 printf("%d", lana_enum.lana[i]);
		 getmac_one( lana_enum.lana[i]);
	 }
 }
 return 0;
} 