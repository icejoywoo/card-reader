
#ifndef ULONG
#define ULONG unsigned long
#endif

#ifndef HUINT
#define HUINT unsigned short
#endif

#ifndef UCHAR
#define UCHAR unsigned char
#endif

#ifndef WORD
#define WORD unsigned short
#endif
#define MHSTATUS ULONG


#define INSTALL_ONLY_USB_DOG_DRVIER				1
#define INSTALL_ONLY_PARALLEL_DOG_DRVIER		2
#define INSTALL_ALL_DOG_DRVIER					3

#define UNINSTALL_ONLY_USB_DOG_DRVIER			1
#define UNINSTALL_ONLY_PARALLEL_DOG_DRVIER		2
#define UNINSTALL_ALL_DOG_DRVIER				3

typedef int (PASCAL *CHECKVERSION) (BOOL bShowMessageBox,int *piUsbVerStatus,int*piParVerStatus);
typedef int (PASCAL *INSTALL)(int iFlag);
typedef int (PASCAL *UNINSTALL)(int iFlag);
