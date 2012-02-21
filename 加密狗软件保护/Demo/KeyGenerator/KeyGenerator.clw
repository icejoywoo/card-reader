; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CKeyGeneratorDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "KeyGenerator.h"

ClassCount=3
Class1=CKeyGeneratorApp
Class2=CKeyGeneratorDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_KEYGENERATOR_DIALOG

[CLS:CKeyGeneratorApp]
Type=0
HeaderFile=KeyGenerator.h
ImplementationFile=KeyGenerator.cpp
Filter=N

[CLS:CKeyGeneratorDlg]
Type=0
HeaderFile=KeyGeneratorDlg.h
ImplementationFile=KeyGeneratorDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CKeyGeneratorDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=KeyGeneratorDlg.h
ImplementationFile=KeyGeneratorDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_KEYGENERATOR_DIALOG]
Type=1
Class=CKeyGeneratorDlg
ControlCount=9
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_REQUEST_FILE,edit,1350631552
Control3=IDC_BUTTON_CHOOSE_FILE,button,1342242816
Control4=IDC_BUTTON_GENERATE_KEY,button,1342242816
Control5=IDC_LIST_RESULT,listbox,1352728833
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_DAYS,edit,1350631552
Control9=IDC_STATIC,button,1342177287

