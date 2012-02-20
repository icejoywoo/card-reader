#ifndef _HARDWARE_INFO_H_
#define _HARDWARE_INFO_H_

#include <winsock2.h> //��ͷ�ļ�������Socket��̵Ĺ���  
#include <httpext.h>   //��ͷ�ļ�֧��HTTP����  
#include <windef.h>   //��ͷ�ļ�������Windows���������ݻ�����̬  
#include <Nb30.h>   //��ͷ�ļ�������netbios�����еĺ���   
#pragma comment(lib,"ws2_32.lib")    //����ws2_32.lib��.ֻҪ�������õ�Winsock API ��������Ҫ�õ� Ws2_32.lib  
#pragma comment(lib,"netapi32.lib")   //����Netapi32.lib�⣬MAC��ȡ���õ���NetApi32.DLL�Ĺ��� 

//��Win32ƽ̨�ϵ�Winsock��̶�Ҫ�������еĻ������裺�������->���Winsock�汾->����Winsock��->  
//��ʼ��->�����׽���->�����׽���ѡ��->�ر��׽���->ж��Winsock�⣬�ͷ�������Դ��  
int GetIP(char* ip);

//ͨ��WindowsNT/Win2000�����õ�NetApi32.DLL�Ĺ�����ʵ�ֵġ�����ͨ������NCBENUM����,��ȡ������  
//��Ŀ��ÿ���������ڲ����,Ȼ���ÿ��������ŷ���NCBASTAT�����ȡ��MAC��ַ��  
int GetMAC(char * mac);

#endif