#include "StdAfx.h"
#include "HardwareInfo.h"
 
int GetIP(char* ip)
{
	WSADATA wsaData;  
	char name[155];      //定义用于存放获得主机名的变量  
	PHOSTENT hostinfo;
	
	//调用MAKEWORD()获得Winsocl版本的正确值，用于下面的加载Winscok库  
	if ( WSAStartup( MAKEWORD(2,0), &wsaData ) == 0 )   
	{   //加载Winsock库，如果WSAStartup()函数返回值为0，说明加载成功，程序可以继续往下执行  
		if( gethostname ( name, sizeof(name)) == 0)   
		{ //如果成功，将本地主机名存放入由name参数指定的缓冲区中  
			if((hostinfo = gethostbyname(name)) != NULL)   
			{ //这是获取主机，如果获得主机名成功的话，将返回一个指针，指向hostinfo,hostinfo为PHOSTENT型的变量。  
				sprintf(ip, "%s", inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list));   
				//inet_addr()函数把地址串转换为IP地址  
				//调用inet_ntoa()函数,将hostinfo结构变量中的h_addr_list转化为标准的IP地址(如202.197.11.12.)
				return 0;
			}   
		}   
		WSACleanup( );         //卸载Winsock库，并释放所有资源  
    }

	return -1;
}

int GetMAC(char * mac)
{
	NCB ncb;     //定义一个NCB(网络控制块)类型的结构体变量ncb  
	typedef struct _ASTAT_     //自定义一个结构体_ASTAT_  
	{  
		ADAPTER_STATUS   adapt;   
		NAME_BUFFER   NameBuff   [30];       
	}ASTAT, *PASTAT;  
	ASTAT Adapter;     
	
	typedef struct _LANA_ENUM     //自定义一个结构体_ASTAT_  
	{  
		UCHAR length;   
		UCHAR lana[MAX_LANA];     //存放网卡MAC地址   
	}LANA_ENUM;       
	LANA_ENUM lana_enum;     
	
	//   取得网卡信息列表       
	UCHAR uRetCode;       
	memset(&ncb, 0, sizeof(ncb));     //将已开辟内存空间ncb 的值均设为值 0  
	memset(&lana_enum, 0, sizeof(lana_enum));     //清空一个结构类型的变量lana_enum，赋值为0  
	//对结构体变量ncb赋值  
	ncb.ncb_command = NCBENUM;     //统计系统中网卡的数量  
	ncb.ncb_buffer = (unsigned char *)&lana_enum; //ncb_buffer成员指向由LANA_ENUM结构填充的缓冲区  
	ncb.ncb_length = sizeof(LANA_ENUM);     
	//向网卡发送NCBENUM命令，以获取当前机器的网卡信息，如有多少个网卡，每个网卡的编号（MAC地址）   
	uRetCode = Netbios(&ncb); //调用netbois(ncb)获取网卡序列号      
	if(uRetCode != NRC_GOODRET)       
        return uRetCode;       
	
	//对每一个网卡，以其网卡编号为输入编号，获取其MAC地址     
	for(int lana=0; lana<lana_enum.length; lana++)       
	{  
		ncb.ncb_command = NCBRESET;   //对网卡发送NCBRESET命令，进行初始化  
		ncb.ncb_lana_num = lana_enum.lana[lana];   
		uRetCode = Netbios(&ncb);     
	}   
	if(uRetCode != NRC_GOODRET)  
        return uRetCode;       
	
	//   准备取得接口卡的状态块取得MAC地址  
	memset(&ncb, 0, sizeof(ncb));   
	ncb.ncb_command = NCBASTAT;    //对网卡发送NCBSTAT命令，获取网卡信息  
	ncb.ncb_lana_num = lana_enum.lana[0];     //指定网卡号，这里仅仅指定第一块网卡，通常为有线网卡   
	strcpy((char*)ncb.ncb_callname, "*");     //远程系统名赋值为*  
	ncb.ncb_buffer = (unsigned char *)&Adapter; //指定返回的信息存放的变量  
	ncb.ncb_length = sizeof(Adapter);  
	//接着发送NCBASTAT命令以获取网卡的信息 
	uRetCode = Netbios(&ncb);   
	//   取得网卡的信息，并且如果网卡正常工作的话，返回标准的冒号分隔格式。     
	if(uRetCode != NRC_GOODRET)     
        return uRetCode;     
	//把网卡MAC地址格式转化为常用的16进制形式,输出到字符串mac中   
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
		printf("获得网卡信息失败！");  
		return   FALSE;  
	}  
	//   分配网卡信息内存  
	pAdapterInfo   =   (PIP_ADAPTER_INFO)   GlobalAlloc(GPTR,   AdapterInfoSize);  
	if(pAdapterInfo   ==   NULL){  
		printf("分配网卡信息内存失败");  
		return   FALSE;  
	}    
	if(GetAdaptersInfo(pAdapterInfo,   &AdapterInfoSize)   !=   0){  
		printf("获得网卡信息失败！\n");  
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