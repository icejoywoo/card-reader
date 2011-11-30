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

[CLS:CCardReaderServerDlg]
Type=0
HeaderFile=CardReaderServerDlg.h
ImplementationFile=CardReaderServerDlg.cpp
Filter=D
LastObject=IDC_EDIT_LOG
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=CardReaderServerDlg.h
ImplementationFile=CardReaderServerDlg.cpp
Filter=D

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
ControlCount=7
Control1=IDC_EDIT_LOG,edit,1350631620
Control2=IDC_BUTTON1,button,1342242816
Control3=IDC_BUTTON_START,button,1342242816
Control4=IDC_BUTTON_STOP,button,1342242816
Control5=IDC_BUTTON4,button,1342242816
Control6=IDC_BUTTON5,button,1342242816
Control7=IDC_BUTTON_RESTART,button,1342242816

[DLG:IDD_SERVERSETTING_DIALOG]
Type=1
Class=ServerSetting
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[CLS:ServerSetting]
Type=0
HeaderFile=ServerSetting.h
ImplementationFile=ServerSetting.cpp
BaseClass=CDialog
Filter=D

