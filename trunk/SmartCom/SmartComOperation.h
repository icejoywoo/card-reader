#ifndef __SmartComOperation_H__
#define __SmartComOperation_H__

#include "SmartComString.h"

#ifdef SMARTCOMOP_EXPORTS
#define SMARTCOMOP_API  __declspec(dllexport) 
#else 
#define SMARTCOMOP_API  __declspec(dllimport) 
#endif

typedef unsigned char BYTE;
struct Communicator;
//ops
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
��NULL��ָ��һ����Ч��ͨ����ָ��
SC_NULL��ʧ��
/************************************************************************/
SMARTCOMOP_API Communicator* GetCOMCommunicator(int comPort,int rate=115200,
									   int waitForSTX2Time=500,int normalWaitTime=500 );

/************************************************************************
���ܣ�
��ȡһ��udpͨ������
��ڲ�����
dstIP:Ŀ��ip
port��Ŀ�Ķ˿�
waitForSTX2Time����һ���ַ���ʱ��Ĭ��1000ms
normalWaitTime���м��ַ���ʱ��Ĭ��1000ms
���ڲ���:
��
����ֵ��
��NULL��ָ��һ����Ч��ͨ����ָ��
SC_NULL��ʧ��
***********************************************************************/
SMARTCOMOP_API Communicator* GetUDPCommunicator(const char* dstIP,int port,
									   int waitForSTX2Time=500,int normalWaitTime=500);

/****************************************************************************
*���ܣ��ͷ�ͨ����
*��ڲ���
pcomm��ָ��Ҫ�ͷŵ�ͨ������ָ��
����
SC_SUCCESS���ɹ�
SCERR_OPERROR��ʧ��
SCERR_INVALID_COMM: ͨ������Ч
****************************************************************************/
SMARTCOMOP_API int ReleaseCommunicator(Communicator* pcomm);

/************************************************************************
���ܣ�
��ȡ�ն��豸id�źͻ���
��ڲ�����
pcomm:����ͨ�ŵ�ͨ����
devIDBufLen: devID����ĳ���
���ڲ���:
DevID�����7�ֽ�id��,
MacNo:1�ֽڻ���
����ֵ��
SC_SUCCESS����ȡ�ɹ�
SCERR_TIMEOUT��ͨ�ų�ʱ����
SCERR_INVALID_COMM: ͨ������Ч
SCERR_OPERROR: ��ȡʧ��
/************************************************************************/
SMARTCOMOP_API int GetDevIDAndMacNo(Communicator* pcomm,SmartCom::string& devID,int& macNo);

/************************************************************************/
/*���ܣ�
ͨ���ն��豸ID�Ÿ��ն��豸���û���
��ڲ�����
pcomm:����ͨ�ŵ�ͨ����
DevID:���7���ֽڵ��豸ID
MacNo:Ҫ���õĻ���
���ڲ�������
����ֵ��
SC_SUCCESS�����óɹ�
SCERR_TIMEOUT��ͨ�ų�ʱ����
SCERR_INVALID_COMM:ͨ������Ч
SCERR_MACNO_OUTRANGE:���ŷ�Χ����
SCERR_OPERROR������ʧ��                                                      */
/************************************************************************/
SMARTCOMOP_API int SetMacNoByDevID(Communicator* pcomm,const char* devID,int macNo);

/************************************************************************/
/* ���ܣ�
��ȡ����汾���ն�����
��ڲ�����
pcomm:����ͨ�ŵ�ͨ����
���ţ�Ĭ��255
���ڲ����� 
appVersion:����汾
devType:�ն�����
����ֵ��
SC_SUCCESS����ȡ�ɹ�
SCERR_TIMEOUT��ͨ�ų�ʱ����
SCERR_INVALID_COMM��ͨ������Ч
SCERR_MACNO_OUTRANGE: ���ŷ�Χ����
SCERR_OPERROR����ȡʧ��                                                     */
/************************************************************************/
SMARTCOMOP_API int GetAppVerAndDevType(Communicator* pcomm,SmartCom::string& appVersion,SmartCom::string& devType,
									 int MacNo=255);
/************************************************************************/
/* ���ܣ�
��ȡ�����ӿ�оƬID��
��ڲ�����
comm:����ͨ�ŵ�ͨ����
macNo:���ţ�Ĭ��255
���ڲ�����
chipID
����ֵ��
SC_SUCCESS���ɹ�
SCERR_TIMEOUT��ͨ�ų�ʱ����
SCERR_INVALID_COMM��ͨ������Ч
SCERR_MACNO_OUTRANGE:���ŷ�Χ����
SCERR_OPERROR����ȡʧ��                                                          */
/************************************************************************/
SMARTCOMOP_API int GetChipID(Communicator* comm,SmartCom::string& chipID,int macNo=255);

/************************************************************************/
/* ���ܣ�
���A�����󿨣�����B����SIM�������Ƿ��п�
��ڲ�����
comm:����ͨ�ŵ�ͨ����
macNO:���ţ�Ĭ��255
���ڲ�����
card: ���card&CARDA_FLAG=1,A�����������card&CARDB_FLAG=1,B������
����ֵ��
SC_SUCCESS�����ɹ�
SCERR_TIMEOUT��ͨ�ų�ʱ����
SCERR_INVALID_COMM��ͨ������Ч
SCERR_MACNO_OUTRANGE:���ŷ�Χ����
SCERR_OPERROR�����ʧ��                                                                     */
/************************************************************************/
SMARTCOMOP_API int IsCardReady(Communicator* comm,int& card,int macNo=255);

/************************************************************************/
/* ���ܣ�
��Ƭ��λӦ��
��ڲ�����
comm:����ͨ�ŵ�ͨ����
card��CARD_A:A����CARD_B��B��,Ĭ��ѡ��A��
macNO:���ţ�Ĭ��255
���ڲ�����
retCode:��λ����ķ���ֵ
retCode="F9"�������޿�
retCode="FD"������ʶ��
����ֵ��
SC_SUCCESS���ɹ�
SCERR_TIMEOUT��ͨ�ų�ʱ����
SCERR_INVALID_COMM��ͨ������Ч  
SCERR_MACNO_OUTRANGE: ���ŷ�Χ����
SCERR_OPERROR:��λʧ��                                                              */
/************************************************************************/
SMARTCOMOP_API int ResetCard(Communicator* comm,SmartCom::string& retCode,CARD_AB card=CARD_A,int macNo=255);

/************************************************************************/
/* ���ܣ�
��Ƭ����-APDU
��ڲ�����
comm:����ͨ�ŵ�ͨ����
apdu:ʮ�������ַ�����ʾ��apdu����
card��CARD_A:A����CARD_B��B��,Ĭ��ѡ��A��
macNO:���ţ�Ĭ��255
���ڲ�����
retCode:ִ��apduָ��ķ���ֵ
retCode="F9"�������޿�
retCode="FD"������ʶ��
retCode="F2"�� ��Ч7816�����
retCode="F0"�� û���ȸ��������ϵ縴λ
����ֵ��
SC_SUCCESS��ͨ�ųɹ�
SCERR_TIMEOUT��ͨ�ų�ʱ����
SCERR_INVALID_COMM��ͨ������Ч 
SCERR_MACNO_OUTRANGE: ���ŷ�Χ����                                                                */
/************************************************************************/
SMARTCOMOP_API int CardApdu(Communicator* comm,const char* apdu,SmartCom::string& retCode,
							CARD_AB card=CARD_A,int macNo=255);

/************************************************************************/
/* ���ܣ�
��Ƭ����-APDU,�˺������Զ���ָ��һ��ִ�У���ʽΪÿ��ָ����һ�������Ű����ķ�����
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
ͨ���� ȡ�þ��嶨��,SC_SERIAL()��ȡ�õ�ֵΪִ�е��ڼ���ָ�
SC_CODE()��ȡ�õ�ֵΪִ�н����
SC_SUCCESS:�ɹ�
SCERR_TIMEOUT:ͨ�ų�ʱ
SCERR_CMDFORMAT_ERR:�����ʽ��
SCERR_INVALID_COMM��ͨ������Ч
SCERR_MACNO_OUTRANGE: ���ŷ�Χ����
SCERR_OPERROR:ִ�г���retcode��Ӧ���һ��ָ��ķ�����                              */
/************************************************************************/
SMARTCOMOP_API int CardApduK(Communicator* comm,const char* apdu,SmartCom::string& retCode,int card=1,int macNo=255);

/************************************************************************/
/* ���ܣ���Ƭ�µ�
��ڲ�����
comm:����ͨ�ŵ�ͨ����
macNO:���ţ�Ĭ��255
���ڲ�������
����ֵ��
SC_SUCCESS���µ�ɹ�
SCERR_TIMEOUT��ͨ�ų�ʱ����
SCERR_INVALID_COMM��ͨ������Ч
SCERR_MACNO_OUTRANGE: ���ŷ�Χ����
SCERR_OPERROR���µ�ʧ��
                                                    */
/************************************************************************/
SMARTCOMOP_API int ShutdownCard(Communicator* comm,int macNo=255);

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
SC_SUCCESS���޸ĳɹ�
SCERR_TIMEOUT��ͨ�ų�ʱ����
SCERR_INVALID_COMM��ͨ������Ч
SCERR_MACNO_OUTRANGE: ���ŷ�Χ����
SCERR_OPERROR���޸�ʧ��
                                                              */
/************************************************************************/
SMARTCOMOP_API int ModifyCardBraudRate(Communicator* comm,int braudRate,int macNo=255);

/************************************************************************/
/* ���ܣ�
����ͨ�Ų�����
��ڲ���:
comm:����ͨ�ŵ�ͨ����
macNO:���ţ�Ĭ��255
���ڲ�����
braudRate����ǰ����ͨ�Ų�����
����ֵ��
SC_SUCCESS����ȡ�ɹ�
SCERR_TIMEOUT��ͨ�ų�ʱ����
SCERR_INVALID_COMM��ͨ������Ч
SCERR_MACNO_OUTRANGE: ���ŷ�Χ����
SCERR_OPERROR����ȡʧ��
                                                            */
/************************************************************************/
SMARTCOMOP_API int GetCardBraudRate(Communicator* comm,int& braudRate,int macNo=255);

/************************************************************************/
/* ���ܣ�
�޸Ŀ�Ƭ��Դ
��ڲ���:
comm:����ͨ�ŵ�ͨ����
power����Դ��power=POWER_5V: 5v��power=POWER_3V: 3v��power=POWER_1_8V: 1.8v
card:1:A����2��B��,Ĭ��ѡ��A��
macNO:���ţ�Ĭ��255
���ڲ�������
����ֵ��
SC_SUCCESS���޸ĳɹ�
SCERR_TIMEOUT��ͨ�ų�ʱ����
SCERR_INVALID_COMM��ͨ������Ч
SCERR_MACNO_OUTRANGE: ���ŷ�Χ����
SCERR_OPERROR:�޸�ʧ��
                                                            */
/************************************************************************/
SMARTCOMOP_API int ModifyCardPower(Communicator* comm,CARD_POWER power,CARD_AB card=CARD_A,int macNo=255);

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
SC_SUCCESS���ɹ�
SCERR_TIMEOUT��ͨ�ų�ʱ����
SCERR_INVALID_COMM��ͨ������Ч
SCERR_MACNO_OUTRANGE: ���ŷ�Χ����
SCERR_OPERROR: ����ʧ��
                                                               */
/************************************************************************/
SMARTCOMOP_API int  ExcuteMulAPDU(Communicator* comm,int cmdNum,CARD_AB card=CARD_A,int macNo=255);

/************************************************************************/
/* ���ܣ�
����ִ��������APDU����,���ȴ���������ɺ�ŷ���
��ڲ�����
comm:����ͨ�ŵ�ͨ����  
card:ѡ��ִ�еĿ���card=1ΪA����2ΪB����Ĭ��A��
cmdNum:Ҫִ�е�ָ������
macNO:���ţ�Ĭ��255
���ڲ�������
����ֵ��
SC_SUCCESS���ɹ�
SCERR_TIMEOUT��ͨ�ų�ʱ����
SCERR_INVALID_COMM��ͨ������Ч
SCERR_MACNO_OUTRANGE: ���ŷ�Χ����
SCERR_OPERROR: ����ʧ��
*/
/************************************************************************/
SMARTCOMOP_API int  ExcuteMulAPDUSyn(Communicator* comm,int cmdNum,CARD_AB card=CARD_A,int macNo=255);

/************************************************************************/
/* ���ܣ�
������������ƽű��ļ�
��ڲ�����
comm:����ͨ�ŵ�ͨ����
bytes:Ҫ��ȡ���ֽ���
 macNO:���ţ�Ĭ��255 
 offset:��ȡ���ݵ��ļ�ƫ�Ƶ�ַ
 ���ڲ�����
 strData:��ȡ��ת����ʮ�������ַ���������
 ����ֵ��
SC_SUCCESS����ȡ�ɹ�
SCERR_TIMEOUT��ͨ�ų�ʱ����
SCERR_INVALID_COMM��ͨ������Ч
SCERR_MACNO_OUTRANGE: ���ŷ�Χ����
SCERR_OPERROR: ��ȡʧ��
                                                              */
/************************************************************************/
SMARTCOMOP_API int GetScriptData(Communicator* comm,int offset,unsigned char bytes,SmartCom::string& strData,int macNo=255);

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
SC_SUCCESS�����سɹ�
SCERR_TIMEOUT��ͨ�ų�ʱ����
SCERR_INVALID_COMM��ͨ������Ч
SCERR_MACNO_OUTRANGE: ���ŷ�Χ����
SCERR_OPERROR: ����ʧ��
SCERR_OPENFILE_FAIL:�ļ���ʧ��
                                                           */
/************************************************************************/
SMARTCOMOP_API int DownloadFile(Communicator* comm,FILE_TYPE flag,const char* fileName,int macNo=255);

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
SC_SUCCESS�����سɹ�
SCERR_TIMEOUT��ͨ�ų�ʱ����
SCERR_INVALID_COMM��ͨ������Ч
SCERR_MACNO_OUTRANGE: ���ŷ�Χ����
SCERR_OPERROR: ����ʧ��
SCERR_OPENFILE_FAIL:�ļ���ʧ��
SCERR_DRIVER_NOTINSTALL:��������δ��װ
                                                           */
/************************************************************************/
SMARTCOMOP_API int DownloadFileK(Communicator* comm,FILE_TYPE flag,const char* fileName,int macNo=255);

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
SC_EXCUTING������ִ��
SCERR_INVALID_COMM��ͨ������Ч
SCERR_MACNO_OUTRANGE: ���ŷ�Χ����
                                                  */
/************************************************************************/
SMARTCOMOP_API int CheckBatchResult(Communicator* comm,SmartCom::string& retCode,int macNo=255);


/************************************************************************/
/* ���ܣ�
��SST25VF016B�洢��������Ƭ����
��ڲ�����
comm:����ͨ�ŵ�ͨ����
macNO:���ţ�Ĭ��255 
���ڲ�������
 ����ֵ��
SC_SUCCESS: �����ɹ�
SCERR_TIMEOUT��ͨ�ų�ʱ����
SCERR_INVALID_COMM��ͨ������Ч
SCERR_MACNO_OUTRANGE: ���ŷ�Χ����
SCERR_OPERROR������ʧ��

/************************************************************************/
SMARTCOMOP_API int ClearMem(Communicator* comm,int macNo=255);

/************************************************************************/
/* ���ܣ�
���ö���APDU��������ɺ��Զ����ش�
��ڲ�����
comm:����ͨ�ŵ�ͨ����
macNO:���ţ�Ĭ��255 
���ڲ�������
����ֵ��
SC_SUCCESS: ���óɹ�
SCERR_TIMEOUT��ͨ�ų�ʱ����
SCERR_INVALID_COMM��ͨ������Ч
SCERR_MACNO_OUTRANGE: ���ŷ�Χ����
SCERR_OPERROR������ʧ��

/************************************************************************/
SMARTCOMOP_API int EnableAutoAnswer(Communicator* comm,int macNo=255);

/************************************************************************/
/* ���ܣ�
��ֹ����APDU��������ɺ��Զ����ش�
��ڲ�����
comm:����ͨ�ŵ�ͨ����
macNO:���ţ�Ĭ��255 
���ڲ�������
����ֵ��
SC_SUCCESS: ���óɹ�
SCERR_TIMEOUT��ͨ�ų�ʱ����
SCERR_INVALID_COMM��ͨ������Ч
SCERR_MACNO_OUTRANGE: ���ŷ�Χ����
SCERR_OPERROR������ʧ��

/************************************************************************/
SMARTCOMOP_API int DisableAutoAnswer(Communicator* comm,int macNo=255);

/************************************************************************/
/* ���ܣ�
���÷�������ʱ����,ʵ�ʼ��=5*��0��255����S
��ڲ�����
comm:����ͨ�ŵ�ͨ����
interval:0~255,��λ��S��ʵ�ʼ��=5*��0��255����S
macNO:���ţ�Ĭ��255 
���ڲ�������
����ֵ��
SC_SUCCESS: ���óɹ�
SCERR_TIMEOUT��ͨ�ų�ʱ����
SCERR_INVALID_COMM��ͨ������Ч
SCERR_MACNO_OUTRANGE: ���ŷ�Χ����
SCERR_OPERROR������ʧ��

/************************************************************************/
SMARTCOMOP_API int SetSendInterval(Communicator* comm,BYTE interval,int macNo=255);


#endif