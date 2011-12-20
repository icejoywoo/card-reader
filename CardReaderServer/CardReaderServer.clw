; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCardReaderServerDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "CardReaderServer.h"

ClassCount=4
Class1=CCardReaderServerApp
Class2=CCardReaderServerDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_CARDREADERSERVER_DIALOG
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
LastObject=IDC_TREE_CLIENTS
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
ControlCount=8
Control1=IDC_EDIT_LOG,edit,1353779396
Control2=IDC_BUTTON_START,button,1342242816
Control3=IDC_BUTTON_STOP,button,1342242816
Control4=IDC_BUTTON_RESTART,button,1342242816
Control5=IDC_BUTTON_CLEAR,button,1342242816
Control6=IDC_BUTTON_LOG,button,1342242816
Control7=IDC_BUTTON_SETTING,button,1342242816
Control8=IDC_TREE_CLIENTS,SysTreeView32,1350631424

[DLG:IDD_SERVERSETTING_DIALOG]
Type=1
Class=ServerSetting
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308353
Control4=IDC_EDIT_PORT,edit,1350631552
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,button,1342177287
Control7=IDC_BUTTON_ADD,button,1342242816
Control8=IDC_BUTTON_DEL,button,1342242816
Control9=IDC_LIST_READER,SysListView32,1350631441

[CLS:ServerSetting]
Type=0
HeaderFile=ServerSetting.h
ImplementationFile=ServerSetting.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_BUTTON_ADD
VirtualFilter=dWC

