#ifndef __SmartCom_h__
#define __SmartCom_h__

#include "Communicator.h"
#include "SmartComString.h"
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the SMARTCOM_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// SMARTCOM_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef SMARTCOM_EXPORTS_MACRO
#define SMARTCOM_API __declspec(dllexport)
#else
#define SMARTCOM_API __declspec(dllimport)
#endif

#define USE_SMARTCOMSTRING
/********************************************
����:
��ʼ���뿨Ƭ��д����ͨ��.
��ڲ�������
���ڲ�������
����ֵ��
-1����ʼ��ʧ��
0���ɹ�
*********************************************/
SMARTCOM_API int InitUDPComm();



/************************************************************************/
/* 
���ܣ�
��ȡһ��comͨ����
��ڲ�����
comPort:Ҫͨ�ŵĶ˿ں�
rate:�����ʣ�Ĭ��115200
waitForSTX2Time����һ���ַ���ʱ��Ĭ��1000ms
normalWaitTime���м��ַ���ʱ��Ĭ��1000ms
���ڲ�������
����ֵ��
0���ɹ�
-1��ʧ��
/************************************************************************/
SMARTCOM_API int GetOneCOMCommunicator(Communicator& aCommunicator,int comPort,int rate=115200,
									   int waitForSTX2Time=1000,int normalWaitTime=1000 );

/************************************************************************
���ܣ�
�ر�COMͨ��
��ڲ�������
���ڲ���:��
����ֵ��
0���ɹ�
-1��ʧ��
***********************************************************************/
SMARTCOM_API int CloseCOMComm();

/************************************************************************
���ܣ�
�ر�udpͨ��
��ڲ�������
���ڲ���:��
����ֵ��
0���ɹ�
-1��ʧ��
***********************************************************************/
SMARTCOM_API int CloseUDPComm();

/************************************************************************
���ܣ�
��ȡһ��udpͨ������
��ڲ�����
dstIP:Ŀ��ip
port��Ŀ�Ķ˿�
waitForSTX2Time����һ���ַ���ʱ��Ĭ��1000ms
normalWaitTime���м��ַ���ʱ��Ĭ��1000ms
���ڲ���:
aCommunicator:���ص�ͨ����
����ֵ��
0���ɹ�
-1��ʧ��
***********************************************************************/
SMARTCOM_API int GetOneUDPCommunicator(Communicator& aCommunicator,const char* dstIP,int port,
									   int waitForSTX2Time=1000,int normalWaitTime=1000);

/************************************************************************
���ܣ�
��ȡ�ն��豸id�źͻ���
��ڲ�����
comm:����ͨ�ŵ�ͨ����
devIDBufLen: devID����ĳ���
���ڲ���:
DevID�����7�ֽ�id��,
MacNo:1�ֽڻ���
����ֵ��
0����ȡ�ɹ�
-1��ͨ�ų�ʱ����
-2: ͨ������Ч
-3: ��ȡʧ��

/************************************************************************/
SMARTCOM_API int GetDevIDAndMacNo(Communicator& comm,char* devID,int devIDBufLen,int& macNo);

#ifdef USE_SMARTCOMSTRING
SMARTCOM_API int GetDevIDAndMacNo(Communicator& comm, SmartCom::string& devID,int& macNo);
#endif
/************************************************************************/
/*���ܣ�
ͨ���ն��豸ID�Ÿ��ն��豸���û���
��ڲ�����
comm:����ͨ�ŵ�ͨ����
DevID:���7���ֽڵ��豸ID
MacNo:Ҫ���õĻ���
���ڲ�������
����ֵ��
0�����óɹ�
-1��ͨ�ų�ʱ����
-2:ͨ������Ч
-3:���ŷ�Χ����
-4������ʧ��
                                                      */
/************************************************************************/
SMARTCOM_API int SetMacNoByDevID(Communicator& comm,const char* devID,int macNo);

/************************************************************************/
/* ���ܣ�
��ȡ����汾���ն�����
��ڲ�����
comm:����ͨ�ŵ�ͨ����
verLen:���appversion�Ļ��峤��
typelen������ն����͵Ļ��峤��
���ţ�Ĭ��255
���ڲ����� 
appVersion:����汾
devType:�ն�����
����ֵ��
0����ȡ�ɹ�
-1��ͨ�ų�ʱ����
-2��ͨ������Ч
-3: ���ŷ�Χ����
-4����ȡʧ��
                                                     */
/************************************************************************/
SMARTCOM_API int GetAppVerAndDevType(Communicator& comm,char* appVersion,int Verlen,char* devType,int typeLen,
									 int MacNo=255);
#ifdef USE_SMARTCOMSTRING
SMARTCOM_API int GetAppVerAndDevType(Communicator& comm,SmartCom::string& appVersion,SmartCom::string& devType,
									 int MacNo=255);
#endif
/************************************************************************/
/* ���ܣ�
��λ�ն��豸
��ڲ�����
comm:����ͨ�ŵ�ͨ����
macNo:���ţ�Ĭ��255
���ڲ�������
����ֵ��
0���ɹ�
-1��ͨ�ų�ʱ����
-2��ͨ������Ч
-3:���ŷ�Χ����
                                                                    */
/************************************************************************/
SMARTCOM_API int ResetDev(Communicator& comm,int macNo=255);

/************************************************************************/
/* ���ܣ�
��ȡ�����ӿ�оƬID��
��ڲ�����
comm:����ͨ�ŵ�ͨ����
chipIDLen:��Žӿ�оƬID�Ļ��泤��
macNo:���ţ�Ĭ��255
���ڲ�����
chipID
����ֵ��
0���ɹ�
-1��ͨ�ų�ʱ����
-2��ͨ������Ч
-3:���ŷ�Χ����
-4����ȡʧ��
                                                                    */
/************************************************************************/
SMARTCOM_API int GetChipID(Communicator& comm,char* chipID,int chipIDLen,int macNo=255);

#ifdef USE_SMARTCOMSTRING
SMARTCOM_API int GetChipID(Communicator& comm,SmartCom::string& chipID,int macNo=255);
#endif
/************************************************************************/
/* ���ܣ�
���A�����󿨣�����B����SIM�������Ƿ��п�
��ڲ�����
comm:����ͨ�ŵ�ͨ����
macNO:���ţ�Ĭ��255
���ڲ�����
cardA:1,A�����п���0��A�����޿�
cardB:1,B�����п���0��B�����޿�
����ֵ��
0�����ɹ�
-1��ͨ�ų�ʱ����
-2��ͨ������Ч
-3:���ŷ�Χ����
-4�����ʧ��
                                                                      */
/************************************************************************/
SMARTCOM_API int IsCardReady(Communicator& comm,int& cardA,int& cardB,int macNo=255);

/************************************************************************/
/* ���ܣ�
��Ƭ��λӦ��
��ڲ�����
comm:����ͨ�ŵ�ͨ����
card��1:A����2��B��,Ĭ��ѡ��A��
macNO:���ţ�Ĭ��255
���ڲ�����
retCode:��λ����ķ���ֵ
retCode="F9"�������޿�
retCode="FD"������ʶ��
����ֵ��
0���ɹ�
-1��ͨ�ų�ʱ����
-2��ͨ������Ч  
-3: ���ŷ�Χ����
 -4:��λʧ��                                                              */
/************************************************************************/
SMARTCOM_API int ResetCard(Communicator& comm,SmartCom::string& retCode,int card=1,int macNo=255);

/************************************************************************/
/* ���ܣ�
��Ƭ����-APDU
��ڲ�����
comm:����ͨ�ŵ�ͨ����
apdu:ʮ�������ַ�����ʾ��apdu����
card��1:A����2��B��,Ĭ��ѡ��A��
macNO:���ţ�Ĭ��255
���ڲ�����
retCode:ִ��apduָ��ķ���ֵ
retCode="F9"�������޿�
retCode="FD"������ʶ��
retCode="F2"�� ��Ч7816�����
retCode="F0"�� û���ȸ��������ϵ縴λ
����ֵ��
0��ͨ�ųɹ�
-1��ͨ�ų�ʱ����
-2��ͨ������Ч 
-3: ���ŷ�Χ����
                                                                 */
/************************************************************************/
SMARTCOM_API int CardApdu(Communicator& comm,const char* apdu,SmartCom::string& retCode,int card=1,int macNo=255);


/************************************************************************/
/* ���ܣ���Ƭ�µ�
��ڲ�����
comm:����ͨ�ŵ�ͨ����
macNO:���ţ�Ĭ��255
���ڲ�������
����ֵ��
0���µ�ɹ�
-1��ͨ�ų�ʱ����
-2��ͨ������Ч
-3: ���ŷ�Χ����
-4���µ�ʧ��
                                                    */
/************************************************************************/
SMARTCOM_API int ShutdownCard(Communicator& comm,int macNo=255);

/************************************************************************/
/* ���ܣ�
�޸Ŀ�ͨ�Ų�����
��ڲ���:
comm:����ͨ�ŵ�ͨ����
braudRate:Ҫ�޸ĵĲ����ʣ�ֻ��ѡ����ֵ��
115200��57600��38400��28800��23040��19200��14400��12800��9600
macNO:���ţ�Ĭ��255
���ڲ�������
����ֵ��
0���޸ĳɹ�
-1��ͨ�ų�ʱ����
-2��ͨ������Ч
-3: ���ŷ�Χ����
-4���޸�ʧ��
                                                              */
/************************************************************************/
SMARTCOM_API int ModifyCardBraudRate(Communicator& comm,int braudRate,int macNo=255);

/************************************************************************/
/* ���ܣ�
����ͨ�Ų�����
��ڲ���:
comm:����ͨ�ŵ�ͨ����
macNO:���ţ�Ĭ��255
���ڲ�����
braudRate����ǰ����ͨ�Ų�����
����ֵ��
0����ȡ�ɹ�
-1��ͨ�ų�ʱ����
-2��ͨ������Ч
-3: ���ŷ�Χ����
-4����ȡʧ��

                                                            */
/************************************************************************/
SMARTCOM_API int GetCardBraudRate(Communicator& comm,int& braudRate,int macNo=255);

/************************************************************************/
/* ���ܣ�
�޸Ŀ�Ƭ��Դ
��ڲ���:
comm:����ͨ�ŵ�ͨ����
power����Դ��power=1: 5v��power=2: 3v��power=3: 1.8v
card:1:A����2��B��,Ĭ��ѡ��A��
macNO:���ţ�Ĭ��255
���ڲ�������
����ֵ��
0���޸ĳɹ�
-1��ͨ�ų�ʱ����
-2��ͨ������Ч
-3: ���ŷ�Χ����
-4:�޸�ʧ��
                                                            */
/************************************************************************/
SMARTCOM_API int ModifyCardPower(Communicator& comm,int power,int card=1,int macNo=255);

/************************************************************************/
/* ���ܣ�
����ִ��������APDU����
��ڲ�����
comm:����ͨ�ŵ�ͨ����  
card:ѡ��ִ�еĿ���card=1ΪA����2ΪB����Ĭ��A��
cmdNum:Ҫִ�е�ָ������
macNO:���ţ�Ĭ��255
���ڲ�������
����ֵ��
0���ɹ�
-1��ͨ�ų�ʱ����
-2��ͨ������Ч
-3: ���ŷ�Χ����
-4: ����ʧ��
                                                               */
/************************************************************************/
SMARTCOM_API int  ExcuteMulAPDU(Communicator& comm,int cmdNum,int card=1,int macNo=255);

/************************************************************************/
/* ���ܣ�
������������ƽű��ļ�
��ڲ�����
comm:����ͨ�ŵ�ͨ����
bytes:Ҫ��ȡ���ֽ���
 macNO:���ţ�Ĭ��255 
 strDataLen����Ŷ�ȡ��ʮ�������ַ������ݵĻ��泤��
 offset:��ȡ���ݵ��ļ�ƫ�Ƶ�ַ
 ���ڲ�����
 strData:��ȡ��ת����ʮ�������ַ���������
 ����ֵ��
 0����ȡ�ɹ�
 -1��ͨ�ų�ʱ����
 -2��ͨ������Ч
 -3: ���ŷ�Χ����
 -4: ��ȡʧ��
                                                              */
/************************************************************************/
SMARTCOM_API int GetScriptData(Communicator& comm,int offset,unsigned char bytes,char* strData,int strDataLen,int macNo=255);

#ifdef USE_SMARTCOMSTRING
SMARTCOM_API int GetScriptData(Communicator& comm,int offset,unsigned char bytes,SmartCom::string& strData,int macNo=255);
#endif
/************************************************************************/
/* ���ܣ�
�����ļ�
��ڲ�����
comm:����ͨ�ŵ�ͨ����
flag:flag=1,�����������ļ���flag=2����������ͷ�ļ�
fileName:�ļ���
macNO:���ţ�Ĭ��255 
���ڲ�������
 ����ֵ����
 0�����سɹ�
 -1��ͨ�ų�ʱ����
-2��ͨ������Ч 
-3: ���ŷ�Χ����
- 4: ����ʧ��
-5:�ļ���ʧ��
                                                           */
/************************************************************************/
SMARTCOM_API int DownloadFile(Communicator& comm,int flag,const char* fileName,int macNo=255);

/************************************************************************/
/* ���ܣ�
��ѯִ��������APDU���
��ڲ�����
comm:����ͨ�ŵ�ͨ����
macNO:���ţ�Ĭ��255 
���ڲ�����
retCode:���һ��ָ��ķ���ֵ 
retCode="F1": δѡ�������޿��򿨸�λʧ��(����ʧЧ)��APDU��Ӧ��ʱ������Ч��APDU����ȴ���
����ֵ��
>=0�������Ѿ�ִ�е���������
-1��ͨ�ų�ʱ����
-2��ͨ������Ч 
-3�����ŷ�Χ����
                                                  */
/************************************************************************/
SMARTCOM_API int CheckBatchResult(Communicator& comm,SmartCom::string& retCode,int macNo=255);

/************************************************************************/
/* ���ܣ�
��SST25VF016B�洢��������Ƭ����
��ڲ�����
comm:����ͨ�ŵ�ͨ����
macNO:���ţ�Ĭ��255 
���ڲ�������
 ����ֵ��
0: �����ɹ�
-1��ͨ�ų�ʱ����
-2��ͨ������Ч
-3�����ŷ�Χ����
-4������ʧ��

/************************************************************************/
SMARTCOM_API int ClearMem(Communicator& comm,int macNo=255);

#endif