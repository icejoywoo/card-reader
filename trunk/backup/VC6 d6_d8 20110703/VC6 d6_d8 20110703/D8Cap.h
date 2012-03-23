#ifndef D8CAP_H
#define D8CAP_H

#include <windows.h> 
#include <stdio.h> 

typedef __int16 (__stdcall *myDcCard)(HANDLE icdev,unsigned char _Mode,unsigned long *_Snr);

typedef HANDLE (__stdcall *myDcInit)(__int16 port,long baud);
typedef __int16  (__stdcall *myDcLoadKey)(HANDLE icdev,unsigned char _Mode,unsigned char _SecNr,unsigned char *_NKey);
typedef __int16 (__stdcall *myDcAuth)(HANDLE icdev,unsigned char _Mode,unsigned char _SecNr);
typedef __int16  (__stdcall *myDcAuth2)(HANDLE icdev,unsigned char _Mode,unsigned char KeyNr,unsigned char Adr);

typedef __int16 (__stdcall *myDcRead)(HANDLE icdev,unsigned char _Adr,unsigned char *_Data);
typedef __int16 (__stdcall *myDcWrite)(HANDLE icdev,unsigned char _Adr,unsigned char *_Data);
typedef __int16 (__stdcall *myDcBeep)(HANDLE icdev,unsigned short _Msec);
typedef __int16 (__stdcall *myDcExit)(HANDLE icdev);
typedef __int16 (__stdcall *myDcRequest)(HANDLE icdev,unsigned char _Mode,unsigned __int16  *TagType);
typedef __int16 (__stdcall *myDcSelect)(HANDLE icdev,unsigned long _Snr,unsigned char *_Size);
typedef __int16 (__stdcall *myDcAnticoll)(HANDLE icdev,unsigned char _Bcnt,unsigned long *_Snr);
typedef __int16 (__stdcall *myDcAuthPass)(HANDLE icdev,unsigned char _Mode, unsigned char _Addr,unsigned char *passbuff);
typedef __int16 (__stdcall *myDcHalt)(HANDLE icdev);
typedef __int16 (__stdcall *myDcChangeb3)(HANDLE icdev,unsigned char _SecNr,unsigned char *_KeyA,
									   unsigned char _B0,unsigned char _B1,unsigned char _B2,
									   unsigned char _B3,unsigned char _Bk,unsigned char *_KeyB);
typedef __int16  (__stdcall *myDcHLAuthentication)(HANDLE icdev,unsigned char reqmode,unsigned long snr,
												unsigned char authmode,unsigned char secnr);
typedef __int16 (__stdcall *myDcCheckWrite)(HANDLE icdev,unsigned long Snr,unsigned char authmode,
										  unsigned char Adr,unsigned char * _data);
typedef __int16 (__stdcall *myDcHLRead)(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,
									  unsigned long _Snr,unsigned char *_Data,unsigned long *_NSnr);
typedef __int16 (__stdcall *myDcHLWrite)(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,
									   unsigned long *_Snr,unsigned char *_Data);
typedef __int16  (__stdcall *myDcDesHex)(unsigned char *key,unsigned char *sour,unsigned char *dest,
									  __int16 m);

//added on 20110627
typedef __int16 (__stdcall *myDcReadblock)(HANDLE icdev,unsigned char flags,
							   unsigned char startblock,unsigned char blocknum, 
							   unsigned char *UID, 
							   unsigned char *rlen,unsigned char *rbuffer);
typedef __int16 (__stdcall *myDcReadblockHex)(HANDLE icdev,unsigned char flags,
								   unsigned char startblock,unsigned char blocknum, 
								   unsigned char *UID, 
								   unsigned char *rlen,unsigned char *rbuffer);
typedef __int16 (__stdcall *myDcWriteblock)(HANDLE icdev,unsigned char flags,
								unsigned char startblock,unsigned char blocknum, 
								unsigned char *UID, 
								unsigned char wlen,unsigned char *rbuffer);
typedef __int16 (__stdcall *myDcWriteblockHex)(HANDLE icdev,unsigned char flags,
									unsigned char startblock,unsigned char blocknum, 
									unsigned char *UID, 
								unsigned char wlen,unsigned char *rbuffer);


typedef __int16 ( __stdcall  *myDcCardAB)(HANDLE icdev,unsigned char *rlen,unsigned char *rbuf,unsigned char *type);
//added on 20110627

//带Hex函数
typedef __int16 (__stdcall *myDcCardHex)(HANDLE icdev,unsigned char _Mode,unsigned char *snrstr);
typedef __int16 (__stdcall *myDcLoadKeyHex)(HANDLE icdev,unsigned char _Mode,unsigned char _SecNr,char *_NKey);
typedef __int16 (__stdcall *myDcAuthenticationPathHex)(HANDLE icdev,unsigned char _Mode,unsigned char _Addr,unsigned char *passbuff);
typedef __int16 (__stdcall *myDcReadHex)(HANDLE icdev,unsigned char _Adr,char *_Data);
typedef __int16 (__stdcall *myDcWriteHex)(HANDLE icdev,unsigned char _Adr,char *_Data);
typedef __int16 (__stdcall *myDcSrdEepromHex)(HANDLE icdev,__int16   offset,__int16   lenth,unsigned char *rec_buffer);
typedef __int16 (__stdcall *myDcSwrEepromHex)(HANDLE icdev,__int16   offset,__int16   lenth, unsigned char* send_buffer);
typedef __int16 (__stdcall *myDcCpuapduHex)(HANDLE icdev,unsigned char slen, char * sendbuffer,unsigned char *rlen, char * databuffer);
typedef __int16 (__stdcall *myDcCpuresetHex)(HANDLE icdev,unsigned char *rlen, char *databuffer);

//值操作
typedef __int16 (__stdcall *myDcInitval)(HANDLE icdev,unsigned char _Adr,unsigned long _Value);
typedef __int16 (__stdcall *myDcReadVal)(HANDLE icdev,unsigned char _Adr,unsigned long *_Value);
typedef __int16 (__stdcall *myDcIncrement)(HANDLE icdev,unsigned char _Adr,unsigned long _Value);
typedef __int16 (__stdcall *myDcDecrement)(HANDLE icdev,unsigned char _Adr,unsigned long _Value);
typedef __int16 (__stdcall *myDcRestore)(HANDLE icdev,unsigned char _Adr);
//设备函数
typedef __int16  (__stdcall *myDcSwrEeprom)(HANDLE icdev,__int16   offset,__int16 lenth,
											unsigned char* send_buffer);
typedef __int16 (__stdcall *myA_hex)(unsigned char *a,unsigned char *hex,__int16 len);
typedef __int16 (__stdcall *myHex_a)(unsigned char *hex,unsigned char *a,__int16 length);
typedef __int16 (__stdcall *myDc_Reset)(HANDLE icdev,unsigned __int16   _Msec);
typedef __int16 (__stdcall *myDc_Cpuapdu)(HANDLE icdev,unsigned char slen,unsigned char * sendbuffer,
										  unsigned char *rlen,unsigned char * databuffer);
typedef __int16 (__stdcall *myDc_Cpuapdusource)(HANDLE icdev,unsigned char slen,unsigned char * sendbuffer,
												unsigned char *rlen,unsigned char * databuffer);
typedef __int16 (__stdcall *myDc_Cpureset)(HANDLE icdev,unsigned char *rlen,unsigned char *databuffer);

typedef __int16 (__stdcall *myDc_Setcpu)(HANDLE icdev,unsigned char _Byte);

//接触式界面CPU卡
typedef __int16 ( __stdcall  *myDc_Setcpupara)(HANDLE icdev,unsigned char cputype,
											   unsigned char cpupro,unsigned char cpuetu);

typedef __int16  (__stdcall *myDc_Srd_eeprom)(HANDLE icdev,__int16   offset,__int16 lenth,
											  unsigned char *rec_buffer);

typedef __int16 (__stdcall *myDc_Getver)(HANDLE icdev,unsigned char *sver);
typedef __int16  (__stdcall *myDc_Beep)(HANDLE icdev,unsigned short _Msec);
typedef __int16  (__stdcall *myDc_Transfer)(HANDLE icdev,unsigned char _Adr);
typedef __int16  (__stdcall *myDc_Restore)(HANDLE icdev,unsigned char _Adr);

//RFMA专用
typedef __int16 (__stdcall *myDcGettime)(HANDLE icdev,unsigned char *time);
typedef __int16 (__stdcall *myDcDispMode)(HANDLE icdev,unsigned char mode);
typedef __int16 (__stdcall *myDcHighDisp)(HANDLE icdev,unsigned char offset,unsigned char displen,unsigned char *dispstr);
typedef __int16 (__stdcall *myDcSetBright)(HANDLE icdev,unsigned char bright);
typedef __int16 (__stdcall *myDcDispStr)(HANDLE icdev,char *dispstr);
typedef __int16 (__stdcall *myDcSettime)(HANDLE icdev,unsigned char *time);

//NEW ADD BY ZXB 091116
typedef __int16 (__stdcall *myDcGetcpupara)(HANDLE icdev,unsigned char cputype,unsigned char *cpupro,unsigned char *cpuetu);
typedef __int16 (__stdcall *myDcCpuApduSourceExt)(HANDLE icdev,__int16 slen,unsigned char * sendbuffer,__int16 *rlen,unsigned char * databuffer);
typedef __int16 (__stdcall *myDcCpuApduSourceExtHex)(HANDLE icdev,__int16 slen, char * sendbuffer,__int16 *rlen, char * databuffer);
typedef __int16 (__stdcall *myDcCpuApduExt) (HANDLE icdev,__int16 slen,unsigned char * sendbuffer,__int16 *rlen,unsigned char * databuffer);
typedef __int16 (__stdcall *myDcCpuApduExtHex)(HANDLE icdev,__int16 slen,char * sendbuffer,__int16 *rlen,char * databuffer);

typedef __int16 (__stdcall *myDcProCommandLinkExt)(HANDLE idComDev,unsigned int slen,
										 unsigned char * sendbuffer,unsigned int *rlen,
										 unsigned char * databuffer,unsigned char timeout,
										 unsigned char FG);


typedef __int16 (__stdcall *myDCProReset)(HANDLE icdev,unsigned char *rlen,unsigned char *receive_data);
typedef __int16 (__stdcall *myDCProCommand)(HANDLE idComDev,unsigned char slen,
								 unsigned char * sendbuffer,unsigned char *rlen,
								 unsigned char * databuffer,unsigned char timeout);

typedef __int16  (__stdcall * myDCProHalt)(HANDLE icdev);
typedef __int16  (__stdcall * myDCConfig)(HANDLE icdev,unsigned char _Mode,unsigned char _Baud); 


typedef __int16 (__stdcall *myDCCardDouble)(HANDLE icdev,unsigned char _Mode,unsigned char *_Snr);
typedef __int16 (__stdcall *myDCCardDoubleHex)(HANDLE icdev,unsigned char _Mode,unsigned char *_Snr);


typedef __int16  (__stdcall *myDCGettimehex)(HANDLE icdev,char *time);
typedef __int16  (__stdcall *myDCSettimehex)(HANDLE icdev,char *time);



typedef __int16  (__stdcall * myDCProCommandsource)(HANDLE idComDev,unsigned char slen,
													unsigned char * sendbuffer,unsigned char *rlen,
                                                    unsigned char * databuffer,unsigned char timeout);

typedef __int16  (__stdcall * myDCProCommandsourceHex)(HANDLE idComDev,unsigned char slen,
													   char * sendbuffer,unsigned char *rlen,
                                                       char * databuffer,unsigned char timeout);

typedef __int16 (__stdcall* myDCCpudown)(HANDLE icdev);
/***********************************自动生成代码***added by chch 20110703****************************/
/***********************************自动生成代码***added by chch 20110703****************************/
typedef __int16(__stdcall *func_type_dc_config)(HANDLE icdev,unsigned char _Mode,unsigned char _Baud);
typedef __int16(__stdcall *func_type_dc_write_TS)(HANDLE icdev);
typedef __int16(__stdcall *func_type_dc_initval_ml)(HANDLE icdev,unsigned __int16   _Value);
typedef __int16(__stdcall *func_type_dc_readval_ml)(HANDLE icdev,unsigned __int16   *_Value);
typedef __int16(__stdcall *func_type_dc_authentication_2)(HANDLE icdev,unsigned char _Mode,unsigned char KeyNr,unsigned char Adr);
typedef __int16(__stdcall *func_type_dc_anticoll2)(HANDLE icdev,unsigned char _Bcnt,unsigned long *_Snr);
typedef __int16(__stdcall *func_type_dc_select2)(HANDLE icdev,unsigned long _Snr,unsigned char *_Size);
typedef __int16(__stdcall *func_type_dc_HL_writehex)(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,unsigned long *_Snr,unsigned char *_Data);
typedef __int16(__stdcall *func_type_dc_HL_readhex)(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,unsigned long _Snr,unsigned char *_Data,unsigned long *_NSnr);
typedef __int16(__stdcall *func_type_dc_check_writehex)(HANDLE icdev,unsigned long Snr,unsigned char authmode,unsigned char Adr,unsigned char * _data);
typedef __int16(__stdcall *func_type_dc_clr_control_bit)(HANDLE icdev,unsigned char _b);
typedef __int16(__stdcall *func_type_dc_set_control_bit)(HANDLE icdev,unsigned char _b);
typedef __int16(__stdcall *func_type_dc_swr_eeprom)(HANDLE icdev,__int16   offset,__int16 lenth,unsigned char* send_buffer);
typedef __int16(__stdcall *func_type_swr_alleeprom)(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char* snd_buffer);
typedef __int16(__stdcall *func_type_srd_alleeprom)(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char *receive_buffer);
typedef __int16(__stdcall *func_type_dc_ctl_mode)(HANDLE icdev,unsigned char mode);
typedef __int16(__stdcall *func_type_dcdeshex)(unsigned char *key,unsigned char *sour,unsigned char *dest,__int16 m);
typedef __int16(__stdcall *func_type_dcdes)(unsigned char *key,unsigned char *sour,unsigned char *dest,__int16 m);
typedef __int16(__stdcall *func_type_dc_light)(HANDLE icdev,unsigned short _OnOff);
typedef __int16(__stdcall *func_type_dc_setcpu)(HANDLE icdev,unsigned char _Byte);
typedef __int16(__stdcall *func_type_dc_cpuapdu)(HANDLE icdev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer);
typedef __int16(__stdcall *func_type_dc_cpuapdusource_hex)(HANDLE icdev,unsigned char slen, char * sendbuffer,unsigned char *rlen, char * databuffer);
typedef __int16(__stdcall *func_type_dc_cpuapdurespon)(HANDLE idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer);
typedef __int16(__stdcall *func_type_dc_cpuapdurespon_hex)(HANDLE idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer);
typedef __int16(__stdcall *func_type_dc_set_addr)(unsigned char saddr);
typedef HANDLE(__stdcall *func_type_dc_init_485)(__int16 port,long baud);
typedef __int16(__stdcall *func_type_dc_changebaud_485)(HANDLE icdev,long baud);
typedef __int16(__stdcall *func_type_dc_change_addr)(HANDLE icdev,unsigned char saddr);
typedef __int16(__stdcall *func_type_dc_pro_resethex)(HANDLE icdev,unsigned char *rlen, char *receive_data);
typedef __int16(__stdcall *func_type_dc_pro_commandhex)(HANDLE idComDev,unsigned char slen,char * sendbuffer,unsigned char *rlen,char * databuffer,unsigned char timeout);
typedef __int16(__stdcall *func_type_dc_pro_halt)(HANDLE icdev);
typedef __int16(__stdcall *func_type_dc_request_shc1102)(HANDLE icdev,unsigned char _Mode,unsigned __int16 *TagType);
typedef __int16(__stdcall *func_type_dc_auth_shc1102)(HANDLE icdev,unsigned char *_Data);
typedef __int16(__stdcall *func_type_dc_read_shc1102)(HANDLE icdev,unsigned char _Adr,unsigned char *_Data);
typedef __int16(__stdcall *func_type_dc_write_shc1102)(HANDLE icdev,unsigned char _Adr,unsigned char *_Data);
typedef __int16(__stdcall *func_type_dc_halt_shc1102)(HANDLE icdev);
typedef __int16(__stdcall *func_type_dc_config_card)(HANDLE icdev,unsigned char cardtype);
typedef __int16(__stdcall *func_type_dc_request_b)(HANDLE icdev,unsigned char _Mode,unsigned char AFI,unsigned char N,unsigned char *ATQB);
typedef __int16(__stdcall *func_type_dc_slotmarker)(HANDLE icdev,unsigned char N, unsigned char *ATQB);
typedef __int16(__stdcall *func_type_dc_attrib)(HANDLE icdev,unsigned char *PUPI, unsigned char CID);
typedef __int16(__stdcall *func_type_dc_open_door)(HANDLE icdev,unsigned char cflag);
typedef __int16(__stdcall *func_type_dc_open_timedoor)(HANDLE icdev,unsigned __int16 utime);
typedef __int16(__stdcall *func_type_dc_read_random)(HANDLE icdev, unsigned char *data);
typedef __int16(__stdcall *func_type_dc_write_random)(HANDLE icdev,__int16 len, unsigned char *data);
typedef __int16(__stdcall *func_type_dc_read_random_hex)(HANDLE icdev, unsigned char *data);
typedef __int16(__stdcall *func_type_dc_write_random_hex)(HANDLE icdev,__int16 len, unsigned char *data);
typedef __int16(__stdcall *func_type_dc_erase_random)(HANDLE icdev,__int16 len);
typedef __int16(__stdcall *func_type_dc_mfdes_auth)(HANDLE icdev,unsigned char keyno,unsigned char keylen,unsigned char *authkey,unsigned char *randAdata,unsigned char *randBdata);
typedef __int16(__stdcall *func_type_dc_disp_neg)(HANDLE icdev,char *dispstr);
typedef __int16(__stdcall *func_type_dc_pro_commandlink)(HANDLE idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer,unsigned char timeout,unsigned char FG);
typedef __int16(__stdcall *func_type_dc_pro_commandlink_hex)(HANDLE idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer,unsigned char timeout,unsigned char FG);
typedef __int16(__stdcall *func_type_dc_read_idcard)(HANDLE icdev,unsigned char times,unsigned char *_Data);
typedef __int16(__stdcall *func_type_dc_read_idcard_hex)(HANDLE icdev,unsigned char times,unsigned char *_Data);
typedef __int16(__stdcall *func_type_dc_authentication_pass_hex)(HANDLE icdev,unsigned char _Mode,unsigned char _Addr,unsigned char *passbuff);
typedef __int16(__stdcall *func_type_dc_setcpupara)(HANDLE icdev,unsigned char cputype,unsigned char cpupro,unsigned char cpuetu);
typedef __int16(__stdcall *func_type_dc_command)(HANDLE idComDev,unsigned char cmd,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer);
typedef __int16(__stdcall *func_type_dc_command_hex)(HANDLE idComDev,unsigned char cmd,unsigned char slen,char * sendbuffer,unsigned char *rlen,char * databuffer);
typedef __int16(__stdcall *func_type_dc_creat_mac)(unsigned char KeyLen,unsigned char *Key,unsigned short DataLen,unsigned char *Data,unsigned char *InitData,unsigned char AutoFixFlag,unsigned char FixChar,unsigned char *MacData);
typedef __int16(__stdcall *func_type_dc_creat_mac_hex)(unsigned char KeyLen,unsigned char *Key,unsigned short DataLen,unsigned char *Data,unsigned char *InitData,unsigned char AutoFixFlag,unsigned char FixChar,unsigned char *MacData);
typedef __int16(__stdcall *func_type_dc_HL_write_hex)(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,unsigned long *_Snr,unsigned char *_Data);
typedef __int16(__stdcall *func_type_dc_HL_read_hex)(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,unsigned long _Snr,unsigned char *_Data,unsigned long *_NSnr);
typedef __int16(__stdcall *func_type_dc_check_write_hex)(HANDLE icdev,unsigned long Snr,unsigned char authmode,unsigned char Adr,unsigned char * _data);
typedef __int16(__stdcall *func_type_dc_srd_eeprom_hex)(HANDLE icdev,__int16   offset,__int16   lenth,unsigned char *rec_buffer);
typedef __int16(__stdcall *func_type_dc_swr_eeprom_hex)(HANDLE icdev,__int16   offset,__int16   lenth,unsigned char* send_buffer);
typedef __int16(__stdcall *func_type_dc_gettime_hex)(HANDLE icdev,char *time);
typedef __int16(__stdcall *func_type_dc_settime_hex)(HANDLE icdev,char *time);
typedef __int16(__stdcall *func_type_dc_des)(unsigned char *key,unsigned char *sour,unsigned char *dest,__int16 m);
typedef __int16(__stdcall *func_type_dc_pro_reset_hex)(HANDLE icdev,unsigned char *rlen, char *receive_data);
typedef __int16(__stdcall *func_type_dc_pro_command_hex)(HANDLE idComDev,unsigned char slen,char * sendbuffer,unsigned char *rlen,char * databuffer,unsigned char timeout);
typedef __int16(__stdcall *func_type_dc_pro_commandsource_hex)(HANDLE idComDev,unsigned char slen,char * sendbuffer,unsigned char *rlen,char * databuffer,unsigned char timeout);
typedef __int16(__stdcall *func_type_dc_switch_unix)(HANDLE icdev,long baud);
typedef __int16(__stdcall *func_type_dc_authentication_passaddr)(HANDLE icdev,unsigned char _Mode,unsigned char _Addr,unsigned char *passbuff);
typedef __int16(__stdcall *func_type_dc_authentication_passaddr_hex)(HANDLE icdev,unsigned char _Mode,unsigned char _Addr,unsigned char *passbuff);
typedef __int16(__stdcall *func_type_dc_card_fm11rf005)(HANDLE icdev,unsigned char _Mode,unsigned long *_Snr);
typedef __int16(__stdcall *func_type_dc_setusbtimeout)(unsigned char ntimes);
typedef __int16(__stdcall *func_type_dc_mfdes_baud)(HANDLE icdev,unsigned char _Mode,unsigned char para);
typedef __int16(__stdcall *func_type_dc_tripledes)(unsigned char *key,unsigned char *src,unsigned char *dest,__int16 m);
typedef __int16(__stdcall *func_type_dc_tripledes_hex)(unsigned char *key,unsigned char *src,unsigned char *dest,__int16 m);
typedef __int16(__stdcall *func_type_dc_mfdes_auth_hex)(HANDLE icdev,unsigned char keyno,unsigned char keylen,unsigned char *authkey,unsigned char *randAdata,unsigned char *randBdata);
typedef __int16(__stdcall *func_type_dc_pro_sendcommandsource)(HANDLE idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char timeout);
typedef __int16(__stdcall *func_type_dc_pro_receivecommandsource)(HANDLE idComDev,unsigned char *rlen,unsigned char * databuffer);
typedef __int16(__stdcall *func_type_dc_inventory)(HANDLE icdev,unsigned char flags,unsigned char AFI,unsigned char masklen,unsigned char *rlen,unsigned char *rbuffer);
typedef __int16(__stdcall *func_type_dc_inventory_hex)(HANDLE icdev,unsigned char flags,unsigned char AFI,unsigned char masklen,unsigned char *rlen,unsigned char *rbuffer);
typedef __int16(__stdcall *func_type_dc_stay_quiet)(HANDLE icdev,unsigned char flags,unsigned char *UID);
typedef __int16(__stdcall *func_type_dc_stay_quiet_hex)(HANDLE icdev,unsigned char flags,unsigned char *UID);
typedef __int16(__stdcall *func_type_dc_select_uid)(HANDLE icdev,unsigned char flags,unsigned char *UID);
typedef __int16(__stdcall *func_type_dc_select_uid_hex)(HANDLE icdev,unsigned char flags,unsigned char *UID);
typedef __int16(__stdcall *func_type_dc_reset_to_ready)(HANDLE icdev,unsigned char flags,unsigned char *UID);
typedef __int16(__stdcall *func_type_dc_reset_to_ready_hex)(HANDLE icdev,unsigned char flags,unsigned char *UID);
typedef __int16(__stdcall *func_type_dc_lock_block)(HANDLE icdev,unsigned char flags,unsigned char block,unsigned char *UID);
typedef __int16(__stdcall *func_type_dc_lock_block_hex)(HANDLE icdev,unsigned char flags,unsigned char block,unsigned char *UID);
typedef __int16(__stdcall *func_type_dc_write_afi)(HANDLE icdev,unsigned char flags,unsigned char AFI,unsigned char *UID);
typedef __int16(__stdcall *func_type_dc_write_afi_hex)(HANDLE icdev,unsigned char flags,unsigned char AFI,unsigned char *UID);
typedef __int16(__stdcall *func_type_dc_lock_afi)(HANDLE icdev,unsigned char flags,unsigned char AFI,unsigned char *UID);
typedef __int16(__stdcall *func_type_dc_lock_afi_hex)(HANDLE icdev,unsigned char flags,unsigned char AFI,unsigned char *UID);
typedef __int16(__stdcall *func_type_dc_write_dsfid)(HANDLE icdev,unsigned char flags,unsigned char DSFID,unsigned char *UID);
typedef __int16(__stdcall *func_type_dc_write_dsfid_hex)(HANDLE icdev,unsigned char flags,unsigned char DSFID,unsigned char *UID);
typedef __int16(__stdcall *func_type_dc_lock_dsfid)(HANDLE icdev,unsigned char flags,unsigned char DSFID,unsigned char *UID);
typedef __int16(__stdcall *func_type_dc_lock_dsfid_hex)(HANDLE icdev,unsigned char flags,unsigned char DSFID,unsigned char *UID);
typedef __int16(__stdcall *func_type_dc_get_systeminfo)(HANDLE icdev,unsigned char flags,unsigned char *UID,unsigned char *rlen,unsigned char *rbuffer);
typedef __int16(__stdcall *func_type_dc_get_systeminfo_hex)(HANDLE icdev,unsigned char flags,unsigned char *UID,unsigned char *rlen,unsigned char *rbuffer);
typedef __int16(__stdcall *func_type_dc_get_securityinfo)(HANDLE icdev,unsigned char flags,unsigned char startblock,unsigned char blocknum,unsigned char *UID,unsigned char *rlen,unsigned char *rbuffer);
typedef __int16(__stdcall *func_type_dc_get_securityinfo_hex)(HANDLE icdev,unsigned char flags,unsigned char startblock,unsigned char blocknum,unsigned char *UID,unsigned char *rlen,unsigned char *rbuffer);
typedef __int16(__stdcall *func_type_dc_getsnr_fm11rf005)(HANDLE icdev,unsigned long *_Snr);
typedef __int16(__stdcall *func_type_dc_getsnr_fm11rf005_hex)(HANDLE icdev,unsigned char *snrstr);
typedef __int16(__stdcall *func_type_dc_write_fm11rf005)(HANDLE icdev,unsigned char _Adr,unsigned char *_Data);
typedef __int16(__stdcall *func_type_dc_read_fm11rf005)(HANDLE icdev,unsigned char _Adr,unsigned char *_Data);
typedef __int16(__stdcall *func_type_dc_read_fm11rf005_hex)(HANDLE icdev,unsigned char _Adr,char *_Data);
typedef __int16(__stdcall *func_type_dc_write_fm11rf005_hex)(HANDLE icdev,unsigned char _Adr,char *_Data);
typedef __int16(__stdcall *func_type_DCDEV_CommandMcu)(HANDLE idComDev,unsigned char ctimeout,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer);
typedef __int16(__stdcall *func_type_DCDEV_CommandMcu_Hex)(HANDLE idComDev,unsigned char ctimeout,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer);
typedef __int16(__stdcall *func_type_dc_displcd)(HANDLE idComDev,unsigned char flag);
typedef __int16(__stdcall *func_type_dc_getinputpass)(HANDLE idComDev,unsigned char ctime,unsigned char *rlen,unsigned char * cpass);
typedef __int16(__stdcall *func_type_dc_readmagcard)(HANDLE idComDev, unsigned char ctime, unsigned char *pTrack2Data, unsigned long *pTrack2Len, unsigned char *pTrack3Data, unsigned long *pTrack3Len);
typedef __int16(__stdcall *func_type_dc_testdevicecomm)(HANDLE idComDev);
typedef __int16(__stdcall *func_type_dc_dispmainmenu)(HANDLE idComDev);
typedef __int16(__stdcall *func_type_dc_setdevicetime)(HANDLE idComDev,unsigned char year,unsigned char month,unsigned char date,unsigned char hour,unsigned char minute,unsigned char second);
typedef __int16(__stdcall *func_type_dc_getdevicetime)(HANDLE idComDev,unsigned char *year,unsigned char *month,unsigned char *date,unsigned char *hour,unsigned char *minute,unsigned char *second);
typedef __int16(__stdcall *func_type_dc_dispinfo)(HANDLE idComDev,unsigned char line,unsigned char offset,char *data);
typedef __int16(__stdcall *func_type_dc_dispmaininfo)(HANDLE idComDev,unsigned char offset,char *data);
typedef __int16(__stdcall *func_type_dc_posbeep)(HANDLE idComDev,unsigned char beeptime);
typedef __int16(__stdcall *func_type_dc_ctlbacklight)(HANDLE idComDev, unsigned char cOpenFlag);
typedef __int16(__stdcall *func_type_dc_ctlled)(HANDLE idComDev, unsigned char cLed, unsigned char cOpenFlag);
typedef __int16(__stdcall *func_type_dc_lcdclrscrn)(HANDLE idComDev, unsigned char cLine);
typedef __int16(__stdcall *func_type_dc_passin)(HANDLE idComDev,unsigned char ctime);
typedef __int16(__stdcall *func_type_dc_passget)(HANDLE idComDev,unsigned char *rlen,unsigned char * cpass);
typedef __int16(__stdcall *func_type_dc_passcancel)(HANDLE idComDev);
typedef __int16(__stdcall *func_type_dc_getinputkey)(HANDLE idComDev,unsigned char disptype,unsigned char line,unsigned char ctime,unsigned char *rlen,unsigned char * ckeydata);
typedef __int16(__stdcall *func_type_dc_displcd_ext)(HANDLE idComDev,unsigned char flag,unsigned char row,unsigned char offset);
typedef __int16(__stdcall *func_type_dc_readmagcardall)(HANDLE idComDev, unsigned char ctime, unsigned char *pTrack1Data, unsigned long *pTrack1Len,unsigned char *pTrack2Data, unsigned long *pTrack2Len, unsigned char *pTrack3Data, unsigned long *pTrack3Len);
typedef __int16(__stdcall *func_type_dc_readdevsnr)(HANDLE idComDev,unsigned char *snr);
typedef __int16(__stdcall *func_type_dc_readreadersnr)(HANDLE idComDev,unsigned char *snr);
typedef __int16(__stdcall *func_type_dc_resetdevice)(HANDLE idComDev);
typedef __int16(__stdcall *func_type_dc_read_4442)(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * buffer);
typedef __int16(__stdcall *func_type_dc_read_4442_hex)(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char* buffer);
typedef __int16(__stdcall *func_type_dc_write_4442)(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * buffer);
typedef __int16(__stdcall *func_type_dc_write_4442_hex)(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char* buffer);
typedef __int16(__stdcall *func_type_dc_verifypin_4442)(HANDLE icdev,unsigned char *passwd);
typedef __int16(__stdcall *func_type_dc_verifypin_4442_hex)(HANDLE icdev,unsigned char *passwd);
typedef __int16(__stdcall *func_type_dc_readpin_4442)(HANDLE icdev,unsigned char *passwd);
typedef __int16(__stdcall *func_type_dc_readpin_4442_hex)(HANDLE icdev,unsigned char *passwd);
typedef __int16(__stdcall *func_type_dc_readpincount_4442)(HANDLE icdev);
typedef __int16(__stdcall *func_type_dc_changepin_4442)(HANDLE icdev,unsigned char *passwd);
typedef __int16(__stdcall *func_type_dc_changepin_4442_hex)(HANDLE icdev,unsigned char *passwd);
typedef __int16(__stdcall *func_type_dc_readwrotect_4442)(HANDLE icdev,__int16 offset,__int16 leng,unsigned char *buffer);
typedef __int16(__stdcall *func_type_dc_readwrotect_4442_hex)(HANDLE icdev,__int16 offset,__int16 leng,unsigned char *buffer);
typedef __int16(__stdcall *func_type_dc_writeprotect_4442)(HANDLE icdev,__int16 offset,__int16 leng,unsigned char *buffer);
typedef __int16(__stdcall *func_type_dc_writeprotect_4442_hex)(HANDLE icdev,__int16 offset,__int16 leng,unsigned char *buffer);
typedef __int16(__stdcall *func_type_dc_write_24c)(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * snd_buffer);
typedef __int16(__stdcall *func_type_dc_write_24c_hex)(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * snd_buffer);
typedef __int16(__stdcall *func_type_dc_write_24c64)(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * snd_buffer);
typedef __int16(__stdcall *func_type_dc_write_24c64_hex)(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * snd_buffer);
typedef __int16(__stdcall *func_type_dc_read_24c)(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * receive_buffer);
typedef __int16(__stdcall *func_type_dc_read_24c_hex)(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * receive_buffer);
typedef __int16(__stdcall *func_type_dc_read_24c64)(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * receive_buffer);
typedef __int16(__stdcall *func_type_dc_read_24c64_hex)(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * receive_buffer);
typedef __int16(__stdcall *func_type_dc_read_4428)(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * buffer);
typedef __int16(__stdcall *func_type_dc_read_4428_hex)(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char* buffer);
typedef __int16(__stdcall *func_type_dc_write_4428)(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * buffer);
typedef __int16(__stdcall *func_type_dc_write_4428_hex)(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char* buffer);
typedef __int16(__stdcall *func_type_dc_verifypin_4428)(HANDLE icdev,unsigned char *passwd);
typedef __int16(__stdcall *func_type_dc_verifypin_4428_hex)(HANDLE icdev,unsigned char *passwd);
typedef __int16(__stdcall *func_type_dc_readpin_4428)(HANDLE icdev,unsigned char *passwd);
typedef __int16(__stdcall *func_type_dc_readpin_4428_hex)(HANDLE icdev,unsigned char *passwd);
typedef __int16(__stdcall *func_type_dc_readpincount_4428)(HANDLE icdev);
typedef __int16(__stdcall *func_type_dc_changepin_4428)(HANDLE icdev,unsigned char *passwd);
typedef __int16(__stdcall *func_type_dc_changepin_4428_hex)(HANDLE icdev,unsigned char *passwd);
typedef __int16(__stdcall *func_type_dc_Check_4442)(HANDLE icdev);
typedef __int16(__stdcall *func_type_dc_Check_4428)(HANDLE icdev);
typedef __int16(__stdcall *func_type_dc_Check_24C01)(HANDLE icdev);
typedef __int16(__stdcall *func_type_dc_Check_24C02)(HANDLE icdev);
typedef __int16(__stdcall *func_type_dc_Check_24C04)(HANDLE icdev);
typedef __int16(__stdcall *func_type_dc_Check_24C08)(HANDLE icdev);
typedef __int16(__stdcall *func_type_dc_Check_24C16)(HANDLE icdev);
typedef __int16(__stdcall *func_type_dc_Check_24C64)(HANDLE icdev);
typedef __int16(__stdcall *func_type_dc_Check_CPU)(HANDLE icdev);
typedef __int16(__stdcall *func_type_dc_CheckCard)(HANDLE icdev);
typedef __int16(__stdcall *func_type_dc_getrcinfo)(HANDLE icdev,unsigned char *info);
typedef __int16(__stdcall *func_type_dc_getrcinfo_hex)(HANDLE icdev,unsigned char *info);
typedef __int16(__stdcall *func_type_dc_getlongver)(HANDLE icdev,unsigned char *sver);
typedef __int16(__stdcall *func_type_dc_cardstr)(HANDLE icdev,unsigned char _Mode,char * Strsnr);
typedef __int16(__stdcall *func_type_dc_card_b)(HANDLE icdev,unsigned char *rbuf);
typedef __int16(__stdcall *func_type_dc_card_b_hex)(HANDLE icdev,char *rbuf);
typedef __int16(__stdcall *func_type_dc_dispinfo_T8)(HANDLE idComDev,unsigned char line,unsigned char offset,char *data);
typedef __int16(__stdcall *func_type_dc_dispinfo_pro_T8)(HANDLE idComDev,unsigned char offset,char *data);
typedef __int16(__stdcall *func_type_dc_clearlcd_T8)(HANDLE icdev,unsigned char line);
typedef __int16(__stdcall *func_type_dc_led_T8)(HANDLE icdev,unsigned char cled,unsigned char cflag);
typedef __int16(__stdcall *func_type_dc_MFPL0_writeperso)(HANDLE icdev,unsigned int BNr,unsigned char * dataperso);
typedef __int16(__stdcall *func_type_dc_MFPL0_writeperso_hex)(HANDLE icdev,unsigned int BNr,unsigned char * dataperso);
typedef __int16(__stdcall *func_type_dc_MFPL0_commitperso)(HANDLE icdev);
typedef __int16(__stdcall *func_type_dc_MFPL1_authl1key)(HANDLE icdev,unsigned char *authkey);
typedef __int16(__stdcall *func_type_dc_MFPL1_authl1key_hex)(HANDLE icdev,unsigned char *authkey);
typedef __int16(__stdcall *func_type_dc_MFPL1_switchtol2)(HANDLE icdev,unsigned char *authkey);
typedef __int16(__stdcall *func_type_dc_MFPL1_switchtol3)(HANDLE icdev,unsigned char *authkey);
typedef __int16(__stdcall *func_type_dc_MFPL2_switchtol3)(HANDLE icdev,unsigned char *authkey);
typedef __int16(__stdcall *func_type_dc_MFPL3_authl3key)(HANDLE icdev,unsigned int keyBNr,unsigned char *authkey);
typedef __int16(__stdcall *func_type_dc_MFPL3_authl3key_hex)(HANDLE icdev,unsigned int keyBNr,unsigned char *authkey);
typedef __int16(__stdcall *func_type_dc_MFPL3_authl3sectorkey)(HANDLE icdev,unsigned char mode,unsigned int sectorBNr,unsigned char *authkey);
typedef __int16(__stdcall *func_type_dc_MFPL3_authl3sectorkey_hex)(HANDLE icdev,unsigned char mode,unsigned int sectorBNr,unsigned char *authkey);
typedef __int16(__stdcall *func_type_dc_MFPL3_readinplain)(HANDLE icdev,unsigned int BNr,unsigned char Numblock, unsigned char *readdata);
typedef __int16(__stdcall *func_type_dc_MFPL3_readinplain_hex)(HANDLE icdev,unsigned int BNr,unsigned char Numblock, unsigned char *readdata);
typedef __int16(__stdcall *func_type_dc_MFPL3_readencrypted)(HANDLE icdev,unsigned int BNr,unsigned char Numblock, unsigned char *readdata, unsigned char flag);
typedef __int16(__stdcall *func_type_dc_MFPL3_readencrypted_hex)(HANDLE icdev,unsigned int BNr,unsigned char Numblock, unsigned char *readdata, unsigned char flag);
typedef __int16(__stdcall *func_type_dc_MFPL3_writeinplain)(HANDLE icdev,unsigned int BNr,unsigned char Numblock,unsigned char *writedata);
typedef __int16(__stdcall *func_type_dc_MFPL3_writeinplain_hex)(HANDLE icdev,unsigned int BNr,unsigned char Numblock,unsigned char *writedata);
typedef __int16(__stdcall *func_type_dc_MFPL3_writeencrypted)(HANDLE icdev,unsigned int BNr,unsigned char Numblock,unsigned char *writedata, unsigned char flag);
typedef __int16(__stdcall *func_type_dc_MFPL3_writeencrypted_hex)(HANDLE icdev,unsigned int BNr,unsigned char Numblock,unsigned char *writedata, unsigned char flag);
typedef __int16(__stdcall *func_type_dc_auth_ulc)(HANDLE icdev, unsigned char * key);
typedef __int16(__stdcall *func_type_dc_auth_ulc_hex)(HANDLE icdev, unsigned char * key);
typedef __int16(__stdcall *func_type_dc_changekey_ulc)(HANDLE icdev,unsigned char *newkey);
typedef __int16(__stdcall *func_type_dc_changekey_ulc_hex)(HANDLE icdev,unsigned char *newkey);
typedef __int16(__stdcall *func_type_dc_pro_commandlinkEXT_hex)(HANDLE idComDev,unsigned int slen,unsigned char * sendbuffer,unsigned int *rlen,unsigned char * databuffer,unsigned char timeout,unsigned char FG);
/***********************************自动生成代码***added by chch 20110703****************************/
/***********************************自动生成代码***added by chch 20110703****************************/


class D8Cap{
public:
	HINSTANCE hinstLib;
	//基本函数
	myDcInit my_dc_init;
	myDcCard my_dc_card;
	myDcLoadKey my_dc_load_key;
	myDcAuth my_dc_authentication;
	myDcAuth2 my_dc_authentication2;
	myDcRead my_dc_read;
	myDcWrite my_dc_write;
	myDcBeep my_dc_beep;
	myDcExit my_dc_exit;
	myDcRequest my_dc_request;
	myDcSelect my_dc_select;
	myDcAnticoll my_dc_anticoll;
	myDcAuthPass my_dc_authentication_pass;
	myDcHalt my_dc_halt;
	myDcChangeb3 my_dc_changeb3;
	myDcHLAuthentication my_dc_HL_authentication;
	myDcCheckWrite my_dc_check_write;
	myDcHLRead my_dc_HL_read;
	myDcHLWrite my_dc_HL_write;
	myDcDesHex my_dc_des_hex;

	//带Hex函数
	myDcCardHex my_dc_card_hex;
	myDcLoadKeyHex my_dc_load_key_hex;
	myDcAuthenticationPathHex my_dc_authentication_path_hex;
	myDcReadHex my_dc_read_hex;
	myDcWriteHex my_dc_write_hex;
	myDcSrdEepromHex my_dc_srd_eepromhex;
	myDcSwrEepromHex my_dc_swr_eepromhex;
	myDcCpuapduHex my_dc_cpuapdu_hex;
	myDcCpuresetHex my_dc_cpureset_hex;

	//值操作
	myDcInitval my_dc_initval;
	myDcReadVal my_dc_readval;
	myDcIncrement my_dc_increment;
	myDcDecrement my_dc_decrement;
	myDcRestore my_dc_restore;

	myDcSwrEeprom  my_dc_swreeprom;
	myA_hex my_a_hex;
	myHex_a my_hex_a;
	myDc_Reset my_dc_reset;
	myDc_Cpuapdu my_dc__cpuapdu;
	myDc_Cpuapdusource my_dc_cpuapdusource;
	myDc_Cpureset my_dc_cpureset;
	myDc_Setcpu my_dc_Setcpu;
	myDc_Setcpupara my_dc_Setcpupara;


	myDc_Transfer my_dc_transfer;
	//myDc_Beep my_dc_beep;
	myDc_Srd_eeprom my_dc_srd_eeprom;
	myDc_Getver my_dc_getver;


	//RFMA专用
	myDcGettime my_dc_gettime;
	myDcDispMode my_dc_disp_mode;
	myDcHighDisp my_dc_high_disp;
	myDcSetBright my_dc_setbright;
	myDcDispStr my_dc_disp_str;
	myDcSettime my_dc_settime;

	//NEW ADD BY ZXB 091116
	myDcGetcpupara my_dc_getcpupara;
	myDcCpuApduSourceExt my_dc_cpuapdusourceEXT;
	myDcCpuApduSourceExtHex	my_dc_cpuapdusourceEXT_hex;
	myDcCpuApduExt	my_dc_cpuapduEXT;
	myDcCpuApduExtHex my_dc_cpuapduEXT_hex;

	myDcProCommandLinkExt my_dc_pro_commandlinkEXT;
	myDCProReset my_dc_pro_reset;
	myDCProCommand my_dc_pro_command;
    
	myDCConfig   my_dc_config;
	myDCProHalt  my_dc_pro_halt;

	myDCCardDouble my_dc_card_double;
	myDCCardDoubleHex my_dc_card_double_hex;

	myDCGettimehex my_dc_gettimehex;
	myDCSettimehex my_dc_settimehex;

	//added on 20110627
	myDcReadblock my_dc_readblock;
	myDcReadblockHex my_dc_readblock_hex;
	myDcWriteblock my_dc_writeblock;
	myDcWriteblockHex my_dc_writeblock_hex;

	myDcCardAB my_dc_cardAB;
	//added on 20110627



	myDCProCommandsource my_dc_pro_commandsource;
    myDCProCommandsourceHex my_dc_pro_commandsourcehex;
	myDCCpudown my_dc_cpudown;
	/***********************************自动生成代码***added by chch 20110703****************************/
/***********************************自动生成代码***added by chch 20110703****************************/
func_type_dc_write_TS my_dc_write_TS;
func_type_dc_initval_ml my_dc_initval_ml;
func_type_dc_readval_ml my_dc_readval_ml;
func_type_dc_authentication_2 my_dc_authentication_2;
func_type_dc_anticoll2 my_dc_anticoll2;
func_type_dc_select2 my_dc_select2;
func_type_dc_HL_writehex my_dc_HL_writehex;
func_type_dc_HL_readhex my_dc_HL_readhex;
func_type_dc_check_writehex my_dc_check_writehex;
func_type_dc_clr_control_bit my_dc_clr_control_bit;
func_type_dc_set_control_bit my_dc_set_control_bit;
func_type_dc_swr_eeprom my_dc_swr_eeprom;
func_type_swr_alleeprom my_swr_alleeprom;
func_type_srd_alleeprom my_srd_alleeprom;
func_type_dc_ctl_mode my_dc_ctl_mode;
func_type_dcdeshex my_dcdeshex;
func_type_dcdes my_dcdes;
func_type_dc_light my_dc_light;
func_type_dc_setcpu my_dc_setcpu;
func_type_dc_cpuapdu my_dc_cpuapdu;
func_type_dc_cpuapdusource_hex my_dc_cpuapdusource_hex;
func_type_dc_cpuapdurespon my_dc_cpuapdurespon;
func_type_dc_cpuapdurespon_hex my_dc_cpuapdurespon_hex;
func_type_dc_set_addr my_dc_set_addr;
func_type_dc_init_485 my_dc_init_485;
func_type_dc_changebaud_485 my_dc_changebaud_485;
func_type_dc_change_addr my_dc_change_addr;
func_type_dc_pro_resethex my_dc_pro_resethex;
func_type_dc_pro_commandhex my_dc_pro_commandhex;
func_type_dc_request_shc1102 my_dc_request_shc1102;
func_type_dc_auth_shc1102 my_dc_auth_shc1102;
func_type_dc_read_shc1102 my_dc_read_shc1102;
func_type_dc_write_shc1102 my_dc_write_shc1102;
func_type_dc_halt_shc1102 my_dc_halt_shc1102;
func_type_dc_config_card my_dc_config_card;
func_type_dc_request_b my_dc_request_b;
func_type_dc_slotmarker my_dc_slotmarker;
func_type_dc_attrib my_dc_attrib;
func_type_dc_open_door my_dc_open_door;
func_type_dc_open_timedoor my_dc_open_timedoor;
func_type_dc_read_random my_dc_read_random;
func_type_dc_write_random my_dc_write_random;
func_type_dc_read_random_hex my_dc_read_random_hex;
func_type_dc_write_random_hex my_dc_write_random_hex;
func_type_dc_erase_random my_dc_erase_random;
func_type_dc_mfdes_auth my_dc_mfdes_auth;
func_type_dc_disp_neg my_dc_disp_neg;
func_type_dc_pro_commandlink my_dc_pro_commandlink;
func_type_dc_pro_commandlink_hex my_dc_pro_commandlink_hex;
func_type_dc_read_idcard my_dc_read_idcard;
func_type_dc_read_idcard_hex my_dc_read_idcard_hex;
func_type_dc_authentication_pass_hex my_dc_authentication_pass_hex;
func_type_dc_setcpupara my_dc_setcpupara;
func_type_dc_command my_dc_command;
func_type_dc_command_hex my_dc_command_hex;
func_type_dc_creat_mac my_dc_creat_mac;
func_type_dc_creat_mac_hex my_dc_creat_mac_hex;
func_type_dc_HL_write_hex my_dc_HL_write_hex;
func_type_dc_HL_read_hex my_dc_HL_read_hex;
func_type_dc_check_write_hex my_dc_check_write_hex;
func_type_dc_srd_eeprom_hex my_dc_srd_eeprom_hex;
func_type_dc_swr_eeprom_hex my_dc_swr_eeprom_hex;
func_type_dc_gettime_hex my_dc_gettime_hex;
func_type_dc_settime_hex my_dc_settime_hex;
func_type_dc_des my_dc_des;
func_type_dc_pro_reset_hex my_dc_pro_reset_hex;
func_type_dc_pro_command_hex my_dc_pro_command_hex;
func_type_dc_pro_commandsource_hex my_dc_pro_commandsource_hex;
func_type_dc_switch_unix my_dc_switch_unix;
func_type_dc_authentication_passaddr my_dc_authentication_passaddr;
func_type_dc_authentication_passaddr_hex my_dc_authentication_passaddr_hex;
func_type_dc_card_fm11rf005 my_dc_card_fm11rf005;
func_type_dc_setusbtimeout my_dc_setusbtimeout;
func_type_dc_mfdes_baud my_dc_mfdes_baud;
func_type_dc_tripledes my_dc_tripledes;
func_type_dc_tripledes_hex my_dc_tripledes_hex;
func_type_dc_mfdes_auth_hex my_dc_mfdes_auth_hex;
func_type_dc_pro_sendcommandsource my_dc_pro_sendcommandsource;
func_type_dc_pro_receivecommandsource my_dc_pro_receivecommandsource;
func_type_dc_inventory my_dc_inventory;
func_type_dc_inventory_hex my_dc_inventory_hex;
func_type_dc_stay_quiet my_dc_stay_quiet;
func_type_dc_stay_quiet_hex my_dc_stay_quiet_hex;
func_type_dc_select_uid my_dc_select_uid;
func_type_dc_select_uid_hex my_dc_select_uid_hex;
func_type_dc_reset_to_ready my_dc_reset_to_ready;
func_type_dc_reset_to_ready_hex my_dc_reset_to_ready_hex;
func_type_dc_lock_block my_dc_lock_block;
func_type_dc_lock_block_hex my_dc_lock_block_hex;
func_type_dc_write_afi my_dc_write_afi;
func_type_dc_write_afi_hex my_dc_write_afi_hex;
func_type_dc_lock_afi my_dc_lock_afi;
func_type_dc_lock_afi_hex my_dc_lock_afi_hex;
func_type_dc_write_dsfid my_dc_write_dsfid;
func_type_dc_write_dsfid_hex my_dc_write_dsfid_hex;
func_type_dc_lock_dsfid my_dc_lock_dsfid;
func_type_dc_lock_dsfid_hex my_dc_lock_dsfid_hex;
func_type_dc_get_systeminfo my_dc_get_systeminfo;
func_type_dc_get_systeminfo_hex my_dc_get_systeminfo_hex;
func_type_dc_get_securityinfo my_dc_get_securityinfo;
func_type_dc_get_securityinfo_hex my_dc_get_securityinfo_hex;
func_type_dc_getsnr_fm11rf005 my_dc_getsnr_fm11rf005;
func_type_dc_getsnr_fm11rf005_hex my_dc_getsnr_fm11rf005_hex;
func_type_dc_write_fm11rf005 my_dc_write_fm11rf005;
func_type_dc_read_fm11rf005 my_dc_read_fm11rf005;
func_type_dc_read_fm11rf005_hex my_dc_read_fm11rf005_hex;
func_type_dc_write_fm11rf005_hex my_dc_write_fm11rf005_hex;
func_type_DCDEV_CommandMcu my_DCDEV_CommandMcu;
func_type_DCDEV_CommandMcu_Hex my_DCDEV_CommandMcu_Hex;
func_type_dc_displcd my_dc_displcd;
func_type_dc_getinputpass my_dc_getinputpass;
func_type_dc_readmagcard my_dc_readmagcard;
func_type_dc_testdevicecomm my_dc_testdevicecomm;
func_type_dc_dispmainmenu my_dc_dispmainmenu;
func_type_dc_setdevicetime my_dc_setdevicetime;
func_type_dc_getdevicetime my_dc_getdevicetime;
func_type_dc_dispinfo my_dc_dispinfo;
func_type_dc_dispmaininfo my_dc_dispmaininfo;
func_type_dc_posbeep my_dc_posbeep;
func_type_dc_ctlbacklight my_dc_ctlbacklight;
func_type_dc_ctlled my_dc_ctlled;
func_type_dc_lcdclrscrn my_dc_lcdclrscrn;
func_type_dc_passin my_dc_passin;
func_type_dc_passget my_dc_passget;
func_type_dc_passcancel my_dc_passcancel;
func_type_dc_getinputkey my_dc_getinputkey;
func_type_dc_displcd_ext my_dc_displcd_ext;
func_type_dc_readmagcardall my_dc_readmagcardall;
func_type_dc_readdevsnr my_dc_readdevsnr;
func_type_dc_readreadersnr my_dc_readreadersnr;
func_type_dc_resetdevice my_dc_resetdevice;
func_type_dc_read_4442 my_dc_read_4442;
func_type_dc_read_4442_hex my_dc_read_4442_hex;
func_type_dc_write_4442 my_dc_write_4442;
func_type_dc_write_4442_hex my_dc_write_4442_hex;
func_type_dc_verifypin_4442 my_dc_verifypin_4442;
func_type_dc_verifypin_4442_hex my_dc_verifypin_4442_hex;
func_type_dc_readpin_4442 my_dc_readpin_4442;
func_type_dc_readpin_4442_hex my_dc_readpin_4442_hex;
func_type_dc_readpincount_4442 my_dc_readpincount_4442;
func_type_dc_changepin_4442 my_dc_changepin_4442;
func_type_dc_changepin_4442_hex my_dc_changepin_4442_hex;
func_type_dc_readwrotect_4442 my_dc_readwrotect_4442;
func_type_dc_readwrotect_4442_hex my_dc_readwrotect_4442_hex;
func_type_dc_writeprotect_4442 my_dc_writeprotect_4442;
func_type_dc_writeprotect_4442_hex my_dc_writeprotect_4442_hex;
func_type_dc_write_24c my_dc_write_24c;
func_type_dc_write_24c_hex my_dc_write_24c_hex;
func_type_dc_write_24c64 my_dc_write_24c64;
func_type_dc_write_24c64_hex my_dc_write_24c64_hex;
func_type_dc_read_24c my_dc_read_24c;
func_type_dc_read_24c_hex my_dc_read_24c_hex;
func_type_dc_read_24c64 my_dc_read_24c64;
func_type_dc_read_24c64_hex my_dc_read_24c64_hex;
func_type_dc_read_4428 my_dc_read_4428;
func_type_dc_read_4428_hex my_dc_read_4428_hex;
func_type_dc_write_4428 my_dc_write_4428;
func_type_dc_write_4428_hex my_dc_write_4428_hex;
func_type_dc_verifypin_4428 my_dc_verifypin_4428;
func_type_dc_verifypin_4428_hex my_dc_verifypin_4428_hex;
func_type_dc_readpin_4428 my_dc_readpin_4428;
func_type_dc_readpin_4428_hex my_dc_readpin_4428_hex;
func_type_dc_readpincount_4428 my_dc_readpincount_4428;
func_type_dc_changepin_4428 my_dc_changepin_4428;
func_type_dc_changepin_4428_hex my_dc_changepin_4428_hex;
func_type_dc_Check_4442 my_dc_Check_4442;
func_type_dc_Check_4428 my_dc_Check_4428;
func_type_dc_Check_24C01 my_dc_Check_24C01;
func_type_dc_Check_24C02 my_dc_Check_24C02;
func_type_dc_Check_24C04 my_dc_Check_24C04;
func_type_dc_Check_24C08 my_dc_Check_24C08;
func_type_dc_Check_24C16 my_dc_Check_24C16;
func_type_dc_Check_24C64 my_dc_Check_24C64;
func_type_dc_Check_CPU my_dc_Check_CPU;
func_type_dc_CheckCard my_dc_CheckCard;
func_type_dc_getrcinfo my_dc_getrcinfo;
func_type_dc_getrcinfo_hex my_dc_getrcinfo_hex;
func_type_dc_getlongver my_dc_getlongver;
func_type_dc_cardstr my_dc_cardstr;
func_type_dc_card_b my_dc_card_b;
func_type_dc_card_b_hex my_dc_card_b_hex;
func_type_dc_dispinfo_T8 my_dc_dispinfo_T8;
func_type_dc_dispinfo_pro_T8 my_dc_dispinfo_pro_T8;
func_type_dc_clearlcd_T8 my_dc_clearlcd_T8;
func_type_dc_led_T8 my_dc_led_T8;
func_type_dc_MFPL0_writeperso my_dc_MFPL0_writeperso;
func_type_dc_MFPL0_writeperso_hex my_dc_MFPL0_writeperso_hex;
func_type_dc_MFPL0_commitperso my_dc_MFPL0_commitperso;
func_type_dc_MFPL1_authl1key my_dc_MFPL1_authl1key;
func_type_dc_MFPL1_authl1key_hex my_dc_MFPL1_authl1key_hex;
func_type_dc_MFPL1_switchtol2 my_dc_MFPL1_switchtol2;
func_type_dc_MFPL1_switchtol3 my_dc_MFPL1_switchtol3;
func_type_dc_MFPL2_switchtol3 my_dc_MFPL2_switchtol3;
func_type_dc_MFPL3_authl3key my_dc_MFPL3_authl3key;
func_type_dc_MFPL3_authl3key_hex my_dc_MFPL3_authl3key_hex;
func_type_dc_MFPL3_authl3sectorkey my_dc_MFPL3_authl3sectorkey;
func_type_dc_MFPL3_authl3sectorkey_hex my_dc_MFPL3_authl3sectorkey_hex;
func_type_dc_MFPL3_readinplain my_dc_MFPL3_readinplain;
func_type_dc_MFPL3_readinplain_hex my_dc_MFPL3_readinplain_hex;
func_type_dc_MFPL3_readencrypted my_dc_MFPL3_readencrypted;
func_type_dc_MFPL3_readencrypted_hex my_dc_MFPL3_readencrypted_hex;
func_type_dc_MFPL3_writeinplain my_dc_MFPL3_writeinplain;
func_type_dc_MFPL3_writeinplain_hex my_dc_MFPL3_writeinplain_hex;
func_type_dc_MFPL3_writeencrypted my_dc_MFPL3_writeencrypted;
func_type_dc_MFPL3_writeencrypted_hex my_dc_MFPL3_writeencrypted_hex;
func_type_dc_auth_ulc my_dc_auth_ulc;
func_type_dc_auth_ulc_hex my_dc_auth_ulc_hex;
func_type_dc_changekey_ulc my_dc_changekey_ulc;
func_type_dc_changekey_ulc_hex my_dc_changekey_ulc_hex;
func_type_dc_pro_commandlinkEXT_hex my_dc_pro_commandlinkEXT_hex;
/***********************************自动生成代码***added by chch 20110703****************************/
/***********************************自动生成代码***added by chch 20110703****************************/



public:
	D8Cap();
	void Initial(int port);
	~D8Cap();
private:
	bool initDll(int port);
	bool freeDll();
public:
	//基本函数
	HANDLE  __stdcall  dc_init8(__int16 port,long baud);	//初始化端口
	__int16  __stdcall dc_load_key8(HANDLE icdev,unsigned char _Mode,unsigned char _SecNr, unsigned char *_NKey);
	__int16  __stdcall dc_card8(HANDLE icdev,unsigned char _Mode,unsigned long *_Snr);
	__int16  __stdcall dc_authentication8(HANDLE icdev,unsigned char _Mode,unsigned char _SecNr);
	__int16  __stdcall dc_authentication_28(HANDLE icdev,unsigned char _Mode,unsigned char KeyNr,unsigned char Adr);
	__int16  __stdcall dc_read8(HANDLE icdev,unsigned char _Adr,unsigned char *_Data);
	__int16  __stdcall dc_write8(HANDLE icdev,unsigned char _Adr,unsigned char *_Data);
	__int16  __stdcall dc_beep8(HANDLE icdev,unsigned short _Msec);
	__int16  __stdcall dc_exit8(HANDLE icdev);
	__int16  __stdcall dc_request8(HANDLE icdev,unsigned char _Mode,unsigned __int16  *TagType);
	__int16  __stdcall dc_select8(HANDLE icdev,unsigned long _Snr,unsigned char *_Size);
	__int16  __stdcall  dc_anticoll8(HANDLE icdev,unsigned char _Bcnt,unsigned long *_Snr);
	__int16 __stdcall dc_authentication_pass8(HANDLE icdev,unsigned char _Mode, unsigned char _Addr,unsigned char *passbuff);
	__int16  __stdcall dc_halt8(HANDLE icdev);
	__int16  __stdcall dc_changeb38(HANDLE icdev,unsigned char _SecNr,unsigned char *_KeyA,
		unsigned char _B0,unsigned char _B1,unsigned char _B2,
		unsigned char _B3,unsigned char _Bk,unsigned char *_KeyB);
	__int16  __stdcall dc_HL_authentication8(HANDLE icdev,unsigned char reqmode,unsigned long snr,
		unsigned char authmode,unsigned char secnr);
	__int16  __stdcall dc_check_write8(HANDLE icdev,unsigned long Snr,unsigned char authmode,
		unsigned char Adr,unsigned char * _data);
	__int16  __stdcall dc_HL_read8(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,
		unsigned long _Snr,unsigned char *_Data,unsigned long *_NSnr);
	__int16  __stdcall dc_HL_write8(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,
		unsigned long *_Snr,unsigned char *_Data);
	__int16  __stdcall dc_des_hex8(unsigned char *key,unsigned char *sour,unsigned char *dest,
		__int16 m);

	//带Hex函数
	__int16 __stdcall dc_card_hex8(HANDLE icdev,unsigned char _Mode,unsigned char *snrstr);
	__int16  __stdcall dc_load_key_hex8(HANDLE icdev,unsigned char _Mode,unsigned char _SecNr,char *_NKey);
	__int16 __stdcall dc_authentication_pass_hex8(HANDLE icdev,unsigned char _Mode,unsigned char _Addr,unsigned char *passbuff);
	__int16  __stdcall dc_read_hex8(HANDLE icdev,unsigned char _Adr,char *_Data);
	__int16  __stdcall dc_write_hex8(HANDLE icdev,unsigned char _Adr,char *_Data);
	__int16  __stdcall dc_srd_eepromhex8(HANDLE icdev,__int16   offset,__int16   lenth,unsigned char *rec_buffer);
	__int16  __stdcall dc_swr_eepromhex8(HANDLE icdev,__int16   offset,__int16   lenth, unsigned char* send_buffer);
	__int16 __stdcall dc_cpuapdu_hex8(HANDLE icdev,unsigned char slen, char * sendbuffer,unsigned char *rlen, char * databuffer);
	__int16 __stdcall dc_cpureset_hex8(HANDLE icdev,unsigned char *rlen, char *databuffer);
	
	//值操作
	__int16  __stdcall dc_initval8(HANDLE icdev,unsigned char _Adr,unsigned long _Value);
	__int16  __stdcall dc_readval8(HANDLE icdev,unsigned char _Adr,unsigned long *_Value);
	__int16  __stdcall dc_increment8(HANDLE icdev,unsigned char _Adr,unsigned long _Value);
	__int16  __stdcall dc_decrement8(HANDLE icdev,unsigned char _Adr,unsigned long _Value);
	__int16  __stdcall dc_restore8(HANDLE icdev,unsigned char _Adr);

	__int16  __stdcall dc_swreeprom8(HANDLE icdev,__int16   offset,__int16 lenth,
		unsigned char* send_buffer);
	__int16 __stdcall a_hex8(unsigned char *a,unsigned char *hex,__int16 len);
	__int16 __stdcall hex_a8(unsigned char *hex,unsigned char *a,__int16 length);
	__int16 __stdcall dc_reset8(HANDLE icdev,unsigned __int16   _Msec);
	__int16 __stdcall dc_cpuapdu8(HANDLE icdev,unsigned char slen,unsigned char * sendbuffer,
		unsigned char *rlen,unsigned char * databuffer);
	__int16 __stdcall dc_cpuapdusource8(HANDLE icdev,unsigned char slen,unsigned char * sendbuffer,
		unsigned char *rlen,unsigned char * databuffer);

	__int16 __stdcall dc_cpureset8(HANDLE icdev,unsigned char *rlen,unsigned char *databuffer);

	__int16 __stdcall dc_setcpu8(HANDLE icdev,unsigned char _Byte);
	__int16 __stdcall  dc_setcpupara8(HANDLE icdev,unsigned char cputype,
		unsigned char cpupro,unsigned char cpuetu);

	__int16  __stdcall dc_srd_eeprom8(HANDLE icdev,__int16   offset,__int16 lenth,
		unsigned char *rec_buffer);

	__int16 __stdcall dc_getver8(HANDLE icdev,unsigned char *sver);
	//__int16  __stdcall dc_beep8(HANDLE icdev,unsigned short _Msec);
	__int16  __stdcall dc_transfer8(HANDLE icdev,unsigned char _Adr);
	//__int16  __stdcall dc_restore8(HANDLE icdev,unsigned char _Adr);


	//RFMA专用
	__int16  __stdcall dc_gettime8(HANDLE icdev,unsigned char *time);
	__int16 __stdcall dc_high_disp8(HANDLE icdev,unsigned char offset,unsigned char displen,	unsigned char *dispstr);
	__int16  __stdcall dc_disp_mode8(HANDLE icdev,unsigned char mode);
	__int16  __stdcall dc_setbright8(HANDLE icdev,unsigned char bright);
	__int16  __stdcall dc_disp_str8(HANDLE icdev,char *dispstr);
	__int16  __stdcall dc_settime8(HANDLE icdev,unsigned char *time);

	//NEW ADD BY ZXB 091116
	__int16 __stdcall  dc_getcpupara8(HANDLE icdev,unsigned char cputype,unsigned char *cpupro,unsigned char *cpuetu);
	__int16 __stdcall  dc_cpuapdusourceEXT8(HANDLE icdev,__int16 slen,unsigned char * sendbuffer,__int16 *rlen,unsigned char * databuffer);
	__int16 __stdcall  dc_cpuapdusourceEXT_hex8(HANDLE icdev,__int16 slen, char * sendbuffer,__int16 *rlen, char * databuffer);
	__int16 __stdcall  dc_cpuapduEXT8(HANDLE icdev,__int16 slen,unsigned char * sendbuffer,__int16 *rlen,unsigned char * databuffer);
	__int16 __stdcall  dc_cpuapduEXT_hex8(HANDLE icdev,__int16 slen,char * sendbuffer,__int16 *rlen,char * databuffer);

	__int16 __stdcall  dc_pro_commandlinkEXT8(HANDLE idComDev,unsigned int slen,
		unsigned char * sendbuffer,unsigned int *rlen,
		unsigned char * databuffer,unsigned char timeout,
		unsigned char FG);
	__int16 __stdcall dc_pro_reset8(HANDLE icdev,unsigned char *rlen,unsigned char *receive_data);
	__int16 __stdcall dc_pro_command8(HANDLE idComDev,unsigned char slen,
		unsigned char * sendbuffer,unsigned char *rlen,
								 unsigned char * databuffer,unsigned char timeout);


   __int16  __stdcall dc_config8(HANDLE icdev,unsigned char _Mode,unsigned char _Baud);
   __int16  __stdcall dc_pro_halt8(HANDLE icdev);


   __int16 __stdcall dc_card_double8(HANDLE icdev,unsigned char _Mode,unsigned char *_Snr);
   __int16 __stdcall dc_card_double_hex8(HANDLE icdev,unsigned char _Mode,unsigned char *_Snr);

   __int16  __stdcall dc_gettimehex8(HANDLE icdev,char *time);
   __int16  __stdcall dc_settimehex8(HANDLE icdev,char *time);

   //added on 20110627
   __int16 __stdcall dc_readblock8(HANDLE icdev,unsigned char flags,
	   unsigned char startblock,unsigned char blocknum, 
	   unsigned char *UID, 
	   unsigned char *rlen,unsigned char *rbuffer);
   __int16 __stdcall dc_readblock_hex8(HANDLE icdev,unsigned char flags,
	   unsigned char startblock,unsigned char blocknum, 
	   unsigned char *UID, 
	   unsigned char *rlen,unsigned char *rbuffer);
   __int16 __stdcall dc_writeblock8(HANDLE icdev,unsigned char flags,
	   unsigned char startblock,unsigned char blocknum, 
	   unsigned char *UID, 
	   unsigned char wlen,unsigned char *rbuffer);
   __int16 __stdcall dc_writeblock_hex8(HANDLE icdev,unsigned char flags,
	   unsigned char startblock,unsigned char blocknum, 
	   unsigned char *UID, 
	   unsigned char wlen,unsigned char *rbuffer);

  __int16 __stdcall  dc_cardAB8(HANDLE icdev,unsigned char *rlen,unsigned char *rbuf,unsigned char *type);

   //added on 20110627

  __int16 __stdcall dc_pro_commandsource8(HANDLE idComDev,unsigned char slen,
	                                      unsigned char * sendbuffer,unsigned char *rlen,
									       unsigned char * databuffer,unsigned char timeout);

  
  __int16 __stdcall dc_pro_commandsourcehex8(HANDLE idComDev,unsigned char slen, 
	                                         char * sendbuffer,unsigned char *rlen, 
								  	         char * databuffer,unsigned char timeout);

  __int16 __stdcall dc_cpudown8(HANDLE icdev);
  /***********************************自动生成代码***added by chch 20110703****************************/
/***********************************自动生成代码***added by chch 20110703****************************/
__int16 __stdcall dc_write_TS8(HANDLE icdev);
__int16 __stdcall dc_initval_ml8(HANDLE icdev,unsigned __int16   _Value);
__int16 __stdcall dc_readval_ml8(HANDLE icdev,unsigned __int16   *_Value);
__int16 __stdcall dc_anticoll28(HANDLE icdev,unsigned char _Bcnt,unsigned long *_Snr);
__int16 __stdcall dc_select28(HANDLE icdev,unsigned long _Snr,unsigned char *_Size);
__int16 __stdcall dc_HL_writehex8(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,unsigned long *_Snr,unsigned char *_Data);
__int16 __stdcall dc_HL_readhex8(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,unsigned long _Snr,unsigned char *_Data,unsigned long *_NSnr);
__int16 __stdcall dc_check_writehex8(HANDLE icdev,unsigned long Snr,unsigned char authmode,unsigned char Adr,unsigned char * _data);
__int16 __stdcall dc_clr_control_bit8(HANDLE icdev,unsigned char _b);
__int16 __stdcall dc_set_control_bit8(HANDLE icdev,unsigned char _b);
__int16 __stdcall dc_swr_eeprom8(HANDLE icdev,__int16   offset,__int16 lenth,unsigned char* send_buffer);
__int16 __stdcall swr_alleeprom8(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char* snd_buffer);
__int16 __stdcall srd_alleeprom8(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char *receive_buffer);
__int16 __stdcall dc_ctl_mode8(HANDLE icdev,unsigned char mode);
__int16 __stdcall dcdeshex8(unsigned char *key,unsigned char *sour,unsigned char *dest,__int16 m);
__int16 __stdcall dcdes8(unsigned char *key,unsigned char *sour,unsigned char *dest,__int16 m);
__int16 __stdcall dc_light8(HANDLE icdev,unsigned short _OnOff);
__int16 __stdcall dc_cpuapdusource_hex8(HANDLE icdev,unsigned char slen, char * sendbuffer,unsigned char *rlen, char * databuffer);
__int16 __stdcall dc_cpuapdurespon8(HANDLE idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer);
__int16 __stdcall dc_cpuapdurespon_hex8(HANDLE idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer);
__int16 __stdcall dc_set_addr8(unsigned char saddr);
HANDLE __stdcall dc_init_4858(__int16 port,long baud);
__int16 __stdcall dc_changebaud_4858(HANDLE icdev,long baud);
__int16 __stdcall dc_change_addr8(HANDLE icdev,unsigned char saddr);
__int16 __stdcall dc_pro_resethex8(HANDLE icdev,unsigned char *rlen, char *receive_data);
__int16 __stdcall dc_pro_commandhex8(HANDLE idComDev,unsigned char slen,char * sendbuffer,unsigned char *rlen,char * databuffer,unsigned char timeout);
__int16 __stdcall dc_request_shc11028(HANDLE icdev,unsigned char _Mode,unsigned __int16 *TagType);
__int16 __stdcall dc_auth_shc11028(HANDLE icdev,unsigned char *_Data);
__int16 __stdcall dc_read_shc11028(HANDLE icdev,unsigned char _Adr,unsigned char *_Data);
__int16 __stdcall dc_write_shc11028(HANDLE icdev,unsigned char _Adr,unsigned char *_Data);
__int16 __stdcall dc_halt_shc11028(HANDLE icdev);
__int16 __stdcall dc_config_card8(HANDLE icdev,unsigned char cardtype);
__int16 __stdcall dc_request_b8(HANDLE icdev,unsigned char _Mode,unsigned char AFI,unsigned char N,unsigned char *ATQB);
__int16 __stdcall dc_slotmarker8(HANDLE icdev,unsigned char N, unsigned char *ATQB);
__int16 __stdcall dc_attrib8(HANDLE icdev,unsigned char *PUPI, unsigned char CID);
__int16 __stdcall dc_open_door8(HANDLE icdev,unsigned char cflag);
__int16 __stdcall dc_open_timedoor8(HANDLE icdev,unsigned __int16 utime);
__int16 __stdcall dc_read_random8(HANDLE icdev, unsigned char *data);
__int16 __stdcall dc_write_random8(HANDLE icdev,__int16 len, unsigned char *data);
__int16 __stdcall dc_read_random_hex8(HANDLE icdev, unsigned char *data);
__int16 __stdcall dc_write_random_hex8(HANDLE icdev,__int16 len, unsigned char *data);
__int16 __stdcall dc_erase_random8(HANDLE icdev,__int16 len);
__int16 __stdcall dc_mfdes_auth8(HANDLE icdev,unsigned char keyno,unsigned char keylen,unsigned char *authkey,unsigned char *randAdata,unsigned char *randBdata);
__int16 __stdcall dc_disp_neg8(HANDLE icdev,char *dispstr);
__int16 __stdcall dc_pro_commandlink8(HANDLE idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer,unsigned char timeout,unsigned char FG);
__int16 __stdcall dc_pro_commandlink_hex8(HANDLE idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer,unsigned char timeout,unsigned char FG);
__int16 __stdcall dc_read_idcard8(HANDLE icdev,unsigned char times,unsigned char *_Data);
__int16 __stdcall dc_read_idcard_hex8(HANDLE icdev,unsigned char times,unsigned char *_Data);
__int16 __stdcall dc_command8(HANDLE idComDev,unsigned char cmd,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer);
__int16 __stdcall dc_command_hex8(HANDLE idComDev,unsigned char cmd,unsigned char slen,char * sendbuffer,unsigned char *rlen,char * databuffer);
__int16 __stdcall dc_creat_mac8(unsigned char KeyLen,unsigned char *Key,unsigned short DataLen,unsigned char *Data,unsigned char *InitData,unsigned char AutoFixFlag,unsigned char FixChar,unsigned char *MacData);
__int16 __stdcall dc_creat_mac_hex8(unsigned char KeyLen,unsigned char *Key,unsigned short DataLen,unsigned char *Data,unsigned char *InitData,unsigned char AutoFixFlag,unsigned char FixChar,unsigned char *MacData);
__int16 __stdcall dc_HL_write_hex8(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,unsigned long *_Snr,unsigned char *_Data);
__int16 __stdcall dc_HL_read_hex8(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,unsigned long _Snr,unsigned char *_Data,unsigned long *_NSnr);
__int16 __stdcall dc_check_write_hex8(HANDLE icdev,unsigned long Snr,unsigned char authmode,unsigned char Adr,unsigned char * _data);
__int16 __stdcall dc_srd_eeprom_hex8(HANDLE icdev,__int16   offset,__int16   lenth,unsigned char *rec_buffer);
__int16 __stdcall dc_swr_eeprom_hex8(HANDLE icdev,__int16   offset,__int16   lenth,unsigned char* send_buffer);
__int16 __stdcall dc_gettime_hex8(HANDLE icdev,char *time);
__int16 __stdcall dc_settime_hex8(HANDLE icdev,char *time);
__int16 __stdcall dc_des8(unsigned char *key,unsigned char *sour,unsigned char *dest,__int16 m);
__int16 __stdcall dc_pro_reset_hex8(HANDLE icdev,unsigned char *rlen, char *receive_data);
__int16 __stdcall dc_pro_command_hex8(HANDLE idComDev,unsigned char slen,char * sendbuffer,unsigned char *rlen,char * databuffer,unsigned char timeout);
__int16 __stdcall dc_pro_commandsource_hex8(HANDLE idComDev,unsigned char slen,char * sendbuffer,unsigned char *rlen,char * databuffer,unsigned char timeout);
__int16 __stdcall dc_switch_unix8(HANDLE icdev,long baud);
__int16 __stdcall dc_authentication_passaddr8(HANDLE icdev,unsigned char _Mode,unsigned char _Addr,unsigned char *passbuff);
__int16 __stdcall dc_authentication_passaddr_hex8(HANDLE icdev,unsigned char _Mode,unsigned char _Addr,unsigned char *passbuff);
__int16 __stdcall dc_card_fm11rf0058(HANDLE icdev,unsigned char _Mode,unsigned long *_Snr);
__int16 __stdcall dc_setusbtimeout8(unsigned char ntimes);
__int16 __stdcall dc_mfdes_baud8(HANDLE icdev,unsigned char _Mode,unsigned char para);
__int16 __stdcall dc_tripledes8(unsigned char *key,unsigned char *src,unsigned char *dest,__int16 m);
__int16 __stdcall dc_tripledes_hex8(unsigned char *key,unsigned char *src,unsigned char *dest,__int16 m);
__int16 __stdcall dc_mfdes_auth_hex8(HANDLE icdev,unsigned char keyno,unsigned char keylen,unsigned char *authkey,unsigned char *randAdata,unsigned char *randBdata);
__int16 __stdcall dc_pro_sendcommandsource8(HANDLE idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char timeout);
__int16 __stdcall dc_pro_receivecommandsource8(HANDLE idComDev,unsigned char *rlen,unsigned char * databuffer);
__int16 __stdcall dc_inventory8(HANDLE icdev,unsigned char flags,unsigned char AFI,unsigned char masklen,unsigned char *rlen,unsigned char *rbuffer);
__int16 __stdcall dc_inventory_hex8(HANDLE icdev,unsigned char flags,unsigned char AFI,unsigned char masklen,unsigned char *rlen,unsigned char *rbuffer);
__int16 __stdcall dc_stay_quiet8(HANDLE icdev,unsigned char flags,unsigned char *UID);
__int16 __stdcall dc_stay_quiet_hex8(HANDLE icdev,unsigned char flags,unsigned char *UID);
__int16 __stdcall dc_select_uid8(HANDLE icdev,unsigned char flags,unsigned char *UID);
__int16 __stdcall dc_select_uid_hex8(HANDLE icdev,unsigned char flags,unsigned char *UID);
__int16 __stdcall dc_reset_to_ready8(HANDLE icdev,unsigned char flags,unsigned char *UID);
__int16 __stdcall dc_reset_to_ready_hex8(HANDLE icdev,unsigned char flags,unsigned char *UID);
__int16 __stdcall dc_lock_block8(HANDLE icdev,unsigned char flags,unsigned char block,unsigned char *UID);
__int16 __stdcall dc_lock_block_hex8(HANDLE icdev,unsigned char flags,unsigned char block,unsigned char *UID);
__int16 __stdcall dc_write_afi8(HANDLE icdev,unsigned char flags,unsigned char AFI,unsigned char *UID);
__int16 __stdcall dc_write_afi_hex8(HANDLE icdev,unsigned char flags,unsigned char AFI,unsigned char *UID);
__int16 __stdcall dc_lock_afi8(HANDLE icdev,unsigned char flags,unsigned char AFI,unsigned char *UID);
__int16 __stdcall dc_lock_afi_hex8(HANDLE icdev,unsigned char flags,unsigned char AFI,unsigned char *UID);
__int16 __stdcall dc_write_dsfid8(HANDLE icdev,unsigned char flags,unsigned char DSFID,unsigned char *UID);
__int16 __stdcall dc_write_dsfid_hex8(HANDLE icdev,unsigned char flags,unsigned char DSFID,unsigned char *UID);
__int16 __stdcall dc_lock_dsfid8(HANDLE icdev,unsigned char flags,unsigned char DSFID,unsigned char *UID);
__int16 __stdcall dc_lock_dsfid_hex8(HANDLE icdev,unsigned char flags,unsigned char DSFID,unsigned char *UID);
__int16 __stdcall dc_get_systeminfo8(HANDLE icdev,unsigned char flags,unsigned char *UID,unsigned char *rlen,unsigned char *rbuffer);
__int16 __stdcall dc_get_systeminfo_hex8(HANDLE icdev,unsigned char flags,unsigned char *UID,unsigned char *rlen,unsigned char *rbuffer);
__int16 __stdcall dc_get_securityinfo8(HANDLE icdev,unsigned char flags,unsigned char startblock,unsigned char blocknum,unsigned char *UID,unsigned char *rlen,unsigned char *rbuffer);
__int16 __stdcall dc_get_securityinfo_hex8(HANDLE icdev,unsigned char flags,unsigned char startblock,unsigned char blocknum,unsigned char *UID,unsigned char *rlen,unsigned char *rbuffer);
__int16 __stdcall dc_getsnr_fm11rf0058(HANDLE icdev,unsigned long *_Snr);
__int16 __stdcall dc_getsnr_fm11rf005_hex8(HANDLE icdev,unsigned char *snrstr);
__int16 __stdcall dc_write_fm11rf0058(HANDLE icdev,unsigned char _Adr,unsigned char *_Data);
__int16 __stdcall dc_read_fm11rf0058(HANDLE icdev,unsigned char _Adr,unsigned char *_Data);
__int16 __stdcall dc_read_fm11rf005_hex8(HANDLE icdev,unsigned char _Adr,char *_Data);
__int16 __stdcall dc_write_fm11rf005_hex8(HANDLE icdev,unsigned char _Adr,char *_Data);
__int16 __stdcall DCDEV_CommandMcu8(HANDLE idComDev,unsigned char ctimeout,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer);
__int16 __stdcall DCDEV_CommandMcu_Hex8(HANDLE idComDev,unsigned char ctimeout,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer);
__int16 __stdcall dc_displcd8(HANDLE idComDev,unsigned char flag);
__int16 __stdcall dc_getinputpass8(HANDLE idComDev,unsigned char ctime,unsigned char *rlen,unsigned char * cpass);
__int16 __stdcall dc_readmagcard8(HANDLE idComDev, unsigned char ctime, unsigned char *pTrack2Data, unsigned long *pTrack2Len, unsigned char *pTrack3Data, unsigned long *pTrack3Len);
__int16 __stdcall dc_testdevicecomm8(HANDLE idComDev);
__int16 __stdcall dc_dispmainmenu8(HANDLE idComDev);
__int16 __stdcall dc_setdevicetime8(HANDLE idComDev,unsigned char year,unsigned char month,unsigned char date,unsigned char hour,unsigned char minute,unsigned char second);
__int16 __stdcall dc_getdevicetime8(HANDLE idComDev,unsigned char *year,unsigned char *month,unsigned char *date,unsigned char *hour,unsigned char *minute,unsigned char *second);
__int16 __stdcall dc_dispinfo8(HANDLE idComDev,unsigned char line,unsigned char offset,char *data);
__int16 __stdcall dc_dispmaininfo8(HANDLE idComDev,unsigned char offset,char *data);
__int16 __stdcall dc_posbeep8(HANDLE idComDev,unsigned char beeptime);
__int16 __stdcall dc_ctlbacklight8(HANDLE idComDev, unsigned char cOpenFlag);
__int16 __stdcall dc_ctlled8(HANDLE idComDev, unsigned char cLed, unsigned char cOpenFlag);
__int16 __stdcall dc_lcdclrscrn8(HANDLE idComDev, unsigned char cLine);
__int16 __stdcall dc_passin8(HANDLE idComDev,unsigned char ctime);
__int16 __stdcall dc_passget8(HANDLE idComDev,unsigned char *rlen,unsigned char * cpass);
__int16 __stdcall dc_passcancel8(HANDLE idComDev);
__int16 __stdcall dc_getinputkey8(HANDLE idComDev,unsigned char disptype,unsigned char line,unsigned char ctime,unsigned char *rlen,unsigned char * ckeydata);
__int16 __stdcall dc_displcd_ext8(HANDLE idComDev,unsigned char flag,unsigned char row,unsigned char offset);
__int16 __stdcall dc_readmagcardall8(HANDLE idComDev, unsigned char ctime, unsigned char *pTrack1Data, unsigned long *pTrack1Len,unsigned char *pTrack2Data, unsigned long *pTrack2Len, unsigned char *pTrack3Data, unsigned long *pTrack3Len);
__int16 __stdcall dc_readdevsnr8(HANDLE idComDev,unsigned char *snr);
__int16 __stdcall dc_readreadersnr8(HANDLE idComDev,unsigned char *snr);
__int16 __stdcall dc_resetdevice8(HANDLE idComDev);
__int16 __stdcall dc_read_44428(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * buffer);
__int16 __stdcall dc_read_4442_hex8(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char* buffer);
__int16 __stdcall dc_write_44428(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * buffer);
__int16 __stdcall dc_write_4442_hex8(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char* buffer);
__int16 __stdcall dc_verifypin_44428(HANDLE icdev,unsigned char *passwd);
__int16 __stdcall dc_verifypin_4442_hex8(HANDLE icdev,unsigned char *passwd);
__int16 __stdcall dc_readpin_44428(HANDLE icdev,unsigned char *passwd);
__int16 __stdcall dc_readpin_4442_hex8(HANDLE icdev,unsigned char *passwd);
__int16 __stdcall dc_readpincount_44428(HANDLE icdev);
__int16 __stdcall dc_changepin_44428(HANDLE icdev,unsigned char *passwd);
__int16 __stdcall dc_changepin_4442_hex8(HANDLE icdev,unsigned char *passwd);
__int16 __stdcall dc_readwrotect_44428(HANDLE icdev,__int16 offset,__int16 leng,unsigned char *buffer);
__int16 __stdcall dc_readwrotect_4442_hex8(HANDLE icdev,__int16 offset,__int16 leng,unsigned char *buffer);
__int16 __stdcall dc_writeprotect_44428(HANDLE icdev,__int16 offset,__int16 leng,unsigned char *buffer);
__int16 __stdcall dc_writeprotect_4442_hex8(HANDLE icdev,__int16 offset,__int16 leng,unsigned char *buffer);
__int16 __stdcall dc_write_24c8(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * snd_buffer);
__int16 __stdcall dc_write_24c_hex8(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * snd_buffer);
__int16 __stdcall dc_write_24c648(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * snd_buffer);
__int16 __stdcall dc_write_24c64_hex8(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * snd_buffer);
__int16 __stdcall dc_read_24c8(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * receive_buffer);
__int16 __stdcall dc_read_24c_hex8(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * receive_buffer);
__int16 __stdcall dc_read_24c648(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * receive_buffer);
__int16 __stdcall dc_read_24c64_hex8(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * receive_buffer);
__int16 __stdcall dc_read_44288(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * buffer);
__int16 __stdcall dc_read_4428_hex8(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char* buffer);
__int16 __stdcall dc_write_44288(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * buffer);
__int16 __stdcall dc_write_4428_hex8(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char* buffer);
__int16 __stdcall dc_verifypin_44288(HANDLE icdev,unsigned char *passwd);
__int16 __stdcall dc_verifypin_4428_hex8(HANDLE icdev,unsigned char *passwd);
__int16 __stdcall dc_readpin_44288(HANDLE icdev,unsigned char *passwd);
__int16 __stdcall dc_readpin_4428_hex8(HANDLE icdev,unsigned char *passwd);
__int16 __stdcall dc_readpincount_44288(HANDLE icdev);
__int16 __stdcall dc_changepin_44288(HANDLE icdev,unsigned char *passwd);
__int16 __stdcall dc_changepin_4428_hex8(HANDLE icdev,unsigned char *passwd);
__int16 __stdcall dc_Check_44428(HANDLE icdev);
__int16 __stdcall dc_Check_44288(HANDLE icdev);
__int16 __stdcall dc_Check_24C018(HANDLE icdev);
__int16 __stdcall dc_Check_24C028(HANDLE icdev);
__int16 __stdcall dc_Check_24C048(HANDLE icdev);
__int16 __stdcall dc_Check_24C088(HANDLE icdev);
__int16 __stdcall dc_Check_24C168(HANDLE icdev);
__int16 __stdcall dc_Check_24C648(HANDLE icdev);
__int16 __stdcall dc_Check_CPU8(HANDLE icdev);
__int16 __stdcall dc_CheckCard8(HANDLE icdev);
__int16 __stdcall dc_getrcinfo8(HANDLE icdev,unsigned char *info);
__int16 __stdcall dc_getrcinfo_hex8(HANDLE icdev,unsigned char *info);
__int16 __stdcall dc_getlongver8(HANDLE icdev,unsigned char *sver);
__int16 __stdcall dc_cardstr8(HANDLE icdev,unsigned char _Mode,char * Strsnr);
__int16 __stdcall dc_card_b8(HANDLE icdev,unsigned char *rbuf);
__int16 __stdcall dc_card_b_hex8(HANDLE icdev,char *rbuf);
__int16 __stdcall dc_dispinfo_T88(HANDLE idComDev,unsigned char line,unsigned char offset,char *data);
__int16 __stdcall dc_dispinfo_pro_T88(HANDLE idComDev,unsigned char offset,char *data);
__int16 __stdcall dc_clearlcd_T88(HANDLE icdev,unsigned char line);
__int16 __stdcall dc_led_T88(HANDLE icdev,unsigned char cled,unsigned char cflag);
__int16 __stdcall dc_MFPL0_writeperso8(HANDLE icdev,unsigned int BNr,unsigned char * dataperso);
__int16 __stdcall dc_MFPL0_writeperso_hex8(HANDLE icdev,unsigned int BNr,unsigned char * dataperso);
__int16 __stdcall dc_MFPL0_commitperso8(HANDLE icdev);
__int16 __stdcall dc_MFPL1_authl1key8(HANDLE icdev,unsigned char *authkey);
__int16 __stdcall dc_MFPL1_authl1key_hex8(HANDLE icdev,unsigned char *authkey);
__int16 __stdcall dc_MFPL1_switchtol28(HANDLE icdev,unsigned char *authkey);
__int16 __stdcall dc_MFPL1_switchtol38(HANDLE icdev,unsigned char *authkey);
__int16 __stdcall dc_MFPL2_switchtol38(HANDLE icdev,unsigned char *authkey);
__int16 __stdcall dc_MFPL3_authl3key8(HANDLE icdev,unsigned int keyBNr,unsigned char *authkey);
__int16 __stdcall dc_MFPL3_authl3key_hex8(HANDLE icdev,unsigned int keyBNr,unsigned char *authkey);
__int16 __stdcall dc_MFPL3_authl3sectorkey8(HANDLE icdev,unsigned char mode,unsigned int sectorBNr,unsigned char *authkey);
__int16 __stdcall dc_MFPL3_authl3sectorkey_hex8(HANDLE icdev,unsigned char mode,unsigned int sectorBNr,unsigned char *authkey);
__int16 __stdcall dc_MFPL3_readinplain8(HANDLE icdev,unsigned int BNr,unsigned char Numblock, unsigned char *readdata);
__int16 __stdcall dc_MFPL3_readinplain_hex8(HANDLE icdev,unsigned int BNr,unsigned char Numblock, unsigned char *readdata);
__int16 __stdcall dc_MFPL3_readencrypted8(HANDLE icdev,unsigned int BNr,unsigned char Numblock, unsigned char *readdata, unsigned char flag);
__int16 __stdcall dc_MFPL3_readencrypted_hex8(HANDLE icdev,unsigned int BNr,unsigned char Numblock, unsigned char *readdata, unsigned char flag);
__int16 __stdcall dc_MFPL3_writeinplain8(HANDLE icdev,unsigned int BNr,unsigned char Numblock,unsigned char *writedata);
__int16 __stdcall dc_MFPL3_writeinplain_hex8(HANDLE icdev,unsigned int BNr,unsigned char Numblock,unsigned char *writedata);
__int16 __stdcall dc_MFPL3_writeencrypted8(HANDLE icdev,unsigned int BNr,unsigned char Numblock,unsigned char *writedata, unsigned char flag);
__int16 __stdcall dc_MFPL3_writeencrypted_hex8(HANDLE icdev,unsigned int BNr,unsigned char Numblock,unsigned char *writedata, unsigned char flag);
__int16 __stdcall dc_auth_ulc8(HANDLE icdev, unsigned char * key);
__int16 __stdcall dc_auth_ulc_hex8(HANDLE icdev, unsigned char * key);
__int16 __stdcall dc_changekey_ulc8(HANDLE icdev,unsigned char *newkey);
__int16 __stdcall dc_changekey_ulc_hex8(HANDLE icdev,unsigned char *newkey);
__int16 __stdcall dc_pro_commandlinkEXT_hex8(HANDLE idComDev,unsigned int slen,unsigned char * sendbuffer,unsigned int *rlen,unsigned char * databuffer,unsigned char timeout,unsigned char FG);
/***********************************自动生成代码***added by chch 20110703****************************/
/***********************************自动生成代码***added by chch 20110703****************************/


};



#endif