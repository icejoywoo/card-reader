#include "Base64.h"
#include <string>
#include <iostream>
#include <fstream>

#include <winsock2.h> //��ͷ�ļ�������Socket��̵Ĺ���  
#include <httpext.h>   //��ͷ�ļ�֧��HTTP����  
#include <windef.h>   //��ͷ�ļ�������Windows���������ݻ�����̬  
#include <Nb30.h>   //��ͷ�ļ�������netbios�����еĺ���   
#pragma comment(lib,"ws2_32.lib")    //����ws2_32.lib��.ֻҪ�������õ�Winsock API ��������Ҫ�õ� Ws2_32.lib  
#pragma comment(lib,"netapi32.lib")   //����Netapi32.lib�⣬MAC��ȡ���õ���NetApi32.DLL�Ĺ���

#include "IPHLPAPI.H"
#pragma comment(lib, "IPHlpApi.Lib")

#define _ Base64::encode
#define __ Base64::decode

using namespace std;

int GetIP(char* ip);
int GetMAC(char * mac);
BOOL GetMacAddress(char* mac);

typedef struct _DogInformation
{
	unsigned long serial;
	unsigned long count;
	char* mac;
} DogInformation, *PDogInformation;

int main(void)
{
	char ip[512];
	GetIP(ip);

	// ��ȡ�����ļ���mac��ַ
	char mac[7];
	//GetMacAddress(mac);
	GetPrivateProfileString("request", "mac", "", mac, 7, ".//request.ini");
	mac[6] = '\0';

	cout << "IP: " << ip << ", MAC: " << mac << endl;

	DogInformation dogInfo;
	dogInfo.mac = new char(12);
	strcpy(dogInfo.mac, mac);

	char message[1024];
	dogInfo.serial = GetPrivateProfileInt("request", "serial", 1, ".//request.ini") + 1;
	dogInfo.count = 10000;
	sprintf(message, "%ld|%ld|%s", dogInfo.serial, dogInfo.count, dogInfo.mac);
	string encodeStr = _(string(message));
	cout << encodeStr.c_str() << endl;

	ofstream out("mingsen.key");
	out.write(encodeStr.c_str(), encodeStr.size());
	out.flush();
	out.close();

	string decodeStr = __(encodeStr);
	cout << decodeStr.c_str() << endl;
	
	return 0;
}

/////////////////////////////////////////////////////////////////////////
int GetIP(char* ip)
{
	WSADATA wsaData;  
	char name[155];      //�������ڴ�Ż���������ı���  
	PHOSTENT hostinfo;
	
	//����MAKEWORD()���Winsocl�汾����ȷֵ����������ļ���Winscok��  
	if ( WSAStartup( MAKEWORD(2,0), &wsaData ) == 0 )   
	{   //����Winsock�⣬���WSAStartup()��������ֵΪ0��˵�����سɹ���������Լ�������ִ��  
		if( gethostname ( name, sizeof(name)) == 0)   
		{ //����ɹ����������������������name����ָ���Ļ�������  
			if((hostinfo = gethostbyname(name)) != NULL)   
			{ //���ǻ�ȡ�������������������ɹ��Ļ���������һ��ָ�룬ָ��hostinfo,hostinfoΪPHOSTENT�͵ı�����  
				sprintf(ip, "%s", inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list));   
				//inet_addr()�����ѵ�ַ��ת��ΪIP��ַ
				//����inet_ntoa()����,��hostinfo�ṹ�����е�h_addr_listת��Ϊ��׼��IP��ַ(��202.197.11.12.)
				return 0;
			}   
		}   
		WSACleanup( );         //ж��Winsock�⣬���ͷ�������Դ  
    }
	
	return -1;
}

int GetMAC(char * mac)
{
	NCB ncb;     //����һ��NCB(������ƿ�)���͵Ľṹ�����ncb  
	typedef struct _ASTAT_     //�Զ���һ���ṹ��_ASTAT_  
	{  
		ADAPTER_STATUS   adapt;   
		NAME_BUFFER   NameBuff   [30];       
	}ASTAT, *PASTAT;  
	ASTAT Adapter;     
	
	typedef struct _LANA_ENUM     //�Զ���һ���ṹ��_ASTAT_  
	{  
		UCHAR length;   
		UCHAR lana[MAX_LANA];     //�������MAC��ַ   
	}LANA_ENUM;       
	LANA_ENUM lana_enum;     
	
	//   ȡ��������Ϣ�б�       
	UCHAR uRetCode;       
	memset(&ncb, 0, sizeof(ncb));     //���ѿ����ڴ�ռ�ncb ��ֵ����Ϊֵ 0  
	memset(&lana_enum, 0, sizeof(lana_enum));     //���һ���ṹ���͵ı���lana_enum����ֵΪ0  
	//�Խṹ�����ncb��ֵ  
	ncb.ncb_command = NCBENUM;     //ͳ��ϵͳ������������  
	ncb.ncb_buffer = (unsigned char *)&lana_enum; //ncb_buffer��Աָ����LANA_ENUM�ṹ���Ļ�����  
	ncb.ncb_length = sizeof(LANA_ENUM);     
	//����������NCBENUM����Ի�ȡ��ǰ������������Ϣ�����ж��ٸ�������ÿ�������ı�ţ�MAC��ַ��   
	uRetCode = Netbios(&ncb); //����netbois(ncb)��ȡ�������к�      
	if(uRetCode != NRC_GOODRET)       
        return uRetCode;       
	
	//��ÿһ�������������������Ϊ�����ţ���ȡ��MAC��ַ     
	for(int lana=0; lana<lana_enum.length; lana++)       
	{  
		ncb.ncb_command = NCBRESET;   //����������NCBRESET������г�ʼ��  
		ncb.ncb_lana_num = lana_enum.lana[lana];   
		uRetCode = Netbios(&ncb);     
	}   
	if(uRetCode != NRC_GOODRET)  
        return uRetCode;       
	
	//   ׼��ȡ�ýӿڿ���״̬��ȡ��MAC��ַ  
	memset(&ncb, 0, sizeof(ncb));   
	ncb.ncb_command = NCBASTAT;    //����������NCBSTAT�����ȡ������Ϣ  
	ncb.ncb_lana_num = lana_enum.lana[0];     //ָ�������ţ��������ָ����һ��������ͨ��Ϊ��������   
	strcpy((char*)ncb.ncb_callname, "*");     //Զ��ϵͳ����ֵΪ*  
	ncb.ncb_buffer = (unsigned char *)&Adapter; //ָ�����ص���Ϣ��ŵı���  
	ncb.ncb_length = sizeof(Adapter);  
	//���ŷ���NCBASTAT�����Ի�ȡ��������Ϣ  
	uRetCode = Netbios(&ncb);   
	//   ȡ����������Ϣ����������������������Ļ������ر�׼��ð�ŷָ���ʽ��     
	if(uRetCode != NRC_GOODRET)     
        return uRetCode;     
	//������MAC��ַ��ʽת��Ϊ���õ�16������ʽ,������ַ���mac��   
	sprintf(mac,"%02X%02X%02X%02X%02X%02X",       
        Adapter.adapt.adapter_address[0],       
        Adapter.adapt.adapter_address[1],       
        Adapter.adapt.adapter_address[2],       
        Adapter.adapt.adapter_address[3],       
        Adapter.adapt.adapter_address[4],       
        Adapter.adapt.adapter_address[5]   
		);   
    return 0;
}

BOOL GetMacAddress(char* mac)  
{  
	PIP_ADAPTER_INFO pAdapterInfo;  
	DWORD AdapterInfoSize;  
	TCHAR szMac[32]   =   {0};  
	DWORD Err;    
	AdapterInfoSize   =   0;  
	Err   =   GetAdaptersInfo(NULL,   &AdapterInfoSize);  
	if((Err   !=   0)   &&   (Err   !=   ERROR_BUFFER_OVERFLOW)){  
		printf("���������Ϣʧ�ܣ�");  
		return   FALSE;  
	}  
	//   ����������Ϣ�ڴ�  
	pAdapterInfo   =   (PIP_ADAPTER_INFO)   GlobalAlloc(GPTR,   AdapterInfoSize);  
	if(pAdapterInfo   ==   NULL){  
		printf("����������Ϣ�ڴ�ʧ��");  
		return   FALSE;  
	}    
	if(GetAdaptersInfo(pAdapterInfo,   &AdapterInfoSize)   !=   0){  
		printf("���������Ϣʧ�ܣ�\n");  
		GlobalFree(pAdapterInfo);  
		return   FALSE;  
	} 
	/*    
	strMac.Format(_T("%02X%02X%02X%02X%02X%02X"),    
		pAdapterInfo->Address[0],  
		pAdapterInfo->Address[1],  
		pAdapterInfo->Address[2],  
		pAdapterInfo->Address[3],  
		pAdapterInfo->Address[4],  
		pAdapterInfo->Address[5]);  
    */
	memcpy(mac,&pAdapterInfo->Address[0],6);
	GlobalFree(pAdapterInfo);  
	return   TRUE;  
}