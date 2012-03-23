#include "stdafx.h"
#include "D8Cap.h"

#include <string>
#include <iostream>
using namespace std;

D8Cap::D8Cap(){

}

//基本函数
__int16  __stdcall D8Cap::dc_card8(HANDLE icdev,unsigned char _Mode,unsigned long *_Snr){	
	if (NULL != my_dc_card){
		return my_dc_card(icdev, _Mode, _Snr);
	}
	return -1;
}



HANDLE D8Cap::dc_init8(__int16 port,long baud){
	if (NULL != my_dc_init){
		return my_dc_init(port, baud);
	}
	return NULL;
}

__int16  __stdcall D8Cap::dc_load_key8(HANDLE icdev,unsigned char _Mode,unsigned char _SecNr, unsigned char *_NKey){
	if (NULL != my_dc_load_key){
		return my_dc_load_key(icdev, _Mode, _SecNr, _NKey);
	}
	return -1;
}
__int16  __stdcall D8Cap::dc_authentication8(HANDLE icdev,unsigned char _Mode,unsigned char _SecNr){
	if (NULL != my_dc_authentication){
		return my_dc_authentication(icdev, _Mode, _SecNr);
	}
	return -1;
}
__int16  __stdcall D8Cap::dc_authentication_28(HANDLE icdev,unsigned char _Mode,unsigned char KeyNr,unsigned char Adr){
	if (NULL != my_dc_authentication2){
		return my_dc_authentication2(icdev, _Mode, KeyNr, Adr);
	}
	return -1;
}

__int16  __stdcall D8Cap::dc_read8(HANDLE icdev,unsigned char _Adr,unsigned char *_Data){
	if (NULL != my_dc_read){
		return my_dc_read(icdev, _Adr, _Data);
	}
	return -1;
}
__int16  __stdcall D8Cap::dc_write8(HANDLE icdev,unsigned char _Adr,unsigned char *_Data){
	if (NULL != my_dc_write){
		return my_dc_write(icdev, _Adr, _Data);
	}
	return -1;
}
__int16  __stdcall D8Cap::dc_beep8(HANDLE icdev,unsigned short _Msec){
	if (NULL != my_dc_beep){
		return my_dc_beep(icdev, _Msec);
	}
	return -1;
}
__int16  __stdcall D8Cap::dc_exit8(HANDLE icdev){
	if (NULL != my_dc_exit){
		return my_dc_exit(icdev);
	}
	return -1;
}
__int16  __stdcall D8Cap::dc_request8(HANDLE icdev,unsigned char _Mode,unsigned __int16  *TagType){
	if (NULL != my_dc_request){
		return my_dc_request(icdev, _Mode, TagType);
	}
	return -1;
}
__int16  __stdcall D8Cap::dc_select8(HANDLE icdev,unsigned long _Snr,unsigned char *_Size){
	if (NULL != my_dc_select){
		return my_dc_select(icdev, _Snr, _Size);
	}
	return -1;
}
__int16  __stdcall  D8Cap::dc_anticoll8(HANDLE icdev,unsigned char _Bcnt,unsigned long *_Snr){
	if (NULL != my_dc_anticoll){
		return my_dc_anticoll(icdev, _Bcnt, _Snr);
	}
	return -1;
}
__int16 __stdcall D8Cap::dc_authentication_pass8(HANDLE icdev,unsigned char _Mode, unsigned char _Addr,unsigned char *passbuff){
	if (NULL != my_dc_authentication_pass){
		return my_dc_authentication_pass(icdev, _Mode, _Addr, passbuff);
	}
	return -1;
}
__int16  __stdcall D8Cap::dc_halt8(HANDLE icdev){
	if (NULL != my_dc_halt){
		return my_dc_halt(icdev);
	}
	return -1;
}
__int16  __stdcall D8Cap::dc_changeb38(HANDLE icdev,unsigned char _SecNr,unsigned char *_KeyA,
									   unsigned char _B0,unsigned char _B1,unsigned char _B2,
									   unsigned char _B3,unsigned char _Bk,unsigned char *_KeyB){
										   if (NULL != my_dc_changeb3){
											   return my_dc_changeb3(icdev,_SecNr, _KeyA,_B0,_B1,_B2, _B3, _Bk, _KeyB);
										   }
										   return -1;
}

__int16  __stdcall D8Cap::dc_HL_authentication8(HANDLE icdev,unsigned char reqmode,unsigned long snr,
												unsigned char authmode,unsigned char secnr){
													if (NULL != my_dc_HL_authentication){
														return my_dc_HL_authentication(icdev, reqmode, snr, authmode, secnr);
													}
													return -1;

}
__int16  __stdcall D8Cap::dc_check_write8(HANDLE icdev,unsigned long Snr,unsigned char authmode,
										  unsigned char Adr,unsigned char * _data){
											  if (NULL != my_dc_check_write){
												  return my_dc_check_write(icdev, Snr, authmode, Adr, _data);
											  }
											  return -1;
}

__int16  __stdcall D8Cap::dc_HL_read8(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,
									  unsigned long _Snr,unsigned char *_Data,unsigned long *_NSnr){
										  if (NULL != my_dc_HL_read){
											  return my_dc_HL_read(icdev, _Mode, _Adr, _Snr, _Data, _NSnr);
										  }
										  return -1;
}
__int16  __stdcall D8Cap::dc_HL_write8(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,
									   unsigned long *_Snr,unsigned char *_Data){
										   if (NULL != my_dc_HL_write){
											   return my_dc_HL_write(icdev, _Mode, _Adr, _Snr, _Data);
										   }
										   return -1;
}
__int16  __stdcall D8Cap::dc_des_hex8(unsigned char *key,unsigned char *sour,unsigned char *dest,
									  __int16 m){
										  if (NULL != my_dc_des_hex){
											  return my_dc_des_hex(key, sour, dest, m);
										  }
										  return -1;
}
//带Hex函数
__int16 __stdcall D8Cap::dc_card_hex8(HANDLE icdev,unsigned char _Mode,unsigned char *snrstr){
	if (NULL != my_dc_card_hex){
		return my_dc_card_hex(icdev, _Mode, snrstr);
	}
	return -1;
}
__int16  __stdcall D8Cap::dc_load_key_hex8(HANDLE icdev,unsigned char _Mode,unsigned char _SecNr,char *_NKey){
	if (NULL != my_dc_load_key_hex){
		return my_dc_load_key_hex(icdev, _Mode, _SecNr, _NKey);
	}
	return -1;
}

__int16 __stdcall D8Cap::dc_authentication_pass_hex8(HANDLE icdev,unsigned char _Mode,unsigned char _Addr,unsigned char *passbuff){
	if (NULL != my_dc_authentication_path_hex){
		return my_dc_authentication_path_hex(icdev, _Mode, _Addr, passbuff);
	}
	return -1;
}
__int16  __stdcall D8Cap::dc_read_hex8(HANDLE icdev,unsigned char _Adr,char *_Data){
	if (NULL != my_dc_read_hex){
		return my_dc_read_hex(icdev, _Adr, _Data);
	}
	return -1;
}
__int16  __stdcall D8Cap::dc_write_hex8(HANDLE icdev,unsigned char _Adr,char *_Data){
	if (NULL != my_dc_write_hex){
		return my_dc_write_hex(icdev, _Adr, _Data);
	}
	return -1;
}
__int16  __stdcall D8Cap::dc_srd_eepromhex8(HANDLE icdev,__int16   offset,__int16   lenth,unsigned char *rec_buffer){
	if (NULL != my_dc_srd_eepromhex){
		return my_dc_srd_eepromhex(icdev, offset, lenth, rec_buffer);
	}
	return -1;
}
__int16  __stdcall D8Cap::dc_swr_eepromhex8(HANDLE icdev,__int16   offset,__int16   lenth, unsigned char* send_buffer){
	if (NULL != my_dc_swr_eepromhex){
		return my_dc_swr_eepromhex(icdev, offset, lenth, send_buffer);
	}
	return -1;
}
__int16 __stdcall D8Cap::dc_cpuapdu_hex8(HANDLE icdev,unsigned char slen, char * sendbuffer,unsigned char *rlen, char * databuffer){
	if (NULL != my_dc_cpuapdu_hex){
		return my_dc_cpuapdu_hex(icdev, slen, sendbuffer, rlen, databuffer);
	}
	return -1;
}
__int16 __stdcall D8Cap::dc_cpureset_hex8(HANDLE icdev,unsigned char *rlen, char *databuffer){
	if (NULL != my_dc_cpureset_hex){
		return my_dc_cpureset_hex(icdev, rlen, databuffer);
	}
	return -1;
}

//值操作
__int16  __stdcall D8Cap::dc_initval8(HANDLE icdev,unsigned char _Adr,unsigned long _Value){
	if (NULL != my_dc_initval){
		return my_dc_initval(icdev, _Adr, _Value);
	}
	return -1;
}
__int16  __stdcall D8Cap::dc_readval8(HANDLE icdev,unsigned char _Adr,unsigned long *_Value){
	if (NULL != my_dc_readval){
		return my_dc_readval(icdev, _Adr, _Value);
	}
	return -1;
}
__int16  __stdcall D8Cap::dc_increment8(HANDLE icdev,unsigned char _Adr,unsigned long _Value){
	if (NULL != my_dc_increment){
		return my_dc_increment(icdev, _Adr, _Value);
	}
	return -1;
}
__int16  __stdcall D8Cap::dc_decrement8(HANDLE icdev,unsigned char _Adr,unsigned long _Value){
	if (NULL != my_dc_decrement){
		return my_dc_decrement(icdev, _Adr, _Value);
	}
	return -1;
}
__int16  __stdcall D8Cap::dc_restore8(HANDLE icdev,unsigned char _Adr){
	if (NULL != my_dc_restore){
		return my_dc_restore(icdev, _Adr);
	}
	return -1;
}


__int16 __stdcall D8Cap::dc_getver8(HANDLE icdev,unsigned char *sver)
{
	if (NULL != my_dc_getver){
		return my_dc_getver(icdev, sver);
	}
	return -1;
}




__int16  __stdcall D8Cap::dc_srd_eeprom8(HANDLE icdev,__int16   offset,__int16 lenth,
								  unsigned char *rec_buffer)
{
	if (NULL != my_dc_srd_eeprom){
		return my_dc_srd_eeprom(icdev, offset, lenth,rec_buffer);
	}
	return -1;
}

__int16  __stdcall D8Cap::dc_transfer8(HANDLE icdev,unsigned char _Adr)
{
if (NULL != my_dc_transfer){
		return my_dc_transfer(icdev, _Adr);
	}
	return -1;
}






__int16  __stdcall D8Cap::dc_swreeprom8(HANDLE icdev,__int16   offset,__int16 lenth,
										unsigned char* send_buffer)
{
	if (NULL != my_dc_swreeprom){
		return my_dc_swreeprom(icdev,offset,lenth,send_buffer);
	}
	return -1;
}


__int16 __stdcall D8Cap::a_hex8(unsigned char *a,unsigned char *hex,__int16 len)
{
	if (NULL != my_a_hex){
		return my_a_hex(a,hex,len);
	}
	return -1;
}

__int16 __stdcall D8Cap::hex_a8(unsigned char *hex,unsigned char *a,__int16 length)
{
	if (NULL != my_hex_a){
		return my_hex_a(hex,a,length);
	}
	return -1;
}
__int16 __stdcall D8Cap::dc_reset8(HANDLE icdev,unsigned __int16   _Msec)
{
	if (NULL != my_dc_reset){
		return my_dc_reset(icdev,_Msec);
	}
	return -1;
}


__int16 __stdcall D8Cap::dc_cpuapdu8(HANDLE icdev,unsigned char slen,unsigned char * sendbuffer,
									 unsigned char *rlen,unsigned char * databuffer)
{
	if (NULL != my_dc__cpuapdu){
		return my_dc__cpuapdu(icdev,slen,sendbuffer,rlen,databuffer);
	}
	return -1;
}

__int16 __stdcall D8Cap::dc_cpuapdusource8(HANDLE icdev,unsigned char slen,unsigned char * sendbuffer,
										   unsigned char *rlen,unsigned char * databuffer)
{
	if (NULL != my_dc_cpuapdusource){
		return my_dc_cpuapdusource(icdev,slen,sendbuffer,rlen,databuffer);
	}
	return -1;
}

__int16 __stdcall D8Cap::dc_cpureset8(HANDLE icdev,unsigned char *rlen,unsigned char *databuffer)
{
	if (NULL != my_dc_cpureset){
		return my_dc_cpureset(icdev,rlen,databuffer);
	}
	return -1;
}


__int16 __stdcall D8Cap::dc_setcpu8(HANDLE icdev,unsigned char _Byte)
{
	if (NULL != my_dc_Setcpu){
		return my_dc_Setcpu(icdev,_Byte);
	}
	return -1;
}


__int16 __stdcall  D8Cap::dc_setcpupara8(HANDLE icdev,unsigned char cputype,
										 unsigned char cpupro,unsigned char cpuetu)
{
	if (NULL != my_dc_Setcpupara){
		return my_dc_Setcpupara(icdev,cputype,cpupro,cpuetu);
	}
	return -1;
}

//RFMA专用
__int16  __stdcall D8Cap::dc_gettime8(HANDLE icdev,unsigned char *time){
	if (NULL != my_dc_gettime){
		return my_dc_gettime(icdev, time);
	}
	return -1;
}
__int16 __stdcall D8Cap::dc_high_disp8(HANDLE icdev,unsigned char offset,unsigned char displen,	unsigned char *dispstr){
	if (NULL != my_dc_high_disp){
		return my_dc_high_disp(icdev, offset, displen, dispstr);
	}
	return -1;
}
__int16  __stdcall D8Cap::dc_disp_mode8(HANDLE icdev,unsigned char mode){
	if (NULL != my_dc_disp_mode){
		return my_dc_disp_mode(icdev, mode);
	}
	return -1;
}
__int16  __stdcall D8Cap::dc_setbright8(HANDLE icdev,unsigned char bright){
	if (NULL != my_dc_setbright){
		return my_dc_setbright(icdev, bright);
	}
	return -1;
}
__int16  __stdcall D8Cap::dc_disp_str8(HANDLE icdev,char *dispstr){
	if (NULL != my_dc_disp_str){
		return my_dc_disp_str(icdev, dispstr);
	}
	return -1;
}
__int16  __stdcall D8Cap::dc_settime8(HANDLE icdev,unsigned char *time){
	if (NULL != my_dc_settime){
		return my_dc_settime(icdev, time);
	}
	return -1;
}

//NEW ADD BY ZXB 091116
__int16 __stdcall  D8Cap::dc_getcpupara8(HANDLE icdev,unsigned char cputype,unsigned char *cpupro,unsigned char *cpuetu){
	if (NULL != my_dc_getcpupara){
		return my_dc_getcpupara(icdev, cputype,cpupro,cpuetu);
	}
	return -1;
}
__int16 __stdcall  D8Cap::dc_cpuapdusourceEXT8(HANDLE icdev,__int16 slen,unsigned char * sendbuffer,__int16 *rlen,unsigned char * databuffer){
	if (NULL != my_dc_cpuapdusourceEXT){
		return my_dc_cpuapdusourceEXT(icdev, slen,sendbuffer,rlen,databuffer);
	}
	return -1;
}
__int16 __stdcall  D8Cap::dc_cpuapdusourceEXT_hex8(HANDLE icdev,__int16 slen, char * sendbuffer,__int16 *rlen, char * databuffer){
	if (NULL != my_dc_cpuapdusourceEXT_hex){
		return my_dc_cpuapdusourceEXT_hex(icdev, slen,sendbuffer,rlen,databuffer);
	}
	return -1;
}
__int16 __stdcall  D8Cap::dc_cpuapduEXT8(HANDLE icdev,__int16 slen,unsigned char * sendbuffer,__int16 *rlen,unsigned char * databuffer){
	if (NULL != my_dc_cpuapduEXT){
		return my_dc_cpuapduEXT(icdev, slen,sendbuffer,rlen,databuffer);
	}
	return -1;
}
__int16 __stdcall  D8Cap::dc_cpuapduEXT_hex8(HANDLE icdev,__int16 slen,char * sendbuffer,__int16 *rlen,char * databuffer){
	if (NULL != my_dc_cpuapduEXT_hex){
		return my_dc_cpuapduEXT_hex(icdev, slen,sendbuffer,rlen,databuffer);
	}
	return -1;
}
__int16 __stdcall  D8Cap::dc_pro_commandlinkEXT8(HANDLE idComDev,unsigned int slen,
										 unsigned char * sendbuffer,unsigned int *rlen,
										 unsigned char * databuffer,unsigned char timeout,
										 unsigned char FG){
											 if (NULL != my_dc_pro_commandlinkEXT){
												 return my_dc_pro_commandlinkEXT(idComDev, slen,sendbuffer,rlen,databuffer,timeout,FG);
											 }
											 return -1;
}

__int16 __stdcall D8Cap::dc_pro_reset8(HANDLE icdev,unsigned char *rlen,unsigned char *receive_data)
{
	if(NULL!=my_dc_pro_reset)
	{
		return my_dc_pro_reset(icdev,rlen,receive_data);
	}
	return -1;
	
}
__int16 __stdcall D8Cap::dc_pro_command8(HANDLE idComDev,unsigned char slen,
								 unsigned char * sendbuffer,unsigned char *rlen,
								 unsigned char * databuffer,unsigned char timeout)
{
	if(NULL!=my_dc_pro_command)
	{
		return my_dc_pro_command(idComDev,slen,sendbuffer,rlen,databuffer,timeout);

	}
	return -1;
	
}


__int16 __stdcall D8Cap::dc_pro_halt8(HANDLE icdev)
{
	if(NULL!=my_dc_pro_halt)
	{
		return my_dc_pro_halt(icdev);
	}
	return -1;

}
__int16  __stdcall D8Cap::dc_config8(HANDLE icdev,unsigned char _Mode,unsigned char _Baud)
{
	if(NULL!=my_dc_config)
	{
		return my_dc_config(icdev,_Mode,_Baud);
	}
	return -1;
	
}



 __int16 __stdcall D8Cap::dc_card_double8(HANDLE icdev,unsigned char _Mode,unsigned char *_Snr)
 {
	 if(NULL!=my_dc_card_double)
	 {
		 return my_dc_card_double(icdev,_Mode,_Snr);
	 }
	 return -1;

 }


  __int16 __stdcall D8Cap::dc_card_double_hex8(HANDLE icdev,unsigned char _Mode,unsigned char *_Snr)
  {
	  if(NULL!=my_dc_card_double_hex)
	  {
		  return my_dc_card_double_hex(icdev,_Mode,_Snr);
	  }
	  return -1;
  }


__int16  __stdcall  D8Cap::dc_gettimehex8(HANDLE icdev,char *time)
{
	if(NULL!=my_dc_gettimehex)
	{
		return my_dc_gettimehex(icdev,time);
	}
	return -1;

}
 __int16  __stdcall  D8Cap::dc_settimehex8(HANDLE icdev,char *time)
 {
	 if(NULL!=my_dc_settimehex)
	 {
		 return my_dc_settimehex(icdev,time);
	 }
	 return -1;

 }

  //added on 20110627
 __int16 __stdcall D8Cap::dc_readblock8(HANDLE icdev,unsigned char flags,
	 unsigned char startblock,unsigned char blocknum, 
	 unsigned char *UID, 
	 unsigned char *rlen,unsigned char *rbuffer){
	 if(NULL!=my_dc_readblock)
	 {
		 return my_dc_readblock(icdev,flags,startblock,blocknum,UID,rlen,rbuffer);
	 }
	 return -1;
	 
 }
 __int16 __stdcall D8Cap::dc_readblock_hex8(HANDLE icdev,unsigned char flags,
	 unsigned char startblock,unsigned char blocknum, 
	 unsigned char *UID, 
	 unsigned char *rlen,unsigned char *rbuffer){
	 if(NULL!=my_dc_readblock_hex)
	 {
		 return my_dc_readblock_hex(icdev,flags,startblock,blocknum,UID,rlen,rbuffer);
	 }
	 return -1;
	 
 }
 __int16 __stdcall D8Cap::dc_writeblock8(HANDLE icdev,unsigned char flags,
	 unsigned char startblock,unsigned char blocknum, 
	 unsigned char *UID, 
	 unsigned char wlen,unsigned char *rbuffer){
	 if(NULL!=my_dc_writeblock)
	 {
		 return my_dc_writeblock(icdev,flags,startblock,blocknum,UID,wlen,rbuffer);
	 }
	 return -1;
	 
 }
 __int16 __stdcall D8Cap::dc_writeblock_hex8(HANDLE icdev,unsigned char flags,
	 unsigned char startblock,unsigned char blocknum, 
	 unsigned char *UID, 
	 unsigned char wlen,unsigned char *rbuffer){
	 if(NULL!=my_dc_writeblock_hex)
	 {
		 return my_dc_writeblock_hex(icdev,flags,startblock,blocknum,UID,wlen,rbuffer);
	 }
	 return -1;
	 
 }


 __int16 __stdcall  D8Cap::dc_cardAB8(HANDLE icdev,unsigned char *rlen,unsigned char *rbuf,unsigned char *type)
 {
	 if(NULL!=my_dc_cardAB)
	 {
		 return my_dc_cardAB(icdev,rlen,rbuf,type);
	 }
	 return -1;
	 

 }

  //added on 20110627
  
 __int16 __stdcall D8Cap::dc_pro_commandsource8(HANDLE idComDev,unsigned char slen,
											    unsigned char * sendbuffer,unsigned char *rlen,
									            unsigned char * databuffer,unsigned char timeout)
 {
	 if(NULL!=my_dc_pro_commandsource)
	 {
		 return my_dc_pro_commandsource(idComDev,slen,sendbuffer,rlen,databuffer,timeout);
	 }
	 return -1;

 }
 

 __int16 __stdcall D8Cap::dc_pro_commandsourcehex8(HANDLE idComDev,unsigned char slen, 
											char * sendbuffer,unsigned char *rlen, 
										    char * databuffer,unsigned char timeout)
 {
	 if(NULL!=my_dc_pro_commandsourcehex)
	 {
		 return my_dc_pro_commandsourcehex(idComDev,slen,sendbuffer,rlen,databuffer,timeout);
	 }
	 return -1;
	 
 }


 __int16 __stdcall D8Cap::dc_cpudown8(HANDLE icdev)
 {
	 if(NULL!=my_dc_cpudown)
	 {
		 return my_dc_cpudown(icdev);
	 }
	 return -1;

 }
 /***********************************自动生成代码***added by chch 20110703****************************/
/***********************************自动生成代码***added by chch 20110703****************************/
__int16 D8Cap::dc_write_TS8(HANDLE icdev){
	if(NULL != my_dc_write_TS){
		return my_dc_write_TS(icdev);
	}
	return NULL;
}
__int16 D8Cap::dc_initval_ml8(HANDLE icdev,unsigned __int16   _Value){
	if(NULL != my_dc_initval_ml){
		return my_dc_initval_ml(icdev,_Value);
	}
	return NULL;
}
__int16 D8Cap::dc_readval_ml8(HANDLE icdev,unsigned __int16   *_Value){
	if(NULL != my_dc_readval_ml){
		return my_dc_readval_ml(icdev,_Value);
	}
	return NULL;
}
__int16 D8Cap::dc_anticoll28(HANDLE icdev,unsigned char _Bcnt,unsigned long *_Snr){
	if(NULL != my_dc_anticoll2){
		return my_dc_anticoll2(icdev,_Bcnt,_Snr);
	}
	return NULL;
}
__int16 D8Cap::dc_select28(HANDLE icdev,unsigned long _Snr,unsigned char *_Size){
	if(NULL != my_dc_select2){
		return my_dc_select2(icdev,_Snr,_Size);
	}
	return NULL;
}
__int16 D8Cap::dc_HL_writehex8(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,unsigned long *_Snr,unsigned char *_Data){
	if(NULL != my_dc_HL_writehex){
		return my_dc_HL_writehex(icdev,_Mode,_Adr,_Snr,_Data);
	}
	return NULL;
}
__int16 D8Cap::dc_HL_readhex8(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,unsigned long _Snr,unsigned char *_Data,unsigned long *_NSnr){
	if(NULL != my_dc_HL_readhex){
		return my_dc_HL_readhex(icdev,_Mode,_Adr,_Snr,_Data,_NSnr);
	}
	return NULL;
}
__int16 D8Cap::dc_check_writehex8(HANDLE icdev,unsigned long Snr,unsigned char authmode,unsigned char Adr,unsigned char * _data){
	if(NULL != my_dc_check_writehex){
		return my_dc_check_writehex(icdev,Snr,authmode,Adr,_data);
	}
	return NULL;
}
__int16 D8Cap::dc_clr_control_bit8(HANDLE icdev,unsigned char _b){
	if(NULL != my_dc_clr_control_bit){
		return my_dc_clr_control_bit(icdev,_b);
	}
	return NULL;
}
__int16 D8Cap::dc_set_control_bit8(HANDLE icdev,unsigned char _b){
	if(NULL != my_dc_set_control_bit){
		return my_dc_set_control_bit(icdev,_b);
	}
	return NULL;
}
__int16 D8Cap::dc_swr_eeprom8(HANDLE icdev,__int16   offset,__int16 lenth,unsigned char* send_buffer){
	if(NULL != my_dc_swr_eeprom){
		return my_dc_swr_eeprom(icdev,offset,lenth,send_buffer);
	}
	return NULL;
}
__int16 D8Cap::swr_alleeprom8(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char* snd_buffer){
	if(NULL != my_swr_alleeprom){
		return my_swr_alleeprom(icdev,offset,lenth,snd_buffer);
	}
	return NULL;
}
__int16 D8Cap::srd_alleeprom8(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char *receive_buffer){
	if(NULL != my_srd_alleeprom){
		return my_srd_alleeprom(icdev,offset,lenth,receive_buffer);
	}
	return NULL;
}
__int16 D8Cap::dc_ctl_mode8(HANDLE icdev,unsigned char mode){
	if(NULL != my_dc_ctl_mode){
		return my_dc_ctl_mode(icdev,mode);
	}
	return NULL;
}
__int16 D8Cap::dcdeshex8(unsigned char *key,unsigned char *sour,unsigned char *dest,__int16 m){
	if(NULL != my_dcdeshex){
		return my_dcdeshex(key,sour,dest,m);
	}
	return NULL;
}
__int16 D8Cap::dcdes8(unsigned char *key,unsigned char *sour,unsigned char *dest,__int16 m){
	if(NULL != my_dcdes){
		return my_dcdes(key,sour,dest,m);
	}
	return NULL;
}
__int16 D8Cap::dc_light8(HANDLE icdev,unsigned short _OnOff){
	if(NULL != my_dc_light){
		return my_dc_light(icdev,_OnOff);
	}
	return NULL;
}
__int16 D8Cap::dc_cpuapdusource_hex8(HANDLE icdev,unsigned char slen, char * sendbuffer,unsigned char *rlen, char * databuffer){
	if(NULL != my_dc_cpuapdusource_hex){
		return my_dc_cpuapdusource_hex(icdev,slen,sendbuffer,rlen,databuffer);
	}
	return NULL;
}
__int16 D8Cap::dc_cpuapdurespon8(HANDLE idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer){
	if(NULL != my_dc_cpuapdurespon){
		return my_dc_cpuapdurespon(idComDev,slen,sendbuffer,rlen,databuffer);
	}
	return NULL;
}
__int16 D8Cap::dc_cpuapdurespon_hex8(HANDLE idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer){
	if(NULL != my_dc_cpuapdurespon_hex){
		return my_dc_cpuapdurespon_hex(idComDev,slen,sendbuffer,rlen,databuffer);
	}
	return NULL;
}
__int16 D8Cap::dc_set_addr8(unsigned char saddr){
	if(NULL != my_dc_set_addr){
		return my_dc_set_addr(saddr);
	}
	return NULL;
}
HANDLE D8Cap::dc_init_4858(__int16 port,long baud){
	if(NULL != my_dc_init_485){
		return my_dc_init_485(port,baud);
	}
	return NULL;
}
__int16 D8Cap::dc_changebaud_4858(HANDLE icdev,long baud){
	if(NULL != my_dc_changebaud_485){
		return my_dc_changebaud_485(icdev,baud);
	}
	return NULL;
}
__int16 D8Cap::dc_change_addr8(HANDLE icdev,unsigned char saddr){
	if(NULL != my_dc_change_addr){
		return my_dc_change_addr(icdev,saddr);
	}
	return NULL;
}
__int16 D8Cap::dc_pro_resethex8(HANDLE icdev,unsigned char *rlen, char *receive_data){
	if(NULL != my_dc_pro_resethex){
		return my_dc_pro_resethex(icdev,rlen,receive_data);
	}
	return NULL;
}
__int16 D8Cap::dc_pro_commandhex8(HANDLE idComDev,unsigned char slen,char * sendbuffer,unsigned char *rlen,char * databuffer,unsigned char timeout){
	if(NULL != my_dc_pro_commandhex){
		return my_dc_pro_commandhex(idComDev,slen,sendbuffer,rlen,databuffer,timeout);
	}
	return NULL;
}

__int16 D8Cap::dc_request_shc11028(HANDLE icdev,unsigned char _Mode,unsigned __int16 *TagType){
	if(NULL != my_dc_request_shc1102){
		return my_dc_request_shc1102(icdev,_Mode,TagType);
	}
	return NULL;
}
__int16 D8Cap::dc_auth_shc11028(HANDLE icdev,unsigned char *_Data){
	if(NULL != my_dc_auth_shc1102){
		return my_dc_auth_shc1102(icdev,_Data);
	}
	return NULL;
}
__int16 D8Cap::dc_read_shc11028(HANDLE icdev,unsigned char _Adr,unsigned char *_Data){
	if(NULL != my_dc_read_shc1102){
		return my_dc_read_shc1102(icdev,_Adr,_Data);
	}
	return NULL;
}
__int16 D8Cap::dc_write_shc11028(HANDLE icdev,unsigned char _Adr,unsigned char *_Data){
	if(NULL != my_dc_write_shc1102){
		return my_dc_write_shc1102(icdev,_Adr,_Data);
	}
	return NULL;
}
__int16 D8Cap::dc_halt_shc11028(HANDLE icdev){
	if(NULL != my_dc_halt_shc1102){
		return my_dc_halt_shc1102(icdev);
	}
	return NULL;
}
__int16 D8Cap::dc_config_card8(HANDLE icdev,unsigned char cardtype){
	if(NULL != my_dc_config_card){
		return my_dc_config_card(icdev,cardtype);
	}
	return NULL;
}
__int16 D8Cap::dc_request_b8(HANDLE icdev,unsigned char _Mode,unsigned char AFI,unsigned char N,unsigned char *ATQB){
	if(NULL != my_dc_request_b){
		return my_dc_request_b(icdev,_Mode,AFI,N,ATQB);
	}
	return NULL;
}
__int16 D8Cap::dc_slotmarker8(HANDLE icdev,unsigned char N, unsigned char *ATQB){
	if(NULL != my_dc_slotmarker){
		return my_dc_slotmarker(icdev,N,ATQB);
	}
	return NULL;
}
__int16 D8Cap::dc_attrib8(HANDLE icdev,unsigned char *PUPI, unsigned char CID){
	if(NULL != my_dc_attrib){
		return my_dc_attrib(icdev,PUPI,CID);
	}
	return NULL;
}
__int16 D8Cap::dc_open_door8(HANDLE icdev,unsigned char cflag){
	if(NULL != my_dc_open_door){
		return my_dc_open_door(icdev,cflag);
	}
	return NULL;
}
__int16 D8Cap::dc_open_timedoor8(HANDLE icdev,unsigned __int16 utime){
	if(NULL != my_dc_open_timedoor){
		return my_dc_open_timedoor(icdev,utime);
	}
	return NULL;
}
__int16 D8Cap::dc_read_random8(HANDLE icdev, unsigned char *data){
	if(NULL != my_dc_read_random){
		return my_dc_read_random(icdev,data);
	}
	return NULL;
}
__int16 D8Cap::dc_write_random8(HANDLE icdev,__int16 len, unsigned char *data){
	if(NULL != my_dc_write_random){
		return my_dc_write_random(icdev,len,data);
	}
	return NULL;
}
__int16 D8Cap::dc_read_random_hex8(HANDLE icdev, unsigned char *data){
	if(NULL != my_dc_read_random_hex){
		return my_dc_read_random_hex(icdev,data);
	}
	return NULL;
}
__int16 D8Cap::dc_write_random_hex8(HANDLE icdev,__int16 len, unsigned char *data){
	if(NULL != my_dc_write_random_hex){
		return my_dc_write_random_hex(icdev,len,data);
	}
	return NULL;
}
__int16 D8Cap::dc_erase_random8(HANDLE icdev,__int16 len){
	if(NULL != my_dc_erase_random){
		return my_dc_erase_random(icdev,len);
	}
	return NULL;
}
__int16 D8Cap::dc_mfdes_auth8(HANDLE icdev,unsigned char keyno,unsigned char keylen,unsigned char *authkey,unsigned char *randAdata,unsigned char *randBdata){
	if(NULL != my_dc_mfdes_auth){
		return my_dc_mfdes_auth(icdev,keyno,keylen,authkey,randAdata,randBdata);
	}
	return NULL;
}
__int16 D8Cap::dc_disp_neg8(HANDLE icdev,char *dispstr){
	if(NULL != my_dc_disp_neg){
		return my_dc_disp_neg(icdev,dispstr);
	}
	return NULL;
}
__int16 D8Cap::dc_pro_commandlink8(HANDLE idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer,unsigned char timeout,unsigned char FG){
	if(NULL != my_dc_pro_commandlink){
		return my_dc_pro_commandlink(idComDev,slen,sendbuffer,rlen,databuffer,timeout,FG);
	}
	return NULL;
}
__int16 D8Cap::dc_pro_commandlink_hex8(HANDLE idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer,unsigned char timeout,unsigned char FG){
	if(NULL != my_dc_pro_commandlink_hex){
		return my_dc_pro_commandlink_hex(idComDev,slen,sendbuffer,rlen,databuffer,timeout,FG);
	}
	return NULL;
}
__int16 D8Cap::dc_read_idcard8(HANDLE icdev,unsigned char times,unsigned char *_Data){
	if(NULL != my_dc_read_idcard){
		return my_dc_read_idcard(icdev,times,_Data);
	}
	return NULL;
}
__int16 D8Cap::dc_read_idcard_hex8(HANDLE icdev,unsigned char times,unsigned char *_Data){
	if(NULL != my_dc_read_idcard_hex){
		return my_dc_read_idcard_hex(icdev,times,_Data);
	}
	return NULL;
}
__int16 D8Cap::dc_command8(HANDLE idComDev,unsigned char cmd,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer){
	if(NULL != my_dc_command){
		return my_dc_command(idComDev,cmd,slen,sendbuffer,rlen,databuffer);
	}
	return NULL;
}
__int16 D8Cap::dc_command_hex8(HANDLE idComDev,unsigned char cmd,unsigned char slen,char * sendbuffer,unsigned char *rlen,char * databuffer){
	if(NULL != my_dc_command_hex){
		return my_dc_command_hex(idComDev,cmd,slen,sendbuffer,rlen,databuffer);
	}
	return NULL;
}
__int16 D8Cap::dc_creat_mac8(unsigned char KeyLen,unsigned char *Key,unsigned short DataLen,unsigned char *Data,unsigned char *InitData,unsigned char AutoFixFlag,unsigned char FixChar,unsigned char *MacData){
	if(NULL != my_dc_creat_mac){
		return my_dc_creat_mac(KeyLen,Key,DataLen,Data,InitData,AutoFixFlag,FixChar,MacData);
	}
	return NULL;
}
__int16 D8Cap::dc_creat_mac_hex8(unsigned char KeyLen,unsigned char *Key,unsigned short DataLen,unsigned char *Data,unsigned char *InitData,unsigned char AutoFixFlag,unsigned char FixChar,unsigned char *MacData){
	if(NULL != my_dc_creat_mac_hex){
		return my_dc_creat_mac_hex(KeyLen,Key,DataLen,Data,InitData,AutoFixFlag,FixChar,MacData);
	}
	return NULL;
}
__int16 D8Cap::dc_HL_write_hex8(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,unsigned long *_Snr,unsigned char *_Data){
	if(NULL != my_dc_HL_write_hex){
		return my_dc_HL_write_hex(icdev,_Mode,_Adr,_Snr,_Data);
	}
	return NULL;
}
__int16 D8Cap::dc_HL_read_hex8(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,unsigned long _Snr,unsigned char *_Data,unsigned long *_NSnr){
	if(NULL != my_dc_HL_read_hex){
		return my_dc_HL_read_hex(icdev,_Mode,_Adr,_Snr,_Data,_NSnr);
	}
	return NULL;
}
__int16 D8Cap::dc_check_write_hex8(HANDLE icdev,unsigned long Snr,unsigned char authmode,unsigned char Adr,unsigned char * _data){
	if(NULL != my_dc_check_write_hex){
		return my_dc_check_write_hex(icdev,Snr,authmode,Adr,_data);
	}
	return NULL;
}
__int16 D8Cap::dc_srd_eeprom_hex8(HANDLE icdev,__int16   offset,__int16   lenth,unsigned char *rec_buffer){
	if(NULL != my_dc_srd_eeprom_hex){
		return my_dc_srd_eeprom_hex(icdev,offset,lenth,rec_buffer);
	}
	return NULL;
}
__int16 D8Cap::dc_swr_eeprom_hex8(HANDLE icdev,__int16   offset,__int16   lenth,unsigned char* send_buffer){
	if(NULL != my_dc_swr_eeprom_hex){
		return my_dc_swr_eeprom_hex(icdev,offset,lenth,send_buffer);
	}
	return NULL;
}
__int16 D8Cap::dc_gettime_hex8(HANDLE icdev,char *time){
	if(NULL != my_dc_gettime_hex){
		return my_dc_gettime_hex(icdev,time);
	}
	return NULL;
}
__int16 D8Cap::dc_settime_hex8(HANDLE icdev,char *time){
	if(NULL != my_dc_settime_hex){
		return my_dc_settime_hex(icdev,time);
	}
	return NULL;
}
__int16 D8Cap::dc_des8(unsigned char *key,unsigned char *sour,unsigned char *dest,__int16 m){
	if(NULL != my_dc_des){
		return my_dc_des(key,sour,dest,m);
	}
	return NULL;
}
__int16 D8Cap::dc_pro_reset_hex8(HANDLE icdev,unsigned char *rlen, char *receive_data){
	if(NULL != my_dc_pro_reset_hex){
		return my_dc_pro_reset_hex(icdev,rlen,receive_data);
	}
	return NULL;
}
__int16 D8Cap::dc_pro_command_hex8(HANDLE idComDev,unsigned char slen,char * sendbuffer,unsigned char *rlen,char * databuffer,unsigned char timeout){
	if(NULL != my_dc_pro_command_hex){
		return my_dc_pro_command_hex(idComDev,slen,sendbuffer,rlen,databuffer,timeout);
	}
	return NULL;
}
__int16 D8Cap::dc_pro_commandsource_hex8(HANDLE idComDev,unsigned char slen,char * sendbuffer,unsigned char *rlen,char * databuffer,unsigned char timeout){
	if(NULL != my_dc_pro_commandsource_hex){
		return my_dc_pro_commandsource_hex(idComDev,slen,sendbuffer,rlen,databuffer,timeout);
	}
	return NULL;
}
__int16 D8Cap::dc_switch_unix8(HANDLE icdev,long baud){
	if(NULL != my_dc_switch_unix){
		return my_dc_switch_unix(icdev,baud);
	}
	return NULL;
}
__int16 D8Cap::dc_authentication_passaddr8(HANDLE icdev,unsigned char _Mode,unsigned char _Addr,unsigned char *passbuff){
	if(NULL != my_dc_authentication_passaddr){
		return my_dc_authentication_passaddr(icdev,_Mode,_Addr,passbuff);
	}
	return NULL;
}
__int16 D8Cap::dc_authentication_passaddr_hex8(HANDLE icdev,unsigned char _Mode,unsigned char _Addr,unsigned char *passbuff){
	if(NULL != my_dc_authentication_passaddr_hex){
		return my_dc_authentication_passaddr_hex(icdev,_Mode,_Addr,passbuff);
	}
	return NULL;
}
__int16 D8Cap::dc_card_fm11rf0058(HANDLE icdev,unsigned char _Mode,unsigned long *_Snr){
	if(NULL != my_dc_card_fm11rf005){
		return my_dc_card_fm11rf005(icdev,_Mode,_Snr);
	}
	return NULL;
}
__int16 D8Cap::dc_setusbtimeout8(unsigned char ntimes){
	if(NULL != my_dc_setusbtimeout){
		return my_dc_setusbtimeout(ntimes);
	}
	return NULL;
}
__int16 D8Cap::dc_mfdes_baud8(HANDLE icdev,unsigned char _Mode,unsigned char para){
	if(NULL != my_dc_mfdes_baud){
		return my_dc_mfdes_baud(icdev,_Mode,para);
	}
	return NULL;
}
__int16 D8Cap::dc_tripledes8(unsigned char *key,unsigned char *src,unsigned char *dest,__int16 m){
	if(NULL != my_dc_tripledes){
		return my_dc_tripledes(key,src,dest,m);
	}
	return NULL;
}
__int16 D8Cap::dc_tripledes_hex8(unsigned char *key,unsigned char *src,unsigned char *dest,__int16 m){
	if(NULL != my_dc_tripledes_hex){
		return my_dc_tripledes_hex(key,src,dest,m);
	}
	return NULL;
}
__int16 D8Cap::dc_mfdes_auth_hex8(HANDLE icdev,unsigned char keyno,unsigned char keylen,unsigned char *authkey,unsigned char *randAdata,unsigned char *randBdata){
	if(NULL != my_dc_mfdes_auth_hex){
		return my_dc_mfdes_auth_hex(icdev,keyno,keylen,authkey,randAdata,randBdata);
	}
	return NULL;
}
__int16 D8Cap::dc_pro_sendcommandsource8(HANDLE idComDev,unsigned char slen,unsigned char * sendbuffer,unsigned char timeout){
	if(NULL != my_dc_pro_sendcommandsource){
		return my_dc_pro_sendcommandsource(idComDev,slen,sendbuffer,timeout);
	}
	return NULL;
}
__int16 D8Cap::dc_pro_receivecommandsource8(HANDLE idComDev,unsigned char *rlen,unsigned char * databuffer){
	if(NULL != my_dc_pro_receivecommandsource){
		return my_dc_pro_receivecommandsource(idComDev,rlen,databuffer);
	}
	return NULL;
}
__int16 D8Cap::dc_inventory8(HANDLE icdev,unsigned char flags,unsigned char AFI,unsigned char masklen,unsigned char *rlen,unsigned char *rbuffer){
	if(NULL != my_dc_inventory){
		return my_dc_inventory(icdev,flags,AFI,masklen,rlen,rbuffer);
	}
	return NULL;
}
__int16 D8Cap::dc_inventory_hex8(HANDLE icdev,unsigned char flags,unsigned char AFI,unsigned char masklen,unsigned char *rlen,unsigned char *rbuffer){
	if(NULL != my_dc_inventory_hex){
		return my_dc_inventory_hex(icdev,flags,AFI,masklen,rlen,rbuffer);
	}
	return NULL;
}
__int16 D8Cap::dc_stay_quiet8(HANDLE icdev,unsigned char flags,unsigned char *UID){
	if(NULL != my_dc_stay_quiet){
		return my_dc_stay_quiet(icdev,flags,UID);
	}
	return NULL;
}
__int16 D8Cap::dc_stay_quiet_hex8(HANDLE icdev,unsigned char flags,unsigned char *UID){
	if(NULL != my_dc_stay_quiet_hex){
		return my_dc_stay_quiet_hex(icdev,flags,UID);
	}
	return NULL;
}
__int16 D8Cap::dc_select_uid8(HANDLE icdev,unsigned char flags,unsigned char *UID){
	if(NULL != my_dc_select_uid){
		return my_dc_select_uid(icdev,flags,UID);
	}
	return NULL;
}
__int16 D8Cap::dc_select_uid_hex8(HANDLE icdev,unsigned char flags,unsigned char *UID){
	if(NULL != my_dc_select_uid_hex){
		return my_dc_select_uid_hex(icdev,flags,UID);
	}
	return NULL;
}
__int16 D8Cap::dc_reset_to_ready8(HANDLE icdev,unsigned char flags,unsigned char *UID){
	if(NULL != my_dc_reset_to_ready){
		return my_dc_reset_to_ready(icdev,flags,UID);
	}
	return NULL;
}
__int16 D8Cap::dc_reset_to_ready_hex8(HANDLE icdev,unsigned char flags,unsigned char *UID){
	if(NULL != my_dc_reset_to_ready_hex){
		return my_dc_reset_to_ready_hex(icdev,flags,UID);
	}
	return NULL;
}
__int16 D8Cap::dc_lock_block8(HANDLE icdev,unsigned char flags,unsigned char block,unsigned char *UID){
	if(NULL != my_dc_lock_block){
		return my_dc_lock_block(icdev,flags,block,UID);
	}
	return NULL;
}
__int16 D8Cap::dc_lock_block_hex8(HANDLE icdev,unsigned char flags,unsigned char block,unsigned char *UID){
	if(NULL != my_dc_lock_block_hex){
		return my_dc_lock_block_hex(icdev,flags,block,UID);
	}
	return NULL;
}
__int16 D8Cap::dc_write_afi8(HANDLE icdev,unsigned char flags,unsigned char AFI,unsigned char *UID){
	if(NULL != my_dc_write_afi){
		return my_dc_write_afi(icdev,flags,AFI,UID);
	}
	return NULL;
}
__int16 D8Cap::dc_write_afi_hex8(HANDLE icdev,unsigned char flags,unsigned char AFI,unsigned char *UID){
	if(NULL != my_dc_write_afi_hex){
		return my_dc_write_afi_hex(icdev,flags,AFI,UID);
	}
	return NULL;
}
__int16 D8Cap::dc_lock_afi8(HANDLE icdev,unsigned char flags,unsigned char AFI,unsigned char *UID){
	if(NULL != my_dc_lock_afi){
		return my_dc_lock_afi(icdev,flags,AFI,UID);
	}
	return NULL;
}
__int16 D8Cap::dc_lock_afi_hex8(HANDLE icdev,unsigned char flags,unsigned char AFI,unsigned char *UID){
	if(NULL != my_dc_lock_afi_hex){
		return my_dc_lock_afi_hex(icdev,flags,AFI,UID);
	}
	return NULL;
}
__int16 D8Cap::dc_write_dsfid8(HANDLE icdev,unsigned char flags,unsigned char DSFID,unsigned char *UID){
	if(NULL != my_dc_write_dsfid){
		return my_dc_write_dsfid(icdev,flags,DSFID,UID);
	}
	return NULL;
}
__int16 D8Cap::dc_write_dsfid_hex8(HANDLE icdev,unsigned char flags,unsigned char DSFID,unsigned char *UID){
	if(NULL != my_dc_write_dsfid_hex){
		return my_dc_write_dsfid_hex(icdev,flags,DSFID,UID);
	}
	return NULL;
}
__int16 D8Cap::dc_lock_dsfid8(HANDLE icdev,unsigned char flags,unsigned char DSFID,unsigned char *UID){
	if(NULL != my_dc_lock_dsfid){
		return my_dc_lock_dsfid(icdev,flags,DSFID,UID);
	}
	return NULL;
}
__int16 D8Cap::dc_lock_dsfid_hex8(HANDLE icdev,unsigned char flags,unsigned char DSFID,unsigned char *UID){
	if(NULL != my_dc_lock_dsfid_hex){
		return my_dc_lock_dsfid_hex(icdev,flags,DSFID,UID);
	}
	return NULL;
}
__int16 D8Cap::dc_get_systeminfo8(HANDLE icdev,unsigned char flags,unsigned char *UID,unsigned char *rlen,unsigned char *rbuffer){
	if(NULL != my_dc_get_systeminfo){
		return my_dc_get_systeminfo(icdev,flags,UID,rlen,rbuffer);
	}
	return NULL;
}
__int16 D8Cap::dc_get_systeminfo_hex8(HANDLE icdev,unsigned char flags,unsigned char *UID,unsigned char *rlen,unsigned char *rbuffer){
	if(NULL != my_dc_get_systeminfo_hex){
		return my_dc_get_systeminfo_hex(icdev,flags,UID,rlen,rbuffer);
	}
	return NULL;
}
__int16 D8Cap::dc_get_securityinfo8(HANDLE icdev,unsigned char flags,unsigned char startblock,unsigned char blocknum,unsigned char *UID,unsigned char *rlen,unsigned char *rbuffer){
	if(NULL != my_dc_get_securityinfo){
		return my_dc_get_securityinfo(icdev,flags,startblock,blocknum,UID,rlen,rbuffer);
	}
	return NULL;
}
__int16 D8Cap::dc_get_securityinfo_hex8(HANDLE icdev,unsigned char flags,unsigned char startblock,unsigned char blocknum,unsigned char *UID,unsigned char *rlen,unsigned char *rbuffer){
	if(NULL != my_dc_get_securityinfo_hex){
		return my_dc_get_securityinfo_hex(icdev,flags,startblock,blocknum,UID,rlen,rbuffer);
	}
	return NULL;
}
__int16 D8Cap::dc_getsnr_fm11rf0058(HANDLE icdev,unsigned long *_Snr){
	if(NULL != my_dc_getsnr_fm11rf005){
		return my_dc_getsnr_fm11rf005(icdev,_Snr);
	}
	return NULL;
}
__int16 D8Cap::dc_getsnr_fm11rf005_hex8(HANDLE icdev,unsigned char *snrstr){
	if(NULL != my_dc_getsnr_fm11rf005_hex){
		return my_dc_getsnr_fm11rf005_hex(icdev,snrstr);
	}
	return NULL;
}
__int16 D8Cap::dc_write_fm11rf0058(HANDLE icdev,unsigned char _Adr,unsigned char *_Data){
	if(NULL != my_dc_write_fm11rf005){
		return my_dc_write_fm11rf005(icdev,_Adr,_Data);
	}
	return NULL;
}
__int16 D8Cap::dc_read_fm11rf0058(HANDLE icdev,unsigned char _Adr,unsigned char *_Data){
	if(NULL != my_dc_read_fm11rf005){
		return my_dc_read_fm11rf005(icdev,_Adr,_Data);
	}
	return NULL;
}
__int16 D8Cap::dc_read_fm11rf005_hex8(HANDLE icdev,unsigned char _Adr,char *_Data){
	if(NULL != my_dc_read_fm11rf005_hex){
		return my_dc_read_fm11rf005_hex(icdev,_Adr,_Data);
	}
	return NULL;
}
__int16 D8Cap::dc_write_fm11rf005_hex8(HANDLE icdev,unsigned char _Adr,char *_Data){
	if(NULL != my_dc_write_fm11rf005_hex){
		return my_dc_write_fm11rf005_hex(icdev,_Adr,_Data);
	}
	return NULL;
}
__int16 D8Cap::DCDEV_CommandMcu8(HANDLE idComDev,unsigned char ctimeout,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer){
	if(NULL != my_DCDEV_CommandMcu){
		return my_DCDEV_CommandMcu(idComDev,ctimeout,slen,sendbuffer,rlen,databuffer);
	}
	return NULL;
}
__int16 D8Cap::DCDEV_CommandMcu_Hex8(HANDLE idComDev,unsigned char ctimeout,unsigned char slen,unsigned char * sendbuffer,unsigned char *rlen,unsigned char * databuffer){
	if(NULL != my_DCDEV_CommandMcu_Hex){
		return my_DCDEV_CommandMcu_Hex(idComDev,ctimeout,slen,sendbuffer,rlen,databuffer);
	}
	return NULL;
}
__int16 D8Cap::dc_displcd8(HANDLE idComDev,unsigned char flag){
	if(NULL != my_dc_displcd){
		return my_dc_displcd(idComDev,flag);
	}
	return NULL;
}
__int16 D8Cap::dc_getinputpass8(HANDLE idComDev,unsigned char ctime,unsigned char *rlen,unsigned char * cpass){
	if(NULL != my_dc_getinputpass){
		return my_dc_getinputpass(idComDev,ctime,rlen,cpass);
	}
	return NULL;
}
__int16 D8Cap::dc_readmagcard8(HANDLE idComDev, unsigned char ctime, unsigned char *pTrack2Data, unsigned long *pTrack2Len, unsigned char *pTrack3Data, unsigned long *pTrack3Len){
	if(NULL != my_dc_readmagcard){
		return my_dc_readmagcard(idComDev,ctime,pTrack2Data,pTrack2Len,pTrack3Data,pTrack3Len);
	}
	return NULL;
}
__int16 D8Cap::dc_testdevicecomm8(HANDLE idComDev){
	if(NULL != my_dc_testdevicecomm){
		return my_dc_testdevicecomm(idComDev);
	}
	return NULL;
}
__int16 D8Cap::dc_dispmainmenu8(HANDLE idComDev){
	if(NULL != my_dc_dispmainmenu){
		return my_dc_dispmainmenu(idComDev);
	}
	return NULL;
}
__int16 D8Cap::dc_setdevicetime8(HANDLE idComDev,unsigned char year,unsigned char month,unsigned char date,unsigned char hour,unsigned char minute,unsigned char second){
	if(NULL != my_dc_setdevicetime){
		return my_dc_setdevicetime(idComDev,year,month,date,hour,minute,second);
	}
	return NULL;
}
__int16 D8Cap::dc_getdevicetime8(HANDLE idComDev,unsigned char *year,unsigned char *month,unsigned char *date,unsigned char *hour,unsigned char *minute,unsigned char *second){
	if(NULL != my_dc_getdevicetime){
		return my_dc_getdevicetime(idComDev,year,month,date,hour,minute,second);
	}
	return NULL;
}
__int16 D8Cap::dc_dispinfo8(HANDLE idComDev,unsigned char line,unsigned char offset,char *data){
	if(NULL != my_dc_dispinfo){
		return my_dc_dispinfo(idComDev,line,offset,data);
	}
	return NULL;
}
__int16 D8Cap::dc_dispmaininfo8(HANDLE idComDev,unsigned char offset,char *data){
	if(NULL != my_dc_dispmaininfo){
		return my_dc_dispmaininfo(idComDev,offset,data);
	}
	return NULL;
}
__int16 D8Cap::dc_posbeep8(HANDLE idComDev,unsigned char beeptime){
	if(NULL != my_dc_posbeep){
		return my_dc_posbeep(idComDev,beeptime);
	}
	return NULL;
}
__int16 D8Cap::dc_ctlbacklight8(HANDLE idComDev, unsigned char cOpenFlag){
	if(NULL != my_dc_ctlbacklight){
		return my_dc_ctlbacklight(idComDev,cOpenFlag);
	}
	return NULL;
}
__int16 D8Cap::dc_ctlled8(HANDLE idComDev, unsigned char cLed, unsigned char cOpenFlag){
	if(NULL != my_dc_ctlled){
		return my_dc_ctlled(idComDev,cLed,cOpenFlag);
	}
	return NULL;
}
__int16 D8Cap::dc_lcdclrscrn8(HANDLE idComDev, unsigned char cLine){
	if(NULL != my_dc_lcdclrscrn){
		return my_dc_lcdclrscrn(idComDev,cLine);
	}
	return NULL;
}
__int16 D8Cap::dc_passin8(HANDLE idComDev,unsigned char ctime){
	if(NULL != my_dc_passin){
		return my_dc_passin(idComDev,ctime);
	}
	return NULL;
}
__int16 D8Cap::dc_passget8(HANDLE idComDev,unsigned char *rlen,unsigned char * cpass){
	if(NULL != my_dc_passget){
		return my_dc_passget(idComDev,rlen,cpass);
	}
	return NULL;
}
__int16 D8Cap::dc_passcancel8(HANDLE idComDev){
	if(NULL != my_dc_passcancel){
		return my_dc_passcancel(idComDev);
	}
	return NULL;
}
__int16 D8Cap::dc_getinputkey8(HANDLE idComDev,unsigned char disptype,unsigned char line,unsigned char ctime,unsigned char *rlen,unsigned char * ckeydata){
	if(NULL != my_dc_getinputkey){
		return my_dc_getinputkey(idComDev,disptype,line,ctime,rlen,ckeydata);
	}
	return NULL;
}
__int16 D8Cap::dc_displcd_ext8(HANDLE idComDev,unsigned char flag,unsigned char row,unsigned char offset){
	if(NULL != my_dc_displcd_ext){
		return my_dc_displcd_ext(idComDev,flag,row,offset);
	}
	return NULL;
}
__int16 D8Cap::dc_readmagcardall8(HANDLE idComDev, unsigned char ctime, unsigned char *pTrack1Data, unsigned long *pTrack1Len,unsigned char *pTrack2Data, unsigned long *pTrack2Len, unsigned char *pTrack3Data, unsigned long *pTrack3Len){
	if(NULL != my_dc_readmagcardall){
		return my_dc_readmagcardall(idComDev,ctime,pTrack1Data,pTrack1Len,pTrack2Data,pTrack2Len,pTrack3Data,pTrack3Len);
	}
	return NULL;
}
__int16 D8Cap::dc_readdevsnr8(HANDLE idComDev,unsigned char *snr){
	if(NULL != my_dc_readdevsnr){
		return my_dc_readdevsnr(idComDev,snr);
	}
	return NULL;
}
__int16 D8Cap::dc_readreadersnr8(HANDLE idComDev,unsigned char *snr){
	if(NULL != my_dc_readreadersnr){
		return my_dc_readreadersnr(idComDev,snr);
	}
	return NULL;
}
__int16 D8Cap::dc_resetdevice8(HANDLE idComDev){
	if(NULL != my_dc_resetdevice){
		return my_dc_resetdevice(idComDev);
	}
	return NULL;
}
__int16 D8Cap::dc_read_44428(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * buffer){
	if(NULL != my_dc_read_4442){
		return my_dc_read_4442(icdev,offset,lenth,buffer);
	}
	return NULL;
}
__int16 D8Cap::dc_read_4442_hex8(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char* buffer){
	if(NULL != my_dc_read_4442_hex){
		return my_dc_read_4442_hex(icdev,offset,lenth,buffer);
	}
	return NULL;
}
__int16 D8Cap::dc_write_44428(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * buffer){
	if(NULL != my_dc_write_4442){
		return my_dc_write_4442(icdev,offset,lenth,buffer);
	}
	return NULL;
}
__int16 D8Cap::dc_write_4442_hex8(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char* buffer){
	if(NULL != my_dc_write_4442_hex){
		return my_dc_write_4442_hex(icdev,offset,lenth,buffer);
	}
	return NULL;
}
__int16 D8Cap::dc_verifypin_44428(HANDLE icdev,unsigned char *passwd){
	if(NULL != my_dc_verifypin_4442){
		return my_dc_verifypin_4442(icdev,passwd);
	}
	return NULL;
}
__int16 D8Cap::dc_verifypin_4442_hex8(HANDLE icdev,unsigned char *passwd){
	if(NULL != my_dc_verifypin_4442_hex){
		return my_dc_verifypin_4442_hex(icdev,passwd);
	}
	return NULL;
}
__int16 D8Cap::dc_readpin_44428(HANDLE icdev,unsigned char *passwd){
	if(NULL != my_dc_readpin_4442){
		return my_dc_readpin_4442(icdev,passwd);
	}
	return NULL;
}
__int16 D8Cap::dc_readpin_4442_hex8(HANDLE icdev,unsigned char *passwd){
	if(NULL != my_dc_readpin_4442_hex){
		return my_dc_readpin_4442_hex(icdev,passwd);
	}
	return NULL;
}
__int16 D8Cap::dc_readpincount_44428(HANDLE icdev){
	if(NULL != my_dc_readpincount_4442){
		return my_dc_readpincount_4442(icdev);
	}
	return NULL;
}
__int16 D8Cap::dc_changepin_44428(HANDLE icdev,unsigned char *passwd){
	if(NULL != my_dc_changepin_4442){
		return my_dc_changepin_4442(icdev,passwd);
	}
	return NULL;
}
__int16 D8Cap::dc_changepin_4442_hex8(HANDLE icdev,unsigned char *passwd){
	if(NULL != my_dc_changepin_4442_hex){
		return my_dc_changepin_4442_hex(icdev,passwd);
	}
	return NULL;
}
__int16 D8Cap::dc_readwrotect_44428(HANDLE icdev,__int16 offset,__int16 leng,unsigned char *buffer){
	if(NULL != my_dc_readwrotect_4442){
		return my_dc_readwrotect_4442(icdev,offset,leng,buffer);
	}
	return NULL;
}
__int16 D8Cap::dc_readwrotect_4442_hex8(HANDLE icdev,__int16 offset,__int16 leng,unsigned char *buffer){
	if(NULL != my_dc_readwrotect_4442_hex){
		return my_dc_readwrotect_4442_hex(icdev,offset,leng,buffer);
	}
	return NULL;
}
__int16 D8Cap::dc_writeprotect_44428(HANDLE icdev,__int16 offset,__int16 leng,unsigned char *buffer){
	if(NULL != my_dc_writeprotect_4442){
		return my_dc_writeprotect_4442(icdev,offset,leng,buffer);
	}
	return NULL;
}
__int16 D8Cap::dc_writeprotect_4442_hex8(HANDLE icdev,__int16 offset,__int16 leng,unsigned char *buffer){
	if(NULL != my_dc_writeprotect_4442_hex){
		return my_dc_writeprotect_4442_hex(icdev,offset,leng,buffer);
	}
	return NULL;
}
__int16 D8Cap::dc_write_24c8(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * snd_buffer){
	if(NULL != my_dc_write_24c){
		return my_dc_write_24c(icdev,offset,lenth,snd_buffer);
	}
	return NULL;
}
__int16 D8Cap::dc_write_24c_hex8(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * snd_buffer){
	if(NULL != my_dc_write_24c_hex){
		return my_dc_write_24c_hex(icdev,offset,lenth,snd_buffer);
	}
	return NULL;
}
__int16 D8Cap::dc_write_24c648(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * snd_buffer){
	if(NULL != my_dc_write_24c64){
		return my_dc_write_24c64(icdev,offset,lenth,snd_buffer);
	}
	return NULL;
}
__int16 D8Cap::dc_write_24c64_hex8(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * snd_buffer){
	if(NULL != my_dc_write_24c64_hex){
		return my_dc_write_24c64_hex(icdev,offset,lenth,snd_buffer);
	}
	return NULL;
}
__int16 D8Cap::dc_read_24c8(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * receive_buffer){
	if(NULL != my_dc_read_24c){
		return my_dc_read_24c(icdev,offset,lenth,receive_buffer);
	}
	return NULL;
}
__int16 D8Cap::dc_read_24c_hex8(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * receive_buffer){
	if(NULL != my_dc_read_24c_hex){
		return my_dc_read_24c_hex(icdev,offset,lenth,receive_buffer);
	}
	return NULL;
}
__int16 D8Cap::dc_read_24c648(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * receive_buffer){
	if(NULL != my_dc_read_24c64){
		return my_dc_read_24c64(icdev,offset,lenth,receive_buffer);
	}
	return NULL;
}
__int16 D8Cap::dc_read_24c64_hex8(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * receive_buffer){
	if(NULL != my_dc_read_24c64_hex){
		return my_dc_read_24c64_hex(icdev,offset,lenth,receive_buffer);
	}
	return NULL;
}
__int16 D8Cap::dc_read_44288(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * buffer){
	if(NULL != my_dc_read_4428){
		return my_dc_read_4428(icdev,offset,lenth,buffer);
	}
	return NULL;
}
__int16 D8Cap::dc_read_4428_hex8(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char* buffer){
	if(NULL != my_dc_read_4428_hex){
		return my_dc_read_4428_hex(icdev,offset,lenth,buffer);
	}
	return NULL;
}
__int16 D8Cap::dc_write_44288(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char * buffer){
	if(NULL != my_dc_write_4428){
		return my_dc_write_4428(icdev,offset,lenth,buffer);
	}
	return NULL;
}
__int16 D8Cap::dc_write_4428_hex8(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char* buffer){
	if(NULL != my_dc_write_4428_hex){
		return my_dc_write_4428_hex(icdev,offset,lenth,buffer);
	}
	return NULL;
}
__int16 D8Cap::dc_verifypin_44288(HANDLE icdev,unsigned char *passwd){
	if(NULL != my_dc_verifypin_4428){
		return my_dc_verifypin_4428(icdev,passwd);
	}
	return NULL;
}
__int16 D8Cap::dc_verifypin_4428_hex8(HANDLE icdev,unsigned char *passwd){
	if(NULL != my_dc_verifypin_4428_hex){
		return my_dc_verifypin_4428_hex(icdev,passwd);
	}
	return NULL;
}
__int16 D8Cap::dc_readpin_44288(HANDLE icdev,unsigned char *passwd){
	if(NULL != my_dc_readpin_4428){
		return my_dc_readpin_4428(icdev,passwd);
	}
	return NULL;
}
__int16 D8Cap::dc_readpin_4428_hex8(HANDLE icdev,unsigned char *passwd){
	if(NULL != my_dc_readpin_4428_hex){
		return my_dc_readpin_4428_hex(icdev,passwd);
	}
	return NULL;
}
__int16 D8Cap::dc_readpincount_44288(HANDLE icdev){
	if(NULL != my_dc_readpincount_4428){
		return my_dc_readpincount_4428(icdev);
	}
	return NULL;
}
__int16 D8Cap::dc_changepin_44288(HANDLE icdev,unsigned char *passwd){
	if(NULL != my_dc_changepin_4428){
		return my_dc_changepin_4428(icdev,passwd);
	}
	return NULL;
}
__int16 D8Cap::dc_changepin_4428_hex8(HANDLE icdev,unsigned char *passwd){
	if(NULL != my_dc_changepin_4428_hex){
		return my_dc_changepin_4428_hex(icdev,passwd);
	}
	return NULL;
}
__int16 D8Cap::dc_Check_44428(HANDLE icdev){
	if(NULL != my_dc_Check_4442){
		return my_dc_Check_4442(icdev);
	}
	return NULL;
}
__int16 D8Cap::dc_Check_44288(HANDLE icdev){
	if(NULL != my_dc_Check_4428){
		return my_dc_Check_4428(icdev);
	}
	return NULL;
}
__int16 D8Cap::dc_Check_24C018(HANDLE icdev){
	if(NULL != my_dc_Check_24C01){
		return my_dc_Check_24C01(icdev);
	}
	return NULL;
}
__int16 D8Cap::dc_Check_24C028(HANDLE icdev){
	if(NULL != my_dc_Check_24C02){
		return my_dc_Check_24C02(icdev);
	}
	return NULL;
}
__int16 D8Cap::dc_Check_24C048(HANDLE icdev){
	if(NULL != my_dc_Check_24C04){
		return my_dc_Check_24C04(icdev);
	}
	return NULL;
}
__int16 D8Cap::dc_Check_24C088(HANDLE icdev){
	if(NULL != my_dc_Check_24C08){
		return my_dc_Check_24C08(icdev);
	}
	return NULL;
}
__int16 D8Cap::dc_Check_24C168(HANDLE icdev){
	if(NULL != my_dc_Check_24C16){
		return my_dc_Check_24C16(icdev);
	}
	return NULL;
}
__int16 D8Cap::dc_Check_24C648(HANDLE icdev){
	if(NULL != my_dc_Check_24C64){
		return my_dc_Check_24C64(icdev);
	}
	return NULL;
}
__int16 D8Cap::dc_Check_CPU8(HANDLE icdev){
	if(NULL != my_dc_Check_CPU){
		return my_dc_Check_CPU(icdev);
	}
	return NULL;
}
__int16 D8Cap::dc_CheckCard8(HANDLE icdev){
	if(NULL != my_dc_CheckCard){
		return my_dc_CheckCard(icdev);
	}
	return NULL;
}
__int16 D8Cap::dc_getrcinfo8(HANDLE icdev,unsigned char *info){
	if(NULL != my_dc_getrcinfo){
		return my_dc_getrcinfo(icdev,info);
	}
	return NULL;
}
__int16 D8Cap::dc_getrcinfo_hex8(HANDLE icdev,unsigned char *info){
	if(NULL != my_dc_getrcinfo_hex){
		return my_dc_getrcinfo_hex(icdev,info);
	}
	return NULL;
}
__int16 D8Cap::dc_getlongver8(HANDLE icdev,unsigned char *sver){
	if(NULL != my_dc_getlongver){
		return my_dc_getlongver(icdev,sver);
	}
	return NULL;
}
__int16 D8Cap::dc_cardstr8(HANDLE icdev,unsigned char _Mode,char * Strsnr){
	if(NULL != my_dc_cardstr){
		return my_dc_cardstr(icdev,_Mode,Strsnr);
	}
	return NULL;
}
__int16 D8Cap::dc_card_b8(HANDLE icdev,unsigned char *rbuf){
	if(NULL != my_dc_card_b){
		return my_dc_card_b(icdev,rbuf);
	}
	return NULL;
}
__int16 D8Cap::dc_card_b_hex8(HANDLE icdev,char *rbuf){
	if(NULL != my_dc_card_b_hex){
		return my_dc_card_b_hex(icdev,rbuf);
	}
	return NULL;
}
__int16 D8Cap::dc_dispinfo_T88(HANDLE idComDev,unsigned char line,unsigned char offset,char *data){
	if(NULL != my_dc_dispinfo_T8){
		return my_dc_dispinfo_T8(idComDev,line,offset,data);
	}
	return NULL;
}
__int16 D8Cap::dc_dispinfo_pro_T88(HANDLE idComDev,unsigned char offset,char *data){
	if(NULL != my_dc_dispinfo_pro_T8){
		return my_dc_dispinfo_pro_T8(idComDev,offset,data);
	}
	return NULL;
}
__int16 D8Cap::dc_clearlcd_T88(HANDLE icdev,unsigned char line){
	if(NULL != my_dc_clearlcd_T8){
		return my_dc_clearlcd_T8(icdev,line);
	}
	return NULL;
}
__int16 D8Cap::dc_led_T88(HANDLE icdev,unsigned char cled,unsigned char cflag){
	if(NULL != my_dc_led_T8){
		return my_dc_led_T8(icdev,cled,cflag);
	}
	return NULL;
}
__int16 D8Cap::dc_MFPL0_writeperso8(HANDLE icdev,unsigned int BNr,unsigned char * dataperso){
	if(NULL != my_dc_MFPL0_writeperso){
		return my_dc_MFPL0_writeperso(icdev,BNr,dataperso);
	}
	return NULL;
}
__int16 D8Cap::dc_MFPL0_writeperso_hex8(HANDLE icdev,unsigned int BNr,unsigned char * dataperso){
	if(NULL != my_dc_MFPL0_writeperso_hex){
		return my_dc_MFPL0_writeperso_hex(icdev,BNr,dataperso);
	}
	return NULL;
}
__int16 D8Cap::dc_MFPL0_commitperso8(HANDLE icdev){
	if(NULL != my_dc_MFPL0_commitperso){
		return my_dc_MFPL0_commitperso(icdev);
	}
	return NULL;
}
__int16 D8Cap::dc_MFPL1_authl1key8(HANDLE icdev,unsigned char *authkey){
	if(NULL != my_dc_MFPL1_authl1key){
		return my_dc_MFPL1_authl1key(icdev,authkey);
	}
	return NULL;
}
__int16 D8Cap::dc_MFPL1_authl1key_hex8(HANDLE icdev,unsigned char *authkey){
	if(NULL != my_dc_MFPL1_authl1key_hex){
		return my_dc_MFPL1_authl1key_hex(icdev,authkey);
	}
	return NULL;
}
__int16 D8Cap::dc_MFPL1_switchtol28(HANDLE icdev,unsigned char *authkey){
	if(NULL != my_dc_MFPL1_switchtol2){
		return my_dc_MFPL1_switchtol2(icdev,authkey);
	}
	return NULL;
}
__int16 D8Cap::dc_MFPL1_switchtol38(HANDLE icdev,unsigned char *authkey){
	if(NULL != my_dc_MFPL1_switchtol3){
		return my_dc_MFPL1_switchtol3(icdev,authkey);
	}
	return NULL;
}
__int16 D8Cap::dc_MFPL2_switchtol38(HANDLE icdev,unsigned char *authkey){
	if(NULL != my_dc_MFPL2_switchtol3){
		return my_dc_MFPL2_switchtol3(icdev,authkey);
	}
	return NULL;
}
__int16 D8Cap::dc_MFPL3_authl3key8(HANDLE icdev,unsigned int keyBNr,unsigned char *authkey){
	if(NULL != my_dc_MFPL3_authl3key){
		return my_dc_MFPL3_authl3key(icdev,keyBNr,authkey);
	}
	return NULL;
}
__int16 D8Cap::dc_MFPL3_authl3key_hex8(HANDLE icdev,unsigned int keyBNr,unsigned char *authkey){
	if(NULL != my_dc_MFPL3_authl3key_hex){
		return my_dc_MFPL3_authl3key_hex(icdev,keyBNr,authkey);
	}
	return NULL;
}
__int16 D8Cap::dc_MFPL3_authl3sectorkey8(HANDLE icdev,unsigned char mode,unsigned int sectorBNr,unsigned char *authkey){
	if(NULL != my_dc_MFPL3_authl3sectorkey){
		return my_dc_MFPL3_authl3sectorkey(icdev,mode,sectorBNr,authkey);
	}
	return NULL;
}
__int16 D8Cap::dc_MFPL3_authl3sectorkey_hex8(HANDLE icdev,unsigned char mode,unsigned int sectorBNr,unsigned char *authkey){
	if(NULL != my_dc_MFPL3_authl3sectorkey_hex){
		return my_dc_MFPL3_authl3sectorkey_hex(icdev,mode,sectorBNr,authkey);
	}
	return NULL;
}
__int16 D8Cap::dc_MFPL3_readinplain8(HANDLE icdev,unsigned int BNr,unsigned char Numblock, unsigned char *readdata){
	if(NULL != my_dc_MFPL3_readinplain){
		return my_dc_MFPL3_readinplain(icdev,BNr,Numblock,readdata);
	}
	return NULL;
}
__int16 D8Cap::dc_MFPL3_readinplain_hex8(HANDLE icdev,unsigned int BNr,unsigned char Numblock, unsigned char *readdata){
	if(NULL != my_dc_MFPL3_readinplain_hex){
		return my_dc_MFPL3_readinplain_hex(icdev,BNr,Numblock,readdata);
	}
	return NULL;
}
__int16 D8Cap::dc_MFPL3_readencrypted8(HANDLE icdev,unsigned int BNr,unsigned char Numblock, unsigned char *readdata, unsigned char flag){
	if(NULL != my_dc_MFPL3_readencrypted){
		return my_dc_MFPL3_readencrypted(icdev,BNr,Numblock,readdata,flag);
	}
	return NULL;
}
__int16 D8Cap::dc_MFPL3_readencrypted_hex8(HANDLE icdev,unsigned int BNr,unsigned char Numblock, unsigned char *readdata, unsigned char flag){
	if(NULL != my_dc_MFPL3_readencrypted_hex){
		return my_dc_MFPL3_readencrypted_hex(icdev,BNr,Numblock,readdata,flag);
	}
	return NULL;
}
__int16 D8Cap::dc_MFPL3_writeinplain8(HANDLE icdev,unsigned int BNr,unsigned char Numblock,unsigned char *writedata){
	if(NULL != my_dc_MFPL3_writeinplain){
		return my_dc_MFPL3_writeinplain(icdev,BNr,Numblock,writedata);
	}
	return NULL;
}
__int16 D8Cap::dc_MFPL3_writeinplain_hex8(HANDLE icdev,unsigned int BNr,unsigned char Numblock,unsigned char *writedata){
	if(NULL != my_dc_MFPL3_writeinplain_hex){
		return my_dc_MFPL3_writeinplain_hex(icdev,BNr,Numblock,writedata);
	}
	return NULL;
}
__int16 D8Cap::dc_MFPL3_writeencrypted8(HANDLE icdev,unsigned int BNr,unsigned char Numblock,unsigned char *writedata, unsigned char flag){
	if(NULL != my_dc_MFPL3_writeencrypted){
		return my_dc_MFPL3_writeencrypted(icdev,BNr,Numblock,writedata,flag);
	}
	return NULL;
}
__int16 D8Cap::dc_MFPL3_writeencrypted_hex8(HANDLE icdev,unsigned int BNr,unsigned char Numblock,unsigned char *writedata, unsigned char flag){
	if(NULL != my_dc_MFPL3_writeencrypted_hex){
		return my_dc_MFPL3_writeencrypted_hex(icdev,BNr,Numblock,writedata,flag);
	}
	return NULL;
}
__int16 D8Cap::dc_auth_ulc8(HANDLE icdev, unsigned char * key){
	if(NULL != my_dc_auth_ulc){
		return my_dc_auth_ulc(icdev,key);
	}
	return NULL;
}
__int16 D8Cap::dc_auth_ulc_hex8(HANDLE icdev, unsigned char * key){
	if(NULL != my_dc_auth_ulc_hex){
		return my_dc_auth_ulc_hex(icdev,key);
	}
	return NULL;
}
__int16 D8Cap::dc_changekey_ulc8(HANDLE icdev,unsigned char *newkey){
	if(NULL != my_dc_changekey_ulc){
		return my_dc_changekey_ulc(icdev,newkey);
	}
	return NULL;
}
__int16 D8Cap::dc_changekey_ulc_hex8(HANDLE icdev,unsigned char *newkey){
	if(NULL != my_dc_changekey_ulc_hex){
		return my_dc_changekey_ulc_hex(icdev,newkey);
	}
	return NULL;
}
__int16 D8Cap::dc_pro_commandlinkEXT_hex8(HANDLE idComDev,unsigned int slen,unsigned char * sendbuffer,unsigned int *rlen,unsigned char * databuffer,unsigned char timeout,unsigned char FG){
	if(NULL != my_dc_pro_commandlinkEXT_hex){
		return my_dc_pro_commandlinkEXT_hex(idComDev,slen,sendbuffer,rlen,databuffer,timeout,FG);
	}
	return NULL;
}
/***********************************自动生成代码***added by chch 20110703****************************/
/***********************************自动生成代码***added by chch 20110703****************************/




void D8Cap::Initial(int port)
{
	hinstLib = NULL;
	initDll(port);
	if(hinstLib != NULL){
		//初始化
		
		//基本函数
		 my_dc_init = NULL;
		 my_dc_card = NULL;
		 my_dc_load_key = NULL;
		 my_dc_authentication = NULL;
		 my_dc_authentication2 = NULL;
		 my_dc_read = NULL;
		 my_dc_write = NULL;
		 my_dc_beep = NULL;
		 my_dc_exit = NULL;
		 my_dc_request = NULL;
		 my_dc_select = NULL;
		 my_dc_anticoll = NULL;
		 my_dc_authentication_pass = NULL;
		 my_dc_halt = NULL;
		 my_dc_changeb3 = NULL;
		 my_dc_HL_authentication = NULL;
		 my_dc_check_write = NULL;
		 my_dc_HL_read = NULL;
		 my_dc_HL_write = NULL;
		 my_dc_des_hex = NULL;

		//带Hex函数
		 my_dc_card_hex = NULL;
		 my_dc_load_key_hex = NULL;
		 my_dc_authentication_path_hex = NULL;
		 my_dc_read_hex = NULL;
		 my_dc_write_hex = NULL;
		 my_dc_srd_eepromhex = NULL;
		 my_dc_swr_eepromhex = NULL;
		 my_dc_cpuapdu_hex = NULL;
		 my_dc_cpureset_hex = NULL;

		//值操作
		 my_dc_initval = NULL;
		 my_dc_readval = NULL;
		 my_dc_increment = NULL;
		 my_dc_decrement = NULL;
		 my_dc_restore = NULL;

		  my_dc_swreeprom = NULL;
		 my_a_hex = NULL;
		 my_hex_a = NULL;
		 my_dc_reset = NULL;
		 my_dc__cpuapdu = NULL;
		 my_dc_cpuapdusource = NULL;
		 my_dc_cpureset = NULL;
		 my_dc_Setcpu = NULL;
		 my_dc_Setcpupara = NULL;


		 my_dc_transfer = NULL;
		//myDc_Beep my_dc_beep;
		 my_dc_srd_eeprom = NULL;
		 my_dc_getver = NULL;


		//RFMA专用
		 my_dc_gettime = NULL;
		 my_dc_disp_mode = NULL;
		 my_dc_high_disp = NULL;
		 my_dc_setbright = NULL;
		 my_dc_disp_str = NULL;
		 my_dc_settime = NULL;

		 //NEW ADD BY ZXB 091116
		my_dc_getcpupara = NULL;
		my_dc_cpuapdusourceEXT = NULL;
		my_dc_cpuapdusourceEXT_hex = NULL;
		my_dc_cpuapduEXT = NULL;
		my_dc_cpuapduEXT_hex = NULL;

		my_dc_pro_commandlinkEXT = NULL;

		my_dc_pro_reset=NULL;
		my_dc_pro_command=NULL;

		my_dc_pro_halt=NULL;
		my_dc_config=NULL;

		my_dc_card_double=NULL;
		my_dc_card_double_hex=NULL;

		my_dc_gettimehex=NULL;
		my_dc_settimehex=NULL;

		//added on 20110627
		my_dc_readblock = NULL;
		my_dc_readblock_hex = NULL;
		my_dc_writeblock= NULL;
		my_dc_writeblock_hex = NULL;
        my_dc_cardAB=NULL;
		//added on 20110627


		my_dc_pro_commandsource= NULL;
		my_dc_pro_commandsourcehex= NULL;
		my_dc_cpudown=NULL;
		/***********************************自动生成代码***added by chch 20110703****************************/
/***********************************自动生成代码***added by chch 20110703****************************/
my_dc_config = NULL;
my_dc_write_TS = NULL;
my_dc_initval_ml = NULL;
my_dc_readval_ml = NULL;
my_dc_authentication_2 = NULL;
my_dc_anticoll2 = NULL;
my_dc_select2 = NULL;
my_dc_HL_writehex = NULL;
my_dc_HL_readhex = NULL;
my_dc_check_writehex = NULL;
my_dc_clr_control_bit = NULL;
my_dc_set_control_bit = NULL;
my_dc_swr_eeprom = NULL;
my_swr_alleeprom = NULL;
my_srd_alleeprom = NULL;
my_dc_ctl_mode = NULL;
my_dcdeshex = NULL;
my_dcdes = NULL;
my_dc_light = NULL;
my_dc_setcpu = NULL;
my_dc_cpuapdu = NULL;
my_dc_cpuapdusource_hex = NULL;
my_dc_cpuapdurespon = NULL;
my_dc_cpuapdurespon_hex = NULL;
my_dc_set_addr = NULL;
my_dc_init_485 = NULL;
my_dc_changebaud_485 = NULL;
my_dc_change_addr = NULL;
my_dc_pro_resethex = NULL;
my_dc_pro_commandhex = NULL;
my_dc_pro_halt = NULL;
my_dc_request_shc1102 = NULL;
my_dc_auth_shc1102 = NULL;
my_dc_read_shc1102 = NULL;
my_dc_write_shc1102 = NULL;
my_dc_halt_shc1102 = NULL;
my_dc_config_card = NULL;
my_dc_request_b = NULL;
my_dc_slotmarker = NULL;
my_dc_attrib = NULL;
my_dc_open_door = NULL;
my_dc_open_timedoor = NULL;
my_dc_read_random = NULL;
my_dc_write_random = NULL;
my_dc_read_random_hex = NULL;
my_dc_write_random_hex = NULL;
my_dc_erase_random = NULL;
my_dc_mfdes_auth = NULL;
my_dc_disp_neg = NULL;
my_dc_pro_commandlink = NULL;
my_dc_pro_commandlink_hex = NULL;
my_dc_read_idcard = NULL;
my_dc_read_idcard_hex = NULL;
my_dc_authentication_pass_hex = NULL;
my_dc_setcpupara = NULL;
my_dc_command = NULL;
my_dc_command_hex = NULL;
my_dc_creat_mac = NULL;
my_dc_creat_mac_hex = NULL;
my_dc_HL_write_hex = NULL;
my_dc_HL_read_hex = NULL;
my_dc_check_write_hex = NULL;
my_dc_srd_eeprom_hex = NULL;
my_dc_swr_eeprom_hex = NULL;
my_dc_gettime_hex = NULL;
my_dc_settime_hex = NULL;
my_dc_des = NULL;
my_dc_pro_reset_hex = NULL;
my_dc_pro_command_hex = NULL;
my_dc_pro_commandsource_hex = NULL;
my_dc_switch_unix = NULL;
my_dc_authentication_passaddr = NULL;
my_dc_authentication_passaddr_hex = NULL;
my_dc_card_fm11rf005 = NULL;
my_dc_setusbtimeout = NULL;
my_dc_mfdes_baud = NULL;
my_dc_tripledes = NULL;
my_dc_tripledes_hex = NULL;
my_dc_mfdes_auth_hex = NULL;
my_dc_pro_sendcommandsource = NULL;
my_dc_pro_receivecommandsource = NULL;
my_dc_inventory = NULL;
my_dc_inventory_hex = NULL;
my_dc_stay_quiet = NULL;
my_dc_stay_quiet_hex = NULL;
my_dc_select_uid = NULL;
my_dc_select_uid_hex = NULL;
my_dc_reset_to_ready = NULL;
my_dc_reset_to_ready_hex = NULL;
my_dc_lock_block = NULL;
my_dc_lock_block_hex = NULL;
my_dc_write_afi = NULL;
my_dc_write_afi_hex = NULL;
my_dc_lock_afi = NULL;
my_dc_lock_afi_hex = NULL;
my_dc_write_dsfid = NULL;
my_dc_write_dsfid_hex = NULL;
my_dc_lock_dsfid = NULL;
my_dc_lock_dsfid_hex = NULL;
my_dc_get_systeminfo = NULL;
my_dc_get_systeminfo_hex = NULL;
my_dc_get_securityinfo = NULL;
my_dc_get_securityinfo_hex = NULL;
my_dc_getsnr_fm11rf005 = NULL;
my_dc_getsnr_fm11rf005_hex = NULL;
my_dc_write_fm11rf005 = NULL;
my_dc_read_fm11rf005 = NULL;
my_dc_read_fm11rf005_hex = NULL;
my_dc_write_fm11rf005_hex = NULL;
my_DCDEV_CommandMcu = NULL;
my_DCDEV_CommandMcu_Hex = NULL;
my_dc_displcd = NULL;
my_dc_getinputpass = NULL;
my_dc_readmagcard = NULL;
my_dc_testdevicecomm = NULL;
my_dc_dispmainmenu = NULL;
my_dc_setdevicetime = NULL;
my_dc_getdevicetime = NULL;
my_dc_dispinfo = NULL;
my_dc_dispmaininfo = NULL;
my_dc_posbeep = NULL;
my_dc_ctlbacklight = NULL;
my_dc_ctlled = NULL;
my_dc_lcdclrscrn = NULL;
my_dc_passin = NULL;
my_dc_passget = NULL;
my_dc_passcancel = NULL;
my_dc_getinputkey = NULL;
my_dc_displcd_ext = NULL;
my_dc_readmagcardall = NULL;
my_dc_readdevsnr = NULL;
my_dc_readreadersnr = NULL;
my_dc_resetdevice = NULL;
my_dc_read_4442 = NULL;
my_dc_read_4442_hex = NULL;
my_dc_write_4442 = NULL;
my_dc_write_4442_hex = NULL;
my_dc_verifypin_4442 = NULL;
my_dc_verifypin_4442_hex = NULL;
my_dc_readpin_4442 = NULL;
my_dc_readpin_4442_hex = NULL;
my_dc_readpincount_4442 = NULL;
my_dc_changepin_4442 = NULL;
my_dc_changepin_4442_hex = NULL;
my_dc_readwrotect_4442 = NULL;
my_dc_readwrotect_4442_hex = NULL;
my_dc_writeprotect_4442 = NULL;
my_dc_writeprotect_4442_hex = NULL;
my_dc_write_24c = NULL;
my_dc_write_24c_hex = NULL;
my_dc_write_24c64 = NULL;
my_dc_write_24c64_hex = NULL;
my_dc_read_24c = NULL;
my_dc_read_24c_hex = NULL;
my_dc_read_24c64 = NULL;
my_dc_read_24c64_hex = NULL;
my_dc_read_4428 = NULL;
my_dc_read_4428_hex = NULL;
my_dc_write_4428 = NULL;
my_dc_write_4428_hex = NULL;
my_dc_verifypin_4428 = NULL;
my_dc_verifypin_4428_hex = NULL;
my_dc_readpin_4428 = NULL;
my_dc_readpin_4428_hex = NULL;
my_dc_readpincount_4428 = NULL;
my_dc_changepin_4428 = NULL;
my_dc_changepin_4428_hex = NULL;
my_dc_Check_4442 = NULL;
my_dc_Check_4428 = NULL;
my_dc_Check_24C01 = NULL;
my_dc_Check_24C02 = NULL;
my_dc_Check_24C04 = NULL;
my_dc_Check_24C08 = NULL;
my_dc_Check_24C16 = NULL;
my_dc_Check_24C64 = NULL;
my_dc_Check_CPU = NULL;
my_dc_CheckCard = NULL;
my_dc_getrcinfo = NULL;
my_dc_getrcinfo_hex = NULL;
my_dc_getlongver = NULL;
my_dc_cardstr = NULL;
my_dc_card_b = NULL;
my_dc_card_b_hex = NULL;
my_dc_dispinfo_T8 = NULL;
my_dc_dispinfo_pro_T8 = NULL;
my_dc_clearlcd_T8 = NULL;
my_dc_led_T8 = NULL;
my_dc_MFPL0_writeperso = NULL;
my_dc_MFPL0_writeperso_hex = NULL;
my_dc_MFPL0_commitperso = NULL;
my_dc_MFPL1_authl1key = NULL;
my_dc_MFPL1_authl1key_hex = NULL;
my_dc_MFPL1_switchtol2 = NULL;
my_dc_MFPL1_switchtol3 = NULL;
my_dc_MFPL2_switchtol3 = NULL;
my_dc_MFPL3_authl3key = NULL;
my_dc_MFPL3_authl3key_hex = NULL;
my_dc_MFPL3_authl3sectorkey = NULL;
my_dc_MFPL3_authl3sectorkey_hex = NULL;
my_dc_MFPL3_readinplain = NULL;
my_dc_MFPL3_readinplain_hex = NULL;
my_dc_MFPL3_readencrypted = NULL;
my_dc_MFPL3_readencrypted_hex = NULL;
my_dc_MFPL3_writeinplain = NULL;
my_dc_MFPL3_writeinplain_hex = NULL;
my_dc_MFPL3_writeencrypted = NULL;
my_dc_MFPL3_writeencrypted_hex = NULL;
my_dc_auth_ulc = NULL;
my_dc_auth_ulc_hex = NULL;
my_dc_changekey_ulc = NULL;
my_dc_changekey_ulc_hex = NULL;
my_dc_pro_commandlinkEXT_hex = NULL;
/***********************************自动生成代码***added by chch 20110703****************************/
/***********************************自动生成代码***added by chch 20110703****************************/


		//基本函数
		my_dc_card = (myDcCard)GetProcAddress(hinstLib, "dc_card");
		my_dc_init = (myDcInit)GetProcAddress(hinstLib, "dc_init");
		my_dc_load_key = (myDcLoadKey)GetProcAddress(hinstLib,"dc_load_key");
		my_dc_authentication = (myDcAuth)GetProcAddress(hinstLib,"dc_authentication");
		my_dc_authentication2 = (myDcAuth2)GetProcAddress(hinstLib, "dc_authentication2");
		my_dc_read = (myDcRead)GetProcAddress(hinstLib, "dc_read");
		my_dc_write = (myDcWrite)GetProcAddress(hinstLib, "dc_write");
		my_dc_beep = (myDcBeep)GetProcAddress(hinstLib, "dc_beep");
		my_dc_exit = (myDcExit)GetProcAddress(hinstLib,"dc_exit");
		my_dc_request = (myDcRequest)GetProcAddress(hinstLib, "dc_request");
		my_dc_select = (myDcSelect)GetProcAddress(hinstLib, "dc_select");
		my_dc_anticoll = (myDcAnticoll)GetProcAddress(hinstLib,"dc_anticoll");
		my_dc_authentication_pass = (myDcAuthPass)GetProcAddress(hinstLib,"dc_authentication_pass");
		my_dc_halt = (myDcHalt)GetProcAddress(hinstLib,"dc_halt");
		my_dc_changeb3 = (myDcChangeb3)GetProcAddress(hinstLib, "dc_changeb3");
		my_dc_HL_authentication = (myDcHLAuthentication)GetProcAddress(hinstLib,"dc_HL_authentication");
		my_dc_check_write = (myDcCheckWrite)GetProcAddress(hinstLib, "dc_check_write");
		my_dc_HL_read = (myDcHLRead)GetProcAddress(hinstLib,"dc_HL_read");
		my_dc_HL_write = (myDcHLWrite)GetProcAddress(hinstLib, "dc_HL_write");
		my_dc_des_hex = (myDcDesHex)GetProcAddress(hinstLib,"dc_des_hex");

		//带Hex函数
		my_dc_card_hex = (myDcCardHex)GetProcAddress(hinstLib, "dc_card_hex");
		my_dc_load_key_hex = (myDcLoadKeyHex)GetProcAddress(hinstLib, "dc_load_key_hex");
		my_dc_authentication_path_hex = (myDcAuthenticationPathHex)GetProcAddress(hinstLib, "dc_authentication_path_hex");
		my_dc_read_hex =(myDcReadHex)GetProcAddress(hinstLib,"dc_read_hex");
		my_dc_write_hex = (myDcWriteHex)GetProcAddress(hinstLib,"dc_write_hex");
		my_dc_srd_eepromhex = (myDcSrdEepromHex)GetProcAddress(hinstLib,"dc_srd_eepromhex");
		my_dc_swr_eepromhex = (myDcSwrEepromHex)GetProcAddress(hinstLib,"dc_swr_eepromhex");
		my_dc_cpuapdu_hex = (myDcCpuapduHex)GetProcAddress(hinstLib, "dc_cpuapdu_hex");
		my_dc_cpureset_hex = (myDcCpuresetHex)GetProcAddress(hinstLib, "dc_cpureset_hex");
		
		//值操作
		my_dc_initval = (myDcInitval)GetProcAddress(hinstLib,"dc_initval");
		my_dc_readval = (myDcReadVal)GetProcAddress(hinstLib,"dc_readval");
		my_dc_increment = (myDcIncrement)GetProcAddress(hinstLib,"dc_increment");
		my_dc_decrement = (myDcDecrement)GetProcAddress(hinstLib, "dc_decrement");
		my_dc_restore = (myDcRestore)GetProcAddress(hinstLib,"dc_restore");

		my_dc_swreeprom = (myDcSwrEeprom)GetProcAddress(hinstLib, "dc_swr_eeprom");

		my_a_hex = (myA_hex)GetProcAddress(hinstLib, "a_hex");

		my_hex_a = (myHex_a)GetProcAddress(hinstLib, "hex_a");
		my_dc_reset = (myDc_Reset)GetProcAddress(hinstLib, "dc_reset");	

		my_dc__cpuapdu = (myDc_Cpuapdu)GetProcAddress(hinstLib, "dc_cpuapdu");	

		my_dc_cpuapdusource = (myDc_Cpuapdusource)GetProcAddress(hinstLib, "dc_cpuapdusource");	

		my_dc_cpureset = (myDc_Cpureset)GetProcAddress(hinstLib, "dc_cpureset");	

		my_dc_Setcpu = (myDc_Setcpu)GetProcAddress(hinstLib, "dc_setcpu");	

		my_dc_Setcpupara = (myDc_Setcpupara)GetProcAddress(hinstLib, "dc_setcpupara");



		my_dc_srd_eeprom = (myDc_Srd_eeprom)GetProcAddress(hinstLib, "dc_srd_eeprom");

		my_dc_getver = (myDc_Getver)GetProcAddress(hinstLib, "dc_getver");

		my_dc_beep = (myDc_Beep)GetProcAddress(hinstLib, "dc_beep");
		my_dc_transfer = (myDc_Transfer)GetProcAddress(hinstLib, "dc_transfer");

		//RFMA专用
		my_dc_gettime = (myDcGettime)GetProcAddress(hinstLib, "dc_gettime");
		my_dc_high_disp = (myDcHighDisp)GetProcAddress(hinstLib,"dc_high_disp");
		my_dc_disp_mode = (myDcDispMode)GetProcAddress(hinstLib, "dc_disp_mode");
		my_dc_setbright = (myDcSetBright)GetProcAddress(hinstLib, "dc_dc_setbright");
		my_dc_disp_str = (myDcDispStr)GetProcAddress(hinstLib,"dc_disp_str");
		my_dc_settime = (myDcSettime)GetProcAddress(hinstLib, "dc_settime");

		//NEW ADD BY ZXB 091116
		my_dc_getcpupara = (myDcGetcpupara)GetProcAddress(hinstLib,"dc_getcpupara");
		my_dc_cpuapdusourceEXT = (myDcCpuApduSourceExt)GetProcAddress(hinstLib,"dc_cpuapdusourceEXT");
		my_dc_cpuapdusourceEXT_hex = (myDcCpuApduSourceExtHex)GetProcAddress(hinstLib,"dc_cpuapdusourceEXT_hex");
		my_dc_cpuapduEXT = (myDcCpuApduExt)GetProcAddress(hinstLib,"dc_cpuapduEXT");
		my_dc_cpuapduEXT_hex = (myDcCpuApduExtHex)GetProcAddress(hinstLib,"dc_cpuapduEXT_hex");
		my_dc_pro_commandlinkEXT = (myDcProCommandLinkExt)GetProcAddress(hinstLib,"dc_pro_commandlinkEXT");
		my_dc_pro_reset=(myDCProReset)GetProcAddress(hinstLib,"dc_pro_reset");
		my_dc_pro_command=(myDCProCommand)GetProcAddress(hinstLib,"dc_pro_command");


		my_dc_pro_halt=(myDCProHalt)GetProcAddress(hinstLib,"dc_pro_halt");
		my_dc_config  =  (myDCConfig)GetProcAddress(hinstLib,"dc_config");



		my_dc_card_double=(myDCCardDouble)GetProcAddress(hinstLib,"dc_card_double");
		my_dc_card_double_hex=(myDCCardDoubleHex)GetProcAddress(hinstLib,"dc_card_double_hex");


		my_dc_gettimehex=(myDCGettimehex)GetProcAddress(hinstLib,"dc_gettimehex");
		my_dc_settimehex=(myDCSettimehex)GetProcAddress(hinstLib,"dc_settimehex");

		//added on 20110627
		my_dc_readblock = (myDcReadblock)GetProcAddress(hinstLib, "dc_readblock");
		my_dc_readblock_hex = (myDcReadblockHex)GetProcAddress(hinstLib, "dc_readblock_hex");
		my_dc_writeblock= (myDcWriteblock)GetProcAddress(hinstLib, "dc_writeblock");
		my_dc_writeblock_hex = (myDcWriteblockHex)GetProcAddress(hinstLib, "dc_writeblock_hex");
        my_dc_cardAB=(myDcCardAB)GetProcAddress(hinstLib, "dc_cardAB");
		//added on 20110627

		my_dc_pro_commandsource=(myDCProCommandsource)GetProcAddress(hinstLib,"dc_pro_commandsource");
        my_dc_pro_commandsourcehex=(myDCProCommandsourceHex)GetProcAddress(hinstLib,"dc_pro_commandsourcehex");
		my_dc_cpudown=(myDCCpudown)GetProcAddress(hinstLib,"dc_cpudown");
		/***********************************自动生成代码***added by chch 20110703****************************/

/***********************************自动生成代码***added by chch 20110703****************************/
my_dc_config = (func_type_dc_config)GetProcAddress(hinstLib, "dc_config");
my_dc_write_TS = (func_type_dc_write_TS)GetProcAddress(hinstLib, "dc_write_TS");
my_dc_initval_ml = (func_type_dc_initval_ml)GetProcAddress(hinstLib, "dc_initval_ml");
my_dc_readval_ml = (func_type_dc_readval_ml)GetProcAddress(hinstLib, "dc_readval_ml");
my_dc_authentication_2 = (func_type_dc_authentication_2)GetProcAddress(hinstLib, "dc_authentication_2");
my_dc_anticoll2 = (func_type_dc_anticoll2)GetProcAddress(hinstLib, "dc_anticoll2");
my_dc_select2 = (func_type_dc_select2)GetProcAddress(hinstLib, "dc_select2");
my_dc_HL_writehex = (func_type_dc_HL_writehex)GetProcAddress(hinstLib, "dc_HL_writehex");
my_dc_HL_readhex = (func_type_dc_HL_readhex)GetProcAddress(hinstLib, "dc_HL_readhex");
my_dc_check_writehex = (func_type_dc_check_writehex)GetProcAddress(hinstLib, "dc_check_writehex");
my_dc_clr_control_bit = (func_type_dc_clr_control_bit)GetProcAddress(hinstLib, "dc_clr_control_bit");
my_dc_set_control_bit = (func_type_dc_set_control_bit)GetProcAddress(hinstLib, "dc_set_control_bit");
my_dc_swr_eeprom = (func_type_dc_swr_eeprom)GetProcAddress(hinstLib, "dc_swr_eeprom");
my_swr_alleeprom = (func_type_swr_alleeprom)GetProcAddress(hinstLib, "swr_alleeprom");
my_srd_alleeprom = (func_type_srd_alleeprom)GetProcAddress(hinstLib, "srd_alleeprom");
my_dc_ctl_mode = (func_type_dc_ctl_mode)GetProcAddress(hinstLib, "dc_ctl_mode");
my_dcdeshex = (func_type_dcdeshex)GetProcAddress(hinstLib, "dcdeshex");
my_dcdes = (func_type_dcdes)GetProcAddress(hinstLib, "dcdes");
my_dc_light = (func_type_dc_light)GetProcAddress(hinstLib, "dc_light");
my_dc_setcpu = (func_type_dc_setcpu)GetProcAddress(hinstLib, "dc_setcpu");
my_dc_cpuapdu = (func_type_dc_cpuapdu)GetProcAddress(hinstLib, "dc_cpuapdu");
my_dc_cpuapdusource_hex = (func_type_dc_cpuapdusource_hex)GetProcAddress(hinstLib, "dc_cpuapdusource_hex");
my_dc_cpuapdurespon = (func_type_dc_cpuapdurespon)GetProcAddress(hinstLib, "dc_cpuapdurespon");
my_dc_cpuapdurespon_hex = (func_type_dc_cpuapdurespon_hex)GetProcAddress(hinstLib, "dc_cpuapdurespon_hex");
my_dc_set_addr = (func_type_dc_set_addr)GetProcAddress(hinstLib, "dc_set_addr");
my_dc_init_485 = (func_type_dc_init_485)GetProcAddress(hinstLib, "dc_init_485");
my_dc_changebaud_485 = (func_type_dc_changebaud_485)GetProcAddress(hinstLib, "dc_changebaud_485");
my_dc_change_addr = (func_type_dc_change_addr)GetProcAddress(hinstLib, "dc_change_addr");
my_dc_pro_resethex = (func_type_dc_pro_resethex)GetProcAddress(hinstLib, "dc_pro_resethex");
my_dc_pro_commandhex = (func_type_dc_pro_commandhex)GetProcAddress(hinstLib, "dc_pro_commandhex");
my_dc_pro_halt = (func_type_dc_pro_halt)GetProcAddress(hinstLib, "dc_pro_halt");
my_dc_request_shc1102 = (func_type_dc_request_shc1102)GetProcAddress(hinstLib, "dc_request_shc1102");
my_dc_auth_shc1102 = (func_type_dc_auth_shc1102)GetProcAddress(hinstLib, "dc_auth_shc1102");
my_dc_read_shc1102 = (func_type_dc_read_shc1102)GetProcAddress(hinstLib, "dc_read_shc1102");
my_dc_write_shc1102 = (func_type_dc_write_shc1102)GetProcAddress(hinstLib, "dc_write_shc1102");
my_dc_halt_shc1102 = (func_type_dc_halt_shc1102)GetProcAddress(hinstLib, "dc_halt_shc1102");
my_dc_config_card = (func_type_dc_config_card)GetProcAddress(hinstLib, "dc_config_card");
my_dc_request_b = (func_type_dc_request_b)GetProcAddress(hinstLib, "dc_request_b");
my_dc_slotmarker = (func_type_dc_slotmarker)GetProcAddress(hinstLib, "dc_slotmarker");
my_dc_attrib = (func_type_dc_attrib)GetProcAddress(hinstLib, "dc_attrib");
my_dc_open_door = (func_type_dc_open_door)GetProcAddress(hinstLib, "dc_open_door");
my_dc_open_timedoor = (func_type_dc_open_timedoor)GetProcAddress(hinstLib, "dc_open_timedoor");
my_dc_read_random = (func_type_dc_read_random)GetProcAddress(hinstLib, "dc_read_random");
my_dc_write_random = (func_type_dc_write_random)GetProcAddress(hinstLib, "dc_write_random");
my_dc_read_random_hex = (func_type_dc_read_random_hex)GetProcAddress(hinstLib, "dc_read_random_hex");
my_dc_write_random_hex = (func_type_dc_write_random_hex)GetProcAddress(hinstLib, "dc_write_random_hex");
my_dc_erase_random = (func_type_dc_erase_random)GetProcAddress(hinstLib, "dc_erase_random");
my_dc_mfdes_auth = (func_type_dc_mfdes_auth)GetProcAddress(hinstLib, "dc_mfdes_auth");
my_dc_disp_neg = (func_type_dc_disp_neg)GetProcAddress(hinstLib, "dc_disp_neg");
my_dc_pro_commandlink = (func_type_dc_pro_commandlink)GetProcAddress(hinstLib, "dc_pro_commandlink");
my_dc_pro_commandlink_hex = (func_type_dc_pro_commandlink_hex)GetProcAddress(hinstLib, "dc_pro_commandlink_hex");
my_dc_read_idcard = (func_type_dc_read_idcard)GetProcAddress(hinstLib, "dc_read_idcard");
my_dc_read_idcard_hex = (func_type_dc_read_idcard_hex)GetProcAddress(hinstLib, "dc_read_idcard_hex");
my_dc_authentication_pass_hex = (func_type_dc_authentication_pass_hex)GetProcAddress(hinstLib, "dc_authentication_pass_hex");
my_dc_setcpupara = (func_type_dc_setcpupara)GetProcAddress(hinstLib, "dc_setcpupara");
my_dc_command = (func_type_dc_command)GetProcAddress(hinstLib, "dc_command");
my_dc_command_hex = (func_type_dc_command_hex)GetProcAddress(hinstLib, "dc_command_hex");
my_dc_creat_mac = (func_type_dc_creat_mac)GetProcAddress(hinstLib, "dc_creat_mac");
my_dc_creat_mac_hex = (func_type_dc_creat_mac_hex)GetProcAddress(hinstLib, "dc_creat_mac_hex");
my_dc_HL_write_hex = (func_type_dc_HL_write_hex)GetProcAddress(hinstLib, "dc_HL_write_hex");
my_dc_HL_read_hex = (func_type_dc_HL_read_hex)GetProcAddress(hinstLib, "dc_HL_read_hex");
my_dc_check_write_hex = (func_type_dc_check_write_hex)GetProcAddress(hinstLib, "dc_check_write_hex");
my_dc_srd_eeprom_hex = (func_type_dc_srd_eeprom_hex)GetProcAddress(hinstLib, "dc_srd_eeprom_hex");
my_dc_swr_eeprom_hex = (func_type_dc_swr_eeprom_hex)GetProcAddress(hinstLib, "dc_swr_eeprom_hex");
my_dc_gettime_hex = (func_type_dc_gettime_hex)GetProcAddress(hinstLib, "dc_gettime_hex");
my_dc_settime_hex = (func_type_dc_settime_hex)GetProcAddress(hinstLib, "dc_settime_hex");
my_dc_des = (func_type_dc_des)GetProcAddress(hinstLib, "dc_des");
my_dc_pro_reset_hex = (func_type_dc_pro_reset_hex)GetProcAddress(hinstLib, "dc_pro_reset_hex");
my_dc_pro_command_hex = (func_type_dc_pro_command_hex)GetProcAddress(hinstLib, "dc_pro_command_hex");
my_dc_pro_commandsource_hex = (func_type_dc_pro_commandsource_hex)GetProcAddress(hinstLib, "dc_pro_commandsource_hex");
my_dc_switch_unix = (func_type_dc_switch_unix)GetProcAddress(hinstLib, "dc_switch_unix");
my_dc_authentication_passaddr = (func_type_dc_authentication_passaddr)GetProcAddress(hinstLib, "dc_authentication_passaddr");
my_dc_authentication_passaddr_hex = (func_type_dc_authentication_passaddr_hex)GetProcAddress(hinstLib, "dc_authentication_passaddr_hex");
my_dc_card_fm11rf005 = (func_type_dc_card_fm11rf005)GetProcAddress(hinstLib, "dc_card_fm11rf005");
my_dc_setusbtimeout = (func_type_dc_setusbtimeout)GetProcAddress(hinstLib, "dc_setusbtimeout");
my_dc_mfdes_baud = (func_type_dc_mfdes_baud)GetProcAddress(hinstLib, "dc_mfdes_baud");
my_dc_tripledes = (func_type_dc_tripledes)GetProcAddress(hinstLib, "dc_tripledes");
my_dc_tripledes_hex = (func_type_dc_tripledes_hex)GetProcAddress(hinstLib, "dc_tripledes_hex");
my_dc_mfdes_auth_hex = (func_type_dc_mfdes_auth_hex)GetProcAddress(hinstLib, "dc_mfdes_auth_hex");
my_dc_pro_sendcommandsource = (func_type_dc_pro_sendcommandsource)GetProcAddress(hinstLib, "dc_pro_sendcommandsource");
my_dc_pro_receivecommandsource = (func_type_dc_pro_receivecommandsource)GetProcAddress(hinstLib, "dc_pro_receivecommandsource");
my_dc_inventory = (func_type_dc_inventory)GetProcAddress(hinstLib, "dc_inventory");
my_dc_inventory_hex = (func_type_dc_inventory_hex)GetProcAddress(hinstLib, "dc_inventory_hex");
my_dc_stay_quiet = (func_type_dc_stay_quiet)GetProcAddress(hinstLib, "dc_stay_quiet");
my_dc_stay_quiet_hex = (func_type_dc_stay_quiet_hex)GetProcAddress(hinstLib, "dc_stay_quiet_hex");
my_dc_select_uid = (func_type_dc_select_uid)GetProcAddress(hinstLib, "dc_select_uid");
my_dc_select_uid_hex = (func_type_dc_select_uid_hex)GetProcAddress(hinstLib, "dc_select_uid_hex");
my_dc_reset_to_ready = (func_type_dc_reset_to_ready)GetProcAddress(hinstLib, "dc_reset_to_ready");
my_dc_reset_to_ready_hex = (func_type_dc_reset_to_ready_hex)GetProcAddress(hinstLib, "dc_reset_to_ready_hex");
my_dc_lock_block = (func_type_dc_lock_block)GetProcAddress(hinstLib, "dc_lock_block");
my_dc_lock_block_hex = (func_type_dc_lock_block_hex)GetProcAddress(hinstLib, "dc_lock_block_hex");
my_dc_write_afi = (func_type_dc_write_afi)GetProcAddress(hinstLib, "dc_write_afi");
my_dc_write_afi_hex = (func_type_dc_write_afi_hex)GetProcAddress(hinstLib, "dc_write_afi_hex");
my_dc_lock_afi = (func_type_dc_lock_afi)GetProcAddress(hinstLib, "dc_lock_afi");
my_dc_lock_afi_hex = (func_type_dc_lock_afi_hex)GetProcAddress(hinstLib, "dc_lock_afi_hex");
my_dc_write_dsfid = (func_type_dc_write_dsfid)GetProcAddress(hinstLib, "dc_write_dsfid");
my_dc_write_dsfid_hex = (func_type_dc_write_dsfid_hex)GetProcAddress(hinstLib, "dc_write_dsfid_hex");
my_dc_lock_dsfid = (func_type_dc_lock_dsfid)GetProcAddress(hinstLib, "dc_lock_dsfid");
my_dc_lock_dsfid_hex = (func_type_dc_lock_dsfid_hex)GetProcAddress(hinstLib, "dc_lock_dsfid_hex");
my_dc_get_systeminfo = (func_type_dc_get_systeminfo)GetProcAddress(hinstLib, "dc_get_systeminfo");
my_dc_get_systeminfo_hex = (func_type_dc_get_systeminfo_hex)GetProcAddress(hinstLib, "dc_get_systeminfo_hex");
my_dc_get_securityinfo = (func_type_dc_get_securityinfo)GetProcAddress(hinstLib, "dc_get_securityinfo");
my_dc_get_securityinfo_hex = (func_type_dc_get_securityinfo_hex)GetProcAddress(hinstLib, "dc_get_securityinfo_hex");
my_dc_getsnr_fm11rf005 = (func_type_dc_getsnr_fm11rf005)GetProcAddress(hinstLib, "dc_getsnr_fm11rf005");
my_dc_getsnr_fm11rf005_hex = (func_type_dc_getsnr_fm11rf005_hex)GetProcAddress(hinstLib, "dc_getsnr_fm11rf005_hex");
my_dc_write_fm11rf005 = (func_type_dc_write_fm11rf005)GetProcAddress(hinstLib, "dc_write_fm11rf005");
my_dc_read_fm11rf005 = (func_type_dc_read_fm11rf005)GetProcAddress(hinstLib, "dc_read_fm11rf005");
my_dc_read_fm11rf005_hex = (func_type_dc_read_fm11rf005_hex)GetProcAddress(hinstLib, "dc_read_fm11rf005_hex");
my_dc_write_fm11rf005_hex = (func_type_dc_write_fm11rf005_hex)GetProcAddress(hinstLib, "dc_write_fm11rf005_hex");
my_DCDEV_CommandMcu = (func_type_DCDEV_CommandMcu)GetProcAddress(hinstLib, "DCDEV_CommandMcu");
my_DCDEV_CommandMcu_Hex = (func_type_DCDEV_CommandMcu_Hex)GetProcAddress(hinstLib, "DCDEV_CommandMcu_Hex");
my_dc_displcd = (func_type_dc_displcd)GetProcAddress(hinstLib, "dc_displcd");
my_dc_getinputpass = (func_type_dc_getinputpass)GetProcAddress(hinstLib, "dc_getinputpass");
my_dc_readmagcard = (func_type_dc_readmagcard)GetProcAddress(hinstLib, "dc_readmagcard");
my_dc_testdevicecomm = (func_type_dc_testdevicecomm)GetProcAddress(hinstLib, "dc_testdevicecomm");
my_dc_dispmainmenu = (func_type_dc_dispmainmenu)GetProcAddress(hinstLib, "dc_dispmainmenu");
my_dc_setdevicetime = (func_type_dc_setdevicetime)GetProcAddress(hinstLib, "dc_setdevicetime");
my_dc_getdevicetime = (func_type_dc_getdevicetime)GetProcAddress(hinstLib, "dc_getdevicetime");
my_dc_dispinfo = (func_type_dc_dispinfo)GetProcAddress(hinstLib, "dc_dispinfo");
my_dc_dispmaininfo = (func_type_dc_dispmaininfo)GetProcAddress(hinstLib, "dc_dispmaininfo");
my_dc_posbeep = (func_type_dc_posbeep)GetProcAddress(hinstLib, "dc_posbeep");
my_dc_ctlbacklight = (func_type_dc_ctlbacklight)GetProcAddress(hinstLib, "dc_ctlbacklight");
my_dc_ctlled = (func_type_dc_ctlled)GetProcAddress(hinstLib, "dc_ctlled");
my_dc_lcdclrscrn = (func_type_dc_lcdclrscrn)GetProcAddress(hinstLib, "dc_lcdclrscrn");
my_dc_passin = (func_type_dc_passin)GetProcAddress(hinstLib, "dc_passin");
my_dc_passget = (func_type_dc_passget)GetProcAddress(hinstLib, "dc_passget");
my_dc_passcancel = (func_type_dc_passcancel)GetProcAddress(hinstLib, "dc_passcancel");
my_dc_getinputkey = (func_type_dc_getinputkey)GetProcAddress(hinstLib, "dc_getinputkey");
my_dc_displcd_ext = (func_type_dc_displcd_ext)GetProcAddress(hinstLib, "dc_displcd_ext");
my_dc_readmagcardall = (func_type_dc_readmagcardall)GetProcAddress(hinstLib, "dc_readmagcardall");
my_dc_readdevsnr = (func_type_dc_readdevsnr)GetProcAddress(hinstLib, "dc_readdevsnr");
my_dc_readreadersnr = (func_type_dc_readreadersnr)GetProcAddress(hinstLib, "dc_readreadersnr");
my_dc_resetdevice = (func_type_dc_resetdevice)GetProcAddress(hinstLib, "dc_resetdevice");
my_dc_read_4442 = (func_type_dc_read_4442)GetProcAddress(hinstLib, "dc_read_4442");
my_dc_read_4442_hex = (func_type_dc_read_4442_hex)GetProcAddress(hinstLib, "dc_read_4442_hex");
my_dc_write_4442 = (func_type_dc_write_4442)GetProcAddress(hinstLib, "dc_write_4442");
my_dc_write_4442_hex = (func_type_dc_write_4442_hex)GetProcAddress(hinstLib, "dc_write_4442_hex");
my_dc_verifypin_4442 = (func_type_dc_verifypin_4442)GetProcAddress(hinstLib, "dc_verifypin_4442");
my_dc_verifypin_4442_hex = (func_type_dc_verifypin_4442_hex)GetProcAddress(hinstLib, "dc_verifypin_4442_hex");
my_dc_readpin_4442 = (func_type_dc_readpin_4442)GetProcAddress(hinstLib, "dc_readpin_4442");
my_dc_readpin_4442_hex = (func_type_dc_readpin_4442_hex)GetProcAddress(hinstLib, "dc_readpin_4442_hex");
my_dc_readpincount_4442 = (func_type_dc_readpincount_4442)GetProcAddress(hinstLib, "dc_readpincount_4442");
my_dc_changepin_4442 = (func_type_dc_changepin_4442)GetProcAddress(hinstLib, "dc_changepin_4442");
my_dc_changepin_4442_hex = (func_type_dc_changepin_4442_hex)GetProcAddress(hinstLib, "dc_changepin_4442_hex");
my_dc_readwrotect_4442 = (func_type_dc_readwrotect_4442)GetProcAddress(hinstLib, "dc_readwrotect_4442");
my_dc_readwrotect_4442_hex = (func_type_dc_readwrotect_4442_hex)GetProcAddress(hinstLib, "dc_readwrotect_4442_hex");
my_dc_writeprotect_4442 = (func_type_dc_writeprotect_4442)GetProcAddress(hinstLib, "dc_writeprotect_4442");
my_dc_writeprotect_4442_hex = (func_type_dc_writeprotect_4442_hex)GetProcAddress(hinstLib, "dc_writeprotect_4442_hex");
my_dc_write_24c = (func_type_dc_write_24c)GetProcAddress(hinstLib, "dc_write_24c");
my_dc_write_24c_hex = (func_type_dc_write_24c_hex)GetProcAddress(hinstLib, "dc_write_24c_hex");
my_dc_write_24c64 = (func_type_dc_write_24c64)GetProcAddress(hinstLib, "dc_write_24c64");
my_dc_write_24c64_hex = (func_type_dc_write_24c64_hex)GetProcAddress(hinstLib, "dc_write_24c64_hex");
my_dc_read_24c = (func_type_dc_read_24c)GetProcAddress(hinstLib, "dc_read_24c");
my_dc_read_24c_hex = (func_type_dc_read_24c_hex)GetProcAddress(hinstLib, "dc_read_24c_hex");
my_dc_read_24c64 = (func_type_dc_read_24c64)GetProcAddress(hinstLib, "dc_read_24c64");
my_dc_read_24c64_hex = (func_type_dc_read_24c64_hex)GetProcAddress(hinstLib, "dc_read_24c64_hex");
my_dc_read_4428 = (func_type_dc_read_4428)GetProcAddress(hinstLib, "dc_read_4428");
my_dc_read_4428_hex = (func_type_dc_read_4428_hex)GetProcAddress(hinstLib, "dc_read_4428_hex");
my_dc_write_4428 = (func_type_dc_write_4428)GetProcAddress(hinstLib, "dc_write_4428");
my_dc_write_4428_hex = (func_type_dc_write_4428_hex)GetProcAddress(hinstLib, "dc_write_4428_hex");
my_dc_verifypin_4428 = (func_type_dc_verifypin_4428)GetProcAddress(hinstLib, "dc_verifypin_4428");
my_dc_verifypin_4428_hex = (func_type_dc_verifypin_4428_hex)GetProcAddress(hinstLib, "dc_verifypin_4428_hex");
my_dc_readpin_4428 = (func_type_dc_readpin_4428)GetProcAddress(hinstLib, "dc_readpin_4428");
my_dc_readpin_4428_hex = (func_type_dc_readpin_4428_hex)GetProcAddress(hinstLib, "dc_readpin_4428_hex");
my_dc_readpincount_4428 = (func_type_dc_readpincount_4428)GetProcAddress(hinstLib, "dc_readpincount_4428");
my_dc_changepin_4428 = (func_type_dc_changepin_4428)GetProcAddress(hinstLib, "dc_changepin_4428");
my_dc_changepin_4428_hex = (func_type_dc_changepin_4428_hex)GetProcAddress(hinstLib, "dc_changepin_4428_hex");
my_dc_Check_4442 = (func_type_dc_Check_4442)GetProcAddress(hinstLib, "dc_Check_4442");
my_dc_Check_4428 = (func_type_dc_Check_4428)GetProcAddress(hinstLib, "dc_Check_4428");
my_dc_Check_24C01 = (func_type_dc_Check_24C01)GetProcAddress(hinstLib, "dc_Check_24C01");
my_dc_Check_24C02 = (func_type_dc_Check_24C02)GetProcAddress(hinstLib, "dc_Check_24C02");
my_dc_Check_24C04 = (func_type_dc_Check_24C04)GetProcAddress(hinstLib, "dc_Check_24C04");
my_dc_Check_24C08 = (func_type_dc_Check_24C08)GetProcAddress(hinstLib, "dc_Check_24C08");
my_dc_Check_24C16 = (func_type_dc_Check_24C16)GetProcAddress(hinstLib, "dc_Check_24C16");
my_dc_Check_24C64 = (func_type_dc_Check_24C64)GetProcAddress(hinstLib, "dc_Check_24C64");
my_dc_Check_CPU = (func_type_dc_Check_CPU)GetProcAddress(hinstLib, "dc_Check_CPU");
my_dc_CheckCard = (func_type_dc_CheckCard)GetProcAddress(hinstLib, "dc_CheckCard");
my_dc_getrcinfo = (func_type_dc_getrcinfo)GetProcAddress(hinstLib, "dc_getrcinfo");
my_dc_getrcinfo_hex = (func_type_dc_getrcinfo_hex)GetProcAddress(hinstLib, "dc_getrcinfo_hex");
my_dc_getlongver = (func_type_dc_getlongver)GetProcAddress(hinstLib, "dc_getlongver");
my_dc_cardstr = (func_type_dc_cardstr)GetProcAddress(hinstLib, "dc_cardstr");
my_dc_card_b = (func_type_dc_card_b)GetProcAddress(hinstLib, "dc_card_b");
my_dc_card_b_hex = (func_type_dc_card_b_hex)GetProcAddress(hinstLib, "dc_card_b_hex");
my_dc_dispinfo_T8 = (func_type_dc_dispinfo_T8)GetProcAddress(hinstLib, "dc_dispinfo_T8");
my_dc_dispinfo_pro_T8 = (func_type_dc_dispinfo_pro_T8)GetProcAddress(hinstLib, "dc_dispinfo_pro_T8");
my_dc_clearlcd_T8 = (func_type_dc_clearlcd_T8)GetProcAddress(hinstLib, "dc_clearlcd_T8");
my_dc_led_T8 = (func_type_dc_led_T8)GetProcAddress(hinstLib, "dc_led_T8");
my_dc_MFPL0_writeperso = (func_type_dc_MFPL0_writeperso)GetProcAddress(hinstLib, "dc_MFPL0_writeperso");
my_dc_MFPL0_writeperso_hex = (func_type_dc_MFPL0_writeperso_hex)GetProcAddress(hinstLib, "dc_MFPL0_writeperso_hex");
my_dc_MFPL0_commitperso = (func_type_dc_MFPL0_commitperso)GetProcAddress(hinstLib, "dc_MFPL0_commitperso");
my_dc_MFPL1_authl1key = (func_type_dc_MFPL1_authl1key)GetProcAddress(hinstLib, "dc_MFPL1_authl1key");
my_dc_MFPL1_authl1key_hex = (func_type_dc_MFPL1_authl1key_hex)GetProcAddress(hinstLib, "dc_MFPL1_authl1key_hex");
my_dc_MFPL1_switchtol2 = (func_type_dc_MFPL1_switchtol2)GetProcAddress(hinstLib, "dc_MFPL1_switchtol2");
my_dc_MFPL1_switchtol3 = (func_type_dc_MFPL1_switchtol3)GetProcAddress(hinstLib, "dc_MFPL1_switchtol3");
my_dc_MFPL2_switchtol3 = (func_type_dc_MFPL2_switchtol3)GetProcAddress(hinstLib, "dc_MFPL2_switchtol3");
my_dc_MFPL3_authl3key = (func_type_dc_MFPL3_authl3key)GetProcAddress(hinstLib, "dc_MFPL3_authl3key");
my_dc_MFPL3_authl3key_hex = (func_type_dc_MFPL3_authl3key_hex)GetProcAddress(hinstLib, "dc_MFPL3_authl3key_hex");
my_dc_MFPL3_authl3sectorkey = (func_type_dc_MFPL3_authl3sectorkey)GetProcAddress(hinstLib, "dc_MFPL3_authl3sectorkey");
my_dc_MFPL3_authl3sectorkey_hex = (func_type_dc_MFPL3_authl3sectorkey_hex)GetProcAddress(hinstLib, "dc_MFPL3_authl3sectorkey_hex");
my_dc_MFPL3_readinplain = (func_type_dc_MFPL3_readinplain)GetProcAddress(hinstLib, "dc_MFPL3_readinplain");
my_dc_MFPL3_readinplain_hex = (func_type_dc_MFPL3_readinplain_hex)GetProcAddress(hinstLib, "dc_MFPL3_readinplain_hex");
my_dc_MFPL3_readencrypted = (func_type_dc_MFPL3_readencrypted)GetProcAddress(hinstLib, "dc_MFPL3_readencrypted");
my_dc_MFPL3_readencrypted_hex = (func_type_dc_MFPL3_readencrypted_hex)GetProcAddress(hinstLib, "dc_MFPL3_readencrypted_hex");
my_dc_MFPL3_writeinplain = (func_type_dc_MFPL3_writeinplain)GetProcAddress(hinstLib, "dc_MFPL3_writeinplain");
my_dc_MFPL3_writeinplain_hex = (func_type_dc_MFPL3_writeinplain_hex)GetProcAddress(hinstLib, "dc_MFPL3_writeinplain_hex");
my_dc_MFPL3_writeencrypted = (func_type_dc_MFPL3_writeencrypted)GetProcAddress(hinstLib, "dc_MFPL3_writeencrypted");
my_dc_MFPL3_writeencrypted_hex = (func_type_dc_MFPL3_writeencrypted_hex)GetProcAddress(hinstLib, "dc_MFPL3_writeencrypted_hex");
my_dc_auth_ulc = (func_type_dc_auth_ulc)GetProcAddress(hinstLib, "dc_auth_ulc");
my_dc_auth_ulc_hex = (func_type_dc_auth_ulc_hex)GetProcAddress(hinstLib, "dc_auth_ulc_hex");
my_dc_changekey_ulc = (func_type_dc_changekey_ulc)GetProcAddress(hinstLib, "dc_changekey_ulc");
my_dc_changekey_ulc_hex = (func_type_dc_changekey_ulc_hex)GetProcAddress(hinstLib, "dc_changekey_ulc_hex");
my_dc_pro_commandlinkEXT_hex = (func_type_dc_pro_commandlinkEXT_hex)GetProcAddress(hinstLib, "dc_pro_commandlinkEXT_hex");
/***********************************自动生成代码***added by chch 20110703****************************/
/***********************************自动生成代码***added by chch 20110703****************************/


	}

}

//初始化类
bool D8Cap::initDll(int port){
	char Buffer[MAX_PATH];
	char Direct[128];
	memset(Direct,0,128);
	DWORD dwRet;
    //dwRet=GetCurrentDirectory(MAX_PATH,Buffer);
	dwRet=GetModuleFileName(NULL,Buffer,MAX_PATH);
	if(dwRet==0||dwRet>MAX_PATH)
	{
		return NULL;
	}
	CString strPath(Buffer);
	CString strIni(Buffer);
    int index=strPath.ReverseFind('\\');
	strPath=strPath.Left(index);
	strIni=strPath.Left(index);

    CString strError("str_err_Com");
	CString strCom;
	strCom.Format("%d",port+1);
    strError+=strCom;

	CTime t = CTime::GetCurrentTime();
    CString m_timeStr = t.Format("%Y,%B,%d,%H,%M,%S");
	CString strErrorInfo(" 加载");
	CString fileName("dcrf32");
	CString postfix(".dll");
	fileName+=strCom;
	fileName+=postfix;
    strErrorInfo+=fileName;
	strErrorInfo+="出错";
	m_timeStr+=strErrorInfo;

   
	strIni += "\\READER_SETUP.ini";
	strIni.Replace("\\","\\\\");
    GetPrivateProfileString("ReadersConfig","DirectoryName","",Direct,128,strIni);
	CString strDirectoryName(Direct);
    strPath+="\\";
	strPath+=strDirectoryName;
    strPath+="\\";
	strPath+=fileName;
	strPath.Replace("\\","\\\\");
	hinstLib = LoadLibrary(strPath);
	if (hinstLib == NULL) 
	{
		WritePrivateProfileString("ErrorInfo",strError,m_timeStr,strIni);
		return false;
	}
	return true;
}

bool D8Cap::freeDll(){
	return static_cast<bool>(FreeLibrary(hinstLib));
}

D8Cap::~D8Cap(){
	freeDll();
}



//int main(){
//	D8Cap d8;
//	HANDLE icdev=d8.dc_init8(0,115200); 
//
//	if ((int)icdev<=0){
//		cout << "error" << endl;
//	}
//
//
//	return TRUE;  // return TRUE  unless you set the focus to a control
//}