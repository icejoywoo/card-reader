#ifndef __SmartComDefine_H__
#define __SmartComDefine_H__

//
#define  SC_SERIAL(retcode) ((retcode)>>16)
#define  SC_CODE(retcode)   (-((retcode)&0xffff))

//


//
enum FILE_TYPE{
	FILE_HEAD=2,    //头文件
	FILE_BODY=1     //体文件
};

enum CARD_AB{
	CARD_A=1,
	CARD_B=2
};

enum CARD_POWER{
	POWER_5V=1,
	POWER_3V=2,
	POWER_1_8V=3
};

#define  CARDA_FLAG    1
#define  CARDB_FLAG    2

//
#define  SC_SUCCESS           0
#define  SC_NULL              0
#define  SC_EXCUTING         -1
//ERRORS
#define  SCERR_OPERROR        -4
#define  SCERR_TIMEOUT        -1
#define  SCERR_RESET_FAIL     -5
#define  SCERR_DOWNLOAD_FAIL  -6
#define  SCERR_INVALID_COMM   -2
#define  SCERR_OPENFILE_FAIL  -8
#define  SCERR_MACNO_OUTRANGE -3
#define  SCERR_CMDFORMAT_ERR  -9
#define  SCERR_DRIVER_NOTINSTALL -7
#define  SCERR_INVALID_DATA      -10


#endif