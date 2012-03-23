//1.
typedef HANDLE  (__stdcall * DC_init) (__int16 port,long baud);
//2.
typedef __int16  (__stdcall * DC_exit)(HANDLE icdev);
//3.
typedef __int16  (__stdcall * DC_config)(HANDLE icdev,unsigned char _Mode,unsigned char _Baud);
//4.
typedef __int16  (__stdcall * DC_request)(HANDLE icdev,unsigned char _Mode,unsigned __int16  *TagType);
//5.
typedef __int16  (__stdcall * DC_anticoll) (HANDLE icdev,unsigned char _Bcnt,unsigned long *_Snr);
//6.
typedef __int16  (__stdcall * DC_select)(HANDLE icdev,unsigned long _Snr,unsigned char *_Size);
//7.
typedef __int16  (__stdcall * DC_authentication)(HANDLE icdev,unsigned char _Mode,unsigned char _SecNr);
//8.
typedef __int16  (__stdcall * DC_halt)(HANDLE icdev);
//9
typedef __int16  (__stdcall * DC_read)(HANDLE icdev,unsigned char _Adr,unsigned char *_Data);
//10.
typedef __int16  (__stdcall * DC_read_hex)(HANDLE icdev,unsigned char _Adr,char *_Data);
//11.
typedef __int16  (__stdcall * DC_write)(HANDLE icdev,unsigned char _Adr,unsigned char *_Data);
//12.
typedef __int16  (__stdcall * DC_write_hex)(HANDLE icdev,unsigned char _Adr,char *_Data);

typedef __int16  (__stdcall * DC_write_TS)(HANDLE icdev);
//13.
typedef __int16  (__stdcall * DC_load_key)(HANDLE icdev,unsigned char _Mode,unsigned char _SecNr,
							   unsigned char *_NKey);
//14.
typedef __int16  (__stdcall * DC_load_key_hex)(HANDLE icdev,unsigned char _Mode,unsigned char _SecNr,
								   char *_NKey);
//15.
typedef __int16  (__stdcall * DC_card)(HANDLE icdev,unsigned char _Mode,unsigned long *_Snr);
//16
typedef __int16  (__stdcall * DC_card_hex)(HANDLE icdev,unsigned char _Mode,unsigned char *snrstr);
//17.
typedef __int16  (__stdcall * DC_changeb3)(HANDLE icdev,unsigned char _SecNr,unsigned char *_KeyA,
							   unsigned char _B0,unsigned char _B1,unsigned char _B2,
							   unsigned char _B3,unsigned char _Bk,unsigned char *_KeyB);
//18.
typedef __int16  (__stdcall * DC_restore)(HANDLE icdev,unsigned char _Adr);
//19
typedef __int16  (__stdcall * DC_transfer)(HANDLE icdev,unsigned char _Adr);
//20
typedef __int16  (__stdcall * DC_increment)(HANDLE icdev,unsigned char _Adr,unsigned long _Value);
//21.
typedef __int16  (__stdcall * DC_decrement)(HANDLE icdev,unsigned char _Adr,unsigned long _Value);
//22.
typedef __int16  (__stdcall * DC_initval)(HANDLE icdev,unsigned char _Adr,unsigned long _Value);
//23.
typedef __int16  (__stdcall * DC_readval)(HANDLE icdev,unsigned char _Adr,unsigned long *_Value);
//24
typedef __int16  (__stdcall * DC_initval_ml)(HANDLE icdev,unsigned __int16   _Value);
//25
typedef __int16  (__stdcall * DC_readval_ml)(HANDLE icdev,unsigned __int16   *_Value);//17
//26
typedef __int16  (__stdcall * DC_decrement_ml)(HANDLE icdev,unsigned __int16   _Value);
//27
typedef __int16  (__stdcall * DC_authentication_2)(HANDLE icdev,unsigned char _Mode,unsigned char KeyNr,
									   unsigned char Adr);
//28
typedef __int16  (__stdcall * DC_anticoll2)(HANDLE icdev,unsigned char _Bcnt,unsigned long *_Snr);
//29
typedef __int16  (__stdcall * DC_select2)(HANDLE icdev,unsigned long _Snr,unsigned char *_Size);
//30.
typedef __int16  (__stdcall * DC_HL_write)(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,
							   unsigned long *_Snr,unsigned char *_Data);
//31
typedef __int16  (__stdcall * DC_HL_writehex)(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,
								  unsigned long *_Snr,unsigned char *_Data);

//32.
typedef __int16  (__stdcall * DC_HL_read)(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,
							  unsigned long _Snr,unsigned char *_Data,unsigned long *_NSnr);
//33
typedef __int16  (__stdcall * DC_HL_readhex)(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,
								 unsigned long _Snr,unsigned char *_Data,unsigned long *_NSnr);

//34.
typedef __int16  (__stdcall * DC_HL_authentication)(HANDLE icdev,unsigned char reqmode,unsigned long snr,
										unsigned char authmode,unsigned char secnr);
//35.
typedef __int16  (__stdcall * DC_check_write)(HANDLE icdev,unsigned long Snr,unsigned char authmode,
								  unsigned char Adr,unsigned char * _data);
//36
typedef __int16  (__stdcall * DC_check_writehex)(HANDLE icdev,unsigned long Snr,unsigned char authmode,
									 unsigned char Adr,unsigned char * _data);

//37.
typedef __int16  (__stdcall * DC_getver)(HANDLE icdev,unsigned char *sver);
//38
typedef __int16  (__stdcall * DC_update)(HANDLE icdev);
//39
typedef __int16  (__stdcall * DC_clr_control_bit)(HANDLE icdev,unsigned char _b);
//40.
typedef __int16  (__stdcall * DC_set_control_bit)(HANDLE icdev,unsigned char _b);
//41.
typedef __int16  (__stdcall * DC_reset)(HANDLE icdev,unsigned __int16   _Msec);
//42
typedef __int16  (__stdcall * DC_beep)(HANDLE icdev,unsigned short _Msec);
//43.
typedef __int16  (__stdcall * DC_disp_str)(HANDLE icdev,char *dispstr);
//44
typedef __int16  (__stdcall * DC_srd_eeprom)(HANDLE icdev,__int16   offset,__int16 lenth,
								 unsigned char *rec_buffer);
//45
typedef __int16  (__stdcall * DC_swr_eeprom)(HANDLE icdev,__int16   offset,__int16 lenth,
								 unsigned char* send_buffer);
//46
typedef __int16  (__stdcall * swr_alleeprom)(HANDLE icdev,__int16 offset,__int16 lenth,
								unsigned char* snd_buffer);
//47
typedef __int16  (__stdcall * srd_alleeprom)(HANDLE icdev,__int16 offset,__int16 lenth,
								unsigned char *receive_buffer);
//48
typedef __int16  (__stdcall * DC_srd_eepromhex)(HANDLE icdev,__int16   offset,__int16   lenth,
									unsigned char *rec_buffer);

//49
typedef __int16  (__stdcall * DC_swr_eepromhex)(HANDLE icdev,__int16   offset,__int16   lenth,
									unsigned char* send_buffer);

//50
typedef __int16  (__stdcall * DC_gettime)(HANDLE icdev,unsigned char *time);
//51
typedef __int16  (__stdcall * DC_gettimehex)(HANDLE icdev,char *time);

//52
typedef __int16  (__stdcall * DC_settime)(HANDLE icdev,unsigned char *time);
//53
typedef __int16  (__stdcall * DC_settimehex)(HANDLE icdev,char *time);

//54
typedef __int16  (__stdcall * DC_setbright)(HANDLE icdev,unsigned char bright);
//55
typedef __int16  (__stdcall * DC_ctl_mode)(HANDLE icdev,unsigned char mode);
//56
typedef __int16  (__stdcall * DC_disp_mode)(HANDLE icdev,unsigned char mode);
//57
typedef __int16  (__stdcall * dcdeshex)(unsigned char *key,unsigned char *sour,unsigned char *dest,
							__int16 m);

//58
typedef __int16  (__stdcall * dcdes)(unsigned char *key,unsigned char *sour,unsigned char *dest,__int16 m);
//59
typedef __int16  (__stdcall * DC_light)(HANDLE icdev,unsigned short _OnOff);
//60
typedef __int16  (__stdcall * DC_high_disp)(HANDLE icdev,unsigned char offset,unsigned char displen,
							   unsigned char *dispstr);
//61
typedef __int16  (__stdcall * DC_setcpu)(HANDLE icdev,unsigned char _Byte);
//62
typedef __int16  (__stdcall * DC_cpureset)(HANDLE icdev,unsigned char *rlen,unsigned char *databuffer);
//63
typedef __int16  (__stdcall * DC_cpuapdusource)(HANDLE icdev,unsigned char slen,unsigned char * sendbuffer,
								   unsigned char *rlen,unsigned char * databuffer);
//64
typedef __int16  (__stdcall * DC_cpuapdu)(HANDLE icdev,unsigned char slen,unsigned char * sendbuffer,
							 unsigned char *rlen,unsigned char * databuffer);
//65
typedef __int16  (__stdcall * DC_cpureset_hex)(HANDLE icdev,unsigned char *rlen, char *databuffer);
//66
typedef __int16  (__stdcall * DC_cpuapdusource_hex)(HANDLE icdev,unsigned char slen, char * sendbuffer,
									   unsigned char *rlen, char * databuffer);
//67
typedef __int16  (__stdcall * DC_cpuapdu_hex)(HANDLE icdev,unsigned char slen, char * sendbuffer,
								 unsigned char *rlen, char * databuffer);

typedef __int16  (__stdcall * DC_cpuapdurespon)(HANDLE idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer);
typedef __int16  (__stdcall * DC_cpuapdurespon_hex)(HANDLE idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer);


//68
typedef __int16  (__stdcall * DC_cpudown)(HANDLE icdev);
//69
typedef __int16  (__stdcall * DC_set_addr)(unsigned char saddr);
//70
typedef HANDLE (__stdcall * DC_init_485)(__int16 port,long baud);
//71
typedef __int16  (__stdcall * DC_changebaud_485)(HANDLE icdev,long baud);
//72
typedef __int16  (__stdcall * DC_change_addr)(HANDLE icdev,unsigned char saddr);
//73
typedef __int16  (__stdcall * DC_pro_reset)(HANDLE icdev,unsigned char *rlen,unsigned char *receive_data);
//74
typedef __int16  (__stdcall * DC_pro_command)(HANDLE idComDev,unsigned char slen,
								 unsigned char * sendbuffer,unsigned char *rlen,
								 unsigned char * databuffer,unsigned char timeout);
//75
typedef __int16  (__stdcall * DC_pro_resethex)(HANDLE icdev,unsigned char *rlen, char *receive_data);


//76
typedef __int16  (__stdcall * DC_pro_commandhex)(HANDLE idComDev,unsigned char slen, 
									char * sendbuffer,unsigned char *rlen, 
									char * databuffer,unsigned char timeout);
//77
typedef __int16  (__stdcall * DC_pro_commandsource)(HANDLE idComDev,unsigned char slen,
									   unsigned char * sendbuffer,unsigned char *rlen,
									   unsigned char * databuffer,unsigned char timeout);
//78
typedef __int16  (__stdcall * DC_pro_commandsourcehex)(HANDLE idComDev,unsigned char slen, 
									char * sendbuffer,unsigned char *rlen, 
									char * databuffer,unsigned char timeout);

//79
typedef __int16  (__stdcall * DC_pro_halt)(HANDLE icdev);
//80
typedef __int16  (__stdcall * DC_request_shc1102)(HANDLE icdev,unsigned char _Mode,
									 unsigned __int16 *TagType);
//81
typedef __int16  (__stdcall * DC_auth_shc1102)(HANDLE icdev,unsigned char *_Data);
//82
typedef __int16  (__stdcall * DC_read_shc1102)(HANDLE icdev,unsigned char _Adr,unsigned char *_Data);
//83
typedef __int16  (__stdcall * DC_write_shc1102)(HANDLE icdev,unsigned char _Adr,unsigned char *_Data);
//84
typedef __int16  (__stdcall * DC_halt_shc1102)(HANDLE icdev);
//85
typedef __int16  (__stdcall * HEX_a)(unsigned char *hex,unsigned char *a,__int16 length);
//86
typedef __int16  (__stdcall * A_hex)(unsigned char *a,unsigned char *hex,__int16 len);
//87
typedef __int16  (__stdcall * DC_config_card)(HANDLE icdev,unsigned char cardtype);
//88
typedef __int16  (__stdcall * DC_request_b)(HANDLE icdev,unsigned char _Mode,unsigned char AFI, 
		                       unsigned char N,unsigned char *ATQB);
//89
typedef __int16  (__stdcall * DC_slotmarker)(HANDLE icdev,unsigned char N, unsigned char *ATQB);
//90
typedef __int16  (__stdcall * DC_attrib)(HANDLE icdev,unsigned char *PUPI, unsigned char CID);
//91
typedef __int16  (__stdcall * DC_open_door)(HANDLE icdev,unsigned char cflag);
//92
typedef __int16  (__stdcall * DC_open_timedoor)(HANDLE icdev,unsigned __int16 utime);
//93
typedef __int16  (__stdcall * DC_read_random)(HANDLE icdev, unsigned char *data);
//94
typedef __int16  (__stdcall * DC_write_random)(HANDLE icdev,__int16 len, unsigned char *data);
//95
typedef __int16  (__stdcall * DC_read_random_hex)(HANDLE icdev, unsigned char *data);
//96
typedef __int16  (__stdcall * DC_write_random_hex)(HANDLE icdev,__int16 len, unsigned char *data);
//97
typedef __int16  (__stdcall * DC_erase_random)(HANDLE icdev,__int16 len);
//98
typedef __int16  (__stdcall * DC_mfdes_auth)(HANDLE icdev,unsigned char keyno,unsigned char keylen,unsigned char *authkey,
								unsigned char *randAdata,unsigned char *randBdata);
//99
typedef __int16  (__stdcall * DC_authentication_pass)(HANDLE icdev,unsigned char _Mode,
										 unsigned char _Addr,unsigned char *passbuff);
//100
typedef __int16  (__stdcall * DC_disp_neg)(HANDLE icdev,char *dispstr);
//101
typedef __int16  (__stdcall * DC_pro_commandlink)(HANDLE idComDev,unsigned char slen,
								 unsigned char * sendbuffer,unsigned char *rlen,
								 unsigned char * databuffer,unsigned char timeout,
								 unsigned char FG);
//102
typedef __int16  (__stdcall * DC_pro_commandlink_hex)(HANDLE idComDev,unsigned char slen,
										 unsigned char * sendbuffer,unsigned char *rlen,
										 unsigned char * databuffer,unsigned char timeout,
										 unsigned char FG);

typedef __int16  (__stdcall * DC_card_double)(HANDLE icdev,unsigned char _Mode,unsigned char *_Snr);
typedef __int16  (__stdcall * DC_card_double_hex)(HANDLE icdev,unsigned char _Mode,unsigned char *_Snr);
typedef __int16  (__stdcall * DC_read_idcard)(HANDLE icdev,unsigned char times,unsigned char *_Data);
typedef __int16  (__stdcall * DC_read_idcard_hex)(HANDLE icdev,unsigned char times,unsigned char *_Data);

typedef __int16  (__stdcall * DC_authentication_pass_hex)(HANDLE icdev,unsigned char _Mode,
										 unsigned char _Addr,unsigned char *passbuff);

typedef __int16  (__stdcall * DC_setcpupara) (HANDLE icdev,unsigned char cputype,
								  unsigned char cpupro,unsigned char cpuetu);
typedef __int16  (__stdcall * DC_command)(HANDLE idComDev,unsigned char cmd,unsigned char slen,
									   unsigned char * sendbuffer,unsigned char *rlen,
									   unsigned char * databuffer);

typedef __int16  (__stdcall * DC_command_hex)(HANDLE idComDev,unsigned char cmd,unsigned char slen, 
										  char * sendbuffer,unsigned char *rlen, 
										  char * databuffer);
typedef __int16  (__stdcall * DC_creat_mac)(unsigned char KeyLen,unsigned char *Key,unsigned short DataLen,
							unsigned char *Data,unsigned char *InitData,unsigned char AutoFixFlag,
							unsigned char FixChar,unsigned char *MacData);
typedef __int16  (__stdcall * DC_creat_mac_hex)(unsigned char KeyLen,unsigned char *Key,unsigned short DataLen,
							unsigned char *Data,unsigned char *InitData,unsigned char AutoFixFlag,
							unsigned char FixChar,unsigned char *MacData);
//------------------------------新增的为了整齐DLL而做的代码------------------------------
typedef __int16  (__stdcall * DC_HL_write_hex)(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,
								   unsigned long *_Snr,unsigned char *_Data);
typedef __int16  (__stdcall * DC_HL_read_hex)(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,
								  unsigned long _Snr,unsigned char *_Data,unsigned long *_NSnr);
typedef __int16  (__stdcall * DC_check_write_hex)(HANDLE icdev,unsigned long Snr,unsigned char authmode,
									  unsigned char Adr,unsigned char * _data);

typedef __int16  (__stdcall * DC_srd_eeprom_hex)(HANDLE icdev,__int16   offset,__int16   lenth,
									 unsigned char *rec_buffer);
typedef __int16  (__stdcall * DC_swr_eeprom_hex)(HANDLE icdev,__int16   offset,__int16   lenth,
									 unsigned char* send_buffer);

typedef __int16  (__stdcall * DC_gettime_hex)(HANDLE icdev,char *time);
typedef __int16  (__stdcall * DC_settime_hex)(HANDLE icdev,char *time);
typedef __int16  (__stdcall * DC_des_hex)(unsigned char *key,unsigned char *sour,unsigned char *dest,
							  __int16 m);
typedef __int16  (__stdcall * DC_des)(unsigned char *key,unsigned char *sour,unsigned char *dest,__int16 m);
typedef __int16  (__stdcall * DC_pro_reset_hex)(HANDLE icdev,unsigned char *rlen, char *receive_data);
typedef __int16  (__stdcall * DC_pro_command_hex)(HANDLE idComDev,unsigned char slen, 
									 char * sendbuffer,unsigned char *rlen, 
									 char * databuffer,unsigned char timeout);
typedef __int16  (__stdcall * DC_pro_commandsource_hex)(HANDLE idComDev,unsigned char slen, 
										   char * sendbuffer,unsigned char *rlen, 
										   char * databuffer,unsigned char timeout);
//-------------------------------------整齐DLL工作结束--------------------------------------------------
typedef __int16  (__stdcall * DC_switch_unix)(HANDLE icdev,long baud);

typedef __int16  (__stdcall * DC_authentication_passaddr)(HANDLE icdev,unsigned char _Mode,
										 unsigned char _Addr,unsigned char *passbuff);
typedef __int16  (__stdcall * DC_authentication_passaddr_hex)(HANDLE icdev,unsigned char _Mode,
											 unsigned char _Addr,unsigned char *passbuff);

typedef __int16  (__stdcall * DC_card_fm11rf005)(HANDLE icdev,unsigned char _Mode,unsigned long *_Snr);

typedef __int16  (__stdcall * DC_setusbtimeout)(unsigned char ntimes);

typedef __int16  (__stdcall * DC_mfdes_baud)(HANDLE icdev,unsigned char _Mode,unsigned char para);

typedef __int16  (__stdcall * DC_tripledes)(unsigned char *key,unsigned char *src,unsigned char *dest,__int16 m);

typedef __int16  (__stdcall * DC_tripledes_hex)(unsigned char *key,unsigned char *src,unsigned char *dest,__int16 m);

typedef __int16  (__stdcall * DC_mfdes_auth_hex)(HANDLE icdev,unsigned char keyno,unsigned char keylen,unsigned char *authkey,
								unsigned char *randAdata,unsigned char *randBdata);

typedef __int16  (__stdcall * DC_pro_sendcommandsource)(HANDLE idComDev,unsigned char slen,
										   unsigned char * sendbuffer,unsigned char timeout);										   

typedef __int16  (__stdcall * DC_pro_receivecommandsource)(HANDLE idComDev,unsigned char *rlen,
											  unsigned char * databuffer);
//----------------------------------以下为ISO15693 相关函数----------------------------------------
typedef __int16  (__stdcall * DC_inventory)(HANDLE icdev,unsigned char flags,
							   unsigned char AFI, 
							   unsigned char masklen, 
							   unsigned char *rlen,unsigned char *rbuffer);
typedef __int16  (__stdcall * DC_inventory_hex)(HANDLE icdev,unsigned char flags,
							   unsigned char AFI, 
							   unsigned char masklen, 
							   unsigned char *rlen,unsigned char *rbuffer);
typedef __int16  (__stdcall * DC_stay_quiet)(HANDLE icdev,unsigned char flags,unsigned char *UID);
typedef __int16  (__stdcall * DC_stay_quiet_hex)(HANDLE icdev,unsigned char flags,unsigned char *UID);
typedef __int16  (__stdcall * DC_select_uid)(HANDLE icdev,unsigned char flags,unsigned char *UID);
typedef __int16  (__stdcall * DC_select_uid_hex)(HANDLE icdev,unsigned char flags,unsigned char *UID);
typedef __int16  (__stdcall * DC_reset_to_ready)(HANDLE icdev,unsigned char flags,unsigned char *UID);
typedef __int16  (__stdcall * DC_reset_to_ready_hex)(HANDLE icdev,unsigned char flags,unsigned char *UID);
typedef __int16  (__stdcall * DC_readblock)(HANDLE icdev,unsigned char flags,
							   unsigned char startblock,unsigned char blocknum, 
							   unsigned char *UID, 
							   unsigned char *rlen,unsigned char *rbuffer);
typedef __int16  (__stdcall * DC_readblock_hex)(HANDLE icdev,unsigned char flags,
							   unsigned char startblock,unsigned char blocknum, 
							   unsigned char *UID, 
							   unsigned char *rlen,unsigned char *rbuffer);
typedef __int16  (__stdcall * DC_writeblock)(HANDLE icdev,unsigned char flags,
								unsigned char startblock,unsigned char blocknum, 
								unsigned char *UID, 
								unsigned char wlen,unsigned char *rbuffer);
typedef __int16  (__stdcall * DC_writeblock_hex)(HANDLE icdev,unsigned char flags,
								unsigned char startblock,unsigned char blocknum, 
								unsigned char *UID, 
								unsigned char wlen,unsigned char *rbuffer);
typedef __int16  (__stdcall * DC_lock_block)(HANDLE icdev,unsigned char flags,unsigned char block,
								unsigned char *UID);
typedef __int16  (__stdcall * DC_lock_block_hex)(HANDLE icdev,unsigned char flags,unsigned char block,
								unsigned char *UID);
typedef __int16  (__stdcall * DC_write_afi)(HANDLE icdev,unsigned char flags,unsigned char AFI,
							   unsigned char *UID);
typedef __int16  (__stdcall * DC_write_afi_hex)(HANDLE icdev,unsigned char flags,unsigned char AFI,
							   unsigned char *UID);
typedef __int16  (__stdcall * DC_lock_afi)(HANDLE icdev,unsigned char flags,unsigned char AFI,
							  unsigned char *UID);
typedef __int16  (__stdcall * DC_lock_afi_hex)(HANDLE icdev,unsigned char flags,unsigned char AFI,
							  unsigned char *UID);
typedef __int16  (__stdcall * DC_write_dsfid)(HANDLE icdev,unsigned char flags,unsigned char DSFID,
								 unsigned char *UID);
typedef __int16  (__stdcall * DC_write_dsfid_hex)(HANDLE icdev,unsigned char flags,unsigned char DSFID,
								 unsigned char *UID);
typedef __int16  (__stdcall * DC_lock_dsfid)(HANDLE icdev,unsigned char flags,unsigned char DSFID,
								unsigned char *UID);
typedef __int16  (__stdcall * DC_lock_dsfid_hex)(HANDLE icdev,unsigned char flags,unsigned char DSFID,
								unsigned char *UID);
typedef __int16  (__stdcall * DC_get_systeminfo)(HANDLE icdev,unsigned char flags,
									unsigned char *UID, 
									unsigned char *rlen,unsigned char *rbuffer);
typedef __int16  (__stdcall * DC_get_systeminfo_hex)(HANDLE icdev,unsigned char flags,
									unsigned char *UID, 
									unsigned char *rlen,unsigned char *rbuffer);
typedef __int16  (__stdcall * DC_get_securityinfo)(HANDLE icdev,unsigned char flags,
									  unsigned char startblock,unsigned char blocknum, 
									  unsigned char *UID, 
									  unsigned char *rlen,unsigned char *rbuffer);
typedef __int16  (__stdcall * DC_get_securityinfo_hex)(HANDLE icdev,unsigned char flags,
									  unsigned char startblock,unsigned char blocknum, 
									  unsigned char *UID, 
									  unsigned char *rlen,unsigned char *rbuffer);

//------------------------------FM11RF005M------------------------------------
typedef __int16  (__stdcall * DC_getsnr_fm11rf005)(HANDLE icdev,unsigned long *_Snr);
typedef __int16  (__stdcall * DC_getsnr_fm11rf005_hex)(HANDLE icdev,unsigned char *snrstr);
typedef __int16  (__stdcall * DC_write_fm11rf005)(HANDLE icdev,unsigned char _Adr,unsigned char *_Data);
typedef __int16  (__stdcall * DC_read_fm11rf005)(HANDLE icdev,unsigned char _Adr,unsigned char *_Data);
typedef __int16  (__stdcall * DC_read_fm11rf005_hex)(HANDLE icdev,unsigned char _Adr,char *_Data);
typedef __int16  (__stdcall * DC_write_fm11rf005_hex)(HANDLE icdev,unsigned char _Adr,char *_Data);

//------------------------------z9 function----------------------------------------
typedef __int16  (__stdcall * DCDEV_CommandMcu)(HANDLE idComDev,unsigned char ctimeout,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer);
typedef __int16  (__stdcall * DCDEV_CommandMcu_Hex)(HANDLE idComDev,unsigned char ctimeout,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer);

typedef __int16  (__stdcall * DC_displcd)(HANDLE idComDev,unsigned char flag);
typedef __int16  (__stdcall * DC_getinputpass)(HANDLE idComDev,unsigned char ctime,unsigned char *rlen,unsigned char * cpass);
typedef __int16  (__stdcall * DC_readmagcard)(HANDLE idComDev, unsigned char ctime, unsigned char *pTrack2Data, unsigned long *pTrack2Len, unsigned char *pTrack3Data, unsigned long *pTrack3Len);
typedef __int16  (__stdcall * DC_testdevicecomm)(HANDLE idComDev);
typedef __int16  (__stdcall * DC_dispmainmenu)(HANDLE idComDev);
typedef __int16  (__stdcall * DC_setdevicetime)(HANDLE idComDev,
									 unsigned char year,
									 unsigned char month,
									 unsigned char date,
									 unsigned char hour,
									 unsigned char minute,
									 unsigned char second);
typedef __int16  (__stdcall * DC_getdevicetime)(HANDLE idComDev,
									 unsigned char *year,
									 unsigned char *month,
									 unsigned char *date,
									 unsigned char *hour,
									 unsigned char *minute,
									 unsigned char *second);
typedef __int16  (__stdcall * DC_dispinfo)(HANDLE idComDev,unsigned char line,unsigned char offset,char *data);
typedef __int16  (__stdcall * DC_dispmaininfo)(HANDLE idComDev,unsigned char offset,char *data);
typedef __int16  (__stdcall * DC_posbeep)(HANDLE idComDev,unsigned char beeptime);
typedef __int16  (__stdcall * DC_ctlbacklight)(HANDLE idComDev, unsigned char cOpenFlag);
typedef __int16  (__stdcall * DC_ctlled)(HANDLE idComDev, unsigned char cLed, unsigned char cOpenFlag);
typedef __int16  (__stdcall * DC_lcdclrscrn)(HANDLE idComDev, unsigned char cLine);
typedef __int16  (__stdcall * DC_passin)(HANDLE idComDev,unsigned char ctime);
typedef __int16  (__stdcall * DC_passget)(HANDLE idComDev,unsigned char *rlen,unsigned char * cpass);
typedef __int16  (__stdcall * DC_passcancel)(HANDLE idComDev);
typedef __int16  (__stdcall * DC_getinputkey)(HANDLE idComDev,unsigned char disptype,unsigned char line,
							unsigned char ctime,unsigned char *rlen,unsigned char * ckeydata);
typedef __int16  (__stdcall * DC_displcd_ext)(HANDLE idComDev,unsigned char flag,unsigned char row,
								   unsigned char offset);
typedef __int16  (__stdcall * DC_readmagcardall)(HANDLE idComDev, unsigned char ctime, unsigned char *pTrack1Data, unsigned long *pTrack1Len,
									  unsigned char *pTrack2Data, unsigned long *pTrack2Len, unsigned char *pTrack3Data, unsigned long *pTrack3Len);
//-----------------------------z9 function end---------------------------------------------------
typedef __int16  (__stdcall * DC_readdevsnr)(HANDLE idComDev,unsigned char *snr);
typedef __int16  (__stdcall * DC_readreadersnr)(HANDLE idComDev,unsigned char *snr);
typedef __int16  (__stdcall * DC_resetdevice) (HANDLE idComDev);

//-------------------------------------接触式同步卡操作函数--------------------------
typedef __int16  (__stdcall * DC_read_4442)(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * buffer);
typedef __int16  (__stdcall * DC_read_4442_hex)(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char* buffer);
typedef __int16  (__stdcall * DC_write_4442)(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * buffer);
typedef __int16  (__stdcall * DC_write_4442_hex)(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char* buffer);
typedef __int16  (__stdcall * DC_verifypin_4442)(HANDLE icdev,unsigned char *passwd);
typedef __int16  (__stdcall * DC_verifypin_4442_hex)(HANDLE icdev,unsigned char *passwd);
typedef __int16  (__stdcall * DC_readpin_4442)(HANDLE icdev,unsigned char *passwd);
typedef __int16  (__stdcall * DC_readpin_4442_hex)(HANDLE icdev,unsigned char *passwd);
typedef __int16  (__stdcall * DC_readpincount_4442)(HANDLE icdev);
typedef __int16  (__stdcall * DC_changepin_4442)(HANDLE icdev,unsigned char *passwd);
typedef __int16  (__stdcall * DC_changepin_4442_hex)(HANDLE icdev,unsigned char *passwd);
typedef __int16  (__stdcall * DC_readwrotect_4442)(HANDLE icdev,__int16 offset,__int16 leng,unsigned char *buffer);
typedef __int16  (__stdcall * DC_readwrotect_4442_hex)(HANDLE icdev,__int16 offset,__int16 leng,unsigned char *buffer);
typedef __int16  (__stdcall * DC_writeprotect_4442)(HANDLE icdev,__int16 offset,__int16 leng,unsigned char *buffer);
typedef __int16  (__stdcall * DC_writeprotect_4442_hex)(HANDLE icdev,__int16 offset,__int16 leng,unsigned char *buffer);

typedef __int16  (__stdcall * DC_write_24c)(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * snd_buffer);
typedef __int16  (__stdcall * DC_write_24c_hex)(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * snd_buffer);
typedef __int16  (__stdcall * DC_write_24c64)(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * snd_buffer);
typedef __int16  (__stdcall * DC_write_24c64_hex)(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * snd_buffer);
typedef __int16  (__stdcall * DC_read_24c)(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * receive_buffer);
typedef __int16  (__stdcall * DC_read_24c_hex)(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * receive_buffer);
typedef __int16  (__stdcall * DC_read_24c64)(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * receive_buffer);
typedef __int16  (__stdcall * DC_read_24c64_hex)(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * receive_buffer);


typedef __int16  (__stdcall * DC_read_4428)(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * buffer);
typedef __int16  (__stdcall * DC_read_4428_hex)(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char* buffer);
typedef __int16  (__stdcall * DC_write_4428)(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * buffer);
typedef __int16  (__stdcall * DC_write_4428_hex)(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char* buffer);
typedef __int16  (__stdcall * DC_verifypin_4428)(HANDLE icdev,unsigned char *passwd);
typedef __int16  (__stdcall * DC_verifypin_4428_hex)(HANDLE icdev,unsigned char *passwd);
typedef __int16  (__stdcall * DC_readpin_4428)(HANDLE icdev,unsigned char *passwd);
typedef __int16  (__stdcall * DC_readpin_4428_hex)(HANDLE icdev,unsigned char *passwd);
typedef __int16  (__stdcall * DC_readpincount_4428)(HANDLE icdev);
typedef __int16  (__stdcall * DC_changepin_4428)(HANDLE icdev,unsigned char *passwd);
typedef __int16  (__stdcall * DC_changepin_4428_hex)(HANDLE icdev,unsigned char *passwd);

typedef __int16 (__stdcall * DC_Check_4442)(HANDLE icdev);
typedef __int16  (__stdcall * DC_Check_4428) (HANDLE icdev);
typedef __int16  (__stdcall * DC_Check_24C01) (HANDLE icdev);
typedef __int16  (__stdcall * DC_Check_24C02) (HANDLE icdev);
typedef __int16  (__stdcall * DC_Check_24C04) (HANDLE icdev);
typedef __int16  (__stdcall * DC_Check_24C08) (HANDLE icdev);
typedef __int16  (__stdcall * DC_Check_24C16) (HANDLE icdev);
typedef __int16  (__stdcall * DC_Check_24C64) (HANDLE icdev);
typedef __int16  (__stdcall * DC_Check_CPU) (HANDLE icdev);
typedef __int16  (__stdcall * DC_CheckCard) (HANDLE icdev);

//--------------------------------------------------------------------------------
typedef __int16  (__stdcall * DC_getrcinfo)(HANDLE icdev,unsigned char *info);
typedef __int16  (__stdcall * DC_getrcinfo_hex)(HANDLE icdev,unsigned char *info);
typedef __int16  (__stdcall * DC_getlongver)(HANDLE icdev,unsigned char *sver);

//Check Card Type A or Type B
typedef __int16  (__stdcall * DC_cardAB)(HANDLE icdev,unsigned char *rlen,unsigned char *rbuf,unsigned char *type);
