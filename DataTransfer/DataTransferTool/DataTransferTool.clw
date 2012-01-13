; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDataTransferToolDlg
LastTemplate=CFileDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DataTransferTool.h"

ClassCount=4
Class1=CDataTransferToolApp
Class2=CDataTransferToolDlg
Class3=CAboutDlg

ResourceCount=2
Resource1=IDR_MAINFRAME
Class4=TargetFileChooseDialog
Resource2=IDD_DATATRANSFERTOOL_DIALOG

[CLS:CDataTransferToolApp]
Type=0
HeaderFile=DataTransferTool.h
ImplementationFile=DataTransferTool.cpp
Filter=N

[CLS:CDataTransferToolDlg]
Type=0
HeaderFile=DataTransferToolDlg.h
ImplementationFile=DataTransferToolDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_EDIT_TARGET_FILE

[CLS:CAboutDlg]
Type=0
HeaderFile=DataTransferToolDlg.h
ImplementationFile=DataTransferToolDlg.cpp
Filter=D

[DLG:IDD_DATATRANSFERTOOL_DIALOG]
Type=1
Class=CDataTransferToolDlg
ControlCount=20
Control1=IDC_LIST_TEMPLATES,SysListView32,1350631435
Control2=IDC_STATIC,button,1342178055
Control3=IDC_STATIC,button,1342178055
Control4=IDC_LIST_FIELD_TABLE,SysListView32,1350631427
Control5=IDC_BUTTON_NEW_FIELD,button,1342242816
Control6=IDC_BUTTON_DEL_FIELD,button,1342242816
Control7=IDC_BUTTON_MODIFY_FIELD,button,1342242816
Control8=IDC_BUTTON_NEW_TEMPLATE,button,1342242816
Control9=IDC_BUTTON_DEL_TEMPLATE,button,1342242816
Control10=IDC_BUTTON_APPLY_TEMPLATE,button,1342242816
Control11=IDC_BUTTON_EXIT,button,1342242816
Control12=IDC_STATIC,static,1342308352
Control13=IDC_EDIT_TARGET_FILE,edit,1350631552
Control14=IDC_BUTTON_CHOOSE_TARGET,button,1342242816
Control15=IDC_STATIC,button,1342177287
Control16=IDC_BUTTON_START_TRANSFER,button,1342242816
Control17=IDC_STATIC,static,1342308352
Control18=IDC_EDIT_CURRENT_TEMPLATE,edit,1484849280
Control19=IDC_BUTTON_CHOOSE_DIR,button,1342242816
Control20=IDC_BUTTON_SAVE_TEMPLATE,button,1342242816

[CLS:TargetFileChooseDialog]
Type=0
HeaderFile=TargetFileChooseDialog.h
ImplementationFile=TargetFileChooseDialog.cpp
BaseClass=CFileDialog
Filter=D

