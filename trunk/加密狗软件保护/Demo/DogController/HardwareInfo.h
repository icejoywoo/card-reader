#ifndef _HARDWARE_INFO_H_
#define _HARDWARE_INFO_H_

#include <winsock2.h> //该头文件定义了Socket编程的功能  
#include <httpext.h>   //该头文件支持HTTP请求  
#include <windef.h>   //该头文件定义了Windows的所有数据基本型态  
#include <Nb30.h>   //该头文件声明了netbios的所有的函数   
#pragma comment(lib,"ws2_32.lib")    //连接ws2_32.lib库.只要程序中用到Winsock API 函数，都要用到 Ws2_32.lib  
#pragma comment(lib,"netapi32.lib")   //连接Netapi32.lib库，MAC获取中用到了NetApi32.DLL的功能 

//在Win32平台上的Winsock编程都要经过下列的基本步骤：定义变量->获得Winsock版本->加载Winsock库->  
//初始化->创建套接字->设置套接字选项->关闭套接字->卸载Winsock库，释放所有资源。  
int GetIP(char* ip);

//通过WindowsNT/Win2000中内置的NetApi32.DLL的功能来实现的。首先通过发送NCBENUM命令,获取网卡的  
//数目和每张网卡的内部编号,然后对每个网卡标号发送NCBASTAT命令获取其MAC地址。  
int GetMAC(char * mac);

#endif