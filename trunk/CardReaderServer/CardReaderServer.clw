; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=ServerSetting
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "CardReaderServer.h"

ClassCount=4
Class1=CCardReaderServerApp
Class2=CCardReaderServerDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_CARDREADERSERVER_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class4=ServerSetting
Resource4=IDD_SERVERSETTING_DIALOG

[CLS:CCardReaderServerApp]
Type=0
HeaderFile=CardReaderServer.h
ImplementationFile=CardReaderServer.cpp
Filter=N
LastObject=CCardReaderServerApp

[CLS:CCardReaderServerDlg]
Type=0
HeaderFile=CardReaderServerDlg.h
ImplementationFile=CardReaderServerDlg.cpp
Filter=D
LastObject=CCardReaderServerDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=CardReaderServerDlg.h
ImplementationFile=CardReaderServerDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CARDREADERSERVER_DIALOG]
Type=1
Class=CCardReaderServerDlg
ControlCount=13
Control1=IDC_EDIT_LOG,edit,1353779396
Control2=IDC_BUTTON_START,button,1342242816
Control3=IDC_BUTTON_STOP,button,1342242816
Control4=IDC_BUTTON_RESTART,button,1342242816
Control5=IDC_BUTTON_CLEAR,button,1342242816
Control6=IDC_BUTTON_LOG,button,1342242816
Control7=IDC_BUTTON_SETTING,button,1073807360
Control8=IDC_TREE_CLIENTS,SysTreeView32,1350631424
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EDIT_ERRORS,edit,1350633600
Control12=IDC_EDIT_WARNS,edit,1350633600
Control13=IDC_STATIC,button,1342177287

[DLG:IDD_SERVERSETTING_DIALOG]
Type=1
Class=ServerSetting
ControlCount=14
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308353
Control4=IDC_EDIT_PORT,edit,1350631552
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,button,1342177287
Control7=IDC_BUTTON_ADD,button,1342242816
Control8=IDC_BUTTON_DEL,button,1342242816
Control9=IDC_EDIT_READER_ID,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,static,1342308352
Control13=IDC_EDIT_READER_COM,edit,1350631552
Control14=IDC_LIST_READERS,SysListView32,1350631425

[CLS:ServerSetting]
Type=0
HeaderFile=ServerSetting.h
ImplementationFile=ServerSetting.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT_PORT
VirtualFilter=dWC

